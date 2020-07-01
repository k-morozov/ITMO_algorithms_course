#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdlib>
#include <unordered_map>

using namespace std;
using Type = int;

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
    std::vector<Type> numbers;
    read_input(numbers);
    cout << numbers << endl;
    filesystem::path file(filesystem::current_path());
    file.append("output.txt");
    std::ofstream stream(file.native(), ios_base::out);

    for(int i=numbers.size() - 1; i>=0; --i) {
        int max_pos = 0;
        int max_num = numbers[0];
        for(auto j=0; j<=i; ++j) {
            if (numbers[j]>max_num) {
                max_num = numbers[j];
                max_pos = j;
            }
        }
        if (numbers[max_pos] == numbers[i]) continue;
        std::swap(numbers[max_pos], numbers[i]);
        stream << "Swap elements at indices "<< max_pos+1 << " and " << i+1 << "." << std::endl;

    }
    stream << "No more swaps needed."<< std::endl << numbers;
    std::cout << numbers << std::endl;
    return 0;
}
