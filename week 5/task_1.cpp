#include <iostream>
#include <filesystem>
#include <fstream>
#include <stack>

bool check_heap(const std::vector<int>& heap)
{
    const std::size_t len = heap.size();
    bool flag = true;
    for(std::size_t i=1; i<=len && flag; ++i)
    {

        if (2*(i)-1<len)
        {
//            std::cout << heap[i] << " > " << heap[2*(i+1)] << std::endl;
            if (heap[i-1]>heap[2*(i)-1]) flag = false;
        }

        if (2*(i)<len)
        {
//            std::cout << heap[i] << " > " << heap[2*(i+1)+1] << std::endl;
            if (heap[i-1]>heap[2*(i)]) flag = false;
        }
    }
    return flag;
}
int main()
{
    std::filesystem::path file_in(std::filesystem::current_path());
    file_in.append("input.txt");
    std::ifstream in_stream(file_in.native(), std::ios_base::in);

    std::size_t Q;
    in_stream >> Q;
    int value;
    std::vector<int> heap;
    for(std::size_t i=0; i<Q; ++i)
    {
        in_stream >> value;
        heap.push_back(value);
    }

    bool flag = check_heap(heap);

    std::filesystem::path file_out(std::filesystem::current_path());
    file_out.append("output.txt");
    std::ofstream out_stream(file_out.native(), std::ios_base::out);
    out_stream << (flag ? "YES" : "NO");
//    std::cout << (flag ? "YES" : "NO") << std::endl;
    return 0;
}
