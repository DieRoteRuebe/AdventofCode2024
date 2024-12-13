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

long long calculateSumPart2(const std::vector<Block>& blocks)
{
	int currentNumPos = 0;
	long long sum = 0;

	for (const Block& block : blocks)
	{
		//skip moved space
		if (block.occupiedIds.size() == 0)
		{
			currentNumPos += block.occupied;
		}
		for (const int& num : block.occupiedIds)
		{
			sum += num * currentNumPos;
			currentNumPos++;
		}
		for (const int& num : block.freeUsed)
		{
			sum += num * currentNumPos;
			currentNumPos++;
		}

		// Skip free space
		currentNumPos += block.free;
	}

	return sum;
}

void rearangeSpacesPart2(std::vector<Block>& blocks)
{
	for (int backPos = blocks.size() - 1; backPos >= 0; backPos--)
	{
		if (blocks[backPos].occupiedIds.empty())
			continue;

		for (int frontPos = 0; frontPos < backPos; frontPos++)
		{
			if (blocks[frontPos].free >= blocks[backPos].occupiedIds.size())
			{
				// Move entire file
				blocks[frontPos].freeUsed.insert(blocks[frontPos].freeUsed.end(),
					blocks[backPos].occupiedIds.begin(),
					blocks[backPos].occupiedIds.end());

				blocks[frontPos].free -= blocks[backPos].occupiedIds.size();
				blocks[backPos].occupiedIds.clear();
				break; // File moved; exit inner loop
			}
		}
	}
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

void debugBlocks(const std::vector<Block>& blocks)
{
	for (size_t i = 0; i < blocks.size(); ++i)
	{
		std::cout << "Block " << i << ": ";
		std::cout << "OccupiedIds: ";
		for (int id : blocks[i].occupiedIds)
			std::cout << id << " ";
		std::cout << "| FreeUsed: ";
		for (int id : blocks[i].freeUsed)
			std::cout << id << " ";
		std::cout << "| Free: " << blocks[i].free << "\n";
	}
	std::cout << "-----\n";
}

int main()
{
	std::string text;

	std::ifstream in_file("input09.txt");
	std::vector<Block> blocks;
	while (std::getline(in_file, text));

	int y = 1;
	int id = 0;

	for (int i = 0; i < text.size(); i += 2)
	{
		Block block;
		block.occupied = text[i] - 48;
		for (int j = 0; j < block.occupied; j++)
		{
			block.occupiedIds.push_back(id);
		}
		block.free = (i + 1 < text.size()) ? text[i + 1] - 48 : 0;
		blocks.push_back(block);
		id++;
	}

	std::vector<Block> blocks2 = blocks;
	rearangeSpaces(blocks);
	long long ret = calculateSum(blocks);
	rearangeSpacesPart2(blocks2);
	debugBlocks(blocks2);
	long long ret2 = calculateSumPart2(blocks2);
	std::cout << "Part1 sol: " << ret << std::endl;
	std::cout << "Part2 sol: " << ret2 << std::endl;
	return 0;

}
