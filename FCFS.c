#include<stdio.h>

int WaitingTime(int process[], int n, int burstT[], int waitT[])
{
    waitT[0]=0;

    for(int i=1; i<n; i++)
      waitT[i]=burstT[i-1]+ waitT[i-1];
}

int turnAT(int process[], int n, int burstT[], int waitT[], int tat[])
{
    for(int i=0; i<n; i++)
    tat[i]= burstT[i]+waitT[i];
}

int avgT( int process[], int n, int burstT[]) 
{ 
    int waitT[n], tat[n], total_wait = 0, total_tat = 0; 
    
    WaitingTime(process, n,  burstT,  waitT);
   
    turnAT( process,  n,  burstT,  waitT,  tat);
    
    printf("\tProcess\tBT\tWT\tTAT\n"); 
   
    for (int  i=0; i<n; i++) 
    { 
        total_wait = total_wait + waitT[i]; 
        total_tat = total_tat + tat[i]; 
        printf("\t%d ",(i+1));
        printf("\t%d ", burstT[i] );
        printf("\t%d",waitT[i] );
        printf("\t%d\n",tat[i] ); 
    } 
    float s=(float)total_wait / (float)n;
    float t=(float)total_tat / (float)n;
    printf("Average waiting time = %f",s);
    printf("\n");
    printf("Average turn around time = %f ",t); 
} 
   
int main() 
{  
     int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process[n];
    int burstT[n];

    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burstT[i]);
        process[i] = i + 1; 
    }
    
    avgT(process, n, burstT); 
    return 0; 
} 

