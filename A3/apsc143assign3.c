#include <stdio.h>
#include <math.h>

int main(){
    //init variables
    float sourceVoltage;
    float current;
    float bulbVoltage;
    float time;
    //get user input
    printf("Enter time in seconds: ");
    scanf("%f",&time);
    //calculations for source voltage
    sourceVoltage = 8 * cos(M_PI * time);
    //calculate circuit current
    current = sourceVoltage / 10;
    //calculate voltage at bulb using only the 8 ohm resistance of the bulb
    bulbVoltage = current * 8;
    //identifying voltage positivity
    if (sourceVoltage > 0){
        printf("\nSource voltage is positive\n");
    }else if (sourceVoltage < 0){
        printf("\nSource voltage is negative\n");
    }else {
        printf("Source voltage is 0\n");
    }
    //identifying closed switches
    if (sourceVoltage < -0.7){
        bulbVoltage = 0;
        printf("Switch 1 is closed\n");
    }else if (sourceVoltage > 6.4){
        bulbVoltage = 0;
        printf("Switch 2 is closed\n");
    }
    //give user bulb voltage
    printf("The Voltage of the bulb is %.2f V\n",bulbVoltage);
    //check if the bulb is within operating range
    if (1 < bulbVoltage && bulbVoltage < 5.2){
        printf("The bulb is on\n");
    }else {
        printf("The bulb is not on\n");
    }
    return 0;
}
