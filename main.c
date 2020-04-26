/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
// ban do ship
// 6 dice
//hull(9),shield(5)
//36 threat(random 1 -36)
int i,j;
int k;// so xi ngau ban dau--------------
int B[6]; //xuc sac tren tay nguoi choi---------------------
int me=0; //ap dung cho viec kiem tra medical o gan cuoi chuong trinh-------
int end=0;
#define M 10  // so enemy toi da o the xuat hien cung luc----------------------
#define N 7
int T[M][N];// to hop enemy--------------------------
int A[6]={0,0,0,0,0,0}; // assign list
int B1[6]={0,0,0,0,0,0};//trang thai da assign chua-----------------
int shield=5;
int hull=9;

//COLOR FOR FONT-------------------------------
#define B_YELLOW "\x1b[1;33m"
#define B_MAGENTA "\x1b[1;35m"
#define B_CYAN "\x1b[1;36m"
#define B_GREEN "\x1b[1;32m"
#define B_RED "\x1b[1;31m"
#define B_BLUE "\x1b[1;34m" 

#define YELLOW "\x1b[0;33m"
#define MAGENTA "\x1b[0;35m"
#define CYAN "\x1b[0;36m"
#define GREEN "\x1b[0;32m"
#define RED "\x1b[0;31m"
#define BLUE "\x1b[0;34m"

#define RESET "\x1b[0m"// mau mac dinh

//ham khoi tao top hop enemy mang test-----------------------------
void makeT()
{
    for (i=0;i<M;i++)
    {
        for (j=0;j<N;j++)
        {
            T[i][j]=0;
        }
    }
}
void printTtest()
{
    for (i=0;i<M;i++)
    {
        for (j=0;j<N;j++)
        {
               printf("%d ",T[i][j]);
        }
        printf("\n");
    }
}
//ham in danh sach mang T test----------------------
void enemy_info_check();
void printT()
{
    printf(B_MAGENTA"\nTHREAT LIST:"RESET);
    for (i=0;i<M;i++)
    {
        if (T[i][0]>=1 ) printf(MAGENTA"\n%d. <HP: %d> ",i+1,T[i][0]);
        if (T[i][0]==-10) printf(MAGENTA"\n%d. "RESET,i+1);
        enemy_info_check();
    }    
    printf(RESET);
}

// ham ngau nhien k xi ngau---------------------
void random_dice(int k)
{
    srand(time(0));
    for (i=0;i<k;i++)
    {
        B[i]=(rand()%(6-1+1))+1;
    }
}
// ham xuat B de test-----------------------------
void xuat(int B[],int k)
{
    printf("\n");
    for (i=0;i<k;i++)
    {
        printf("%d ",B[i]);
    }
}
// in ki tu crew------------------------------------
void print_hand(int k)
{
    printf("\t\t ");
    for (i=1;i<=k;i++)
    {
        printf(B_GREEN"%d "RESET,i);
    }
    printf(B_CYAN"\navailable crews: "RESET);
    for (i=0;i<k;i++)
    {
        if (B[i]==1) printf(BLUE"C "RESET);
        if (B[i]==2) printf(RED"T "RESET);
        if (B[i]==3) printf(MAGENTA"M "RESET);
        if (B[i]==4) printf(GREEN"S "RESET);
        if (B[i]==5) printf(YELLOW"E "RESET);
        if (B[i]==6) printf("! ");
    }
}
// ham dem so threat---------------------------------
int threat_count(int k)
{
    int dem=0;
    for (i=0;i<k;i++)
    {
        if (B[i]==6) dem++;
    }
    return dem;
}

//ham lam moi mang A---------------------------------
void renew(int X[])
{
    for (i=0;i<6;i++)
    {
        X[i]=0;
    }
}

