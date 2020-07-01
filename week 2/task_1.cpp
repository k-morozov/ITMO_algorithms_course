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

std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> result;
    result.resize(left.size()+right.size());

    int pos_left = 0;
    int pos_right = 0;
    int left_len = left.size();
    int right_len = right.size();
    int pos_res = 0;

    while(pos_left<left_len || pos_right<right_len) {

        if (pos_right == right_len || (pos_left<left_len && left[pos_left]<=right[pos_right])) {
            result[pos_res] = left[pos_left];
            pos_left++;
        } else {
            result[pos_res] = right[pos_right];
            pos_right++;
        }
        pos_res++;
    }

    return result;
}

std::vector<int> merge_sort(std::vector<int>& a, std::ofstream& stream,  int shift = 1) {
    int len = a.size();
    if (len==1) return a;

    std::vector<int> l = {a.begin(), a.begin()+len/2};
    std::vector<int> r = {a.begin()+len/2, a.end()};

    l = merge_sort(l,stream, shift);
    r = merge_sort(r,stream, shift+(len)/2);

    auto res = merge(l,r);

    stream << shift << " " << shift+(len)-1 << " ";
    stream << *(res.begin()) << " " << *prev(res.end()) << endl;

    return res;
}

int main()
{
    std::vector<Type> numbers;
    read_input(numbers);
    //cout << numbers << endl;
    filesystem::path file(filesystem::current_path());
    file.append("output.txt");
    std::ofstream stream(file.native(), ios_base::out);

    numbers = merge_sort(numbers, stream);
    stream << numbers << std::endl;

    return 0;
}
