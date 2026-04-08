/*
 * Replace string in file
 * Auhor Alf Gisslen 2021-10-22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Syntax: %s <file to change>", argv[0]);
    }
    FILE *f;
    char *ch;
    char d1[2];
    char d2[2];
    f = fopen(argv[1], "r");
    // Check if file is found and opened
    if (f == NULL) {
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        exit(1);
    }
    // File opened  OK

	// Create tempfile
	char tempfile[255];
	strcpy(tempfile, argv[1]);
	strcat(tempfile, "_temp");
//	printf("New filename; %s\n", tempfile);
    FILE *f2 = fopen(tempfile, "w");
	// now, find line
    char buffer[80];
    ch = fgets(buffer, 200, f );

    while (ch != NULL) {
		if ((ch = strstr(buffer, "PGM_AMENDMENT_LEVEL")) != NULL) {
//			printf("Found: %s\n", ch);
			int alevel;
			char name[30];
			sscanf(ch, "%s %c%3i%c", name, d1, &alevel, d2);
			++alevel;
//			printf("Definition: %s\n", name);
//			printf("New level: %.3d\n", alevel);
			fprintf(f2, "#define %s \"%.3d\"\n", name, alevel);
		} else {
			fprintf(f2, buffer);
		}
		ch = fgets(buffer, 200, f );
    }
//	if (strlen(buffer) > 0) {
//		fprintf(f2, buffer);
//	}
    fclose(f);
    fclose(f2);
	
	remove(argv[1]);
	rename(tempfile, argv[1]);

    return 0;
}
