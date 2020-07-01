#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <climits>
#include <array>

using Node = std::array<int, 3>;
using Tree_type = std::vector<Node>;

bool foo(const Tree_type& tree, int low = INT_MIN, int high = INT_MAX, int pos = 0)
{
    bool result = true;
    if (tree.empty()) return result;

    const int& pos_left = tree[pos][1];
    const int& pos_right = tree[pos][2];
    const int& value = tree[pos][0];

    if (value<=low || value>=high) return false;

    if (pos_left!=0)
    {
        if (tree[pos_left-1][0]>=value) return false;
        else result = foo(tree, low, value, pos_left-1);
    }
    if (!result) return false;
    if (pos_right!=0)
    {
        if (tree[pos_right-1][0]<=value) return false;
        else result = foo(tree, value, high, pos_right-1);
    }

    return result;
}
int main()
{
    std::filesystem::path file_in(std::filesystem::current_path());
    file_in.append("input.txt");
    std::ifstream stream_in(file_in.native(), std::ios_base::in);

    std::size_t counts;
    stream_in >> counts;
    Tree_type tree(counts);

    for(std::size_t i=0; i<counts; ++i)
    {
        int value, left, right;
        stream_in >> value >> left >> right;
        tree[i] = {value, left, right};
    }

    bool result = foo(tree);

    std::filesystem::path file_out(std::filesystem::current_path());
    file_out.append("output.txt");
    std::ofstream stream_out(file_out.native(), std::ios_base::out);
    stream_out << (result ? "YES" : "NO");
    std::cout << (result ? "YES" : "NO") << std::endl;
    return 0;
}
