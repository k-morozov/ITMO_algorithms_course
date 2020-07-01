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

using namespace std;
using Type = int;

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& numbers) {
    for(const auto& a:numbers) {
        stream << a << endl;
    }
    return stream;
}

void outputs_result(const std::vector< std::pair<int, int>*> & results)
{
    filesystem::path file_out(filesystem::current_path());
    file_out.append("output.txt");
    std::ofstream stream(file_out.native(), ios_base::out);

    for(const auto& res:results)
    {
        stream << res->first << " " << res->second << std::endl;
    }
}

int main()
{
    std::size_t count_elements, count_request;

    filesystem::path file_in(filesystem::current_path());
    file_in.append("input.txt");

    std::ifstream stream(file_in.native(), ios_base::in);

    stream >> count_elements;
    std::vector<int> base_vector(count_elements);

    for(auto& a:base_vector)
    {
        stream >> a;
    }

    stream >> count_request;
    std::map<int, std::pair<int, int>> results;

    std::vector< std::pair<int, int>*> total_results(count_request);

    std::set<int> values_first, values_end;
    int value;
    for(std::size_t i=0; i<count_request; ++i)
    {
        stream >> value;
        results[value] = std::make_pair(-1, -1);
        values_first.insert(value);
        total_results[i] = &results.at(value);
    }
// ***********************************************************************************************
    for(std::size_t pos=0; pos<count_elements; ++pos)
    {
        if (values_first.find(base_vector[pos])!= values_first.end())
        {
            results[base_vector[pos]].first = pos + 1;
            values_end.insert(base_vector[pos]);
            values_first.erase(base_vector[pos]);
        }
    }

    for(int pos=count_elements-1; pos>=0; --pos)
    {
        if (values_end.find(base_vector[pos])!= values_end.end())
        {
            results[base_vector[pos]].second = pos + 1;
            values_end.erase(base_vector[pos]);
        }
    }
// ***********************************************************************************************
    outputs_result(total_results);
    return 0;
} 
