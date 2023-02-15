#include <stdio.h>
#include <math.h>

//constants used in calculations
#define k (9.65*pow(10,-2))
#define t 0.01

//function definition
double reaction(double NH3, double O2,double N2,double H2O);

int main() {
    //initial variables for concentrations
    double initNH3 = 0;
    double initO2 = 0;
    double initN2 = 0;
    double initH2O = 0;
    //user input of the NH3 and O2 concentrations
    printf("Enter initial ammonia and oxygen concentrations: ");
    scanf("%lf %lf",&initNH3,&initO2);

    //final output of the reaction length
    printf("\nThe reaction will take %.2lf seconds to reach a rate 0.001 M/s.\n",reaction(initNH3,initO2,initN2,initH2O)/100);

    return 0;
}

//recursive function to find the concentrations of the reaction
double reaction(double NH3, double O2,double N2, double H2O){
    //find the rate of rxn based on NH3 and O2
    double rate = k  * NH3 * pow(O2,2);
    //calculate new concentrations based on rate
    NH3 -= 4 * rate * t;
    O2 -= 3 * rate * t;
    N2 += rate * 2 * t;
    H2O += rate * 6 * t;
    //if the rate is below 0.001 end loop and print the values
    if (rate < 0.001){
        printf("\nFinal Reaction Molarities:");
        printf("\nNH3: %.2lf M",NH3);
        printf("\nO2:  %.2lf M",O2);
        printf("\nN2:  %.2lf M",N2);
        printf("\nH2O: %.2lf M",H2O);
        return 0;
    }else{
        //add one and rerun function using new concentration values
        return 1 + reaction(NH3,O2,N2,H2O);
    }
}