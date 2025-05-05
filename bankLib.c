
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "bankLib.h"

const int szDb=(sizeof(u64)*2+sizeof(f64)+sizeof(char)*(MAX_USRN_LEN+MAX_PASS_LEN));

void loginMenu(void){
	printf(BPINK"\n-------------WELCOME TO @JET BANK--------------\n");
	printf("Please enter login credentials.\n"RESET);
}

void adminMenu(void){
	printf(BPINK"\nHI ADMIN:\n"
                        "[KEY]  : ACTION\n"
                        "c/C    : Create New account.\n"
                        "u/U    : Update Old account info.\n"
                        "h/H    : Transaction history.\n"
                        "w/W    : Withdraw amount.\n"
                        "d/D    : Deposit amount.\n"
                        "b/B    : Balance enquery.\n"
                        "t/T    : Transfer money.\n"
                        "e/E    : Display all accounts details.\n"
                        "f/F    : Finding/searching for specific account.\n"
                        "q/Q    : Quit from app.\n"BYELLOW
                        "Enter choice:"RESET);
}

void userMenu(void){
	printf(BPINK"\nHI CUSTOMER:\n"
                        "[KEY]  : ACTION\n"
                        "h/H    : Transaction history.\n"
                        "w/W    : Withdraw amount.\n"
                        "d/D    : Deposit amount.\n"
                        "b/B    : Balance enquery.\n"
                        "t/T    : Transfer amount.\n"
                        "q/Q    : Quit from app.\n"BYELLOW
                        "Enter choice:"RESET);

}

void menu(void){
	printf("\n------------------MENU--------------------------\n"
	                "[KEY]	: ACTION\n"
			"c/C 	: Create New account.\n"
			"u/U    : Update Old account info.\n"
			"h/H 	: Transaction history.\n"
			"w/W 	: Withdraw amount.\n"
			"d/D 	: Deposit amount.\n"
			"b/B	: Balance enquery.\n"
			"t/T 	: Transfer money.\n"
			"e/E	: Display all accounts details.\n"
			"f/F	: Finding/searching for specific account.\n"
			"q/Q	: Quit from app.\n"
			"Enter choice:");
}

Acc* isValid(Acc *head,char *usr,char *pass){
	while(head){
		if((!strcmp(usr,head->usrName))&&(!strcmp(pass,head->pass)))
			 break;
		head=head->nxt;
	}
	return head;
}

void newAcc( Acc **head){
	char *temp=NULL,flag=1;
	Acc *new=calloc(1,sizeof(Acc));
        new->tranHist=NULL;
	new->tranCnt=0;
	new->num=getUnqId(*head);
	printf("Enter Name:");
	new->name=getStr();
	format(new->name);
	printf("Enter Mobile No.:");
	scanf("%llu",&(new->phno));
	flag=1;
	while(flag){
		printf("Enter Login Username:");
		temp=getStr();
		if(strlen(temp)>=MAX_USRN_LEN){
			puts("Username too long,try again!!");
			continue;
		}
		if(isUnq(*head,temp)){
			strcpy(new->usrName,temp);
			free(temp);
			flag=0;
		}else{
			puts("User name aldready exits!");
			puts("Try differnt one.");
		}
		
	}
	flag=1;
	while(flag){
		if(flag>1)puts("Password mismatch!! Retry.");
		printf("Enter Login Password:");
		temp=getStr();
		if(strlen(temp)>=MAX_PASS_LEN){
                        puts("Password too long,try again!!");
			flag=1;
                        continue;
                }
		strcpy(new->pass,temp);
		free(temp);
		printf("Re-enter Login Password:");
		temp=getStr();
		flag=(strcmp(temp,new->pass)?flag+1:0);
	}
	printf("Enter Opening Amount:");
        scanf("%lf",&(new->bal));//must update trancs
	addTran(new,new->bal,DEPOSIT);//0

	dispAcc(new);
	//add to database
	new->nxt=*head;
	*head=new;
	puts(BGREEN"Account Created."RESET);
	free(temp);
}

int isUnq(Acc *head,char *str){
	if(!strcmp(str,ADMIN_USRN)) return 0;
	while(head){
		if(!strcmp(str,head->usrName)) return 0;
		head=head->nxt;
	}
	return 1;
}

