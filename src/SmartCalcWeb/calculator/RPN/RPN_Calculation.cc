#include "RPN_Calculation.h"

#include <cmath>
#include <regex>
// #include <array>

#include <iostream>

namespace s21 {

template <typename Type>
void Print(Type const &value) {
#ifdef DEBUG
  std::cout << "Value: " << value << std::endl;
#endif
}

std::map<char, std::function<double(double, double)>>
    RPN_Calculation::function = {
        {'l', [](double x, double y = 0.0) { return log10(x) + y; }},
        {'q', [](double x, double y = 0.0) { return sqrt(x) + y; }},
        {'o', [](double x, double y = 0.0) { return acos(x) + y; }},
        {'i', [](double x, double y = 0.0) { return asin(x) + y; }},
        {'a', [](double x, double y = 0.0) { return atan(x) + y; }},
        {'c', [](double x, double y = 0.0) { return cos(x) + y; }},
        {'s', [](double x, double y = 0.0) { return sin(x) + y; }},
        {'t', [](double x, double y = 0.0) { return tan(x) + y; }},
        {'n', [](double x, double y = 0.0) { return log(x) + y; }},
        {'u', [](double x, double y = 0.0) { return y - x; }},
        {'%', [](double x, double y) { return fmod(x, y); }},
        {'^', [](double x, double y) { return pow(x, y); }},
        {'+', [](double x, double y) { return x + y; }},
        {'-', [](double x, double y) { return x - y; }},
        {'*', [](double x, double y) { return x * y; }},
        {'/', [](double x, double y) { return x / y; }}};

RPN_Calculation::Priority RPN_Calculation::get_priority(char ch) {
  static std::string operations = "(+-*/%u^";
  static Priority priority[] = {P, ADD, ADD, MUL, MUL, MUL, UNARY, POW};

  return operations.find(ch) == std::string::npos
             ? FUN
             : priority[operations.find(ch)];
}

bool RPN_Calculation::is_two_args_func(char ch) {
  static std::string two_args_func = "+-*/%^";

  return two_args_func.find(ch) != std::string::npos;
}

bool RPN_Calculation::is_one_arg_func(char ch) {
  static std::string one_arg_func = "oiacstqnlu";

  return one_arg_func.find(ch) != std::string::npos;
}

bool RPN_Calculation::is_digit(const std::string &str, size_t i) {
  return std::isdigit(str.at(i)) ||  //
         str.find("inf", i) == i ||  //
         str.find("nan", i) == i;
}

int RPN_Calculation::count_breckets(const std::string &str) {
  int count = 0;

  for (auto i : str) {
    if (i == ')') count--;
    if (i == '(') count++;
    if (count < 0) return count;
  }

  return count;
}

std::string RPN_Calculation::form_final_expression(
    const std::string &source_str) {
  static std::regex regex("[e%*/^+-]$");

  std::string str = source_str;
  std::regex_search(str, regex) ? str.append(")(")
                                : str.append(count_breckets(str), ')');

  return str;
}

bool RPN_Calculation::check_expression(const std::string &source_str) {
  if (source_str.size() > 255 || count_breckets(source_str) < 0) return false;

  std::string str = std::regex_replace(source_str, std::regex("^[+]"), "-");
  str = std::regex_replace(str, std::regex("\\([+]"), "(-");
  str = std::regex_replace(str, std::regex("inf|nan"), "x");
  str = replace_expression_patterns(str);

  std::vector<std::regex> arr = {// 1) 1.1.1, 1..1
                                 std::regex("(\\d*[.]\\d*[.])|([.][^\\de])"),
                                 // 2) +*, *)
                                 std::regex("[%*/u^+-][%*/^+-.)]"),
                                 // 3) start *, (*
                                 std::regex("(^[%/^*.])|(\\([/^*%.])"),
                                 // 4) after ) - sin(, 123, x
                                 std::regex("\\)[\\doiacstqnlx(]"),
                                 // 5) xx, 1x, 1sin(, xsin(
                                 std::regex("[\\dx][oiacstqnlx]"),
                                 // 6) x1, x.
                                 std::regex("x[\\d.]"),
                                 // 7) 1(, x(
                                 std::regex("[\\dx.]\\("),
                                 // 8) (-)
                                 std::regex("\\([^\\dx]*\\)"),
                                 // 9) ^e, xe
                                 std::regex("^e|[^\\d.]e"),
                                 // 10) ex, esin(, e*
                                 std::regex("e[^\\d+-]"),
                                 // 11) e+x, e+sin(
                                 std::regex("e[+-][^\\d]"),
                                 // 12) e+1.1,
                                 std::regex("e[+-]?[\\d]*[.]"),
                                 // 13) ^001, (001.1,
                                 std::regex("^0{2}|[^\\d.]0{2}")};

  for (size_t i = 0; i < arr.size(); ++i)
    if (std::regex_search(str, arr[i])) return false;

  Print(str);

  return true;
}

std::string RPN_Calculation::replace_expression_patterns(
    const std::string &source_str) {
  static std::vector<std::string> pattern = {
      " ",    "acos", "asin", "atan", "cos",  "sin",  "tan",
      "sqrt", "ln",   "log",  "^-",   "\\(-", "^\\+", "\\(\\+"};

  static std::vector<std::string> change = {"",  "o", "i", "a", "c",  "s", "t",
                                            "q", "n", "l", "u", "(u", "",  "("};

  std::string str = source_str;
  for (size_t i = 0; i < pattern.size(); i++)
    str = std::regex_replace(str, std::regex(pattern[i]), change[i]);

  return str;
}

template <typename type>
type RPN_Calculation::my_pop(std::stack<type> &stack) {
  if (stack.empty()) throw std::invalid_argument("my_pop: stack is empty");

  auto res = stack.top();
  stack.pop();
  return res;
}

double RPN_Calculation::calc(const std::string &str, double x) {
  double res = NAN;
  bool ok = true;

  if (str_expression != str &&
      (ok = check_expression(form_final_expression(str))))
    try {
      form_deque(replace_expression_patterns(str));
      str_expression = str;
    } catch (const std::out_of_range &e) {
      ok = false;
      Print(e.what());
    } catch (...) {
      ok = false;
      Print("form_deque: Something's wrong");
    }

  if (ok) try {
      res = calc_lexems(x);
    } catch (const std::invalid_argument &e) {
      Print(e.what());
    } catch (const std::bad_variant_access &e) {
      Print(e.what());
    } catch (...) {
      Print("calc_lexems: Something's wrong");
    }
  return res;
}

// Скобочная запись функций
void RPN_Calculation::form_deque(const std::string &str) {
  std::list<Lexem> lexems;
  std::stack<Lexem> lex_stack;

  for (size_t i = 0; i < str.size();) {
    if (is_digit(str, i)) {
      size_t tmp = 0;
      lexems.push_back({std::stod(str.substr(i), &tmp), Type::NUM});
      i += tmp;

    } else if (str.at(i) == 'x') {
      lexems.push_back({0.0, Type::VAR});
      i++;

    } else if (str.at(i) == '(') {
      lex_stack.push({str.at(i++), Type::OPERATION});

    } else if (str.at(i) == ')') {
      while (std::get<char>(lex_stack.top().value) != '(') {
        lexems.push_back(my_pop(lex_stack));
      }

      lex_stack.pop();
      i++;

    } else {
      while (lex_stack.size() &&
             ((get_priority(str.at(i)) <
               get_priority(std::get<char>(lex_stack.top().value))) ||
              (str.at(i) != '^' &&
               get_priority(str.at(i)) ==
                   get_priority(std::get<char>(lex_stack.top().value))))) {
        lexems.push_back(my_pop(lex_stack));
      }

      lex_stack.push({str.at(i++), Type::OPERATION});
    }
  }

  while (lex_stack.size()) lexems.push_back(my_pop(lex_stack));

  lexems_ = std::move(lexems);
}

double RPN_Calculation::calc_lexems(double x) {
  std::stack<double> stack;

  for (const auto &i : lexems_) {
    if (i.type == NUM || i.type == VAR) {
      stack.push(std::get<double>(i.type == VAR ? x : i.value));
      continue;
    }

    char ch = std::get<char>(i.value);

    if (is_two_args_func(ch)) {
      double num_1 = my_pop(stack), num_2 = my_pop(stack);
      stack.push(function.at(ch)(num_2, num_1));

    } else if (is_one_arg_func(ch)) {
      stack.push(function.at(ch)(my_pop(stack), 0.0));

    } else {
      throw std::invalid_argument("calc_lexems: No such function");
    }
  }

  if (stack.size() != 1)
    throw std::invalid_argument("calc_lexems: stack.size() != 1");

  return stack.top();
}

}  // namespace s21
