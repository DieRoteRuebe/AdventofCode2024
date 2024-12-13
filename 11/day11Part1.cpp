#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string& str, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}

	return tokens;
}


std::vector<long long> rule1(long long stone)
{
	std::vector<long long> res;
	res.push_back(1);
	return res;
	
}

std::vector<long long> rule2(long long stone, long long size)
{
	std::vector<long long> res;
	long long middle = size / 2;
	int i = 0;
	int num2 = 0;
	while (i < middle)
	{
		long long temp = stone%10;
		num2 += temp;
		num2 *= 10;
		stone /= 10;
		i++;
	}
	num2 /= 10;
	res.push_back(stone);
	res.push_back(num2);
	return res;
}

std::vector<long long> nothingFits(long long stone)
{
	std::vector<long long> res;
	res.push_back(stone * 2024);
	return res;
}

int findRule(long long stone)
{
	int rule = 0;
	if (stone == 0)
	{
		return 1;
	}
	else if(std::to_string(stone).size()%2 == 0)
	{
		return std::to_string(stone).size();
	}
	else
	{
		return 0;
	}
	return rule;
}

long long calculate(std::vector<long long> stones, int blinks)
{
	int currentBlinks = 0;
	while (currentBlinks < blinks)
	{
		std::cout << "Current Blink: " << currentBlinks << "\n";
		std::vector<long long> stonesNew;
		for (const long long& stone : stones)
		{
			std::vector<long long> temp;
			long long foundRule = findRule(stone);
			switch (foundRule)
			{
			case 1:
				temp = rule1(stone);
				break;
			case 0:
				temp = nothingFits(stone);
				break;
			default:
				temp = rule2(stone, foundRule);
				
			}
			stonesNew.insert(stonesNew.end(), temp.begin(), temp.end());
		}
		stones = stonesNew;
		currentBlinks++;
		std::cout << "CurrentSize: " << stones.size() << "\n";
	}

	return stones.size();
}

int main()
{
	std::string line;
	std::ifstream file_in("input11.txt");
	while (std::getline(file_in, line));

	std::vector<long long> stones;
	std::vector<std::string> stonesStr;
	stonesStr = split(line, ' ');
	for (const std::string& s : stonesStr)
	{
		stones.push_back(std::stoi(s));
	}

	int blinks = 25;
	long long ret = calculate(stones, 25);
	std::cout << "Part1: " << ret << "\n";
	//Ok this will take some time -> I´ll implement a threaded solution with maybe some bit shenanigans to solve part2. Solution 2 coming soon.
	//long long ret2 = calculate(stones, 75);
	//std::cout << "Part2: " << ret2 << "\n";
	return 0;
}
