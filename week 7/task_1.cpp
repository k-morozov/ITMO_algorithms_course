#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>

const auto INPUT_FILE = "input.txt";
const auto OUTPUT_FILE = "output.txt";

enum STATUS
{
    NOT_FOUND = -1
};

struct Node
{
    explicit Node(int m_key, int m_left, int m_right): key(m_key)
    {
        children.first = m_left;
        children.second = m_right;
    }

    const int key;
    int height = 0;
    std::pair<int, int> children;
};

/*****************************************************************************************************************
*
*                                       DECLARATION
*
*****************************************************************************************************************/
class AVL_Tree
{
private:
    std::vector<std::shared_ptr<Node>> tree;
    void AddNode(int m_key, int m_left, int m_right)
    {
        tree.push_back(std::make_shared<Node>(m_key, m_left-1, m_right-1));
    }

    void update_height(std::shared_ptr<Node> ptr_node);

    std::pair<int, int> CheckChild(std::shared_ptr<Node> p_node) const;
    int GetChildHeight(std::shared_ptr<Node> p_node)
    {
        const auto child = CheckChild(p_node);
        return std::max(child.first, child.second);
    }
    int GetBalance(std::shared_ptr<Node> p_node) const
    {
        const auto child = CheckChild(p_node);
        return child.second - child.first;
    }

public:
    AVL_Tree() = default;
    AVL_Tree(const AVL_Tree&) = delete;
    AVL_Tree operator=(const AVL_Tree&) = delete;


    void LoadFromFile();
    void LoadToFile() const;

    void CheckHeight()
    {
        if (!tree.empty())
        {
            update_height(tree.front());
        }
    }
};

/*****************************************************************************************************************
*
*                                       MAIN
*
*****************************************************************************************************************/

int main()
{
    auto avl_tree = std::make_unique<AVL_Tree>();

    avl_tree->LoadFromFile();
    avl_tree->CheckHeight();
    avl_tree->LoadToFile();
    return 0;
}
/*****************************************************************************************************************
*
*                                       DEFINITION
*
*****************************************************************************************************************/
void AVL_Tree::update_height(std::shared_ptr<Node> ptr_node)
{
    if (ptr_node->children.first != STATUS::NOT_FOUND)
    {
        update_height(tree[ptr_node->children.first]);
    }
    if (ptr_node->children.second != STATUS::NOT_FOUND)
    {
        update_height(tree[ptr_node->children.second]);
    }

    ptr_node->height = GetChildHeight(ptr_node) + 1;

}

std::pair<int, int> AVL_Tree::CheckChild(std::shared_ptr<Node> p_node) const
{
    const auto& left_child = p_node->children.first;
    const auto& right_child = p_node->children.second;
    const auto left_height = (left_child != STATUS::NOT_FOUND) ? tree[left_child]->height : 0;
    const auto right_height = (right_child != STATUS::NOT_FOUND) ? tree[right_child]->height : 0;

    return std::make_pair(left_height, right_height);
}

void AVL_Tree::LoadFromFile()
{
    std::ifstream in(INPUT_FILE);

    std::size_t count;
    in >> count;

    int key, left, right;

    for(std::size_t i=0; i< count; ++i)
    {
        in >> key >> left >> right;
        AddNode(key, left, right);
    }
}
void AVL_Tree::LoadToFile() const
{
    std::ofstream out(OUTPUT_FILE);
    for(const auto& child : tree)
    {
        out << GetBalance(child) << std::endl;
    }
}
