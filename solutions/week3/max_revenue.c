#include <stdio.h>

long int max(long int n, long int* price, long int* click){
	long int max_p, max_c, index_p, index_c, i, j, result = 0;
	
	for(i=0;i<n;i++){
		max_p = -1, max_c = -1;
		for(j=0;j<n;j++){
			if(price[j] > max_p){
				max_p = price[j];
				index_p = j;
			}
			if(click[j] > max_c){
				max_c = click[j];
				index_c = j;
			}
		}
		result += max_p * max_c;
		price[index_p] = -1;
		click[index_c] = -1;
	}
	return result;
}

int main(){
	long int n, price[1000], click[1000], i;
	
	scanf("%ld", &n);
	for(i=0;i<n;i++){
		scanf("%ld", &price[i]);
	}	
	for(i=0;i<n;i++){
		scanf("%ld", &click[i]);
	}
	printf("%ld", max(n, price, click));	
	return 0;
}
