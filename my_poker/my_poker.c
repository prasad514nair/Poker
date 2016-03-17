#include<stdio.h>
#include<conio.h>
#include <time.h>

#define FOLD 1
#define RAISE 0
#define FLOP 3
#define TURN 4
#define RIVER 5
#define SUITS 4
#define FACES 13
#define AVAILABLE 0
#define TAKEN 1
#define TRUE 1
#define FALSE 0
#define NUM_RANKS 13



int straight, flush, four, three,straight_flush,royal_flush;
int pairs = 0;
int player1Coins=100;
int player2Coins=100;
int suitsForPlayer1[2] ;
int facesForPlayer1[2] ;
int suitsForPlayer2[2] ;
int facesForPlayer2[2] ;
int suitsForTable[5] ;
int facesForTable[5] ;
int branches[10]={0};
int player1_prev[200]={0};
int player2_prev[200]={0};
int sub_branches[10]={0};
char *suits[4] = { "Hearts", "Diamonds", "Spades", "Clubs" };
char *faces[13] = { "Two", "Three", "Four", "Five", "Six", "Seven",
		"Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
char *rank_hands[10] = {"HIGH CARD","ONE PAIR","TWO PAIR","THREE OF A KIND","STRAIGHT","FLUSH","FULL HOUSE","FOUR OF A KIND","STRAIGHT FLUSH","ROYAL FLUSH"};
		


void dealTable(int suitsInTable[], int facesInTable[], char *suits[], char *faces[], int card_deck[][FACES],int suitsForTable[], int facesForTable[]);
int evaluation_function(int suitsInRound1[],int facesInRound1[],int open_suitsInTable[],int open_facesInTable[],int no_open_cards,int level);
int isFlush(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open);
void shuffle_card( int card_deck[][ 13 ] );
void dealCard(int suitsInRound[], int facesInRound[], char *suits[], char *faces[], int card_deck[][FACES],int *suitsForPlayer,int *facesForPlayer);
void dealRound(int suitsInRound[], int facesInRound[], char *suits[], char *faces[], int card_deck[][FACES],int suitsForPlayer[],int facesForPlayer[] );
void scoreRound(int suitsInRound[], int facesInRound[]);
void displayResults(int suitsInRound[], int facesInRound[], int *pointValue);
void winning_combinations(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open_cards);
void checkHand(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open);
int isFullHouse(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open);
void winning_combinations_table(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open);
int isHighCard(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open);

void main()
{
	int round=0;
	while(player1Coins>0 && player2Coins>0){	
		

		int card_deck[4][13] = { { AVAILABLE } };
		int table[5][5]={0};
		int suitsInRound[4] = {0} ;
		int facesInRound[13] = {0};
		int suitsInRound2[4] = {0};
		int facesInRound2[13] = {0};
		int suitsInTable[4] = {0} ;
		int facesInTable[13] = {0};
		int player1Score = 0;
		int player2Score = 0;
		int player1Win = 0;
		int player2Win = 0;
	
		int winner=0;
		
		int player1action=0;
		int open_suitsInTable[5]={0};
		int open_facesInTable[5]={0};
		int pot=0;
		int evaluated_value=0;
		int i,j,prev;
		int fold=FALSE;
		
			srand( time( NULL ) ); 
			shuffle_card( card_deck );

			round++;
			printf("ROUND %d\n", round);
			printf("\nPlayer 1 has %d coins:\n",player1Coins);
			printf("\nPlayer 2 has %d coins:\n",player2Coins);
			printf("\nEnter any key to continue.........\n");
			getchar();
			
	
			dealRound(suitsInRound, facesInRound, suits, faces, card_deck,suitsForPlayer1,facesForPlayer1);
			printf("\nPlayer 1 has following cards:\n");
			for(i=0;i<2;i++){
				printf("%5s of %-8s \n", suits[suitsForPlayer1[i]], faces[facesForPlayer1[i]]);
				
			}
			printf("\n\n");
			
			dealRound(suitsInRound2, facesInRound2, suits, faces, card_deck,suitsForPlayer2,facesForPlayer2);
			printf("\nPlayer 2 has following cards:\n");
			for(i=0;i<2;i++){
				printf("%5s of %-8s \n",  faces[facesForPlayer2[i]],suits[suitsForPlayer2[i]]);
			}
			printf("\n\n");
			
			dealTable(suitsInTable, facesInTable, suits, faces, card_deck, suitsForTable, facesForTable);
			printf("\nTable has following cards:\n");
			for(i=0;i<5;i++){
				printf("%5s of %-8s \n",  faces[facesForTable[i]],suits[suitsForTable[i]]);
			}
			
			
				printf("\n\n-----FLOP------------\n\n");
				for(j=0;j<3;j++){
					printf("%5s of %-8s \n", faces[facesForTable[j]],suits[suitsForTable[j]]);   //Flop
					open_suitsInTable[j]=suitsForTable[j];
					open_facesInTable[j]=facesForTable[j];
				}
				player1Coins=player1Coins-5;
				player2Coins=player2Coins-5;
				pot=pot+10;
				evaluated_value = evaluation_function(suitsForPlayer1,facesForPlayer1,open_suitsInTable,open_facesInTable,FLOP,0);
			//	printf("\n evlauated value for FLOP:%d \n",evaluated_value );
				printf("\n Enter a key to open TURN\n");
				getchar();
			
				if(evaluated_value<4){
						printf("\n\n-----TURN------------\n\n");
						printf("%5s of %-8s \n", faces[facesForTable[3]],suits[suitsForTable[3]]);   //Turn
						open_suitsInTable[3]=suitsForTable[3];
						open_facesInTable[3]=facesForTable[3];
						player1Coins=player1Coins-10;
						player2Coins=player2Coins-10;
						pot=pot+20;
						evaluated_value = evaluation_function(suitsForPlayer1,facesForPlayer1,open_suitsInTable,open_facesInTable,TURN,0);
					//	printf("\n evlauated value for TURN:%d \n",evaluated_value );
						printf("\n Enter a key to open RIVER\n");
						getchar();
				
						if(evaluated_value<3){
							printf("\n\n-----RIVER------------\n\n");
							printf("%5s of %-8s \n", faces[facesForTable[4]],suits[suitsForTable[4]]);   //River
							open_suitsInTable[4]=suitsForTable[4];
							open_facesInTable[4]=facesForTable[4];
							player1Coins=player1Coins-15;
							player2Coins=player2Coins-15;
							pot=pot+30;
							evaluated_value = evaluation_function(suitsForPlayer1,facesForPlayer1,open_suitsInTable,open_facesInTable,TURN,0);
						//	printf("\n evlauated value for TURN:%d \n",evaluated_value );
							
						
							winning_combinations(suitsForPlayer1,facesForPlayer1,open_suitsInTable,open_facesInTable,TURN);
							for(i=10;i>0;i--){
								if(branches[i]==1){
									player1Win=i;
								//	printf("\n i:%d, winner1:%d\n",i,player1Win);
									printf("\n Player1 has %5s:\n",rank_hands[i]);
								
									break;
								}
							}
							
							winning_combinations(suitsForPlayer2,facesForPlayer2,open_suitsInTable,open_facesInTable,TURN);
							for(i=10;i>0;i--){
								if(branches[i]==1){
									player2Win=i;
							//		printf("\n i:%d, player2:%d\n",i,player2Win);
									printf("\n Player2 has %5s:\n",rank_hands[i]);
								
									break;
								}
							}
							if(player1Win>player2Win){
								printf("\n--------------Player1 won this round-------------------\n");
								player1Coins=player1Coins + pot;
							}
							else if(player1Win<player2Win){
							
								printf("\n--------------Player2 won this round-------------------\n");
								player2Coins=player2Coins + pot;
							}
							else if(player1Win == player2Win){
								printf("\n--------------This round ended in a draw-------------------\n");
								player1Coins=player1Coins + (pot/2);
								player2Coins=player2Coins + (pot/2);
							}
							else{
								printf("\n--------------ERROR-------------------\n");
							}
							
							
						}
						else{
							player2Coins=player2Coins + pot;
							printf("\n------------Player 1 Folded-----------\n");
						
						}
						
						
					
				}
				else{
					player2Coins=player2Coins + pot;
					printf("\n------------Player 1 Folded-----------\n");
				}
				
		getchar();
	}
	
	printf("\n--------------------GAME OVER------------------------------\n");
	if(player2Coins<=0){
		printf("\n------------------PLAYER 1 WON THE GAME-------------------------\n");
	}else{
		printf("\n------------------PLAYER 2 WON THE GAME-------------------------\n");
	}
}

//DISTRIBUTE CARDS TWO CARDS EACH TO TWO PLAYERS AND FIVE CARDS TO TABLE AND REMOVE IT FROM THE PACK OF 52 

void shuffle_card( int card_deck[][ 13 ] )
{
	int row; 
	int column; 
	int card; 

	
	for ( card = 1; card <= 52; card++ )
	{
		do 
		{
			row = rand() % 4; 
			column = rand() % 13; 
		} while( card_deck[ row ][ column ] != 0 ); 

		
		card_deck[ row ][ column ] = card;
	}
} 


void dealRound(int suitsInRound[], int facesInRound[], char *suits[], char *faces[], int card_deck[][FACES],int suitsForPlayer[],int facesForPlayer[])
{
	int i;

	for(i = 0; i < 2; i++)
		dealCard(suitsInRound, facesInRound, suits, faces, card_deck,&suitsForPlayer[i],&facesForPlayer[i]);
	printf("\n");
}

void dealCard(int suitsInRound[], int facesInRound[], char *suits[], char *faces[], int card_deck[][FACES],int *suitsForPlayer,int *facesForPlayer)
{
	int suitIndex, faceIndex;
	suitIndex = rand() % 4;
	faceIndex = rand() % 13;

	while( card_deck[suitIndex][faceIndex] == TAKEN ){
		suitIndex = rand() % 4;
		faceIndex = rand() % 13;
	}
	card_deck[suitIndex][faceIndex] = TAKEN;
	facesInRound[faceIndex]++;
	suitsInRound[suitIndex]++;
	*suitsForPlayer = suitIndex;
	*facesForPlayer = faceIndex;
}

void dealTable(int suitsInTable[], int facesInTable[], char *suits[], char *faces[], int card_deck[][FACES],int suitsForTable[], int facesForTable[])
{
	int i;

	for(i = 0; i < 5; i++)
		dealCard(suitsInTable, facesInTable, suits, faces, card_deck, &suitsForTable[i], &facesForTable[i]);
	printf("\n");
}


//DISTRIBUTION OF CARDS OVER. PACK CONTAINS NOW 43 CARDS

//EVALUATION FUNCTION IS THE DIFFERENCE BETWEEN HIGHEST RANKING POSSIBLE FROM THE COMBINATION OF CARDS ON TABLE AND THE REMAINING 43 CARDS IN THE PACK 
//AND THE HIGHEST RANKING POSSIBLE FROM THE COMBINATION OF CARDS ON TABLE AND THE PAIR OF CARDS OF THE PLAYER

//EVALUATION STARTS 
int evaluation_function(int suitsForRound1[],int facesForRound1[],int open_suitsInTable[],int open_facesInTable[],int no_open_cards,int level){
	
	int i;
	int utility_value=0;
	winning_combinations(suitsForRound1,facesForRound1,open_suitsInTable,open_facesInTable,no_open_cards);

	winning_combinations_table(suitsForRound1,facesForRound1,open_suitsInTable,open_facesInTable,no_open_cards);
	printf("\n");
//	for(i=10;i>0;i--){
//		printf("sub_branches[%d]:%d\n",i,sub_branches[i]);
//	}
	printf("\n");
//	for(i=10;i>0;i--){
//		printf("branches[%d]:%d\n",i,branches[i]);
//	}
//	getchar();
	utility_value = max_value(level+1,0,10);

//	getchar();
	return utility_value;
}

int max_value(int level,int utility_value,int branch){
	
	int i,j,min_utility_value,max_utility_value;
	i=branch;
	min_utility_value=0;
	max_utility_value=0;
//	printf("\n UTILITY VALUE:%d,i:%d",utility_value,branch);
//	getchar();
	if(level==6)
		return utility_value;

	if(sub_branches[i]==1){
		min_utility_value=1;
	}
		
	if(branches[i]==1){
		max_utility_value=1;
	}
	
	if((min_utility_value-max_utility_value)!=0)
		utility_value++;
	min_value(level+1,utility_value,i-1);
		
		
			
		
}

int min_value(int level,int utility_value,int branch){
	int i,j,min_utility_value,max_utility_value;
	i=branch;
	min_utility_value=0;
	max_utility_value=0;
//	printf("\n UTILITY VALUE:%d,i:%d",utility_value,branch);
//	getchar();
	
	
	if(level==6)
		return utility_value;

	if(sub_branches[i]==1){
		min_utility_value=1;
	}
		
	if(branches[i]==1){
		max_utility_value=1;
	}
	
	if((min_utility_value-max_utility_value)!=0)
			utility_value++;
	
	max_value(level+1,utility_value,i-1);


}

//EVALUATION ENDS

//CALCULATE WINNING COMBINATION POSSIBLE FROM THE CARDS ON THE TABLE AND THE REMAINING CARDS EXCLUDING THE TWO CARDS THAT PLAYER HAS

void winning_combinations_table(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){
	int i,j,k,l,m,n;
	int suits_Round[4] = {0} ;
	int faces_Round[13] = {0};
	int club_store[13]={0};
	int heart_store[13]={0};
	int spade_store[13]={0};
	int diamond_store[13]={0};
	int num_consec = 0;
	int st_flush = 0;
	int rank, suit;
	int table_straight = FALSE;
	int table_straight_flush = FALSE;
	int table_royal_flush = FALSE;
	int table_flush = FALSE;
	int table_four = FALSE;
	int table_three = FALSE;
	int table_pairs = 0;


	for(i=0;i<10;i++){
		sub_branches[i]=0;
	}
	
	
	for(i=0;i<no_open;i++){

		faces_Round[open_facesInTable[i]]++;
	}
	
	
	
	
	
	for(i=0;i<no_open;i++){
	
		suits_Round[open_suitsInTable[i]]++;
		
		if(open_suitsInTable[i]==0)
			heart_store[open_facesInTable[i]]++;
		if(open_suitsInTable[i]==1)
			diamond_store[open_facesInTable[i]]++;
		if(open_suitsInTable[i]==2)
			spade_store[open_facesInTable[i]]++;
		if(open_suitsInTable[i]==3)
			club_store[open_facesInTable[i]]++;
		
	}
	
	if(suits_Round[0]>=no_open-2){
		rank = 0;
		while (heart_store[rank] == 0){
			rank++;
		
		}
	
	
	
			for (; rank < FACES; rank++){
			m=rank+4;
			st_flush=0;
			for(j=rank;j<m;j++){
				if(heart_store[j])
					st_flush++;
				
			}
	
			if(st_flush>=no_open-2){
	
				table_straight_flush=TRUE;
				break;
			}
		}
		if(m==13 && table_straight_flush==TRUE)
			table_royal_flush=TRUE;
	
	
	}
	
	
	if(suits_Round[1]>=no_open-2){
		rank = 0;
		while (diamond_store[rank] == 0){
			rank++;
		
		}
	
	
		for (; rank < FACES; rank++){
			m=rank+4;
			st_flush=0;
			for(j=rank;j<m;j++){
				if(diamond_store[j])
					st_flush++;
				
			}
	
			if(st_flush>=no_open-2){
	
				table_straight_flush=TRUE;
				break;
			}
		}
		if(m==13 && table_straight_flush==TRUE)
			table_royal_flush=TRUE;
	
	
	}
	
	if(suits_Round[2]>=no_open-2){
		rank = 0;
		while (spade_store[rank] == 0){
			rank++;
		
		}
	
	
		for (; rank < FACES; rank++){
			m=rank+4;
			st_flush=0;
			for(j=rank;j<m;j++){
				if(spade_store[j])
					st_flush++;
				
			}
	
			if(st_flush>=no_open-2){
				
				table_straight_flush=TRUE;

				break;
			}
		}
		if(m==13 && straight_flush==TRUE)
			table_royal_flush=TRUE;
	
	
	}

	if(suits_Round[3]>=no_open-2){
		rank = 0;
		while (club_store[rank] == 0){
			rank++;
		
		}
	
		for (; rank < FACES; rank++){
			m=rank+4;
			st_flush=0;
			for(j=rank;j<m;j++){
				if(club_store[j])
					st_flush++;
				
			}

			if(st_flush>=no_open-2){

				table_straight_flush=TRUE;
				break;
			}
		}
		if(m==13 && table_straight_flush==TRUE)
			table_royal_flush=TRUE;
	
	
	}
	
	
	rank = 0;
	while (faces_Round[rank] == 0){
		rank++;
		
	}
		
		for (; rank < FACES; rank++){
			num_consec=0;
			st_flush=0;
			k=rank+4;
	
			for(i=rank;i<=k;i++){
				if(faces_Round[i]){
					num_consec++;
		
				}
			}
			if (num_consec >= no_open) {
				table_straight = TRUE;
				break;
			}
		
		}
		if(table_straight==FALSE)
			table_straight_flush=FALSE;
		if(table_straight_flush==FALSE)
			table_royal_flush=FALSE;
		
		
	for (rank = 0; rank < NUM_RANKS; rank++) {

		if (faces_Round[rank] >= no_open-3)
		table_four = TRUE;

		if (faces_Round[rank] >= no_open-4)
		table_three = TRUE;

		if (faces_Round[rank] >= no_open-5)
		table_pairs++;
	}


	for(i=0;i<4;i++){
		if(suits_Round[i]==no_open-2)
			table_flush = TRUE;
	}



	if(table_royal_flush){
		sub_branches[10]=1;
	
	}
	
	if(table_straight_flush){

		sub_branches[9]=1;
	
	}
	
	if (table_four) { 
	
		sub_branches[8]=1;
	
	}
	if (table_three==1 && table_pairs >= 1) {
	
		sub_branches[7]=1;
	
	}
	
	if (table_flush==1) {
	
		sub_branches[6]=1;
	
	}
	
	 if (table_straight){ 
	
		sub_branches[5]=1;
	
	}
	
	if (table_three) { 
	
		sub_branches[4]=1;
	
	}
	

	if (table_pairs >= 2) { 
	
		sub_branches[3]=1;
	
	}
	
	if (table_pairs >= 1) { 

		sub_branches[2]=1;

	}

}
//CALCULATION OF TABLE WINNING COMBINATION ENDS

//CALCULATE WINNING COMBINATION POSSIBLE OF THE PLAYER
void winning_combinations(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open_cards){
	int i;
	
	for(i=0;i<10;i++){
		branches[i]=0;
	}
	
	branches[10]=isRoyalFlush(suitsForPlayer,facesForPlayer,open_suitsInTable,open_facesInTable,no_open_cards);

	branches[9]=isStraightFlush(suitsForPlayer,facesForPlayer,open_suitsInTable,open_facesInTable,no_open_cards);

	branches[8]=isFourofKind(suitsForPlayer,facesForPlayer,open_suitsInTable,open_facesInTable,no_open_cards);

	branches[7]=isFullHouse(suitsForPlayer,facesForPlayer,open_suitsInTable,open_facesInTable,no_open_cards);

	branches[6]=isFlush(suitsForPlayer,facesForPlayer,open_suitsInTable,open_facesInTable,no_open_cards);

	branches[5]=isStraight(suitsForPlayer,facesForPlayer,open_suitsInTable,open_facesInTable,no_open_cards);

	branches[4]=isThreeofKind(suitsForPlayer,facesForPlayer,open_suitsInTable,open_facesInTable,no_open_cards);

	branches[3]=isTwoPair(suitsForPlayer,facesForPlayer,open_suitsInTable,open_facesInTable,no_open_cards);

	branches[2]=isOnePair(suitsForPlayer,facesForPlayer,open_suitsInTable,open_facesInTable,no_open_cards);

	branches[1]=isHighCard(suitsForPlayer,facesForPlayer,open_suitsInTable,open_facesInTable,no_open_cards);

}

int isRoyalFlush(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){
	checkHand(suitsForPlayer,facesForPlayer,open_suitsInTable,open_facesInTable,no_open);
	
	if(royal_flush){
	
		return 1;
	}
	return 0;

}

int isStraightFlush(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){
	if(straight_flush){
	
		return 1;
	}
	return 0;

}

int isFourofKind(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){
	
	if (four) { 
	
		return 1;
	}
	return 0;
}

int isFullHouse(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){
	
	if (three==1 && pairs >= 1) {
	
		return 1;
	}
	return 0;
}

int isFlush(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){
	
	int i;
	int common_suit=1;
	flush = FALSE;
	
	
	if(suitsForPlayer[0]==suitsForPlayer[1]);
		common_suit++;
	for(i=0;i<no_open;i++){
		if(suitsForPlayer[0]==open_suitsInTable[i]||suitsForPlayer[1]==open_suitsInTable[i]){
			common_suit++;
		}
	}
	
	if(common_suit==no_open){
		flush=TRUE;
		return 1;
	}
	return 0;	
	
}
void checkHand(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){

	int i,j,k,l,m,n,o;
	int suits_Round[4] = {0} ;
	int faces_Round[13] = {0};
	int club_store[13]={0};
	int heart_store[13]={0};
	int spade_store[13]={0};
	int diamond_store[13]={0};
	int num_consec = 0;
	int st_flush = 0;
	int rank, suit;
	straight = FALSE;
	straight_flush = FALSE;
	royal_flush = FALSE;
	flush = FALSE;
	four = FALSE;
	three = FALSE;
	pairs = 0;
	
	
	for(i=0;i<2;i++){
	
		faces_Round[facesForPlayer[i]]++;
	
	}
	for(i=0;i<no_open;i++){

		faces_Round[open_facesInTable[i]]++;
	
	}
	l=0;
	o=0;
	for(i=0;i<2;i++){
	
		suits_Round[suitsForPlayer[i]]++;
	
		if(suitsForPlayer[i]==0)
			heart_store[facesForPlayer[i]]++;
		if(suitsForPlayer[i]==1)
			diamond_store[facesForPlayer[i]]++;
		if(suitsForPlayer[i]==2)
			spade_store[facesForPlayer[i]]++;
		if(suitsForPlayer[i]==3)
			club_store[facesForPlayer[i]]++;
		
	}
	for(i=0;i<no_open;i++){

		suits_Round[open_suitsInTable[i]]++;
	
		if(open_suitsInTable[i]==0)
			heart_store[facesForPlayer[i]]++;
		if(open_suitsInTable[i]==1)
			diamond_store[facesForPlayer[i]]++;
		if(open_suitsInTable[i]==2)
			spade_store[facesForPlayer[i]]++;
		if(open_suitsInTable[i]==3)
			club_store[facesForPlayer[i]]++;
	
	}
	
	
	if(suits_Round[0]>=no_open){
		rank = 0;
		while (heart_store[rank] == 0){
			rank++;
		
		}
	
	
	
		for (; rank < FACES; rank++){
			m=rank+4;
			st_flush=0;
			for(j=rank;j<m;j++){
				if(heart_store[j])
					st_flush++;
				
			}
	
			if(st_flush>=no_open){
				
				straight_flush=TRUE;
				break;
			}
		}
		if(m==13 && straight_flush==TRUE)
			royal_flush=TRUE;
	
	
	}
	
	
	if(suits_Round[1]>=no_open){
		rank = 0;
		while (diamond_store[rank] == 0){
			rank++;
		
		}
	
	
	

		for (; rank < FACES; rank++){
			m=rank+4;
			st_flush=0;
			for(j=rank;j<m;j++){
				if(diamond_store[j])
					st_flush++;
				
			}
	
			if(st_flush>=no_open){
				
				straight_flush=TRUE;
				break;
			}
		}
		if(m==13 && straight_flush==TRUE)
			royal_flush=TRUE;
	
	
	}
	
	if(suits_Round[2]>=no_open){
		rank = 0;
		while (spade_store[rank] == 0){
			rank++;
		
		}
	
	

		for (; rank < FACES; rank++){
			m=rank+4;
			st_flush=0;
			for(j=rank;j<m;j++){
				if(spade_store[j])
					st_flush++;
				
			}
	
			if(st_flush>=no_open){
				
				straight_flush=TRUE;
				break;
			}
		}
		if(m==13 && straight_flush==TRUE)
			royal_flush=TRUE;
	
	
	}
	//Straight and royal Flush of Clubs
	if(suits_Round[3]>=no_open){
		rank = 0;
		while (club_store[rank] == 0){
			rank++;
		
		}
	
	
	
	
		for (; rank < FACES; rank++){
			m=rank+4;
			st_flush=0;
			for(j=rank;j<m;j++){
				if(club_store[j])
					st_flush++;
				
			}
	
			if(st_flush>=no_open){
				
				straight_flush=TRUE;
				break;
			}
		}
		if(m==13 && straight_flush==TRUE)
			royal_flush=TRUE;
	
	
	}
	
	
	
	rank = 0;
	while (faces_Round[rank] == 0){
		rank++;
		
		}
		
		for (; rank < FACES; rank++){
			num_consec=0;
			st_flush=0;
			k=rank+4;
			
			for(i=rank;i<=k;i++){
				if(faces_Round[i]){
					
					num_consec++;
					
					
				}
			}
			
			
			
			if (num_consec == no_open) {
				straight = TRUE;
	
				break;
			}
		
		}
	for(i=0;i<4;i++){
		if(suits_Round[i]==no_open)
			flush = TRUE;
	}
	
		
		
	for (rank = 0; rank < NUM_RANKS; rank++) {
		if (faces_Round[rank] >= no_open-1)
		four = TRUE;

		if (faces_Round[rank] >= no_open-2)
		three = TRUE;

		if (faces_Round[rank] >= no_open-3)
		pairs++;
	}

}

int isStraight(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){

	 if (straight){ 

		return 1;
	}
	return 0;
}


int isThreeofKind(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){

	if (three) { 

		return 1;
	}
	return 0;
}

int isTwoPair(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){
	
	if (pairs >= 2) { 

		return 1;
	}
	return 0;
}

int isOnePair(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){
	
	if (pairs >= 1) { 
	
		return 1;
	}

return 0;
}

int isHighCard(int suitsForPlayer[],int facesForPlayer[],int open_suitsInTable[],int open_facesInTable[],int no_open){

return 1;
}
//CALCULATION OF THE WINNING COMBINATION OF THE PLAYER ENDS
