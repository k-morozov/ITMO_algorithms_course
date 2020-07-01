#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

int main()
{
    filesystem::path file(filesystem::current_path());
    file.append("input.txt");
    int summa = 0;
    {
        std::ifstream stream(file.native(), ios_base::in);
        int num;
        while (stream >> num) {
            summa += num;
        }
    }
    {
        file.replace_filename("output.txt");
        std::ofstream stream(file.native(), ios_base::out);
        stream << summa << endl;
    }
    return 0;
}
