#include <stdio.h>
#include <math.h>

int main() {
    int limestones;
    int lowestGravityID = 0;

    //collect user input
    printf("Enter the number of limestones to compare: ");
    scanf("%d",&limestones);

    double limestoneData[limestones][4];//porosity,hydraulic conductivity, gravity, flow
    //get data for each limestone and store in an array
    for (int i = 0 ;i < limestones;i++){
        printf("\nEnter the porosity %%, hydraulic conductivity (m/s), and specific gravity for Limestone %d: ",i + 1);
        scanf("%lf %lf %lf",&limestoneData[i][0],&limestoneData[i][1],&limestoneData[i][2]);
    }
    //check through all gravities and find lowest, use a placeholder variable to identify current lowest gravity
    for (int i = 0; i < limestones;i++){
        if (limestoneData[i][2] < limestoneData[lowestGravityID][2]){
            lowestGravityID = i;
        }
    }
    //print lowest gravity
    printf("\nThe limestone with the lowest specific gravity is Limestone %d with a specific gravity of %lf\n", lowestGravityID + 1,limestoneData[lowestGravityID][2] );

    //calculate and print flow velocities
    printf("\nFlow velocities:\n");
    for (int i = 0;i < limestones;i++){
        limestoneData[i][3] = abs(-1*limestoneData[i][1]*1200*-0.725*1000000);
        printf("Limestone %d: %0.2lf cm^3/s\n",i + 1,limestoneData[i][3]);
    }
    //place holder variables for porosity vs flow
    int highestPorID = 0;
    int highestFlowID = 0;
    //find highest porosity using same idea as gravity
    for (int i = 0; i < limestones;i++){
        if (limestoneData[i][0] >= limestoneData[highestPorID][0]) {
            highestPorID = i;
        }
    }
    //find highest flow using same idea as gravity
    for (int i = 0; i < limestones;i++){
        if (limestoneData[i][3] >= limestoneData[highestFlowID][3]) {
            highestFlowID = i;
        }
    }
    //compare flow vs porosity and output correct statement
    if (highestFlowID == highestPorID){
        printf("The rock with the highest porosity has the highest flow velocity.");
    }else {
        printf("The rock with the highest porosity does not have the highest flow velocity.");
    }

    return 0;
}
