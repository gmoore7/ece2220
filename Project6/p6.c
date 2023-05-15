/* Georgia Moore
   Systems Programming
   04-11-2023
   Bitmaps
   Purpose Statement: Manipulate given bitmap images by reading binary values, edge detection to create a new image and 
                      adding gaussian noise to the image.
*/

/* 
     Assumptions:
      user understands how to view output in another file. 
      User knows to enter read, edge, or noise command when running the program 
      User inserts an output file when using read function

*/

/*   
    Known Bugs:
      Not exactly sure how the standard deviation was to be applied in the gaussian fucntion but I think it is done correctly
      If user does not put output file for read function, there is a seg fault
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>

struct HEADER 
{
    unsigned short int Type;
    unsigned int Size;
    unsigned short int Reserved1, Reserved2;
    unsigned int Offset;
} Header;

struct INFOHEADER
{
    unsigned int Size;
    int Width, Height;
    unsigned short int Planes;
    unsigned short int Bits;
    unsigned int Compression;
    unsigned int ImageSize;
    int xResolution, yResolution;
    unsigned int Colors;
    unsigned int ImportantColors;
} InfoHeader;

struct PIXEL
{
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
} pixel;

char Filter[3][3] =
    { { 0, -1, 0 },
    { -1, 4, -1 },
    { 0, -1, 0 }
    };

//checks if row, column pair is a valid point in matrix
int check(int r, int c){
    if (r >= 0 && r < InfoHeader.Height && c >= 0 && c < InfoHeader.Width) {
                return 1;
        }
    else{
        return 0;
    }
}

// makes calulations on using the given matrix on neighbors of specific pixel
struct PIXEL findNeighbors(struct PIXEL** data, int r, int c){
    struct PIXEL new;
    int status;
    new.Red = Filter[1][1] * data[r][c].Red;
    new.Green = Filter[1][1] * data[r][c].Green;
    new.Blue = Filter[1][1] * data[r][c].Blue;
    
    // checks validity of pixel and calculates new value for each neighbor
    status = check(r-1, c-1);
    if(status == 1){
        new.Red = new.Red + (Filter[0][0] * data[r-1][c-1].Red);
        new.Green = new.Green + (Filter[0][0] * data[r-1][c-1].Green);
        new.Blue = new.Blue + (Filter[0][0] * data[r-1][c-1].Blue);
    }  
    status = check(r-1, c);
    if(status == 1){
        new.Red = new.Red + (Filter[0][1] * data[r-1][c].Red);
        new.Green = new.Green + (Filter[0][1] * data[r-1][c].Green);
        new.Blue = new.Blue + (Filter[0][1] * data[r-1][c].Blue);
    }  
    status = check(r-1, c+1);
    if(status == 1){
        new.Red = new.Red + (Filter[0][2] * data[r-1][c+1].Red);
        new.Green = new.Green + (Filter[0][2] * data[r-1][c+1].Green);
        new.Blue = new.Blue + (Filter[0][2] * data[r-1][c+1].Blue);
    }  
    status = check(r, c-1);
    if(status == 1){
        new.Red = new.Red + (Filter[1][0] * data[r][c-1].Red);
        new.Green = new.Green + (Filter[1][0] * data[r][c-1].Green);
        new.Blue = new.Blue + (Filter[1][0] * data[r][c-1].Blue);
    }  
    status = check(r, c+1);
    if(status == 1){
        new.Red = new.Red + (Filter[1][2] * data[r][c+1].Red);
        new.Green = new.Green + (Filter[1][2] * data[r][c+1].Green);
        new.Blue = new.Blue + (Filter[1][2] * data[r][c+1].Blue);
    }  
    status = check(r+1, c-1);
    if(status == 1){
        new.Red = new.Red + (Filter[2][0] * data[r+1][c-1].Red);
        new.Green = new.Green + (Filter[2][0] * data[r+1][c-1].Green);
        new.Blue = new.Blue + (Filter[2][0] * data[r+1][c-1].Blue);
    }  
    status = check(r+1, c);
    if(status == 1){
        new.Red = new.Red + (Filter[2][1] * data[r+1][c].Red);
        new.Green = new.Green + (Filter[2][1] * data[r+1][c].Green);
        new.Blue = new.Blue + (Filter[2][1] * data[r+1][c].Blue);
    }  
    status = check(r+1, c+1);
    if(status == 1){
        new.Red = new.Red + (Filter[2][2] * data[r+1][c+1].Red);
        new.Green = new.Green + (Filter[2][2] * data[r+1][c+1].Green);
        new.Blue = new.Blue + (Filter[2][2] * data[r+1][c+1].Blue);
    }  
   
    return new;
    
}

// take in image and read Header and InfoHeader information
void readFile(FILE* imagePtr){
    fread(&Header.Type, 2, 1, imagePtr);

    if(Header.Type != 0x4D42){
        printf("Incorrect file type...exiting file.\n");
    }
   
    fread(&Header.Size, 4, 1, imagePtr);
    fseek(imagePtr, 4, SEEK_CUR);
    fread(&Header.Offset, 4, 1, imagePtr);
    fread(&InfoHeader.Size, 4, 1, imagePtr);
    fread(&InfoHeader.Width, 4, 1, imagePtr);
    fread(&InfoHeader.Height, 4, 1, imagePtr);
    fread(&InfoHeader.Planes, 2, 1, imagePtr);
    fread(&InfoHeader.Bits, 2, 1, imagePtr);
    fread(&InfoHeader.Compression, 4, 1, imagePtr);
    fread(&InfoHeader.ImageSize, 4, 1, imagePtr);
    fread(&InfoHeader.xResolution, 4, 1, imagePtr);
    fread(&InfoHeader.yResolution, 4, 1, imagePtr);
    fread(&InfoHeader.Colors, 4, 1, imagePtr);
    fread(&InfoHeader.ImportantColors, 4, 1, imagePtr);
}

// prints header information, bytes, and rbg values
void Read(FILE* imagePtr, FILE* outputPtr){
    readFile(imagePtr);

    fprintf(outputPtr, "Header.Type = B\n");
    fprintf(outputPtr, "Header.Type = M\n");
    fprintf(outputPtr, "Header.Size = %i\n", Header.Size);
    fprintf(outputPtr, "Header.Offset = %i\n", Header.Offset);
    fprintf(outputPtr, "InfoHeader.Size = %i\n", InfoHeader.Size);
    fprintf(outputPtr, "InfoHeader.Width = %i\n", InfoHeader.Width);
    fprintf(outputPtr, "InfoHeader.Height = %i\n", InfoHeader.Height);
    fprintf(outputPtr, "InfoHeader.Planes = %hu\n", InfoHeader.Planes);
    fprintf(outputPtr, "InfoHeader.Bits = %hu\n", InfoHeader.Bits);
    fprintf(outputPtr, "InfoHeader.Compresion = %i\n", InfoHeader.Compression);
    fprintf(outputPtr, "InfoHeader.ImageSize = %i\n", InfoHeader.ImageSize);
    fprintf(outputPtr, "InfoHeader.xResolution = %i\n", InfoHeader.xResolution);
    fprintf(outputPtr, "InfoHeader.yResolution = %i\n", InfoHeader.yResolution);
    fprintf(outputPtr, "InfoHeader.Colors = %i\n", InfoHeader.Colors);
    fprintf(outputPtr, "InfoHeader.ImportantColors = %i\n", InfoHeader.ImportantColors);
    fprintf(outputPtr, "Padding = %i\n", (4-((3*InfoHeader.Width%4))%4));
   
    // calculates padding 
    unsigned char Padding = (4-((3*InfoHeader.Width%4))%4);
    unsigned char temp;
    fseek(imagePtr, 0, SEEK_SET);
    
    //prints Bytes
    for(int i = 0; i<Header.Offset; i++){
        fread(&temp, 1, 1, imagePtr);
        fprintf(outputPtr, "Byte[%i] = %.3i\n", i, temp);
    }

    unsigned char green;
    unsigned char blue;
    unsigned char red;
    int k = 0;
    fseek(imagePtr, 54, SEEK_SET);
    
    // reads and prints RGB bits
    for(int i = 0; i<InfoHeader.Height; i++){  
        for(int j = 0; j<InfoHeader.Width; j++){
            fread(&blue, 1, 1, imagePtr);
            fread(&green, 1, 1, imagePtr);
            fread(&red, 1, 1, imagePtr);
            fprintf(outputPtr, "RGB[%i,%i] = %.3i.%.3i.%.3i\n", i,j, red,green, blue);
        }
        fread(&temp,1, 1, imagePtr);
        fprintf(outputPtr,"Padding[%i] = 000\n", i);
    }
}

// detects edges and creates new bitmap
void Edge(FILE * imagePtr, char* filename){
    int length;
    char* add = "-edge.bmp";
    char* newFile = malloc(strlen(filename)+20);
    
    readFile(imagePtr);

    // creating to file to add "-edge"
    FILE *fPtr;
    newFile = strcpy(newFile, filename);
    strcpy(&newFile[strlen(filename)-4], "-edge.bmp");
    fPtr = fopen(newFile, "wb");


    struct PIXEL** data = (struct PIXEL**) malloc(InfoHeader.Width*InfoHeader.Height*sizeof(struct PIXEL));
    unsigned char Padding = (4-((3*InfoHeader.Width%4)))%4;

    // writing all header values to new file
    fwrite(&Header.Type, 2, 1, fPtr);
    fwrite(&Header.Size, 4, 1, fPtr);
    fwrite(&Header.Reserved1, 2, 1, fPtr);
    fwrite(&Header.Reserved2, 2, 1, fPtr);
    fwrite(&Header.Offset, 4, 1, fPtr);
    
    fwrite(&InfoHeader.Size, 4, 1, fPtr);
    fwrite(&InfoHeader.Width, 4, 1, fPtr);
    fwrite(&InfoHeader.Height, 4, 1, fPtr);
    fwrite(&InfoHeader.Planes, 2, 1, fPtr);
    fwrite(&InfoHeader.Bits, 2, 1, fPtr);
    fwrite(&InfoHeader.Compression, 4, 1, fPtr);
    fwrite(&InfoHeader.ImageSize, 4, 1, fPtr);
    fwrite(&InfoHeader.xResolution, 4, 1, fPtr);
    fwrite(&InfoHeader.yResolution, 4, 1, fPtr);
    fwrite(&InfoHeader.Colors, 4, 1, fPtr);
    fwrite(&InfoHeader.ImportantColors, 4, 1, fPtr);

    // reads in RGB bits
    unsigned char temp;
    fseek(imagePtr, 54, SEEK_SET);
    for(int i = 0; i<InfoHeader.Height; i++){  
        data[i] = malloc(InfoHeader.Width * sizeof(struct PIXEL));
        for(int j = 0; j<InfoHeader.Width; j++){
            fread(&data[i][j].Blue, 1, 1, imagePtr);
            fread(&data[i][j].Green, 1, 1, imagePtr);
            fread(&data[i][j].Red, 1, 1, imagePtr);
        }
        if(Padding>0){
            for(int k = 0; k<Padding; k++){
                fread(&temp,1,1, imagePtr);
            }
        }
    }

  
    // Edge detection creating new bitmap
    struct PIXEL** newMap= (struct PIXEL**) malloc(InfoHeader.Width*InfoHeader.Height*sizeof(struct PIXEL));
    struct PIXEL new;
    for(int i = 0; i<InfoHeader.Height; i++){
        newMap[i] = malloc(InfoHeader.Width*sizeof(struct PIXEL));
        for(int j = 0; j< InfoHeader.Width; j++){
            new = findNeighbors(data, i, j);
            newMap[i][j]=new;
        }
    }

    // writing new bitmap 
    for(int i = 0; i<InfoHeader.Height; i++){  
        for(int j = 0; j<InfoHeader.Width; j++){
            fwrite(&newMap[i][j].Blue, 1, 1, fPtr);
            fwrite(&newMap[i][j].Green, 1, 1, fPtr);
            fwrite(&newMap[i][j].Red, 1, 1, fPtr);
        }
        if(Padding>0){
            for(int k = 0; k<Padding; k++){
                fwrite(&temp,1,1, fPtr);
            }
        }
    }

    fclose(fPtr);
    for(int i = 0; i<InfoHeader.Height; i++){ 
        free(data[i]);
    }
    free(data);
}

// creates random gaussian number
double gaussian(double l, double h){
    double v1 = ((double)rand()+1)/((double)(RAND_MAX)+1);
    double v2 = ((double)rand()+1)/((double)(RAND_MAX)+1);
    return (((cos(2*3.14*v2)*sqrt(-2*log(v1)))*h)+l);
}

// adds gaussian distribution noise and creates new file
void Noise(FILE* imagePtr, char*filename){
    int length;
    char* add = "-noise.bmp";
    char* newFile = malloc(strlen(filename)+11);
    double low = 5;
    double high = 20;
    
    readFile(imagePtr);

    // creating to file to add "-noise"
    FILE *fPtr;
    newFile = strcpy(newFile, filename);
    strcpy(&newFile[strlen(filename)-4], "-noise.bmp");
    fPtr = fopen(newFile, "wb");

    struct PIXEL** RGB = (struct PIXEL**) malloc(InfoHeader.Width*InfoHeader.Height*sizeof(struct PIXEL));
    unsigned char Padding = (4-((3*InfoHeader.Width%4)))%4;

    // writing all header values to new file
    fwrite(&Header.Type, 2, 1, fPtr);
    fwrite(&Header.Size, 4, 1, fPtr);
    fwrite(&Header.Reserved1, 2, 1, fPtr);
    fwrite(&Header.Reserved2, 2, 1, fPtr);
    fwrite(&Header.Offset, 4, 1, fPtr);
    
    fwrite(&InfoHeader.Size, 4, 1, fPtr);
    fwrite(&InfoHeader.Width, 4, 1, fPtr);
    fwrite(&InfoHeader.Height, 4, 1, fPtr);
    fwrite(&InfoHeader.Planes, 2, 1, fPtr);
    fwrite(&InfoHeader.Bits, 2, 1, fPtr);
    fwrite(&InfoHeader.Compression, 4, 1, fPtr);
    fwrite(&InfoHeader.ImageSize, 4, 1, fPtr);
    fwrite(&InfoHeader.xResolution, 4, 1, fPtr);
    fwrite(&InfoHeader.yResolution, 4, 1, fPtr);
    fwrite(&InfoHeader.Colors, 4, 1, fPtr);
    fwrite(&InfoHeader.ImportantColors, 4, 1, fPtr);

    // reads in RGB bits
    unsigned char temp;
    fseek(imagePtr, 54, SEEK_SET);
    for(int i = 0; i<InfoHeader.Height; i++){  
        RGB[i] = malloc(InfoHeader.Width * sizeof(struct PIXEL));
        for(int j = 0; j<InfoHeader.Width; j++){
            fread(&RGB[i][j].Blue, 1, 1, imagePtr);
            fread(&RGB[i][j].Green, 1, 1, imagePtr);
            fread(&RGB[i][j].Red, 1, 1, imagePtr);
        }
        if(Padding>0){
            for(int k = 0; k<Padding; k++){
                fread(&temp,1,1, imagePtr);
            }
        }
    }

    // adds gaussian noise to each pixel
    double Rand;
    struct PIXEL** newMap = (struct PIXEL**) malloc(InfoHeader.Height*InfoHeader.Width*sizeof(struct PIXEL));
    for(int i = 0; i<InfoHeader.Height; i++){
        newMap[i]=malloc(InfoHeader.Width*sizeof(struct PIXEL));
        for(int j = 0; j<InfoHeader.Width; j++ ){
            Rand = gaussian(low, high);
            newMap[i][j].Blue = RGB[i][j].Blue + Rand;
            Rand = gaussian(low, high);
            newMap[i][j].Green = RGB[i][j].Green + Rand;
            Rand = gaussian(low, high);
            newMap[i][j].Red = RGB[i][j].Red + Rand;
        }
    }

    //writes new values to new file
    for(int i = 0; i<InfoHeader.Height; i++){  
        for(int j = 0; j<InfoHeader.Width; j++){
            fwrite(&newMap[i][j].Blue, 1, 1, fPtr);
            fwrite(&newMap[i][j].Green, 1, 1, fPtr);
            fwrite(&newMap[i][j].Red, 1, 1, fPtr);
        }
        if(Padding>0){
            for(int k = 0; k<Padding; k++){
                fwrite(&temp,1,1, fPtr);
            }
        }
    }
    fclose(fPtr);
     for(int i = 0; i<InfoHeader.Height; i++){ 
        free(RGB[i]);
    }
    free(RGB);


}

int main(int argc, char** argv){
    char* action = argv[1];
    FILE *imagePtr;
    FILE *outputPtr;
    char * filename = (char*) malloc(30);
    imagePtr = fopen(argv[2], "rb");
    outputPtr = fopen(argv[3], "w");
    filename = argv[2];

    if(imagePtr == NULL){
      printf("Error creating file\n");
      exit(1);
    }

    if(strcmp(action, "read") == 0){
        Read(imagePtr, outputPtr);
    }
    else if(strcmp(action, "edge") == 0){
        Edge(imagePtr, argv[2]);
    }
    else if(strcmp(action, "noise") == 0){
        Noise(imagePtr, argv[2]);
    }
    else {
        printf("Invalid action...exiting program\n");
        exit(1);
    }

    fclose(imagePtr);

    return 0;
}