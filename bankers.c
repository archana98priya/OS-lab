#include<stdio.h>

int p,r;

void calculate_need(int need[][r],int max[][r],int allot[][r] )
{
  int i,j;
  for(i=0;i<p;i++)
  {
    for(j=0;j<r;j++)
    {
      need[i][j]= max[i][j]-allot[i][j];
    }
  }

}

int safe(int process[],int avail[],int max[][r],int allot[][r],int need[][r])
{

  printf("abc\n");

  int i,j;

  calculate_need(need,max,allot);


  int finish[p];
  int  safe_seq[p];

  for(i=0;i<p;i++)
  {
    finish[i]=0;
    safe_seq[i]=-1;
  }





  int work[r];

  for(i=0;i<r;i++)
  work[i]=avail[i];


  int count=0;

  while(count<p)
  {
    int found=0;
    for(i=0;i<p;i++)
    {
      if(finish[i]==0)
      {
        for(j=0;j<r;j++){
          if(need[i][j] >work[j])
          break;
        }


        if(j==r)
        {
          int k;
          for(k=0;k<r;k++)
             work[k] += allot[i][k];


           safe_seq[count++]=i;
           finish[i]=1;
           found=1;
        }
      }
    }


    if(found==0)
    {
      printf("system is not int the safe state\n");
      return 0;
    }
  }

  printf("system is in the safe state\n the sequence is\n");

  for(i=0;i<p;i++)
  {
    printf("%d ",safe_seq[i]);

  }
  printf("\n");

  return 1;
}


void resource_request(int process[],int avail[],int max[][r],int allot[][r],int need[][r])
{
  int i,j,p1;
  printf("enter the process number which is making an additional request\n");
  scanf("%d",&p1);

  int request[r];
  printf("enter the request \n");
  for(i=0;i<r;i++)
     scanf("%d",&request[i]);

  int flag=0;
  for(j=0;j<r;j++)
  {
    if(request[j]>need[p1][j])
     {
       flag=1;
       break;
     }
  }
  if(flag==1)
    printf("request cannot be granted\n");
  else
  {
     flag=0;
    for(j=0;j<r;j++)
    {
      if(request[j]>avail[j])
       {
         flag=2;
         break;
       }
    }
    if(flag==2)
         printf("request cannot be granted\n");
    else
    {
      for(i=0;i<r;i++)
      {
        avail[i] -= request[i];
        allot[p1][i] += request[i];

      }

      printf("the need matrix is \n");

      for(i=0;i<p;i++)
      {

        for(j=0;j<r;j++)
        {
          printf("%d ",need[i][j]);
        }
        printf("\n");
      }

      printf("the allocated  matrix is \n");

      for(i=0;i<p;i++)
      {

        for(j=0;j<r;j++)
        {
          printf("%d ",allot[i][j]);
        }
        printf("\n");
      }

      printf("the avail resources is\n");
      for(i=0;i<r;i++)
        printf("%d ",avail[i]);

        printf("\n");


      safe(process,avail,max,allot,need);

    }

  }



}



int main()
{
  int i,j,k,l,m,n;
  printf("enter the number of processes\n");
   scanf("%d",&p);
    printf("enter the number of resources\n");
    scanf("%d",&r);
    int avail[r];

    printf("enter the available instances of each resources\n");
    for(i=0;i<r;i++)
    {
      scanf("%d",&avail[i]);
    }


  int process[p],max[p][r],allot[p][r];
    printf("enter the max matrix: the maximum resource that can be allocated to any process\n");

    for(i=0;i<p;i++)
    {
      process[i]=i;
      for(j=0;j<r;j++)
      {
        scanf("%d",&max[i][j]);
      }
    }

    printf("enter the allocated matrix:\n");
    for(i=0;i<p;i++)
    {

      for(j=0;j<r;j++)
      {
        scanf("%d",&allot[i][j]);
      }
    }
    // to check if the system is in the safe state or not

    int need[p][r];

    safe(process,avail,max,allot,need);

    printf("the need matrix is \n");

    for(i=0;i<p;i++)
    {

      for(j=0;j<r;j++)
      {
        printf("%d ",need[i][j]);
      }
      printf("\n");
    }

    resource_request(process,avail,max,allot,need);


    return 0;


}