// ham thuc hien tactical crew---------------------------
void tactical()
{
    int target;
    printf(B_RED"|_____ATTACK ONE THREAT (2 Damage)_____|"RESET);
    //printT();
    jump2:
    printf("\nChoose target (type 0 to cancel): "); scanf("%d",&target);
    if (target==0)
    {
        printf(B_RED"\nCANCELLED!\n"RESET);
        return;
    }
    if (T[target-1][0]<=0 && T[target-1][0]!=-10)
    {
        printf("\nThis target is unavailable. try again sir.");
        goto jump2;
    }
    
    if (T[target-1][0]==-10)
    {
        printf("\nUnfortunately, fire power don't affected that target, sir.");
    }
    
    if (T[target-1][0]>=1)
    {
        T[target-1][0]=T[target-1][0]-2;
        if (T[target-1][0]<=0)
        {
            printf(B_RED"\nTarget is unlimininated, sir."RESET);
            end--;
        }
    }
    printf(B_RED"\nCOMPLETED!\n"RESET);
    
}
// ham thuc hien medical----------------------------------------------
void medical()
{
    //se kiem tra medical o gan cuoi chuong trinh de tang k-----------
    printf(B_MAGENTA"|_____RETURN 2 LOST CREWS (AT THE END OF THE TURN)_____|"RESET);
    printf(B_MAGENTA"\nCOMPLETED!\n"RESET);
}
// ham thuc hien science--------------------------------------
void science()
{
    int i1;
    int choose;
    printf(B_GREEN"1.|_____RECHARGE ALL SHIELDS_____|"RESET);
    printf(B_GREEN"\n2.|_____UNLEASH ENERGY ( PAY 2 SHIELDS TO DEAL 1 DAMAGE TO ALL THREATS)_____|"RESET);
    ChooseS:
    printf("\nSelect (1 or 2): ");
    scanf("\n%d",&choose);
    if (choose!=1 && choose!=2)
    {
        printf("\nUnavailable option. Try again.");
        goto ChooseS;
    }
    if (choose==2)
    {
        printf("\nEnergy unleashed!");
        shield-=2;
        printf("\nShields: %d/5",shield);
        sleep(1);
        for (i1=0;i1<M;i1++)
        {
            if (T[i1][0]>0)
            {
                T[i1][0]-=1;
                if (T[i1][0]==0)
                {
                    end--;
                    printf(B_RED"\n[%d]: is unliminated!"RESET,i1+1);
                }
            }
        }
        
    }
    if (choose==1)
    {
       printf("\nShields recharged: 5/5"); shield=5;
    }
    printf(B_GREEN"\nCOMPLETED!\n"RESET);
}
// ham thuc hien engineering-----------------------------
void engineering()
{
    int choose;
    printf(B_YELLOW"1.|_____REPAIR 2 HULL_____|"RESET);
    printf(B_YELLOW"\n2.|_____PAY 1 HULL DESTROY 1 NONE-HP THREAT_____|");
    ChooseS:
    printf(RESET"\nSelect (1 or 2): ");
    scanf("\n%d",&choose);
    if (choose!=1 && choose!=2)
    {
        printf("\nUnavailable option. Try again.");
        goto ChooseS;
    }
    if (choose==1)
    {
        hull+=2;
        if (hull>9) hull=9;
        printf("\nHull repaired: %d/9",hull);
    }
    if (choose==2)
    {
        int target;
        jump2:
        printf("\nChoose target (type 0 to cancel): "); scanf("%d",&target);
        if (target==0)
        {
            printf(B_YELLOW"\nCANCELLED!\n"RESET);
            return;
        }
        if (T[target-1][0]!=-10)
        {
            printf("\nThis target is unavailable. try again sir.");
            goto jump2;
        }
        hull-=1;
        T[target-1][0]=0;
        printf(B_YELLOW"\nTarget is destroyed, sir."RESET);
        printf("\nHull: %d/9",hull);
        
        end--;
    }
    printf(B_YELLOW"\nCOMPLETED!\n"RESET);
}
//ham thuc hien commander--------------------------------------------------------------------------
void commander()
{
    int change_to;
    printf(B_BLUE"|_____TRANFORM THIS CREW TO ANOTHER JOB:_____|"RESET);
    
    jump1:
    printf("\nChange to: "); 
    printf(RED"\n2. Tactical"RESET);
    printf(MAGENTA"\n3. Medical"RESET);
    printf(GREEN"\n4. Science"RESET);
    printf(YELLOW"\n5. Engineering\n"RESET);

    
    scanf("%d",&change_to);
    if (change_to>5)
    {
        printf("\nCannot tranform to that, sir. Try again.");
        goto jump1;
    } else
    {
        if (change_to==2) tactical();
        if (change_to==3) {medical(); me=1;}
        if (change_to==4) science();
        if (change_to==5) engineering();
    }
    printf(B_BLUE"\nCOMPLETED!\n"RESET);
}

