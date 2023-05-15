/* Georgia Moore
   Systems Programming
   04-25-2023
   Signals - Base to Subs
   Purpose Statement: Using system funcitnos and signals, create a game running 3 submarines
                      that will be radnomly assigned amount of fuel and number of missles. The 
                      distance away from base will increase until all missles are launched, the 
                      submarine will then head back to base. If the submarine runs out of fuel, the 
                      mission is unsuccessful. 
*/


/* 
     Assumptions:
        There will only be 4 terminals open or the user will know what the first four terminals are. 
*/

/*   
    Known Bugs:
      when run on appollo machien the terminals detect terminals that aren't mine therefore output is werid
      when the game is over there is no output int he main terminal that declares the results
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

struct Sub{
    int fuelSize;
    int payload;
    int distance;
}sub;

// global variables needed to be used in signal handlers
FILE *fptr;
int itr, sub1, sub2, sub3, parentPid;

// fucntion to report stats for each submarine
void report(){
    time_t t;
    struct tm *info;
    char time[50];
    info = localtime(&t);
    if(sub.fuelSize < 0) sub.fuelSize = 0;
    if(sub.distance < 0) sub.distance = 0;
    if(sub.payload < 0) sub.payload = 0;
    strftime(time, 50, "%X", info);
    fprintf(fptr, "\nTime: %s \n", time);
    fprintf(fptr, "\tsub %i to base, %i gallons left,\n", getpid(), sub.fuelSize);
    fprintf(fptr, "\t%i missles left, %i miles from base\n\n", sub.payload, sub.distance);
}

// signals for refuel and launch 
void signal_handler(int sig){
    //launch a missle when given the signal
    if(sig == SIGUSR1){
        sub.payload = sub.payload - 1;
        fprintf(fptr, "--------------------------------\n");
        fprintf(fptr, "   Launching a missle!!\n");
        if(sub.payload>0){
            fprintf(fptr, "   Number of missles left: %i\n", sub.payload);
            fprintf(fptr, "--------------------------------\n");
        }
        else if (sub.payload==0){
            fprintf(fptr, "   No More missles Left!! \n");
            fprintf(fptr, "     Returning to base\n" );
            fprintf(fptr, "--------------------------------\n");
        }
    } 
    // refuel when prompted 
    else if(sig == SIGUSR2){
        srand(time(0)+getpid());
        if(sub.fuelSize > 0){
            sub.fuelSize = sub.fuelSize + (rand() % (5000 - 1000 + 1)) + 1000;
        }
        else if(sub.fuelSize <= 0){
             // warning of low fuel and unsuccessful mission message 
            printf("Sub %i is dead in the water! \n", getpid()-parentPid);
            fprintf(fptr, "Rescue is on the way, Sub %i\n", getpid()-parentPid);
            fprintf(fptr, "Unsuccessful Mission, Sub %i\n", getpid()-parentPid);
            fclose(fptr);
            kill(getpid(), SIGKILL);
        }
    }
}

// alarm instructions 
void alarm_handler(int signum){
    srand(time(0)+getpid());
    
    // decrement fuel each second
    sub.fuelSize = sub.fuelSize - ((rand() % (200-100 +1)) + 100);

    // increment or decrement distance every 2 seconds
    if(itr % 2 == 0){ 
        if(sub.payload>0){
            sub.distance = sub.distance + ((rand() % (10-5 + 1)) + 5);}
        else{
            sub.distance = sub.distance - ((rand() % (8-3 + 1)) + 3);
        }

    }

    // print report every 3 seconds
    if(itr % 3 == 0){
        report();
        if(sub.fuelSize < 500){
            fprintf(fptr, "Sub %i is running out of fuel!\n", getpid()-parentPid);
        }
    }
    itr++;
}

// set and run the submarines
void createSub(FILE *fptr){
    int check = 0;
    // to make numbers random
    srand(time(0)+getpid());
    
    // set fuel size and amount of missles
    sub.fuelSize = (rand() % (5000 - 1000 + 1)) + 1000;
    sub.payload = (rand() % (10-6+1) +6);
    fprintf(fptr,"fuelSize: %i\npayload: %i\ndistance: %i\n\n", sub.fuelSize, sub.payload, sub.distance);

    itr = 1;
    signal(SIGALRM, alarm_handler);
    
    // continue to make adjustments until fuel runs out 
    while(sub.fuelSize>0){
        alarm(1);
        pause(); 
        if(check>3 && sub.distance==0){
            fprintf(fptr," successfull mission!!! \n");
            kill(getpid(), SIGKILL);
        }
        check++;
    }
    kill(getpid(), SIGUSR2);

}

int main(void){
    char temp[20];
    char parent[20];
    int itr = 0;
    char **terminals;
    int size = 30;
    terminals = (char**) malloc(80);
    
    // signal codes
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    signal(SIGINT, SIG_DFL);
    
    // store original parent terminal
    strcpy(parent, ttyname(STDOUT_FILENO));

    //discover how many terminals are open and store them
    for(int i=0; i<=136; i++){
        sprintf(temp, "/dev/pts/%d", i); 
        if(strcmp(parent, temp) && (fptr = fopen(temp, "r"))!=NULL){
            if((sizeof(terminals)+20)>size){
                size = size + 20;
                terminals = (char**) realloc(terminals, size);}

            terminals[itr] = (char*)malloc(20);
            sprintf(terminals[itr], "/dev/pts/%d", i);
            ++itr;
        }
    }

    // quit program if not enough terminals are open
    if(!terminals[0] || !terminals[1] || !terminals[2]){
        printf("NOT ENOUGH TERMINALS. EXITING...\n");
        exit(1);
    }

    // display the date and time of the start of the mission
    time_t t;
    time(&t);
    
    printf("Current date and time:\n \t%s\n", ctime(&t));

    // use fork() to spawn three child submarine tasks
    int pid, pid1, pid2;
    char input[5];

    parentPid = getpid();
    sub1 = parentPid +1;
    sub2 = parentPid +2;
    sub3 = parentPid +3;
    pid = fork();
    if(pid == 0){
        fptr = fopen(terminals[0], "w");
        fprintf(fptr, "\nThis is submarine 1.\n");
        createSub(fptr);
    }
    else{
        pid1=fork();
        if(pid1 == 0){
            fptr = fopen(terminals[1], "w");
            fprintf(fptr, "\nThis is submarine 2.\n");
            createSub(fptr);
        }
        else {
            pid2 = fork();
            if(pid2==0){
                fptr = fopen(terminals[2], "w");
                fprintf(fptr, "\nThis is submarine 3.\n");
                createSub(fptr);
            }
        }
    }
  
    // get input from user throughout process
    while(getpid() == parentPid){
        int temp = 1;
        int check = 0;
        
        // print options, added game over option to choose when all submarines are 
        //    done so a final message can be sent
        printf("\tOptions\n");
        printf("\t--------\n");
        printf("\tln - launch submarine n's missle\n");
        printf("\trn - refuel submarine n's fuel\n");
        printf("\tsn - scuttle submarine n \n");
        printf("\tq - quit\n");
        printf("\tgo - game over\n\n");
        
        
        if(check){
            scanf("%i", &temp);
        }
        scanf("%s", input);
        check = 1;
       

        // prompt refuel of submarine
        if(!strcmp("r1", input) || !strcmp("r2", input) || !strcmp("r3", input)){
            if(input[1]=='1') kill(sub1, SIGUSR2);
            else if(input[1]=='2') kill(sub2, SIGUSR2);
            else if(input[1]=='3') kill(sub3, SIGUSR2);
        }
        // prompt launch of missle from submarine
        else if(!strcmp("l1", input) || !strcmp("l2", input) || !strcmp("l3", input)){
            if(input[1]=='1') kill(sub1, SIGUSR1);
            else if(input[1]=='2') kill(sub2, SIGUSR1);
            else if(input[1]=='3') kill(sub3, SIGUSR1);
        }
        // prompt the killing of submarine 
        else if(!strcmp("s1", input) || !strcmp("s2", input) || !strcmp("s3", input)){
            if(input[1]=='1'){
                fptr = fopen(terminals[0], "w");
                fprintf(fptr, "terminating the process...\n");
                kill(sub1, SIGKILL); 
                fclose(fptr);
            } 
            else if(input[1]=='2'){
                fptr = fopen(terminals[1], "w");
                fprintf(fptr, "terminating the process...\n");
                kill(sub2, SIGKILL);
                fclose(fptr);
            }
            else if(input[1]=='3'){
                fptr = fopen(terminals[2], "w");
                fprintf(fptr, "terminating the process...\n");
                kill(sub3, SIGKILL);
                fclose(fptr);
            } 
        }
        // quit program 
        else if(!strcmp("q", input)){
            kill(sub1, SIGKILL);
            kill(sub2, SIGKILL);
            kill(sub3, SIGKILL);
            printf("Current date and time:\n \t%s\n", ctime(&t));
            kill(getpid(), SIGINT);
        }
        // when game over 
        else if(!strcmp("go", input)){
            printf("Game over...Hope you had fun!\n");
            exit(1);
        }
        // invalid entry menu
        else{
            printf("Invalid entry Try again.\n\n");
            printf("\tOptions\n");
            printf("\t--------\n");
            printf("\tln - launch submarine n's missle\n");
            printf("\trn - refuel submarine n's fuel\n");
            printf("\tsn - scuttle submarine n \n");
            printf("\tq - quit\n");
            printf("\tgo - game over\n");
        }

        if((kill(sub1,0)==-1) && (kill(sub2,0)==-1) && (kill(sub3,0)==-1)){
            printf("all processes are done\n Woohoo!\n");
        }
    }
    return 0;
}