// find_command.cpp : Defines the entry point for the application.
//

#include "../include/utilities.h"
#include <iostream>

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
		utilities::read_sub(where_to_look);
	}
	else if (argc == 2) //findf <where-to-look>
	{
		/*
			User only wants to display the pathnames of all files in the specified directory
			along with all subdirectories. Recursion needed.
		*/
		where_to_look = argv[1];
		utilities::read_sub(where_to_look);
	}
	else if (argc == 4) //findf <where_to_look> <option_entered> <argument_entered>
	{
		/*
			User has a criteria in mind
		*/
		where_to_look = argv[1]; //argument used for <where_to_look>
		option option_entered = utilities::parse_option(argv[2]); //argument used for <option_entered>
		char* arg_entered = argv[3]; //argument used for <argument_entered>


		switch (option_entered)
		{
		case option::ERR: //find <where_to_look>
		{
			std::cout << "Error: Unexpected argument (" << argv[2] << ")." << std::endl;
			return 1;
		}
		case option::NAME://findf <where_to_look> -name <file_name>
		{
			char& file_name = *arg_entered;
			utilities::read_subn(where_to_look, &file_name);
			return 0;
		}

		case option::MMIN://findf <where_to_look> -mmin <n_mins>
		{
			char& n_mins = *arg_entered;
			utilities::read_subm(where_to_look, &n_mins);
			return 0;
		}
		case option::INUM://findf <where_to_look> -inum <i_node>
		{
			char& i_node = *arg_entered;
			utilities::read_subi(where_to_look, &i_node);
			return 0;
		}
		}
	}
	else
	{
		std::cout << "Error: Unexpected number of arguments (" << argc << ")" << std::endl;
		return 1;
	}


	return 0;
}
