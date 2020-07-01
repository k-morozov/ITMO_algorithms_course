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
int read_input(std::vector<T> &numbers) {
    filesystem::path file(filesystem::current_path());
    file.append("input.txt");
    {
        std::ifstream stream(file.native(), ios_base::in);
        int count;
        stream >> count;
//        T value;
//        for(int i=0; i<count; ++i) {
//            stream >> value;
//            numbers.emplace_back(value);
//        }
        return count;
    }

}

void quick_sort(int v[], int n) {
    if (n<=1) return;

    swap(v[0], v[rand()%n]);
    int last = 0;

    for(int i=1;i<n; ++i) {
        if (v[i]<v[0]) {
            swap(v[++last],v[i]);
        }
    }
    swap(v[0], v[last]);
    quick_sort(v, last);
    quick_sort(v + last +1, n-last-1);
}

int number;
void def(int* v,int len) {
    if (len<1) return;
    v[len/2] = number;
    --number;
    def(v+len/2+1, len - len/2-1);
    def(v, len/2);

}

int main()
{
    std::vector<int> numbers;
    int count = read_input(numbers);

    filesystem::path file(filesystem::current_path());
    file.append("output.txt");
    std::ofstream stream(file.native(), ios_base::out);

    numbers.resize(count);
    number = count;
    def(numbers.data(), numbers.size());

    stream << numbers << std::endl;
    return 0;
}
