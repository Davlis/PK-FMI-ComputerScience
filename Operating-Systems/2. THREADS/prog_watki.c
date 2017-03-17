#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define REENTRANT

#define ROW_AMOUNT      2
#define COLUMN_AMOUNT   10

struct Data
{
    int tab[ROW_AMOUNT][COLUMN_AMOUNT];
    int sum[ROW_AMOUNT];
};

struct DatawRow
{
    struct Data *dat;
    int row;
};

int randomNumber(int min_num, int max_num)
{
  int low_num=0,hi_num=0;
  if(min_num<max_num)
  {
    low_num=min_num;
    hi_num=max_num+1;
  }else{
    low_num=max_num;
    hi_num=min_num+1;
  }
  return (rand()%(hi_num-low_num))+low_num;
}

void initTab(struct Data *d)
{
    int i, j;
    for(i=0; i<ROW_AMOUNT; i++)
        d->sum[i]=0;

    for(i=0; i<ROW_AMOUNT; i++)
        for(j=0; j<COLUMN_AMOUNT; j++)
            d->tab[i][j]=randomNumber(1,100);
}

void showTab(struct Data *d)
{
    int i, j;
    for(i=0; i<ROW_AMOUNT; i++)
    {
        for(j=0; j<COLUMN_AMOUNT; j++)
           printf("%3d ", d->tab[i][j]);
        printf("\n");
    }
}

void end(char tekst[], int arg)
{
    printf("Cannot %s thread %d!\n", tekst, arg);
    exit(-1);
}

void *sumRow(struct DatawRow *d)
{
    int i;
    for(i=0; i<COLUMN_AMOUNT; i++)
        d->dat->sum[d->row]+=d->dat->tab[d->row][i];
    pthread_exit(0);
}

int main()
{
    srand((unsigned)time(NULL));

    struct Data d;
    initTab(&d);
    showTab(&d);

    pthread_t threadID[ROW_AMOUNT];
    int status, i, sum=0;

    struct DatawRow dr[ROW_AMOUNT];
    for(i=0; i<ROW_AMOUNT; i++)
    {
        dr[i].dat=&d;
        dr[i].row=i;
    }

	printf("ID main thread: %u\n", pthread_self());

    for(i=0; i<ROW_AMOUNT; i++)
    {
        status=pthread_create(&threadID[i], NULL, sumRow, &dr[i]);
        printf("create status thread %d: %d\n", i, status);
        if(status==-1) end("create", i+1);
    }

    for(i=0; i<ROW_AMOUNT; i++)
    {
        status=pthread_join(threadID[i], NULL);
        printf("join status thread %d: %d\n", i, status);
        if(status==-1) end("join", i+1);
    }

    for(i=0; i<ROW_AMOUNT; i++)
    {
        status=pthread_detach(threadID[i]);
        printf("detach status thread %d: %d\n", i, status);
        if(status==-1) end("detach", i+1);
    }

    for(i=0; i<ROW_AMOUNT; i++)
    {
        printf("Sum by thread %d: %d\n", i+1, d.sum[i]);
        sum+=d.sum[i];
    }

    printf("Full sum: %d\n", sum);
    return 0;
  }






while (temp->nastepna)
{

}
