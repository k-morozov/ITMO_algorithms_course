#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <deque>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <iterator>
#include <array>

using namespace std;
using Node = std::array<int, 4>;

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& numbers) {
    for(const auto& a:numbers) {
        stream << a << endl;
    }
    return stream;
}

void outputs_result(const std::vector<int>& results)
{
    filesystem::path file_out(filesystem::current_path());
    file_out.append("output.txt");
    std::ofstream stream(file_out.native(), ios_base::out);

    for(const auto& result: results)
    {
        stream << result << std::endl;
//        cout << result << std::endl;
    }
}

int remove_nodes(std::vector<Node>& tree, std::size_t pos)
{
    int count_rem_heads = 1;

    if (tree[pos][1]>0)
    {
        count_rem_heads += remove_nodes(tree, tree[pos][1]-1);
        tree[pos][1] = 0;
    }
    if (tree[pos][2]>0)
    {
        count_rem_heads += remove_nodes(tree, tree[pos][2]-1);
        tree[pos][2] = 0;
    }

    return count_rem_heads;
}


std::vector<int> foo(std::vector<Node>& tree, const std::vector<int>& list_remove , int count_head)
{
    std::vector<bool> status_node(tree.size(), true);
    std::vector<int> results;

    for(const auto& remove_element: list_remove)
    {
        std::size_t pos = 0;
        while (pos < tree.size())
        {
            if (tree[pos][0] == remove_element && status_node[pos])
            {
                break;
            }
            else
            {
                if (remove_element > tree[pos].front() && tree[pos][2] != 0)
                {
                    pos = tree[pos][2]-1;
                }
                else
                {
                    if (remove_element <= tree[pos].front()  && tree[pos][1] != 0)
                    {
                        pos = tree[pos][1]-1;
                    } else break;
                }
            }
        }

        if (tree[pos][0] == remove_element)
        {
            int count_rem_heads = 0;
            count_rem_heads += remove_nodes(tree, pos);

            count_head -= count_rem_heads;

            for(std::size_t i=0; i<tree.size(); ++i)
            {
                if (tree[i][1] == pos+1)
                {
                    tree[i][1] = 0;
                    break;
                }
                if (tree[i][2] == pos+1)
                {
                    tree[i][2] = 0;
                    break;
                }
            }
        }
        results.push_back(count_head);

    }
    return results;
}
int main()
{
    filesystem::path file_in(filesystem::current_path());
    file_in.append("input.txt");

    std::ifstream stream(file_in.native(), ios_base::in);

    std::size_t count_head;
    stream >> count_head;
    std::vector<Node> tree(count_head);
    for(std::size_t i=0; i<count_head; ++i)
    {
        int root, left, right;
        stream >> root >> left >> right;
        tree[i] = {root, left, right, 1};
    }
    int count_remove;
    stream >> count_remove;
    std::vector<int> list_remove(count_remove);
    for(auto& a: list_remove)
    {
        stream >> a;
    }

    if (!tree.empty()) outputs_result(foo(tree, list_remove, count_head));
// ***********************************************************************************************
    return 0;
}
