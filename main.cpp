#include <iostream>
#include <utility> // for std::move
#include "headers/orderbook.h"

int main() {

    // create book1 and populate it
    Orderbook book1;
    try {
        book1.insert_bid(100.05, 200);
        book1.insert_bid(100.10, 500);
        book1.insert_bid(100.07, 300);

        book1.insert_ask(100.25, 150);
        book1.insert_ask(100.20, 300);
        book1.insert_ask(100.30, 400);

        std::cout << "--- book1 (Before move) ---\n";
        book1.print_book();

        // move it to book2 using std::move
        Orderbook book2 = std::move(book1);

        // verify book2 has the data
        std::cout << "\n--- book2 (After move) ---\n";
        book2.print_book();

        // verify book1 is empty
        std::cout << "\n--- book1 (Should be empty after move) ---\n";
        book1.print_book();

        // cleanup
        book2.reset_pool();
        book1.reset_pool();

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
