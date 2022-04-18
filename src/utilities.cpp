
#include "../include/utilities.h"


void utilities::read_sub(char* directory)
{
	/* Recursively read directory. Print out all file and directory names. */

	DIR* dir_stream_ptr = opendir(directory);//open a directory stream
	struct dirent* dirent_ptr; //define dirent structure

	if (dir_stream_ptr != NULL) //check to see if dir_stream_ptr opened successfully
	{
		//loop to read one entry each time
		while ((dirent_ptr = readdir(dir_stream_ptr)) != NULL)
		{

			char* dirent_name = dirent_ptr->d_name;
			char* DOT = ".";
			char* DOTDOT = "..";
			char* F_SLASH = "/";

			//make sure directory name is not the hidden directories
			if (strcmp(dirent_name, DOT) != 0 && strcmp(dirent_name, DOTDOT) != 0) //recurisvely loop into the sub-directory
			{
				//token_build == "/[dirent_name]"
				char token_build[100];
				strcpy(token_build, F_SLASH);

				strcat(token_build, dirent_name);

				//temp_full_path == [directory]/[dirent_name]
				char* temp_full_path = new char[2000];
				strcpy(temp_full_path, directory);
				strcat(temp_full_path, token_build);

				//print current file or directory
				printf(temp_full_path);
				printf("\n");

				//try to open directory. If null, it's just a file
				DIR* sub_sub_directory_ptr = opendir(temp_full_path); //to check whether it is a file or directory
				if (sub_sub_directory_ptr != NULL)
				{
					//this is a directory
					//close the stream, because we will reopen it in the recursive call.
					closedir(sub_sub_directory_ptr);
					read_sub(temp_full_path);
				}
				delete(temp_full_path);
			}
		}
		closedir(dir_stream_ptr);
	}
	else
	{
		printf("Cannot open directory\n");
		exit(2);
	}

	return;
}

void utilities::read_subn(char* directory, char* file_name)
{
	/* Recursively read directory. Only print the path of specified file name(s).*/

	DIR* dir_stream_ptr = opendir(directory);//open a directory stream
	struct dirent* dirent_ptr; //define dirent structure


	if (dir_stream_ptr != NULL) //check to see if dir_stream_ptr opened successfully
	{
		//loop to read one entry each time
		while ((dirent_ptr = readdir(dir_stream_ptr)) != NULL)
		{

			char* dirent_name = dirent_ptr->d_name;
			char* DOT = ".";
			char* DOTDOT = "..";
			char* F_SLASH = "/";

			if (strcmp(dirent_name, DOT) != 0 && strcmp(dirent_name, DOTDOT) != 0)
			{
				/* Non "." or ".." file name found. */

				//token_build == "/[dirent_name]" to append to parent directory
				char token_build[100];
				strcpy(token_build, F_SLASH);
				strcat(token_build, dirent_name);

				//temp_full_path == [directory]/[dirent_name]
				char* temp_full_path = new char[2000];
				strcpy(temp_full_path, directory);
				strcat(temp_full_path, token_build);

				if (strcmp(dirent_name, file_name) == 0)
				{
					//file name found...print current file or directory
					printf(temp_full_path);
					printf("\n");
				}

				//try to open directory. If null, it's just a file
				DIR* sub_sub_directory_ptr = opendir(temp_full_path); //to check whether it is a file or directory
				if (sub_sub_directory_ptr != NULL)
				{
					//this is a directory
					closedir(sub_sub_directory_ptr); //close the stream, because we will reopen it in the recursive call.
					read_subn(temp_full_path, file_name); //go to sub directory to find file
				}
				delete(temp_full_path);
			}
		}
		closedir(dir_stream_ptr);
	}
	else
	{
		printf("Cannot open directory\n");
		exit(2);
	}
}

void utilities::read_subm(char* directory, char* n_mins)
{
	/* 
		This will find those files modified with the specified number of minutes ago.
		You can specify a number “n” to mean exactly n, “-n” to mean less than n, and “+n” to mean 
		more than n.
		$ find Document -mmin -10
		This is used to locate files modified less than 10 minutes ago 
	*/

	DIR* dir_stream_ptr = opendir(directory);//open a directory stream
	struct dirent* dirent_ptr; //define dirent structure
	struct stat file_stat; //define file status structure object

	if (dir_stream_ptr != NULL) //check to see if dir_stream_ptr opened successfully
	{
		//loop to read one entry each time
		while ((dirent_ptr = readdir(dir_stream_ptr)) != NULL)
		{

			char* dirent_name = dirent_ptr->d_name;
			char* DOT = ".";
			char* DOTDOT = "..";
			char* F_SLASH = "/";

			if (strcmp(dirent_name, DOT) != 0 && strcmp(dirent_name, DOTDOT) != 0)
			{
				/* Non "." or ".." file name found. */

				//token_build == "/[dirent_name]" to append to parent directory
				char token_build[100];
				strcpy(token_build, F_SLASH);
				strcat(token_build, dirent_name);

				//temp_full_path == [directory]/[dirent_name]
				char* temp_full_path = new char[2000];
				strcpy(temp_full_path, directory);
				strcat(temp_full_path, token_build);

				/*
					Now time logic.
				*/
				if (stat(dirent_ptr->d_name, &file_stat) == 0)
				{

				}
				

				// ===============================
				// Recurse if directory
				// ===============================
				//try to open directory. If null, it's just a file
				DIR* sub_sub_directory_ptr = opendir(temp_full_path); //to check whether it is a file or directory
				if (sub_sub_directory_ptr != NULL)
				{
					//this is a directory
					closedir(sub_sub_directory_ptr); //close the stream, because we will reopen it in the recursive call.
					read_subn(temp_full_path, file_name); //go to sub directory to find file
				}
				delete(temp_full_path);
			}
		}
		closedir(dir_stream_ptr);
	}
	else
	{
		printf("Cannot open directory\n");
		exit(2);
	}
}

void utilities::read_subi(char* directory, char* i_node)
{
}

option utilities::parse_option(char* arg)
{
	//This function parses the option passed. If option is not recognized, an error flag is returned.

	if (arg[0] != '-') //no dash found
	{
		return option::ERR;
	}

	//remove the '-'
	char parsed_option[10];
	strcpy(parsed_option, &arg[1]);

	if (strcmp(parsed_option, "name") == 0) //user used option -name
	{
		return option::NAME;
	}
	else if (strcmp(parsed_option, "mmin") == 0)
	{
		return option::MMIN;
	}
	else if (strcmp(parsed_option, "inum") == 0)
	{
		return option::INUM;
	}
	else
	{
		return option::ERR;
	}
}