// ham kiem tra crew vua nhap-----------------------------------------------------------
void player_action(int x)
{
    if (x==1) commander();
    if (x==2) tactical();
    if (x==3) {medical(); me+=1;}
    if (x==4) science();
    if (x==5) engineering();
}

// ham assign k crew--------------------------------
void assign_crew(int k)
{
    printf("\n");
    sleep(1);
    printf(B_GREEN"\n---ASSIGN CREWS: (can type once at a time, type 0 to end)---\n"RESET);
    int x1=0;
    for (i=0;i<k;i++)
    {
        int x,dem=0;
        scanf("%d",&x);
        if (x==0)
        {
            
            break;
        }
             
        else
        {
            if (x>k || B[x-1]==6)
            {
                printf(B_RED"[%d]: THIS CREW IS NOT AVAILABLE, SIR.\n"RESET,x);
                i--;
            }
            else if (B1[x-1]==1) 
            {
                printf(B_RED"[%d]: YOU ALREADY ASSIGNED THIS CREW, SIR.\n"RESET,x);
                i--;
            }
            else
            {
                A[i]=B[x-1];
                player_action(A[i]);
                B1[x-1]=1;
                dem++;
            }
    
        }
                
    }
    printf(B_GREEN"\nASSIGNMENT COMPLETED!"RESET);
}        
//ham tao enemy (Tien do: 11/10)---------------------------------------
int enemy_gen()
{
    srand(time(0));
    return (rand()%(11-1+1))+1;
}


//ham get enemy vao mang T--------------------------------------------------------
void get_enemy(int X[], int ran)
{
    k=0;
    if (X[6]==ran)
    {
        while (1){
        if (T[k][0]==0)
        {
        	for(j=0;j<N;j++)
        	{
            	T[k][j]=X[j];
        	}
        	break;
        } else k++;
        
        }
    }
}

