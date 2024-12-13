#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

struct Block
{
	int occupied;
	std::vector<int> occupiedIds;
	int free;
	std::vector<int> freeUsed;	
};

long long calculateSum(std::vector<Block>& blocks)
{
	int currentBlockPos = 0;
	int currentNumPos = 0;
	long long sum = 0;
	while (blocks[currentBlockPos].occupiedIds.size() > 0)
	{
		for (const int& num : blocks[currentBlockPos].occupiedIds)
		{
			sum += num * currentNumPos;
			currentNumPos++;
		}
		for (const int& num : blocks[currentBlockPos].freeUsed)
		{
			sum += num * currentNumPos;
			currentNumPos++;
		}
		currentBlockPos++;
	}
	return sum;
}

void rearangeSpaces(std::vector<Block>& blocks)
{
	int frontPos = 0;
	int backPos = blocks.size() - 1;
	while (backPos > frontPos)
	{
		
		while (blocks[backPos].occupied > 0)
		{
			
			if (blocks[frontPos].free > 0)
			{
				blocks[backPos].occupied--;
				blocks[frontPos].free--;
				blocks[frontPos].freeUsed.push_back(backPos);
				blocks[backPos].occupiedIds.pop_back();
			}
			else
			{
				frontPos++;
				if (frontPos == backPos)
				{
					break;
				}
			}
		}
		backPos--;
	}
}

int main()
{
	std::string text;

	std::ifstream in_file("input09.txt");
	std::vector<Block> blocks;
	while (std::getline(in_file, text));

	
	// Map:
	// id, pair < Occuptied-Space, Free-Space>

	int y = 1;
	int id = 0;
	for (int i = 0; i < text.size(); i+=2)
	{
		y = i + 1;
		Block block;
		if (y < text.size())
		{
			block.occupied = text[i] - 48;
			for (int i = 0; i < block.occupied; i++)
			{
				block.occupiedIds.push_back(id);
			}
			block.free = text[y] - 48;

		}
		else
		{
			block.occupied = text[i] - 48;
			for (int i = 0; i <= block.occupied; i++)
			{
				block.occupiedIds.push_back(text[i] - 48);
			}
			block.free = 0;
		}
		blocks.push_back(block);
		id++;
	}
	
	rearangeSpaces(blocks);
	long long ret = calculateSum(blocks);
	std::cout << "Part1 sol: " << ret;
	return 0;

}
