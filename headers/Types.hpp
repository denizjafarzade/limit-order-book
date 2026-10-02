#pragma once
#include <cstdint>

using OrderID = std::uint64_t;
using Price = std::int64_t; // Fixed-point price in cents, e.g. $100.50 -> 10050. Avoids floating-point rounding errors.
using Qty = std::uint32_t; 

enum class Side{ Buy, Sell };
enum class OrderType{ Market, Limit };