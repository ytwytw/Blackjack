/*
Junhua Zhang
Ryerson University
Computer Engineering Student
This is assignment4
junhua.zhang@ryerson.ca
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#define SERVER_PORT_NUM 2944            //define port number
#define SERVER_IP_ADDRESS "127.0.0.1"	//define server address
#define BACKLOGS 4						//useless in the client 
#define TRUE 1		// This is True, mad?
#define FALSE 0		// This is false, yeah!

int main() {
while (1==1) {		// I love looooooooooooops as much as you do
    int clientSockFd;	//this is how to identify myself
    int len;
    char shit[255]="0xdeadbeef";  //this is the secret i am sending to the server
    char damn[255];	//oh god damn it!!!
    int lolwut=0;	//lol wut ?!
    struct sockaddr_in serverAddress;
    int result;	//result is result, what is the matter?!
	char ch='A';	// A is for a boss like me :P
    clientSockFd = socket(PF_INET, SOCK_STREAM, 0); //provided in the Bb!!!
    serverAddress.sin_family = AF_INET; //use AF_INET NO IPv6 YAY party?!
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS); //ip-serverAddress
    serverAddress.sin_port = htons(SERVER_PORT_NUM); //port number
    memset(serverAddress.sin_zero, '\0', sizeof(serverAddress.sin_zero) ); //provided in the Bb!!!
    len = sizeof(serverAddress); //now i figure out where i should go...
	system("clear"); //clean the screen
    //connecting to server
    result = connect(clientSockFd, (struct sockaddr *)&serverAddress, len);
    if (result == -1)
    {
        fprintf(stderr,"\n\nI cannot connect ytwytw's BlackJact Server :( \n\n");
        exit(1);
    }
    //after it connects the server...
	read(clientSockFd, &damn, 255);		//reading the welcome msg
	printf("\nMessage from server: %s\n", damn); 
	read(clientSockFd, &damn, 255);		//reading my ip
	printf("\nMessage from server: %s\n", damn); 
	//Sending the damn secret
    printf("\nSending secret \"%s\" to the server\n", shit);
	write(clientSockFd, &shit, 255);
    //read a byte from the server?! NO!!! I am reading 255 bytes from the server LOL
    read(clientSockFd, &shit, 255);
    printf("\nThe secret \"%s\" has been received by the server\n", shit);	//just wanna make sure he got my candy
    read(clientSockFd, &shit, 255);
    printf("\nmsg from the server = %s\n", shit);  //let's see what my boss got for me
    lolwut = strncmp(shit, "Game Start!", 10); //Does it match?!
	if (lolwut != 0) {			//if NOPE
		close(clientSockFd);	//then... 
		exit(1);				//Kick!!!
	}
    //Game starts here!
    int roundno=0;
    int card0=0;
    int card1=0;
    int systemcode=0;
    int buffer=0;
    int score1=0; 
    int score2=0;
    // I am sorry for those annoying variables, i mean, those **** O.o
    while (TRUE) {	//Life saver when you wanna play it again!
        read(clientSockFd, &roundno, 4);	//just read round number, as advertised... 
        if (roundno>1) {
            system("clear");	//just wanna make it clean... who wanna see dusts?! you?!
        }
        printf("\nThis is round %i\n",roundno); //print out the round # as required...

        //jumps to dealplayer start
        read(clientSockFd, &card0, 4);	//read first card
        read(clientSockFd, &card1, 4);	//read second card
        printf("\nYour cards : %d %d\n", card0, card1);	//see the two cards
        read(clientSockFd, &systemcode, 4);	//getting systemcode (sth like signal) 
        if (systemcode==999){	// incidents happens, sometimes
            do {
                printf("\nAce 1 or 11?:\n");
                scanf("\n%d", &buffer);			//you know what i am doing, so yeah
            }
            while (buffer==1 || buffer ==11);
            write(clientSockFd, &buffer, 4);	//get my answer back to the server :O
            read(clientSockFd, &systemcode, 4);		//get my question from the server :S
            if (systemcode==132) {printf("\nok~\n");}	//to show this thing does go through.
        }
        else {printf("\nok~~~\n");}		//to show that thing does go through...
        //dealplayer ends
            
        //jumps to dealdealer
        read(clientSockFd, &card0, 4);	//read cards
        read(clientSockFd, &card1, 4);	//still...
        printf("\nDealer  cards : %d %d\n", card0, card1);    // so you can see now
        //dealdealer ends, THATS IT?!
            
        //jumps to gameplayer 
            while(TRUE) {		//dont tell me you hate looooooooooooooooooooops
                printf("\nWanne More Cards?! [Y/N]\n");		//yeah some more cards are tasty
                scanf("\n%c", &ch);		//tell me if you wanna it or not
                ch = toupper(ch);		//convert to upper class, just for fun :P
                write(clientSockFd, &ch, 1);	//Send my wish to the server
                if (ch=='N') {		//if you say no
                    break;			//then my heart breaks
                }
                read(clientSockFd, &card0, 4);	//read my wish from the server
                if (card0 == 1 || card0 == 11) {	//sometimes, incident does happen...
                    do {
                        printf("\nAce 1 or 11?:\n");
                        scanf("\n%d", &buffer);		//dont ask me if you dont know!
                    }
                    while (buffer==1 || buffer ==11);	//too much loops, i know
                    write(clientSockFd, &buffer, 4);	//write what i want back to the server
                }
                read(clientSockFd, &buffer, 4);		//let me see what I have right now...
                printf("Your card total is: %d\n", buffer);	//so yeah, i see it now~
                if (buffer > 21) {		//oh ho,noooooooooo
                    break;		// </3
                }
            }
            
        //gamplayer ends ends
            
        read(clientSockFd, &systemcode, 4); //i dont even know what i am reading now
        system("clear");	//so i clear the screen for you
   
		read(clientSockFd, &score1, 4);				//so here is...
		printf("\nYour Card Total: %d\n", score1);	//your good/bad news
		read(clientSockFd, &score2, 4);				//and there is...
		printf("Dealer Card Total: %d\n", score2);	//you lost/win
        //The following is to figure out you beat the casino or you got beaten by the casino
		read(clientSockFd, &systemcode, 4);
		if (systemcode==233) {	
			printf("\nTIE!!! :O\n");
	    }
        if (systemcode==466) {
            printf("\nYou WIN!!! :D\n");
        }
        if (systemcode==699) {
            printf("\nDealer wins D:\n");
        }
        printf("\nDo you want to play again? [Y/N]: \n"); // wanna more candy?!
        scanf("\n%c", &ch);								  // Tell me then~
        ch = toupper(ch);	//convert to upper case
        write(clientSockFd, &ch, 1);	//tell my wish to the server
        read(clientSockFd, &roundno, 4);	//get how many rounds have been run
        read(clientSockFd, &systemcode, 4);	//check systemcode/signal
        if (systemcode==555) {	//oh no
            system("clear");	//why you leave me alone
            printf("\nThanks for playing :)\n\nYou have played %i rounds.\n\n", roundno-1); //good luck then
            break; // </3
        }
    }   
    close(clientSockFd); //farewell, bye server~
    return 0;
} //while loop
} //main 
