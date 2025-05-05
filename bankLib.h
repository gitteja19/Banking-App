// bankers header file
//

#ifndef _BANKLIB_H_
#define _BANKLIB_H_


#define MAX_DEPOSIT	30000 //30K
#define MAX_WITHDRAW	30000 //30k
#define MAX_TRANSFER 	100000//1lk

#define NAME_LEN 30
#define MAX_PASS_LEN 20
#define MAX_USRN_LEN 20

#define ADMIN_USRN "admin"
#define ADMIN_PASS "admin"
#define ADMIN_EXIT "exit"

#define WITHDRAW 1
#define DEPOSIT  2
#define TRANSFER_IN 3
#define TRANSFER_OUT 4

#define CAPS(ch) (ch &=~(32))

//decorations
#define RESET   "\033[0m"
#define BBLACK  "\033[1;30m"
#define BRED    "\033[1;31m"
#define BGREEN  "\033[1;32m"
#define BYELLOW "\033[1;33m"
#define BBLUE   "\033[1;34m"
#define BPINK   "\033[1;35m"
#define BCYAN   "\033[1;36m"
#define BWHITE  "\033[1;37m"

typedef unsigned long long int u64;
typedef double f64;

typedef struct A{
        f64 amt;
        u64 id;

	char type;
	struct A *nxt;
}Tran;

typedef struct B{
        u64 num;//unique acc num/id
        f64 bal;//bank balance
        u64 phno;//mobile
        char usrName[MAX_USRN_LEN];
	char pass[MAX_PASS_LEN];
        char *name;//name
        
	Tran *tranHist;
        u64 tranCnt;
	struct B *nxt;
}Acc;

extern const int szDb;

//**functions**\\

//Account-handling
//main
void loginMenu(void);
void adminMenu(void);
void userMenu(void);
void accMenu(void);
void menu(void);

Acc* isValid(Acc*,char*,char*);
int isUnq(Acc*,char*);
void dispAcc(Acc*);

void newAcc(Acc**);
void updateAcc(Acc**,Acc*);
void dltAcc(Acc**);
Acc* getAcc(Acc*);

void withdraw(Acc*);
void deposit(Acc*);
void transfer(Acc*,Acc*);
void addTran(Acc*,f64,char);
void balance(Acc*);
void statement(Acc*);
void database(Acc*);

///sub
u64   getUnqId(Acc*);
u64   getTranId(Acc*);
u64   getTimeStamp(void);
char  getKey(void);
char* getStr(void);
void  format(char*);

//file-handling
void saveData(Acc *);
void syncData(Acc **);

#endif
