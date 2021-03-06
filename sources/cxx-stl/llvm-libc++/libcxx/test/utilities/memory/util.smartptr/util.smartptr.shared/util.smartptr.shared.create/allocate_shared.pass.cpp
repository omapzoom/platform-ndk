//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <memory>

// shared_ptr

// template<class T, class A, class... Args>
//    shared_ptr<T> allocate_shared(const A& a, Args&&... args);

#include <memory>
#include <new>
#include <cstdlib>
#include <cassert>
#include "test_allocator.h"

int new_count = 0;

struct A
{
    static int count;

    A(int i, char c) : int_(i), char_(c) {++count;}
    A(const A& a)
        : int_(a.int_), char_(a.char_)
        {++count;}
    ~A() {--count;}

    int get_int() const {return int_;}
    char get_char() const {return char_;}
private:
    int int_;
    char char_;
};

int A::count = 0;

int main()
{
    {
    int i = 67;
    char c = 'e';
    std::shared_ptr<A> p = std::allocate_shared<A>(test_allocator<A>(54), i, c);
    assert(test_allocator<A>::alloc_count == 1);
    assert(A::count == 1);
    assert(p->get_int() == 67);
    assert(p->get_char() == 'e');
    }
    assert(A::count == 0);
    assert(test_allocator<A>::alloc_count == 0);
}
