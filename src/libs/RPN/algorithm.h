#ifndef MEMORY_COMMON_ALGORITHM_H_
#define MEMORY_COMMON_ALGORITHM_H_

#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <vector>

template <typename ContainerOut, typename ContainerIn, typename Function>
ContainerOut Transform(ContainerIn const& in, Function const& function) {
  ContainerOut out;
  out.reserve(in.size());
  std::transform(in.begin(), in.end(), std::back_inserter(out), function);
  return out;
}

template <typename ContainerOut, typename ContainerIn, typename Function>
ContainerOut Transform(ContainerIn& in, Function const& function) {
  ContainerOut out;
  out.reserve(in.size());
  std::transform(in.begin(), in.end(), std::back_inserter(out), function);
  return out;
}

template <typename Container, typename Function>
void ForEach(Container const& container, Function const& function) {
  std::for_each(container.begin(), container.end(), function);
}

template <typename Container, typename Function>
void ForEach(Container& container, Function const& function) {
  std::for_each(container.begin(), container.end(), function);
}

template <typename Container, typename Function>
void ReverseForEach(Container& container, Function const& function) {
  std::for_each(container.rbegin(), container.rend(), function);
}

template <typename Container, typename Function>
void ReverseForEach(const Container& container, Function const& function) {
  std::for_each(container.rbegin(), container.rend(), function);
}

template <typename ContainerOut, typename ContainerIn, typename Function>
ContainerOut Accumulate(ContainerIn const& in, ContainerOut&& _out,
                        Function const& function) {
  return std::accumulate(in.begin(), in.end(), _out, function);
}

template <typename Container,
          typename Compar = std::less<typename Container::value_type>>
void Sort(Container& in) {
  std::sort(in.begin(), in.end(), Compar());
}

template <typename Container, typename Function>
typename Container::iterator FindIf(Container& container,
                                    Function const& function) {
  return std::find_if(container.begin(), container.end(), function);
}

void s21_memcpy(void* dst, void* src, size_t size);

template <typename Type>
std::vector<char> Convert(std::vector<Type>& in) {
  auto size = sizeof(Type) * in.size();
  std::vector<char> out(size);
  s21_memcpy(out.data(), in.data(), size);
  return out;
}

template <typename T>
T Cast(void* ptr) {
  return reinterpret_cast<T>(ptr);
}

template <typename TypeOut, typename TypeIn>
TypeOut Cast(TypeIn ptr) {
  return static_cast<TypeOut>(ptr);
}

template <typename Type, typename Container>
Type Pop(Container& stack) {
  if (stack.empty()) throw std::invalid_argument("Pop: stack is empty");

  Type res = stack.top();
  stack.pop();
  return res;
}
#endif  // MEMORY_COMMON_ALGORITHM_H_
