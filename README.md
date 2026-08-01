# MyHeapAllocator
16 byte aligned custom heap allocator for Windows.

## Features
- 16 byte alignment guaranteed
- Automatic block splitting & coalescing
- Zero dependencies (built on Windows API's VirtualAlloc function)

## Usage
```cpp
#include "Heap.hpp"
#include "HeapAllocator.hpp"

int main() {
    Heap heap(0x1000);
    HeapAllocator allocator(heap);

    auto* p = allocator.allocate(32);
    allocator.free(p);

    return 0;
}
```
