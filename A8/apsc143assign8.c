#include <stdio.h>
#include <math.h>

//function definitions
    //get value from e^x^2
double function(double xValue);
    //find factorial of a number
int factorial(int number);
    //calculate riemann sums from lower to upper for intervals amount
float riemann(double lower, double upper, int intervals);
    //find y value using taylor series from input using intervals
float taylor (double input, int intervals);
    //calculate riemann sums using taylor series for y values
float mixedSeries(double lower, double upper, int intervals);
    //calculate error between riemann sums and taylor series riemann sums
float error(double lower, double upper, int intervals);

int main() {
    //creates variables for user input
    double lowerBound = 0;
    double upperBound = 0;
    //check for valid bounds
    do {
        printf("\nEnter the bounds to compute the Riemann Sum: ");
        scanf(" %lf %lf", &lowerBound, &upperBound);
    } while (upperBound < lowerBound);

    //print riemann sums at various intervals
    printf("\nRiemann Sum with 5 intervals: %.2f",riemann(lowerBound,upperBound,5));
    printf("\nRiemann Sum with 25 intervals: %.2f",riemann(lowerBound,upperBound,25));
    printf("\nRiemann Sum with 100 intervals: %.2f",riemann(lowerBound,upperBound,100));

    //print Taylor series at various intervals
    printf("\nTaylor Series Approximation at x = %.2f with 3 terms: %.2f",lowerBound, taylor(lowerBound,3));
    printf("\nTaylor Series Approximation at x = %.2f with 5 terms: %.2f",lowerBound, taylor(lowerBound,5));
    printf("\nTaylor Series Approximation at x = %.2f with 10 terms: %.2f",lowerBound, taylor(lowerBound,10));

    //print riemann sums with taylor series
    printf("\nTaylor Series Riemann Sum with 5 intervals: %.2f", mixedSeries(lowerBound,upperBound,5));
    printf("\nTaylor Series Riemann Sum with 25 intervals: %.2f", mixedSeries(lowerBound,upperBound,25));
    printf("\nTaylor Series Riemann Sum with 100 intervals: %.2f", mixedSeries(lowerBound,upperBound,100));

    //output error between riemann and mixed function
    printf("\nError in Riemann Sums with 5 intervals: %.2f%%", error(lowerBound,upperBound,5));
    printf("\nError in Riemann Sums with 25 intervals: %.2f%%", error(lowerBound,upperBound,25));
    printf("\nError in Riemann Sums with 100 intervals: %.2f%%", error(lowerBound,upperBound,100));

    return 0;
}

double function(double xValue){
    //calculate value for e^x^2 value
    return pow(M_E, pow(xValue,2));
}
int factorial(int number){
    //if factorial is 0 then return 1
    if (number == 0) {
        return 1;
    }
    //calculate factorial by decreasing the interval by one each time
    for (int i = number; i>=2;i--){
        number *= i - 1;
    }
    return number;
}
float riemann(double lower, double upper, int intervals){
    //create variables for calculating riemann
    double deltaX;
    double area = 0;
    //find deltaX to calculate sums
    deltaX = (upper-lower)/intervals;
    //loop through amount of intervals and find rectangle area at each x value
    for (int i = 0; i < intervals;i++){
        area += (function(lower+(deltaX*i)) * deltaX);
    }
    //return the total area of the riemann sums
    return area;
}
float taylor(double input, int intervals){
    double total = 0;
    for(int i = 0;i < intervals;i++){
        //using taylor series equation find the estimated y value
        total += pow(pow(input,2),i)/ factorial(i);
    }
    //return the total Taylor value
    return total;
}
float mixedSeries(double lower, double upper, int intervals){
    double deltaX;
    double area = 0;
    //create the x intervals
    deltaX = (upper-lower)/intervals;
    for (int i = 0; i < intervals;i++){
        //calculate riemann sum using taylor series for y values
        area += (taylor(lower + (deltaX * i),10) * deltaX);
    }
    return area;
}
float error(double lower, double upper, int intervals){
    //return error between the mixed and riemann by substituting (m-r)/r changed to a percentage
    return (100 * (mixedSeries(lower,upper,intervals)- riemann(lower,upper,intervals))/riemann(lower,upper,intervals));
}
