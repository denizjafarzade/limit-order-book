#pragma once
#include "Types.hpp"
struct LimitLevel;

struct Order{
    OrderID id;
    Side side;
    Price price;
    Qty original_quantity;
    Qty remaining_quantity;
    Order* prev = nullptr;
    Order* next = nullptr;
    LimitLevel* level = nullptr;
};