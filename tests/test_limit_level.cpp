#include <cassert>
#include <iostream>
#include "LimitLevel.hpp"

int main(){
    LimitLevel level{10050};
    Order a{1, Side::Buy, 10050, 100, 100};
    Order b{2, Side::Buy, 10050, 50, 50};
    Order c{3, Side::Buy, 10050, 70, 70};


    level.append(&a);

    assert(level.head == &a);
    assert(level.tail == &a);
    assert(level.total_quantity == 100);

    level.append(&b);
    level.append(&c);

    assert(a.level == &level);
    assert(level.head == &a);
    assert(level.tail == &c);
    assert(a.next == &b);
    assert(b.next == &c);
    assert(c.prev == &b);
    assert(b.prev == &a);
    assert(a.prev == nullptr);
    assert(c.next == nullptr);
    assert(level.total_quantity == 220);

    std::cout << "All tests passed\n";
}