//Enemy list--------------------------------------------------------
int Raider[]={2,4,6,0,0,0,1};// 2HP, -2 HULL, INGNORE SHEILD (1) (DONE)
int Solar[]={-10,2,0,0,0,0,2};// effect, -4 HEALTH (2) (DONE)
int Flagship[]={4,4,5,6,0,0,3};// -3 HEALTH (3) (DONE)
int Intercepter[]={3,1,2,3,4,5,4};// -1 HEALTH (4) (DONE)
int Scout[]={3,1,2,3,4,5,5};// if your Hull is not full this turn, -1 HEALTH (5)(DONE)
int Bounty[]={4,1,2,0,0,0,6};// Destroy all shields -1 HEALTH (6) (DONE)
int Bomber[]={3,3,4,0,0,0,7};// Destroy 1 crew, -1 HEALTH (7) (DONE)
int Pirate[]={2,3,6,0,0,0,8};// -2 HEALTH (8) DONE
int Cruiser[]={4,1,2,0,0,0,9};// -2 HEALTH (9) DONE
int Drone[]={1,2,4,6,0,0,10};// -3 health (10) DONE
int Corsair[]={2,4,5,6,0,0,11};// -2 health (11) DONE
int Dark[]={-10,4,0,0,0,0,12};// -2 crew once
// ham check info enemy--------------------------
void enemy_info_check()
{
    if (T[i][7-1]==1) printf(MAGENTA"Raiders (LOW) < -2 HULL, ignores shields. >"RESET);
    if (T[i][7-1]==2) printf(MAGENTA"Solar Winds (LOW) < -4 HEALTH once. >"RESET);
    if (T[i][7-1]==3) printf(MAGENTA"Flagship (MEDIUM) < -2 HEALTH. >"RESET);
    if (T[i][7-1]==4) printf(MAGENTA"Intercepter (HIGH) < -1 HEALTH. >"RESET);
    if (T[i][7-1]==5) printf(MAGENTA"Scout (HIGH) < If Hull is below 9, -1 HEALTH. >"RESET);
    if (T[i][7-1]==6) printf(MAGENTA"Bounty (LOW) < Destroy all shields, -1 HEALTH. >"RESET);
    if (T[i][7-1]==7) printf(MAGENTA"Bomber (LOW) < Destroy all 1 crew, -1 HEALTH. >"RESET);
    if (T[i][7-1]==8) printf(MAGENTA"Pirate (LOW) < -2 HEALTH. >"RESET);
    if (T[i][7-1]==9) printf(MAGENTA"Cruiser (LOW) < -2 HEALTH. >"RESET);
    if (T[i][7-1]==10) printf(MAGENTA"Drone (MEDIUM) < -3 HEALTH. >"RESET);
    if (T[i][7-1]==11) printf(MAGENTA"Corsair (MEDIUM) < -2 HEALTH. >"RESET);
    if (T[i][7-1]==1) printf(MAGENTA"Dark (Low) < -2 CREWS once. >"RESET);
    
    
    
}
// ham check nhan dang enemy (tap hop ham get_enemy)--------------------------------------------
void enemy_spawn_check(int ran)
{
    get_enemy(Raider, ran);
    get_enemy(Solar, ran);
    get_enemy(Flagship, ran);
    get_enemy(Intercepter, ran);
    get_enemy(Scout, ran);
    get_enemy(Bounty, ran);
    get_enemy(Bomber, ran);
    get_enemy(Pirate, ran);
    get_enemy(Cruiser, ran);
    get_enemy(Drone, ran);
    get_enemy(Corsair, ran);
    get_enemy(Dark, ran);
}
//ham enemy_attack de enemy tan cong------------------------
void dark_atk(int *X)
{
    *X=0;
    printf("\nWe lost 2 crews, sir.");
    printf("\nDark have disappeared, sir.\n");
    end--;
}
void pirate_atk()
{
    if (shield<=0)
    {
        hull-=2;
        printf(GREEN"\nHull: %d/9\n"RESET,hull);
    } else 
    {
        shield-=2;
        printf(GREEN"\nShields: %d/5\n"RESET,shield);
    }
}

void cruiser_atk()
{
    if (shield<=0)
    {
        hull-=2;
        printf(GREEN"\nHull: %d/9\n"RESET,hull);
    } else 
    {
        shield-=2;
        printf(GREEN"\nShields: %d/5\n"RESET,shield);
    }
}

void drone_atk()
{
    if (shield<=0)
    {
        hull-=3;
        printf(GREEN"\nHull: %d/9\n"RESET,hull);
    } else 
    {
        shield-=3;
        printf(GREEN"\nShields: %d/5\n"RESET,shield);
    }
}

void corsair_atk()
{
    if (shield<=0)
    {
        hull-=2;
        printf(GREEN"\nHull: %d/9\n"RESET,hull);
    } else 
    {
        shield-=2;
        printf(GREEN"\nShields: %d/5\n"RESET,shield);
    }
}
void raiders_atk()
{
    hull=hull-2;
    printf(GREEN"\nHull: %d/9\n"RESET,hull);
}

void solar_atk(int *X)
{
    if (shield<=0)
    {
        hull-=4;
        printf(GREEN"\nHull: %d/9"RESET,hull);
        *X=0;
    } else 
    {
        shield-=4;
        printf(GREEN"\nShields: %d/5"RESET,shield);
        *X=0;
    }
    printf("\nSolar winds have disappeared, sir.\n");
    
    end--;
    
    
}
void flagship_atk()
{
    if (shield<=0)
    {
        hull-=2;
        printf(GREEN"\nHull: %d/9\n"RESET,hull);
    } else 
    {
        shield-=2;
        printf(GREEN"\nShields: %d/5\n"RESET,shield);
    }
}

