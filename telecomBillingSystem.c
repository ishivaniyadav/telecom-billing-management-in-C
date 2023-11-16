#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
struct subscriber
{
char phonenumber[20];
char name[50];
float amount;
}s;
void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment();
char get;
int main()
{
int password;
int phonenumber;
char choice;
printf("\n\t\t*******************************************************************************************************************");
printf("\n\t\t-------------------------------WELCOME TO TELECOM BILLING MANAGEMENT SYSTEM----------------------------------------");
printf("\n\t\t*******************************************************************************************************************");
getchar();
while(1)
{
	printf("\nEnter \nA: for adding new records.\nL: for list of records.\nM: for modyfying records.\nD: for deleting a record.\nS: for searching records.\nP: for payment.\nE: exit.\n");
	choice=getchar();
	choice=toupper(choice);
	switch(choice)
	{
	case 'A':
		addrecords();break;
	case 'L':
		listrecords();break;
	case 'M':
		modifyrecords();break;
	case 'D':
		deleterecords();break;
	case 'S':
		searchrecords();break;
	case 'P':
		payment();break;
	case 'E':
		printf("\n\n\t\t\t\tTHANK YOU FOR USING OUR SERVICES");
		exit(0);
		break;
	default:
		printf("Invalid input...Try again!!!");
		printf("\nAny key to continue");
		getchar();
		break;
	}
}
}

void addrecords()
{
	FILE *f;
	char test;
	f=fopen("telecom.txt","ab+");
	if(f==0)
	{
	f=fopen("telecom.txt","wb+");
	printf("Please wait while we configure your computer");
	printf("\nPress any key to continue");
	getchar();
	}
	while(1)
	{
	printf("\nEnter phone number:");
	scanf("%s",s.phonenumber);
	printf("\n Enter Name:");
	fflush(stdin);
	scanf("%s[^\n]",s.name);
	printf("\nEnter amount:");
	scanf("%f",&s.amount);
	fwrite(&s,sizeof(s),1,f);
	fflush(stdin);
	printf("Record added successfully!!");
	printf("\n Press esc to exit, any other key to add another record.");
	test=getchar();
	if(test==27)
		break;

	}
	fclose(f);
}

void listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("telecom.txt","rb"))==NULL)
		exit(0);
	printf("Phone number\t\tUsername\t\t\tAmount\n");
	for(i=0; i<79; i++)
		printf("-");
	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\tRs. %.2lf /-",s.phonenumber,s.name,s.amount);
	}
	printf("\n");
	for(i=0; i<79; i++)
		printf("-");
fclose(f);
getchar();
}

void deleterecords()
{
	FILE *f,*t;
	int i=1;
	char phonenumber[20];
	if((t=fopen("telecom.txt","w+"))==NULL)
	exit(0);
	if((f=fopen("telecom.txt","rb+"))==NULL)
	exit(0);
	printf("Enter phone number to be deleted from the database:");
	fflush(stdin);
	scanf("%[^\n]",phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			i=0;
			continue;
		}
		else
			fwrite(&s,sizeof(s),1,t);
	}
	if(i==1)
	{
		printf("Phone number \"%s\" not found",phonenumber);
		remove("telecom.txt");
		rename("temp.txt","telecom.txt");
		getchar();
		fclose(f);
		fclose(t);
		main();
	}
	remove("telecom.txt");
	rename("temp.txt","telecom.txt");
	printf("The Number %s Successfully Deleted!!!",phonenumber);
	fclose(f);
	fclose(t);
	getchar();
}

void searchrecords()
{
	FILE *f;
	char phonenumber[20];
	int flag=1;
	f=fopen("telecom.txt","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	printf("Enter phone number to search in our database:");
	scanf("%s",phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			printf("Record found");
			printf("\\nPhonenumber: %s\nName: %s\nAmount: Rs.%0.2f\n",s.phonenumber,s.name,s.amount);
			flag=0;
			break;
		}
		else if(flag==1)
		{
			printf("Requested Phone number not found in our database.");
		}
	}
	getchar();
	fclose(f);
}

void modifyrecords()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	if((f=fopen("telecom.txt","rb+"))==NULL)
		exit(0);
	printf("Enter phone number of the subscriber to modify:");
	scanf("%s[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			printf("\nEnter phone number:");
			scanf("%s",s.phonenumber);
			printf("\nEnter name:");
			fflush(stdin);
			scanf("%s[^\n]",s.name);
			printf("\nEnter amount:");
			scanf("%f",&s.amount);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
}

void payment()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	float amt;
	int i;
	if((f=fopen("telecom.txt","rb+"))==NULL)
		exit(0);
	printf("Enter phone number of the subscriber for payment");
	scanf("%s[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			printf("\nPhone no.: %s",s.phonenumber);
			printf("\nName : %s",s.name);
			printf("\nCurrent amount : %f",s.amount);
			printf("\n");
			for(i=0; i<79; i++)
				printf("-");
			printf("\n\nEnter amount of payment:");
			fflush(stdin);
			scanf("%f",&amt);
			s.amount=s.amount-amt;
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
	getchar();
	fclose(f);
}
