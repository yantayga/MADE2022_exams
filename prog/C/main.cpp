#include <iostream>
#include <vector>
#include <algorithm>

struct Pair
{
    size_t n = 0, k = 0;
};

__uint64_t c(size_t n, size_t k)
{
    size_t res = 1;
    for (size_t i = n - k + 1; i <= n; ++i)
    {
        res *= i;
    }
    for (size_t i = 1; i <= k; ++i)
    {
        res /= i;
    }
    return res;
}

int main()
{
    size_t m;
    std::cin >> m;

    std::vector<size_t> v;
    v.resize(m);
    
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cin >> v[i];
    }

    std::sort(v.begin(), v.end(), [](int a, int b) {return a > b;});

    for (size_t i = 0; i < v.size(); ++i)
    {
        size_t most_central = i;
        __int64_t dmin = v[i];
        for (size_t j = i; j < v.size(); ++j)
        {
            __int64_t d = v[i] - 2 * v[j];
            if (d < 0)
                d = -d;
            if (d < dmin || (d == dmin && v[j] > v[most_central]))
            {
                dmin = d;
                most_central = j;
            }
            //std::cout << "n=" << v[i] << ", k=" << v[j] << ", d=" << d << std::endl;
        }
        __uint64_t cc = c(v[i], v[most_central]);
        std::cout << "n=" << v[i] << ", k=" << v[most_central] << ", cc=" << cc << std::endl;
        //std::cout << v[i] << " " << v[most_central] << std::endl;
        //break;
    }

    // std::vector<Pair> ps;
    // ps.resize(m*(m + 1) / 2);
    // size_t k = 0;

    // std::sort(ps.begin(), ps.end(), [](const Pair& a, const Pair& b) {
        // if (a.n == b.n)
            // return (a.n - a.k / 2) > (b.n - b.k / 2);
        // return a.n > b.n;
    // });
    // for (size_t i = 0; i < ps.size(); ++i)
        // std::cout << "n=" << ps[i].n << ", k=" << ps[i].k << ", c(x,y)=" << c(ps[i].n, ps[i].k) << std::endl;

    //size_t fx = v[0], fy = v[0], maxc = 0;

    // for (size_t i = 0; i < v.size(); ++i)
    // {
        // for (size_t j = i; j < v.size(); ++j)
        // {
            // size_t res = c(v[i], v[j]);
            // if (res > maxc)
            // {
                // maxc = res;
                // fx = v[i];
                // fy = v[j];
            // }
            // std::cout << "n=" << v[i] << ", k=" << v[j] << ", c(x,y)=" << res << std::endl;
        // }
    // }
    // std::cout << fx << " " << fy << std::endl;
}