#include "linked_list.hpp"
#include <iostream>

#define print_val(__x) std::cout << #__x << " = " << __x << std::endl
#define newline        std::cout << std::endl
#define header(__x)    std::cout << #__x << std::endl

int main(int argc, char **argv) {
    using namespace dio;

    LinkedList<int> ll_int;
    LinkedList<int> ll_int2;
    LinkedList<int> ll_int3;

    ll_int.Push(1);
    ll_int.Push(2);
    ll_int.Push(3);
    ll_int.Push(4);

    header(ll_int);

    for (int num : ll_int) {
        print_val(num);
    }

    newline;

    ll_int2 = ll_int;

    header(ll_int2);

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

    return 0;
}