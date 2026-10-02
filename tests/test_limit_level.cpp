#include <cassert>
#include <iostream>
#include "LimitLevel.hpp"

// One order joins an empty level: it is both first and last.
void test_append_to_empty_level(){
    LimitLevel level{10050};
    Order a{1, Side::Buy, 10050, 100, 100};

    level.append(&a);

    assert(level.head == &a);
    assert(level.tail == &a);
    assert(level.total_quantity == 100);
    assert(a.level == &level);
    assert(a.prev == nullptr);
    assert(a.next == nullptr);
}

// Three orders join in turn: arrival order is preserved (a, b, c).
void test_append_keeps_arrival_order(){
    LimitLevel level{10050};
    Order a{1, Side::Buy, 10050, 100, 100};
    Order b{2, Side::Buy, 10050, 50, 50};
    Order c{3, Side::Buy, 10050, 70, 70};

    level.append(&a);
    level.append(&b);
    level.append(&c);

    assert(level.head == &a);
    assert(level.tail == &c);

    assert(a.prev == nullptr);
    assert(a.next == &b);
    assert(b.prev == &a);
    assert(b.next == &c);
    assert(c.prev == &b);
    assert(c.next == nullptr);

    assert(b.level == &level);
    assert(c.level == &level);
    assert(level.total_quantity == 220);
}

// The middle order leaves: its two neighbours become linked.
void test_remove_middle(){
    LimitLevel level{10050};
    Order a{1, Side::Buy, 10050, 100, 100};
    Order b{2, Side::Buy, 10050, 50, 50};
    Order c{3, Side::Buy, 10050, 70, 70};
    level.append(&a);
    level.append(&b);
    level.append(&c);

    level.remove(&b);

    assert(level.head == &a);
    assert(level.tail == &c);
    assert(a.next == &c);
    assert(c.prev == &a);
    assert(level.total_quantity == 170);

    assert(b.prev == nullptr);
    assert(b.next == nullptr);
    assert(b.level == nullptr);
}

// The first order leaves: the second becomes first.
void test_remove_first(){
    LimitLevel level{10050};
    Order a{1, Side::Buy, 10050, 100, 100};
    Order b{2, Side::Buy, 10050, 50, 50};
    Order c{3, Side::Buy, 10050, 70, 70};
    level.append(&a);
    level.append(&b);
    level.append(&c);

    level.remove(&a);

    assert(level.head == &b);
    assert(level.tail == &c);
    assert(b.prev == nullptr);
    assert(b.next == &c);
    assert(level.total_quantity == 120);
    assert(a.next == nullptr);
    assert(a.level == nullptr);
}

// The last order leaves: the second-to-last becomes last.
void test_remove_last(){
    LimitLevel level{10050};
    Order a{1, Side::Buy, 10050, 100, 100};
    Order b{2, Side::Buy, 10050, 50, 50};
    Order c{3, Side::Buy, 10050, 70, 70};
    level.append(&a);
    level.append(&b);
    level.append(&c);

    level.remove(&c);

    assert(level.head == &a);
    assert(level.tail == &b);
    assert(b.next == nullptr);
    assert(b.prev == &a);
    assert(level.total_quantity == 150);
    assert(c.prev == nullptr);
    assert(c.level == nullptr);
}

// The only order leaves: the level is empty again.
void test_remove_only_order(){
    LimitLevel level{10050};
    Order a{1, Side::Buy, 10050, 100, 100};
    level.append(&a);

    level.remove(&a);

    assert(level.head == nullptr);
    assert(level.tail == nullptr);
    assert(level.total_quantity == 0);
    assert(a.level == nullptr);
}

// A level that has been emptied can be used again.
void test_append_after_level_emptied(){
    LimitLevel level{10050};
    Order a{1, Side::Buy, 10050, 100, 100};
    Order b{2, Side::Buy, 10050, 50, 50};
    level.append(&a);
    level.remove(&a);

    level.append(&b);

    assert(level.head == &b);
    assert(level.tail == &b);
    assert(b.prev == nullptr);
    assert(b.next == nullptr);
    assert(level.total_quantity == 50);
}

// A partly filled order counts only its unfilled quantity.
void test_total_uses_remaining_quantity(){
    LimitLevel level{10050};
    Order a{1, Side::Buy, 10050, 100, 30};

    level.append(&a);
    assert(level.total_quantity == 30);

    level.remove(&a);
    assert(level.total_quantity == 0);
}

int main(){
    test_append_to_empty_level();
    test_append_keeps_arrival_order();
    test_remove_middle();
    test_remove_first();
    test_remove_last();
    test_remove_only_order();
    test_append_after_level_emptied();
    test_total_uses_remaining_quantity();

    std::cout << "All 8 tests passed\n";
}