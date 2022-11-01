#include <stdio.h>
#include <string.h>

int main(){
    //get user input for how many acronyms
    int acronyms = 0;
    printf("Enter number of acronyms to add to the database: ");
    scanf("%d",&acronyms);
    //accept the enter key to not interfere with long strings
    getchar();
    //create 2 arrays to store values of acronyms and full length
    char fullLengthString[acronyms][50];
    char shortString[acronyms][50];
    //variable for keeping order of acronym order
    int place;
    //loop through how many acronyms to be made
    for (int i = 0; i < acronyms;i++){
        //reset count for each new acronym
        place = 0;
        //get user input in full length
        printf("\nEnter the string to convert into an acronym: ");
        fgets(fullLengthString[i],50,stdin);
        //cycle through each char of user input
        for (int j = 0; j < 50;j++){
            //if capital letter add to shortened array at place position
            if (65 <= fullLengthString[i][j] && fullLengthString[i][j] <= 90){
                shortString[i][place] = fullLengthString[i][j];
                place++;
                //if the valid string is over, must be null or new line, then make null on both and end loop
            }else if (fullLengthString[i][j] == '\n'||fullLengthString[i][j] == '\0'){
                fullLengthString[i][j] = '\0';
                shortString[i][place] = '\0';
                break;
            }
        }
        //return to user the value and acronym
        printf("\nAcronym of \"%s\" is \"%s\".",fullLengthString[i],shortString[i]);
    }
    //create new user input
    char user[50];
    //repeat infinitely
    do {
        //get user input to return acrnoyms
        printf("\nEnter the acronym of the string you would like to see, or enter 0 to exit: ");
        fgets(user,50,stdin);
        //if 0 exit loop
        if (strcmp(user,"0") == 0 || strcmp(user,"0\n") == 0){
            break;
        }else {
            //check for null/end line, make null for proper comparison later
            for (int i = 0; i < 50; i++) {
                if (user[i] == '\0' || user[i] == '\n') {
                    user[i] = '\0';
                }
            }
            //check through all acronyms for a match
            for (int i = 0; i < acronyms; i++) {
                //if equal to known acronym output both acronym and string
                if (strcmp(user, shortString[i]) == 0) {
                    printf("\nThe corresponding string to \"%s\" is \"%s\".", shortString[i], fullLengthString[i]);
                }else {
                    //return no match to user if no acronym matches
                    printf("\nNo match found.");
                }
            }
        }
    } while (1);
    return 0;
}