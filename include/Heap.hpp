#pragma once

#include "types.hpp"

// 引数の align は 2 の累乗である必要あり
#define ALIGN_UP(value, align) ((value + (align - 1)) & ~(align - 1))

class HeapAllocator;
class Heap {
    struct alignas(16) HeapHeader {
        size_t capacity;
        size_t used_size; // 使用済みのサイズ (HeapHeader/BlockHeader を含む)
    };
    static_assert(sizeof(HeapHeader) == 16);

    struct alignas(16) BlockHeader {
        u32          block_size;
        u32          is_free;
        BlockHeader* prev;
    };
    static_assert(sizeof(BlockHeader) == 16);

    static constexpr size_t alignment          = 16;
    static constexpr size_t minimum_block_size = sizeof(BlockHeader) + alignment;
public:
    Heap(size_t heap_size);
    ~Heap();

    Heap(Heap&& other)            noexcept;
    Heap& operator=(Heap&& other) noexcept;

    Heap(const Heap&)            = delete;
    Heap& operator=(const Heap&) = delete;

    size_t free_space() const noexcept;
    size_t used_space() const noexcept;
private:
    HeapHeader* heap_header;

    friend class HeapAllocator;
};
