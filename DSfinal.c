#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ScoreLinks {
	int burstTime;
	int arriveTime;
	int doing;
	char ID[20];
	struct ScoreLinks * Link;
}scType;

typedef struct qnode{
	char ID[10];
	int burstTime;
	int arriveTime;
	int doing;
	int exiting;
	struct qnode *next;
}Qtype;

typedef struct {
	Qtype *front;
	Qtype *rear;
	int size;
}queue;

void add(scType **, int,char[],int);
void add1(scType **, int,char[],int,int);
void printScores(scType *);
void addQFromOrderList(queue*,scType *);
void FCFS(queue*);
void NSJF(queue*);
void RR(queue*);
void PSJF(queue*);
void AA(queue *,queue *,int,float,int);
void OrderQ(queue*);
void deQ(queue*);
void newQ(queue*);

int main(){

	char ID[10];
	scType * A = NULL,*B = NULL;
	int burstTime,arriveTime,total=0,chose;
	queue Q1,Q2,Q3,Q4;
	newQ(&Q1);newQ(&Q2);newQ(&Q3);newQ(&Q4);
	FILE *fp = fopen("test.txt", "r");
	while ( fscanf(fp, "%d", &burstTime) != EOF ) {
		fscanf(fp, "%s", ID);
		fscanf(fp, "%d", &arriveTime);
		add(&A, burstTime,ID,arriveTime);
		//add1(&B, burstTime,ID,arriveTime);
		total = total + burstTime;
	}
	while(chose!=0)
	{
	printf("chose:(1)NSJF(2)FCFS(3)RR(4)PSJF(0)Exit\nEnter:");
	scanf("%d",&chose);
	if(chose==2)
	{
	printf("FCFS:\n");
	addQFromOrderList(&Q1,A);
	FCFS(&Q1);
	}
	if(chose==1)
	{
	printf("\nNSJF:\n");
	addQFromOrderList(&Q2,A);
	NSJF(&Q2);
	}
	if(chose==3)
	{
	printf("\nRR:\n");
	addQFromOrderList(&Q3,A);
	RR(&Q3);
	}
	if(chose==4)
	{
	printf("\nPSJF:\n");
	addQFromOrderList(&Q4,A);
	PSJF(&Q4);
	}
	}
}

void deQ(queue *q)
{
	Qtype *t;
	t = q->front;
	q->front = t->next;
	free(t);
	q->size--;

	if(q->size == 0)
		q->rear = NULL;
}

void add(scType * * L, int burstTime,char ID[],int arriveTime)
{
	scType * N, * T;
	N = malloc(sizeof(scType));
	N->burstTime = burstTime;
	N->arriveTime = arriveTime;
	N->doing = burstTime;
	strcpy(N->ID,ID);
	N->Link = NULL;

	if (* L == NULL)
		* L = N;
	else {
		if (((*L)->arriveTime) >= (N->arriveTime))
                {
                    T = *L;
                    *L = N;
                    (*L)->Link = T;
                    N = malloc(sizeof(scType));
                    N->Link = NULL;
                }
                else
                {
                    T = *L;
                    while ((T != NULL) && ((N->arriveTime) > (T->arriveTime)))
                    {
                      if ((T->Link != NULL) && ((N->arriveTime) <= (T->Link->arriveTime)))
                        {
                            N->Link = T->Link;
                            T->Link = N;
                            break;
                        }
                        else if (T->Link == NULL)
                        {
                            T->Link = N;
                            break;
                        }
                        T = T->Link;
                    }

                    N = malloc(sizeof(scType));
                    N->Link = NULL;
                }
	}
}

void add1(scType * * L, int burstTime,char ID[],int arriveTime,int doing)
{
	scType * N, * T;
	N = malloc(sizeof(scType));
	N->burstTime = burstTime;
	N->arriveTime = arriveTime;
	N->doing = doing;
	strcpy(N->ID,ID);
	N->Link = NULL;

	if (* L == NULL)
		* L = N;
	else {
		if (((*L)->burstTime) >= (N->burstTime))
                {
                    T = *L;
                    *L = N;
                    (*L)->Link = T;
                    N = malloc(sizeof(scType));
                    N->Link = NULL;
                }
                else
                {
                    T = *L;
                    while ((T != NULL) && ((N->burstTime) > (T->burstTime)))
                    {
                      if ((T->Link != NULL) && ((N->burstTime) <= (T->Link->burstTime)))
                        {
                            N->Link = T->Link;
                            T->Link = N;
                            break;
                        }
                        else if (T->Link == NULL)
                        {
                            T->Link = N;
                            break;
                        }
                        T = T->Link;
                    }

                    N = malloc(sizeof(scType));
                    N->Link = NULL;
                }
	}
}

