// name: Mingzhe Ou
// email: ou.mi@northeastern.edu

#include <stdio.h>

int d[20];

long long int dp(int n) {

    // Add your code here
    if(n == 0) return 1;
    if(n == 1) return 0;
    if(n == 2) return 3;

    long long int result = 3 * dp(n - 2);

    if(d[n] != -1) return d[n];

    for (int k = 4; k <= n; k += 2) {
        result += 2 * dp(n - k);
    }

    return result;
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp(n));
}
