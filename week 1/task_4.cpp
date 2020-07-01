#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdlib>
#include <unordered_map>
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

template <typename T>
void read_input(std::vector<T> &numbers) {
    filesystem::path file(filesystem::current_path());
    file.append("input.txt");
    {
        std::ifstream stream(file.native(), ios_base::in);
        int count;
        stream >> count;
        T value;
        for(int i=0; i<count; ++i) {
            stream >> value;
            numbers.emplace_back(value);
        }
    }
}
int main()
{
    std::vector<double> numbers;
    read_input(numbers);
    cout << numbers << endl;
    filesystem::path file(filesystem::current_path());
    file.append("output.txt");
    std::ofstream stream(file.native(), ios_base::out);

    std::unordered_map<double, int> base;
    for(int i=0; i<static_cast<int>(numbers.size()); ++i) {
        base[numbers[i]] = i+1;
    }
    for(auto i=1; i<static_cast<int>(numbers.size()); ++i) {
        auto j=i - 1;
        while (j>=0 && numbers[j]>numbers[j+1]) {
            std::swap(numbers[j], numbers[j+1]);
            --j;
        }
    }
    stream << base.at(numbers[0]) << " " << base.at(numbers[numbers.size()/2])
            << " " << base.at(numbers[numbers.size()-1]) <<  endl;

    return 0;
}
