// Copyright 2020 by Polevoy Dmitry under Free Public License 1.0.0

#pragma once
#ifndef STAKL_STAKL_H
#define STAKL_STAKL_H

#include <memory>

//! \class StackL stackl.h stackl/stackl.h
//! \brief Стек значений float с реализацией на списке.
class StackL {
public:
  StackL() = default;
  StackL(const StackL& s);
  StackL& operator=(const StackL& rhs);
  ~StackL();
  bool is_empty() const noexcept;
  void push(const float value);
  void pop() noexcept;
  float& top();
  const float& top() const;
private:
  struct Node {
    float value = 0.0f;
    Node* next = nullptr;
  };
private:
  Node* head_ = nullptr;
};

#endif