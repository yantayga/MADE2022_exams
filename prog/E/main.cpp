#include <iostream>
#include <vector>
#include <map>
#include <string>

struct Card
{
    union {
        struct {
            char _bounds;
            char _color;
            char _form;
            char _size;
        };
        size_t num;
    };
};

bool triple_equal_or_alldiffers(char a1, char a2, char a3)
{
    return (a1 == a2 && a1 == a3 && a2 == a3) || (a1 != a2 && a1 != a3 && a2 != a3);
}

int main()
{
    size_t m;
    std::cin >> m;

    std::vector<Card> v;
    v.resize(m);

    std::map<size_t, size_t> mv;
    
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
        mv[v[i].num]++;
    }
    
    // std::vector<int> res;
    // res.resize(m, 0);
    // for (size_t i = 0; i < v.size(); ++i)
    // {
        // for (size_t j = i + 1; j < v.size(); ++j)
        // {
            // for (size_t k = j + 1; k < v.size(); ++k)
            // {
                // if (triple_equal_or_alldiffers(v[i]._bounds, v[j]._bounds, v[k]._bounds) &&
                    // triple_equal_or_alldiffers(v[i]._color, v[j]._color, v[k]._color) &&
                    // triple_equal_or_alldiffers(v[i]._form, v[j]._form, v[k]._form) &&
                    // triple_equal_or_alldiffers(v[i]._size, v[j]._size, v[k]._size))
                // {
                    // //std::cout << "found " << i << " " << j << " " << k << std::endl;
                    // res[i]++;
                    // res[j]++;
                    // res[k]++;
                // }
            // }
        // }
    // }

    // for (size_t i = 0; i < v.size(); ++i)
        // std::cout << res[i] << std::endl;

    std::map<size_t, size_t> mres;

    for (auto i = mv.begin(); i != mv.end(); ++i)
    {
        mres[i->first] = 0;
    }

    for (auto i = mv.begin(); i != mv.end(); ++i)
    {
        if (i->second > 2)
            mres[i->first] += (i->second - 1) * (i->second - 2) / 2;

        Card ci;
        ci.num = i->first;
 
        //std::cout << "(" << int(ci._bounds) << "," << int(ci._color)  << ","  << int(ci._form)  << "," << int(ci._size) << ") " << "=" << i->second << std::endl;

        for (auto j = std::next(i); j != mv.end(); ++j)
        {
            Card cj;
            cj.num = j->first;
            
            for (auto k = std::next(j); k != mv.end(); ++k)
            {
                Card ck;
                ck.num = k->first;

                if (triple_equal_or_alldiffers(ci._bounds, cj._bounds, ck._bounds) &&
                    triple_equal_or_alldiffers(ci._color, cj._color, ck._color) &&
                    triple_equal_or_alldiffers(ci._form, cj._form, ck._form) &&
                    triple_equal_or_alldiffers(ci._size, cj._size, ck._size))
                {
                    mres[i->first] += j->second * k->second;
                    mres[j->first] += i->second * k->second;
                    mres[k->first] += i->second * j->second;
                }
            }
        }
    }

    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << mres[v[i].num] << std::endl;
    }
}