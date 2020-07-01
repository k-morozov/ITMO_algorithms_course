#include <fstream>
#include <vector>
#include <iostream>
#include <array>
#include <list>
#include <forward_list>
#include <algorithm>
#include <deque>

struct Node
{
    Node(const std::string a_key, const std::string& a_value = "") : key(a_key), value(a_value) {}
    
    const std::string key;
    std::string value;

    Node* prev = nullptr;
    Node* next = nullptr;

    bool operator==(const Node& r) { return this->key == r.key; }
    bool operator==(const Node& r) const { return this->key == r.key; }
};


class Hash_table
{
public:
    Hash_table() = default;

    void put(const Node& value)
    {
        int buck = shash(value.key) % num_bucket;
        auto& ar = data[buck];
        auto it = std::find(ar.begin(), ar.end(), value.key);
        if (it == ar.end())
        {
            ar.push_front(value);
            if (last_node!=nullptr) last_node->next = &ar.front();
            ar.front().prev = last_node;
            last_node = &ar.front();
        }
        else it->value = value.value;
    }
    const std::string& get(const std::string& key) const
    {
        int buck = shash(key) % num_bucket;
        auto& ar = data[buck];
        auto it = std::find(ar.begin(), ar.end(), key);
        return (it!=ar.end()) ? it->value : none;
    }
    void del(const std::string& key)
    {
        int buck = shash(key) % num_bucket;
        auto& ar = data[buck];
        auto it = std::find(ar.begin(), ar.end(), key);
        if (it != ar.end())
        {
            Node* prev_node = it->prev;
            Node* next_node = it->next;

            if (it->key == last_node->key) last_node = prev_node;

            if (prev_node != nullptr && next_node != nullptr)
            {
                prev_node->next = next_node;
                next_node->prev = prev_node;
            }
            else
            {
                if (prev_node != nullptr && next_node == nullptr)
                {
                    prev_node->next = nullptr;
                }
                if (prev_node == nullptr && next_node != nullptr)
                {
                    next_node->prev = nullptr;
                }
            }

            ar.remove(Node(key, std::string()));
        }
    }
    const std::string& next(const std::string& key) const
    {
        const int buck = shash(key) % num_bucket;
        const auto& ar = data[buck];
        auto it = std::find(ar.begin(), ar.end(), key);
        if (it==ar.end()) return none;

        return (it->next!=nullptr) ? it->next->value : none;
    }
    const std::string& prev(const std::string& key) const
    {
        const int buck = shash(key) % num_bucket;
        const auto& ar = data[buck];
        auto it = std::find(ar.begin(), ar.end(), key);
        if (it==ar.end()) return none;

        return (it->prev!=nullptr) ? it->prev->value : none;
    }
private:
    static constexpr std::size_t num_bucket = 55001;
    std::hash<std::string> shash;
    std::array<std::list<Node>, num_bucket> data;

    const std::string none = "<none>";
    Node* last_node = nullptr;
};

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int n;
    in >> n;
    Hash_table hash_table;
    std::string command, key, value;
    for(int i=0; i<n; ++i)
    {
        in >> command;
        if (command=="get")
        {
            in >> key;
            out << hash_table.get(key) << std::endl;
        }
        if (command=="put")
        {
            in >> key >> value;
            hash_table.put(Node(key, value));
        }
        if (command=="delete")
        {
            in >> key;
            hash_table.del(key);
        }
        if (command=="next")
        {
            in >> key;
            out << hash_table.next(key) << std::endl;
        }
        if (command=="prev")
        {
            in >> key;
            out << hash_table.prev(key) << std::endl;
        }
    }
}
