#include <stdio.h>
#include<string.h>
//#include<stdbool.h>
#define MAX_N 26
#define MAX_T 2048
typedef struct {
	char id;
	int c;
	int p;
	int d;
} Task;
int is_iddle(int c_rest[],int n_tasks){
	int iddle = 0,i;
	for(i = 0; i < n_tasks; ++i){
		if(c_rest[i] > 0)
			iddle = 0;
		else
			iddle = 1;	
	}
	printf("Got here, iddle = %d\n",iddle);
	return iddle;
}
int main(void){
	int n_tasks = 0, time =0, i =0,n_preemp = 0, n_ctx_stc =0, c_rest[MAX_N],chosen_task = 100,t = 0;
	Task task[MAX_N];
	char tsk_brd[MAX_T + 1];
	printf("############################\n");
	printf("# Welcome to LST Simulator #\n");
	printf("############################\n");
	while(1){
		//read
		printf("\n\nPlese insert the following parameters:\n\nNº of Tasks \nSimulation Time\n");
		scanf("%d %d", &n_tasks,&time);
		if((n_tasks == 0)||(time == 0))
			break;
		for(i = 0; i < n_tasks; i++){
			task[i].id = 'A' + i;
			printf("\nPlese insert the following parameters:\n\nComputing Time \nPeriod \nDeadline\n");
			scanf("%d %d %d", &(task[i].c),&(task[i].p),&(task[i].d));
			c_rest[i] = task[i].c;//initializes the first c_rest
		}
		printf("\nTasks added:	");
		for(i = 0; i < n_tasks; ++i){
			printf("T(%c) = (%d,%d,%d) ",task[i].id,task[i].c,task[i].p,task[i].d);
			if(i == 4)
				printf("\n");
		}
		printf("\n");		
		//running
		for(t = 0; t < time;++t){
			for(i = 0; i < n_tasks; ++i){
				if(is_iddle(c_rest,n_tasks) == 1){
					tsk_brd[t] = '.';
					printf("\n\t\t\t\ttsk_brd[%d] = %c",t,tsk_brd[t]);
				}
				if(((task[i].d - c_rest[i] - t) < chosen_task)&&(c_rest[i] > 0)){
					chosen_task = task[i].d - c_rest[i] - t;
					tsk_brd[t] = task[i].id;
					printf("\nc_rest[%d] before: %d\ttime = %d\ttsk_brd[%d] = %c",i,c_rest[i],t,t,tsk_brd[t]);
					c_rest[i] = c_rest[i] - 1;
					printf("\nc_rest[%d]  after: %d\ttime = %d",i,c_rest[i],t);
				}
				if((c_rest[i] == 0)&&(t == task[i].d))
					c_rest[i] = task[i].c;
			}
		}
		//results
		printf("\nTask-board:\n %s \nP:  %d TC: %d \n\n",tsk_brd,n_preemp,n_ctx_stc);
	}
	return 0;
}
