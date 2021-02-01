// Copyright 2020 by Polevoy Dmitry under Free Public License 1.0.0

#pragma once
#ifndef QUEUEA_QUEUEA_H
#define QUEUEA_QUEUEA_H

#include <cstddef>

//! \class QueueA queuea.h queuea\queuea.h
//! \brief Очередь значений float с реализацией на массиве (подвижные концы).
class QueueA {
public:
  QueueA() = default;
  QueueA(const QueueA& q);
  QueueA& operator=(const QueueA& q);
  ~QueueA();
  bool is_empty() const noexcept;
  void push(const float value);
  void pop() noexcept;
  float& top();
  const float& top() const;
  std::ptrdiff_t capacity_ = 0;
  std::ptrdiff_t i_head_ = -1;
  std::ptrdiff_t i_tail_ = -1;
private:
  float* data_ = nullptr; 
};

#endif