#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <array>
#include <string>

using namespace std;
using Type = int;

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& numbers) {
    for(const auto& a:numbers) {
        stream << a << endl;
    }
    return stream;
}
void outputs_result(const std::vector<int>& seq)
{
    filesystem::path file_out(filesystem::current_path());
    file_out.append("output.txt");
    std::ofstream stream(file_out.native(), ios_base::out);

    stream << seq;
//    cout << seq;
}

int main()
{
    std::vector<int> working_data;
    std::vector<int> delete_data;
    std::size_t Q;
    {
        filesystem::path file_in(filesystem::current_path());
        file_in.append("input.txt");

        std::ifstream stream(file_in.native(), ios_base::in);

        filesystem::path file(filesystem::current_path());
        file.append("input.txt");
        {
            std::ifstream stream(file.native(), ios_base::in);
            stream >> Q;

            char action;
            int value;
            for(std::size_t i=0; i<Q; ++i) {
                stream >> action;
                if (action == '+')
                {
                    stream >> value;
                    working_data.push_back(value);
                }
                else
                {
                    delete_data.push_back(working_data.back());
                    working_data.pop_back();
                }
            }

        }

    }


    outputs_result(delete_data);
    return 0;
}