void newQ(queue*q)
{
	q->front = NULL;
	q->rear = NULL;
	q->size = 0;
}

void addQFromOrderList(queue *q,scType * L)
{
	if(q->size==0)
	{
	q->rear = malloc(sizeof(Qtype));
	q->front = q->rear;
	}
	else
	{
	q->rear->next = malloc(sizeof(Qtype));
	q->rear = q->rear->next;
	}
	q->rear->burstTime =L->burstTime;
	q->rear->arriveTime =L->arriveTime;
	q->rear->doing = L->doing;
	strcpy(q->rear->ID,L->ID);
	q->rear->next = NULL;
	q->size++;
	if(L->Link != NULL)
	addQFromOrderList(q,L->Link);
}

void OrderQ(queue *q)
{
	scType * L;
	scType * N = NULL;
	L = malloc(sizeof(scType));
	while(q->size>0)
	{
	L = malloc(sizeof(scType));
	L->burstTime=q->front->burstTime;
	L->arriveTime=q->front->arriveTime;
	L->doing = q->front->doing;
	strcpy(L->ID,q->front->ID);
	add1(&N, L->burstTime,L->ID,L->arriveTime,L->doing);
	deQ(q);
	}
	addQFromOrderList(q,N);
}

void addQ(queue *q,queue * T)
{
	if(q->size==0)
	{
	q->rear = malloc(sizeof(Qtype));
	q->front = q->rear;
	}
	else
	{
	q->rear->next = malloc(sizeof(Qtype));
	q->rear = q->rear->next;
	}
	q->rear->burstTime =T->front->burstTime;
	q->rear->arriveTime =T->front->arriveTime;
	q->rear->doing = T->front->doing;
	strcpy(q->rear->ID,T->front->ID);
	q->rear->next = NULL;
	q->size++;
}

void FCFS(queue* Q)
{
	int time=0,i=1,waitTime=0;
	float averagetime=0;
	int size;
	size = Q->size;
	time = Q->front->arriveTime;
	while(Q->size>0)
	{
	if(time<Q->front->arriveTime)
	{
	time = Q->front->arriveTime;
	printf("\n%d.%s:\narrivealTime:%d\n",i,Q->front->ID,Q->front->arriveTime);
	time = Q->front->burstTime+Q->front->arriveTime;
	waitTime = time-Q->front->arriveTime-Q->front->burstTime;
	averagetime = averagetime + waitTime;
	printf("Exit time:%d\n",time);
	printf("Waiting time:%d\n",waitTime);
	deQ(Q);
	i++;
	}
	else{
	time = Q->front->burstTime+time;
	printf("\n%d.%s:\narrivealTime:%d\n",i,Q->front->ID,Q->front->arriveTime);
	waitTime = time-Q->front->arriveTime-Q->front->burstTime;
	averagetime = averagetime + waitTime;
	printf("Exit time:%d\n",time);
	printf("Waiting time:%d\n",waitTime);
	deQ(Q);
	i++;}
	}
	printf("\nAverage waiting time:%f\n",averagetime/size);
}

void NSJF(queue* q)
{
	int time=0,i=1,waitTime=0,k=0;
	float averagetime=0;
	int size;
	size = q->size;
	queue readyQ;
	newQ(&readyQ);
	addQ(&readyQ,q);
	time = readyQ.front->arriveTime;
	deQ(q);
	while(i<size+1)
	{
	if(readyQ.size==0&&q->size!=0)
	time = q->front->arriveTime;
	if(readyQ.size>=1)
	{
	waitTime = time-readyQ.front->arriveTime;
	time = readyQ.front->burstTime+time;
	printf("\n%d.%s:\narrivealTime:%d\n",i,readyQ.front->ID,readyQ.front->arriveTime);
	printf("Exit time:%d\n",time);
	printf("Waiting time:%d\n",waitTime);
	averagetime = averagetime + waitTime;
	deQ(&readyQ);
	i++;
	}
	if((q->front!=NULL)&&(q->front->arriveTime<=time))
	{
	while((q->front!=NULL)&&(q->front->arriveTime<=time))
	{
	addQ(&readyQ,q);
	OrderQ(&readyQ);
	deQ(q);
	}
	}

	}
	printf("\nAverage waiting time:%f\n",averagetime/size);
}

