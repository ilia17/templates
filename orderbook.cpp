#include "./headers/orderbook.h"
#include <iostream>

Node* Orderbook::allocate() {
    if (pool_index >= 1000) {
        std::cerr << "Pool exhausted. Halting.\n";
        std::exit(1);
    }
    return &pool[pool_index++];
}

Orderbook::Orderbook() {
    pool_index = 0;
    bids = nullptr;
    asks = nullptr;
}
Orderbook::~Orderbook() {	

}


void Orderbook::insert_bid(double price, int quantity) {
    bids = insert(bids, price, quantity, [](double a, double b){ return a < b; });
}

void Orderbook::insert_ask(double price, int quantity) {
    asks = insert(asks, price, quantity, [](double a, double b){ return a > b; });
}

void Orderbook::delete_bid(double price) {
    bids = delete_level(bids, price);
}

void Orderbook::delete_ask(double price) {
    asks = delete_level(asks, price);
}

void Orderbook::print_book() {
    Node* current_bid = bids;
    while (current_bid != nullptr) {
        std::cout << "Bid: " << current_bid->price << " Quantity: " << current_bid->quantity << "\n";
        current_bid = current_bid->next;
    }
    Node* current_ask = asks;
    while (current_ask != nullptr) {
        std::cout << "Ask: " << current_ask->price << " Quantity: " << current_ask->quantity << "\n";
        current_ask = current_ask->next;
    }
}

void Orderbook::reset_pool() {
    pool_index = 0;
    bids = nullptr;
    asks = nullptr;
}

Node* Orderbook::delete_level(Node* head, double price) {
    if (head == nullptr) return nullptr;
    if (head->price == price) return head->next;
    Node* current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->next->price == price) {
            current->next = current->next->next;
            return head;
        }
        current = current->next;
    }
    return head;
}

