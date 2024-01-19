#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long rand_pivot(long long first, long long last){
	return (rand() % (last - first + 1)) + first;
}

//üç bölüm var: ilk kýsým küçükler, sonra eþitler sonra büyükler. Ve bunlarýn saðýnda hiç bakýlmamýþ elemanlar. Eðer yeni bakýlan eleman
//eþitse k nýn tuttuðu sayýyla swap yeterli ve sadece k yý artýrýrýz. Çünkü ikinci kýsým bir arttý.
//büyükse j yi artýrmak yeterli, 3. kýsým bir artar sadece. 
//küçükse iþler deðiþir. Eðer ki j, k dan farklýysa önce k ve i nin tuttuklarý swap edilir, sonra i ve j ninkiler. Eðer j, k ile eþitse
//i ve k için swap yapmamak lazým. Çünkü sonrasýnda yapacaðýmýz i-j swap'ý ile baþladýðýmýz yere geri dönmüþ oluruz. Ama j ve k nýn
//durumundan baðýmsýz k artýmý olmalý çünkü 1. kýsým bir arttý, ikinci kýsým bir saða kayar. 
//Ayrýca j, k sorunu yalnýzca dizideki max eleman pivot seçilirse ve bu max elemandan birden fazla varsa yaþanýyor... 
	
void pivot(long long* arr, long long first, long long last, long long* m1, long long* m2){
	long long i, j, k, temp, pivot_ind;
	
	pivot_ind = rand_pivot(first, last);
	
	temp = arr[pivot_ind];
	arr[pivot_ind] = arr[first];
	arr[first] = temp;
	
	i = first + 1; // i, pivotdan küçüklerin olduðu kýsmýn bir saðýný yani eþitlerin ilkini tutar.
	k = first + 1; // k ise eþitlerin olduðu kýsmýn bir saðýný yani büyüklerin ilkini tutar.
	 
	for(j=first+1;j<=last;j++){
		if(arr[first] > arr[j]){
			if(j != k){
				temp = arr[k];
				arr[k] = arr[i];
				arr[i] = temp;	
			}
			
			temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
		
			i++;
			k++;
		}
		else if(arr[first] == arr[j]){
			temp = arr[j];
			arr[j] = arr[k];
			arr[k] = temp;
			k++;
		}
	}
	
	temp = arr[first];
	arr[first] = arr[i-1];
	arr[i-1] = temp;
	
	*m1 = i-1;
	*m2 = k;
}

void quick_sort(long long* arr, long long n, long long first, long long last){
	long long m1, m2;
	if(first < last){
		pivot(arr, first, last, &m1, &m2);
		quick_sort(arr, n, first, m1);
		quick_sort(arr, n, m2, last);
	}
}


int main(){
	long long *arr, n, i;
	
	srand(time(0));
	scanf("%lld", &n);
	
	arr = (long long*) malloc(n * sizeof(long long));
	
	for(i=0;i<n;i++){
		scanf("%lld", &arr[i]);
	}
	
	quick_sort(arr, n, 0, n-1);
	for(i=0;i<n;i++) printf("%lld ", arr[i]);
	
	return 0;
}
