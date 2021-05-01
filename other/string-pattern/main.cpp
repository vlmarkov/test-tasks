#include <unordered_map>
#include <iostream>
#include <string>


bool match(const std::string& patern, const std::string& string)
{
    if (patern.empty() || string.empty())
    {
        return false;
    }

    std::unordered_map<char, int> map;
    for (std::size_t i = 0; i < patern.size(); ++i)
    {
        map.insert({patern[i], i});
    }

    auto idx = -1;
    for (auto ch : string)
    {
        // if map.empty() -> return true to optimize loop
        auto found = map.find(ch);
        if (found != map.end())
        {
            if (idx + 1 != found->second)
            {
                return false;
            }
            else
            {
                idx++;
                map.erase(found);
            }
        }
    }

    return map.empty();
}

int main(int argc, char const *argv[])
{
    std::cout << match("fort", "five or ten") << std::endl;
    std::cout << match("fort", "five or one") << std::endl;
    std::cout << match("fort", "five rome one") << std::endl;
    std::cout << match("fort", "invalid") << std::endl;
    return 0;
}
