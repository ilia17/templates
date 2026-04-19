#include <iostream>
#include "headers/orderbook.h"

int main() {

    Orderbook book;

    // build the book
    book.insert_bid(100.05, 200);
    book.insert_bid(100.10, 500);
    book.insert_bid(100.07, 300);

    book.insert_ask(100.25, 150);
    book.insert_ask(100.20, 300);
    book.insert_ask(100.30, 400);

    std::cout << "--- Initial book ---\n";
    book.print_book();

    // delete a level
    book.delete_bid(100.07);
    std::cout << "\n--- After deleting bid 100.07 ---\n";
    book.print_book();

    // cleanup
    book.reset_pool();

    return 0;
}
