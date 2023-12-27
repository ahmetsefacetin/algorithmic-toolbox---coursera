#include <stdio.h>

long long dynamic(long long coins[], long long n, int sum){
	long long i, min_num_coins[sum+1], m, num_coins;
	
	min_num_coins[0] = 0;
	for(m=1;m<=sum;m++){
		min_num_coins[m] = min_num_coins[m-1] + coins[n-1]; //sonsuz bir sayý olmasýný saðlýyoruz.
		for(i=0;i<n;i++){
			if(m >= coins[i]){
				num_coins = min_num_coins[m-coins[i]] + 1;
				if(num_coins < min_num_coins[m]){
					min_num_coins[m] = num_coins;
				}
			}
		}
	}
	return min_num_coins[sum];
}

int main(){
	long long money, n = 3, coins[3] = {1,3,4};
	
	scanf("%lld", &money);

	printf("%lld", dynamic(coins, n, money));
	
	return 0;
}