void intercepter_atk()
{
    if (shield<=0)
    {
        hull-=1;
        printf(GREEN"\nHull: %d/9\n"RESET,hull);
    } else 
    {
        shield-=1;
        printf(GREEN"\nShields: %d/5\n"RESET,shield);
    }
}

void scout_atk()
{
    if (hull<9)
    hull-=1;
    printf(GREEN"\nHull: %d/9\n"RESET,hull);
}

void bounty_atk()
{
    shield=0;
    hull-=1;
    printf(GREEN"\nHull: %d/9\n"RESET,hull);
}

void bomber_atk()
{
    if (shield<=0)
    {
        hull-=1;
        printf(GREEN"\nHull: %d/9\n"RESET,hull);
    } else 
    {
        shield-=1;
        printf(GREEN"\nShields: %d/5\n"RESET,shield);
    }
}

void enemy_attack(int *k)
{
    srand(time(NULL));
    int ran1=(rand()%(6-1+1))+1;
    //printf("\nran1: %d",ran1);
    for (i=0;i<M;i++)
    {
        for (j=1;j<6;j++)
        {
            if (T[i][j]==ran1)
            {
                if (T[i][6]==1) {sleep(1);printf(B_RED"\n[%d]: Raiders attack!!!"RESET,i+1); raiders_atk();}
                if (T[i][6]==2) {sleep(1);printf(B_RED"\n[%d]: Solar winds activated!!!"RESET,i+1); solar_atk(&T[i][0]);}
                if (T[i][6]==3) {sleep(1);printf(B_RED"\n[%d]: Flagship attack!!!"RESET,i+1); flagship_atk();}
                if (T[i][6]==4) {sleep(1);printf(B_RED"\n[%d]: Intercepter attack!!!"RESET,i+1); intercepter_atk();}
                if (T[i][6]==5 && hull!=9 ) {sleep(1);printf(B_RED"\n[%d]: Scout attack!!!"RESET,i+1); scout_atk();}
                if (T[i][6]==6) {sleep(1);printf(B_RED"\n[%d]: Bounty has destroyed our shields. Attack incomming!!!"RESET,i+1); bounty_atk();}
                if (T[i][6]==7) {sleep(1);printf(B_RED"\n[%d]: Bomber has eliminated one of our crew, sir. Attack incomming!!!"RESET,i+1); bounty_atk(); *k=*k-1;}
                if (T[i][6]==8) {sleep(1);printf(B_RED"\n[%d]: Pirate attack!!!"RESET,i+1); pirate_atk();}
                if (T[i][6]==9) {sleep(1);printf(B_RED"\n[%d]: Cruiser attack!!!"RESET,i+1); cruiser_atk();}
                if (T[i][6]==10) {sleep(1);printf(B_RED"\n[%d]: Drone attack!!!"RESET,i+1); drone_atk();}
                if (T[i][6]==11) {sleep(1);printf(B_RED"\n[%d]: Corsair attack!!!"RESET,i+1); corsair_atk();}
                if (T[i][6]==12) {sleep(1);printf(B_RED"\n[%d]: Dark activated!!!"RESET,i+1); dark_atk(&T[i][0]); *k=*k-2;}
                
                
            }
        }
    }
    
}





//ham check HP cua enemy trong T--------------------------------------------------------
void enemy_HP_check()
{
    for (i=0;i<M;i++)
    {
        if ( T[i][0]<=0 && T[i][0]!=-10)
        {
            for (j=i+1;j<M;j++)
            {
                for (k=0;k<N;k++)
                {
                    T[i][k]=T[j][k];
                }
            }
                
        }
    }
}

