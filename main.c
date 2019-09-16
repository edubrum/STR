#include <stdio.h>
#include<string.h>
#define MAX_N 26
#define MAX_T 2048
typedef struct {
	char id;
	int c;
	int p;
	int d;
	int c_now;
	int lack;
	int priority;
} Task;

int is_iddle(struct Task task[],int n_tasks){
	int i, iddle = 0;
	for(i =0; i< n_tasks;i++)
		if(task[i].c_now == 0)
			iddle++;
	if(iddle == n_tasks)
		iddle = 1;
	else
		iddle = 0;
	return iddle;
}

int find_act_period(){

}

int find _act_deadline(){

}

int main(void){
	int n_tasks = 0, time =0, i,n_preemp = 0,n_ctx_stc = 0,t;
	Task task[MAX_N];
	char tsk_brd[MAX_T + 1];
	printf("\n############################\n");
	printf("# Welcome to LST Simulator #\n");
	printf("############################\n");
	while(1){
		//read
		printf("\nPlese insert the following parameters:\n\nNº of Tasks \nSimulation Time\n");
		scanf("%d %d", &n_tasks,&time);
		if((n_tasks == 0)||(time == 0))
			break;
		for(i = 0; i < n_tasks; i++){
			task[i].id = 'A' + i;
			printf("\nPlese insert the following parameters:\n\nComputing Time \nPeriod \nDeadline\n");
			scanf("%d %d %d", &(task[i].c),&(task[i].p),&(task[i].d));
			task[i].c_now = task[i].c;//c_now changes throught time increment 
			task[i].priority = i+1;// priority is set by process arrival
		}
		printf("\nTasks added: ");
		for(i = 0; i < n_tasks; ++i){
			printf("T(%c) = [(C:%d);(P:%d);(D:%d)] ",task[i].id,task[i].c,task[i].p,task[i].d);
			if((i % 2) != 0)
				printf("\n              ");
		}
		printf("\n");		
		//running
		for(t = 0; t <= time;++t){
			if(is_iddle(task,n_tasks) == 1)
				tsk_brd[t] = '.';
			else{
				for(i = 0; i < n_tasks; ++i) {
							
				}
			}
		}
	}
	//results
	printf("\nTask-board: %s \nP:  %d TC: %d \n\n",tsk_brd,n_preemp,n_ctx_stc);
	
	return 0;
}
