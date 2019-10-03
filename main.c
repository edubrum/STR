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
Task mem;
Task task[MAX_N];
int n_preemp = 0,n_ctx_switch = 0;

int find_act_deadline(Task *task,int i,int t){
	int n =0;
	while((task[i].d + task[i].p*n)<= t)
		n++;
	return task[i].d + task[i].p*n;
}
int find_act_period(Task *task,int i, int t){
	int n =0;
	while((task[i].p*n)<= t)
		n++;
	return task[i].p*n;
}

void rest_c(Task *task, int i,int t){
	int p = find_act_period(task,i,t);
	printf("$ P of %c is: %d $ ",task[i].id,p);
	if((task[i].c_now == 0)&&(t == p - task[i].p))
		task[i].c_now = task[i].c;
}

void lst_sched(Task *task, int i,int t,int n_tasks){
	task[i].slack = find_act_deadline(task,i,t) - task[i].c_now - t;
	printf(" L[%d]= d:%d - c:%d - t:%d = %d ## ",i,find_act_deadline(task,i,t),task[i].c_now,t,task[i].slack);
	if((task[i].slack < scheduler.slack)||((task[i].slack == scheduler.slack)&&( task[i].priority < scheduler.priority))){
		if(task[i].c_now > 0){
			scheduler = task[i];
			scheduler.d = find_act_deadline(task,i,t);
		}
	}
	for(int j =0; j < n_tasks;j++){
		if((task[j].slack == task[i].slack) && (i != j)){
			if((task[i].priority < task[j].priority))
				scheduler = task[i];
			else 
				scheduler = task[j];			
		}
	}
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
		}
		printf("\nTasks added: ");
		for(i = 0; i < n_tasks; i++){
			printf("T(%c) = [(C:%d);(P:%d);(D:%d)] ",task[i].id,task[i].c,task[i].p,task[i].d);
			//if((i % 2) == 0)
			//	printf("\n              ");
		}
		printf("\n");		
		//running
		for(t = 0; t <= time;t++){
			scheduler.slack = time;
			mem = scheduler;
			for(i = 0; i< n_tasks; i++){
				rest_c(task,i,t);
			}
			if(is_iddle(task,n_tasks)){
				tsk_brd[t] = '.';
				scheduler.id = '.';
				scheduler.c = 0;
				scheduler.p = 0;			
			}
			else{
				for(i = 0; i < n_tasks; i++) 
					lst_sched(task,i,t,n_tasks);
				for(i = 0; i < n_tasks; i++) 
					if(scheduler.id == task[i].id)
						task[i].c_now--;			
			}
			//printf("Mem: %c %d %d ", mem.id, mem.c_now,mem.d);
			//printf("Scheduler: %c %d %d ##", scheduler.id, scheduler.c_now,scheduler.d);
			if(t > 0){
				if(mem.id != scheduler.id)
					n_ctx_switch++;
					if(mem.c_now != 0)
						n_preemp++;
			}	
			printf("T: %d  S: %c \n\n", t,scheduler.id);
			tsk_brd[t] = scheduler.id;
		}
	//results
	printf("\nTask-board: %s \nP:  %d TC: %d \n\n",tsk_brd,n_preemp,n_ctx_switch);
	}
	return 0;
}


