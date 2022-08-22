#include <iostream>
#include <vector>
#include <algorithm>

void multiple_push_back(std::vector<int>& v, size_t n, int a, size_t k)
{
    auto is_greater = [a](int i)
        {
            //std::cout << i << " > " << a << std::endl;
            return i > a;
        };

    auto p = std::find_if(v.begin(), v.end(), is_greater);

    if (p - v.begin() <= k)
        v.insert(p, n, a);
}

int main()
{
    size_t n, m, k;
    std::cin >> n;
    std::cin >> m;
    std::cin >> k;
    
    std::vector<int> vinit;
    vinit.resize(n);
    for (size_t i = 0; i < vinit.size(); ++i)
        std::cin >> vinit[i];

    std::sort(vinit.begin(), vinit.end());

    for (size_t i = 0; i < m; ++i)
    {
        size_t n1;
        int a;
        std::cin >> n1;
        std::cin >> a;
        multiple_push_back(vinit, n1, a, k);
    }

    // std::cout << std::endl;
    // for (size_t i = 0; i < vinit.size(); ++i)
        // std::cout << vinit[i] << ',';
    // std::cout << std::endl;
    
    std::cout << vinit[k - 1] << std::endl;

    return 0;
}