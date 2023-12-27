#include <stdio.h>
#include <stdlib.h>

//Dp için optimal çözüm ve daha küçük boyutlardaki optimal çözümler arasýnda baðlantý kurduktan sonra iki seçenek kalýyor. Anladýðým kadarýyla
//ikisi arasýndaki tercih sana kalýyor çok kesin çizgiler yok gibi hangisini kullanacaðýna dair.

//bottom up (tabulation): iterative þekilde base caseden baþlayýp istenen duruma kadar devam ettirirsin. 

//top down (memoization): recursive þekilde istenen durumdan baþlayarak sub problemlere ve base case'e doðru ilerlersin. Bunu yaparken ayný input
//için ayný sonucu tekrar tekrar hesaplamamak için bunlarý bir array veya dictte tutarsýn ve ayný input istenirse doðrudan cevabý döndürürsün.

//karmaþýklýk olarak ikisi ayný ancak memoizationda recursive çaðrý maliyeti var.

//memoizationda deðerleri tutmak için pitonda kodluyosan dict en mantýklýsý. Burda indexe göre tuttum.

long long bottom_up_fibo(long long n){
	long long arr[n+1], i;
	
	arr[0] = 0, arr[1] = 1;
	
	for(i=2;i<=n;i++){
		arr[i] = arr[i-1] + arr[i-2];
	}
	
	return arr[n];
}

long long top_down_fibo(long long n, long long* memo){
	if(n == 0 || memo[n] != 0) return memo[n];
	
	memo[n] = top_down_fibo(n-1, memo) + top_down_fibo(n-2, memo);
	
	return memo[n];
}

int main(){
	long long n, *memo;
	
	scanf("%lld", &n);
	
	memo = (long long*) calloc((n+1), sizeof(long long));
	
	memo[1] = 1;
	
	printf("%lld", bottom_up_fibo(n));
	
	printf("\n%lld", top_down_fibo(n, memo));
	
	return 0;
}
