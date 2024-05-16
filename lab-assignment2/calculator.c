// Mingzhe Ou
// ou.mi@northeastern.edu
#include<stdio.h>
int main()
{
    int a,b,c, choice;
    
    printf("Enter your choice\n");
    printf(" 1. addition\n 2. Subtraction\n 3. Multiplication\n 4. Division\n");
    scanf("%d",&choice);
    
    printf("Enter a and b values: ");
    scanf("%d %d", &a, &b);
    
    // Add your code here using switch
    switch(choice){
        case 1:
            c = a + b;
            printf("Addition\n");
            printf("Sum=%d\n", c);
            break;

        case 2:
            c = a - b;
            printf("Subtraction\n");
            printf("Difference=%d\n", c);
            break;

        case 3:
            c = a * b;
            printf("Multiplication\n");
            printf("Product=%d\n", c);
            break;

        case 4:
            if(b != 0){
                c = a / b;
                printf("Division\n");
                printf("Quotient=%d\n", c);
            }else{
                printf("Denominator can't be 0.\n");
            }        
            break;
        
        default: 
        printf("Invalid option");
        break;
    }
           
    return 0;
}
