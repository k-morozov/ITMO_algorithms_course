#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <deque>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <iterator>

using namespace std;
using Type = int;

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& numbers) {
    for(const auto& a:numbers) {
        stream << a << endl;
    }
    return stream;
}

void outputs_result(double result)
{
    filesystem::path file_out(filesystem::current_path());
    file_out.append("output.txt");
    std::ofstream stream(file_out.native(), ios_base::out);

    stream.precision(9);
    stream << fixed << result;
}



double foo(int n, std::vector<double>& h)
{
    double l = 0, r = h[0];
    while (r - l > 0.0000000001) {
        h[1] = (l + r) / 2;
        bool Up = true;
        for (int i = 2; i < n; i++) {
            h[i] = 2 * h[i - 1] - h[i - 2] + 2;
            if (h[i] < 0) {
                Up = false;
                break;
            }
        }
        if (Up) {
            r = h[1];
        }
        else {
            l = h[1];
        }
    }
    return h[n - 1];

}

int main()
{
    filesystem::path file_in(filesystem::current_path());
    file_in.append("input.txt");

    std::ifstream stream(file_in.native(), ios_base::in);

    int n;
    std::vector<double> h;

    stream >> n;
    h.resize(n);
    stream >> h[0];

    outputs_result(foo(n, h));
// ***********************************************************************************************
    return 0;
}
