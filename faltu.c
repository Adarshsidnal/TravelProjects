#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#define  MAX_VERTICES 100
#define  INF 999999
#define  MAX_DISTRICTS 30
#define  MAX_QUERY_LENGTH 50

typedef struct places
{
    char name[20];
}place;


typedef struct package
{
    int travellers;
    int budget;
    char vehicle[30];
}pack;

int q[30],top=-1,stack[50];

void packages(pack arr[24])
{
   arr[0]. travellers=2;
    arr[0].budget=2000;
    strcpy(arr[0].vehicle,"HERO_BIKE");

    arr[1]. travellers=2;
    arr[1].budget=3000;
    strcpy(arr[1].vehicle,"ALTO_CAR");

    arr[2]. travellers=3;
    arr[2].budget=3000;
    strcpy(arr[2].vehicle,"NANO_CAR");

    arr[3]. travellers=3;
    arr[3].budget=4000;
    strcpy(arr[3].vehicle,"SWIFT_CAR");

    arr[4]. travellers=3;
    arr[4].budget=5000;
    strcpy(arr[4].vehicle,"VOLKS_WAGEN");

    arr[5]. travellers=4;
    arr[5].budget=4000;
    strcpy(arr[5].vehicle,"SWIFT_CAR");

    arr[6]. travellers=4;
    arr[6].budget=5000;
    strcpy(arr[6].vehicle,"BOLERO");

    arr[7]. travellers=5;
    arr[7].budget=5000;
    strcpy(arr[7].vehicle,"MARUTI_SUZUKI");

    arr[8]. travellers=5;
    arr[8].budget=6000;
    strcpy(arr[8].vehicle,"XUV_700");

    arr[9].travellers=6;
    arr[9].budget=6000;
    strcpy(arr[9].vehicle,"AUDI");

    arr[10]. travellers=6;
    arr[10].budget=7000;
    strcpy(arr[10].vehicle,"BENZ_CAR");

    arr[11]. travellers=7;
    arr[11].budget=7000;
    strcpy(arr[11].vehicle,"TESLA");

    arr[12]. travellers=7;
    arr[12].budget=8000;
    strcpy(arr[12].vehicle,"FORTUNER");

    arr[13]. travellers=8;
    arr[13].budget=8000;
    strcpy(arr[13].vehicle,"OMNI_VAN");

    arr[14]. travellers=8;
    arr[14].budget=9000;
    strcpy(arr[14].vehicle,"MAHINDRA_MORZO");

    arr[15]. travellers=9;
    arr[15].budget=9000;
    strcpy(arr[15].vehicle,"TATA_ELECTRIC");

    arr[16]. travellers=9;
    arr[16].budget=10000;
    strcpy(arr[16].vehicle,"TOYOTA");

    arr[17]. travellers=10;
    arr[17].budget=10000;
    strcpy(arr[17].vehicle,"BOLERO");

    arr[18]. travellers=10;
    arr[18].budget=11000;
    strcpy(arr[18].vehicle,"SCORPIO");

    arr[19]. travellers=11;
    arr[19].budget=11000;
    strcpy(arr[19].vehicle,"SLEEPER_BUS");

    arr[20]. travellers=11;
    arr[20].budget=12000;
    strcpy(arr[20].vehicle,"AC_BUS");

    arr[21]. travellers=12;
    arr[21].budget=12000;
    strcpy(arr[21].vehicle,"SLEEPER_BUS");

    arr[22]. travellers=12;
    arr[22].budget=13000;
    strcpy(arr[22].vehicle,"AC_BUS");
}
void create_graph(int graph[24][24],FILE *fp1)
{
    for(int i=0;i<24;i++)
     {
         for(int j=0;j<24;j++)
         {
             fscanf(fp1,"%d",&graph[i][j]);
         }
     }
}
void create_hash_table(place hash[24],FILE *fp2)
{
 for(int i=0;i<24;i++)
       {
         fscanf(fp2,"%s",hash[i].name);
       }
}
int hashKey(place hash[24],char cities[])
{
    for(int i=0;i<24;i++)
    {
        if(strcmp(hash[i].name,cities)==0)
        {
            return i;
        }
    }
    return -1;
}
int district(place hash[30],char source[20])
{
    int i;
    for( i=0;i<30;i++)
     {
        if(!strcmp(hash[i].name,source))
        {
            return i;
        }
     }
    return -1;
}
void Dijkstra(int v,int graph[24][24],int src,int destination,place hash[24])
{
    int cost[24][24],distance[24],visited[24];
    int nextnode;
    int count;

    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {

            if(graph[i][j]==0)
            {
                cost[i][j]=INF;
            }
            else
            {
                cost[i][j]=graph[i][j];
            }
        }
    }
    int mindistance;

    //creating distance visited path
    for(int i=0;i<v;i++)
    {
        distance[i]=cost[src][i];
        visited[i]=0;
    }

    distance[src]=0;
    visited[src]=1;
    count=1;

    while(count<v-1)
    {
        mindistance=INF;
        for(int i=0;i<v;i++)
        {
            if(distance[i]<mindistance && !visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
        }
        visited[nextnode]=1;
        //we have to extract all neigh
        for(int i=0;i<v;i++)
        {
            if(mindistance+cost[nextnode][i]<distance[i] && !visited[i])
            {
                distance[i]=mindistance+cost[nextnode][i];

            }
        }
        count++;
    }

    printf("\nDistance from %s to %s: %d\n",hash[src].name,hash[destination].name,distance[destination ]);



}

