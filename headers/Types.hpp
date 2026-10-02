#pragma once
#include <cstdint>

using OrderID = uint64_t;
using Price = int64_t; // Fixed-point price in cents, e.g. $100.50 -> 10050. Avoids floating-point rounding errors.
using Qty = uint32_t; 

enum class Side{ Buy, Sell };
enum class OrderType{ Market, Limit };