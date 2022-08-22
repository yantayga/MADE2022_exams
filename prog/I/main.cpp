#include <iostream>
#include <vector>
#include <set>

typedef std::vector<std::vector<size_t>> Graph;

std::vector<std::set<size_t>> nreachable;

int d;

std::set<size_t>& update_reachable(const Graph& g, size_t i)
{
    // std::cout << "update_reachable " << i + 1 << " -> " << nreachable[i].size() << std::endl;

    std::set<size_t> visited;
    std::set<size_t> frontier;

    if (d > 0)
    {
        visited.insert(i);
        frontier.insert(i);
    }
    int l = 0;
    while(!frontier.empty() && l < d - 1)
    {
        auto it = frontier.begin();
        frontier.erase(it);
        //std::cout << "got " << *it << " from frontier " << l << std::endl;
        auto& v = g[*it];
        for (auto j: v)
        {
            if (visited.find(j) == visited.end())
            {
                visited.insert(j);
                frontier.insert(j);
            }
        }
        ++l;
    }
    
    nreachable[i] = visited;
  
    // std::cout << "update_reachable resulted " << i + 1 << " -> " << nreachable[i].size() << " for " << i + 1 << " -> (";
    // for (auto j: nreachable[i])
        // std::cout << j + 1 << ",";
    // std::cout << ")" << std::endl;
    return nreachable[i];
}

int main()
{
    size_t n, m;
    std::cin >> n;
    std::cin >> m;
    std::cin >> d;

    Graph g;
    
    g.resize(n);
    nreachable.resize(n);

    for (size_t i = 0; i < m; ++i)
    {
        size_t a, b;
        std::cin >> a;
        std::cin >> b;
        g[a - 1].push_back(b - 1);
        nreachable[a - 1].clear();
    }

    size_t sum = 0;
    for (size_t k = 0; k < g.size(); ++k)
    {
        // std::cout << "call " << k + 1 << std::endl;
        sum += update_reachable(g, k).size();
   }

    std::cout << sum << std::endl;
}