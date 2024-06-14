#pragma once
#include <memory>
#include <optional>
#include <string_view>
#include <unit.hpp>
#include <vector>
struct parser
{
    int bracket_match = 0;
    std::string u;
    [[nodiscard("should be used for evaluation")]] std::optional<std::vector<std::shared_ptr<unit>>> parse(
        std::string_view data);
};