#include "./headers/orderbook.h"
#include <iostream>
// pre-allocated at startup
Node pool[1000];
int pool_index = 0;

Node* allocate(){
    if (pool_index >= 1000){
        std::cerr << "Pool Exchaused. halting execution" << std::endl;
        std::exit(1);
    }
    return &pool[pool_index++];
}

void print_book(Node* bids, Node* asks){
    //print the bids
    Node* current_bid = bids;
    while (current_bid != nullptr){
        std::cout << "Bid: " << current_bid->price << " Quantity: " << current_bid->quantity << std::endl;
        current_bid = current_bid->next;
    }

    //print the asks
    Node* current_ask = asks;
    while (current_ask != nullptr){
        std::cout << "Ask: " << current_ask->price << " Quantity: " << current_ask->quantity << std::endl;
        current_ask = current_ask->next;
    }
} 

void reset_pool() {
    pool_index = 0;
}


Node* delete_level(Node* head, double price){
    Node* current = head;
    if (head->price == price){
        head = head->next;
        return head;
    }
    while (current != nullptr && current->next != nullptr){
        if (current->next->price == price){
            current->next = current->next->next;
            return head;
        }
        current = current->next;
    }
    return head;
}