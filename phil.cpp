#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
using namespace std;

int n;
sem_t chopstick[100];

void *eat(void *arg)
{
	int f=*((int*)arg);
	//int t=rand()%10;
	//for(int i=0;i<t;i++)
	//{
	   usleep(rand()%5);
	   sem_wait(&chopstick[f]);
	   sem_wait(&chopstick[(f+1)%n]);
	   //critical section
	   cout<<"philosopher:"<<f<<" eating"<<endl;
	   usleep(rand()%5);
	   cout<<"philosopher:"<<f<<" thinking"<<endl;
	   sem_post(&chopstick[f]);
	   sem_post(&chopstick[(f+1)%n]);

	//}
}
int main()
{
	 int id[50];
    cout<<"enter the no of philosophers\n";
    cin>>n;
	pthread_t phil[n];
	for(int i=0; i<n; i++)
       id[i] = i;
	for(int i=0;i<n;i++)
	  sem_init(&chopstick[i],0,1);
	for(int i=0;i<n;i++)
	  pthread_create(&phil[i],NULL,eat,id+i);
	for(int i=0;i<n;i++)
	  pthread_join(phil[i],NULL);   
}
