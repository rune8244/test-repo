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

int history(char *history[], int num) // 히스토리 기능
{
		int a;
		a = num;
		int hist_order = 0;
		do
		{
			if(history[a])
			{
				printf("%d %s\n", hist_order, history[a]);
				hist_order++;
			}
			a = (a + 1);
			a = a %  Hist_cnt;
		} while (a!=num);
		return 0;
}

/*int init_history(char *history[]) // 히스토리 초기화
{
		int a=0;
		while(a<Hist_cnt)
		{
			free(history[a]);
			history[a] = NULL;
			a++;
		}

		return 0;
}*/
