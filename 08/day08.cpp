#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <set>



int generateCombinations(const std::vector<std::pair<int,int>>& vec, int& boundaryY, int& boundaryX, std::set<std::pair<int, int>>& anodes)
{
    int result = 0;
    for(size_t i = 0; i < vec.size(); i++)
    {
        std::pair<int, int> p1 = vec[i];
        std::pair<int, int> p2;
        for(size_t y = i+1; y < vec.size(); y++)
        {  
            p2 = vec[y];
            int newpY = p2.first + (p2.first - p1.first);
            int newpX = p2.second + (p2.second - p1.second);
            if( newpY > -1 && newpY < boundaryY &&  newpX > -1 && newpX < boundaryX && anodes.find({newpX, newpY}) == anodes.end())
            {
                anodes.insert({newpX, newpY});
                result++;
                std::cout << "Steigung: " << p1.first << "->" << p1.second << " : " << p2.first << "->" << p2.second<< " Steig: " <<p2.first - p1.first << "->" << p2.second - p1.second<< " newpos: " << p2.first + (p2.first - p1.first)<< "->" << p2.second + (p2.second - p1.second)<< "\n";
                std::cout << "possible Position!" << "\n";
            }
        }
        for(size_t y = 0; y < i; y++)
        {
            p2 = vec[y];
            int newpY = p2.first + (p2.first - p1.first);
            int newpX = p2.second + (p2.second - p1.second);
            if( newpY > -1 && newpY < boundaryY &&  newpX > -1 && newpX < boundaryX && anodes.find({newpX, newpY}) == anodes.end())
            {
                anodes.insert({newpX, newpY});
                result++;
                std::cout << "Steigung: " << p1.first << "->" << p1.second << " : " << p2.first << "->" << p2.second<< " Steig: " <<p2.first - p1.first << "->" << p2.second - p1.second<< " newpos: " << p2.first + (p2.first - p1.first)<< "->" << p2.second + (p2.second - p1.second)<< "\n";
                std::cout << "possible Position!" << "\n";
            }
        }
    }
    return result;
}


int calculated_distance(std::map<char, std::vector<std::pair<int, int>>>& mp, int& boundaryY, int& boundaryX)
{
    int result = 0;
    std::set<std::pair<int, int>> anodes;
    std::map<char, std::vector<std::pair<int, int>>>::iterator it;
    for(it = mp.begin(); it != mp.end(); it++)
    {
        std::cout << it->first << ":" << "\n";
        for(const auto& p : it->second)
        {
            std::cout << p.first << "->" << p.second << "\n";
        }
        if(it->second.size()>1)
        {
            result += generateCombinations(it->second, boundaryY, boundaryX, anodes);
        }
    }

    return result;
   
}



std::map<char, std::vector<std::pair<int, int>>> get_input(const std::string& filename, int& boundaryY, int& boundaryX)
{
    std::string temp;
    std::map<char, std::vector<std::pair<int, int>>> mp;
    std::ifstream in_file(filename);
    int y = 0;
    while(std::getline(in_file, temp))
    {
        std::cout << temp << "\n ";

        for(int x = 0; x < temp.size(); x++)
        {
            auto it = mp.find(temp[x]);

            if(it != mp.end())
            {
                it->second.push_back(std::pair<int,int>{x,y});
            }
            else if(temp[x]!= '.')
            {
                mp.insert(std::make_pair(temp[x], std::vector<std::pair<int,int>>{{x,y}}));
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
    int res = calculated_distance(mp, boundaryY, boundaryX);
    std::cout << "Result: " << res << "\n";
    return 0;
}

