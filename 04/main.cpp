#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>





int main()
{
	std::string file;
	std::string text;

	std::ifstream MyF("input04.txt");

	while (std::getline(MyF, text))
	{
		file += text;
	}
	MyF.close();
	int i = 0;
	int y = 0;
	std::string word = "XMAS";
	int forwardscount = 0;
	int backwardscount = 0;
	while (i < file.size())
	{
		y = 0;
		std::string temp = "";
		while (i < file.size() && y < word.size() && file[i] == word[y])
		{

			temp += file[i];
			y++;
			i++;
		}
		if (y == word.size())
		{
			std::cout << temp << std::endl;
			forwardscount++;
		}
		else if (y > 0) {
			i--;
		}

		i++;
	}
	i = file.size() - 1;
	while (i >= 0)
	{
		y = 0;
		std::string temp = "";
		while (i >= 0 && y < word.size() && file[i] == word[y])
		{

			temp += file[i];
			y++;
			i--;
		}
		if (y == word.size())
		{
			std::cout << temp << std::endl;
			backwardscount++;
		}
		else if (y > 0) {
			i++;
		}
		i--;
	}
	std::vector<std::vector<char>> v;
	std::vector<char> v2;
	std::ifstream MyFile("input04.txt");

	while (std::getline(MyFile, text))
	{
		for (int i = 0; i < text.size(); i++)
		{
			v2.push_back(text[i]);
		}
		v.push_back(v2);
	}
	MyF.close();


	std::cout << backwardscount << std::endl;

	std::cout << forwardscount << std::endl;

	for (i = 0; i < v.size(); i++)
	{
		for (y = 0; y < v[i].size(); y++)
		{
			std::cout << v[i][y];
		}
	}

	return 0;
}