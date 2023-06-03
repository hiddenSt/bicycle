#pragma once

namespace bicycle::container::intrusive {

template <typename T>
struct ListNode {
  ListNode* next_ = nullptr;

  void LinkBefore(ListNode* next) noexcept {
    next_ = next;
  }

  void ResetNext() noexcept {
    next_ = nullptr;
  }

  T* Underlying() {
    return static_cast<T*>(this);
  }

};

template <typename T>
class LinkedList {
 public:
  using Node = ListNode<T>;

  void Append(LinkedList&& other) {
    if (IsEmpty()) {
      head_ = other.head_;
      tail_ = other.tail_;
    } else {
      tail_->LinkBefore(other.head_);
      tail_ = other.tail_;
    }

    size_ += other.size_;
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }

  void PushBack(Node* node) noexcept {
    if (IsEmpty()) {
      head_ = tail_ = node;
    } else {
      tail_->LinkBefore(node);
      tail_ = node;
    }

    ++size_;
  }

  void PushFront(Node* node) noexcept {
    if (IsEmpty()) {
      head_ = tail_ = node;
    } else {
      node->LinkBefore(head_);
      head_ = node;
    }

    ++size_;
  }

  void PopFront() {
    if (IsEmpty()) {
      return;
    }

    Node* tmp = head_;
    head_ = head_->next_;

    if (tail_ == tmp) {
      tail_ = head_;
    }

    tmp->ResetNext();
    --size_;
  }

  T* Back() {
    return tail_->Underlying();
  }

  T* Front() {
    return head_->Underlying();
  }

  void PopBack() {
    if (IsEmpty()) {
      return;
    }

    Node* tmp = head_;

    while (tmp->next_ != tail_) {
      tmp = tmp->next_;
    }

    tail_ = tmp;

    if (head_ == tmp) {
      head_ = tail_;
    }

    tmp->ResetNext();
    --size_;
  }

  [[nodiscard]] bool IsEmpty() const noexcept {
    head_ == nullptr;
  }

  [[nodiscard]] std::size_t Size() const noexcept {
    return size_;
  }

 private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  std::size_t size_ = 0;
};

}  // namespace bicycle::container::intrusive
