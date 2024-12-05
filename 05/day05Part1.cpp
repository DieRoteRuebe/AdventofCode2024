#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

std::vector<std::string> split(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

bool isUpdateValid(const std::vector<int>& update, const std::vector<std::pair<int, int>>& rules) {
	// Erstelle ein Mapping der Positionen der Seiten im Update
	std::unordered_map<int, int> pagePositions;
	for (size_t i = 0; i < update.size(); ++i) {
		pagePositions[update[i]] = i;
	}

	// Prüfe jede Regel
	for (const auto& rule : rules) {
		int x = rule.first, y = rule.second;

		// Prüfe nur, wenn beide Seiten im Update enthalten sind
		if (pagePositions.count(x) && pagePositions.count(y)) {
			// Wenn x nach y kommt, ist die Regel verletzt
			if (pagePositions[x] > pagePositions[y]) {
				return false;
			}
		}
	}
	return true;
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
	std::cout << file << "\n";
	

	std::ifstream in_file2("input05_2.txt"); //X|Y
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
	in_file2.close();
	int sum = 0;
	for (const auto& update : updates)
	{
		if (isUpdateValid(update, rules))
		{
			sum += update[update.size() / 2];
		}
	}
	std::cout << "sum: " << sum << "\n";
	return 0;
}
