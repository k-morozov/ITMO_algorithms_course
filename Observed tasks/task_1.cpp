#include <iostream>
#include <fstream>
#include <filesystem>
#include <stack>

using namespace std;
using Type = int;

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& numbers) {
    for(const auto& a:numbers) {
        stream << a << endl;
    }
    return stream;
}
void outputs_result(int result)
{
    filesystem::path file_out(filesystem::current_path());
    file_out.append("output.txt");
    std::ofstream stream(file_out.native(), ios_base::out);
    stream << result << endl;
    cout << result << endl;
}

int main()
{
    std::vector<bool> data;

    std::size_t Q;

    filesystem::path file_in(filesystem::current_path());
    file_in.append("input.txt");

    std::ifstream stream(file_in.native(), ios_base::in);

    stream >> Q;
    char sym;

    std::stack<int> numbers;
    for(std::size_t i=0; i<Q; ++i)
    {
        stream >> sym;
        if (isdigit(sym))
        {
            int number = sym - '0';
            numbers.push(number);
        }
        else
        {
            int num1 = numbers.top();
            numbers.pop();
            int num2 = numbers.top();
            numbers.pop();
            int result;
            if (sym=='+')
            {
                result = num1 + num2;
//                cout << result << endl;
            }
            if (sym=='-')
            {
                result = num2 - num1;
//                cout << result << endl;
            }
            if (sym=='*')
            {
                result = num1 * num2;
//                cout << result << endl;
            }
            numbers.push(result);
        }
    }

    outputs_result(numbers.top());
    return 0;
}
