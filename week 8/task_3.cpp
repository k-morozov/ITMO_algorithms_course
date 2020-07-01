#include <fstream>
#include <vector>
#include <iostream>
#include <array>
#include <list>
#include <algorithm>

using Type = uint64_t;

constexpr Type k3 = 1'000;
constexpr Type k15 = 1'000'000'000'000'000;

template <typename T>
class Hash_table
{
public:
    Hash_table()
    {
        data.resize(num_bucket);
    }
    void add(T number)
    {
        auto& ar = data[number%num_bucket];
        ar.push_back(number);
    }
    bool find(T number) const
    {
        const auto& ar = data[number%num_bucket];
        return std::find(ar.begin(), ar.end(), number)!=ar.end();
    }
private:
    static constexpr std::size_t num_bucket = 994997;
    std::vector<std::vector<T>> data;
};

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    Type N,X,A,B;
    Type Ac, Bc, Ad, Bd;

    fin >> N >> X >> A >> B >> Ac >> Bc >> Ad >> Bd;

    Hash_table<Type> hash_table;

    for(Type i=0; i<N; ++i)
    {
        if (hash_table.find(X))
        {
            A = (A + Ac) % k3;
            B = (B + Bc) % k15;
        }
        else
        {
            hash_table.add(X);
            A = (A + Ad) % k3;
            B = (B + Bd) % k15;
        }
        X = (X * A + B)%k15;
    }

//    std::cout << X << " " << A << " " << B ;
    fout << X << " " << A << " " << B ;
}
