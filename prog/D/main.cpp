#include <iostream>
#include <vector>
#include <string>

struct Card
{
    int _bounds;
    int _color;
    int _form;
    int _size;
};

bool triple_equal_or_alldiffers(int a1, int a2, int a3)
{
    return (a1 == a2 && a1 == a3 && a2 == a3) || (a1 != a2 && a1 != a3 && a2 != a3);
}

int main()
{
    size_t m;
    std::cin >> m;

    std::vector<Card> v;
    v.resize(m);
    
    std::string s;
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cin >> s;
        switch (s[0])
        {
            case '\\': v[i]._bounds = 0; break;
            case '|': v[i]._bounds = 1; break;
            case '/': v[i]._bounds = 2; break;
        }
        if (s[1] == '0')
        {
            v[i]._color = 10;
            v[i]._form = 0;
        }
        else if (s[1] >= '1' && s[1] <= '3')
        {
            v[i]._color = s[1] - '1';
            v[i]._form = 0;
        }
        else if (s[1] >= 'a' && s[1] <= 'z')
        {
            v[i]._color = s[1] - 'a';
            v[i]._form = 1;
        }
        else if (s[1] >= 'A' && s[1] <= 'Z')
        {
            v[i]._color = s[1] - 'A';
            v[i]._form = 2;
        }
        v[i]._size = s.length() - 3;
        //std::cout << "(" << v[i]._bounds << "," << v[i]._color  << "," << v[i]._size << ") " << s << std::endl;
    }
    
    std::vector<int> res;
    res.resize(m, 0);
    for (size_t i = 0; i < v.size(); ++i)
    {
        for (size_t j = i + 1; j < v.size(); ++j)
        {
            for (size_t k = j + 1; k < v.size(); ++k)
            {
                if (triple_equal_or_alldiffers(v[i]._bounds, v[j]._bounds, v[k]._bounds) &&
                    triple_equal_or_alldiffers(v[i]._color, v[j]._color, v[k]._color) &&
                    triple_equal_or_alldiffers(v[i]._form, v[j]._form, v[k]._form) &&
                    triple_equal_or_alldiffers(v[i]._size, v[j]._size, v[k]._size))
                {
                    res[i]++;
                    res[j]++;
                    res[k]++;
                }
            }
        }
    }

    for (size_t i = 0; i < v.size(); ++i)
        std::cout << res[i] << std::endl;
}