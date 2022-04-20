// utilities.h: Include file for standard system include files,
// or project specific include files.

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <time.h>
#include <math.h>

enum option
{
	ERR = -1,
	NAME = 0,
	MMIN = 1,
	INUM = 2,
	DELETE = 3
};

namespace utilities
{
	void read_sub(char* current_directory);
	void read_subn(char* current_directory, char* file_name, char* argv[], int argc);
	void read_subm(char* current_directory, char* n_mins, char* argv[], int argc);
	void read_subi(char* current_directory, char* i_node, char* argv[], int argc);
	option parse_option(char* arg);
	bool check_delete(char* option_entered);
}
