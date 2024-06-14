#pragma once
#include <string>
enum struct unit_type
{
    op,
    value,
    bracket
};
struct unit
{
    std::string data;
    virtual unit_type get_type() = 0;
    unit(std::string data) : data(data)
    {
    }
    const std::string &get_data() const
    {
        return data;
    }
    virtual ~unit() = default;
};

struct op : unit
{
    inline static unit_type type = unit_type::op;
    op(std::string data) : unit(data)
    {
    }
    unit_type get_type() override;
};

struct value : unit
{
    inline static unit_type type = unit_type::value;
    value(std::string data) : unit(data)
    {
    }
    unit_type get_type() override;
};

struct bracket : unit
{
    inline static unit_type type = unit_type::bracket;
    bracket(std::string data) : unit(data)
    {
    }
    unit_type get_type() override;
};