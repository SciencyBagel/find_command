// find_command.cpp : Defines the entry point for the application.
//

#include "../include/find_command.h"

using namespace std;

int main(int argc, char* argv[])
{
	//===================================
	//Argument Checking
	//===================================
	// 
	//check that "findf" is being used
	if (strcmp(argv[0], "findf") != 0)
	{
		//check if user passed the right arguments
		std::cout << "Error: Wrong command used." << std::endl;
		return 1;
	}

	//check right number of arguments being used
	if (argc < 2)
	{
		//user did not pass enough arguments
		std::cout << "Error: Too few arguments." << std::endl;
		return 1;
	}
	else if (argc >= 2)
	{
		char* where_to_look = argv[1];

		switch (argc)
		{
		case 2:
			/* 
				User only wants to display the pathnames of all files in the specified directory along with all subdirectories. 
				Recursion needed.
				find <where-to-look>
			*/

			break;

		case 3:
			/* 
				User has a criteria in mind: 
				find <where-to-look>[criteria] 
			*/
			break;

		default:
			break;
		}

	}


	return 0;
}
