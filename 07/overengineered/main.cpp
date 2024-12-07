#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include "Threadpool.h"

#define MAXTHREADS 4


struct line
{
	long long Value;
	std::vector<int> v;
	unsigned long long internal_sum;
};

long long applyOperation(long long lhs, long long rhs, char op) 
{
    if (op == '+') 
	{
        	return lhs + rhs;
    	}
    	else if (op == '*') 
    	{
        	return lhs * rhs;
    	} 
	else if (op == '|') 
	{
        // concatenate the numbers
        	std::string lhs_str = std::to_string(lhs);
        	std::string rhs_str = std::to_string(rhs);
        	return std::stoll(lhs_str + rhs_str);
    	}
    return 0;
}


void generateCombinations(const std::vector<char>& operators, int length, std::string current, std::vector<std::string>& result) 
{
	if (length == 0) 
	{
		result.push_back(current);
		return;
	}
	for (char op : operators) 
	{
		generateCombinations(operators, length - 1, current + op, result);
	}
}


void calculate(void* argv)
{
	std::vector<char> op = { '+','*','|'};
	thread_connection* con = static_cast<thread_connection*>(argv);
	line* l = static_cast<line*>(con->arg);
	std::vector<std::string> comb;
	generateCombinations(op, l->v.size()-1, "", comb);

    	bool flag = false;
    	for (const std::string& combo : comb) 
    	{
        long long sum = l->v[0];
        int y = 0;

        // Compute the expression based on the generated combination
        for (size_t i = 1; i < l->v.size(); ++i) 
	{
            sum = applyOperation(sum, l->v[i], combo[y]);
            ++y;
	}

        	if (sum == l->Value) 
		{
			std::string channel_name = "THREAD-"+std::to_string(*con->thread_id);
			std::string logmsg = "Hit at: "+std::to_string(l->Value)+" combo: "+combo+" Sum: "+std::to_string(sum);
			con->l->log(logmsg, channel_name);
           	 	flag = true;
            		break;
	        }
        }
        if (flag) 
	{
            l->internal_sum += l->Value;
        }	
}


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



int main()
{
	Logger L(__THREADED,"MAIN", "123");
	std::string text;
	L.log("starting mainthread", "MAIN");
	std::ifstream file_in("input07.txt");
	std::vector<std::string> v1;
	std::vector<struct line*> v;
	while (std::getline(file_in, text))
	{
		v1 = split(text, ':');
		line* l = new line();
		
		l->Value = stoll(v1[0]);
		std::cout << "Value: " << l->Value << std::endl;
		v1 = split(v1[1], ' ');

		for (const auto& value : v1)
		{
			if (value !=  "")
			{
				l->v.push_back(stoi(value));
			}
		}
		v.push_back(l);

		
	}

	//Init Threadpool:
	int thread_QueueSize = 850;
	Threadpool pool(thread_QueueSize, MAXTHREADS, &L);

	unsigned long long result = 0;
	for (struct line*& l : v)
	{	
		//line = struct line { long long Value, std::vector<int> v, unsigned long long internal_sum}
		pool.threadpool_add_task((*calculate), l);
	}

	pool.join_threads();
	
	for(struct line*& l : v)
	{
		std::cout << "internal sum: " << l->internal_sum << std::endl;
		result += l->internal_sum;
	}
	std::cout << "Result: " << result << std::endl;

	for(struct line*& l : v)
	{
		delete l;
	}
	return 0;

}
