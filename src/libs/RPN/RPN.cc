#include "RPN.h"

#include <stack>
#include <stdexcept>

#include "algorithm.h"

namespace s21 {

template <typename... Args>
void Print(Args const &...args) {
  // #ifdef DEBUG
  ((std::cout << args << ' '), ...);
  std::cout << std::endl;
  // #endif
}

RPN::Lexems RPN::FormRPN(Lexems const &lexems) {
  Lexems rpn;
  std::stack<Lexem> stack;

  for (auto const &lexem : lexems) {
    if (lexem == Priority::NUM) {
      rpn.push_back(lexem);

    } else if (lexem == Priority::PARENTHESIS_OPEN) {
      stack.push(lexem);

    } else if (lexem == Priority::PARENTHESIS_CLOSE) {
      while (stack.top() != Priority::PARENTHESIS_OPEN) {
        rpn.push_back(Pop(stack));
      }
      stack.pop();

    } else {
      while (!stack.empty() &&
             (lexem < stack.top() ||
              lexem != Priority::POW && lexem == stack.top())) {
        rpn.push_back(Pop(stack));
      }
      stack.push(lexem);
    }
  }

  while (!stack.empty()) rpn.push_back(Pop(stack));

  return rpn;
}

double RPN::CalculateLexems(Lexems const &lexems, double x_value) {
  std::stack<double> stack;

  for (auto &lexem : lexems_) {
    if (lexem == Priority::NUM) {
      if (lexem == "x") lexem.value_ = x_value;
      stack.push(lexem.value_);

      Print("Stack value:", lexem);
      continue;
    }

    double y = lexem == Priority::FUN ? 0.0 : Pop(stack);
    double x = Pop(stack);
    double result = lexem.func_(x, y);

    Print("Calculate:", "\n\tLexem:", lexem, "\n\tx:", x, "\n\ty:", y,
          "\n\tresult:", result);
    stack.push(result);
  }

  if (stack.size() != 1)
    throw std::invalid_argument("CalculateLexems: stack.size() != 1");

  return stack.top();
}

double RPN::Calculate(std::string const &expression, double x) {
  Print("Expression:", expression, ";\tx:", x);
  if (expression_ != expression) {
    Print("Unknown expression");

    Print("Form lexems:");
    auto lexems = Lexem::GetLexemList(expression);
    for (auto const &lexem : lexems) Print(lexem);

    Print("Form RPN:");
    lexems_ = FormRPN(lexems);
    for (auto const &lexem : lexems_) Print(lexem);

    Print("Save expression...");
    expression_ = expression;
  }

  Print("Calculating...");
  return CalculateLexems(lexems_, x);
}

}  // namespace s21