u64 getUnqId(Acc *head){
	u64 num;
	Acc *temp=NULL;
	int found=1;
	while(found){
		srand(getpid()+ (unsigned int)head);
		//18 digit unq ID	
		num=getTimeStamp()*10000 +(rand()%10000);
		temp=head;
		found=0;
		while(temp){
			if(num==temp->num){
				found=1;
				break;
			}
			temp=temp->nxt;
		}
	}
	return num;
}

u64 getTimeStamp(void){
    time_t rawtime;
    struct tm *timeinfo;

    // Get current UTC time
    time(&rawtime);

    // Convert to IST (UTC +5:30)
    rawtime +=19800;  // 19800 seconds = 5 hours 30 minutes
    timeinfo =localtime(&rawtime);

    // Format as YYYYMMDDHHMMSS (14-digit ID)
    u64 timeStamp =
        (timeinfo->tm_year+1900)*10000000000ULL+
	(timeinfo->tm_mon+1)*100000000ULL+
	timeinfo->tm_mday*1000000ULL+
	timeinfo->tm_hour*10000ULL+
	timeinfo->tm_min *100ULL+
	timeinfo->tm_sec;

    return timeStamp;
}

char *getStr(void){
	char buff[NAME_LEN]={0};
	__fpurge(stdin);
	scanf("%[^\n]",buff);
	return strdup(buff);
}


char getKey(void){
	char key='\0';
	__fpurge(stdin);
	key=getchar();
	CAPS(key);
	return key;
}

void format(char *str){
	CAPS(str[0]);
	str++;
	while(*str){
		if(*(str-1)==' ')CAPS(*str);
		str++;
	}
}
///

///
void updateAcc(Acc **head,Acc *usr){
	char key,*temp=NULL;
	int flag=1;
	accMenu();

	key=getKey();
	__fpurge(stdin);
	puts("");
	switch(key){
		case 'P':printf("Enter New phone number:");
			 scanf("%llu",&(usr->phno));
			 puts(BGREEN"Mobile Updated."RESET);
			 break;
		case 'O':printf("Enter New Holder name:");
			 usr->name=getStr();
			 format(usr->name);
			 puts(BGREEN"Name Updated."RESET);
			 break;
		case 'U':flag=1;
			 while(flag){
				 printf("Enter New Username:");
				 temp=getStr();
				 if(strlen(temp)>=MAX_USRN_LEN){
					 puts("Username too long,try again!!");
					 continue;
				 }
				 if(isUnq(*head,temp)){
					 strcpy(usr->usrName,temp);
					 free(temp);
					 flag=0;
				 }else{
					 puts("User name aldready exits!");
					 puts("Try differnt one.");
				 }

			 }
			 puts(BGREEN"Username Updated."RESET);
			 break;
		case 'Q':printf("Enter old password:");
			 temp=getStr();
			 if(strcmp(temp,usr->pass)){
				 puts("Wrong password!!");
				 break;
			 }
			 flag=1;
			 while(flag){
				 if(flag>1)puts("Password mismatch!! Retry.");
				 printf("Enter New Login Password:");
				 temp=getStr();
				 if(strlen(temp)>=MAX_PASS_LEN){
					 puts("Password too long,try again!!");
					 flag=1;
					 continue;
				 }
				 strcpy(usr->pass,temp);
				 free(temp);
				 printf("Re-enter New Login Password:");
				 temp=getStr();
				 flag=(strcmp(temp,usr->pass)?flag+1:0);
			 }
			 puts(BGREEN"Password Updated."RESET);
			 break;
		default:puts("invalid input.");
			break;
	}
	free(temp);
}

void accMenu(void){
	printf(BBLUE"\nChange:\n"
			"[KEY]-ACTION\n"
			"p/P  -Phone number.\n"
			"o/O  -Holder's name.\n"
			"u/U  -Username.\n"
			"q/Q  -Password.\n"BYELLOW
			"Enter choice:"RESET);
}
///

