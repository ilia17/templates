#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#include "node.h"
Node* insert_bid(Node* head, double price, int quantity);
Node* insert_ask(Node* head, double price, int quantity);
void print_book(Node* bids, Node* asks);
Node* delete_level(Node* head, double price);
void reset_pool();
Node* allocate();
#endif
