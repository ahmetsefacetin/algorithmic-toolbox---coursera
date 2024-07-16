#include <stdio.h>

/*
Mant�k �u: her bir segmentin sol u�lar�n� s�rala, sa� u�lar�n� s�rala. Her bir point i�in kendisinden ku��k e�it sol u�lar�n say�s�ndan
kendisinden k���k sa� u�lar�n say�s�n� ��kar�rsak cevab� buluruz. Sebep �u: Mesela pointten k���k e�it sol u�lar�n say�s� 4, k���k sa�
u�lar�n say�s� 2 olsun. Mant�ken bu iki sa� u�, 4 sol u�tan ikisinin sa� ucu. Point ise geri kalan 2 sol ucun sa� u�lar�ndan k���k demektir.
Aksi durum olamaz zaten. Pointten k���k sa� u�lar�n e�leri pointten k���k sol u�lard�r.    
Pointten k���k e�it sol u�lar�n say�s�n� bulmak i�in binary search kulland�m. E�er pointe e�it sol u� yoksa i�imiz kolay. Low u d�nd�rcez. 
Ancak pointe e�it sol u� varsa e�itlerin hepsini dahil edebilmemiz laz�m. Sa� u�lar i�in ise binary search fonksiyonuna pointin bir eksi�ini
yolluyorum. ��nk� sa� u�lar i�in pointten k���klerin say�s� �nemli.
*/

//Binary search deki yorum sat�r� k�sm� gereksizdi ve worst case i�in n/2 i�lem yap�yodu. Amac�m�z kendisinden k���k e�it eleman say�s�n�
//bulmak oldu�u i�in e�erki current eleman bizim elemandan k���k e�itse sa�a bakar�z, de�ilse sola bakar�z. En sonunda mecburen low > high 
//durumuna gelicez. ��nk� k���k e�itse dizinin sa��, b�y�kse solu. Bunun en son noktas�nda low high � ge�er. ��nk� ba�ka durma noktas� yok.
//Ve bu durma noktas� da arad���m�z elemandan b�y�k en k���k say�n�n indexini return eder...
//Aksi durumu d���n mesela daha b�y�k bir say�n�n indexi d�nm�� olsun. Bu imkans�z ��nk� bu say�n�n soluna ge�erdi...

long long binary_search_counter(long long* dizi, long long n, long long low, long long high, long long x){
	long long mid = (high - low) / 2 + low;
	
	if(low > high) return low; //e�er x dizide yoksa bu fonksiyon hatal� �al���r ancak soruda zaten var olan bir eleman� aramak i�in kullan�yoruz
	
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

void pivot(long long* arr, long long first, long long last, long long* m1, long long* m2){
	long long i, j, k, temp, pivot_ind;
	
	pivot_ind = rand_pivot(first, last);
	
	temp = arr[pivot_ind];
	arr[pivot_ind] = arr[first];
	arr[first] = temp;
	
	i = first + 1; // i, pivotdan k���klerin oldu�u k�sm�n bir sa��n� yani e�itlerin ilkini tutar.
	k = first + 1; // k ise e�itlerin oldu�u k�sm�n bir sa��n� yani b�y�klerin ilkini tutar.
	 
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

void quick_sort(long long* arr, long long first, long long last){
	long long m1, m2;
	if(first < last){
		pivot(arr, first, last, &m1, &m2);
		quick_sort(arr, first, m1);
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