///
void dispAcc(Acc *usr){
	puts(BBLUE"\n==:Account Details:=="RESET);
	printf("AccNo.:%llu\n",usr->num);
	printf("Name  :%s\n",usr->name);
	printf("Ph.No.:%llu\n",usr->phno);
	printf("Balanc:%lf\n",usr->bal);
	printf("Usrnam:%s\n",usr->usrName);
	printf("Passwd:%s\n",usr->pass);
	printf("TranNo:%llu\n",usr->tranCnt);
}
///

///
Acc* getAcc(Acc *head){
	u64 num=0;
	char key='\0',*str=NULL;
	printf( BBLUE"Find by:\n"
		"[KEY]-ACTION\n"
		"p/P  -Phone number.\n"
		"n/N  -Account number.\n"
		"o/O  -Holder name.\n"
		"u/U  -Username.\n"BYELLOW
		"Enter choice:"RESET);
	key=getKey();
	__fpurge(stdin);
	puts("");
	switch(key){
		case 'P':printf("Enter phone number:");
			 scanf("%llu",&num);
			 while(head){
				if(num==head->phno)break;
				 head=head->nxt;
			 }
			 break;
		case 'N':printf("Enter account number:");
			 scanf("%llu",&num);
			 while(head){
				if(num==head->num)break;
				 head=head->nxt;
			 }
			 break;
		case 'O':printf("Enter holder name:");
			 str=getStr();
			 format(str);
			 while(head){
				if(!strcmp(str,head->name))break;
				 head=head->nxt;
			 }
			 break;
		case 'U':printf("Enter username:");
			 str=getStr();
			 while(head){
				if(!strcmp(str,head->usrName))break;
				 head=head->nxt;
			 }
			 break;
		default:puts("invalid choice");
			head=NULL;
			break;
	}
	free(str);
	return head;
}
///

///
void dltAcc(Acc **head){
	if(!(*head))return;

	//travese to acc
	//delete
}
///

///
void balance(Acc *usr){
	printf("\nAccount Number : %llu\n",usr->num);
	printf("Holder Name    : %s\n",usr->name);
	printf("Current Balance: %+lf Rs/-\n",usr->bal);
}
///

///
void deposit(Acc *usr){
	f64 amt=0;
	printf("\nEnter Deposit Amount:");
        scanf("%lf",&amt);
	
	if(amt<=0){
		puts("Amount cannot be negative!!");
                puts("Try again!!");
	}else if(amt<MAX_DEPOSIT){
		usr->bal += amt;
		//update 2 transc
		addTran(usr,+amt,DEPOSIT);
		puts(BGREEN"Amount Deposited."RESET);
	}else{
		puts("Amount exceeds Max.Deposit limit!!");
		puts("Try again!!");
	}
}
///

///
void withdraw(Acc *usr){
	f64 amt=0;
	printf("\nEnter Withdrawal Amount:");
	scanf("%lf",&amt);
	if(amt<=0){
                puts("Amount cannot be negative!!");
                puts("Try again!!");
        }else if(amt<MAX_WITHDRAW){
		if(amt<=usr->bal){
			usr->bal -= amt;
			//update 2 transc
			addTran(usr,-amt,WITHDRAW);//1
			puts(BGREEN"Amount Withdrawn."RESET);
		}else{
			puts("Low Balance!!");
		}
	}else{
		puts("Amount exceeds Max.Withdraw limit!!");
		puts("Try again!!");
	}
}
///

///
void transfer(Acc *from,Acc *to){
        f64 amt=0;
        printf("\nEnter Transfer Amount:");
        scanf("%lf",&amt);
        if(amt<=0){
                puts("Amount cannot be negative!!");
                puts("Try again!!");
        }else if(amt<MAX_TRANSFER){
                if(amt<=from->bal){
                        from->bal -= amt;
			to->bal   += amt;
                        //update 2 transc of both
			addTran(to,+amt,TRANSFER_IN);
			addTran(from,-amt,TRANSFER_OUT);
                        puts(BGREEN"Amount Transfered."RESET);
                }else{
                        puts("Low Balance!!");
                }
        }else{
                puts("Amount exceeds Max.Transfer limit!!");
                puts("Try again!!");
        }
}
///

