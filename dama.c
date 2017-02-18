/*======================(Checkers)=====================|
|)Name: Koytsioras Panagiotis-------------------------=|
|)AM:2025201100037------------------------------------=|
|)cst11037@uop.gr-------------------------------------=|
|)=====================================================|
|)Name:Gemistos Vasilis-------------------------------=|
|)AM:2025201100010------------------------------------=|
|)cst11010@uop.gr-------------------------------------=|
|)=====================================================|
|)------------------(Date: 22.05.2012)----------------=|
|=====================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 8
//=====[Functions Declaration]=====//
int fl=0;//Checks when a game is loaded or not.
void Parameters();//Print Parameters when user types [ ./dama -h ].
void PrintBoard(int **pa);//Print board in screen.
void FillTable( int **pa);//Fill table With [X] and [O].
int  Game();
int  ConvertLetter(char x[2]);//Converts "char" to "int".
int  ConvertNumber(char x[2]);//convert "char" to "int".
int  MoveX(int **pa,int a1,int a2,int b1,int b2);//Moves [x,X] pawns.
int  MoveO(int **pa,int a1,int a2,int b1,int b2);//Moves [o,O] pawns.
int  CheckWin(int **pa);//Checks if a player win.If yes Prints winner and ends game.
int  eat_x_pawn(int **pa);//Eats the [x,X] pawns.
int  eat_o_pawn(int **pa);//Eats the [o,O] pawns.
int  isValidMode(char a[2],char b[2]);//Checks if moves of user are valid.

typedef struct list {
    int cp[8][8];
    struct list* next;
}list;
	
list list1;//Creates a variable [type of list].
	
list* head;//Creates a pointer which is used at list.
//Stack.
int add_stack(const list* list_ptr);//Puts an Element in stack.
void pop(int **pa);//Deletes the last incoming element in stack.
void free_stack(); //releases the memory for the stack.
//Files.
void SaveToFile();//Saves users Current game into Filename.chk
void LoadFromFile(int **pa,char LoadedFile[20]);//Loads a SavedFile.chk from parameters.

//=====[Function main]=====//
int main( int argc, char *argv[] ){//Parametres of program.
		
    head = NULL;
		
    if( argc != 2 && argc != 3 ){//if User Don't know Parameters then this message is printed.
        printf("Please Enter: [ .\\dama -h ] to view programm parameters.\n");
        return 0;
    } 
    if ( argc == 2 ){//If user types 2 parameters.
        if( strcmp (argv[1],"-n") == 0){//If 2nd parameter is "-n" a new game is starting.
            Game();
        }
        else if(strcmp (argv[1],"-h")==0){
            Parameters();
            return 0;
        }
        else{//If 2nd parameter is not "-h" or "-l" then print this message in screen.
            printf("Please Enter: [ .\\dama -h ] to view programm parameters.\n");
            return 0;
        }
    }
    if (argc == 3){//If user types 3 parameters.
        int i,j;
        int **pa = NULL; 
        pa=(int**)calloc(N,sizeof(int*));//Memory allocation for array pa
        if(pa == NULL){//Check if memory is availabe.
			printf("No Memory Available!\n");
			return 0;
		}   	   	   
        for(i=0; i<N; i++){
            pa[i]=(int*)calloc(N,sizeof(int));
            if( pa[i] == NULL ){//Check if memory is availabe.
				printf("No Memory Available!\n");
				return 0;
			}
        }
        if(strcmp (argv[1],"-l")==0){//if 2nd Parameter is "-l"
            char LoadedFile[20];
            strcpy(LoadedFile,argv[2]);//Copy users File (argv[2]) into LoadedFile.
				
            LoadFromFile(pa,LoadedFile);//Call Function LoadFromFile
	
            fl=1;
            Game();
        }
        free_stack();
        free(pa);
    }
}//=====[End of main]=====//
	
//=====[Functions]=====//

//=====[Parameters Function]=====//
void Parameters(){
    printf("\n\\_====--====---===----==-----=[PARAMETERS]=-----==----===---====--====_/\n");
    printf("  \\__________________________________________________________________/\n");
    printf("   |                               |                                |\n");
    printf("   |[1]->  .\\dama -n               | Start a new game of Checkers.  |\n");
    printf("   |_______________________________|________________________________|\n");
    printf("   |                               |                                |\n");
    printf("   |[2]->  .\\dama -l FileName.chk  | Load a saved game of Checkers. |\n");
    printf("   |_______________________________|________________________________|\n");
    printf("   |                               |                                |\n");
    printf("   |[3]->  .\\dama -h               | Print programm Parameters.     |\n");
    printf("   |_______________________________|________________________________|\n");
    printf(" _/                                                                  \\_\n");
    printf("/ ====--====---===----==-----=----====----=-----==----===---====--==== \\\n\n");
}
 
//=====[FillTable Function]=====//
void FillTable(int **pa){
	int i,j;
    //filling the table with starting pawns of [X]
    for (i=0; i<3; i++){
        for (j=0; j<N; j++){
            if((i+j)%2 == 0)
                pa[i][j]=1;        
        }
    }
    //filling the table with starting pawns of [O]
    for(i=5; i<N; i++){
        for(j=0; j<N; j++){
            if((i+j)%2 == 0)
                pa[i][j]=2;
        }
    }        
}
	
//=====[PrintBoard Function]=====//
void PrintBoard(int **pa){
/* * * * * * * * * 
 *[0]-Dot.       *
 *[1]-Pawn (x).  *
 *[2]-Pawn (o).  *
 *[3]-Pawn (X).  *
 *[4]-Pawn (O).  *
 * * * * * * * * */
    int i,j;
    printf("\n        a b c d e f g h\n");
    printf("      -------------------\n");
    for(i=0; i<N; i++){
        printf("%s%d%s","     ",i+1,"|");
        for(j=0; j<8; j++) {
            if(pa[i][j]==0){
                printf(" .");
            }   
            if(pa[i][j]==1){
                printf(" x");
            }   
            if(pa[i][j]==2){
                printf(" o");
            }
            if(pa[i][j]==3){
                printf(" X");
            }
            if(pa[i][j]==4){
                printf(" O");
            }	
        }
        printf("%s%s%d\n"," ","|",i+1);
    }
    printf("      -------------------\n");
    printf("        a b c d e f g h\n\n");
}
	
