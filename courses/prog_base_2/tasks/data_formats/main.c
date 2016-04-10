#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"
#include "admin.h"



// gcc main.c cJSON.c -lm
int main() {
    FILE * fr = fopen("data.json", "r");
	char line[100];
	char text[1000];
	while(fgets(line, 100, fr) != NULL) {  // read file
        strcat(text, line);
    }
	admin_t ** admins = parse(text);
	admin_print(admins[0]);
	admin_print(admins[1]);
    admin_free(admins[0]);
    admin_free(admins[1]);
	fclose(fr);
	return 0;
}
