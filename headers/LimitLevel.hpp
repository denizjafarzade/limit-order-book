#pragma once
#include "Types.hpp"
#include "Order.hpp"

struct LimitLevel{
    Price price;
    Qty total_quantity = 0;
    Order* head = nullptr;
    Order* tail = nullptr;
};
