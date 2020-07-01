#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> prefix(const string &T)
{
    vector<int> res;
    res.push_back(0);
    for (int i = 1; i < T.length(); ++i)
    {
        int k = res[i - 1];
        while (k > 0 && T[i] != T[k])
        {
            k = res[k - 1];
        }
        if (T[i] == T[k])
        {
            ++k;
        }
        res.push_back(k);
    }
    return res;
}

vector<int> foo(const string &str, string &text)
{
    int str_len = str.length(), text_len = text.length();
    vector<int> res;
    vector<int> Prefix = prefix(str + "#" + text);

    for (int i = 0; i < text_len; ++i)
    {
        if (Prefix[str_len + i + 1] == str_len)
        {
            res.push_back(i - str_len + 2);
        }
    }
    return res;
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    string str, text;
    fin >> str >> text;
    vector<int> Res = foo(str, text);

    fout << Res.size() << endl;
    for (int i = 0; i < Res.size(); ++i)
    {
        fout << Res[i] << " ";
    }
    fout << endl;
    return 0;
}
