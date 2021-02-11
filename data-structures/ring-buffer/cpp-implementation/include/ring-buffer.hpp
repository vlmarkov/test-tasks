#pragma once

#include <array>
#include <iostream>


template<typename T, std::size_t N>
class RingBuffer
{
private:
    std::array<T, N> buffer_;
    std::size_t head_idx_;
    std::size_t tail_idx_;
    bool catch_up_;
    void safe_move_idx_(std::size_t& idx);

public:
    RingBuffer();
    ~RingBuffer();

    void push(const T& t);
    void push(const T&& t);
    T pop();
    void clear();
    std::size_t size() const ;

    std::size_t get_head_idx() const;
    std::size_t get_tail_idx() const;
    bool get_catch_up() const;

    friend std::ostream &operator<<(std::ostream& output, const RingBuffer& rb)
    {
        std::size_t idx = 0; 
        for (auto& i : rb.buffer_)
        {
            if (idx == rb.head_idx_ && idx == rb.tail_idx_)
            {
                output << "[" << idx << "] [HT] " << i << "\n";
            }
            else if (idx == rb.head_idx_)
            {
                output << "[" << idx << "] [H ] " << i << "\n";
            }
            else if (idx == rb.tail_idx_)
            {
                output << "[" << idx << "] [ T] " << i << "\n";
            }
            else
            {
                output << "[" << idx << "] [  ] " << i << "\n";
            }
            ++idx;
        }
        return output; 
    }
};

template<typename T, std::size_t N>
RingBuffer<T, N>::RingBuffer() : head_idx_{0}, tail_idx_{0}, catch_up_{false}
{
    if constexpr (std::is_trivial<T>::value) {
        for (auto& i : buffer_)
            i = T{};
    } else {
        for (auto& i : buffer_)
            i.clear();
    }
}

template<typename T, std::size_t N>
RingBuffer<T, N>::~RingBuffer()
{
    ;
}

template<typename T, std::size_t N>
void RingBuffer<T, N>::push(const T& t)
{
    if (catch_up_)
    {
        catch_up_ = false;
        safe_move_idx_(tail_idx_);
    }

    buffer_[head_idx_] = t;
    safe_move_idx_(head_idx_);
    if (head_idx_ == tail_idx_)
    {
        catch_up_ = true;
    }

    return;
}

template<typename T, std::size_t N>
void RingBuffer<T, N>::push(const T&& t)
{
    if (catch_up_)
    {
        catch_up_ = false;
        safe_move_idx_(tail_idx_);
    }

    buffer_[head_idx_] = std::move(t);
    safe_move_idx_(head_idx_);
    if (head_idx_ == tail_idx_)
    {
        catch_up_ = true;
    }

    return;
}

template<typename T, std::size_t N>
T RingBuffer<T, N>::pop()
{
    const auto idx = tail_idx_;

    if (tail_idx_ == head_idx_ && catch_up_)
    {
        catch_up_ = false;
        safe_move_idx_(tail_idx_);
    }
    else if (tail_idx_ != head_idx_)
    {
        safe_move_idx_(tail_idx_);
    }

    return buffer_[idx];
}

template<typename T, std::size_t N>
void RingBuffer<T, N>::clear()
{
    catch_up_ = false;
    head_idx_ = 0;
    tail_idx_ = 0;

    if constexpr (std::is_trivial<T>::value) {
        for (auto& i : buffer_)
            i = T{};
    } else {
        for (auto& i : buffer_)
            i.clear();
    }

    return;
}

template<typename T, std::size_t N>
std::size_t RingBuffer<T, N>::size() const
{
    return N;
}

template<typename T, std::size_t N>
std::size_t RingBuffer<T, N>::get_head_idx() const
{
    return head_idx_;
}

template<typename T, std::size_t N>
std::size_t RingBuffer<T, N>::get_tail_idx() const
{
    return tail_idx_;
}

template<typename T, std::size_t N>
bool RingBuffer<T, N>::get_catch_up() const
{
    return catch_up_;
}

template<typename T, std::size_t N>
void RingBuffer<T, N>::safe_move_idx_(std::size_t& idx)
{
    if (idx == N - 1)
    {
        idx = 0; // Go to the begining
    }
    else
    {
        idx += 1;
    }
}
