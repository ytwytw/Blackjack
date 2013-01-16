/*
Junhua Zhang
Ryerson University
Computer Engineering Student
This is assignment4
junhua.zhang@ryerson.ca
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "dealer.h"
#define SERVER_PORT_NUM 2944				//Port Number
#define SERVER_IP_ADDRESS "127.0.0.1"		//Useless in the server code
#define BACKLOGS 4							//Max number of clients
#define TRUE 1
#define FALSE 0
char ipstr[INET6_ADDRSTRLEN];  //store ip address, no choice other than Gobi it

void workout(int clientSockFd){
	//The followings are all kinda message sent to the clients
	char shit[255];
    char welcome1[255]="Welcome to ytwytw's Blackjack Server";
    char troll[255]="Game Start!";
    char lolwut[255]="Secret is NOT Matched, You just lost the Game~";
    int watchout=555,normal=000,tied=233,wins=466,lost=699,incidents=444;  //define system code
    int iMad=0; // I just mad about this... new apple product! [BUY IT]
	write(clientSockFd, &welcome1, 255);	//send welcome message
	write(clientSockFd, &ipstr, 255);      //send client ip address
    printf("adding client on fd %d\n", clientSockFd); //so i know someone hook me up
	read(clientSockFd, &shit, 255); // Read texture entered from the client
	printf("\nmsg received: %s\n", shit); //for debug purpose
	write(clientSockFd, &shit, 255); 	//send message back to the client
	iMad = strncmp(shit, "0xdeadbeef", 10);	// here is the password
	if (iMad != 0) {						// dont lose it
		write(clientSockFd, &lolwut, 255);	// otherwise
		close(clientSockFd);				// you are kicked out
	}										// of this place
	write(clientSockFd, &troll, 255);		// To let you know my troll msg~
	
	//BlackJack actually Starts right here :D
	srand(time(NULL));	//guarantee randomness, new seeds everyday 100% guaranteed!!!
    char again;  //check if needs loop back again
    int dealertotal, playertotal, roundno=1; //some necessary job
    do {	//DO IT!!!
//      printf("This is round %i \n", roundno); //DEBUG
        write(clientSockFd, &roundno, 4);  //Send Round # to client      
        playertotal = dealplayer(playertotal, clientSockFd);	//player action
        dealertotal = dealdealer(dealertotal, clientSockFd);	//dealer action
        playertotal = gameplayer(playertotal, clientSockFd);	//validate action
        
        if(dealertotal < 17 && playertotal < 21) {	//sometimes
            dealertotal = gamedealer(dealertotal);	//incidents
            write(clientSockFd, &incidents, 4);		//does
        }											//happen
        else {										//just
            write(clientSockFd, &normal, 4);		//like
        }											//this

//      printf("Your Card Total: %d\n", playertotal); //DEBUG
        write(clientSockFd, &playertotal, 4);	//send player card total to client
        
//      printf("Dealer Card Total: %d\n",dealertotal); //DEBUG
        write(clientSockFd, &dealertotal, 4);	//send dealer card total to client
        
        // The following is checking who wins the game... - -|
        if(playertotal == dealertotal) {
//          printf("\nTIE!!! :O\n");		//DEBUG
            write(clientSockFd, &tied, 4);  //send tie system code
        }
        if((playertotal > dealertotal && playertotal <= 21) || dealertotal > 21) {
//          printf("\nYou WIN!!! :D\n");	//DEBUG
            write(clientSockFd, &wins, 4);  //send win system code
        }
		if(playertotal > 21) {
//          printf("\nDealer wins D:\n");   //DEBUG
            write(clientSockFd, &lost, 4);  //send lost system code
        }
        if(dealertotal > playertotal && dealertotal <= 21) {
//          printf("\nDealer wins D:\n");	//DEBUG
            write(clientSockFd, &lost, 4);  //send lost system code
        }
//      printf("\nDo you want to play again? [Y/N]: \n");       //DEBUG
        read(clientSockFd, &again, 1);	//get input from client to see if needs loop back
//        scanf("\n%c", &again);
        again = toupper(again);	//uppercase FTW
        srand(time(NULL));  //just wanna be random~
        roundno++;	//just round number +1,for candy
        write(clientSockFd, &roundno, 4);  //Send Round #
        if (again=='Y') {                       //if you say yeah yeah yeah
            write(clientSockFd, &normal, 4);    //then lets keep going
        }
        if (again=='N') {                       //if you say no no no
            write(clientSockFd, &watchout, 4); //no fun allowed then
        }
    }
    
    while(again == 'Y');
    
    printf("\nThanks for playing :)\n\nYou have played %i rounds.\n\n", roundno-1);
	close(clientSockFd);	//kick the client, bye bye
	//BlackJack Ends
}

int main() {
    //The following code are provided by the Lab Slides or from TA
    int serverSockFd, clientSockFd, pid;
    socklen_t serverLen, clientLen;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    struct sockaddr_storage addr;
	serverLen = sizeof addr;
    serverSockFd = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(SERVER_PORT_NUM);
    serverLen = sizeof(serverAddress);
    clientLen = sizeof(clientAddress);
    bind(serverSockFd, (struct sockaddr *)&serverAddress, serverLen);
    listen(serverSockFd, BACKLOGS);
    while (TRUE) {
		printf("\nWaiting for clients...\n");
		clientSockFd = accept(serverSockFd, (struct sockaddr *)&clientAddress, &clientLen);
		//TEST FOR GET IP of the clients
		getpeername(clientSockFd, (struct sockaddr*)&addr, &serverLen);
    	struct sockaddr_in *s = (struct sockaddr_in *)&addr;
    	inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
    	printf("\nCustomer IP: %s\n", ipstr);
    	//TEST FOR GET IP of the clients
		if (clientSockFd == -1) {			//check client available
			printf("\nAccept Error\n");
			exit(1);
		}
        pid = fork();		//create threads
        printf("\nCreating new thread...\n");
    	if (pid < 0)
            printf("\nFork Error\n");
        if (pid == 0)  {
            close(serverSockFd);
            workout(clientSockFd);	//target thread workout
            exit(0);
        }
        else close(clientSockFd);   //just kick out
     }
    close(serverSockFd); //usually never reach here
    return 0;
}


