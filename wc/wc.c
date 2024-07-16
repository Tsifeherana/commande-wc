#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include <string.h>
#include <wchar.h>

int count_bytes(FILE *f)
{	
	rewind(f);
	int c;
	int i;
	int caractere = 0;
	for (i = 0; c != EOF; i++)
	{
		c = fgetc(f);
		caractere++;
	}
	return (caractere-1);
}

int nbr_lignes(FILE *f)
{
	rewind(f);
	char mots[555];
	int count = 0;
	while (fgets(mots,555,f) != 0)
	{
		count++;
	}
	return count;
}

int nbr_chars(FILE *f)
{
	rewind(f);
	int countchar = 0;
	int c;
	while (!feof(f))
	{
		c = fgetc(f);
		if ((c & 0xC0) != 0x80 && c != EOF)
			countchar++;
	}
	return countchar;
}

int nbr_words(FILE *f)
{	
	rewind(f);
	int count = 0;
	char mots[555];
	while (1)
	{
		fgets(mots, 555, f);
		mots[strcspn(mots, "\n")] = '\0';
		char *temp = strtok(mots, " ");
		while (temp != NULL)
		{
			temp = strtok(NULL, " ");
			count++;
		}
		if (feof(f))
			break;
	}
	return count;
}

int maxLine(FILE *f)
{
	//variables 
	int i = 0;
	int max = 0;
	int j; 
	
	//loop
	while (!feof(f))
	{
		j = fgetc(f);
		if ((j & 0xC0) != 0x80 && (j != EOF) )
		{
			i++;
		}
		
		if (j == '\n')
		{
			i = 0;
		}
		
		if (i > max)
		{
			max = i;
		}
	}
	return (max);
}

void get_error(FILE *f)
{
	if (f == NULL)
	{
		printf("Erreur d'ouverture du fichier\n'");
		exit(-1);
	}
}
void options(int argc, char *argv[])
{
	//variables 
	FILE *f = NULL;
	f = fopen(argv[argc-1],"r");
	get_error(f);
	int j = 1;
	
	//wc sans paramètre
	rewind(f);
	if ( argc == 2 && strcmp(argv[1], argv[argc-1]) == 0) 
	{
		printf(" %d %d %d %s\n", nbr_lignes(f), nbr_words(f), count_bytes(f), argv[argc-1] );
	}
	else if (argc == 1 && strcmp(argv[0],argv[argc-1]) == 0)
	{
		while (1)
		{
			char mots[555];
			fgets(mots, 555, stdin);
			mots[strcspn(mots, "\n")] = '\0';
		}
	}
	//options
	while ( j < argc )
	{
		//options -c
		if (strcmp(argv[j],"-c") == 0 || strcmp(argv[j], "--bytes") == 0)
		{
			int bytes = count_bytes(f);
			printf("%d  %s\n", bytes, argv[argc-1]);
			rewind(f);
		}

		//options -l
		if (strcmp(argv[j],"-l") == 0 || strcmp(argv[j], "--lines") == 0)
		{
			int lines = nbr_lignes(f);
			printf("%d  %s\n", lines, argv[argc-1]);
			rewind(f);
		}

		//options -w
		if (strcmp(argv[j], "-w") == 0 || strcmp(argv[j], "--words") == 0)
		{
			int words = nbr_words(f);
			printf("%d  %s\n", words, argv[argc-1]);
			rewind(f);
		}

		//options -L
		if (strcmp(argv[j], "-L") == 0 || strcmp(argv[j], "--max-line-length") == 0)
		{
			int max = maxLine(f);
			printf("%d %s\n",max, argv[argc-1]);
			rewind(f);
		}

		//options -m
		if (strcmp(argv[j],"-m") == 0 || strcmp(argv[j],"--chars") == 0)
		{
			int chars = nbr_chars(f);
			printf("%d %s\n", chars, argv[argc-1]);
			rewind(f);
		}

		//options -h
		if (strcmp(argv[j], "-h") == 0 || strcmp(argv[j],"--help") == 0)
		{
			system("cat get_helpWC");
		}
		
		//itération
		j++;
	}
}







