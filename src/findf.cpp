// find_command.cpp : Defines the entry point for the application.
//

#include "../include/utilities.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	//===================================
	//Argument Checking
	//===================================
	//check right number of arguments being used

	char* where_to_look; //directory to be searched
	if (argc == 1)
	{
		//user only typed the findf command -> search current directory
		where_to_look = ".";
		read_sub(where_to_look);
	}
	else if (argc == 2) //find <where-to-look>
	{
		/*
			User only wants to display the pathnames of all files in the specified directory
			along with all subdirectories. Recursion needed.
		*/
		where_to_look = argv[1];
		read_sub(where_to_look);
	}
	else if (argc == 4) //find <where_to_look> <option_entered> <argument_entered>
	{
		/*
			User has a criteria in mind
		*/
		where_to_look = argv[1]; //argument used for <where_to_look>
		char* soption_entered = argv[2]; //argument used for <option_entered>
		char* arg_entered = argv[3]; //argument used for <argument_entered>

		option option_entered = parse_option(soption_entered);
		switch (option_entered)
		{
		case option::ERR: //find <where_to_look>
			std::cout << "Error: Unexpected argument (" << soption_entered << ")." << std::endl;
			return 1;

		case option::NAME://find <where_to_look> -name <file_name>
			read_subn(where_to_look, arg_entered);
			return 0;

		case option::MMIN://TODO: implement mmin option
			return 0;

		case option::INUM://TODO: implement inum option
			return 0;
		}
	}
	else
	{
		std::cout << "Error: Unexpected number of arguments (" << argc << ")" << std::endl;
		return 1;
	}


	return 0;
}
