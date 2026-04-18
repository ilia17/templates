#include <iostream>
#include "headers/orderbook.h"
    

int main() {
    Node* bids = nullptr;
    Node* asks = nullptr;

    // build the book
    bids = insert_bid(bids, 100.05, 200);
    bids = insert_bid(bids, 100.10, 500);
    bids = insert_bid(bids, 100.07, 300);

    asks = insert_ask(asks, 100.25, 150);
    asks = insert_ask(asks, 100.20, 300);
    asks = insert_ask(asks, 100.30, 400);

    std::cout << "--- Initial book ---\n";
    print_book(bids, asks);

    // delete a level
    bids = delete_level(bids, 100.07);
    std::cout << "\n--- After deleting bid 100.07 ---\n";
    print_book(bids, asks);

    // cleanup
    bids = nullptr;
    asks = nullptr;
    reset_pool();
    
    return 0;
}