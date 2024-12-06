#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <tuple>

std::vector<int> changeDir(int& currentDir)
{
	std::vector<std::vector<int>> directions = { {0,-1},{1,0},{0,1},{-1,0} };
	std::vector<int> newDirection;
	switch (currentDir)
	{
	case 0:
		newDirection = directions[1];
		currentDir = 1;
		break;
	case 1:
		newDirection = directions[2];
		currentDir = 2;
		break;
	case 2:
		newDirection = directions[3];
		currentDir = 3;
		break;
	case 3:
		newDirection = directions[0];
		currentDir = 0;
		break;
	}

	return newDirection;
}


bool doesGuardLoop(int startX, int startY, int dir, std::vector<std::vector<char>>& mainmp, int obstX, int obstY) 
{
	std::set<std::pair<int, int>> visited;
	visited.insert({ startX, startY });
	int guarddir = dir;
	int x = startX, y = startY;
	std::vector<std::vector<char>> map = mainmp;
	std::vector<int> direction = changeDir(guarddir);
	std::set<std::tuple<int, int, int>> visited_dirs;
	
	map[obstY][obstX] = '#';
	int moves = 0;
	while (true) 
	{
		visited_dirs.insert({ x,y,guarddir });
		x += direction[0];
		y += direction[1];


		if (x < 0 || y < 0 || y >= map.size() || x >= map[0].size()) break;

		if (map[y][x] == '#') 
		{
			x -= direction[0];
			y -= direction[1];
			direction = changeDir(guarddir);
		}
		else 
		{
			if (visited_dirs.find({ x, y, guarddir }) != visited_dirs.end()) 
			{
				return true;
			}
			else
			{
				moves++;
			}
			visited.insert({ x, y });
		}
	}



	return false;
}


int main()
{
	std::vector<char> x;
	std::vector<std::vector<char>> y;
	std::string text;
	std::ifstream in_file("input06.txt");
	std::vector<int> ps;
	
	int inty = 0;
	int intx = 0;
	while (std::getline(in_file, text))
	{

		int intx = 0;
		for (const char& chr : text)
		{
			x.push_back(chr);
			if (chr == '^')
			{
				ps.push_back(intx);
				ps.push_back(inty);
			}
			intx++;
		}
		y.push_back(x);
		x.clear();
		inty++;
	}
	in_file.close();


	inty = ps[1];
	intx = ps[0];
	
	int dir = 3;

	int moves = 1;

	std::set<std::pair<int, int>> visited;
	std::vector<int> direction = changeDir(dir);
	std::cout << y.size() << std::endl;
	std::cout << y[0].size() << std::endl;
	std::pair<int, int> cord = { intx, inty };
	visited.insert(cord);
	int obstructions = 0;
	std::set<std::pair<int, int>> testedObstructions;
	while (inty > -1 && intx > -1 && inty < y.size()-1 && intx < y[0].size()-1)
	{
		testedObstructions.insert(std::pair<int,int>{ intx,inty });
		if (inty < y.size() - 1 && intx < y[0].size() - 1 && testedObstructions.find({ intx + direction[0], inty + direction[1] }) == testedObstructions.end() && doesGuardLoop(intx, inty, dir, y, intx + direction[0], inty + direction[1]))
		{
			obstructions++;
		}
		intx += direction[0];
		inty += direction[1];
		cord = { intx, inty };


		if (y[inty][intx] == '#')
		{
			intx -= direction[0];
			inty -= direction[1];
			direction = changeDir(dir);
		}
		else
		{

			if (visited.find(cord) == visited.end())
			{
				visited.insert(cord);
				moves++;

			}
			
		}
	}

	std::cout << "moves: " << moves << std::endl;
	std::cout << "obstructions: " << obstructions << std::endl;
	return 0;
}
