#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <algorithm>

using namespace std;

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& numbers) {
    for(const auto& a:numbers) {
        stream << a << " ";
    }
    return stream;
}

template <typename T>
std::size_t read_input(std::vector<T> &numbers) {
    filesystem::path file(filesystem::current_path());
    file.append("input.txt");
    {
        std::ifstream stream(file.native(), ios_base::in);
        int count;
        stream >> count;
        std::size_t k;
        stream >> k;
        T value;
        for(int i=0; i<count; ++i) {
            stream >> value;
            numbers.emplace_back(value);
        }
        return k;
    }

}

int main()
{
    std::vector<int32_t> numbers;
    filesystem::path file_in(filesystem::current_path());
    file_in.append("input.txt");

    std::ifstream stream(file_in.native(), ios_base::in);


    std::size_t step = read_input(numbers);

    for(std::size_t i=0; i<step; i++) {
        std::vector<int> value;
        for(std::size_t j=i; j<numbers.size(); j+=step) {
            value.emplace_back(std::move(numbers[j]));
        }
        std::sort(value.begin(), value.end());

        for(std::size_t pos = 0, j=i; pos<value.size(); ++pos, j+=step) {
            numbers[j] = value[pos];
        }
    }

    {
        filesystem::path file_out(filesystem::current_path());
        file_out.append("output.txt");
        std::ofstream stream(file_out.native(), ios_base::out);

        stream << (std::is_sorted(numbers.begin(), numbers.end())? "YES":"NO") << std::endl;
    }

    return 0;
}
