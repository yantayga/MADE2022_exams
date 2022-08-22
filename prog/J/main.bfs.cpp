#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <queue>

typedef std::vector<bool> Desk;

#pragma pack(1)
struct Coord
{
    char x = 0, y = 0;

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
Coord target;

bool wave_from(const Coord p, Desk& desk, std::vector<Coord>& frontier)
{
//    std::cout << "wave from (" << p.x << "," << p.y << ")" << " to (" << target.x << "," << target.y << ")" << std::endl;
    if (p == target)
        return true;
    
    if (p.x < m - 1)
    {
        Coord px{p.x + 1, p.y};
        if (desk[px.y * m + px.x])
            frontier.emplace_back(px);
        else if (wave_from(px, desk, frontier))
            return true;
    }

    if (p.y < n - 1)
    {
        Coord py{p.x, p.y + 1};
        if (desk[py.y * m + py.x])
            frontier.emplace_back(py);
        else if (wave_from(py, desk, frontier))
            return true;
    }

    return false;
}

#pragma pack(1)
struct State
{
    Desk d;
    Coord removed_at;
    char ns_of_removed = 0;
};

int bfs(std::queue<State>& states)
{
    State s = states.front();
    states.pop();

    // std::cout << "bfs " << states.size() << std::endl;
    // for (size_t i = 0; i < n; ++i)
    // {
        // for (size_t j = 0; j < m; ++j)
            // std::cout << (s.d[i * m + j]?'#':'.');
        // std::cout << std::endl;
    // }

    std::vector<Coord> frontier;
    while (!wave_from(s.removed_at, s.d, frontier))
    {
        for (auto& c: frontier)
        {
            //std::cout << "remove at (" << c.x << "," << c.y << ")" << std::endl;

            State s1{s.d, c, s.ns_of_removed + 1};
            s1.d[c.y * m + c.x] = false;
            states.emplace(s1);
        }

        frontier.clear();
        s = states.front();
        states.pop();
    }

    return s.ns_of_removed;
}

int main()
{
    std::cin >> n;
    std::cin >> m;

    target = Coord{m-1, n-1};

    Desk desk;
    desk.resize(n*m);
    
    for (size_t i = 0; i < n; ++i)
    {
        //desk[i].resize(m);
        std::string s;
        std::cin >> s;
        for (size_t j = 0; j < m; ++j)
            desk[i * m + j] = s[j] == '#';
    }

    std::queue<State> q;
    q.emplace(State{desk, Coord{0, 0}, 0});
    size_t res = bfs(q);
    if (desk[0 * m + 0])
        ++res;
    std::cout << res << std::endl;

    return 0;
}