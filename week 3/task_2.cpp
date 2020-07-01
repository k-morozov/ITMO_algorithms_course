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
        stream << a << " ";
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


void radix_sort(std::vector<std::string>& random_array, int digit) {
    std::vector<std::string> sortedArray(random_array.size());
    static std::array<Type, 26> countsArray;
    std::vector<int> position_word(random_array.size());
    for(std::size_t i = 0; i<random_array.size(); ++i)
    {
        position_word[i] = i+1;
    }

    int counter = 0;
    for(int k=random_array[0].size()-1; k>=0 && counter <digit; k--, counter++) {
        countsArray.fill(0);

        for(const auto& word : random_array)
        {
            std::size_t countIndex = word.at(k) - 97;
            ++countsArray[countIndex];
        }

        Type prevCounter = 0;
        for (std::size_t i = 1; i < countsArray.size(); i++)
        {
            if (countsArray[i] > 0)
            {
                countsArray[i] +=  countsArray[prevCounter];
                prevCounter = i;
            }
        }

        for (int i = random_array.size() - 1; i >= 0; i--)
        {
            Type countIndex = random_array[i].at(k) - 97;
            sortedArray[--countsArray[countIndex]] = random_array[i];
        }
        random_array = sortedArray;
    }

    cout << position_word << endl;
}

std::vector<int> CountSort(const std::string& array, std::vector<int> seq, std::vector<int> resultArray)
{
    constexpr int k = 26;
    static std::array<int,k> countsArray;
    countsArray.fill(0);

    for (std::size_t i = 0; i < array.size(); i++)
    {
        countsArray[array[i] - 97]++;
    }

    for (std::size_t y = 1; y < countsArray.size(); y++)
    {
        countsArray[y] = countsArray[y] + countsArray[y - 1];
    }

    for (int t = seq.size() - 1; t > -1; t--)
    {
        int index_letter = array[seq[t] - 1] - 97;
        int counts_letter = countsArray[index_letter]-1;
        resultArray[counts_letter] = seq[t];
        countsArray[index_letter]--;
    }
    seq = resultArray;
    return seq;
}

int main()
{
    std::vector<std::string> not_sorted_array;
    std::size_t n,m,k;
    {
        filesystem::path file_in(filesystem::current_path());
        file_in.append("input.txt");

        std::ifstream stream(file_in.native(), ios_base::in);

        filesystem::path file(filesystem::current_path());
        file.append("input.txt");
        {
            std::ifstream stream(file.native(), ios_base::in);
            stream >> n;
            stream >> m;
            stream >> k;
            std::string value;
            for(std::size_t i=0; i<m; ++i) {
                stream >> value;
                not_sorted_array.emplace_back(value);
            }

        }

    }
    //radix_sort(not_sorted_array, k);
    std::vector<int> seq (n);
    for (std::size_t i = 0; i < n; i++)
    {
        seq[i] = i + 1;
    }
    std::vector<int> resultArray (n);

    for (int i = m-1; i >=0 && k > 0; i--, k--)
    {
        seq = CountSort(not_sorted_array[i], seq, resultArray);
    }

    outputs_result(seq);
    return 0;
}
