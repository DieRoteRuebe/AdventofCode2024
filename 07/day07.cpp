#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

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

void generateCombinations(const std::vector<char>& operators, int length, std::string current, std::vector<std::string>& result) 
{
	if (length == 0) {
		result.push_back(current);
		return;
	}
	for (char op : operators) 
	{
		generateCombinations(operators, length - 1, current + op, result);
	}
}

struct line
{
	long long Value;
	std::vector<int> v;
};

int main()
{
	std::string text;
	std::ifstream file_in("input07.txt");
	std::vector<std::string> v1;
	std::vector<struct line> v;
	while (std::getline(file_in, text))
	{
		v1 = split(text, ':');
		line l;
		
		l.Value = stoll(v1[0]);
		std::cout << "Value: " << l.Value << std::endl;
		v1 = split(v1[1], ' ');

		for (const auto& value : v1)
		{
			if (value !=  "")
			{
				l.v.push_back(stoi(value));
			}
		}
		v.push_back(l);

		
	}
	std::vector<char> op = { '+','*','|'};
	unsigned long long result = 0;
	for (struct line& line : v)
	{	
		std::vector<std::string> comb;
		generateCombinations(op, line.v.size() - 1, "", comb);
		bool flag = false;
		for (const std::string& combo : comb)
		{
			unsigned long long sum = 0;
			int y = 0;
			
			for (int i = 0; i < line.v.size(); i++)
			{
				if (i == 0)
				{
					sum = line.v[i];
				}
				else if (combo[y] == '+')
				{
					sum += line.v[i];
					y++;
				}
				else if (combo[y] == '*')
				{
					sum *= line.v[i];
					y++;
				}
				else if (combo[y] == '|')
				{
					std::string temp;
					temp = std::to_string(sum);
					sum = 0;
					temp += std::to_string(line.v[i]);
					sum = std::stoll(temp);
					y++;
				}
				
			}
			if (sum == line.Value)
			{
				std::cout << "Hit at: " << line.Value << " combo: " << combo << "Value: " << line.Value << "Sum: " << sum << std::endl;
				flag = true;
				break;
			}
		}
		if (flag)
		{
			result += line.Value;
		}
		
	}
	std::cout << "Result: " << result << std::endl;
	return 0;

}
