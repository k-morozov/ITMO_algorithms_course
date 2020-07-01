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

void sort_insertion(vector<int>& vec, std::function<bool(int, int)> cmp = std::less<int>()) {
    std::size_t len = vec.size();
    for(std::size_t i=1; i<len; ++i) {
        int key = vec[i];
        int j = i-1;
        while (j>=0 && !cmp(vec[j], key)) {
            vec[j+1] = vec[j];
            j--;
        }
        vec[j+1] = key;
    }
}
int main() {
    std::vector<int> vec;
    generate(vec, 20);
    std::cout << vec << std::endl;
    sort_insertion(vec, [](int l, int r) {
        return l>r;
    });
    std::cout << vec << std::endl;
    sort_insertion(vec);
    std::cout << vec << std::endl;
}
