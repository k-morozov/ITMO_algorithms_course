#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& numbers) {
    for(const auto& a:numbers) {
        stream << a << " ";
    }
    return stream;
}

void init_rand(std::vector<int> &numbers, int size) {
    for(int i=0; i<size; ++i) {
        numbers.emplace_back(std::rand()%100);
    }
}

void read_input(std::vector<int> &numbers) {
    filesystem::path file(filesystem::current_path());
    file.append("input.txt");
    {
        std::ifstream stream(file.native(), ios_base::in);
        int count, value;
        stream >> count;
        for(int i=0; i<count; ++i) {
            stream >> value;
            numbers.emplace_back(value);
        }
    }
}
int main()
{
    std::vector<int> numbers;
    read_input(numbers);
    //cout << numbers << endl;
    filesystem::path file(filesystem::current_path());
    file.append("output.txt");
    std::ofstream stream(file.native(), ios_base::out);

    stream << 1 << " ";
    for(auto i=1; i<static_cast<int>(numbers.size()); ++i) {
        auto j=i - 1;
        auto new_ind = i;
        while (j>=0 && numbers[j]>numbers[j+1]) {
            new_ind = j;
            std::swap(numbers[j], numbers[j+1]);
            --j;
        }
        stream << new_ind+1 << " ";
    }
    stream << endl;
    stream << numbers << endl;

    return 0;
}
