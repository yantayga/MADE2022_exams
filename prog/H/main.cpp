#include <iostream>
#include <vector>
#include <set>

typedef std::vector<std::vector<size_t>> Graph;

std::vector<size_t> comps;
std::vector<size_t> rev_comps;

void set_linked(const Graph& g, size_t i, int color)
{
    //std::cout << "set_linked " << i + 1 << " " << color + 1 << " -> " << comps[i] << std::endl;
    for (size_t j = 0; j < g[i].size(); ++j)
    {
        size_t b = g[i][j];
        if (comps[b] == -1)
        {
            comps[b] = color;
            set_linked(g, b, color);
        }
    }
}

int find_comp(const Graph& g, size_t i)
{
    //std::cout << "find_comp " << i + 1 << std::endl;
    if (comps[i] == -1)
    {
        comps[i] = i;
        set_linked(g, i, i);
    }

    return comps[i];
}

int main()
{
    size_t n, m;
    std::cin >> n;
    std::cin >> m;

    Graph g;
    
    g.resize(n);
    comps.resize(n);
    rev_comps.resize(n);

    for (size_t i = 0; i < m; ++i)
    {
        size_t a, b;
        std::cin >> a;
        std::cin >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }

    for (size_t i = 0; i < n; ++i)
        comps[i] = -1;

    size_t sum = 0;
    for (size_t k = 0; k < g.size(); ++k)
    {
        find_comp(g, k);
    }

    for (size_t k = 0; k < comps.size(); ++k)
    {
        rev_comps[comps[k]] += 1;
        //std::cout << "comps[" << k << "]=" <<  comps[k] << std::endl;
    }

    for (size_t k = 0; k < rev_comps.size(); ++k)
    {
        //std::cout << "rev_comps[" << k << "]=" <<  rev_comps[k] << std::endl;
        if (rev_comps[k] > 0)
            sum += rev_comps[k] * rev_comps[k];
    }

    std::cout << sum << std::endl;
}