#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <deque>
#include <map>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;
using Type = int;

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& numbers) {
    for(const auto& a:numbers) {
        stream << a << endl;
    }
    return stream;
}
void outputs_result(const std::vector<bool> & res)
{
    filesystem::path file_out(filesystem::current_path());
    file_out.append("output.txt");
    std::ofstream stream(file_out.native(), ios_base::out);
    for(const auto& flag:res)
    {
        stream << (flag?"YES":"NO") << endl;
    }

//    cout << seq;
}
bool foo(const std::string& data)
{
    std::stack<char> m_stack;
    for(const auto& a:data)
    {
        if (a=='(' || a=='[')
        {
            m_stack.push(a);
        }
        else
        {
            if (a==')')
            {
                if (m_stack.empty() || m_stack.top()!='(' ) return false;
                else m_stack.pop();
            }
            if (a==']')
            {
                if (m_stack.empty() || m_stack.top()!='[' ) return false;
                else m_stack.pop();
            }
        }
    }

    return m_stack.empty();
}
int main()
{
    std::vector<bool> data;

    std::size_t Q;

    filesystem::path file_in(filesystem::current_path());
    file_in.append("input.txt");

    std::ifstream stream(file_in.native(), ios_base::in);

    stream >> Q;
    std::string word;

    for(std::size_t i=0; i<Q; ++i)
    {
        stream >> word;
//        cout << word << endl;
        data.emplace_back(foo(word));
//        cout << data.back() << endl;
    }

    outputs_result(data);
    return 0;
}
