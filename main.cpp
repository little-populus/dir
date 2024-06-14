#include <evaluator.hpp>
#include <iostream>
#include <parser.hpp>
#include <unit.hpp>

int main(int argc, char *argv[])
{
    std::string data{};
    if (argc == 1)
    {
        std::cin >> data;
    }
    else if (argc == 2)
    {
        data = argv[1];
    }
    else
    {
        std::cout << "error" << std::endl;
        return 0;
    }
    auto i = parser().parse(data);
    if (i)
        // for (auto &j : *i)
        //     std::cout << j->get_data() << std::endl;
        ;
    else
        std::cout << "error" << std::endl;
    evaluator e;
    std::cout << e.evaluate(*i) << '\n';
    return 0;
}