#include <iostream>
#include "headers/orderbook.h"
    

int main() {
    Node* bids = nullptr;
    Node* asks = nullptr;

    // build the book
    bids = insert(bids, 100.05, 200, [](double a, double b){ return a < b; });
    bids = insert(bids, 100.10, 500, [](double a, double b){ return a < b; });
    bids = insert(bids, 100.07, 300, [](double a, double b){ return a < b; });
    asks = insert(asks,100.25, 150, [](double a, double b){return a>b;});
    asks = insert(asks, 100.20, 300, [](double a, double b){return a>b;});
    asks = insert(asks, 100.30, 400, [](double a, double b){return a>b;});

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