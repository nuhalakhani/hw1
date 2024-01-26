#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val) {
  if (head_ == nullptr && tail_ == nullptr) {
    head_ = new Item();
    tail_ = head_;
    tail_->val[tail_->first] = val;
    }
    else if (tail_->last != ARRSIZE) {
      tail_->val[tail_->last] = val;
    }
    else {
      Item* tail = new Item();
      tail_->next = tail;
      tail->prev = tail_;
      tail_ = tail;
      tail_->val[tail_->first] = val;
    }
    ++(tail_->last);
    ++(size_);
  }


void ULListStr::push_front(const std::string& val) {
  if (head_ == nullptr && tail_ == nullptr) {
    head_ = new Item();
    tail_ = head_;
    head_->val[head_->last] = val;
    ++(head_->last);
  }
  else if(head_->first == 0) {
    Item* temp = new Item();
    temp->first = ARRSIZE - 1;
    temp->val[temp->first] = val;
    temp->last = ARRSIZE;
    head_->prev = temp;
    temp->next = head_;
    head_ = temp;
  }
  else {
    --(head_->first);
    head_->val[head_->first] = val;
  }
  ++(size_);
}

void ULListStr::pop_back() {
  if (tail_ == nullptr || size_ == 0) {
    return;
  }
  else if (size_ == 1) {
    delete tail_;
    head_ = nullptr;
    tail_ = head_;
  }
  else if (tail_->last == 1) {
    tail_ = tail_->prev;
    delete tail_->next;
    tail_->next = nullptr;
  }
  else {
    --(tail_->last);
  }
  --(size_);
}

void ULListStr::pop_front() {
  if (head_ == nullptr || size_ == 0) {
    return;
  }
  else if (size_ == 1) {
    delete head_;
    head_ = nullptr;
    tail_ = head_;
  }
  else if (head_->last - head_->first == 1) {
    head_ = head_->next;
    delete head_->prev;
    head_->prev = nullptr;
  }
  else {
    ++(head_->first);
  }
  --(size_);
}

std::string const& ULListStr::back() const {
  return tail_->val[(tail_->last) - 1];
}

std::string const& ULListStr::front() const {
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  if (loc >= size_ || loc < 0) {
    return nullptr;
  }
  for (Item* temp = head_; temp != nullptr; temp = temp->next) {
    size_t nSize = temp->last - temp->first;
    if (loc < nSize) {
      return &temp->val[temp->first + loc];
    }
    loc -= nSize;
  }
  return nullptr;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
