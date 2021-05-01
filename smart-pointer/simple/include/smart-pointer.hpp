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

        this->acquire_(t, new std::atomic_int32_t{0});
    }

    ~SmartPointer()
    {
        this->realease_();
    }

    SmartPointer(SmartPointer& rhs)
    {
        this->acquire_(rhs.data_, rhs.counter_);
    }

    SmartPointer& operator=(SmartPointer& rhs)
    {
        this->realease_();
        this->acquire_(rhs.data_, rhs.counter_);

        return *this;
    }

    T* get() const
    {
        return data_;
    }

private:
    std::atomic_int32_t *counter_{nullptr};
    T *data_{nullptr};

    void realease_()
    {
        if (--*counter_ == 0) {
            delete data_;
            data_ = nullptr;
            delete counter_;
            counter_ = nullptr;
        }
    }

    void acquire_(T* data, std::atomic_int32_t* counter)
    {
        data_ = data;
        counter_ = counter;
        ++*counter_;
    }
};

template <typename T>
class SmartPointer<T[]>
{
public:
    explicit SmartPointer(T* t)
    {
        if (t == nullptr)
        {
            throw std::string("array of objects must be valid");
        }

        this->acquire_(t, new std::atomic_int32_t{0});
    }

    ~SmartPointer()
    {
        this->realease_();
    }

    SmartPointer(SmartPointer& rhs)
    {
        this->acquire_(rhs.data_, rhs.counter_);
    }

    SmartPointer& operator=(SmartPointer& rhs)
    {
        this->realease_();
        this->acquire_(rhs.data_, rhs.counter_);

        return *this;
    }

    T* get()const
    {
        return data_;
    }

private:
    std::atomic_int32_t *counter_{nullptr};
    T *data_{nullptr};

    void realease_()
    {
        if (--*counter_ == 0) {
            delete[] data_;
            data_ = nullptr;
            delete counter_;
            counter_ = nullptr;
        }
    }

    void acquire_(T* data, std::atomic_int32_t* counter)
    {
        data_ = data;
        counter_ = counter;
        ++*counter_;
    }
};

#endif /* _SMART_POINTER_H_ */
