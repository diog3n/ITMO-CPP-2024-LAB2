#include "linked_list.hpp"
#include <iostream>

#define print_val(__x) std::cout << #__x << " = " << __x << std::endl
#define newline        std::cout << std::endl
#define header(__x)    std::cout << "========== " << #__x << " ==========" <<std::endl

dio::LinkedList<int> FillLinkedList(int from, int to) {
    dio::LinkedList<int> ll;
    for (int i = from; i < to; i++) {
        ll.Push(i);
    }

    return ll;
}

void FillLinkedListByReference(dio::LinkedList<int>& ll, int from, int to) {
    for (int i = from; i < to; i++) {
        ll.Push(i);
    }
}

dio::LinkedList<int>& AllocateAndFill(int from, int to) {
    dio::LinkedList<int> *llptr = new dio::LinkedList<int>();

    for (int i = from; i < to; i++) {
        llptr->Push(i);
    }

    return *llptr;
}

int main(int argc, char **argv) {
    using namespace dio;

    header(fill linked list);
    LinkedList<int> ll_int = FillLinkedList(1, 10);;
    LinkedList<int> ll_int2;
    LinkedList<int> ll_int3;

    header(ll_int);

    for (int num : ll_int) {
        print_val(num);
    }

    newline;


    header(fill by reference);
    FillLinkedListByReference(ll_int2, 1, 10);

    for (int num : ll_int2) {
        print_val(num);
    }

    newline;

    ll_int3 = std::move(ll_int);

    header(ll_int3);

    for (int num : ll_int3) {
        print_val(num);
    }

    newline;

    LinkedList<int> copy_constr(ll_int2);
    LinkedList<int> move_constr(ll_int3);

    header(copy_constr);

    for (int num : copy_constr) {
        print_val(num);
    }

    newline;

    header(move_constr);

    for (int num : move_constr) {
        print_val(num);
    }

    newline;

    header(allocated);
    LinkedList<int>& allocated = AllocateAndFill(1, 10);

    for (int num : allocated) {
        print_val(num);
    }

    delete &allocated;

    return 0;
}