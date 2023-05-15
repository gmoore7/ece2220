/* Georgia Moore
   Systems Programming
   1-25-2023
   Data Types - Egg Shipments
   Purpose Statement: Store data about an egg company adn display data to user when prompted
   Time worked on: 5 hours
*/

/* 
     Assumptions:
        User will enter a number when prompted for menu choice
        User knows what states are in the US
        User will enter a relevant date when prompted
        User will correctly format the Egg size as shown in the options
        User will clear data before entered more data
*/

/*
    Known Bugs:
        There is an infinite loop when the user enters anyting other than a number for the menu choice and there was previously a bug in
        the output. The egg grade was being listed witht he date and the size was lef tout but that bug has been fixed. 
        If a state letter is entered that does not exist, there will be no output but the program still expects the user to choose a state 
        abbreviation for a nonexistant list. 
        If the user chooses the same menu number twice, weird output happens. 
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    int choice;
    
    // initializing all variables
        char name[33] = "NA";
        char temp;
        int itemp = 1;
        char fstate, c[2024];
        char state[3] = "NA\0";
        long shipment = 0;
        char date[11] = "NA\0";
        double cost = 0;
        char grade[3]= "NA\0";
        char size[15] = "NA\0";
        double ecost = 0;

    while (choice!=6){
    // prints the menu to allow the user to choose what action
        printf("\n   Valid menu options are listed below.\n");
        printf("   ------------------------------------\n");
        printf("\t1 - Enter Company Information\n");
        printf("\t2 - Enter Shipment Information\n");
        printf("\t3 - Enter Egg Information\n");
        printf("\t4 - Display all Data\n");
        printf("\t5 - Clear all Data\n");
        printf("\t6 - Quit\n\n");
        // assuming the user will enter a number
        printf("Enter menu number: ");
        scanf("%i", &choice);
    


    //series of if statesments to determine what the program will do based on the user's choice
        // series of questions to gather company data
        if(choice == 1){
            printf("\nCompany Information\n");
            printf("--------------------\n");
            while (itemp == 1){
                printf("What is the Company Name? (limit of 32 characters) ");
                if (temp!=2){
                    scanf("%c", &temp);
                    temp = 2;
                }
                fgets(name, 33, stdin);
                int length = strlen(name);
                name[length]='\0';
                for (int i = 0; i < length; i++) {
                    if ((isalpha(name[i]))||(name[i] == 46) || (name[i] == 45)){
                        itemp = 0;
                    }
                    else if (isspace(name[i])){
                    }
                    else if (name[i]== '\0'){
                        itemp = 0;
                    }
                    else {
                        itemp = 1;
                        name[0]='\0';
                        break;
                    }
                }
            }
            
            FILE *fptr;
        
        // user validation to input a letter
            while(!isalpha(fstate)){
                printf("What is the first letter (Uppercase) of the state company? ");
                fstate = getchar();
            }

            // checking to see if input is lowercase
            if (fstate >=97 && fstate <= 122){
                fstate = fstate - 32;
            }
            
            // open file in read only mode
            fptr = fopen("StateAbbreviations.txt", "r");
            if(fptr == NULL) {
                perror("Error opening file");
            }
            
            // reading in each line with a state of the letter the user entered
            while(fgets(c, 2024, fptr) != NULL){
                if (!((*c == fstate))){
                continue;
            }
            else{
                for(int i = 0; i < strlen(c); i++){
                    printf("%c", c[i]);
                }
                printf("\n");
            }
        }
    
        // assuming that the User knows what states exist
        printf("Choose an State abbreviation from list: ");
        scanf("%s", state);  
        
        //changing lowercase entries to upper case for abbreviation purposes
        if (state[0] >=97 && state[0] <= 122){
                state[0] = state[0] - 32;
            }
        if (state[1] >=97 && state[1] <= 122){
                state[1] = state[1] - 32;
            }

    }  



// collecting shipment information
        else if (choice == 2){   
            printf("\nShipment Information\n");
            printf("---------------------\n");  
            printf("Enter the Shipment number: ");
            scanf("%ld", &shipment);
            // user validation for shipment number
            while (shipment > 999999999 || shipment < 1){
                printf("Data is too large or too small. Try again: ");
                scanf("%ld", &shipment);
            }
            
            //assuming that the user will enter a correct date. Only checking proper formatting. 
            printf("Enter the date of the shipment (mm-dd-yyyy): ");
            scanf("%s", date);
            if ((date[2] != '-' || date[5] != '-')){
                printf("invalid. Try again: ");
                scanf("%s", date);
            }
            if ((date[10] != '\0')){
                date[10]='\0';
            }

            for (int i=0; i < 10; i++){
                if (i==2 || i==5){
                    continue;
                }
                else if (!(isdigit(date[i]))){
                    printf("invalid. Try again: ");
                    scanf("%s", date);
                }
            }
            
            printf("Enter the Shipment Cost in US Dollars: ");
            scanf("%lf", &cost);
            
            
            //assuming that the user knows to enter a number 
            while (cost > 9999999999999.99){
                printf("Invalid. Try again: ");
                scanf("%lf", &cost);
            }
        }      

    //Egg information input
        else if (choice == 3){
            printf("\nEgg Information\n");
            printf("----------------\n");
            printf("Enter Egg Grade: ");
            scanf("%s", grade);
            while (((grade[0] != 'A') && (grade[0] != 'B')) || ((grade[1] != 'A') && (grade[1] != '\0'))){
                printf("Invalid. Please choose AA, A, or B. ");
                scanf("%s", grade);
            }
    
            
            printf("Enter the egg size (Small, Medium, Large, Extra-Large): ");
            scanf("%s", size);
            //int isize = atoi(size);

            //assuming the user capitalizes the egg size. 
            while (strcmp(size, "Small") && strcmp(size, "Medium") && strcmp(size, "Large") && strcmp(size, "Extra-Large") ){
                printf("Invalid. Choose Small, Medium, Large, or Extra-Large: ");
                scanf("%s", size);
            }

            //asking for individual egg cost
            printf("Enter the individual egg cost: ");
            scanf("%lf", &ecost);
            while (ecost < .01 || ecost > 999999.99){
                printf("Invalid. Try Again: ");
                scanf("%lf", &ecost);
            }
        }

    //Displaying all data
        else if(choice ==4){
            printf("\nCompany Information\n");
            printf("--------------------\n");
            printf("Company Name: %s\n", name);
            printf("Company State: %s\n", state);
            printf("\nShipment Information\n");
            printf("-----------------------\n");
            printf("Shipment number: %ld\n", shipment);
            printf("Shipment Date: %s\n", date);
            printf("Shipment Cost: %.2lf\n", cost);
            printf("\nEgg Information\n");
            printf("-----------------\n");
            printf("Egg Grade: %s\n", grade);
            printf("Egg Size: %s\n", size);
            printf("Individual Egg Cost: %.2lf\n", ecost);
        }

    //clearing all data
        else if(choice == 5){
            name[0] = '\0';
            itemp = 1;
            fstate = '\0';
            c[0]= '\0';
            state[0] = '\0';
            shipment = 0;
            date[0] = '\0';
            cost = 0;
            grade[0]= '\0';
            size[0] = '\0';
            ecost = 0;
            temp=1;
        }

    }
    return 0;
}
    