///
void addTran(Acc *usr,f64 amt,char type){
	Tran *new=calloc(1,sizeof(Tran));
	new->amt=amt;
	new->id =getTranId(usr);
	new->type=type;
	new->nxt=NULL;

	new->nxt=usr->tranHist;
	usr->tranHist=new;

	(usr->tranCnt)++;
}

u64 getTranId(Acc *usr){
	//17 digit unq TranID
	srand(usr->num);
        return getTimeStamp()*1000 +(rand()%1000);
}
///

///
void statement(Acc *usr){
    Tran *temp = usr->tranHist;
    if (temp) {
        printf(BCYAN"\n%-20s%-15s%-12s\n", "Transaction ID", "Amount (Rs)","Type");
        puts("----------------------------------------");
        while (temp) {
            printf("%-20llu%-+15.2lf",temp->id,temp->amt);
	    if(temp->type==DEPOSIT)	 printf("%-12s\n","Deposit");
	    else if(temp->type==WITHDRAW)printf("%-12s\n","Withdraw");
	    else if(temp->type==TRANSFER_IN)printf("%-12s\n","Tranfer IN");
	    else if(temp->type==TRANSFER_OUT)printf("%-12s\n","Tranfer OUT");
            temp = temp->nxt;
        }
    } else {
        puts("No Transaction History!");
    }
    printf(RESET);
}
///

///
void database(Acc *head){
	if(!head){
		puts("Empty Database!!WTF");
		return;
	}
	printf(BBLUE"\n%-20s|%-30s|%-14s|%-12s\n",
			"Account ID",
			"Holder Name",
			"Mobile(+91)",
			"Transactions"RESET);
	while(head){
		printf("%-20llu|%-30s|+91-%-10llu|%-12llu\n",
				head->num,
				head->name,
				head->phno,
				head->tranCnt);
		head=head->nxt;
	}
}
///

///
void saveData(Acc *head){

	FILE *fp=fopen("data/Db","w");
	int len;
	
	while(head){
		fwrite(head,szDb,1,fp);
		len=strlen(head->name);
		fwrite(&len,sizeof(len),1,fp);
		fwrite(head->name,sizeof(char)*len,1,fp);

		//save bank statement
		char spName[25];
		sprintf(spName,"data/%llu",head->num);
		FILE *sp=fopen(spName,"w");
		Tran *t=head->tranHist;
		while(t){
			fwrite(t,sizeof(Tran)-sizeof(Tran*),1,sp);
			t=t->nxt;
		}
		fclose(sp);
		head=head->nxt;
	}

	fclose(fp);
}
void syncData(Acc **head){
	FILE *fp=fopen("data/Db","r");
	if(!fp)return;
        int len;
	Acc temp,*tail=NULL;

	temp.nxt=NULL;
	temp.tranHist=NULL;
	temp.tranCnt=0;
        while(fread(&temp,szDb,1,fp)){
                fread(&len,sizeof(len),1,fp);
		//char *str=malloc(sizeof(char)*(len+1));
                //fread(str,sizeof(char)*len,1,fp);
		//temp.name=str;
		char buff[NAME_LEN]={0};
                fread(buff,sizeof(char)*len,1,fp);
		temp.name=strdup(buff);

		Acc *new =calloc(1,sizeof(Acc));
		memmove(new,&temp,sizeof(Acc));
		if(!(*head))*head=new;
		if(tail)tail->nxt=new;
		tail=new;
		
                //save bank statement
                char spName[25];
                sprintf(spName,"data/%llu",new->num);
                FILE *sp=fopen(spName,"r");
		if(!sp)continue;
                Tran *th=NULL,*tt=NULL,tm;
		int cnt=0;
		tm.nxt=NULL;
                while(fread(&tm,sizeof(Tran)-sizeof(Tran*),1,sp)){
			Tran *c=malloc(sizeof(Tran));
			cnt++;
                        memmove(c,&tm,sizeof(Tran));
			if(!th)th=c;
			if(tt)tt->nxt=c;
                        tt=c;
                }
		new->tranHist=th;
		new->tranCnt=cnt;
                fclose(sp);
        }

        fclose(fp);
}
///