//=====[isValidMode Function]=====//
int  isValidMode(char a[2],char b[2]){
    int flag = 1;//true
    if (a[0] < 'a' || a[0] > 'h' || b[0] < 'a' || b[0] > 'h' || a[1] < '1' || a[1] > '8' || b[1] < '1' || b[1] > '8'){
        flag = 0;//false
    }
    if( strcmp(a,b) == 0){
        flag = 0;//false
    }
    return flag;
}
	
//=====[ConvertLetter Function]=====//
int  ConvertLetter(char x[2]){
	
    if (x[0] == 'a') return 0;
    if (x[0] == 'b') return 1;
    if (x[0] == 'c') return 2;
    if (x[0] == 'd') return 3;
    if (x[0] == 'e') return 4;
    if (x[0] == 'f') return 5;
    if (x[0] == 'g') return 6;
    if (x[0] == 'h') return 7;
	
}
	
//=====[ConvertNumber Function]=====//
int  ConvertNumber(char x[2]){
	
    if (x[1] == '1') return 0;
    if (x[1] == '2') return 1;
    if (x[1] == '3') return 2;
    if (x[1] == '4') return 3;
    if (x[1] == '5') return 4;
    if (x[1] == '6') return 5;
    if (x[1] == '7') return 6;
    if (x[1] == '8') return 7;
	
}
	
