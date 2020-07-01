#include <iostream>
#include <cstdlib>
#include <vector>
#include <functional>

using namespace std;

void generate(vector<int>& vec, int len) {
  for(int i=0; i<len; ++i) {
    vec.emplace_back(std::rand()%100);
  }
}
template <typename T>
std::ostream& operator<<(ostream& ss, const std::vector<T>& vec) {
    for(const auto& v:vec) {
        ss << v << " ";
    }
    return ss;
}

void bubblesort(std::vector<int>& vec)
{
    for(std::size_t i = 0; i<vec.size(); ++i) {
        for(std::size_t j = vec.size()-1; j>i; --j) {
            if (vec[j-1]>vec[j]) std::swap(vec[j-1], vec[j]);
        }
    }

}
int main() {
    std::vector<int> vec;
    generate(vec, 10);
    std::cout << vec << std::endl;
    bubblesort(vec);
    std::cout << "sorted:\t " << vec << std::endl;
}
