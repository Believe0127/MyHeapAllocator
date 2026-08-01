#include "Heap.hpp"

#include <Windows.h>
#include <stdint.h>

Heap::Heap(size_t heap_size)
{
    heap_size   = ALIGN_UP(heap_size, 4096);
    heap_header = reinterpret_cast<HeapHeader *>(VirtualAlloc(nullptr, heap_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if (heap_header) {
        heap_header->capacity  = heap_size;
        heap_header->used_size = sizeof(HeapHeader);

        auto* const block = reinterpret_cast<BlockHeader *>(uintptr_t(heap_header) + sizeof(HeapHeader));
        block->block_size = free_space();
        block->is_free    = 1;
        block->prev       = nullptr;
    }
}

Heap::~Heap() {
    if (heap_header) {
        VirtualFree(reinterpret_cast<void *>(heap_header), 0, MEM_RELEASE);
    }
}

Heap::Heap(Heap&& other) noexcept
    : heap_header(other.heap_header)
{
    other.heap_header = nullptr;
}

Heap& Heap::operator=(Heap&& other) noexcept {
    heap_header       = other.heap_header;
    other.heap_header = nullptr;
    return *this;
}

size_t Heap::free_space() const noexcept {
    return heap_header->capacity - heap_header->used_size;
}

size_t Heap::used_space() const noexcept {
    return heap_header->used_size;
}
