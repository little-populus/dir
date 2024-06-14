#include <memory>
#include <parser.hpp>
#include <unit.hpp>
#include <vector>

std::optional<std::vector<std::shared_ptr<unit>>> parser::parse(std::string_view data)
{
    bracket_match = 0;
    std::vector<std::shared_ptr<unit>> units;
    int negative = 1;
    if (data.empty())
        return std::nullopt;
    for (auto i = 0; i < data.size(); ++i)
    {
        u.clear();
        if (data[i] == '(')
        {
            bracket_match++;
            u += data[i];
            units.emplace_back(new bracket(u));
        }
        else if (data[i] == ')')
        {
            bracket_match--;
            if (bracket_match < 0)
                return std::nullopt;
            if (units.back()->get_type() == unit_type::op)
                return std::nullopt;
            if (units.back()->get_type() == unit_type::bracket and units.back()->get_data() == "(")
                return std::nullopt;
            u += data[i];
            units.emplace_back(new bracket(u));
        }
        else if (data[i] == '+' || data[i] == '-' || data[i] == '*' || data[i] == '/')
        {
            if ((units.empty() || (units.back()->get_data() == "(" || units.back()->get_data() == "+" ||
                                   units.back()->get_data() == "-")) &&
                (data[i] == '*' || data[i] == '/'))
                return std::nullopt;
            if (bool flag = false; units.empty() || units.back()->get_data() == "(" ||
                                   units.back()->get_data() == "+" || units.back()->get_data() == "-")
            {
                for (auto j = i; j < data.size(); ++j)
                {
                    if (data[j] == '-')
                        negative *= -1;
                    else if (data[j] == '+')
                        continue;
                    else
                    {
                        i = j - 1;
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    continue;
            }
            u += data[i];
            units.emplace_back(new op(u));
        }
        else if (data[i] >= '0' and data[i] <= '9' or data[i] == '.')
        {
            auto dot = false;
            if (negative == -1)
                u += '-';
            for (auto j = i; j < data.size(); ++j)
            {
                if (data[j] >= '0' and data[j] <= '9')
                    u += data[j];
                else if (data[j] == '.')
                    if (dot == 0)
                        u += data[j];
                    else
                        return std::nullopt;
                else
                    break;
            }
            negative = 1;
            units.emplace_back(new value(u));
            i += u.size() - 1;
        }
        else
        {
            return std::nullopt;
        }
    }

    if (bracket_match != 0)
        return std::nullopt;

    return units;
}