#include <stdio.h>
#include <stdlib.h>

long long fibonacci_partial_sum(long long from, long long to){
    long long a=0, b=1, c=0, sum=0, i, pisano = 60;
    from = from % pisano;
    to = to % pisano;
    if (to < from) to += 60;
    
    for(i=0;i<from;i++){
        c=(a+b) % 10;
        a=b;
        b=c;
    }
    
    for(i=from;i<=to;i++){
        sum += a;
        sum %= 10;
        c=(a+b) % 10;
        a=b;
        b=c;
    }
    
    return sum % 10;
}

int main(){
    long long from, to;
    scanf("%ld", &from);
    scanf("%ld", &to);
    printf("%ld", fibonacci_partial_sum(from, to));
    return 0;
}
