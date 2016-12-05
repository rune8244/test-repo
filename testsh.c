#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX	500
#define Hist_cnt	500
#define LF	10


//divide input command
int parsingCommand(char *cmd, char *argv[]){

	int i=0;

	//... .... argv. ..
	argv[i++] = strtok(cmd, "\t \n");
	//... .... argv. ..
	while (i < MAX && (argv[i++] = strtok(NULL, "\t \n")) != NULL );

	//.. .. ... ..
	if (argv[0] == NULL) return 1;
	//. .. '!'. .. (ex. !vi, !gcc) ....
	if (argv[0][0] == '!') return 0;
	//... .... .. (argc)
	else return i-1;

}

int cd(int argc, char *argv[]) // CD
{
	if(argc==1)
		chdir(getenv("HOME"));
	else if(argc==2)
	{
		if(chdir(argv[1]))
			printf("%s is uncorrect directory\n", argv[1]);
	}
	else
		printf("Input correct command\n");

	return 0;
}

int init_history(char *history[]) // 히스토리 초기화
{
		int a=0;

		for(a=0; a<Hist_cnt; a++)
		{
			free(history[a]);
			history[a] = NULL;
		}
		return 0;
}

void sig_handler(int signo){

	printf("\n");
	signal(SIGINT, sig_handler);
}

int main()
{
	char cmd[MAX] = "\n";
	char *argv[MAX];	//char argv
	int h, p, i, t;	//p : argc. ..
	char *history[Hist_cnt];
	int h_cnt = 0;
	//h : .... .. ... ..

	printf("*****************************************\n");
	printf("	Team's test shell\n");
	printf("	=================\n\n");
	printf(" if you want to exit, type \"exit\"\n");
	printf("*****************************************\n");

	signal(SIGINT, sig_handler);
	
	for (t=0; t<Hist_cnt; t++)
		history[t] = NULL;

	while(1){
		//Prompt ..
		fprintf(stdout, "Project > ");
		//.. ..
		fgets(cmd, MAX, stdin);

		//.... '\n' ..
		if(feof(stdin)){
			fprintf(stdout, "\n");
			return;
		}

		history[h_cnt++] = strdup(cmd);

		if(!strcmp(cmd, "\n")) continue;
		else{

		//Call parsing funtion
		p = parsingCommand(cmd, argv);

		//... ..
		h = handleCommand(p, argv, history, h_cnt);

		strcpy(cmd, "\n");
		}

	}
	return 0;
}
