#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
    size_t n, m, T;
    std::cin >> n;
    std::cin >> m;
    std::cin >> T;

    std::vector<int> orders_time;
    orders_time.resize(n);
    
    for (size_t i = 0; i < orders_time.size(); ++i)
    {
        std::cin >> orders_time[i];
    }

    std::sort(orders_time.begin(), orders_time.end(), [](int a, int b) {
        return a > b;
    });

    size_t counter;

    size_t tmax = 0, currm = 0;

    for (auto o: orders_time)
    {
        if (currm == 0)
        {
            tmax = o;
            ++currm;
        }
        else
        {
            if (tmax - o <= T && currm < m) 
            {
                ++currm;
            }
            else
            {
                currm = 1;
                tmax = o;
                ++counter;
            }
        }
        //std::cout << counter << ", " << currm << " - " << tmax << " - " << o << std::endl;
    }
    if (currm > 0)
        ++counter;

    std::cout << counter << std::endl;
}