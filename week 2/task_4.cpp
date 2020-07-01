#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <algorithm>

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


void quick_sort(int32_t v[], int32_t n) {
    if (n<=1) return;

    int32_t last = rand()%n;
    std::nth_element(&v[0], &v[last], &v[n]);

    quick_sort(v, last);
    quick_sort(v + last +1, n-last-1);
}


void k_sort(int32_t v[], int32_t n, int32_t k1, int32_t k2) {

    std::nth_element(&v[0], &v[k1-1], &v[n]);
    std::nth_element(&v[k1-1], &v[k2-1], &v[n]);

    quick_sort(v +k1-1,  k2-k1);
}

int main()
{
    std::vector<int32_t> numbers;
    filesystem::path file_in(filesystem::current_path());
    file_in.append("input.txt");

    std::ifstream stream(file_in.native(), ios_base::in);

    int32_t size_array;
    stream >> size_array;

    int32_t k1,k2;
    stream >> k1 >> k2;

    int32_t A, B, C, a1, a2;
    stream >> A >> B >> C >> a1 >> a2;

    numbers.push_back(a1);
    numbers.push_back(a2);
    for(int i=2; i<size_array; ++i) {
        numbers.emplace_back(A*numbers[i-2]+B*numbers[i-1]+C);
    }

//    std::nth_element(numbers.begin(), numbers.begin()+k1-1, numbers.end());
//    std::nth_element(numbers.begin()+k1, numbers.begin()+k2-1, numbers.end());

    k_sort(numbers.data(), size_array, k1, k2);

    std::vector<int32_t> result {std::make_move_iterator(numbers.begin()+k1-1),
                                std::make_move_iterator(numbers.begin()+k2)
                            };
    {
        filesystem::path file_out(filesystem::current_path());
        file_out.append("output.txt");
        std::ofstream stream(file_out.native(), ios_base::out);

        stream << result << std::endl;
//        cout << result << std::endl;
    }

    return 0;
}
