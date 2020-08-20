#pragma once

#include <tree/tree.hpp>
#include <parser/parser.hpp>
#include <exception/exception.hpp>


class TestWriter
{
    public:
        TestWriter(const char* file, const char* string) : file_(file)
        {
            std::ofstream ofs;
            ofs.open(file);
            ofs << string;
            ofs.close();
        }

        ~TestWriter()
        {
            ::remove(this->file_.c_str());
        }

    private:
        std::string file_;
};

class TestReader
{
    public:
        TestReader(const char* file) : file_(file) 
        {
            ;
        }

        ~TestReader()
        {
            ::remove(this->file_.c_str());
        }

    private:
        std::string file_;
};

int compare(const char* file, const char* sample)
{
    std::ifstream ifs(file, std::ifstream::in);
    if (!ifs.is_open())
    {
        throw Exception("can't open deserialize file", errno);
    }

    std::string line;
    std::getline(ifs, line);
    ifs.close();

    if (line.compare(sample) != 0)
    {
        return -1;
    }

    return 0;
}
