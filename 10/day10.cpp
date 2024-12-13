#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>


int findTrails(const std::vector<std::vector<int>>& map, int x, int y, std::set<std::pair<int, int>>& visited)
{
	// Directions : EAST, SOUTH, WEST, NORTH
	std::vector<std::pair<int, int>> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	int trailSum = 0;
	int currentHeight = map[y][x];
	visited.insert({ x, y });
	if (currentHeight == 9)
	{
		return 1;
	}
	for (const auto& direction : directions)
	{
		int newX = x + direction.first;
		int newY = y + direction.second;

		if (newX >= 0 && newX < map[0].size() && newY >= 0 && newY < map.size())
		{
			int newHeight = map[newY][newX];
			if (newHeight - 1 == currentHeight && visited.find({ newX, newY }) == visited.end())
			{
				//std::cout << "CurrentPos: X " << x << " Y " << y << " CurrentHeight: " << currentHeight << "\n";
				//std::cout << "Direction: X " << direction.first << ", Y " << direction.second << " NewPos: " << newX <<"->"<< newY << " Newheight: " << newHeight << "\n";
				trailSum += findTrails(map, newX, newY, visited);
			}
		}
	}

	visited.erase({ x, y }); // Backtracking
	return trailSum;
}

int findTrailsPart2(const std::vector<std::vector<int>>& map, int x, int y)
{
	// Directions : EAST, SOUTH, WEST, NORTH
	std::vector<std::pair<int, int>> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	int trailSum = 0;
	int currentHeight = map[y][x];
	if (currentHeight == 9)
	{
		return 1;
	}
	for (const auto& direction : directions)
	{
		int newX = x + direction.first;
		int newY = y + direction.second;

		if (newX >= 0 && newX < map[0].size() && newY >= 0 && newY < map.size())
		{
			int newHeight = map[newY][newX];
			if (newHeight - 1 == currentHeight)
			{
				//std::cout << "CurrentPos: X " << x << " Y " << y << " CurrentHeight: " << currentHeight << "\n";
				//std::cout << "Direction: X " << direction.first << ", Y " << direction.second << " NewPos: " << newX << "->" << newY << " Newheight: " << newHeight << "\n";
				trailSum += findTrailsPart2(map, newX, newY);
			}
		}
	}

	return trailSum;
}

int main()
{
	std::string line;
	std::ifstream in_file("input10.txt");

	std::vector<std::pair<int, int>> possibleTrailheads;
	std::vector<std::vector<int>> map;
	int y = 0;
	

	while (std::getline(in_file, line))
	{
		int x = 0;
		std::vector<int> cords;
		for (const char& chr : line)
		{
			if (chr == '0')
			{
				possibleTrailheads.push_back(std::pair<int, int>{x, y});
			}
			int height = chr - 48;
			cords.push_back(height);
			x++;
		}
		map.push_back(cords);
		y++;
	}
	int totalScore = 0;

	for (const auto& start : possibleTrailheads)
	{
		std::set<std::pair<int, int>> visited;
		//std::cout << "Start: " << start.first << "->" << start.second << "\n";
		totalScore += findTrails(map, start.first, start.second, visited);
	}
	int totalScore2 = 0;
	for (const auto& start : possibleTrailheads)
	{
		//std::cout << "Start: " << start.first << "->" << start.second << "\n";
		totalScore2 += findTrailsPart2(map, start.first, start.second);
	}

	std::cout << "Part1: " << totalScore << std::endl;
	std::cout << "Part2: " << totalScore2 << std::endl;
	return 0;
}
