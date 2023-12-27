#include <stdio.h>

/*
Mantýk þu: her bir segmentin sol uçlarýný sýrala, sað uçlarýný sýrala. Her bir point için kendisinden kuçük eþit sol uçlarýn sayýsýndan
kendisinden küçük sað uçlarýn sayýsýný çýkarýrsak cevabý buluruz. Sebep þu: Mesela pointten küçük eþit sol uçlarýn sayýsý 4, küçük sað
uçlarýn sayýsý 2 olsun. Mantýken bu iki sað uç, 4 sol uçtan ikisinin sað ucu. Point ise geri kalan 2 sol ucun sað uçlarýndan küçük demektir.
Aksi durum olamaz zaten. Pointten küçük sað uçlarýn eþleri pointten küçük sol uçlardýr.    
Pointten küçük eþit sol uçlarýn sayýsýný bulmak için binary search kullandým. Eðer pointe eþit sol uç yoksa iþimiz kolay. Low u döndürcez. 
Ancak pointe eþit sol uç varsa eþitlerin hepsini dahil edebilmemiz lazým. Sað uçlar için ise binary search fonksiyonuna pointin bir eksiðini
yolluyorum. Çünkü sað uçlar için pointten küçüklerin sayýsý önemli.
*/

//Binary search deki yorum satýrý kýsmý gereksizdi ve worst case için n/2 iþlem yapýyodu. Amacýmýz kendisinden küçük eþit eleman sayýsýný
//bulmak olduðu için eðerki current eleman bizim elemandan küçük eþitse saða bakarýz, deðilse sola bakarýz. En sonunda mecburen low > high 
//durumuna gelicez. Çünkü küçük eþitse dizinin saðý, büyükse solu. Bunun en son noktasýnda low high ý geçer. Çünkü baþka durma noktasý yok.
//Ve bu durma noktasý da aradýðýmýz elemandan büyük en küçük sayýnýn indexini return eder...
//Aksi durumu düþün mesela daha büyük bir sayýnýn indexi dönmüþ olsun. Bu imkansýz çünkü bu sayýnýn soluna geçerdi...

long long binary_search_counter(long long* dizi, long long n, long long low, long long high, long long x){
	long long mid = (high - low) / 2 + low;
	
	if(low > high) return low;
	
//	if(dizi[mid] == x){
//	while(mid+1 < n && dizi[mid] == dizi[mid+1]) mid++;
//		return mid+1;
//	}

	if(dizi[mid] > x) return binary_search_counter(dizi, n, low, mid-1, x);
	return binary_search_counter(dizi, n, mid+1, high, x);
}

long long rand_pivot(long long first, long long last){
	return (rand() % (last - first + 1)) + first;
}

long long pivot(long long* arr, long long first, long long last){
	long long i, j, k, temp, pivot_ind;
	
	pivot_ind = rand_pivot(first, last);
	
	temp = arr[pivot_ind];
	arr[pivot_ind] = arr[first];
	arr[first] = temp;
	
	i = first + 1; // i, pivotdan küçüklerin olduðu kýsmýn bir saðýný tutar. j ise pivotdan büyüklerin olduðu kýsmýn son elemanýný.
	k = first + 1;
	
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
			k++;
			i++;
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
	return i-1;
}

long long find_m2(long long* arr, long long m1, long long last){
	long long i = m1;
	while(arr[m1] == arr[i]) i++;
	return i;
}

void quick_sort(long long* arr, long long first, long long last){
	long long m1, m2;
	if(first < last){
		m1 = pivot(arr, first, last);
		m2 = find_m2(arr, m1, last);
		quick_sort(arr, first, m1-1);
		quick_sort(arr, m2, last);
	}
}

int main(){
	long long n, m, left[50000], right[50000], points[50000], i, result;
	
	scanf("%lld %lld", &n, &m);
	
	for(i=0;i<n;i++) scanf("%lld %lld", &left[i], &right[i]);
	
	for(i=0;i<m;i++) scanf("%lld", &points[i]);
	
	quick_sort(left, 0, n-1);
	quick_sort(right, 0, n-1);
	
	for(i=0;i<m;i++){
		result = binary_search_counter(left, n, 0, n-1, points[i]) - binary_search_counter(right, n, 0, n-1, points[i]-1);
		printf("%lld ", result);
	}
	return 0;
}
