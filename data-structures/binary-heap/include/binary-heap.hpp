#pragma once

#include <array>
#include <iostream>


enum class HeapType { min, max };

template<typename T, std::size_t N, HeapType H>
class BinaryHeap
{
private:
    std::array<T, N> buffer_;
    std::size_t capacity_;

    void heapify_();

public:
    BinaryHeap();
    ~BinaryHeap() = default;

    int insert(const T& t);
    T remove();
    const T& top() const;
    void clear();

    HeapType type() const;
    std::size_t size() const ;
    std::size_t capacity() const ;


    friend std::ostream &operator<<(std::ostream& output, const BinaryHeap& bh)
    {
        std::size_t idx = 0; 
        for (const auto& i : bh.buffer_)
        {
            output << "[" << idx << "] " << i << "\n";
            ++idx;
        }
        return output; 
    }
};

template<typename T, std::size_t N, HeapType H>
BinaryHeap<T, N, H>::BinaryHeap() : capacity_{0}
{
    if constexpr (std::is_trivial<T>::value)
    {
        for (auto& i : buffer_)
        {
            i = T{};
        }
    }
    else
    {
        for (auto& i : buffer_)
        {
            i.clear();
        }
    }
}

template<typename T, std::size_t N, HeapType H>
const T& BinaryHeap<T, N, H>::top() const
{
    return buffer_[0];
}

template<typename T, std::size_t N, HeapType H>
int BinaryHeap<T, N, H>::insert(const T& t)
{
    if (capacity_ == N)
    {
        return -1;
    }

    buffer_[capacity_] = t;
    capacity_++;

    std::size_t i = capacity_ - 1;

    if constexpr (H == HeapType::max)
    {
        while (i > 0 && buffer_[i] > buffer_[i / 2])
        {
            std::swap(buffer_[i], buffer_[i / 2]);
            i = i / 2;
        }
    }
    else
    {
        while (i > 0 && buffer_[i] < buffer_[i / 2])
        {
            std::swap(buffer_[i / 2], buffer_[i]);
            i = i / 2;
        }
    }

    return 0;
}

template<typename T, std::size_t N, HeapType H>
T BinaryHeap<T, N, H>::remove()
{
    if (capacity_ == 0)
    {
        return {};
    }

    capacity_--;
    auto ret = buffer_[0];
    buffer_[0] = buffer_[capacity_];
    buffer_[capacity_] = {};

    heapify_();

    return ret;
}

template<typename T, std::size_t N, HeapType H>
void BinaryHeap<T, N, H>::clear()
{
    capacity_ = 0;

    if constexpr (std::is_trivial<T>::value) {
        for (auto& i : buffer_)
            i = T{};
    } else {
        for (auto& i : buffer_)
            i.clear();
    }

    return;
}

template<typename T, std::size_t N, HeapType H>
HeapType BinaryHeap<T, N, H>::type() const
{
    return H;
}

template<typename T, std::size_t N, HeapType H>
std::size_t BinaryHeap<T, N, H>::size() const
{
    return N;
}

template<typename T, std::size_t N, HeapType H>
std::size_t BinaryHeap<T, N, H>::capacity() const
{
    return capacity_;
}

template<typename T, std::size_t N, HeapType H>
void BinaryHeap<T, N, H>::heapify_()
{
    std::size_t index = 0;
    if constexpr (H == HeapType::max)
    {
        while (true)
        {
            std::size_t left = (index == 0) ? 1 : 2 * index;
            std::size_t right = (index == 0) ? 2 : 2 * index + 1;
            std::size_t largest = index;

            if (left < capacity_ && buffer_[left] > buffer_[index])
            {
                largest = left;
            }
            if (right < capacity_ && buffer_[right] > buffer_[largest])
            {
                largest = right;
            }

            if (largest == index)
            {
                break;
            }

            std::swap(buffer_[index], buffer_[largest]);
            index = largest;
        }
    }
    else
    {
        while (true)
        {
            std::size_t left = (index == 0) ? 1 : 2 * index;
            std::size_t right = (index == 0) ? 2 : 2 * index + 1;
            std::size_t lowest = index;

            if (left < capacity_ && buffer_[left] < buffer_[index])
            {
                lowest = left;
            }
            if (right < capacity_ && buffer_[right] < buffer_[lowest])
            {
                lowest = right;
            }

            if (lowest == index)
            {
                break;
            }

            std::swap(buffer_[index], buffer_[lowest]);
            index = lowest;
        }      
    }
}