void prims(int v,int graph[24][24],int src,int destination,place hash[24])
{
    int distance[24],path[24],visited[24];
    int cost[24][24];
    int nextnode;
    int minicost;
    int sum=0;
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            if(graph[i][j]==0)
                cost[i][j]=INF;
            else
                cost[i][j]=graph[i][j];
        }
    }

    //create visited path distance
    for(int i=0;i<v;i++)
    {
        distance[i]=INF;
        visited[i]=0;
        path[i]=src;
    }

    distance[src]=0;
   int count=1;
   while(count<v)
   {
        minicost=INF;
        if(count>1)
             src=nextnode;
        visited[src]=1;
       for(int i=0;i<v;i++)
       {
           if(!visited[i])
           {
               if(cost[src][i]<distance[i])
               {
                   distance[i]=cost[src][i];
                   path[i]=src;
               }

           }

      }

      for(int i=0;i<v;i++)
      {
          if(!visited[i])
          {
              if(distance[i]<minicost)
              {
                  minicost=distance[i];
                  nextnode=i;
              }
          }

      }
      count++;
      printf("\n");
      sum=sum+distance[nextnode];
      printf("%s---->%s",hash[path[nextnode]].name,hash[nextnode].name);
    }
    printf("\nTOTAL DISTANCE COVERED IN TRAVELING ALL THE PLACES IN A MINIMUM DISTANCE %d\n",sum);
}

void prims1(int v,int graph[24][24],int src,int destination,place hash[24])
{
    int distance[24],path[24],visited[24];
    int cost[24][24];
    int nextnode;
    int minicost;
    int sum=0;
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            if(graph[i][j]==0)
                cost[i][j]=INF;
            else
                cost[i][j]=graph[i][j];
        }
    }

    //create visited path distance
    for(int i=0;i<v;i++)
    {
        distance[i]=INF;
        visited[i]=0;
        path[i]=src;
    }

    distance[src]=0;
   int count=1;
   while(count<v)
   {
        minicost=INF;
        if(count>1)
             src=nextnode;
        visited[src]=1;
       for(int i=src;i<v;i++)
       {
           if(!visited[i])
           {
               if(cost[src][i]<distance[i])
               {
                   distance[i]=cost[src][i];
                   path[i]=src;
               }

           }

      }

      for(int i=0;i<v;i++)
      {
          if(!visited[i])
          {
              if(distance[i]<minicost)
              {
                  minicost=distance[i];
                  nextnode=i;
              }
          }

      }
      count++;
      sum=sum+distance[nextnode];
      printf("%s---->%s\n",hash[path[nextnode]].name,hash[nextnode].name);
      if(nextnode==destination)
      {
          break;
      }
    }
}
void push(int item)
{
if(top==24)
printf("Stack overflow ");
else
stack[++top]=item;
}

int pop()
 {
int k;
   if(top==-1)
   return(0);
else
{
  k=stack[top--];
   return(k);
}
}
struct node
{
    int data;
    struct node *link;
};
typedef struct node *snode;
snode create_node(int i)
{
    snode newnode;
    newnode=(snode)malloc(sizeof(struct node));
    if(newnode==NULL)
        printf("Memory not allocated\n");

         newnode->data=i;
        newnode->link=NULL;

    return newnode;
}
snode insert_end(snode head,int i)
{
    snode newnode,cur;
    newnode=create_node(i);
    if(head==NULL)
        head=newnode;
    else
    {
        cur=head;
        while(cur->link!=NULL)
            cur=cur->link;
        cur->link=newnode;
    }
    return head;
}
void display(place hash[24],snode head)
{
    snode cur;
    if(head==NULL)
        printf("List is empty\n");
    else
    {
        cur=head;
        while(cur!= NULL)
        {
            printf("%s ",hash[cur->data].name);
            cur=cur->link;
        }
    }
}
 snode delete_end(snode head)
 {
     snode cur,prev;
     if(head==NULL)
            printf("List is empty\n");
    else if(head->link==NULL)
        {
            free(head);
            head=NULL;
        }
        else
        {
            prev=NULL;
            cur=head;
            while(cur->link!=NULL)
            {
                prev=cur;
                cur=cur->link;
            }
            free(cur);
            prev->link=NULL;
        }
        return head;
 }
