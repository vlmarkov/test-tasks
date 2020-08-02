#pragma once

#include <string>
#include <exception>


class Exception : public std::exception
{
    public:
        Exception(const char* err, int code = -1);
        ~Exception() = default;

        virtual const char* what() const noexcept override;
        int code() const noexcept;

    private:
        int         code_;
        std::string err_;
};