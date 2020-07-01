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

std::vector<int> merge_sort(std::vector<int>& a, int shift = 1) {
    int len = a.size();
    if (len==1) return a;

    std::vector<int> l = {a.begin(), a.begin()+len/2};
    std::vector<int> r = {a.begin()+len/2, a.end()};

    l = merge_sort(l, shift);
    r = merge_sort(r, shift+(len)/2);

    auto res = merge(l,r);

    return res;
}
int main() {
    std::vector<int> vec_left;
    std::vector<int> vec_right;
    generate(vec_left, 10);
    std::cout << "left:\t" << vec_left << std::endl;
    generate(vec_right, 10);
    std::cout << "right:\t" << vec_right << std::endl;

    vec_left = merge_sort(vec_left);
    vec_right = merge_sort(vec_right);
    std::cout << "\nafter sorted:" << std::endl;
    std::cout << "left:\t" << vec_left << std::endl;
    std::cout << "right:\t" << vec_right << std::endl;

    std::cout << "\ntotal:" << std::endl;
    std::cout << "merge:\t " << merge( vec_left,vec_right) << std::endl;
}