void RR(queue * Q)
{
	int time=0,i=1,waitTime=0;
	float averagetime=0;
	int size;
	queue readyQ;
	newQ(&readyQ);
	size = Q->size;
	addQ(&readyQ,Q);
	time=readyQ.front->arriveTime;
	deQ(Q);
	while(1)
	{
	if(readyQ.size>=1)
	{
		if(readyQ.front->burstTime>=10)
		{
		time=10+time;
		while((Q->front!=NULL)&&(Q->front->arriveTime<=time))
		{
		addQ(&readyQ,Q);
		deQ(Q);
		}
		printf("%d:%s=",i,readyQ.front->ID);
		printf("%d->%d\n",readyQ.front->burstTime,readyQ.front->burstTime-10);
		printf("NOW:%d\n",time);
		readyQ.front->burstTime = readyQ.front->burstTime-10;
		addQ(&readyQ,&readyQ);
		deQ(&readyQ);
		i++;
		}
		else if(readyQ.front->burstTime<10)
		{
		time=readyQ.front->burstTime+time;
		printf("%d:%s=",i,readyQ.front->ID);
		printf("%d->%d\n",readyQ.front->burstTime,0);
		printf("NOW:%d\n",time);
		waitTime= time-readyQ.front->arriveTime-readyQ.front->doing;
		printf("\n%s:waiting time:%d\n",readyQ.front->ID,waitTime);
		averagetime = averagetime+waitTime;
		deQ(&readyQ);
		i++;
		}
	}
	if(readyQ.size==0){
	if((Q->front!=NULL)&&(Q->front->arriveTime<=time))
	{
	while((Q->front!=NULL)&&(Q->front->arriveTime<=time))
	{
	addQ(&readyQ,Q);
	deQ(Q);
	}
	}
	else
	time++;
	}
	if((Q->size==0)&&(readyQ.size==0))
	break;
	}
	printf("\nAverage waiting time:%f\n",averagetime/size);
}

void PSJF(queue * Q)
{
	int time=0,i=1,waitTime=0,k=0;
	float averagetime;
	int size;
	size = Q->size;
	queue readyQ;
	newQ(&readyQ);
	addQ(&readyQ,Q);
	time = readyQ.front->arriveTime;
	deQ(Q);
	AA(Q,&readyQ,time,averagetime,size);
	//k = averagetime;
	//printf("\nAverage waiting time:%f\n",averagetime);

}

void AA(queue * Q,queue * readyQ,int time,float averagetime,int size)
{
	int k,i=0;
	if(readyQ->size==0 && Q->size>0)
	{
	time = Q->front->arriveTime;
	}
	if((Q->front!=NULL)&&(Q->front->arriveTime<=time))
	{
		while((Q->front!=NULL)&&(Q->front->arriveTime<=time))
		{
		addQ(readyQ,Q);
		OrderQ(readyQ);
		deQ(Q);
		}
	}

	if(Q->front!=NULL)
	{
	k = Q->front->arriveTime;
	}

	if(time<k)
	{
		while(time<k&&readyQ->front->burstTime>0)
		{
		readyQ->front->burstTime--;
		printf("ID:%s,%d---",readyQ->front->ID,readyQ->front->burstTime);
		time++;
		printf("NOW:%d\n",time);
		}

		if(readyQ->front->burstTime>0)
		{
		addQ(readyQ,readyQ);
		deQ(readyQ);
		}

		if(readyQ->front->burstTime==0)
		{
		i= time-readyQ->front->arriveTime-readyQ->front->doing;
		printf("\n%s:waiting time:%d\n\n",readyQ->front->ID,i);
		deQ(readyQ);
		averagetime = averagetime+i;
		}

		//printf("\nAverage waiting time:%f\n",averagetime);
	}
	if(Q->size==0&&readyQ->size==0){
	printf("\nAverage waiting time:%f\n\n",averagetime/size);
	return;}
	//if(Q->size==0&&readyQ->size==0)
	//return;
	if(readyQ->size>0||Q->size>0)
	AA(Q,readyQ,time,averagetime,size);
}
