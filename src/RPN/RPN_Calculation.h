#ifndef _RPN_CALCULATION_H_
#define _RPN_CALCULATION_H_

#include <functional>
#include <list>
#include <map>
#include <stack>
#include <string>
#include <variant>

namespace s21 {

class RPN_Calculation {
  enum Type { NUM, VAR, OPERATION };
  enum Priority { P, ADD, MUL, UNARY, POW, FUN };
  struct Lexem {
    std::variant<double, char> value;
    Type type;
  };

 public:
  RPN_Calculation() = default;
  ~RPN_Calculation() = default;

  static std::string form_final_expression(const std::string &source_str);
  static bool check_expression(const std::string &source_str);
  static int count_breckets(const std::string &str);
  double calc(const std::string &str, double x = 0);

 private:
  void form_deque(const std::string &str);
  double calc_lexems(double x = 0);

  template <typename type>
  static type my_pop(std::stack<type> &stack);

  bool is_func(char ch) const;
  static bool is_one_arg_func(char ch);
  static Priority get_priority(char ch);
  static bool is_two_args_func(char ch);
  static bool is_digit(const std::string &str, size_t i);
  static std::string replace_expression_patterns(const std::string &source_str);

 private:
  std::list<Lexem> lexems_;
  std::string str_expression;
  static std::map<char, std::function<double(double, double)>> function;
};
}  // namespace s21

#endif  // _RPN_CALCULATION_H_
