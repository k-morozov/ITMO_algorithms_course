#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <deque>
#include <map>
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
template <typename T>
void outputs_result(const std::vector<T>& seq)
{
    filesystem::path file_out(filesystem::current_path());
    file_out.append("output.txt");
    std::ofstream stream(file_out.native(), ios_base::out);

    stream << seq;
//    cout << seq;
}

int main()
{
    std::deque<int> working_data;
    std::vector<int> min_data;
    std::map<int, int> sorted_min;
    std::size_t Q;

    filesystem::path file_in(filesystem::current_path());
    file_in.append("input.txt");

    std::ifstream stream(file_in.native(), ios_base::in);

    stream >> Q;
    char action;
    int value;

    for(std::size_t i=0; i<Q; ++i)
    {
        stream >> action;
        if (action == '+')
        {
            stream >> value;
            working_data.emplace_back(value);
            ++sorted_min[value];
         }
         else
         {
            if (action == '-')
            {
                --sorted_min[working_data.front()];
                if (sorted_min[working_data.front()]==0)
                {
                    sorted_min.erase(working_data.front());
                }
                working_data.pop_front();
            }
            else
            {
                min_data.push_back(sorted_min.begin()->first);
            }
        }
    }

    outputs_result(min_data);
    return 0;
}
