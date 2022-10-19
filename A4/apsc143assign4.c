#include <stdio.h>
#include <math.h>

int main() {
    //init user variables
    double initCost;
    double annuity;
    double interest;
    int lifespan;
    //init calculation variables
    double currentValue = 0;
    double futureValue;
    double paybackAmount;
    //get user input
    printf("\nEnter the initial cost of the project: $");
    scanf("%lf", &initCost);
    printf("\nEnter the annuity of the project: $");
    scanf("%lf",&annuity);
    printf("\nEnter the interest rate in %%: ");
    scanf("%lf",&interest);
    //adjust interest input to reflect calculation value
    interest /= 100;
    interest += 1;
    printf("\nEnter the lifespan of the project in years: ");
    scanf("%d", &lifespan);
    //loop for present worth of project and economic feasibility
    for (int i = 1; i <= lifespan; i++){
        futureValue = annuity;
        futureValue /= (pow(interest,i));//adjust future value to current using interest
        currentValue += futureValue;
    }
    currentValue -= initCost;//returns present value without init cost
    if (currentValue > 0) {//output present worth and economic feasibility based on value
        printf("\nPresent worth of the project = $%0.2lf\n", currentValue);
        printf("The project is economically feasible.\n");
    }else {
        currentValue = abs(currentValue);//ignore negative sign as its printed before $ sign
        printf("\nPresent worth of the project = -$%0.2lf\n", currentValue);
        printf("The project is not economically feasible.\n");
    }
    //calculate payback years
    paybackAmount = initCost;
    for (int i = 1;;i++){
        paybackAmount *= interest;//add interest
        paybackAmount -= annuity;//subtract payment from user
        if (paybackAmount <= 0) {//complete payback
            printf("The payback period for this project is %d years.", i);
            break;
        }
    }
    printf("\n");
    return 0;
}
