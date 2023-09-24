#include <functional>
#include <iostream>
#include <vector>

namespace s21 {

enum class Priority {
  NUM,                // 0
  PARENTHESIS_OPEN,   // 1
  PARENTHESIS_CLOSE,  // 2
  ADD,                // 3
  MUL,                // 4
  POW,                // 5
  FUN,                // 6
  END,                // 7
};

struct Lexem {
  std::string lexem_;
  Priority priority_;
  std::function<double(double, double)> func_ = nullptr;
  double value_ = 0.0;

  bool operator<(const Lexem &other) const {
    return priority_ < other.priority_;
  }
  bool operator>(const Lexem &other) const {
    return priority_ > other.priority_;
  }
  bool operator==(const Lexem &other) const {
    return priority_ == other.priority_;
  }
  bool operator==(std::string const &lexem) const { return lexem_ == lexem; }
  bool operator!=(const Lexem &other) const { return !(*this == other); }

  bool operator==(Priority priority) const { return priority_ == priority; }
  bool operator<(Priority priority) const { return priority_ < priority; }
  bool operator>(Priority priority) const { return priority_ > priority; }
  bool operator!=(Priority priority) const { return !(*this == priority); }

  friend std::ostream &operator<<(std::ostream &os, const Lexem &lexem);
  static std::vector<Lexem> GetLexemList(std::string const &str);

 private:
  static void CheckLexem(std::vector<Lexem> const &lexems);
  static std::string ProcessExpression(std::string const &str);
};
}  // namespace s21