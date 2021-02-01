#include <stackl/stackl.h>

#include <stdexcept>
#include <iostream>
StackL::StackL(const StackL& s) {
  if (s.is_empty()) { 
    return; 
  }
  head_ = new Node;
  Node* snext = s.head_;
  Node* thishead = head_;
  while(snext != nullptr)
  {
    thishead->value = snext->value;
    snext = snext->next;
    if (snext != nullptr) {
      thishead->next = new Node;
      thishead = thishead->next;
    }
  }
  delete snext;
}

StackL& StackL::operator=(const StackL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  while (!is_empty()) {
    pop();
  }
  if (rhs.is_empty()) {
    head_ = nullptr;
    return *this;
  }
  head_ = new Node;
  Node* snext = rhs.head_;
  Node* thishead = head_;
  while (snext != nullptr)
  {
    thishead->value = snext->value;
    snext = snext->next;
    if (snext != nullptr) {
      thishead->next = new Node;
      thishead = thishead->next;
    }
  }

  delete snext;
  return *this;
}

void StackL::push(const float value) {
  Node* temp = new Node;
  temp->value = value;
  if (head_ == nullptr) {
    head_ = temp;
  }
  else {
     temp->next = head_;
     head_ = temp;
  }
}

void StackL::pop() noexcept {
  if (head_ != nullptr) {
    Node* temp_node = head_->next;
    delete head_;
    head_ = temp_node;
  }
}

float& StackL::top() {
  if (is_empty()){
    throw std::exception("Stack is empty");
  }
  return head_->value;
}

const float& StackL::top() const {
  if (is_empty()) throw std::exception("Stack is empty");
  return head_->value;
}

bool StackL::is_empty() const noexcept {
  return head_ == nullptr;
}

StackL::~StackL() {
  while (!this->is_empty()) {
    pop();
  }
}