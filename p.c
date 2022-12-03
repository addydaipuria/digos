
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define _POSIX_C_SOURCE 199309L
#include<time.h>
#include <stdlib.h>
#include<unistd.h>
struct timespec time1,time2,time3,time4,time5,time6;
int count(){
    unsigned long var1=1;
    int i=1;
    while(i<=32){
        var1=var1*2;
        i++;
    }
    return var1;
}
void *countA(void *j){
  unsigned long x=0;
  unsigned long z=count();
  clock_gettime(CLOCK_MONOTONIC,&time1);
  unsigned long bzt=z-x;
  while(x<z){
    x++;
  }
  clock_gettime(CLOCK_MONOTONIC,&time2);
  printf("%lf sec \n", (double)(time2.tv_sec-time1.tv_sec) + ((double)(time2.tv_nsec-time1.tv_nsec)/1000000000L));
}
void *countB(void *j){
  unsigned long kaka=0;
  unsigned long kak=count();
  clock_gettime(CLOCK_MONOTONIC,&time3);
  unsigned long bzz=kak-kaka;
  while(kaka<bzz){
    kaka++;
  }
  clock_gettime(CLOCK_MONOTONIC,&time4);
  printf("%lf sec \n", (double)(time4.tv_sec-time3.tv_sec) + ((double)(time4.tv_nsec-time3.tv_nsec)/1000000000L));
}
void *countC(void *j){
  unsigned long kaka=0;
  unsigned long kak=count();
  clock_gettime(CLOCK_MONOTONIC,&time5);
  unsigned long z=kak-kaka;
  while(kaka<z){
    kaka++;
  }
  clock_gettime(CLOCK_MONOTONIC,&time6);
  printf("%lf sec \n", (double)(time6.tv_sec-time5.tv_sec) + ((double)(time6.tv_nsec-time5.tv_nsec)/1000000000L));
}
void thread1(pthread_attr_t t_1,struct sched_param sched1){
sched1.sched_priority = 0;
  // sched2.sched_priority = 10;
  pthread_attr_init(&t_1);
  pthread_attr_setinheritsched(&t_1, PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&t_1, SCHED_OTHER);
  pthread_attr_setschedparam(&t_1, &sched1); 


}
void thread2(pthread_attr_t t_2,struct sched_param sched2){
  // sched1.sched_priority = 0;
  sched2.sched_priority = 10;
  pthread_attr_init(&t_2);
  pthread_attr_setinheritsched(&t_2, PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&t_2, SCHED_FIFO);
  pthread_attr_setschedparam(&t_2, &sched2); 

}
void thread3(pthread_attr_t t_3,struct sched_param sched2){
  // sched1.sched_priority = 0;
  sched2.sched_priority = 10;
  pthread_attr_init(&t_3);
  pthread_attr_setinheritsched(&t_3, PTHREAD_EXPLICIT_SCHED);
  pthread_attr_setschedpolicy(&t_3, SCHED_RR);
  pthread_attr_setschedparam(&t_3, &sched2); 

}
int main (){
  count();
  unsigned long papa =count();
  pthread_t t1,t2,t3;
  pthread_attr_t t_1,t_2,t_3;
  struct sched_param sched1,sched2; 
  // sched1.sched_priority = 0;
  // sched2.sched_priority = 10;
  thread1(t_1,sched1);
  pthread_create(&t1,&t_1,&countA,NULL);
  thread2(t_2,sched2);
  pthread_create(&t2,&t_2,&countB,NULL);
  thread1(t_3,sched2);
  pthread_create(&t3,&t_3,&countC,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);
}


