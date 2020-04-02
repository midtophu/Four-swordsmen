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
bool finish_js=false;
bool worklock=true,outputlock=true;
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
	      //     pthread_mutex_lock(&lock); 
		   SDK *sdk=new SDK();
		   if(fgets(sdk->puzzle, sizeof sdk->puzzle, fp) != NULL){
                           pthread_mutex_lock(&lock); 
			   total++;
			   input(sdk);
			//   printf("%s",sdk->puzzle);
                           
			   q1->push(sdk);
			   q2->push(sdk);
                           pthread_mutex_unlock(&lock); 
			   if(worklock){
				   isready_work=true;
                                   worklock=false;
			           pthread_cond_signal(&cond_work);
                                
			   } 
                     //      pthread_mutex_unlock(&lock);
		   }
		   else {
                 //    printf("杈撳叆绾跨▼閫€鍑篭n");
                     finish_input=true;
                     pthread_cond_signal(&cond_work);
                   //  pthread_mutex_unlock(&lock); 
                     pthread_exit(NULL);}
	   }
    pthread_exit(NULL);  
}
void *solve(void *arg) 
{
  //  int p=*(int*)arg;
    while(!finish_js){   
                pthread_mutex_lock(&lock);
		while(!isready_work) {worklock=true;pthread_cond_wait(&cond_work, &lock);}
               // pthread_mutex_unlock(&lock);
     
	        if(!q1->empty()){
                   SDK * sdk=q1->front();
                    q1->pop();
                    sovle_total++;
                    pthread_mutex_unlock(&lock);                      
                    solve_sudoku_dancing_links(sdk);
                    sdk->flag=true;
                 //   pthread_mutex_unlock(&lock); 
                  //  printf("%d\n",p);
                    if(outputlock&&q2->front()->flag==true){
                          isready_output=true;
                          outputlock=false;
                          pthread_cond_signal(&cond_output);    
                      }
	           }
                   else {isready_work=false;pthread_mutex_unlock(&lock); }
             //    pthread_mutex_unlock(&lock);
                if(sovle_total>=total&&finish_input) {
                //  printf("璁＄畻绾跨▼缁撴潫\n");
                finish_js=true; pthread_exit(NULL);}
	}
       return NULL;
}  
void *shuchu(void *arg)
{
   int sum=0;
    while(1){ 
               pthread_mutex_lock(&lock);
		while(!isready_output) {outputlock=true;pthread_cond_wait(&cond_output, &lock);}
                     //   SDK *sdk=new SDK();
			if(!q2->empty()){
                            SDK * sdk=q2->front();
                              if(sdk->flag==true){
                              q2->pop();
                               sum++;
                       //       printf("%d:",sum);
                               for(int i=0;i<N;i++)
                               fprintf(stdout,"%d",sdk->answer[i]);
                               fprintf(stdout,"\n");
                               delete sdk;
                            }
                             else isready_output=false; 
			}
                 pthread_mutex_unlock(&lock); 
                 if(sum>=total&&finish_js) {pthread_exit(NULL); }
	}  
       pthread_exit(NULL);
}
 
int main()
{
	init_neighbors();
	char file[128];
	int p=scanf("%s",file);
	fp = fopen(file, "r");
     pthread_mutex_init(&lock, 0);
     pthread_cond_init(&cond_work,0);
     pthread_cond_init(&cond_output,0);
    pthread_t work_thread[WORK_THREADNUM];
    pthread_t out_thread[OUT_THREADNUM];
    pthread_t in_thread[IN_THREADNUM];  
  int64_t start = now();
	for (int i = 0; i<IN_THREADNUM; i++)
      int temp=pthread_create(&in_thread[i], NULL, shuru, NULL);
           pthread_join(in_thread[0], NULL);
	for (int i = 0; i<WORK_THREADNUM; i++)
      int temp=pthread_create(&work_thread[i], NULL, solve, NULL);
           for (int i = 0; i<WORK_THREADNUM; i++)
           pthread_join(work_thread[i], NULL);
      /*     pthread_join(work_thread[0], NULL);
           pthread_join(work_thread[1], NULL);	
           pthread_join(work_thread[2], NULL);
           pthread_join(work_thread[3], NULL);	*/
	for (int i = 0; i<OUT_THREADNUM; i++)
      int temp=pthread_create(&out_thread[i], NULL, shuchu, NULL);
           pthread_join(out_thread[0], NULL);

  int64_t end = now();
  double sec = (end-start)/1000000.0;
 // fprintf(stdout,"%f sec %f ms each %d\n", sec, 1000*sec/total, sovle_total);
     delete q1;
     delete q2;
     pthread_mutex_destroy(&lock);
     pthread_cond_destroy(&cond_work);
     pthread_cond_destroy(&cond_output);
     
  return 0;
}
