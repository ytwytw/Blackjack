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

int dealplayer(int player, int clientSockFd) {
	int choicetrigger=999,passs=132;		//define systemcode
    int cards[2], choice;					//some necessary, you know~
    cards[0] =2 + rand() / (RAND_MAX / 9 + 1);		//random cards are from here
    cards[1] = 2 + rand() / (RAND_MAX / 9 + 1);		//good luck players :D
    player = cards[0] + cards[1];			//add it up~
//  printf("\nYour Cards  : %d, %d", cards[0], cards[1]);		//DEBUG
    write(clientSockFd, &cards[0], 4);  //Send cards 0
    write(clientSockFd, &cards[1], 4);  //Send cards 1
    if(cards[0] == 11 && cards[1] == 11)	
        {player = player - 10;}
 	if(cards[0] == 11 || cards[1] == 11) {		//something called incident happens here
        do {
//				printf("\nAce 1 or 11?: ");				//DEBUG
       		 	write(clientSockFd, &choicetrigger, 4);
        		read(clientSockFd, &choice, 4);
				if(choice == 1)
            		{player = player - 10;}
        }
	
        while(choice == 1 || choice == 11);		//check if it is fine now
    }
    write(clientSockFd, &passs, 4);		//tell my clients you passed the final
    fflush(stdout);						//clean leftover as always
    return player;
}

int dealdealer(int dealerrr, int clientSockFd) {
    int cards[2];		//so i have two cards now
    cards[0] = 2 + rand() / (RAND_MAX / 9 + 1);		//this is my first one
    cards[1] = 2 + rand() / (RAND_MAX / 9 + 1);		//and this is my second one
    dealerrr = cards[0] + cards[1];		//then add it up~
//  printf("\nDealer Cards: %d, %d\n", cards[0], cards[1]);			//DEBUG
    write(clientSockFd, &cards[0], 4); // send dealer card 0
    write(clientSockFd, &cards[1], 4); // send dealer card 1
	if((cards[0] == 11) || (cards[1] == 11)) {	//sometimes
		if(dealerrr > 21)						//incidents
            dealerrr = dealerrr - 10;			//do
    }											//happen
    fflush(stdout);		//clean leftover
    return dealerrr;	
}

int gameplayer(int player,int clientSockFd) {
    int card;
    char choice;
    do {
//      printf("\nWanne More Cards?! [Y/N]\n");  //DEBUG
        read(clientSockFd, &choice, 4);  //read answer from the client
        choice = toupper(choice);		//for the sake of my life then i upper case it
        switch(choice)					//so miss my switches
        {
            case 'Y': card = 2 + rand() / (RAND_MAX / 9 + 1);	//this is when you wanna more card
                write (clientSockFd, &card, 4);		//send card to the client
                while (card == 1 || card == 11)			//deal
                {										//with
                    if(card == 11) {					//some 
                        printf("\nAce 1 or 11?: ");		//incidents
                        fflush(stdout);					//now
                        read(clientSockFd, &choice, 4); //read answer from clients 
                    }
                }
                player = player + card; //add it up
//              printf("Your card total is: %d\n", player); //DEBUG
                write(clientSockFd, &player, 4);    //send the result to the client
                if(player > 21) {
                    printf("You bust!\n");  //too bad
                    choice = 'z';
//                    system("clear");      //no candy for you
                    break;
                }
                break;      //jump out of the loop

            case 'N':break; //sth lik prison break
        }
    }
    while(choice == 'Y');   //check user input
    return player;
}

int gamedealer(int dealerr) {
    int card;
    while (dealerr < 17) {  //this is my dealer
        card = 2 + rand() / (RAND_MAX / 9 + 1);     //generate random cards
        dealerr = dealerr + card;       //add it up
        if (card == 11 && dealerr > 21)     //check if player i screwed D:
        {card = card -10;}
        if (dealerr > 21)                   //or the dealer got screwed :P
        {printf("Dealer just got screwed!\n\n");}
    }
    return dealerr;
    
}