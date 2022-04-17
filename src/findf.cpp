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
		char* where_to_look = argv[1];
		read_sub(where_to_look);
	}
	else if (argc >= 3) //find <where-to-look> <option_entered> <argument_entered>
	{
		/*
			User has a criteria in mind
		*/
		char* soption_entered = argv[2];
		option option_entered = parse_option(soption_entered);

		char* argument_entered = argv[3];

		switch (option_entered)
		{
		case ERR: //TODO: implement unexpected argument
			break;

		case NAME://TODO: implement name option
			break;

		case MMIN://TODO: implement mmin option
			break;

		case INUM://TODO: implement inum option
			break;
		}
	}


	return 0;
}
