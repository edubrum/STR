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
	int slack;
	int priority;
} Task;

Task scheduler;
Task task[MAX_N];
int n_preemp = 0,n_ctx_switch = 0;

int find_act_deadline(Task *task,int i,int t){
	int n =0;
	while((task[i].d + task[i].p*n)<= t){
		n++;
	}
	return task[i].d + task[i].p*n;
}


void rest_c(Task *task, int i,int t){
	if((task[i].c_now == 0)&&(t == find_act_deadline(task,i,t)))
		task[i].c_now = task[i].c;
}


void lst_sched(Task *task, int i,int t){
	int d = find_act_deadline(task,i,t);
	task[i].slack = d - task[i].c_now - t;
	printf("slack: %d d: %d",task[i].slack,d);
	if((task[i].slack < scheduler.slack)||((task[i].slack == scheduler.slack)&&( task[i].priority < scheduler.priority))){
		scheduler.slack = task[i].slack;
		scheduler.id = task[i].id;
		scheduler.priority = task[i].priority;
		task[i].c_now = task[i].c_now -1;
	}
}

int find_act_period(Task *task,int i, int t){
	int n =0;
	while((task[i].p*n)<= t){
		n++;
	}
	return task[i].p*n;
}

int is_iddle( Task *task,int n_tasks){
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


int main(void){
	int n_tasks = 0, time =0, i,t;
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
			scheduler.slack = task[i].slack;
			scheduler.id = task[i].id;
			scheduler.priority = task[i].priority;
			scheduler.c_now = task[i].c_now;
		}
		printf("\nTasks added: ");
		for(i = 0; i < n_tasks; ++i){
			printf("T(%c) = [(C:%d);(P:%d);(D:%d)] ",task[i].id,task[i].c,task[i].p,task[i].d);
			if((i % 2) != 0)
				printf("\n              ");
		}
		printf("\n");		
		//running
		for(t = 0; t <= time;t++){
			for(i = 0; i< n_tasks; i++){
				rest_c(task,i,t);
			}
			if(is_iddle(task,n_tasks) == 1)
				tsk_brd[t] = '.';
			else{
				char prev_process = scheduler.id;
				int last_c_now = scheduler.c_now;
				for(i = 0; i < n_tasks; i++) {
					lst_sched(task,i,t);
					printf("c_now[%d]: %d slack[%d]: %d ",i,task[i].c_now,i,task[i].slack);
				}
				if(prev_process != scheduler.id){
					n_preemp++;
					if(last_c_now != 0)
						n_ctx_switch++;
				}
			}
			printf("T: %d  S: %c \n", t,scheduler.id);
			tsk_brd[t] = scheduler.id;
		}
	//results
	printf("Got here  \n");
	printf("\nTask-board: %s \nP:  %d TC: %d \n\n",tsk_brd,n_preemp,n_ctx_switch);
	}
	return 0;
}


