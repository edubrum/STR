#include <stdio.h>
#include<string.h>
#define MAX_N 26
#define MAX_T 2048
typedef struct {
	char id;
	int c;
	int p;
	int d;
} Task;
int is_iddle(int c_rest[],int n_tasks){
	short iddle = 0,i;
	for(i = 0; i < n_tasks; ++i){
		if(c_rest[i] > 0)	iddle = 0;
		else 				iddle = 1;	
	}
	return iddle;
}
int main(void){
	int n_tasks = 0, time =0, i,n_preemp = 0, n_ctx_stc =0, c_rest[MAX_N], cur_d[MAX_N], a_slack, t_slack[MAX_N],t;
	Task task[MAX_N];
	char tsk_brd[MAX_T + 1],p_running;
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
			c_rest[i] = task[i].c;//initializes the first c_rest
		}
		printf("\nTasks added: ");
		for(i = 0; i < n_tasks; ++i){
			printf("T(%c) = [(C:%d);(P:%d);(D:%d)] ",task[i].id,task[i].c,task[i].p,task[i].d);
			if(i == 1)
				printf("\n              ");
		}
		printf("\n");		
		//running
		for(t = 0; t <= time;++t){
			for(i = 0; i < n_tasks; ++i)
				if((c_rest[i] == 0)&&((t % task[i].d) == 0))//check if a process crossed its P and C is ended
					c_rest[i] = task[i].c;
			if(is_iddle(c_rest,n_tasks) == 1)//check if processor is iddle
					tsk_brd[t] = '.';			//if yes, then insert dots that process
			else{
			short a_slack = 100;
			for(i = 0; i < n_tasks; ++i){
				//begin finding Di
				if(t < task[i].d)
					cur_d[i] = t;
				else{
					short s =0;
					while(t > cur_d[i]){
						if(t > (task[i].d + task[i].p*s))
							s++;
						else
							cur_d[i] = task[i].d + task[i].p*s;
					}
				}
					t_slack[i] = cur_d[i] - t - c_rest[i];
					if(t_slack[i] < a_slack){
						p_running = task[i].id;
						a_slack = t_slack[i];
					}
			}
			tsk_brd[t] = p_running;
			for(i = 0; i < n_tasks; ++i)//task running get Ci decreased
				if(p_running == task[i].id)
					c_rest[i]--;	
			}
		}
		//results
		printf("\nTask-board: %s \nP:  %d TC: %d \n\n",tsk_brd,n_preemp,n_ctx_stc);
	}
	return 0;
}
