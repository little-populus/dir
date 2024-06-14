#include <evaluator.hpp>
#include <memory>
#include <stack>
#include <string>
#include <unit.hpp>
#include <vector>

double evaluator::evaluate(std::vector<std::shared_ptr<unit>> data)
{
    if (data.empty())
    {
        return 0;
    }
    generated_tree = transform_to_tree(data);
    return generated_tree.evaluate();
}

double evaluator::tree::evaluate()
{
    if (!evaluated)
    {
        root->value = root->evaluate();
        evaluated = true;
    }
    return root->value;
}

double evaluator::node::evaluate()
{
    if (type == operator_type::null)
    {
        return value;
    }
    else
    {
        if (type == operator_type::add)
        {
            value = left->evaluate() + right->evaluate();
            return value;
        }
        if (type == operator_type::sub)
        {
            value = left->evaluate() - right->evaluate();
            return value;
        }
        if (type == operator_type::mul)
        {
            value = left->evaluate() * right->evaluate();
            return value;
        }
        if (type == operator_type::div)
        {
            value = left->evaluate() / right->evaluate();
            return value;
        }
    }
    return 0;
}

evaluator::node::node(std::shared_ptr<unit> data, std::shared_ptr<node> left, std::shared_ptr<node> right)
{
    this->data = data;
    this->left = left;
    this->right = right;
    this->type = operator_type::null;
    if (!data)
        this->data = evaluator::node::zero;
    else if (data->get_type() == unit_type::value)
        this->value = std::stod(data->get_data());
    else if (data->get_type() == unit_type::op)
    {
        switch (data->get_data()[0])
        {
        case '+':
            this->type = operator_type::add;
            break;
        case '-':
            this->type = operator_type::sub;
            break;
        case '*':
            this->type = operator_type::mul;
            break;
        case '/':
            this->type = operator_type::div;
            break;
        }
    }
}
std::shared_ptr<evaluator::node> evaluator::node::get_basic_tree()
{
    std::shared_ptr<node> l_node;
    l_node = std::make_shared<evaluator::node>();
    l_node->type = evaluator::node::operator_type::add;
    l_node->left = std::make_shared<evaluator::node>();
    l_node->right = std::make_shared<evaluator::node>();
    return l_node;
}

evaluator::node &evaluator::node::operator=(const node &other)
{
    this->data = other.data;
    this->left = other.left;
    this->right = other.right;
    this->value = other.value;
    this->type = other.type;
    return *this;
}
evaluator::tree::tree()
{
    root = node::get_basic_tree();
}

evaluator::tree evaluator::transform_to_tree(std::vector<std::shared_ptr<unit>> &data)
{
    std::stack<std::shared_ptr<node>> stack;
    std::shared_ptr<node> node = node::get_basic_tree();
    q = std::make_unique<queue>();
    for (auto i = 0; i < data.size(); ++i)
    {
        q->enqueue(std::make_shared<evaluator::node>(data[i]));
    }
    generated_tree.root = q->tree_root();
    return generated_tree;
}