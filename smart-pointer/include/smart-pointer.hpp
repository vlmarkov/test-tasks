#ifndef _SMART_POINTER_H_
#define _SMART_POINTER_H_

#include <atomic>
#include <string>


template <typename T>
class SmartPointer
{
public:
    explicit SmartPointer(T* t)
    {
        if (t == nullptr)
        {
            throw std::string("object must be valid");
        }
        
        data_ = t;
        counter_ = new std::atomic_int32_t(1);
    }

    ~SmartPointer()
    {
        if (*counter_ == 0) {
            return;
        }
        
        *counter_ -= 1;
        if (*counter_ == 0) {
            delete counter_;
            delete data_;
            data_ = nullptr;
            counter_ = nullptr;
        }
    }

    SmartPointer(SmartPointer& rhs)
    {
        data_ = rhs.data_;
        counter_ = rhs.counter_;
        *counter_ += 1;
    }

    SmartPointer& operator=(SmartPointer& rhs)
    {
        *counter_ -= 1;
        data_ = rhs.data_;
        counter_ = rhs.counter_;       
        *counter_ += 1;
        return *this;
    }

    T* get() {
        return data_;
    }

private:
    std::atomic_int32_t *counter_{nullptr};
    T *data_{nullptr};
};


template <typename T>
class SmartPointer<T[]>
{
public:
    explicit SmartPointer(T* t)
    {
        if (t == nullptr)
        {
            throw std::string("object must be valid");
        }
        
        data_ = t;
        counter_ = new std::atomic_int32_t(1);
    }

    ~SmartPointer()
    {
        if (*counter_ == 0) {
            return;
        }
        *counter_ -= 1;
        if (*counter_ == 0) {
            delete counter_;
            delete[] data_;
            data_ = nullptr;
            counter_ = nullptr;
        }
    }

    SmartPointer(SmartPointer& rhs)
    {
        data_ = rhs.data_;
        counter_ = rhs.counter_;
        *counter_ += 1;
    }

    SmartPointer& operator=(SmartPointer& rhs)
    {
        *counter_ -= 1;
        data_ = rhs.data_;
        counter_ = rhs.counter_;       
        *counter_ += 1;
        return *this;
    }

    T* get() {
        return data_;
    }

private:
    std::atomic_int32_t *counter_{nullptr};
    T *data_{nullptr};
};

#endif /* _SMART_POINTER_H_ */