int main()
{
    printf(B_CYAN"__________________           __\n");
    printf("\\_________________|)____.---'--`---.____\n");
    printf("              ||    \\----.________.----/\n");
    printf("              ||     / /    `--'\n");
    printf("            __||____/ /_\n");
    printf("           |___         \\\n");
    printf("               `--------'\n"RESET);
    printf(B_BLUE"|__________DEEP SPACE__________|\n"RESET);
    
    int threat=0;
    char new_turn;// de bat dau game va ket thuc luot------------
    int ran;// bien luu random enemy----------------------------
    int k=6;// so suc xac ban dau
    makeT();
    srand(time(NULL));// random seed generator---------------
    

    ran=enemy_gen();
    enemy_spawn_check(ran);
    // chon che do choi----------------------------------
    sleep(1);
    jend:
    printf(CYAN"\nchoose mode: "RESET);
    printf(CYAN"\n1. Short mode"RESET);
    printf(CYAN"\n2. Long mode\n"RESET);
    scanf("%d",&end);
    if (end!=1 && end!=2)
    {
        printf("Wrong input. Try again.");
        goto jend;
    }
    if (end==1) end=16;
    if (end==2) end=36;
    printf(B_BLUE"Your goal is to eliminate %d threats."RESET,end);
    
    
    start:
    printf(CYAN"\nPress Y to start game: "RESET);
    scanf("\n%c",&new_turn);
    new_turn=toupper(new_turn);
    if (new_turn!='Y')
    {
        printf("\nWrong character !!! Try again.");
        goto start;
    }
    printf("\e[1;1H\e[2J");//clear screen----------------
        
    // bat dau game----------------------------------    
    while (1)
    {
    printf("\n");
printf(B_BLUE"       _   _ _______        __  _____ _   _ ____  _   _\n");       
printf(" _____| \\ | | ____\\ \\      / / |_   _| | | |  _ \\| \\ | |_____\n"); 
printf("|_____|  \\| |  _|  \\ \\ /\\ / /    | | | | | | |_) |  \\| |_____|\n");
printf("|_____| |\\  | |___  \\ V  V /     | | | |_| |  _ <| |\\  |_____|\n");
printf("      |_| \\_|_____|  \\_/\\_/      |_|  \\___/|_| \\_\\_| \\_|\n"RESET);      
        
        printf(B_CYAN"\n|_____HULL: %d/9_____|"RESET,hull);
        printf(B_GREEN"|_____SHIELD:%d/5_____|\n"RESET,shield);
        printf("\n");
        random_dice(k);
        print_hand(k);// player hand dau tien-------
        //printf("\n"); xuat(k); printf("\n");
        threat+=threat_count(k);
        
        printf(B_RED"\nthreat scanner: %d/3"RESET,threat);
        if (threat>=3)
        {
            printf(B_RED" ==> THREAT INCOMMING!!!\n"RESET);
            threat-=3;
            ran=enemy_gen();
            enemy_spawn_check(ran);
        }
    
        
        printT();
        //printTtest();
        renew(A);
        assign_crew(k);
        k-=threat_count(k);
        //xuat(A,k);
        enemy_HP_check();
        sleep(1);
        printf("\e[1;1H\e[2J");
        printf(B_RED"\nNEW THREAT INCOMMING!!!\n"RESET);
        sleep(1);
        ran=enemy_gen();
        enemy_spawn_check(ran);
        printT();
        printf("\n");
        enemy_attack(&k);
        enemy_HP_check();
        
        if (me!=0) {k+=2*me; me=0;}
        if (k>6) k=6;
        if (shield<=0) shield=0;
        renew(B1);
        if (k==0 || hull<=0)
        {
            printf(B_RED"\nTHE SHIP IS DESTROYED!!! YOU LOSE!"RESET);
            break;
        }
        if (end<=0)
        {
            printf(B_YELLOW"\nCONGRATULATIONS!!! YOU WON!!!");
            break;
        }
        sleep(1);
        printf(B_CYAN"\n|_____HULL: %d/9_____|"RESET,hull);
        printf(B_GREEN"|_____SHIELD:%d/5_____|\n"RESET,shield);
        printf(B_BLUE"<-----%d left threats to eliminate, sir.----->"RESET,end);
        
       eturn:
       printf("\nPress Y to end turn: ");
       scanf("\n%c",&new_turn);
       new_turn=toupper(new_turn);
       if (new_turn!='Y')
       {
           printf("\nWrong character !!! Try again.");
           goto eturn;
       }
       printf("\e[1;1H\e[2J");//clear screen----------------
    }
    


    return 0;
}
















