//=====[Game Function]=====//
int Game(){
    int flag=0,i,j,CX1,CX2,NX1,NX2,CO1,CO2,NO1,NO2,choice;
    char aX[2],bX[2],aO[2],bO[2];
				
    int **pa = NULL; 
				
    //Memory allocation for array pa
    pa=(int**)calloc(N,sizeof(int*));
    if(pa == NULL){//Check if memory is availabe.
        printf("No Memory Available!\n");
        return 0;
    }	   	   	   	   
    for(i=0; i<N; i++){
        pa[i]=(int*)calloc(N,sizeof(int));
        if( pa[i] == NULL ){//Check if memory is availabe.
			printf("No Memory Available!\n");
			return 0;
		}
    }
					
    if(fl==0){
		
    START: //label for goto.
    
        FillTable(pa);
        
        for(i=0; i<8; i++){
            for(j=0; j<8; j++){
                list1.cp[i][j] = pa[i][j];
            }
        }
        
        add_stack(&list1);
				
        printf("\n   =-=-=-=-=-=-=-=-=-=-=-=-=");			  			
        printf("\n   |=  -~=(NEW  GAME)=~-  =|");
        printf("\n   =-=-=-=-=-=-=-=-=-=-=-=-=\n\n");	

    }
    
    if(fl==1){
		
        for(i=0; i<8; i++){
            for(j=0; j<8; j++){
                pa[i][j]=head->cp[i][j];
            }
        }    
        add_stack(&list1);
			
        printf("\n   =-=-=-=-=-=-=-=-=-=-=-=-=");			  			
        printf("\n   |=  -~=(LOAD GAME)=~-  =|");
        printf("\n   =-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    }
    do{ 
		flag=CheckWin(pa);
		if(flag == 0){
			do{
							
				eat_x_pawn(pa);
           
				PrintBoard(pa);
			
               			//Read moves For [X] Player.
				printf("> Player X Give your Move:");
				scanf("%2s-%2s",aX,bX);
				if( strcmp( aX,"z9" ) == 0 && strcmp( bX,"z9" ) == 0 ){
								
					printf("\n\\=-=-=-=-=[GAME OVER]=-=-=-=-=/");
					printf("\n  \\-------------------------/  ");
					printf("\n   | [1]: Start a New Game |");
					printf("\n   | [2]: Save Game        |");
					printf("\n  /-------------------------\\  ");
					printf("\n/=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\\");
					printf("\n>");
					scanf("%d",&choice);
					do{
						switch (choice){
						case 1:
							goto START;
							break;
						case 2:
							//Save Game.
							SaveToFile();
						
							return 0;
							break;
						default:
							printf("Error.\nGive Choice Again:");
							scanf("%d",&choice);
							break;
						}
					}while(choice != 1 || choice != 2);
				}
				if( strcmp( aX,"u9" ) == 0 && strcmp( bX,"u9" ) == 0 ){
					if(head->next  == NULL){
						printf("The Stack is Empty.\n");	
					}
					else{
						pop(pa);
						printf("Undo move.");
						PrintBoard(pa);
					}
				}
			
            }while (isValidMode(aX,bX) == 0 );
						
            //Convert moves.
            CX1=ConvertLetter(aX);
            CX2=ConvertNumber(aX);
            NX1=ConvertLetter(bX);
            NX2=ConvertNumber(bX);
					
            MoveX(pa,CX1,CX2,NX1,NX2);
						
            for(i=0; i<8; i++){
                for(j=0; j<8; j++){
                    list1.cp[i][j] = pa[i][j];
                }
            }
            add_stack(&list1);
            eat_x_pawn(pa);
            PrintBoard(pa);
							
        
            flag=CheckWin(pa);
		}
		if(flag == 0){			
            do{
                //Read Moves For [O] Player!
                printf("> Player O Give your Move:");	
                scanf("%2s-%2s",aO,bO);
                if( strcmp( aO,"z9" ) == 0 && strcmp( bO,"z9" ) == 0 ){
																
                    printf("\n\\=-=-=-=-=[GAME OVER]=-=-=-=-=/");
                    printf("\n  \\-------------------------/  ");
                    printf("\n   | [1]: Start a New Game |");
                    printf("\n   | [2]: Save Game        |");
                    printf("\n  /-------------------------\\  ");
                    printf("\n/=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\\");
                    printf("\n>");
                    scanf("%d",&choice);
                    do{
                        switch (choice){
                        case 1:
                            fl=0;
                            goto START;
                            break;
                        case 2:
                            //Save Game!!!
                            SaveToFile();
                            return 0;
                            break;
                        default:
                            printf("Error.\nGive Choice Again:");
                            scanf("%d",&choice);
                            break;
                        }
                    }while(choice != 1 || choice != 2);
									
                }
                if( strcmp( aO,"u9" ) == 0 && strcmp( bO,"u9" ) == 0 ){
                    if(head->next  == NULL){
                        printf("The Stack is Empty.\n");				
                    }
                    else{
                        pop(pa);
                        printf("Undo move.\n");
                        PrintBoard(pa);
                    }	
                }
            }while (isValidMode(aO,bO) == 0);
            //convert moves.
            CO1=ConvertLetter(aO);
            CO2=ConvertNumber(aO);
            NO1=ConvertLetter(bO);
            NO2=ConvertNumber(bO);
							
            MoveO(pa,CO1,CO2,NO1,NO2);
            for(i=0; i<8; i++){
                for(j=0; j<8; j++){
                    list1.cp[i][j] = pa[i][j];
                }
            }
						
            add_stack(&list1);
			eat_o_pawn(pa);
		}					
							
       	
	}while(flag == 0);
	free_stack();
	free(pa);
}

//=====[MoveX Function]=====//
int  MoveX(int **pa,int a1,int a2,int b1,int b2){ 
    printf("%d \n", b2);
    if(pa[a2][a1]==1){
        if(pa[b2][b1] == 0){
            if( b2>=0 && b2<=6){
                pa[a2][a1]=0;
                pa[b2][b1]=1;
            }
            else if (b2==7){
                pa[a2][a1]=0;
                pa[b2][b1]=3;
            }
        }
    }
		
	
    else if(pa[a2][a1]==3){
        if(pa[b2][b1]==0){
            pa[b2][b1]=3;
            pa[a2][a1]=0;
        }
    }
}

//=====[MoveO Function]=====//
int  MoveO(int **pa,int a1,int a2,int b1,int b2){
    if(pa[a2][a1]==2){
        if(pa[b2][b1] == 0){
            if(b2>=1 && b2<=7){
                pa[a2][a1]=0;
                pa[b2][b1]=2;
            }
            else if(b2==0){
                pa[a2][a1]=0;
                pa[b2][b1]=4;
            }
        }
    }
    else if(pa[a2][a1]==4){
        if(pa[b2][b1]==0){
            pa[b2][b1]=4;
            pa[a2][a1]=0;
        }
    }
	
}

//=====[CheckWin Function]=====//
int CheckWin(int **pa){//9elei dior9wsh!!!
    int i,j,k=0,l=0,flag=0;//k:Counter of[o], l: Counter of [x]
    for ( i=0; i<8; i++ ){
        for( j=0; j<8; j++){
				
            if (pa[i][j] == 2 ){
                k=k+1;
            }
				
            if (pa[i][j] == 1 ){
                l=l+1;
            }					
        }
    }
    //Check if there are [O] pawns.
    if(k == 0){
        printf("PLAYER [X] WINS!!!\n");
        flag = 1;
    }
    //Check if there are [O] pawns.
    if(l == 0){
        printf("PLAYER [O] WINS!!!\n");
        flag = 1;
    }  
    return flag;
}
	
//=====[eat_x_pawn Function]=====//
int eat_x_pawn(int **pa){
	int i,j,k=0,x1,x2,x3,y1,y2,y3,w;
	//Moves simple pawns [o] for eating.
	for(i=0; i<8; i++){
        for(j=0; j<8; j++){
            if(pa[i][j]==2){
                if((i-1)>=0 && (j+1)<=7){
                    if(pa[i-1][j+1]==1 || pa[i-1][j+1]==3){
                        if((i-2)>=0 && (j+2)<=7){
                            if(pa[i-2][j+2]==0){
                                x1=i;
                                y1=j;
                                x2=i-1;
                                y2=j+1;
                                x3=i-2;
                                y3=j+2;
                                w=2;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }	
                    }
                }
                if((i-1)>=0 && (j-1)>=0){
                    if(pa[i-1][j-1]==1 || pa[i-1][j-1]==3){
                        if((i-2)>=0 && (j-2)>=0){
                            if(pa[i-2][j-2]==0){
                                x1=i;
                                y1=j;
                                x2=i-1;
                                y2=j-1;
                                x3=i-2;
                                y3=j-2;
                                w=2;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }
                    }
                }
							
						
            }
//Moves kings [O] for eating.
            if(pa[i][j]==4){
                if((i-1)>=0 && (j+1)<=7){
                    if(pa[i-1][j+1]==1 || pa[i-1][j+1]==3){
                        if((i-2)>=0 && (j+2)<=7){
                            if(pa[i-2][j+2]==0){
                                x1=i;
                                y1=j;
                                x2=i-1;
                                y2=j+1;
                                x3=i-2;
                                y3=j+2;
                                w=4;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }
                    }
                }
                if((i-1)>=0 && (j-1)>=0){
                    if(pa[i-1][j-1]==1 || pa[i-1][j-1]==3){
                        if((i-2)>=0 && (j-2)>=0){
                            if(pa[i-2][j-2]==0){
                                x1=i;
                                y1=j;
                                x2=i-1;
                                y2=j-1;
                                x3=i-2;
                                y3=j-2;
                                w=4;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }
                    }
                }
                if((i+1)<=7 && (j+1)<=7){
                    if(pa[i+1][j+1]==1 || pa[i+1][j+1]==3){
                        if( (i+2)<=7 && (j+1)<=7){
                            if(pa[i+2][j+2]==0){
                                x1=i;
                                y1=j;
                                x2=i+1;
                                y2=j+1;
                                x3=i+2;
                                y3=j+2;
                                w=4;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }
                    }
                }
                if((i+1)<=7 && (j-1)>=0){
                    if(pa[i+1][j-1]==1 || pa[i+1][j-1]==3){
                        if((i+2)<=7 && (j-2)>=0){
                            if(pa[i+2][j-2]==0){
                                x1=i;
                                y1=j;
                                x2=i+1;
                                y2=j-1;
                                x3=i+2;
                                y3=j-2;
                                w=4;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }
                    }
                }
						
            }
						
						
        }
    }
    if(k==1){
        eat_x_pawn(pa); //Recursion.
    }
}

//=====[eat_o_pawn Function]=====//
int eat_o_pawn(int **pa){
	int i,j,k=0,x1,x2,x3,y1,y2,y3,w;
	//Moves simple pawns [x] for eating.
	for(i=0; i<8; i++){
        for(j=0; j<8; j++){
            if(pa[i][j]==1){
                if((i+1)<=7 && (j+1)<=7){
                    if(pa[i+1][j+1]==2 || pa[i+1][j+1]==4){
                        if( (i+2)<=7 && (j+1)<=7){
                            if(pa[i+2][j+2]==0){
                                x1=i;
                                y1=j;
                                x2=i+1;
                                y2=j+1;
                                x3=i+2;
                                y3=j+2;
                                w=1;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }
                    }
                }
                if((i+1)<=7 && (j-1)>=0){
                    if(pa[i+1][j-1]==2 || pa[i+1][j-1]==4){
                        if((i+2)<=7 && (j-2)>=0){
                            if(pa[i+2][j-2]==0){
                                x1=i;
                                y1=j;
                                x2=i+1;
                                y2=j-1;
                                x3=i+2;
                                y3=j-2;
                                w=1;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }
                    }
                }
						
            }
//Moves Kings [X] for eating.
            if(pa[i][j]==3){
                if((i+1)<=7 && (j+1)<=7){
                    if(pa[i+1][j+1]==2 || pa[i+1][j+1]==4){
                        if( (i+2)<=7 && (j+1)<=7){
                            if(pa[i+2][j+2]==0){
                                x1=i;
                                y1=j;
                                x2=i+1;
                                y2=j+1;
                                x3=i+2;
                                y3=j+2;
                                w=3;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }
                    }
                }
                if((i+1)<=7 && (j-1)>=0){
                    if(pa[i+1][j-1]==2 || pa[i+1][j-1]==4){
                        if((i+2)<=7 && (j-2)>=0){
                            if(pa[i+2][j-2]==0){
                                x1=i;
                                y1=j;
                                x2=i+1;
                                y2=j-1;
                                x3=i+2;
                                y3=j-2;
                                w=3;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }
                    }
                }
                if((i-1)>=0 && (j+1)<=7){
                    if(pa[i-1][j+1]==2 || pa[i-1][j+1]==4){
                        if((i-2)>=0 && (j+2)<=7){
                            if(pa[i-2][j+2]==0){
                                x1=i;
                                y1=j;
                                x2=i-1;
                                y2=j+1;
                                x3=i-2;
                                y3=j+2;
                                w=3;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }
                    } 
                }
                if((i-1)>=0 && (j-1)>=0){
                    if(pa[i-1][j-1]==2 || pa[i-1][j-1]==4){
                        if((i-2)>=0 && (j-2)>=0){
                            if(pa[i-2][j-2]==0){
                                x1=i;
                                y1=j;
                                x2=i-1;
                                y2=j-1;
                                x3=i-2;
                                y3=j-2;
                                w=3;
                                pa[x1][y1]=0;
                                pa[x2][y2]=0;
                                pa[x3][y3]=w;
                                k=1;
                            }
                        }
                    }
                }
						
            }
						
        }
    }
    if(k==1){
        eat_o_pawn(pa); //Recursion.
    }
}

//=====[add_stack Function]=====//
int add_stack(const list* list_ptr){
    list* new_mode;
    new_mode=(list*)malloc(sizeof(list));
    if(new_mode == NULL) {
        printf("Error: Not available memory \n");
        exit(1);
    }
    *new_mode=*list_ptr;
	
    new_mode->next = head;
	
    head = new_mode;
}

//=====[pop Function]=====//
void pop(int **pa){
    int i,j;
    list* ptr;
    ptr = head->next;
    free(head);
    head = ptr;
    for(i=0; i<8; i++){
        for(j=0; j<8; j++){
            pa[i][j]=head->cp[i][j];
        }
    }
}
	
//=====[SaveToFile Function]=====//
void SaveToFile(){
    int i,j;
    char FileName[20];//Declare a FileName in order to save the game in a file.
    FILE *fp;
    printf("Give FileName:");
    scanf("%s",FileName);//User types a FileName.
    strcat(FileName,".chk");//Attach ".chk" With FileName.
    fp=fopen(FileName,"w");//Creates a new File.
    //Elements of Array "pa" from Stack are saved in File.
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            fprintf(fp,"%d\n",head->cp[i][j]);
        }
    }
		
    fclose(fp);//Close Opened File.
    printf("---\nSaved archive: %s\n",FileName);//Prints Saved File.
}
	
//=====[LoadFromFile Function]=====//
void LoadFromFile(int **pa,char LoadedFile[20]){
    int i,j;
    FILE *fptr = NULL;//Declare pointer.
    fptr=fopen(LoadedFile,"r");//fptr shows to LoadedFile.
    if(fptr == NULL){
        printf("Error Opening File!!!\n");
    }
    for(i=0; i<N; i++){//Reads elements of LoadedFile.
        for(j=0; j<N; j++){
            fscanf(fptr,"%d\n",&pa[i][j]);
        }
    }
    fclose(fptr);//Close LoadedFile.
    for(i=0; i<N; i++){//Puts elements of "pa" array into stack.
        for(j=0; j<N; j++){
            list1.cp[i][j] = pa[i][j];
        }
    }
    add_stack(&list1);
}
void free_stack(){
	list* ptr;
	list* next_node;
	ptr = head;
	while(ptr!=NULL){
		next_node = ptr->next; //the next_node pointer shows into the next element of the stuck
		free(ptr);
		ptr = next_node; //the ptr pointer shows into the next element of the stuck
	}
}


	
	
	
	
