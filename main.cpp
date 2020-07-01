#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& numbers) {
    for(const auto& a:numbers) {
        stream << a << " ";
    }
    return stream;
}

void init_filesystem() {
    filesystem::path file_input(filesystem::current_path());
    file_input.append("input.txt");
    {
        std::ofstream file(file_input.native());
        file << "1 2 3 4 5 6 7" << std::endl;
    }

    {
        std::ifstream file(file_input.native(), ios_base::in);
        string s;
        while (file >> s) {
            cout << "read = " << s << endl;
        }

    }
    file_input.replace_filename("output.txt");
    {
        std::ofstream file(file_input.native());
        file << "test output" << std::endl;
    }
}

void init_rand(std::vector<int> &numbers, int size) {
    for(int i=0; i<size; ++i) {
        numbers.emplace_back(std::rand()%100);
    }
}


int main()
{
    vector<int> numbers;
    init_rand(numbers, 10);
    std::cout << numbers << std::endl;

    for(int j=1; j<10; ++j) {
        int i = j -1;
        while (i>=0 && numbers[i]>numbers[i+1]) {
            std::swap(numbers[i],numbers[i+1]);
            --i;
        }
    }

    std::cout << numbers << std::endl;
    return 0;
}
