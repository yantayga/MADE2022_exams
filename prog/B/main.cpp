#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

struct RLEItem
{
    size_t _count;
    int _value;
};

void multiple_push_back(std::vector<RLEItem>& v, size_t n, int a, size_t k)
{
    auto p = std::lower_bound(v.begin(), v.end(), RLEItem{n, a}, 
        [](const RLEItem& a, const RLEItem& b) { return a._value < b._value; });

    // std::cout << "(" << n << "," << a << ") -> ";
    // if (p != v.end())
    // {
        // std::cout << "v[" << p - v.begin() << "]=(" << p->_count << "," << p->_value << ")" << std::endl;
    // }
    // else
    // {
        // std::cout << "end" << std::endl;
    // }
    if (p != v.end() && p->_value == a)
        p->_count += n;
    else
        v.insert(p, 1, RLEItem{n, a});
}

int main()
{
    size_t n, m, k;
    std::cin >> n;
    std::cin >> m;
    std::cin >> k;
    
    std::vector<RLEItem> vrle;
    vrle.resize(n);
    
    for (size_t i = 0; i < vrle.size(); ++i)
    {
        vrle[i]._count = 1;
        std::cin >> vrle[i]._value;
    }

    std::sort(vrle.begin(), vrle.end(), [](RLEItem& a, RLEItem& b) { return a._value < b._value; });

    for (size_t i = 0; i < m; ++i)
    {
        size_t n1;
        int a;
        std::cin >> n1;
        std::cin >> a;
        multiple_push_back(vrle, n1, a, k);
    }

    // std::cout << std::endl;
    // for (size_t i = 0; i < vrle.size(); ++i)
        // std::cout << "(" << vrle[i]._count << ":" << vrle[i]._value << "),";
    // std::cout << std::endl;

    size_t len = 1;
    for (size_t i = 0; i < vrle.size(); ++i)
    {
        len += vrle[i]._count;
        //std::cout << vrle[i]._count << ", " << len << ", " << k << std::endl;
        if (len > k)
        {
            std::cout << vrle[i]._value << std::endl;
            break;
        }
    }

    return 0;
}