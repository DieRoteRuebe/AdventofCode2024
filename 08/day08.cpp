#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>

int _gcd(int a, int b)
{
    int res = std::min(a, b);


    while (res > 1)
    {
        if (a % res == 0 && b % res == 0)
            break;
        res--;
    }
    return res;
}

int generateCombinationsPart1(const std::vector<std::pair<int, int>>& vec, int& boundaryY, int& boundaryX, std::set<std::pair<int, int>>& anodes)
{
    int result = 0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::pair<int, int> p1 = vec[i];
        std::pair<int, int> p2;
        for (size_t y = i + 1; y < vec.size(); y++)
        {
            p2 = vec[y];
            int newpY = p2.first + (p2.first - p1.first);
            int newpX = p2.second + (p2.second - p1.second);
            if (newpY > -1 && newpY < boundaryY && newpX > -1 && newpX < boundaryX && anodes.find({ newpX, newpY }) == anodes.end())
            {
                anodes.insert({ newpX, newpY });
                result++;
                std::cout << "Steigung: " << p1.first << "->" << p1.second << " : " << p2.first << "->" << p2.second << " Steig: " << p2.first - p1.first << "->" << p2.second - p1.second << " newpos: " << p2.first + (p2.first - p1.first) << "->" << p2.second + (p2.second - p1.second) << "\n";
                std::cout << "possible Position!" << "\n";
            }
        }
        for (size_t y = 0; y < i; y++)
        {
            p2 = vec[y];
            int newpY = p2.first + (p2.first - p1.first);
            int newpX = p2.second + (p2.second - p1.second);
            if (newpY > -1 && newpY < boundaryY && newpX > -1 && newpX < boundaryX && anodes.find({ newpX, newpY }) == anodes.end())
            {
                anodes.insert({ newpX, newpY });
                result++;
                std::cout << "Steigung: " << p1.first << "->" << p1.second << " : " << p2.first << "->" << p2.second << " Steig: " << p2.first - p1.first << "->" << p2.second - p1.second << " newpos: " << p2.first + (p2.first - p1.first) << "->" << p2.second + (p2.second - p1.second) << "\n";
                std::cout << "possible Position!" << "\n";
            }
        }
    }
    return result;
}

int generateCombinationsPart2(const std::vector<std::pair<int, int>>& vec, int& boundaryY, int& boundaryX, std::set<std::pair<int, int>>& anodes)
{
    int result = 0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::pair<int, int> p1 = vec[i];
        std::pair<int, int> p2;
        for (size_t y = i + 1; y < vec.size(); y++)
        {
            p2 = vec[y];

            int dx = p2.second - p1.second;
            int dy = p2.first - p1.first;
            int gcd = _gcd(std::abs(dx), std::abs(dy)); // Greatest Common Divisor
            dx /= gcd;
            dy /= gcd;

            int newX = p2.second + dx;
            int newY = p2.first + dy;
            while (newY > -1 && newY < boundaryY && newX > -1 && newX < boundaryX)
            {
                if (anodes.find({ newX, newY }) == anodes.end())
                {
                    anodes.insert({ newX, newY });
                    result++;
                    std::cout << "Steigung: " << p1.first << "->" << p1.second << " : " << p2.first << "->" << p2.second << " Steig: " << p2.first - p1.first << "->" << p2.second - p1.second << " newpos: " << p2.first + (p2.first - p1.first) << "->" << p2.second + (p2.second - p1.second) << "\n";
                    std::cout << "possible Position!" << "\n";
                }
                newX += dx;
                newY += dy;
            }
            
            newX = p1.second - dx;
            newY = p1.first - dy;
            while (newX >= 0 && newX < boundaryX && newY >= 0 && newY < boundaryY)
            {
                if (anodes.find({ newX, newY }) == anodes.end())
                {
                    anodes.insert({ newX, newY });
                    result++;
                    std::cout << "Steigung: " << p1.first << "->" << p1.second << " : " << p2.first << "->" << p2.second << " Steig: " << p2.first - p1.first << "->" << p2.second - p1.second << " newpos: " << p2.first + (p2.first - p1.first) << "->" << p2.second + (p2.second - p1.second) << "\n";
                    std::cout << "possible Position!" << "\n";
                }
                newX -= dx;
                newY -= dy;
            }
        }
        if (anodes.find({ p1.second, p1.first }) == anodes.end()) 
        {
            anodes.insert({ p1.second, p1.first });
            result++;
        }
    }
    return result;
}


