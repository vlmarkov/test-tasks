#pragma once

#include <string>
#include <exception>


enum class errors{ none, malformed, type, cmdline };

class Exception : public std::exception
{
    public:
        Exception(const char* err, int code);
        ~Exception() = default;

        virtual const char* what() const noexcept override;
        int code() const noexcept;

    private:
        int         code_;
        std::string err_;
};