#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include "sudoku.h"
#include <queue>

std::queue<SDK*> *q1 = new std::queue<SDK*>;
std::queue<SDK*> *q2 = new std::queue<SDK*>;
pthread_cond_t cond_work;
pthread_cond_t cond_output;
pthread_mutex_t lock;
bool isready_work=false;
bool isready_output=false;
bool finish_input=false;
bool finish_output=false;
bool finish_js=false;
int total=0,sovle_total=0;

FILE* fp;

int64_t now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}
void *shuru(void *arg)
{
	   while(!finish_input){
		   pthread_mutex_lock(&lock); 
		   SDK *sdk=new SDK();
		   if(fgets(sdk->puzzle, sizeof sdk->puzzle, fp) != NULL){
			   total++;
			   input(sdk);
			//   printf("%s",sdk->puzzle);
			   q1->push(sdk);
			   q2->push(sdk);
			   if(!q1->empty()){
				   isready_work=true;
                                //   worklocked=false;
				 //   pthread_cond_signal(&cond_work);
                                
			   } 
                           pthread_mutex_unlock(&lock);
		   }
		   else {
                     finish_input=true;
                     pthread_mutex_unlock(&lock); 
                     pthread_exit(NULL);}
	   }
    pthread_exit(NULL);  
}
void *solve(void *arg) 
{
 //   int p=*(int*)arg;
    while(1){   
             /*   pthread_mutex_lock(&lock);
		while(!isready_work) {worklocked=true;pthread_cond_wait(&cond_work, &lock);}
                pthread_mutex_unlock(&lock);*/
		while(isready_work){
                        SDK *sdk=new SDK();
			if(!q1->empty()){
                             pthread_mutex_lock(&lock); 
                              sdk=q1->front();
                              q1->pop();
                              sovle_total++;   
                              pthread_mutex_unlock(&lock);                       
                              solve_sudoku_dancing_links(sdk);
                              sdk->flag=true;
                          /*       for(int i=0;i<N;i++)
                               printf("%d",sdk->answer[i]);
                               printf("   %d\n",p);*/
                               if(!q2->empty()){
                                      isready_output=true;
                                    //   outputlocked=false;
                                    //  pthread_cond_signal(&cond_output);    
                                }
			}
                        else isready_work=false;
		}
                if(sovle_total>=total&&finish_input) {finish_js=true;pthread_exit(NULL);}
	}
          pthread_exit(NULL);
}  
void *shuchu(void *arg)
{
   int sum=0;
    while(!finish_output){ 
          /*      pthread_mutex_lock(&lock);
		while(!isready_output) {outputlocked=true;pthread_cond_wait(&cond_output, &lock);}
                pthread_mutex_unlock(&lock); */
		while(isready_output){
                        SDK *sdk=new SDK();
			if(!q2->empty()){
                              sdk=q2->front();
                              if(sdk->flag==true){
                              q2->pop();
                              pthread_mutex_lock(&lock); 
                               sum++;
                            //   printf("%d:",sum);
                               for(int i=0;i<N;i++)
                               printf("%d",sdk->answer[i]);
                               printf("\n");
                               pthread_mutex_unlock(&lock); 
                            }
                             else isready_output=false;
			}
                        else {isready_output=false;}
		}
                 if(sum>=total&&finish_js) pthread_exit(NULL); 
	}  
       pthread_exit(NULL);
}
 
int main()
{
	init_neighbors();
	char file[128];
	int p=scanf("%s",file);
	fp = fopen(file, "r");
    pthread_t work_thread[WORK_THREADNUM];
    pthread_t out_thread[OUT_THREADNUM];
    pthread_t in_thread[IN_THREADNUM];  
  int64_t start = now();
	for (int i = 0; i<IN_THREADNUM; i++)
      int temp=pthread_create(&in_thread[i], NULL, shuru, NULL);
         pthread_join(in_thread[0], NULL);
	for (int i = 0; i<WORK_THREADNUM; i++)
      int temp=pthread_create(&work_thread[i], NULL, solve, (void*)&i);
           pthread_join(work_thread[0], NULL);
           pthread_join(work_thread[1], NULL);	
	for (int i = 0; i<OUT_THREADNUM; i++)
      int temp=pthread_create(&out_thread[i], NULL, shuchu, NULL);
           pthread_join(out_thread[0], NULL);
  int64_t end = now();
  double sec = (end-start)/1000000.0;
  printf("%f sec %f ms each %d\n", sec, 1000*sec/total, sovle_total);
  return 0;
}
  /*
  char puzzle[128];
  int total_solved = 0;
  int total = 0;
  bool (*solve)(int) =solve_sudoku_dancing_links;
  int64_t start = now();
  while (fgets(puzzle, sizeof puzzle, fp) != NULL) {
    if (strlen(puzzle) >= N) {
      ++total;
      input(puzzle);
      if (solve(0)) {
        ++total_solved;
        if (!solved())
          assert(0);
      }
      else {
        printf("No: %s", puzzle);
      }
    }
    for(int i=0;i<N;i++)
    printf("%d",board[i]);
    printf("\n");
  }
  int64_t end = now();
  double sec = (end-start)/1000000.0;
  printf("%f sec %f ms each %d\n", sec, 1000*sec/total, total_solved);
  */
