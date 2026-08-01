#include "HeapAllocator.hpp"

#include <stdio.h>
#include <string.h>

int main() {
    Heap heap(0x1000);


    HeapAllocator allocator(heap);

    auto* p1 = allocator.allocate(32);
    auto* p2 = allocator.allocate(64);
    auto* p3 = allocator.allocate(128);
    memset(p1, 0x45, 32);
    memset(p2, 0x19, 64);
    memset(p3, 0x77, 128);

    printf("%p/%p/%p\n", p1, p2, p3);

    allocator.free(p2);
    p2 = allocator.allocate(32);

    allocator.free(p3);
    allocator.free(p1);
    allocator.free(p2);

    allocator.print_data();

    allocator.free(p1);
    allocator.free(p2);
    allocator.free(p3);

    return 0;
}
