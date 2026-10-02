#pragma once
#include "Types.hpp"
#include "Order.hpp"

struct LimitLevel{
    Price price;
    Qty total_quantity = 0;
    Order* head = nullptr;
    Order* tail = nullptr;

    void append(Order* order){
        if(head == nullptr){
            head = order;
            tail = order;
            order->level = this;
            total_quantity += order->remaining_quantity;
        }
        else{
            order->prev = tail;
            tail->next = order;
            tail = order;
            order->level = this;
            total_quantity += order->remaining_quantity;
        }
    }

    void remove(Order* order){
        if(order->prev != nullptr){
            order->prev->next = order->next;
        }
        else{
            head = order->next;
        }
        
        if(order->next != nullptr){
            order->next->prev = order->prev;        
        }
        else{
            tail = order->prev;
        }

        total_quantity -= order->remaining_quantity;
        order->prev = nullptr;
        order->next = nullptr;
        order->level = nullptr;
    }
};
