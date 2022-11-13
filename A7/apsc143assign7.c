#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main() {
    //init variables
    FILE* fp;
    int rows = 0;
    int swapped = 0;
    float sorting = 0;
    int price = 8500;
    //init array to store information
    float* givenData[3];
    //open text file
    fp = fopen("payloads.txt","r");
    //check for text file existing
    if (fp == NULL){
        printf("File not found\n");
        return 0;
    }
    //get how many rows from text file
    fscanf(fp,"%d",&rows);
    if (rows == 0){
        printf("No payloads in file.\n");
    }
    //create second dimension of array to store each set of data
    givenData[0] = (float*) malloc(rows * sizeof(float));
    givenData[1] = (float*) malloc(rows * sizeof(float));
    givenData[2] = (float*) malloc(rows * sizeof(float));
    //begin none looped prints for showing user
    printf("Payload Data:\n");
    printf("Total Mass / Grade / Ore Value\n");
    //cycle through each row calculating the value at the same time then print to user
    for (int i = 0; i < rows;i++){
        fscanf(fp,"%f %f",&givenData[0][i],&givenData[1][i]);
        givenData[2][i] = round(givenData[0][i] * givenData[1][i] * price);
        printf("   %.0f      %.2f    $%.0f\n",givenData[0][i],givenData[1][i],givenData[2][i]);
    }
    //close reading file
    fclose(fp);
    //open writing file
    fp = fopen("ores.txt","w");
    //continue loop until no swaps made
    do {
        //reset swap variable
        swapped  = 0;
        //loop through entire sequence of values switching them if need be
        //follows bubble sort algorithm
        for (int i = 0; i < rows - 1;i++){
            if (givenData[2][i] < givenData[2][i+1]){
                sorting = givenData[2][i+1];
                givenData[2][i+1] = givenData[2][i];
                givenData[2][i] = sorting;
                swapped = 1;
            }
        }
        //exit loop if no swaps made
        if (!swapped){
            break;
        }
        } while (1);
    //write to file none looped text
    fprintf(fp,"Sorted Payload Data:\n");
    fprintf(fp,"Total Mass / Grade / Ore Value\n");
    for (int i = 0; i < rows;i++){
        //write in file now sorted data
        fprintf(fp,"   %.0f      %.2f    $%.0f\n",givenData[0][i],givenData[1][i],givenData[2][i]);
    }
    return 0;
}