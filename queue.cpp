#include <evaluator.hpp>
#include <memory>
#include <queue.hpp>
#include <unit.hpp>

void queue::enqueue(std::shared_ptr<node> node)
{
    if (node->data->get_type() == unit_type::bracket)
    {
        if (node->data->get_data() == "(")
        {
            ++i;
            v.emplace_back(std::vector<std::shared_ptr<evaluator::node>>());
            op.emplace_back(std::vector<std::shared_ptr<evaluator::node>>());
            stack.emplace(m_node);
            m_node = evaluator::node::get_basic_tree();
        }
        else
        {
            if (v[i].size() == 2)
            {
                m_node = op[i][0];
                m_node->right = v[i][1];
            }
            m_node->left = v[i][0];
            v.resize(i);
            op.resize(i);
            --i;
            v[i].emplace_back(m_node);
            m_node = stack.top();
            stack.pop();
        }
    }
    else if (node->type == evaluator::node::operator_type::null)
    {
        v[i].emplace_back(node);
        if (int c1, c2; op[i].size() == 2)
        {
            if (op[i][0]->type == node::operator_type::add || op[i][0]->type == node::operator_type::sub)
                c1 = 0;
            else
                c1 = 1;
            if (op[i][1]->type == node::operator_type::add || op[i][1]->type == node::operator_type::sub)
                c2 = 0;
            else
                c2 = 1;
            if (c1 < c2)
            {
                node->right = node::get_basic_tree();
                node->right->type = op[i][1]->type;
                node->right->left = v[i][1];
                node->right->right = v[i][2];
                v[i][1] = node->right;
                op[i].resize(1);
                v[i].resize(2);
            }
            else
            {
                node->left = node::get_basic_tree();
                node->left->type = op[i][0]->type;
                node->left->left = v[i][0];
                node->left->right = v[i][1];
                v[i][0] = node->left;
                v[i][1] = v[i][2];
                op[i][0] = op[i][1];
                op[i].resize(1);
                v[i].resize(2);
            }
        }
    }
    else
    {
        op[i].emplace_back(node);
    }
}

std::shared_ptr<evaluator::node> queue::tree_root()
{
    if (v[0].size() == 1)
    {
        m_node->left = v[0][0];
    }
    if (v[0].size() == 2)
    {
        m_node->type = op[0][0]->type;
        m_node->left = v[0][0];
        m_node->right = v[0][1];
    }
    return m_node;
}