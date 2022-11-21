#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
	//printf("Made it here \n");
	
	setlogmask (LOG_UPTO (LOG_NOTICE));
	openlog("exampleprog", LOG_CONS, LOG_USER);
	setlogmask(LOG_UPTO(LOG_DEBUG));
	
	if(argc<3){
		printf("Not enough arguments \n");
		syslog(LOG_ERR, "Error: Not enough arguments.");
		closelog();
		exit(1);
	}
	
	
	
	int i = 0;
	FILE *f = fopen(argv[1], "w");
	
	if (f ==NULL){
		printf("Error opening file!\n");
		syslog(LOG_ERR, "Error opening file %s \n", argv[1]);
		closelog();
		exit(1);
	}
	
	fprintf(f,"%s\n", argv[2]);
	syslog(LOG_DEBUG, "Writing %s to file %s", argv[2], argv[1]);
	fclose(f);
	closelog();
	
	return 0;
}



