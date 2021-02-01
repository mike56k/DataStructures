// Copyright 2019 by Polevoy Dmitry under Free Public License 1.0.0

#include <queuea/queuea.h>

#include <stdexcept>


QueueA::QueueA(const QueueA& q) {
  if(q.is_empty()) return;
  capacity_ = q.capacity_;
  i_head_ = q.i_head_;
  i_tail_ = q.i_tail_;
  data_ = new float[capacity_] {0};
  for (int i = 0; i < capacity_; i++) {
    data_[i] = q.data_[i];
  }
}

QueueA& QueueA::operator=(const QueueA& rhs) {
  if(rhs.is_empty()) return *this;
  if(data_ != nullptr) delete[] data_;
  capacity_ = rhs.capacity_;
  data_ = new float[capacity_];
  i_head_ = rhs.i_head_;
  i_tail_ = rhs.i_tail_;
  for (int i = 0; i < capacity_; i++) {
    data_[i] = rhs.data_[i];
  }
  return *this;
}

QueueA::~QueueA() {
  delete[] data_;
}

void QueueA::push(const float value) {
  if (data_ == nullptr) {
    capacity_ = 10;
    data_ = new float[capacity_]{0};
    i_head_ = 0;
    i_tail_ = 0;
  }
 if ((i_tail_ < i_head_ && i_head_ - i_tail_ == 1) || 
      (i_head_ == 0 && i_tail_ == capacity_ - 1)) {
        float *temp_data = new float[capacity_];
        int i = 0;
        while(!is_empty()){
          temp_data[i] = top();
          pop();
          i++;
        }
        delete[] data_;

        data_ = new float[capacity_ * 2]{0};
        for (int i = 1, j = 0; j < capacity_-1; i++, j++) {
          data_ [i] = temp_data[j];

        }

        i_head_ = 0;
        i_tail_ = capacity_ - 1;
        capacity_ *= 2;
  }
  i_tail_ = (i_tail_ + 1) % capacity_;
  data_[i_tail_] = value;

}

void QueueA::pop() noexcept {
  if (is_empty()) {
    return;
  }
  i_head_ = (i_head_ + 1) % capacity_;
}

float& QueueA::top() {
  if (!is_empty()) {
    return data_[(i_head_ + 1)%capacity_];
  }
  else {
    throw std::exception("Queue is empty");
  }
}

const float& QueueA::top() const {
  if (!is_empty()) {
    return data_[(i_head_+1)%capacity_];
  }
  else {
    throw std::exception("Queue is empty");
  }
}

bool QueueA::is_empty() const noexcept {
  return i_head_ == i_tail_;
}

