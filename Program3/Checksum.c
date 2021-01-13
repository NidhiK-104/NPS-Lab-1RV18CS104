#include<stdio.h>
//#include<conio.h>
#include<math.h>
 
 int sender(int b[10],int k)
 {
 	int checksum,sum=0,i;
        	printf("\n****SENDER****\n");
     
for(i=0;i<k;i++)
      		sum+=b[i];
      		printf("SUM IS: %d",sum);
                     
    	checksum=~sum;
    	printf("\nSENDER's CHECKSUM IS:%d",checksum);
    	return checksum;
}
 
int receiver(int b[10],int k)
{
int checksum,sum=0,i;
        	printf("\n****RECEIVER****\n");
     
for(i=0;i<k;i++)
      		sum+=b[i];
      		printf("SUM IS: %d",sum);
                     
    	checksum=~sum;
    	printf("\nRECEIVER's CHECKSUM IS:%d",checksum);
    	return checksum;
  }
   void main()
   {
     	int a[10],i,m,scheck,rcheck,b[10];
//clrscr();
     	printf("\nENTER SIZE OF THE STRING:");
     	scanf("%d",&m);
     	printf("\nENTER THE ELEMENTS OF THE ARRAY SENT:");
     	for(i=0;i<m;i++)
    	scanf("%d",&a[i]);
    	scheck=sender(a,m);
     	printf("\n\n\nENTER THE ELEMENTS OF THE ARRAY RECEIVED:");
     	for(i=0;i<m;i++)
    	scanf("%d",&b[i]);
    	rcheck=receiver(b,m);
    	//rcheck=receiver(a,m,scheck);
    	if(rcheck==scheck)
      		printf("\n\nNO ERROR IN TRANSMISSION\n\n");
    	else
      		printf("\n\nERROR DETECTED\n");
              // getch();
} 	