#include <cmath>
#include <evaluator.hpp>
#include <iostream>
#include <parser.hpp>
#include <unit.hpp>

int main(int argc, char *argv[])
{
    std::string data{};
    double result;
    if (argc == 1)
    {
        while (1)
        {
            std::cin >> data;
            auto i = parser().parse(data);
            if (!i)
                std::cout << "error" << std::endl;
            evaluator e;
            result = e.evaluate(*i);
            if (std::fmod(result, 1) == 0)
                std::cout << std::format("{:>16.0f}", result) << '\n';
            else
                std::cout << std::format("{:>16f}", result) << '\n';
        }
    }
    else if (argc >= 2)
    {
        int j = 1;
        for (j = 1; j < argc; ++j)
        {
            data = argv[j];
            auto i = parser().parse(data);
            if (!i)
                std::cout << "error" << std::endl;
            evaluator e;
            result = e.evaluate(*i);
            if (std::fmod(result, 1) == 0)
                std::cout << std::format("{:>16.0f}", result) << '\n';
            else
                std::cout << std::format("{:>16f}", result) << '\n';
        }
        return 0;
    }
    else
    {
        std::cout << "error" << std::endl;
        return 0;
    }

    return 0;
}