#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include "node.h"
#include <iostream>

class Orderbook {
private:
    Node pool[1000];
    int pool_index;
    Node* bids;
    Node* asks;

    Node* allocate();

        
    // template insert - must live in private not to be used outside the class
    template<typename Comparator>
    Node* insert(Node* head, double price, int quantity, Comparator compare) {
        // case 0 - empty list
        if (head == nullptr) {
            Node* new_node = allocate();
            new_node->price = price;
            new_node->quantity = quantity;
            new_node->next = nullptr;
            return new_node;
        }

        // case 1 - new node becomes head
        if (compare(head->price, price)) {
            Node* new_node = allocate();
            new_node->price = price;
            new_node->quantity = quantity;
            new_node->next = head;
            return new_node;
        }

        // case 2 - middle
        Node* current = head;
        while (current->next != nullptr) {
            if (compare(current->next->price, price)) {
                Node* new_node = allocate();
                new_node->price = price;
                new_node->quantity = quantity;
                new_node->next = current->next;
                current->next = new_node;
                return head;
            }
            current = current->next;
        }

        // case 3 - end
        Node* new_node = allocate();
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = nullptr;
        current->next = new_node;
        return head;
    }

    Node* delete_level(Node* head, double price);

public:
    Orderbook();
    ~Orderbook();

    Orderbook(const Orderbook&) = delete;
    Orderbook& operator=(const Orderbook&) = delete;
    
    void insert_bid(double price, int quantity);
    void insert_ask(double price, int quantity);
    void delete_bid(double price);
    void delete_ask(double price);
    void print_book();
    void reset_pool();
};

#endif