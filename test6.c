#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
int main(int argc, char *argv[]) {
	char cline[67];
	char label[9];
	char others[58];
	char *cptr = NULL;
	FILE *rfd, *wfd; //read & write file descriptor
	if(argc != 3) {
		printf("Usage: %s srcfile \n", argv[0]);
		exit(0);
	}
	if((rfd = fopen(argv[1], "r")) == NULL) { //srcfile open
		fprintf(stderr, "%s %s: cannot open for reading: %s\n", argv[0], argv[1], strerror(errno));
		exit(0);
	}
	if((wfd = fopen(argv[2], "w")) == NULL) {
		fprintf(stderr, "%s %s: cannot open for reading: %s\n", argv[0], argv[1], strerror(errno));
	}
	int start = 997;
	while(fgets(cline, 67, rfd) > 0) { //get a line from srcfile
		cptr = cline;
		start += 3;
		if(*cptr != ' ' && *cptr != '\'' && *cptr != '\t') { //if label exist
			int c = 0;
			while(*cptr != '\n') {
				if(*cptr == ' ' && c == 0) {
					fprintf(wfd, ",");
					c++;
				}
				fprintf(wfd, "%c", *cptr++);
			}
			fprintf(wfd, " : %d\n", start);
		} 
	}
	fclose(rfd); //srcfile close
	fclose(wfd);
	return 0;
}
