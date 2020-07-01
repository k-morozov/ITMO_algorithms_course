#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;
using Type = long;
template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& numbers) {
    for(const auto& a:numbers) {
        stream << a << " ";
    }
    return stream;
}


void radix_sort(std::vector<Type>& v, std::vector<Type>& sortedArray, Type digit) {
    static std::array<Type, 65536> countsArray;
    countsArray.fill(0);
    digit *= 16;

    for(const auto& item : v)
    {
        std::size_t countIndex = (item>>digit) & 0xFFFF;
        ++countsArray[countIndex];
    }

    Type prevCounter = 0;
    for (std::size_t i = 1; i < countsArray.size(); i++)
    {
        if (countsArray[i] > 0)
        {
            countsArray[i] +=  countsArray[prevCounter];
            prevCounter = i;
        }
    }

    for (int i = v.size() - 1; i >= 0; i--)
    {
        Type countIndex = (v[i] >> digit) & 0xFFFF;
        sortedArray[--countsArray[countIndex]] = v[i];
    }
    v = sortedArray;
}

int main()
{
    std::vector<Type> not_sorted_array;
    {
        filesystem::path file_in(filesystem::current_path());
        file_in.append("input.txt");

        std::ifstream stream(file_in.native(), ios_base::in);

        filesystem::path file(filesystem::current_path());
        file.append("input.txt");
        {
            std::ifstream stream(file.native(), ios_base::in);
            std::size_t n;
            stream >> n;
            std::size_t m;
            stream >> m;
            uint32_t value;
            std::vector<uint32_t> a;

            for(std::size_t i=0; i<n; ++i) {
                stream >> value;
                a.emplace_back(value);
            }

            for(std::size_t i=0; i<m; ++i) {
                stream >> value;
                for(std::size_t j=0; j<a.size(); j++) {
                    not_sorted_array.emplace_back(a[j]*value);
                }
            }
        }

    }
    std::vector<Type> sortedArray(not_sorted_array.size());

    for(int i=0; i<2; ++i) {
        radix_sort(not_sorted_array, sortedArray, i);
    }

    int64_t value = 0;
    const std::size_t len = not_sorted_array.size();
//    cout << sortedArray << endl;
    for(std::size_t i=0; i<len; i+=10) {
        value += not_sorted_array[i];
    }

    {
        filesystem::path file_out(filesystem::current_path());
        file_out.append("output.txt");
        std::ofstream stream(file_out.native(), ios_base::out);

        stream << value << std::endl;
//        std::cout << value << std::endl;
    }

    return 0;
}
