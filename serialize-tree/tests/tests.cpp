#include <tree/tree.hpp>
#include <parser/parser.hpp>
#include <exception/exception.hpp>

#include <iostream>

#include <stdio.h>


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
        throw Exception("can't open deserialize file");
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

int test_empty_tree()
{
    try
    {
        TestWriter tw("./in.txt", "");
        TestWriter tr("./out.txt", "");

        Tree tree;
        tree.deserialize("./in.txt");
        tree.serialize("./out.txt");
    }
    catch (...)
    {
        return -1;
    }

    return 0; 
}

int test_tree(const char* sample)
{
    try
    {
        const 
        TestWriter tw("./in.txt", sample);
        TestWriter tr("./out.txt", "");

        Tree tree;
        tree.deserialize("./in.txt");
        tree.serialize("./out.txt");

        if (compare("./out.txt", sample) != 0)
        {
            return -1;
        }
    }
    catch (...)
    {
        return -1;
    }

    return 0; 
}


int main(int argc, char const* argv[])
{
    if (test_empty_tree() != 0)
    {
        return -1;
    }
    if (test_tree("8:{}") != 0)
    {
        return -1;
    }
    if (test_tree("8:{\"bar\":{2.015:{9:{}},2015:{},\"2015\":{}},\"baz\":{\"foo\":{},6.28318:{\"hello\":{}}}}") != 0)
    {
        return -1;
    }
    if (test_tree("8:") == 0)
    {
        return -1;
    }
    return 0;
}