int path[24];
int path_length = 0;

void print_path(int start, int end,place hash[24]) {
    printf("Path: ");
    for (int i = 0; i < path_length; i++) {
        printf("%s ",hash[path[i]].name);
    }
    printf("\n");
   // printf("%d\n", end);
}

void find_all_paths(int graph[24][24],int visited[24],int current, int end,place hash[24]) {
    visited[current] = 1;
    path[path_length++] = current;


    if (current == end) {
        print_path(path[0], end,hash);
    }
    else {

        for (int i = 0; i < 24; i++) {
            if (graph[current][i] && !visited[i]) {
                find_all_paths(graph,visited,i,end,hash);
            }
        }
    }

    path_length--;
    visited[current] = 0;
}

int distance(snode head,int graph[24][24])
{

    int sum=0;
    for(int i=0;i<24;i++)
    {
        for(int j=0;j<24;j++)
        {
            if(graph[i][j]!=0)
            {
                snode cur=head;
                while(cur->link!=NULL)
                {
                    if(cur->data==i && cur->link->data==j)
                    {
                        sum=sum+graph[i][j];
                    }
                    cur=cur->link;
                }
            }
        }
    }
    return sum;
}
 void search2(place hash[24],char query[])
 {
     int m=strlen(query);
     int k;
     for(int i=0;i<24;i++)
     {
         //char place[20];
         //strcpy(place,hash[i].name);
         int n=strlen(hash[i].name);
         for(int j=0;j<n-m;j++)
         {
             k=0;
             while(k<m&&hash[i].name[k]==query[k+j])
             {
                 k=k+1;
                 if(k==m)
                 {
                     printf("%s\n",hash[i].name);
                 }
             }
         }
     }
 }
 void choose_package(pack arr[24],int m,int n,int o)
 {
     for(int i=0;i<24;i++)
     {
         if(m==1||m>12)
         {
             printf("INVALID\n");
         }
         else if(arr[i].travellers==2 && m==2&& n<=2000&&arr[i].budget<=2000)
         {
             n=2000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
             printf("TOTAL_AMOUNT:%d\n",o+n);
         }
         else if(arr[i].travellers==2 && m==2&&arr[i].budget>2000 &&arr[i].budget<=3000 &&n>2000 &&n<=3000)
         {
               n=3000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }
         else if(arr[i].travellers==3 && m==3&&n<=3000&&arr[i].budget<=3000 )
         {
              n=3000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }

         else if(arr[i].travellers==3 && m==3&&arr[i].budget>3000 &&arr[i].budget<=4000 &&n>3000 &&n<=4000)
         {
               n=4000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }
          else if(arr[i].travellers==4 && m==4&&n<=4000&&arr[i].budget<=4000 )
         {
              n=4000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }

         else if(arr[i].travellers==4 && m==4&&arr[i].budget>4000 &&arr[i].budget<=5000 &&n>4000 &&n<=5000)
         {
               n=5000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }
          else if(arr[i].travellers==5 && m==5&&n<=5000&&arr[i].budget<=5000 )
         {
              n=5000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }

         else if(arr[i].travellers==5 && m==5&&arr[i].budget>5000 &&arr[i].budget<=6000 &&n>5000 &&n<=6000)
         {
               n=6000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }
         else if(arr[i].travellers==6 && m==6&&n<=6000&&arr[i].budget<=6000 )
         {
              n=6000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }

         else if(arr[i].travellers==6 && m==6&&arr[i].budget>6000 &&arr[i].budget<=7000 &&n>6000 &&n<=7000)
         {
               n=7000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }
          else if(arr[i].travellers==7 && m==7&&n<=7000&&arr[i].budget<=7000 )
         {
              n=7000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }

         else if(arr[i].travellers==7 && m==7&&arr[i].budget>7000 &&arr[i].budget<=8000 &&n>7000 &&n<=8000)
         {
               n=8000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }
          else if(arr[i].travellers==8 && m==8&&n<=8000&&arr[i].budget<=8000 )
         {
              n=8000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }

         else if(arr[i].travellers==8 && m==8&&arr[i].budget>8000 &&arr[i].budget<=9000 &&n>8000 &&n<=9000)
         {
               n=9000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }
         else if(arr[i].travellers==9 && m==9&&n<=9000&&arr[i].budget<=9000 )
         {
              n=9000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }

         else if(arr[i].travellers==9 && m==9&&arr[i].budget>9000 &&arr[i].budget<=10000 &&n>9000 &&n<=10000)
         {
               n=10000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }
         else if(arr[i].travellers==10 && m==10&&n<=10000&&arr[i].budget<=10000 )
         {
              n=10000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }

         else if(arr[i].travellers==10 && m==10&&arr[i].budget>10000 &&arr[i].budget<=11000 &&n>10000 &&n<=11000)
         {
               n=11000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }
         else if(arr[i].travellers==11 && m==11&&n<=11000&&arr[i].budget<=11000 )
         {
              n=11000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }

         else if(arr[i].travellers==11 && m==11&&arr[i].budget>11000 &&arr[i].budget<=12000 &&n>11000 &&n<=12000)
         {
               n=12000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }
          else if(arr[i].travellers==12 && m==12&&n<=12000&&arr[i].budget<=12000 )
         {
              n=12000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }

         else if(arr[i].travellers==12 && m==12&&arr[i].budget>12000 &&arr[i].budget<=13000 &&n>12000 &&n<=13000)
         {
               n=13000;
             printf("NUMBER OF PERSONS:%d\nVEHICLE_AMOUNT:%d\nVEHICLE:%s\n",m,n,arr[i].vehicle);
              printf("TOTAL_AMOUNT:%d\n",o+n);
         }
     }
 }
