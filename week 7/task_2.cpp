#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <memory>

struct Node;
struct Input_Node;

using ptr_node  = std::shared_ptr<Node>;
using ptr_inode = std::shared_ptr<Input_Node>;

enum SIDE
{
    RIGHT   =0,
    LEFT    =1
};

struct Input_Node
{
    int key;
    int children[2];

    Input_Node(int key, int left, int right) : key(key)
    {
        children[0] = left;
        children[1] = right;
    }
};

struct Node
{
    int key;
    int height;
    int position;
    ptr_node children[2];

    Node(int key, ptr_node left, ptr_node right, int position) : key(key), height(0), position(position)
    {
        children[0] = left;
        children[1] = right;
    }

    Node(ptr_inode node, int position) :  key(node->key), height(0), position(position)
    {
        children[0] = children[1] = nullptr;
    }
};

struct AVL_Tree
{
    std::vector<ptr_inode> input_tree;                          //< сюда считываем данные
    std::vector<ptr_inode> output_tree;                         //< сюда записываем данные
    ptr_node root = nullptr;                                    //< само дерево

    void CreateTree()                                           //< создаем само дерево
    {
        root = std::make_shared<Node>(input_tree[0], 0);
        AddChildren(root);
    }
    void AddChildren(ptr_node node)                             //< рекурсивно добавляем потомков
    {
        for (int i = 0; i < 2; i++)
        {
            const auto& position_child = input_tree[node->position]->children[i];
            if (position_child == -1)
            {
                node->children[i] = nullptr;
            }
            else
            {
                node->children[i] = std::make_shared<Node>(input_tree[position_child], position_child);
                AddChildren(node->children[i]);
            }
        }
    }

    int CheckBalance(const ptr_node node) const
    {
        return (node->children[1] != nullptr ? node->children[1]->height : 0) -
               (node->children[0] != nullptr ? node->children[0]->height : 0);
    }

    void CheckHeight()
    {
        if (input_tree.empty())
        {
            return ;
        }

        UpdateHeight(root);
    }

    void ChechHeightChild(ptr_node node)
    {
        node->height = std::max(GetHeightRight(node), GetHeightLeft(node)) + 1;
    }

    int GetHeightRight(ptr_node v)
    {
        return v->children[1] == nullptr ? 0 : v->children[1]->height;
    }

    int GetHeightLeft(ptr_node v)
    {
        return v->children[0] == nullptr ? 0 : v->children[0]->height;
    }

    void UpdateHeight(ptr_node node)
    {
        for (auto child : node->children)
        {
            if (child != nullptr)
            {
                UpdateHeight(child);
            }
        }
        ChechHeightChild(node);
    }

    ptr_node rotate(ptr_node node, SIDE side)
    {
        ptr_node new_node = node->children[side == SIDE::LEFT ? 1 : 0];
        node->children[side == SIDE::LEFT ? 1 : 0] = new_node->children[side == SIDE::LEFT ? 0 : 1];
        new_node->children[side == SIDE::LEFT ? 0 : 1] = node;
        UpdateHeight(node);
        UpdateHeight(new_node);
        return new_node;
    }

    ptr_node Balance(ptr_node node)
    {
        auto& right_child = node->children[1];
        //< цитата из задачи "за исключением случая, когда у правого ребенка корня баланс до поворота равен −1"
        //< делаем "правый поворот"
        if (CheckBalance(right_child) < 0)
        {
            right_child = rotate(right_child, SIDE::RIGHT);
        }
        //< делаем "левый поворот"
        return rotate(node, SIDE::LEFT);
    }

    void make_output_tree()
    {
        std::queue<ptr_node> queue;
        queue.push(root);
        int num = 1;
        while (!queue.empty())
        {
            ptr_node v = queue.front();
            queue.pop();
            int children_num[2] = {0, 0};
            for (int i = 0; i < 2; i++)
            {
                if (v->children[i] != nullptr)
                {
                    queue.push(v->children[i]);
                    children_num[i] = ++num;
                }
            }
            output_tree.push_back(std::make_shared<Input_Node>(v->key, children_num[0], children_num[1]));
        }
    }
};

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t n;
    in >> n;
    auto avl = std::make_unique<AVL_Tree>();

    for (std::size_t i = 0; i < n; i++)
    {
        int key;
        int left, right;
        in >> key >> left >> right;
        avl->input_tree.push_back(std::make_shared<Input_Node>(key, left-1, right-1));
    }

    avl->CreateTree();
    avl->CheckHeight();
    avl->root = avl->Balance(avl->root);

    avl->make_output_tree();

    out << n << std::endl;
    for (auto v : avl->output_tree)
    {
        out << v->key << " " << v->children[0] << " " << v->children[1] << std::endl;
    }
}
