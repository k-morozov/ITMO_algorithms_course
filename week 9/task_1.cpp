#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

int main()
{
    ifstream in("input.txt");
    std::string base, str;
    in >> base >> str;

    std::vector<int> res;

    for(std::size_t i=0; i<str.size(); ++i)
    {
        if (strncmp(base.data(), str.data()+i, base.size())==0)
        {
            res.push_back(i+1);
        }
    }
    ofstream out("output.txt");
    out << res.size() << endl;
    for(const auto& a:res)
    {
        out << a << " ";
    }
    out << endl;
    return 0;
}
