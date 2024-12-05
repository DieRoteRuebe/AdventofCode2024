#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

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

bool isUpdateValid(const std::vector<int>& update, const std::vector<std::pair<int, int>>& rules) 
{
	std::unordered_map<int, int> pagePositions;
	for (size_t i = 0; i < update.size(); ++i) 
	{
		pagePositions[update[i]] = i;
	}

	for (const auto& rule : rules) {
		int x = rule.first, y = rule.second;

		if (pagePositions.count(x) && pagePositions.count(y)) {
			if (pagePositions[x] > pagePositions[y]) {
				return false;
			}
		}
	}
	return true;
}

std::vector<int> sortUpdate(const std::vector<int>& update, const std::vector<std::pair<int, int>>& rules) 
{
	std::vector<int> sortedUpdate = update;
	//ich hasse compare lambdas btw!! aber so funktionierts:
	auto compare = [&rules](int a, int b) {
		for (const auto& rule : rules) 
		{
			if (rule.first == a && rule.second == b) 
			{
				return true;
			}
			if (rule.first == b && rule.second == a) 
			{
				return false;
			}
		}
		return false;
		};
	
	sort(sortedUpdate.begin(), sortedUpdate.end(), compare);
	


	//Nochmal verständlicher weils Flummis wie mich gibt:
	std::vector<int> sortedUpdate2 = update;
	for (int i = 0; i < sortedUpdate2.size() - 1; i++) 
	{
		for (int j = i + 1; j < sortedUpdate2.size(); j++) 
		{
			bool swap = false;
			for (const auto& rule : rules) 
			{
				if (rule.first == sortedUpdate2[j] && rule.second == sortedUpdate2[i]) {
					swap = true;
					break;
				}
				if (rule.first == sortedUpdate2[i] && rule.second == sortedUpdate2[j]) {
					swap = false;
					break;
				}
			}
			if (swap) {
				std::swap(sortedUpdate2[i], sortedUpdate2[j]);
			}
		}
	}
	return sortedUpdate2;
}




int main()
{
	std::string file;
	std::string text;
	std::vector<std::pair<int, int>> rules;
	std::ifstream in_file("input05_1.txt"); //X|Y


	while(std::getline(in_file, text))
	{
		std::vector<std::string> temp;
		temp = split(text, '|');
		rules.emplace_back(stoi(temp[0]), stoi(temp[1]));
	}
	in_file.close();
	

	std::ifstream in_file2("input05_2.txt"); //Digit,Digit
	std::vector<std::vector<int>> updates;
	while (std::getline(in_file2, text))
	{
		std::vector<std::string> ret;
		ret = split(text, ',');
		std::vector<int> temp;
		for (const std::string& s: ret)
		{
			temp.push_back(stoi(s));
		}
		updates.push_back(temp);
	}
	int sum = 0;
	int updatedSum = 0;
	for (const auto& update : updates)
	{
		if (isUpdateValid(update, rules))
		{
			sum += update[update.size() / 2];
		}
		else
		{
			std::vector<int> correct = sortUpdate(update, rules);
			updatedSum += correct[correct.size() / 2];
		}
	}
	std::cout << "sum: " << sum << "\n";
	std::cout << "Update-sum: " << updatedSum << "\n";


	return 0;
}
