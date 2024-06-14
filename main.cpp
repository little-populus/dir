#include <evaluator.hpp>
#include <iostream>
#include <parser.hpp>
#include <unit.hpp>

int main(int argc, char *argv[])
{
    std::string data{};
    if (argc == 1)
    {
        while (1)
        {
            std::cin >> data;
            auto i = parser().parse(data);
            if (!i)
                std::cout << "error" << std::endl;
            evaluator e;
            std::cout << e.evaluate(*i) << '\n';
        }
    }
    else if (argc == 2)
    {
        data = argv[1];
        auto i = parser().parse(data);
        if (!i)
            std::cout << "error" << std::endl;
        evaluator e;
        std::cout << e.evaluate(*i) << '\n';
        return 0;
    }
    else
    {
        std::cout << "error" << std::endl;
        return 0;
    }

    return 0;
}