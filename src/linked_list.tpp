// This include statement is just a workaround to make clangd work at least somewhat
// properly in .tpp files
#ifndef __DIO_LINKED_LIST_HPP__
#include "linked_list.hpp"
#endif

// ========================= LinkedList =========================

template<typename T>
dio::LinkedList<T>::LinkedList(const LinkedList<T>& other): head_(nullptr), size_(0) {
    pr_copy;

    LinkedListNode<T> *node = other.GetPrev(); // returns the last one if no arguments given

    while (node != other.head_) {
        Push(node->GetValue());
        node = other.GetPrev(node);
    }

    Push(node->GetValue()); // push the head

    if (has_bad_alloc) {
        // Destroy everything we created if things go south
        DestroyFromHead();
    }
}

template<typename T>
dio::LinkedList<T>::LinkedList(LinkedList<T>&& other) {
    pr_move;
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
}

template<typename T>
dio::LinkedList<T>& dio::LinkedList<T>::operator=(const dio::LinkedList<T>& other) {
    pr_copy_assign;
    if (this == &other) return *this;

    LinkedList<T> new_list(other);
    *this = std::move(new_list);

    return *this;
}

template<typename T>
dio::LinkedList<T>& dio::LinkedList<T>::operator=(dio::LinkedList<T>&& other) {
    pr_move_assign;
    if (this == &other) return *this;

    std::swap(size_, other.size_);
    std::swap(head_, other.head_);

    return *this;
}

template<typename T>
dio::LinkedList<T>& dio::LinkedList<T>::Push(const T& val) {
    LinkedListNode<T> *n;

    try {
        n = new LinkedListNode<T>(val);
    } catch (const std::bad_alloc& e) {
        std::cerr << "Allocation failed: " << e.what() << std::endl;
        has_bad_alloc = true;
        return *this;
    }

    n->SetNext(head_);
    head_ = n;

    ++size_;

    return *this;
}

template<typename T>
dio::LinkedList<T>& dio::LinkedList<T>::Push(T&& val) {
    LinkedListNode<T> *n;

    try {
        n = new LinkedListNode<T>(val);
    } catch (const std::bad_alloc& e) {
        std::cerr << "Allocation failed: " << e.what() << std::endl;
        return *this;
    }

    n->SetNext(head_);
    head_ = n;

    ++size_;

    return *this;
}

template<typename T>
void dio::LinkedList<T>::Pop() {
    if (size_ == 0 || head_ == nullptr) return;

    auto tbd = head_;
    head_ = head_->GetNext();
    delete tbd;
    --size_;
}

template<typename T>
T dio::LinkedList<T>::GetHeadValue() const {
    return head_->GetValue();
}

template<typename T>
typename dio::LinkedList<T>::Iter dio::LinkedList<T>::begin() {
    return Iter(head_);
}

template<typename T>
typename dio::LinkedList<T>::Iter dio::LinkedList<T>::end() {
    return Iter(nullptr);
}

template<typename T>
const typename dio::LinkedList<T>::Iter dio::LinkedList<T>::begin() const {
    return Iter(head_);
}

template<typename T>
const typename dio::LinkedList<T>::Iter dio::LinkedList<T>::end() const {
    return Iter(nullptr);
}

template<typename T>
const typename dio::LinkedList<T>::Iter dio::LinkedList<T>::cbegin() const {
    return begin();
}

template<typename T>
const typename dio::LinkedList<T>::Iter dio::LinkedList<T>::cend() const {
    return end();
}

template<typename T>
dio::LinkedList<T>::~LinkedList() {
    pr_begin;
    DestroyFromHead();
}

template<typename T>
void dio::LinkedList<T>::DestroyFromHead() {
    while (size_ > 0) Pop();
}

template<typename T>
dio::LinkedListNode<T> *dio::LinkedList<T>::GetPrev(const LinkedListNode<T> *node) const {
    LinkedListNode<T> *ptr = head_;

    while (ptr->GetNext() != node && ptr->GetNext() != nullptr) ptr = ptr->GetNext();
    if (ptr->GetNext() != node) return nullptr;

    return ptr;
}

// ======================= LinkedListNode =======================
template<typename T>
dio::LinkedListNode<T>::LinkedListNode(const LinkedListNode<T> &other)
        : val_(other.val_), next_(nullptr) { pr_copy; }

template<typename T>
dio::LinkedListNode<T>::LinkedListNode(LinkedListNode<T>&& other) {
    pr_move;

    std::swap(other.next_, next_);
    std::swap(other.val_,  val_);

    return *this;
}

template<typename T>
dio::LinkedListNode<T>& dio::LinkedListNode<T>::operator=(const LinkedListNode<T>& other) {
    pr_copy_assign;

    if (this == &other) return *this;

    val_  = other.val_;
    next_ = next_ == nullptr ? nullptr : next_;
    return *this;
}

template<typename T>
dio::LinkedListNode<T>& dio::LinkedListNode<T>::operator=(LinkedListNode<T>&& other) {
    pr_move_assign;

    if (this == &other) return *this;

    std::swap(other.next_, next_);
    std::swap(other.val_,  val_);

    return *this;
}

template<typename T>
const T& dio::LinkedListNode<T>::GetValue() const {
    return val_;
}

template<typename T>
dio::LinkedListNode<T> *dio::LinkedListNode<T>::GetNext() {
    return next_;
}

template<typename T>
dio::LinkedListNode<T>& dio::LinkedListNode<T>::SetNext(LinkedListNode<T> *next) {
    next_ = next;
    return *this;
}


template<typename T>
dio::LinkedListNode<T>& dio::LinkedListNode<T>::SetValue(const T& val) {
    val_ = val;
    return *this;
}

template<typename T>
dio::LinkedListNode<T>& dio::LinkedListNode<T>::SetValue(T&& val) {
    val_ = std::move(val);
    return *this;
}

template<typename T>
dio::LinkedListNode<T>::~LinkedListNode() {
    pr_begin;

    next_ = nullptr;
}