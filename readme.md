# Smart Pointers Orderbook

A C++ orderbook implementation using a **memory pool** instead of dynamic heap allocation (`new`/`delete`). Bids and asks are stored as sorted singly-linked lists.

## Concepts Demonstrated

- **Memory pool allocation** — a fixed array of 1000 `Node` objects is pre-allocated at startup. Instead of calling `new`, nodes are handed out from this pool via `allocate()`. This avoids heap fragmentation and is faster for high-frequency use cases.
- **Sorted linked lists** — bids are kept in descending order (highest price first), asks in ascending order (lowest price first), matching standard orderbook conventions.
- **Manual memory management without `delete`** — since nodes come from a pool, memory is reclaimed in bulk by calling `reset_pool()`, which simply resets the pool index to 0.

## Project Structure

```
smart_pointers/
├── main.cpp           # Entry point — builds and prints the book
├── orderbook.cpp      # Core logic: insert, delete, print, pool
└── headers/
    ├── node.h         # Node struct definition
    └── orderbook.h    # Function declarations
```

## Data Structure

```cpp
struct Node {
    double price;
    int quantity;
    Node* next;
};
```

## API

| Function | Description |
|---|---|
| `insert_bid(head, price, qty)` | Insert a bid in descending price order |
| `insert_ask(head, price, qty)` | Insert an ask in ascending price order |
| `delete_level(head, price)` | Remove the node matching the given price |
| `print_book(bids, asks)` | Print all bids then all asks to stdout |
| `reset_pool()` | Reset the memory pool (reclaim all nodes) |
| `allocate()` | Internal — returns next free node from pool |

## Build & Run

```bash
g++ main.cpp orderbook.cpp -o main
./main
```

## Example Output

```
--- Initial book ---
Bid: 100.1 Quantity: 500
Bid: 100.07 Quantity: 300
Bid: 100.05 Quantity: 200
Ask: 100.2 Quantity: 300
Ask: 100.25 Quantity: 150
Ask: 100.3 Quantity: 400

--- After deleting bid 100.07 ---
Bid: 100.1 Quantity: 500
Bid: 100.05 Quantity: 200
Ask: 100.2 Quantity: 300
Ask: 100.25 Quantity: 150
Ask: 100.3 Quantity: 400
```

## Pool Limits

The pool holds a maximum of **1000 nodes**. If this limit is exceeded, the program prints an error and exits. To support more nodes, increase the pool size in `orderbook.cpp`:

```cpp
Node pool[1000]; // increase this value
```
