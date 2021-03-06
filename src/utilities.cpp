//implementation file for utilities
#include "../include/utilities.h"


void utilities::read_sub(char* current_directory)
{
	/* Recursively read current_directory. Print out all file and current_directory names. */

	DIR* dir_stream_ptr = opendir(current_directory);//open a current_directory stream
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

			//make sure current_directory name is not the hidden directories
			if (strcmp(dirent_name, DOT) != 0 && strcmp(dirent_name, DOTDOT) != 0) //recurisvely loop into the sub-current_directory
			{
				//token_build == "/[dirent_name]"
				char token_build[100];
				strcpy(token_build, F_SLASH);

				strcat(token_build, dirent_name);

				//full_path == [current_directory]/[dirent_name]
				char* full_path = new char[2000];
				strcpy(full_path, current_directory);
				strcat(full_path, token_build);

				//print current file or current_directory
				std::cout << full_path << '\n';

				// ===============================
				// Recurse if directory.
				// ===============================
				//try to open current_directory. If null, it's just a file
				DIR* child_directory_ptr = opendir(full_path); //to check whether it is a file or current_directory
				if (child_directory_ptr != NULL)
				{
					//this is a current_directory
					//close the stream, because we will reopen it in the recursive call.
					closedir(child_directory_ptr);
					read_sub(full_path);
				}
				delete(full_path);
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

void utilities::read_subn(char* current_directory, char* file_name, char* argv[], int argc = 4)
{
	/* Recursively read current_directory. Only print the path of specified file name(s).*/

	//check if user used a 5th argument in commandline (they might want to delete the file specified)
	bool arg_flag = false; //to check if argc is 5
	if (argc == 5)
	{
		arg_flag = true;
	}

	DIR* dir_stream_ptr = opendir(current_directory);//open a current_directory stream
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

				//token_build == "/[dirent_name]" to append to parent current_directory
				char token_build[100];
				strcpy(token_build, F_SLASH);
				strcat(token_build, dirent_name);

				//full_path == [current_directory]/[dirent_name]
				char* full_path = new char[2000];
				strcpy(full_path, current_directory);
				strcat(full_path, token_build);

				if (strcmp(dirent_name, file_name) == 0)
				{
					//file name found...print current file or current_directory
					std::cout << full_path << '\n';

					//check if user used a 5th argument in commandline (they might want to delete the file specified)
					if (arg_flag == true && utilities::check_delete(argv[4]) == true)
					{
						remove(full_path);
					}
				}

				// ===============================
				// Recurse if directory.
				// ===============================
				//try to open current_directory. If null, it's just a file
				DIR* child_directory_ptr = opendir(full_path); //to check whether it is a file or current_directory
				if (child_directory_ptr != NULL)
				{
					//this is a current_directory
					closedir(child_directory_ptr); //close the stream, because we will reopen it in the recursive call.
					read_subn(full_path, file_name, argv, argc); //go to sub current_directory to find file
				}
				delete(full_path);
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

void utilities::read_subm(char* current_directory, char* nmins, char* argv[], int argc = 4)
{
	/*
		This will find those files modified with the specified number of minutes ago.
		You can specify a number ?n? to mean exactly n, ?-n? to mean less than n, and ?+n? to mean
		more than n.
		$ find Document -mmin -10
		This is used to locate files modified less than 10 minutes ago
	*/

	/* Recursively read current_directory. */
		
	//check if user used a 5th argument in commandline (they might want to delete the file specified)
	bool arg_flag = false; //to check if argc is 5
	if (argc == 5)
	{
		arg_flag = true;
	}

	DIR* dir_stream_ptr = opendir(current_directory);//open a current_directory stream
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

				//token_build == "/[dirent_name]" to append to parent current_directory
				char token_build[100];
				strcpy(token_build, F_SLASH);
				strcat(token_build, dirent_name);

				//full_path == [current_directory]/[dirent_name]
				char* full_path = new char[2000];
				strcpy(full_path, current_directory);
				strcat(full_path, token_build);

				/*
					Time Logic.
				*/

				//Get file attributes and store them in file_stat. If error, exit.
				if (stat(full_path, &file_stat) == 0)
				{
					/* Get change in time from file modification to right now. */
					//get current time
					time_t current_time = time(NULL);

					//get last modified time
					timespec ts2 = file_stat.st_mtim;
					time_t l_modified_t = ts2.tv_sec;

					//get how much time has passed since file has been modified
					double mins_passed = difftime(current_time, l_modified_t) / 60.0; //seconds to minutes
					mins_passed = floor(mins_passed); //round down

					/* Get user specified time. */
					double mins_specified = strtod(nmins, NULL);
					mins_specified = fabs(mins_specified); //take absolute value of mins_specified to avoid "-" and "+" in logic.

					/* logic depends on '+' or '-' */
					switch (nmins[0])
					{
					case '-':
						//case: less than mins_specified
						if (mins_passed < mins_specified)
						{
							//file found
							std::cout << full_path << '\n';

							//check if user used a 5th argument in commandline (they might want to delete the file specified)
							if (arg_flag == true && utilities::check_delete(argv[4]) == true)
							{
								remove(full_path);
							}
						}
						break;
					case '+':
						//case: more than mins_specified
						if (mins_passed > mins_specified)
						{
							//file found
							std::cout << full_path << '\n';

							//check if user used a 5th argument in commandline (they might want to delete the file specified)
							if (arg_flag == true && utilities::check_delete(argv[4]) == true)
							{
								remove(full_path);
							}
						}
						break;
					default:
						//case: exact mins_specified
						if (mins_passed == mins_specified)
						{
							//file found
							std::cout << full_path << '\n';

							//check if user used a 5th argument in commandline (they might want to delete the file specified)
							if (arg_flag == true && utilities::check_delete(argv[4]) == true)
							{
								remove(full_path);
							}
						}
						break;
					}
				}
				else
				{
					std::cout << "Error in opening file: " << dirent_name << std::endl;
					exit(1);
				}


				// ===============================
				// Recurse if directory.
				// ===============================
				//try to open current_directory. If null, it's just a file
				DIR* child_directory_ptr = opendir(full_path); //to check whether it is a file or current_directory
				if (child_directory_ptr != NULL)
				{
					//this is a current_directory
					closedir(child_directory_ptr); //close the stream, because we will reopen it in the recursive call.
					read_subm(full_path, nmins, argv, argc); //go to sub current_directory to find file
				}
				delete(full_path);
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

void utilities::read_subi(char* current_directory, char* i_node, char* argv[], int argc = 4)
{
	/* Recursively read current_directory. Print out directory/file with specified cur_file_inode. */

	bool arg_flag = false; //to check if argc is 5
	if (argc == 5)
	{
		arg_flag = true;
	}

	DIR* dir_stream_ptr = opendir(current_directory);//open a current_directory stream
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

			//make sure current_directory name is not the hidden directories
			if (strcmp(dirent_name, DOT) != 0 && strcmp(dirent_name, DOTDOT) != 0) //recurisvely loop into the sub-current_directory
			{
				//token_build == "/[dirent_name]"
				char token_build[100];
				strcpy(token_build, F_SLASH);

				strcat(token_build, dirent_name);

				//full_path == [current_directory]/[dirent_name]
				char* full_path = new char[2000];
				strcpy(full_path, current_directory);
				strcat(full_path, token_build);


				// ===============================
				// I-node logic.
				// ===============================
				ino_t inode_specified = atol(i_node);

				//outer if else statement to check if file opened properly
				if (stat(full_path, &file_stat) == 0)
				{
					ino_t cur_file_inode = file_stat.st_ino;

					//check if this inode is the one specified by user
					if (cur_file_inode == inode_specified)
					{
						//user specified inode found in current file...print the file
						std::cout << full_path << '\n';

						//check if user used a 5th argument in commandline (they might want to delete the file specified)
						if ( arg_flag == true && utilities::check_delete(argv[4]) == true )
						{
							remove(full_path);
						}
					}
				}
				else
				{
					std::cout << "Error in opening file: " << dirent_name << std::endl;
					exit(1);
				}

				// ===============================
				// Recurse if directory.
				// ===============================
				//try to open current_directory. If null, it's just a file
				DIR* child_directory_ptr = opendir(full_path); //to check whether it is a file or current_directory
				if (child_directory_ptr != NULL)
				{
					//this is a current_directory
					//close the stream, because we will reopen it in the recursive call.
					closedir(child_directory_ptr);
					read_subi(full_path, i_node, argv, argc);
				}
				delete(full_path);
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

option utilities::parse_option(char* arg)
{
	//This function parses the option passed. If option is not recognized, an error flag is returned.

	if (arg[0] != '-')
	{
		//no dash found
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
	else if (strcmp(parsed_option, "delete") == 0)
	{
		return option::DELETE;
	}
	else
	{
		return option::ERR;
	}
}

bool utilities::check_delete(char* option_entered)
{
	option o_option_entered = parse_option(option_entered);
	if (o_option_entered == option::DELETE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

