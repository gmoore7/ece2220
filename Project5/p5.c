/* Georgia Moore
   Systems Programming
   03-29-2023
   Word Hippo - Pointers
   Purpose Statement: Recreate the functions of the Word Hippo advanced serach to grasp a deeper understanding of pointers
*/

/* 
     Assumptions:
      Assumes user will enter lowercase letters
      Assumes user will enter either Y or N when prompted
    

*/

/*   
    Known Bugs:
      findSize() function causes memory to do weird things. 
      the output in each row doesn't go over 80 characters not includign spaces, I wasn't sure if spaces were supposed to be included
      formatting of output is also skewed after putting on clemson machine. 
      randomly seg faulted but the bug may be fixed now
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

// prints the options for user and takes in choice
char printMenu(){
   char choice;
   printf("\n\n\t  Menu Options\n");
   printf(" -------------------------------\n");
   printf("| 1: Starts With...             |\n");
   printf("| 2: In the Middle...           |\n"); 
   printf("| 3: Ends With...               |\n");
   printf("| 4: Anywhere...                |\n");
   printf("| 5: Exclude...                 |\n");
   printf("| 6: Word Length...             |\n");
   printf("| q: quit                       |\n");
   printf(" -------------------------------\n\n");
   printf("    Choose a menu option: ");
   scanf("%c", &choice);
   while((choice < 49 || choice > 55) && choice != 113){
      scanf("%c", &choice);
   }
   printf("\n\n");
   return choice;
}

// couts the number of occurances of a character in a string
int NumOccur(char* str, char c, int length){
   int count = 0;
   for(int i = 0; i < length; i++){
      if(str[i]==c){
         count++;
      }
   }
   return count;
}

// finds the size of an array
long long findSize(char** array){
  long long i = 0;
  while(array[i] != 0){
      ++i;
  }
  return i;
}

// helper pring function
void printArray(char** array){
   int size = findSize(array);
   for(int i=0; i < size; i++ ){
      printf("%s", array[i]);
   }
}

// checks for words that contain given letters
char** Contains(char** reference, char* letters, long long words){
   int i=0, size = 100, num = 0;
   int occur = 0;
   int s=0;
   char** output;
   char* letterOccur;
   letterOccur = (char *) malloc(20);
   int length = (strlen(letters)-1);
   output = (char**) malloc(100);
   //checking for memory allocation for output array
   if(output == NULL){
      printf("Space not allocated\n");
   }


   // checking for want reoccuring letters in the entry
   for(int l = 0; l < length; l++){
      if(NumOccur(letters, letters[l], length) > 1){
         letterOccur[num]=letters[l];
         num++;
      }
   }
   // if there are no reoccuring letters the array for them is NULL
   if (num == 0){
      letterOccur = NULL;
   }

   //loop through all the words in the given dictionary
   for(long long j = 0; j < words; j++ ){
      occur = 0;
      
      // loop through letters entered and check if they are in the word
      for(i = 0; i < length; i++ ){
            if(strchr(reference[j], letters[i]) != NULL){
               ++occur;
            }
         }

   // if there are reoccuring letters check if they are present in word
      if(letterOccur!=NULL){
         for(int it = 0; it < strlen(letterOccur); it++){
            int it = 0;
            if(NumOccur(reference[j], letterOccur[it], strlen(reference[j])) < NumOccur(letters, letterOccur[it], length)){
               occur = 0;
            }
         }  
      }

   // otherwise the word contains the letter if the occurance is equal to the length
      if(occur >= length){
         output[s] = (char*) malloc(30);
         if(s*30 >= size){
            size = size*10;
            output = (char **) realloc(output, size);
         }

         // checking for memory allocation
         if(output[s]==NULL){
            printf("space not allocated for output");
         }
         
         //adding the word to the output 
         strcpy(output[s], reference[j]);
         s++;
      }
   }
   free(letterOccur);
   return output;
}

// looks for given substring at the being of words
char** Starts(char** words, char* letters, long long size){
   long long s=0;
   char** output;
   long long Wsize = 100;
   int length = strlen(letters);
   letters[length-1] = '\0';
   output = malloc(100);

   // loop through word list
   for(long long i = 0; i < size; i++){
      length = strlen(letters);
      if(words[i]==NULL){
         break;
      }

      // check if substring is present and at the beginning of word
      if(((strstr(words[i], letters)) != 0) && ((strncmp(words[i], letters, length)) == 0)){ 
            output[s] = malloc(30);
            if(s*30 >= Wsize){
               Wsize = Wsize*10;
               output = (char **) realloc(output, Wsize);
            }

         // checking for memory allocation
            if(output[s]==NULL){
               printf("space not allocated for output");
            }
            
         //adding the word to the output 
            strcpy(output[s], words[i]);
            s++;
         }
      }
   return output;
}

// looks for substring within words that aren't at the beigining or end
char** Middle(char** words, char* letters, long long size){
   long long s=0;
   char** output;
   int wordSize = 100;
   long long Wsize = 100;
   int length = strlen(letters);
   letters[length-1] = '\0';
   length = strlen(letters);
   output = (char**) malloc(100);
   
   // loping through all the words
   for(long long i = 0; i < size; i++){
      wordSize = strlen(words[i])-2;
      int index = wordSize - length;
      if(words[i]==NULL){
         break;
      }

      // checking if substring is present and not at the beiginning or end
      if(((strstr(words[i], letters)) != 0) && ((strncmp(words[i], letters, length)) != 0) && (strncmp((&words[i][index]), letters, length)!=0)){ 
            output[s] = (char*) malloc(30);
            if(s*30 >= Wsize){
               Wsize = Wsize*10;
               output = (char **) realloc(output, Wsize);
            }

         // checking for memory allocation
            if(output[s]==NULL){
               printf("space not allocated for output");
               exit(1);
            }
            
         //adding the word to the output 
            strcpy(output[s], words[i]);
            s++;
         }
      }
   return output;
}

// looks for given substring at end of words
char** Ends(char** words, char* letters, long long size){
   int s=0;
   char** output;
   int wordSize;
   int Wsize = 100;
   int length = strlen(letters);
   letters[length-1] = '\0';
   output = (char**) malloc(100);
   
   // looping through each word
   for(int i = 0; i < size-1; i++){
      if(words[i]==NULL){
         break;
      }
      length = strlen(letters);
      wordSize = strlen(words[i]);
      int index = wordSize - length;
      
      // checking is substring is present and at the end of word
      if((strstr(words[i], letters)) != NULL && (strncmp((&words[i][index]), letters, length)==0)){
            output[s] = (char*) malloc(30);
            if(s*30 >= Wsize){
               Wsize = Wsize*10;
               output = (char **) realloc(output, Wsize);
            }

         // checking for memory allocation
            if(output[s]==NULL){
               printf("space not allocated for output");
            }
            
         //adding the word to the output 
            strcpy(output[s], words[i]);
            s++;
         }
      }
      //output[s]='\0';
   return output;
}

// looks for words of a given length
char** wordLength(char** words, int length, long long size){
   char** output;
   int s = 0;
   int Wsize =100;
   output = (char**) malloc(100);
   
   // looping htorugh all words
   for(int i = 0; i < size; i++){
      if(words[i]==NULL){
         break;
      }
      
      // checking if word is given length
      if((strlen(words[i])) == length){
          output[s] = (char*) malloc(30);
            if(s*30 >= Wsize){
               Wsize = Wsize*10;
               output = (char **) realloc(output, Wsize);
            }

         // checking for memory allocation
            if(output[s]==NULL){
               printf("space not allocated for output");
            }
         strcpy(output[s], words[i]);
         s++;
      }
   }
   return output;
}

// looks for a given substring anywhere in words
char** anywhere(char** words, char* letters, long long size){
   long long s=0;
   char** output;
   long long Wsize = 100;
   int length = strlen(letters);
   letters[length-1] = '\0';
   output = malloc(100);
   
   // looping through all words
   for(long long i = 0; i < size; i++){
      length = strlen(letters);
      if(words[i]==NULL){
         break;
      }

      // checking if substring is present
      if(strstr(words[i], letters) != NULL){ 
            output[s] = malloc(30);
            if(s*30 >= Wsize){
               Wsize = Wsize*10;
               output = (char **) realloc(output, Wsize);
            }

         // checking for memory allocation
            if(output[s]==NULL){
               printf("space not allocated for output");
            }
            
         //adding the word to the output 
            strcpy(output[s], words[i]);
            s++;
         }
      }
   return output;
}

// looks for words excluding given letters
char** exclude(char** words, char* letters, long long size){
   long long s=0;
   int check = 1;
   char** output;
   long long Wsize = 100;
   int length = strlen(letters);
   letters[length-1] = '\0';
   output = malloc(100);
   
   // looping through all words
   for(long long i = 0; i < size; i++){
      length = strlen(letters);
      if(words[i]==NULL){
         break;
      }

      // checking is any letter is present in word
      for(int k = 0; k < length; k++){
         if(strchr(words[i], letters[k]) != NULL){
            check = -1;
         }
      }
         if(check == 1){ 
            output[s] = malloc(30);
            if(s*30 >= Wsize){
               Wsize = Wsize*10;
               output = (char **) realloc(output, Wsize);
            }

         // checking for memory allocation
         if(output[s]==NULL){
            printf("space not allocated for output");
         }
            
         //adding the word to the output 
         strcpy(output[s], words[i]);
         s++;
         }
         check = 1;
      }
   return output;
}

int main(int argc, char **argv){
   char *file = argv[1];
   char *output = argv[2];
   char **Words; 
   char Letters[64];
   char choice;
   int tmp;
   int length;
   char* test;
   char **Output;
   char contin;
   test = malloc(30);

   // read in file to WORDS array
   FILE *fptr;
   fptr = fopen(file, "r");

   if(fptr == NULL){
      printf("Error creating file\n");
      exit(1);
   }
   
   long long r = 0, Wsize = 100;


   //dynamically allocate space for the words
   Words =(char **) malloc(100);
   Words[0] = (char *) malloc(30);

   //read in words while updating size dynamically
   while( fgets(test, 30, fptr)!= NULL){
      for(int i = 0; i < (int)strlen(test); i++){
         test[i]=tolower(test[i]);
      }
      length = strlen(test);
      test[length-1]='\0';
      Words[r]=(char*)malloc(30);
      if((r*30) >= Wsize){
         Wsize = Wsize*100;
         Words = (char **)realloc(Words, Wsize);
      }
      strcpy(Words[r], test);
      ++r;
   }
   fclose(fptr);

   printf("\nWhat letters does the word contain? ");
   scanf("%i", &tmp);
   fgets(Letters, 64, stdin);
   Output = Contains(Words, Letters, r);

    //free memory from Words
   for(long long i = 0; i<r; i++){
      free(Words[i]);
   }
   free(Words);

   printf("\nAdvanced options below, to quit type q. ");



   while(choice != 'q'){
      choice = printMenu();
      if (choice == 49){
         char ** words = Output;
         printf("\nWhat does letter/letters does the word start with? ");
         scanf("%i", &tmp);
         fgets(Letters, 30, stdin);
         Output = Starts(words, Letters, findSize(words));
         printf("\nWould you Like to choose any other criteria? (Y or N) ");
         scanf("%i", &tmp);
         scanf("%c", &contin);
         if(contin == 'N'){
            break;
         }
         else{
            continue;
         }
      }
   // middle option
      else if(choice == 50){
         char** words = Output;
         printf("\nWhat does letter/letters does the word have in the middle? ");
         scanf("%i", &tmp);
         fgets(Letters, 30, stdin);
         Output = Middle(words, Letters, findSize(words));
         printf("\nWould you Like to choose any other criteria? (Y or N) ");
         scanf("%i", &tmp);
         scanf("%c", &contin);
         if(contin == 'N'){
            break;
         }
         else{
            continue;
         }
      }
   // Ends option
      else if(choice == 51){
         char** words = Output;
         printf("\nWhat does letter/letters does the word end with? ");
         scanf("%i", &tmp);
         fgets(Letters, 30, stdin);
         Output = Ends(words, Letters, findSize(words));
         printf("\nWould you Like to choose any other criteria? (Y or N) ");
         scanf("%i", &tmp);
         scanf("%c", &contin);
         if(contin == 'N'){
            break;
         }
         else{
            continue;
         }
      }
   // anywhere option
      else if(choice == 52){
         char ** words = Output;
         printf("\nWhat does letter/letters are you searching for? ");
         scanf("%i", &tmp);
         fgets(Letters, 30, stdin);
         Output = anywhere(words, Letters, findSize(words));
         printf("\nWould you Like to choose any other criteria? (Y or N) ");
         scanf("%i", &tmp);
         scanf("%c", &contin);
         if(contin == 'N'){
            break;
         }
         else{
            continue;
         }
      }
   // excludes option
      else if(choice == 53){
         char ** words = Output;
         printf("\nWhat does letter/letters are you excluding for? ");
         scanf("%i", &tmp);
         fgets(Letters, 30, stdin);
         Output = exclude(words, Letters, findSize(words));
         printf("\nWould you Like to choose any other criteria? (Y or N) ");
         scanf("%i", &tmp);
         scanf("%c", &contin);
         if(contin == 'N'){
            break;
         }
         else{
            continue;
         }
      }
   // length option
      else if(choice == 54){
         int length;
         char** words = Output;
         printf("\nWhat length? ");
         scanf("%i", &length);
         Output = wordLength(words, length, findSize(words));
         printf("\nWould you Like to choose any other criteria? (Y or N) ");
         scanf("%i", &tmp);
         scanf("%c", &contin);
         if(contin == 'N'){
            break;
         }
         else{
            continue;
         }
      }
      
   }  


   FILE *fp;
   fp = fopen(output, "w+");

    if(Output == NULL){
        printf("There is no match! Exiting program: ");
        exit(1);
    }


   int size = findSize(Output);
   int k;
   int count = 0;
   int column = 0;
   for(int j = 1; j<5; j++){
      if(size % j == 0){
         column = j;
      }
   }

   if(column == 1){
      column = 3;
   }


   fprintf(fp, "%s", Output[0]);
   for(k = 0; k<size; k++){
     if((count) == column){
         fprintf(fp, "\n");
         count = 0; 
      }
      fprintf(fp, "%-25s", Output[k]);
      count++;
   }

   fclose(fp);   


   int OutputSize = findSize(Output);

   for(int j = 0; j<OutputSize; j++){
      free(Output[j]);
   }
   free(Output);

   return 0;
}

