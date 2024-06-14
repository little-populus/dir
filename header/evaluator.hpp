#pragma once
#include <memory>
#include <unit.hpp>
#include <vector>
struct queue;
struct evaluator
{
    struct node
    {
        enum class operator_type
        {
            add,
            sub,
            mul,
            div,
            null
        };
        std::shared_ptr<node> left;
        std::shared_ptr<node> right;
        std::shared_ptr<unit> data;
        double value = 0;
        operator_type type = operator_type::null;
        inline static std::shared_ptr<unit> zero = std::make_shared<struct value>("0");

        static std::shared_ptr<node> get_basic_tree();
        node(std::shared_ptr<unit> data = nullptr, std::shared_ptr<node> left = nullptr,
             std::shared_ptr<node> right = nullptr);
        node &operator=(const node &other);
        double evaluate();
        virtual ~node() = default;
    };
    struct tree
    {
        std::shared_ptr<node> root;
        bool evaluated = false;
        double evaluate();
        tree();
        virtual ~tree() = default;
    };
    tree generated_tree;
    std::unique_ptr<queue> q;

    evaluator() = default;
    [[nodiscard("should be returned as a result")]] double evaluate(std::vector<std::shared_ptr<unit>> data);
    tree transform_to_tree(std::vector<std::shared_ptr<unit>> &data);
};

#include <queue.hpp>