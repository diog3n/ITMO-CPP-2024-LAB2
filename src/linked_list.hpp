#ifndef __DIO_LINKED_LIST_HPP__
#define __DIO_LINKED_LIST_HPP__
#include <iterator>
#include <utility>
#include <iostream>


inline void pr_begin__(const char *func) {
    std::cout << func << ": Executing!" << std::endl;
}

inline void pr_move__(const char *func) {
    std::cout << func << ": Executing a move contructor!" << std::endl;
}

inline void pr_copy__(const char *func) {
    std::cout << func << ": Executing a copy contructor!" << std::endl;
}

inline void pr_move_assign__(const char *func) {
    std::cout << func << ": Executing a move assignment!" << std::endl;
}

inline void pr_copy_assign__(const char *func) {
    std::cout << func << ": Executing a copy assignment!" << std::endl;
}

#define pr_begin       pr_begin__(__func__)
#define pr_copy        pr_copy__(__func__)
#define pr_move        pr_move__(__func__)
#define pr_copy_assign pr_copy_assign__(__func__)
#define pr_move_assign pr_move_assign__(__func__)

namespace dio {

template<typename T> class LinkedList;
template<typename T> class LinkedListNode;

using size_t = long long;

} // namespace dio

template<typename T>
class dio::LinkedList {
public:
    class Iter {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = LinkedListNode<T>;
        using pointer           = LinkedListNode<T> *;  // or also value_type*
        using reference         = const T&;

        LinkedListNode<T> *node_;
    public:
        explicit  Iter(LinkedListNode<T> *node): node_(node) {}
        Iter&     operator++() { node_ = node_->GetNext(); return *this; }
        Iter      operator++(int) { Iter ret = *this; ++(*this); return ret; }
        bool      operator==(Iter other) const { return node_ == other.node_; };
        bool      operator!=(Iter other) const { return !((*this) == other); };
        reference operator*() const { return node_->GetValue(); };
    };

    LinkedList(): head_(nullptr), size_(0) { pr_begin; }
    LinkedList(const LinkedList<T>& other);
    LinkedList(LinkedList<T>&& other);

    LinkedList<T>& operator=(const LinkedList<T>& other);
    LinkedList<T>& operator=(LinkedList<T>&& other);

    LinkedList& Push(const T& val);
    LinkedList& Push(T&& val);
    void Pop();

    T GetHeadValue() const;

    Iter begin();
    Iter end();

    const Iter begin() const;
    const Iter end() const;

    const Iter cbegin() const;
    const Iter cend() const;

    ~LinkedList();
private:
    void DestroyFromHead();
    LinkedListNode<T> *GetPrev(const LinkedListNode<T> *node = nullptr) const;

    LinkedListNode<T> *head_;
    size_t             size_;
    bool               has_bad_alloc = false;
};

template<typename T>
class dio::LinkedListNode {
public:
    LinkedListNode(): val_(), next_(nullptr) { pr_begin; }

    explicit LinkedListNode(const T& val): val_(val), next_(nullptr) { pr_begin; }
    LinkedListNode(const T& val, LinkedListNode<T> *next): val_(val), next_(next)
            { pr_begin; }

    LinkedListNode(T&& val): val_(std::move(val)), next_(nullptr) { pr_begin; }
    LinkedListNode(T&& val, LinkedListNode<T> *next): val_(std::move(val)), next_(next)
            { pr_begin; }

    LinkedListNode(const LinkedListNode<T> &other);
    LinkedListNode(LinkedListNode<T>&& other);

    LinkedListNode<T>& operator=(const LinkedListNode<T>& other);
    LinkedListNode<T>& operator=(LinkedListNode<T>&& other);

    const T& GetValue() const;
    LinkedListNode<T> *GetNext();

    LinkedListNode<T>& SetNext(LinkedListNode<T> *next);
    LinkedListNode<T>& SetValue(const T& val);
    LinkedListNode<T>& SetValue(T&& val);

    ~LinkedListNode();
private:

    T val_;
    LinkedListNode<T> *next_;
};

#include "linked_list.tpp"

#endif