int main()
{
     pack arr[24];
     packages(arr);
     int graph[24][24];
     int a,b,q;
     char source[20];
     char destination[20];
     place hash[24];
     FILE *fp1;
     fp1=fopen("input2.txt","r");
     create_graph(graph,fp1);
     fclose(fp1);
     FILE *fp2;
     fp2=fopen("input1.txt","r");
     create_hash_table(hash,fp2);
     fclose(fp2);
      char query[MAX_QUERY_LENGTH];
      char s[20];
      printf("DO YOU WANNA KNOW THE DISTRICTS SPELL\n");
      scanf("%s",s);
      strupr(s);
      if(strcmp(s,"YES")==0)
      {
        printf("Enter a letter to search from the available district names: ");
        scanf("%s",query);
        strupr(query);
         search2(hash,query);
      }
      printf("Enter your (source) location:\n");
      scanf("%s",source);
      printf("Enter the destination location:\n");
      scanf("%s",destination);
      strupr(source);
      strupr(destination);
       a=district(hash,source);
       b=district(hash,destination);
     if(a==-1||b==-1)
     {
         printf("SOURCE/DESTINATION INVALID\n");
         exit(0);
     }
      int ch;
    while(1)
 {
     printf("TRAVEL MENU\n");
     printf("1:TO DISPLAY ALL THE PATHS PRESENT BETWEEN SOURCE AND DESTINATION AND TO FIND THE DISTANCE VIA THE PATH\n");
     printf("2:TO FIND THE SHORTEST DISTANCE BETWEEN SOURCE AND DESTINATION AND THE PATH TO REACH THE DESTINATION\n");
     printf("3:TO TRAVEL ALL THE PLACES IN A MINIMUM COST ENTER YES\n");
     printf("4:TO GENERATE A BILL\n");
     printf("5:BREAK\n");
    scanf("%d",&ch);
   switch(ch)
  {

    case 1:
    {

       int visited[24];
       for(int i=0;i<24;i++)
       {
        visited[i]=0;
       }
       find_all_paths(graph,visited,a,b,hash);
        snode head1=NULL;
         printf("ENTER THE PATH YOU WANT TO TRAVEL\n");
        for(int i=0;i<16;i++)
        {
            char cities[20];
            scanf("%s",cities);
            strupr(cities);
            int a=hashKey(hash,cities);
            if(a==-1)
            {
                printf("PATH SUCESSFULLY STORED!\n");
                break;
            }
             head1=insert_end(head1,a);
        }
        display(hash,head1);
        q=distance(head1,graph);
        printf("\nDISTANCE OF THE PATH TO DESTINATION:%d ",q);
    }
    break;

    case 2:
    {
    printf("THE MINIMUM DISTANCE BETWEEN SOURCE AND DESTINATION IS\n");
    Dijkstra(24,graph,a,b,hash);
    printf("THE MINIMUM DISTANCE PATH IS\n");
     prims1(24,graph,a,b,hash);
    }
    break;

    case 3:
        {
        char choice[15];
        printf("ENTER YOUR CHOICE\n");
       scanf("%s",choice);
        strupr(choice);
      if(strcmp(choice,"YES")==0)
         prims(24,graph,a,b,hash);
      else
      printf("WISH YOU A HAPPY JOURNEY!!!!!");
        }
    break;
    case 4:
        {
            int m,n,o;
           printf("ENTER THE NUMBER OF MEMBERS TRAVELLING AND BUDGET OF THE TRAVEL\n");
           scanf("%d%d",&m,&n);
           printf("\nBILL WITH GST\n");
           o=q*10;
           choose_package(arr,m,n,o);
        }
    break;
    case 5:exit(0);
    break;
 }

  }

          return 0;
}
