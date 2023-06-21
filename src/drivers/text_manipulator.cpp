#include "text_manipulator.h"

std::string toUpperCase(const std::string &str)
{
    std::string result = str;
    for (char &c : result)
    {
        c = std::toupper(c);
    }
    return result;
}

// Takes string and convert to Unsigned int string that is Non-Zero
std::string toUintStringNZ(std::string len)
{
    if (len.empty())
    {
        len = "1";
    }
    unsigned int num = std::stoul(len);
    if (num <= 0)
    {
        num = 1;
    }
    return std::to_string(num);
}

void addTabs(std::string &str)
{
    std::size_t size = str.size() + 1;
    std::size_t tabs = 0;

    if (size < 28)
    {
        std::size_t roundedSize = 0;
        if (size % 4 != 0)
            roundedSize = ((size + 3) / 4) * 4;
        else
            roundedSize = size + 4;

        tabs = (28 - roundedSize) / 4;
    }

    str.append(tabs, '\t');
}