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
using Node = std::array<int, 3>;

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& numbers) {
    for(const auto& a:numbers) {
        stream << a << endl;
    }
    return stream;
}

void outputs_result(int result)
{
    filesystem::path file_out(filesystem::current_path());
    file_out.append("output.txt");
    std::ofstream stream(file_out.native(), ios_base::out);

    stream << result;
}

int MAX = 0;
void foo(const std::vector<Node>& tree, int pos, int max_len)
{
    ++max_len;
    if (MAX <= max_len) MAX= max_len;

    if (tree[pos][1]!=0) foo(tree, tree[pos][1]-1, max_len);
    if (tree[pos][2]!=0) foo(tree, tree[pos][2]-1, max_len);
}
int main()
{
    filesystem::path file_in(filesystem::current_path());
    file_in.append("input.txt");

    std::ifstream stream(file_in.native(), ios_base::in);

    std::size_t Q;
    stream >> Q;
    std::vector<Node> tree(Q);
    for(std::size_t i=0; i<Q; ++i)
    {
        int root, left, right;
        stream >> root >> left >> right;
        tree[i] = {root, left, right};
    }

    int max_len = 0;

    if (!tree.empty()) foo(tree, 0, max_len);
//    std::cout << MAX << std::endl;
    outputs_result(MAX);
// ***********************************************************************************************
    return 0;
}
