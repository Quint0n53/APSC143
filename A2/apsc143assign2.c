#include <stdio.h>
#include <math.h>

int main() {
    float g = 9.8; //gravity constant
    float boxSpringMass = 0;
    float throneMass = 0;
    float totalMass = 0;
    float newtons = 0; //must be a float for newtons as it can be a decimal
    int students = 0;
    int totalSeconds = 0;//for calculating time at the end
    int minutes = 0;
    int seconds = 0;
    //getting user input
    printf("Enter the mass of the box spring in kg: ");
    scanf("%f",&boxSpringMass);
    printf("Enter the mass of the throne in kg: ");
    scanf("%f",&throneMass);
    //finding mass of thundermugz
    totalMass = boxSpringMass + throneMass;
    newtons = totalMass * g;
    //calculate how many students are needed and round up in case of decimal
    students = ceil(newtons/300);
    //find total time in seconds using equation provided
    totalSeconds = totalMass * (4 - pow(M_E,0.1*students));
    //calculate minutes and seconds from total time
    minutes = floor(totalSeconds/60);
    seconds = floor(totalSeconds%60);
    //output final answers
    printf("\nThe ThunderMugz will need a minimum of %d students to carry it.",students);
    printf("\nIt will take %d minutes and %d seconds to complete the ThunderMugz challenge.",minutes, seconds);
    return 0;
}
