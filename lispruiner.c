#include <stdio.h>
#include "lispruiner.h"

short unsigned int inArgPos(const char* argu, int argc, char* argv[])
/*
If an argument is in argv[], return its position, else return 0
*/
{
	if (argc == 1) return 0; // no arguments

	int i;
	for (i = 1 ; i < argc ; i++)
	{
		if (strcmp(argu,argv[i]) == 0) // argu = argv[i]
		{
			return i;
		}
	}
	return 0;
}

void helpDisplay()
{
    printf("LispRuiner, by Adrien Laporte\n\n");

    printf("Usage : lispruiner [OPTIONS] file\n\n");
    printf("\t-h,\t--help\t: show this message\n");
    printf("\t\t-f\t: force ruining the file\n");
    printf("\t\t-q\t: quiet mode\n");
    printf("\t\t-V\t: verbose mode\n");
    printf("\t\t-F\t: same as -qf\n");
    printf("\t\t-v\t: show version info\n");
    printf("\n");
    printf("\"With Great Power Comes Great Responsibility\"\n");
    exit(0);
}

void shortHelp()
{
    printf("Type \'-h\' or \'--help\' for help\n");
}

void versionDisplay()
{
    printf("Version : %s\n",__DATE__);
    exit(0);
}

void ruinFile(FILE* file, int verbose)
{
    int n_tab = 0;
    int n_par = 0;
    int n_quo = 0;
    char current_char = 0;
    do //until the end of the file
    {
        current_char = fgetc(file); //read the character
        if (current_char == '(' || current_char == ')' || current_char == '\'' || current_char == '\t') //Character found !
        {
            if (current_char == '(')
                n_par++;
            else if (current_char == '\'')
                n_quo++;
            else if (current_char == '\t')
                n_tab++;

            fseek(file, -1, SEEK_CUR);//One character before
            fprintf(file, "%c", '\b');//replace with del
        }
    } while (current_char != EOF);

    if (verbose)
    {
        printf("Ruined parenthesis\t: %6d\n", n_par);
        printf("Ruined \'\t\t: %6d\n", n_quo);
        printf("Ruined tabulations\t: %6d\n", n_tab);
    }
}
