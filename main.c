#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lispruiner.h"
#include <unistd.h> //for getopt


int main (int argc, char* argv[])
{
    int force = 0;
    int quiet = 0;
    int verbose = 0;

    if (argc == 1) //No argv
    {
        shortHelp();
        return 1;
    }

    if (inArgPos("--help", argc, argv)) //Typed --help
    {
        helpDisplay();
        return 0;
    }

    int c;
    opterr = 0;
    while ((c = getopt (argc, argv, "hfqFvV")) != -1)
        switch (c)
            {
                case 'f':
                    force = 1;
                    break;
                case 'q':
                    quiet = 1;
                    verbose = 0;
                    break;
                case 'V':
                    verbose = 1;
                    quiet = 0;
                    break;
                case 'F':
                    force = 1;
                    quiet = 1;
                    break;
                case 'v':
                    versionDisplay();
                    break;
                case 'h':
                    helpDisplay();
                    break;
                case '?':
                    if (isprint (optopt))
                    {
                        fprintf (stderr, "Unknown option `-%c'\n", optopt);
                        shortHelp();
                    }
                    else
                    {
                        fprintf (stderr, "Unknown option character `\\x%x'\n", optopt);
                        shortHelp();
                    }
                return 1;
                default:
                    abort ();
            }
    //printf("%d %d\n", optind, argc); //debug
    if ((argc - optind) != 1)
    {
        printf("lispruiner requires only one non-option argument\n");
        shortHelp();
        return 1;
    }

    //Let the fun begin !
    FILE* lispfile = NULL;
    lispfile = fopen(argv[optind],"r+"); //last arg is the file
    if (lispfile == NULL)
    {
        if (!(quiet))
            printf("\'%s\' : no such file or directory\n",argv[optind]);
        return 1;
    }
    else
    {
        if (force == 0) //force suppression not set, ask to confirm
        {
            char choice;
            printf("You're about to ruin \'%s\',\nDo you want to continue ? (y/n)\n> ",argv[optind]);
            scanf("%c",&choice);
            if (choice != 'y')
            {
                printf("Abortion\n");
                return 0;
            }
        }

        ruinFile(lispfile, verbose);

        fclose(lispfile);
        if (!(quiet))
            printf("File \'%s\' Ruined !\n",argv[optind]);
    }

	return 0;
}
