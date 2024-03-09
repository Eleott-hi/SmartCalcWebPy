#include "Lexem.h"

#include <cmath>
#include <optional>
#include <regex>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "algorithm.h"

namespace s21 {

std::ostream &operator<<(std::ostream &os, const Lexem &lexem) {
  return os << "{ Lexem: \'" << lexem.lexem_ << "\',\tValue: " << lexem.value_
            << ",\tPriority: " << Cast<int>(lexem.priority_) << " }";
}

std::optional<Lexem> GetLexem(std::string const &str, size_t index) {
  static std::vector<Lexem> lexems_ = {
      {"asin", s21::Priority::FUN,
       [](double x, double y) { return std::asin(x); }},
      {"acos", s21::Priority::FUN,
       [](double x, double y) { return std::acos(x); }},
      {"atan", s21::Priority::FUN,
       [](double x, double y) { return std::atan(x); }},
      {"cos", s21::Priority::FUN,
       [](double x, double y) { return std::cos(x); }},
      {"sin", s21::Priority::FUN,
       [](double x, double y) { return std::sin(x); }},
      {"tan", s21::Priority::FUN,
       [](double x, double y) { return std::tan(x); }},
      {"log", s21::Priority::FUN,
       [](double x, double y) { return std::log10(x); }},
      {"ln", s21::Priority::FUN,
       [](double x, double y) { return std::log(x); }},
      {"sqrt", s21::Priority::FUN,
       [](double x, double y) { return std::sqrt(x); }},
      {"^", s21::Priority::POW, [](double x, double y) { return pow(x, y); }},
      {"%", s21::Priority::MUL, [](double x, double y) { return fmod(x, y); }},
      {"*", s21::Priority::MUL, [](double x, double y) { return x * y; }},
      {"/", s21::Priority::MUL, [](double x, double y) { return x / y; }},
      {"-", s21::Priority::ADD, [](double x, double y) { return x - y; }},
      {"+", s21::Priority::ADD, [](double x, double y) { return x + y; }},
      {"(", s21::Priority::PARENTHESIS_OPEN, nullptr},
      {")", s21::Priority::PARENTHESIS_CLOSE, nullptr},
      {"x", s21::Priority::NUM, nullptr},
  };

  auto it = FindIf(lexems_, [str, index](const Lexem &lexem) {
    return str.find(lexem.lexem_, index) == index;
  });

  if (it != lexems_.end()) return *it;

  return std::nullopt;
}

std::vector<Lexem> Lexem::GetLexemList(std::string const &expression) {
  std::string str = ProcessExpression(expression);
  std::vector<Lexem> lexems;

  for (size_t i = 0; i < str.size();) {
    if (auto lexem = GetLexem(str, i); lexem) {
      lexems.push_back(*lexem);
      i += lexem->lexem_.size();

    } else {
      size_t tmp = 0;

      try {
        auto value = std::stod(str.substr(i), &tmp);
        lexems.push_back({str.substr(i, tmp), Priority::NUM, nullptr, value});
        i += tmp;

      } catch (const std::exception &e) {
        std::string error_messege = "Invalid lexem: ";
        std::string pointer(error_messege.size() + str.size(), '~');
        pointer.at(error_messege.size() + i) = '^';

        throw std::invalid_argument(error_messege + str + "\n" + pointer);
      }
    }
  }

  CheckLexem(lexems);

  return lexems;
}

void Lexem::CheckLexem(std::vector<Lexem> const &lexems) {
  static const std::vector<std::vector<bool>> checkMatrix = {
      // NUM   P_O   P_C    ADD    MUL    POW    FUN    END      rh/lh
      {false, false, true, true, true, true, false, true},      // NUM
      {true, true, false, false, false, false, true, false},    // PARENTH_OPEN
      {false, false, true, true, true, true, false, true},      // PARENTH_ClOSE
      {true, true, false, false, false, false, true, false},    // ADD
      {true, true, false, false, false, false, true, false},    // MUL
      {true, true, false, false, false, false, true, false},    // POW
      {false, true, false, false, false, false, false, false},  // FUN
  };

  for (size_t i = 0; i < lexems.size(); i++) {
    auto const &lh = lexems.at(i);
    auto const &rh =
        (i + 1 == lexems.size()) ? Lexem{"", Priority::END} : lexems.at(i + 1);

    if (!checkMatrix.at(Cast<int>(lh.priority_)).at(Cast<int>(rh.priority_))) {
      throw std::invalid_argument("Invalid Lexem Pair: '" + lh.lexem_ + "' '" +
                                  rh.lexem_ + "'");
    }
  }
}

std::string Lexem::ProcessExpression(std::string const &str) {
  std::unordered_map<std::string, std::string> map = {
      {" ", ""},      {"\t", ""},        {"\n", ""},   {"\r", ""},
      {"^\\-", "0-"}, {"\\(\\-", "(0-"}, {"^\\+", ""}, {"\\(\\+", "("},
  };

  auto count_breckets = [](std::string const &str) {
    int count = 0;

    for (auto i : str) {
      if (i == ')') count--;
      if (i == '(') count++;
      if (count < 0) return count;
    }

    return count;
  };

  auto brecket_count = count_breckets(str);
  if (brecket_count < 0) throw std::invalid_argument("Invalid brecket's count");

  std::string processed_str = str + std::string(brecket_count, ')');

  ForEach(processed_str, [](char ch) { return std::tolower(ch); });

  ForEach(map, [&processed_str](auto const &el) {
    auto const &[key, value] = el;
    processed_str = std::regex_replace(processed_str, std::regex(key), value);
  });

  return processed_str;
}
}  // namespace s21