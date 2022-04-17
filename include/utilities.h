// find_command.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

enum option
{
	ERR = -1,
	NAME = 0,
	MMIN = 1,
	INUM = 2
};

void read_sub(char* directory);
void read_subn(char* directory, char* file_name);
void read_subm(char* directory, time_t n_mins);
void read_subi(char* directory, ino_t i_node);
option parse_option(char* arg);