int generateMissingAnodes(std::map<char, std::vector<std::pair<int, int>>>& mp, std::set<std::pair<int, int>>& anodes)
{
    int res = 0;
    std::map<char, std::vector<std::pair<int, int>>>::iterator it;
    for (it = mp.begin(); it != mp.end(); it++)
    {
        for (const std::pair<int, int>& p : it->second)
        {
            //Damn i somehow messed up the x, y orientation in anodes set...........
            if (anodes.find({ p.second,p.first }) == anodes.end() && it->second.size() > 1)
            {
                std::cout << "new Anode: " << it->first << "position: " << p.first << "->" << p.second << "\n";
                anodes.insert({ p.second,p.first });
                res++;
            }
        }

    }

    return res;
}

void print(std::map<char, std::vector<std::pair<int, int>>>& mp, std::set<std::pair<int, int>>& anodes, int& boundaryY, int& boundaryX)
{
    std::vector<std::vector<char>> print;
    for (int y = 0; y < boundaryY; y++)
    {
        std::vector<char> temp;
        for (int x = 0; x < boundaryX; x++)
        {
            temp.push_back('.');
        }
        print.push_back(temp);
    }
    std::map<char, std::vector<std::pair<int, int>>>::iterator it;
    for (it = mp.begin(); it != mp.end(); it++)
    {
        for (const std::pair<int, int>& p : it->second)
        {
            int x = p.first;
            int y = p.second;

            print[y][x] = it->first;
        }
    }
    for (auto i = anodes.begin(); i != anodes.end(); i++)
    {
        print[i->first][i->second] = '#';
    }



    for (const std::vector<char>& v : print)
    {
        for (const char& chr : v)
        {
            std::cout << chr;
        }
        std::cout << "\n";
    }
}

int calculated_distancePart1(std::map<char, std::vector<std::pair<int, int>>>& mp, int& boundaryY, int& boundaryX)
{
    int result = 0;
    std::set<std::pair<int, int>> anodes;
    std::map<char, std::vector<std::pair<int, int>>>::iterator it;
    for (it = mp.begin(); it != mp.end(); it++)
    {
        std::cout << it->first << ":" << "\n";
        for (const auto& p : it->second)
        {
            std::cout << p.first << "->" << p.second << "\n";
        }
        if (it->second.size() > 1)
        {
            result += generateCombinationsPart1(it->second, boundaryY, boundaryX, anodes);
        }
    }

    return result;

}

int calculated_distance_Part2(std::map<char, std::vector<std::pair<int, int>>>& mp, int& boundaryY, int& boundaryX)
{
    int result = 0;
    std::set<std::pair<int, int>> anodes;
    std::map<char, std::vector<std::pair<int, int>>>::iterator it;
    for (it = mp.begin(); it != mp.end(); it++)
    {
        std::cout << it->first << ":" << "\n";
        for (const auto& p : it->second)
        {
            std::cout << p.first << "->" << p.second << "\n";
        }
        if (it->second.size() > 1)
        {
            result += generateCombinationsPart2(it->second, boundaryY, boundaryX, anodes);
        }
    }

    std::cout << "Bevore: " << "\n";
    print(mp, anodes, boundaryY, boundaryX);
    std::cout << "Result: " << result << "\n";
    result += generateMissingAnodes(mp, anodes);
    std::cout << "After: " << "\n";
    print(mp, anodes, boundaryY, boundaryX);

    return result;

}



std::map<char, std::vector<std::pair<int, int>>> get_input(const std::string& filename, int& boundaryY, int& boundaryX)
{
    std::string temp;
    std::map<char, std::vector<std::pair<int, int>>> mp;
    std::ifstream in_file(filename);
    int y = 0;
    while (std::getline(in_file, temp))
    {
        std::cout << temp << "\n ";

        for (int x = 0; x < temp.size(); x++)
        {
            auto it = mp.find(temp[x]);

            if (it != mp.end())
            {
                it->second.push_back(std::pair<int, int>{x, y});
            }
            else if (temp[x] != '.')
            {
                mp.insert(std::make_pair(temp[x], std::vector<std::pair<int, int>>{{x, y}}));
            }
        }
        y++;
    }
    boundaryY = y;
    boundaryX = temp.size();
    return mp;
}

int main()
{
    int boundaryY = 0;
    int boundaryX = 0;
    std::map<char, std::vector<std::pair<int, int>>> mp = get_input("input08.txt", boundaryY, boundaryX);
    std::cout << "BoundY: " << boundaryY << " BoundX: " << boundaryX << std::endl;
    int resp1 = calculated_distancePart1(mp, boundaryY, boundaryX);
    int resp2 = calculated_distance_Part2(mp, boundaryY, boundaryX);
    std::cout << "Result Part1: " << resp1 << "\n";
    std::cout << "Result Part2: " << resp2 << "\n";
    return 0;
}
