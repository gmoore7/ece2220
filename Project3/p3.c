/* Georgia Moore
   Systems Programming
   02-07-2023
   Bitwise Ops - Huffman Encoding/Decoding
   Purpose Statement: Allow user to decode or encode a provided statement using the huffman code
   Time worked on: 8 hours
*/

/*  Assumptions:
    The user will enter Capital letters/ appropriate characters. 
    The user with enter '[' as prompted.
    The user has a basic knowledge of binary, hex and huffmans code. 
    The user will enter a hex value to decode. 
*/

/* Known Bugs:
    After many attempts and hours spent trying to understand how to accurately use bitwise operators, I cam up short. There are many 
    issues with this code and very few successes. Biggest misunderstanding is with storing values appropriately. I could not figure 
    out how to put 2 or more binary values in one varible.
    In Encoding: 
        The user inputted values are stored in separate elements of the array instead of continually as asked. 
    In Decoding:
        Decoding does not work at all. It asked the user for input and stores it that is all. 
        The program does not output a decoded message or store the binary values in the CodeWord variable.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define UCHAR unsigned char


//fucntion to determine the number of bits associated with a symbol
int getSize(int index){
    int size;
    if (index == 0) size = 4;
    else if (index == 1) size = 6;
    else if (index == 2) size = 5;
    else if (index == 3) size = 5;
    else if (index == 4) size = 3;
    else if (index == 5) size = 5;
    else if (index == 6) size = 6;
    else if (index == 7) size = 4;
    else if (index == 8) size = 4;
    else if (index == 9) size = 7;
    else if (index == 10) size = 7;
    else if (index == 11) size = 5;
    else if (index == 12) size = 5;
    else if (index == 13) size = 4;
    else if (index == 14) size = 4;
    else if (index == 15) size = 6;
    else if (index == 16) size = 10;
    else if (index == 17) size = 4;
    else if (index == 18) size = 4;
    else if (index == 19) size = 3;
    else if (index == 20) size = 5;
    else if (index == 21) size = 6;
    else if (index == 22) size = 5;
    else if (index == 23) size = 10;
    else if (index == 24) size = 6;
    else if (index == 25) size = 10;
    else if (index == 26) size = 10;

    return size;

}

// fucntion to read bits left to right
short int reverseBits(short int num, int size){
    short int reverseNum = 0;
    for (int i = 0; i < size; i++){
        if ((num & (1 << i))){
            reverseNum |= 1 << ((size - 1) - i);
        }
    }
    return reverseNum;
}


//function to print bits
void print_bits( void *mem, UCHAR len)
{ UCHAR *addr; int bit;
  // *** Print Binary Value of Memory *** //
  for (addr=(UCHAR *)mem + len - 1; addr>=(UCHAR *)mem; addr--)
  {  for (bit = 7; bit>=0; bit--) printf((*addr >> bit) & 0x01 ? "1" : "0");
  }

}

int main(){
    //huffman code storage
    short int code[28] = {0b0001, 0b001111, 0b10110, 0b00000, 0b011, 0b11011, 0b001100, 0b1001, 0b0100, 0b11001011,
        0b1100100, 0b00001, 0b11000, 0b0101, 0b0010, 0b001110, 0b1100101000, 0b1010, 0b1000, 0b111, 0b10111,
        0b110011, 0b11010, 0b1100101001, 0b001101, 0b1100101010, 0b1100101011};
    short int CodeWord[64];
    int choice=0;
    char input[64];    
    char temp;
    int in = 1;
    int check = 1;

    // write code to quit when 3 is entered
    while(check == 1){  
        printf("Enter 1  to encode or 2 to decode or 3 to quit: ");
        scanf("%i", &choice); 
        CodeWord[0] = '\0';   
        
        //Encoding 
        if (choice == 1){
            printf("Enter statement to Encode (add [ to end): ");
            if (in == 1){
                scanf("%c", &temp);
                in = 2;
            }
            fgets(input, 64, stdin);


            // if lowercase is entered, make upper case
            for(int i=0; input[i]!='\0'; i++){
               if(islower(input[i])){
                    input[i] = input [i] - 32;
                }
            }

            int count;
            short int temp;
            int wordCount = 1;

            for(int j=0; input[j]!='\0'; j++){
                // check if input is letter, space, or eof
                if ((isalpha(input[j]) && !isspace(input[j])) || (input[j] == '[')){
                    count = (((int)input[j])-65);
                    int size = getSize(count);
                    temp = code[count];
                    CodeWord[j+1] = reverseBits(temp, size);
                    wordCount = wordCount+1;
                    
                }
            }

            //print the input as its encoded form 
            CodeWord[0] = wordCount-1;
            printf("CodeWord 0: %i\n", CodeWord[0]);
            for (int i=1; CodeWord[i] != '\0'; i++){
                printf("CodeWord %i: ", i);
                print_bits( &(CodeWord[i]), sizeof(CodeWord[i]));
                printf("  0x%X", CodeWord[i]);
                printf("  %i\n", CodeWord[i]);
            }


        }

        // decoding (I could not figure any of this out)
        else if (choice == 2){
            // store user input
            printf("Enter statement to Decode: ");
            scanf("%c", &temp);
            fgets(input, 64, stdin);

            
        }

        // quit program when prompted
        else if (choice == 3){
            check = 0;
        }
    }


    return 0;
}
