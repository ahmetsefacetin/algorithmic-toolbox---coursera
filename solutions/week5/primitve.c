#include <stdio.h>
#include <stdlib.h>

// Ana mantýk þu: money change de olduðu gibi 1'den n'e kadar tüm sayýlar için kendinden önceki ihtimallerin her birine bakýp minimumu
// seçiyoruz. Mesela n = 8 için arr = {0,0,1,1,2,3,2,3,4} olur. Çünkü mesela i = 8 için þu gerçekleþir: 3'e bölünmez yani ilk koþulu atlar,
// 2'e bölünür ve þu anki arr[8], arr[4] + 1'den büyük, yani arr[8] = arr[4] + 1 olacak çünkü arr[4] üzerine bir iþlem daha yapmýþ olduk.
// en son koþul da arr[8], arr[7] + 1'den büyük deðil yani girmeden atlar.


long long prim(long long n, long long *arr){
	long long i, j;
	for(i=2;i<=n;i++){
		arr[i] = n+1; // sonsuza eþitlemek için kullandýk
		if(i % 3 == 0 && arr[i] > arr[i/3] + 1) arr[i] = arr[i/3] + 1;
		if(i % 2 == 0 && arr[i] > arr[i/2] + 1) arr[i] = arr[i/2] + 1;
		if(arr[i] > arr[i-1] + 1) arr[i] = arr[i-1] + 1;
	}
	
	return arr[n];
}

void print_n(long long n, long long* arr){
	long long i = n, j=0, *temp;
	
	temp = (long long*) malloc((n+1) * sizeof(long long));	
		
	while(i != 1){
		if(i % 3 == 0 && arr[i] == arr[i/3] + 1){
			temp[j++] = i;
			i /= 3;
		}
		else if(i % 2 == 0 && arr[i] == arr[i/2] + 1){
			temp[j++] = i;
			i /= 2;
		}
		else{
			temp[j++] = i;
			i--;
		}
	}
	
	temp[j] = 1;
	for(i=1;i<=n;i++) printf("%lld ", i);
//	for(i=j;i>=0;i--) printf("%lld ", temp[i]);
}

int main(){
	long long n, *arr;
	
	scanf("%lld", &n);
	
	arr = (long long*) malloc((n+1) * sizeof(long long));	
	
	arr[1] = 0;
	
	printf("%lld\n", prim(n, arr));
	
	print_n(n, arr);
	
	return 0;
}
