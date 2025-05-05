

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "bankLib.h"



int main(){
	Acc *db=NULL,*from=NULL,*to=NULL;
	char key='\0',*pass=NULL,*usr=NULL;
	int bye=0;

	//create data folder is not present
	mkdir("data", 0777);
	syncData(&db);
	puts(BRED"Hello All!!"RESET);
	puts("");
	while(1){
		//wait for login
		loginMenu();
		printf(BYELLOW"Enter Username:"RESET);
		usr=getStr();
		printf(BYELLOW"Enter Password:"RESET);
		pass=getStr();
		
		if(!strcmp(usr,ADMIN_USRN)){
			if(!strcmp(pass,ADMIN_PASS))key='A';
			else if(!strcmp(pass,ADMIN_EXIT))exit(1);
		}else if(from=isValid(db,usr,pass)) key='C';
		else{
				puts(BRED"Invalid credentials!"RESET);
				continue;
		}
		free(usr);free(pass);	

		if(key=='A'){
			bye=0;
			while(1){
				adminMenu();
				key=getKey();
				if(!db){
					if((key=='C')||(key=='Q'));
					else{
						puts(BRED"Empty DataBase!!"RESET);
						continue;
					}
				}

				if(key=='H'||key=='W'||key=='D'||key=='T'||key=='B'||key=='F'||key=='U'){
					puts(BGREEN"=== Enter Customer Info ==="RESET);
					from=getAcc(db);
					if(!from){
						puts("Not found!! Try again.");
						continue;
					}

				}
				switch(key){
					case 'C':newAcc(&db);
						 break;
					case 'U':updateAcc(&db,from);
						 break;
					case 'H':statement(from);
						 break;
					case 'W':withdraw(from);
						 break;
					case 'D':deposit(from);
						 break;
					case 'B':balance(from);
						 break;
					case 'T':puts(BGREEN"==:Enter Receiver's info:=="RESET);
						 to  =getAcc(db);
						 if(!to){
							puts("Not found!! Try again.");
							break;
						 }
						 transfer(from,to);
						 break;
					case 'E':database(db);
						 break;
					case 'F':dispAcc(from);
						 break;
					case 'Q':saveData(db);
						 bye=1;
						 break;
					default :puts("invalid option!.");
						 break;
				}
				if(bye){
					puts(BWHITE"Thank you for your work,Admin <3"RESET);
					break;
				}
			}
		}else if(key=='C'){
			bye=0;
			while(1){
				userMenu();
				key=getKey();
				switch(key){
					case 'H':statement(from);
						 break;
					case 'W':withdraw(from);
						 break;
					case 'D':deposit(from);
						 break;
					case 'B':balance(from);
						 break;
					case 'T':puts("==:Enter Receiver's info:==");
						 to  =getAcc(db);
						 if(!to){
							 puts("Not found!! Try again.");
							 break;
						 }
						 transfer(from,to);
						 break;
					case 'Q':saveData(db);
						 bye=1;
						 break;
					default :puts("invalid option!.");
						 break;
				}
				if(bye){
					puts("Happy to help, bye!! :)");
					break;
				}

			}
		}

	}
}

