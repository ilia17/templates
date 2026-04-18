# Templates Orderbook

A C++ orderbook implementation that replaces the separate `insert_bid` / `insert_ask` functions with a single **templated `insert` function**. The sort order (ascending or descending) is controlled by passing a comparator lambda at the call site.

## Concepts Demonstrated

- **C++ templates** — `insert<Comparator>` is a single generic function that works for both bids and asks. The compiler generates two specialisations at compile time: one for each lambda passed in `main.cpp`.
- **Comparator / lambda** — the caller decides the ordering by passing a lambda such as `[](double a, double b){ return a < b; }`. This makes the insert logic reusable without duplication.
- **Memory pool allocation** — same as the previous version: a fixed array of 1000 `Node` objects is pre-allocated at startup. Nodes are handed out via `allocate()` and reclaimed in bulk via `reset_pool()`.
- **Header-only templates** — the `insert` template must live in the header (`orderbook.h`) because the compiler needs to see the full definition at the point of instantiation.

## Project Structure

```
templates/
├── main.cpp           # Entry point — builds and prints the book
├── orderbook.cpp      # Pool, print, delete_level implementations
└── headers/
    ├── node.h         # Node struct definition
    └── orderbook.h    # Template insert + other function declarations
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
| `insert(head, price, qty, comparator)` | Generic sorted insert — order determined by the comparator |
| `delete_level(head, price)` | Remove the node matching the given price |
| `print_book(bids, asks)` | Print all bids then all asks to stdout |
| `reset_pool()` | Reset the memory pool (reclaim all nodes) |
| `allocate()` | Internal — returns next free node from pool |

### Comparator conventions

| Side | Lambda | Order |
|---|---|---|
| Bids | `[](double a, double b){ return a < b; }` | Descending (highest first) |
| Asks | `[](double a, double b){ return a > b; }` | Ascending (lowest first) |

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

The pool holds a maximum of **1000 nodes**. If this limit is exceeded, the program prints an error and exits. To increase the limit, change the pool size in `orderbook.cpp` and the `extern` declaration in `orderbook.h`:

```cpp
Node pool[1000]; // increase this value
```
