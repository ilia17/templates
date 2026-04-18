#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include "node.h"

// pool
extern Node pool[1000];
extern int pool_index;
Node* allocate();
void reset_pool();

// template insert - must live in header

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


// other functions
void print_book(Node* bids, Node* asks);
Node* delete_level(Node* head, double price);


#endif
