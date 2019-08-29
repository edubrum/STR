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
int main(void){
	int n_tasks = 0, time =0;
	Task task[MAX_N];
	char tsk_brd[MAX_T + 1];
	int n_preemp = 0, n_ctx_stc =0; 
	while(1){
		//read
		scanf("%d %d", &n_tasks,&time);
		if((n == 0)||(t == 0))
			break;
		for(i = 0; i < n_tasks, ++i){
			task[i].id = 'A' + i;
			scanf("%d %d %d", &(task[i].id),&(task[i].p),&(task[i].d));
		}
		//running
		n_preemp =n_ctx_stc =0;
		result
		printf("%s \n %d %d %d \n\n",&tsk_brd,&n_preemp,&n_ctx_stc);
		
	}
	return 0;
}
