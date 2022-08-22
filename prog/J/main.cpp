#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <queue>

typedef std::vector<bool> Desk;

typedef std::vector<size_t> DeskW;

constexpr size_t MULTIPLIER = 10000;

    // std::cout << "bfs " << states.size() << std::endl;
    // for (size_t i = 0; i < n; ++i)
    // {
        // for (size_t j = 0; j < m; ++j)
            // std::cout << (s.d[i * m + j]?'#':'.');
        // std::cout << std::endl;
    // }

struct Coord
{
    int x = 0, y = 0;

    bool operator==(const Coord& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator<(const Coord& other) const
    {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }
};

size_t n, m;

size_t shp(const Coord p, Desk& desk, DeskW& w)
{
    //std::cout << "shp (" << p.x << "," << p.y << ")" << std::endl;
    
    size_t thisw = desk[p.y * m + p.x]?MULTIPLIER:0;
    size_t minw = -1;

    if (p.x > 0)
    {
        Coord px{p.x - 1, p.y};
        size_t x = px.y * m + px.x;
        if (w[x] == -1)
           w[x] = shp(px, desk, w);
        if (w[x] + thisw < minw)
            minw = w[x] + thisw;
    }

    if (p.y > 0)
    {
        Coord py{p.x, p.y - 1};
        size_t y = py.y * m + py.x;
        if (w[y] == -1)
           w[y] = shp(py, desk, w);
        if (w[y] + thisw < minw)
            minw = w[y] + thisw;
    }

    if (p.x == 0 && p.y == 0)
        minw = thisw;

    return minw;
}


int main()
{
    std::cin >> n;
    std::cin >> m;

    Desk desk;
    desk.resize(n*m);
    DeskW w;
    w.resize(n*m);
    
    for (size_t i = 0; i < n; ++i)
    {
        //desk[i].resize(m);
        std::string s;
        std::cin >> s;
        for (size_t j = 0; j < m; ++j)
        {
            desk[i * m + j] = s[j] == '#';
            w[i * m + j] = -1;
        }
    }

    w[n * m - 1] = shp(Coord{m-1, n-1}, desk, w);

    // std::cout << std::endl;
    // for (size_t i = 0; i < n; ++i)
    // {
        // for (size_t j = 0; j < m; ++j)
            // std::cout << w[i * m + j] << " ";
        // std::cout << std::endl;
    // }

    std::cout << w[n * m - 1] / MULTIPLIER << std::endl;

    return 0;
}