
#include "include/utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void read_sub(char* directory)
{
	printf("\n\nIn directory %s\n", directory);

	DIR* dir_stream_ptr = opendir(directory);//open a directory stream
	struct dirent* dirent_ptr; //define dirent structure
	struct stat buf; //define file status structure object

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