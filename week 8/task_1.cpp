#include <fstream>
#include <vector>
#include <iostream>
#include <array>
#include <list>
#include <algorithm>

template <typename T>
class Hash_table
{
public:
    Hash_table() = default;
    void add(T number)
    {
        auto& ar = data[number%num_bucket];
        auto it = std::find(ar.begin(), ar.end(), number);
        if (it == ar.end()) ar.push_front(number);
    }
    bool find(T number) const
    {
        const auto& ar = data[number%num_bucket];
        return std::find(ar.begin(), ar.end(), number)!=ar.end();
    }
    void del(T number)
    {
        const auto pos = number%num_bucket;
        auto& ar = data[pos];
        ar.remove(number);
    }
private:
    static constexpr std::size_t num_bucket = 3413;
    std::array<std::list<T>, num_bucket> data;
};

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t n;
    in >> n;
    Hash_table<long long> hash_table;
    char command;
    long long value;
    for(int i=0; i<n; ++i)
    {
        in >> command;
        in >> value;
        if (command=='A')
        {
            hash_table.add(value);
        }
        if (command=='D')
        {
            hash_table.del(value);
        }
        if (command=='?')
        {
            out << (hash_table.find(value) ? "Y" : "N") << std::endl;
        }
    }
}
