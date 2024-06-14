#pragma once
#include <evaluator.hpp>
#include <memory>
#include <stack>
#include <vector>
struct queue
{
    using node = evaluator::node;
    int i{};
    std::stack<std::shared_ptr<node>> stack;
    std::shared_ptr<node> m_node = node::get_basic_tree();
    std::vector<std::vector<std::shared_ptr<node>>> op{};
    std::vector<std::vector<std::shared_ptr<node>>> v{};
    queue()
    {
        op.emplace_back(std::vector<std::shared_ptr<node>>());
        v.emplace_back(std::vector<std::shared_ptr<node>>());
    }
    void enqueue(std::shared_ptr<node> node);
    std::shared_ptr<evaluator::node> tree_root();
    ~queue() = default;
};