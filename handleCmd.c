//Command process
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define TRUE		1
#define FALSE		0
#define BUF_SIZE	100

//background
void cmd_back(int bp, char **argv)
{

	pid_t pid;	
	int exit_status, i;
	char **fw_argv;	//forward argv

	fw_argv = (char **)malloc(32 * sizeof(char *)); //.. ..
	for (i = 0; i<32; i++) //... ... ..
		fw_argv[i] = (char *)malloc(64 * sizeof(char)); //.. ..

	for (i = 0; i<bp; i++) {	// '&'. .....
		strcpy(fw_argv[i], argv[i]); //.... fw_argv. ..
	}

	fw_argv[bp] = '\0';	//'&'. .... .. ... ... ..
	if ((pid = fork()) == -1) {	//fork .. -> .. .... ..... ..
		printf("fork() error\n");
	}
	else if (pid == 0) {	//.. ..... ..
		if (fork() == 0) {	//fork ..
			printf("pid : %d", getpid());
			if (execvp(fw_argv[0], fw_argv) == -1) //fw_argv. ... ..
				if (strlen(fw_argv[0]) != 0)	//.. ... .... ...
					printf("The command did not come in (%s)\n", fw_argv[0]);
			exit(1);
		}
		else
		{
			exit(1);
		}
	}
	else {
		// ....... ... .. ..
		wait(&exit_status);
	}

	//.. ... ... ..
	for (i = 0; i<32; i++){
		free(fw_argv[i]);
	}
	free(fw_argv);
}

//... ..
int cmd_hist(char *history[], int num)
{
	int a;
	a = num;
	int hist_order = 0;

	do {
		if(history[a])
		{
			printf("%d %s\n", hist_order, history[a]);
			hist_order++;
		}
		a = (a + 1);
		a = a % 500;
	} while (a!=num);

	return 0;
}

int handleCommand(int argc, char * argv[], char *hist[], int h_cnt){
	int id, status, i;
	int buf[2] = {0,};

	//exit ... ... .. shell ..
	if (strncmp("exit", argv[0], 4) == 0) {
		printf("Bye!\n");
		exit(1);
	}

	//..... .... ..
	for ( i=0; i< argc; i++){
		if(strcmp(argv[i], "&") == 0){
			buf[0] = 1;	//case 1
			buf[1] = i;
		} else if(strcmp(argv[i], "history") == 0) {
			buf[0] = 2;
			buf[1] = i;
		}
	}

	switch (buf[0]){
		case 1:
			cmd_back(buf[1], argv);	//..... .... ..
			break;
		case 2:
			cmd_hist(hist, h_cnt);
			break;
		default:

			{

				if ((id = fork()) == 0){ 
					execvp(argv[0], argv);	//... ..
					_exit(0); 

				} else if (id < 0){	//fork() error

					fprintf(stderr, "fork failed\n");
					perror("handleCommand:");

				} else wait(&status);	// ....... ... .. ..
			}
	}
	return 1;  

}
