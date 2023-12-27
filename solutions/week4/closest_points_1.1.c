#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Ýki boyutta en yakýn iki noktayý bulma, O(n*(logn)^2): Elimizdeki noktalarý x kordinatlarýna göre sýralýyoruz. Sonra divide and conquer
mantýðýyla n nokta varsa ilk n/2 sine yani soluna bir recursive çaðrýda, saðýna ise diðer recursive çaðrýda bakacaz. Base caseler ise n'in
2 ve 3 olduðu durum için geçerli. Neden bunlar? çünkü elimizde tek nokta kalmasýný istemiyoruz. Sadece 2 için base case olsaydý n = 3 için 
solu iki saðý 1 diye ayýrýrdýk. Sonuç olarak sað taraftan ne dönücek...

Þimdi bu yaklaþýmda sýkýntý þurada: Noktalarý iki ayrý kýsma ayýrdýk ve bunlarý ayrý ayrý inceledik. Sol kýsýmda minimum uzaklýk d1 çýkmýþ 
olsun, saðda ise d2. Bunlardan minimum olanýna d diyip döndürdük diyelim. Biri saðda biri solda bulunan iki nokta arasý mesafe d'den daha
küçük olabilir ama biz bunu hiç ölçmemiþ olucaz. Bunu ölçebilmek için fonksiyona combine kýsmýný ekledik.

Combine için mantýk þu: Bu þartlarda d'den küçük mesafeye sahip iki nokta varsa bu noktalar ayýrdýðýmýz noktanýn yani mid'deki noktanýn x'inin
en fazla d solunda veya en fazla d saðýnda olmalý. Bu kapsamýn dýþýnda ise iki noktanýn x leri farký d den büyük olacaðýndan deðerlendirmeye 
gerek kalmaz. Yani yalnýzca bu kapsamdaki noktalarý alýcaz ve bir diziye kaydedicez. 

Sonrasýnda bir geometri gerçeðinden faydalanýcaz. Varsayalým ki sað ve sol kýsýmdan minimum mesafe olarak d yi elde ettik. Bu sebeple combine
kýsmý için mid deki noktanýn d solu ve d saðý içindeki noktalarý bi diziye kaydettik. Bu noktalarýn y kordinatlarýna da ayný iþlemi yaparsak,
yani d mesafesine göre bakarsak görücez ki kenar uzunluðu d olan ve üst üste veya yan yana olan iki karede en fazla 6 nokta bulunur. Karelerin
köþelerine noktalarý yerleþtir. 6 nokta eder. 7. nokta nerede olursa olsun diðer noktalarla arasýndaki mesafe d den küçük olur. Bu da bi 
çeliþki oluþturur. Çünkü herbir kare bir bölgeye ait. Recursive çaðrýlarda bu noktalar arasýndaki mesafe ölçülürdü ve d olduðundan küçük 
çýkardý.

Þimdi bu durumda combine aþamasýnda y lere göre sýralama yaparsak her bir nokta için y kordinatýna göre en fazla kendisinden yukardaki 6 nokta
ile arasýndaki mesafe d den küçük çýkma adayý olurdu. Bunun uygulamasýný close_strip_2 fonksiyonunda görebilirsin. Aslýnda close_strip 
fonksiyounda yapýlanýn önceki ile hiçbir farký yok sadece daha temiz duruyor. strip_2 de her tur n karþýlaþtýrma var gibi düþünebilirsin ama
y ye göre sýralý ve d mesafesini aþtýðý ilk anda çýkacak ve i artýcak yani en fazla 6 karþýlaþtýrma ve hesap olacak. Ki zaten j=i+1 atamsý var.
kendisinin hemen üstündeki noktadan baþlýyor. Boþa dönme ihtimali yok normal strip ile ayný fonksiyon.


Analysis: T(n) = 2T(n/2) + O(nlogn) baðýntýsý var. Her bir çaðrýda y lere göre sýralama olacaðýndan nlogn lik iþ yapýlýr. Yükseklik logn olur ve
her bir seviyede yapýlan iþ eþittir. nlogn*logn yani O(n*(logn)^2) olur.
*/

void merge(long long left, long long mid, long long right, long long x[], long long y[]){
	long long n, m, i, j, k;
	n = mid - left + 1;
	m = right - mid;
	int L[n][2], R[m][2];
	
	for(i=0;i<n;i++){
		L[i][0] = x[left + i];
		L[i][1] = y[left + i];
	}
	
	for(i=0;i<m;i++){
		R[i][0] = x[mid + 1 + i];
		R[i][1] = y[mid + 1 + i];
	}
	
	i=0, j=0, k=left;
	while(i < n && j < m && L[n-1][0] > R[j][0]){
		if(L[i][0] > R[j][0]){
			x[k] = R[j][0];
			y[k] = R[j][1];
			j++;
		}
		else{
			x[k] = L[i][0];
			y[k] = L[i][1];
	 		i++;
	 	}
	 	k++;
	}
	
	while(i < n){
		x[k] = L[i][0];
		y[k] = L[i][1];
		i++;
		k++;
	}
	
	while(j < m){
		x[k] = R[j][0];
		y[k] = R[j][1];
		j++;
		k++;
	}
}

void merge_sort(long long left, long long right, long long x[], long long y[]){
	long long mid;
	if(left < right){
		mid = left + (right - left) / 2;
		
		merge_sort(left, mid, x, y);
		merge_sort(mid + 1, right, x, y);
		
		merge(left, mid, right, x, y);
	}
}

double dist(long long x1, long long y1, long long x2, long long y2){
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//O(n^2): y ye göre sýralama yapmadýk o sebeple y lerine göre d den küçük mesafedeki noktalar, en fazla 6 tane olduklarýný bilsek de, karýþýk
//durumdalar yani her bir noktaya bakmalýyýz.

double close_strip_1(long long x[], long long y[], double d, long long left, long long right, long long mid){
	long long n = right-left+1, strip_x[n], strip_y[n], i, j=0;
	double min = d;
	
	for(i=left;i<=right;i++){
		if(llabs(x[mid] - x[i]) < d){
			strip_x[j] = x[i];
			strip_y[j] = y[i];
			j++;
		}
	}
	
	n = j;
	
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(strip_y[j] - strip_y[i] < min){
				d = dist(strip_x[j], strip_y[j], strip_x[i], strip_y[i]);
				if(min > d) min = d;
			}
		}
	}
	return min;
}

//O(n*logn): y  ye göre sýraladýk. Bu sebeple içerdeki döngüde y koordinatý þu anki noktanýnkinden daha büyük noktalara bakýyoruz. d mesafede
//en fazla 6 tane olacaðýndan içerdeki döngü her bir turda en fazla 6 kez dönüyor. 6 dan az sayýda ise daha az döner ama sonuçta sabit sayýda.
//Bir kere çýktý mý i artar yani ileriki tura geçeriz. Zaten çýktýysa d mesafesini aþtýk demektir çünkü sýraladýk. Yani bu kýsým O(n) oldu.

double close_strip_2(long long x[], long long y[], double d, long long left, long long right, long long mid){
	long long n = right-left+1, strip_x[n], strip_y[n], i, j=0;
	double min = d;
	
	for(i=left;i<=right;i++){
		if(llabs(x[mid] - x[i]) < d){
			strip_x[j] = x[i];
			strip_y[j] = y[i];
			j++;
		}
	}
	
	n = j;
	merge_sort(0, n-1, strip_y, strip_x);
	
	for(i=0;i<n-1;i++){
		j=i+1;
		while(j < n && strip_y[j] - strip_y[i] < min){
			d = dist(strip_x[j], strip_y[j], strip_x[i], strip_y[i]);
			if(min > d) min = d;
			j++;
		}
	}
	return min;
}

double close_strip(long long x[], long long y[], double d, long long left, long long right, long long mid){
	long long n = right-left+1, strip_x[n], strip_y[n], i, j=0;
	double min = d;
	
	for(i=left;i<=right;i++){
		if(llabs(x[mid] - x[i]) < d){
			strip_x[j] = x[i];
			strip_y[j] = y[i];
			j++;
		}
	}
	
	n = j;
	merge_sort(0, n-1, strip_y, strip_x);
	
	for(i=0;i<n;i++){
		for(j=1;j<7;j++){
			if(i+j < n && strip_y[i+j] - strip_y[i] < min){
				d = dist(strip_x[i+j], strip_y[i+j], strip_x[i], strip_y[i]);
				if(min > d) min = d;
			}
		}
	}
	return min;
}

double close(long long x[], long long y[], long long left, long long right){
	double d, d1, d2;
	long long mid;
	
	//base case
	if(right - left == 1) return dist(x[left], y[left], x[left+1], y[left+1]);
	if(right - left == 2){
		d = dist(x[left], y[left], x[left+1], y[left+1]);
		d1 = dist(x[left], y[left], x[left+2], y[left+2]);
		if(d > d1) d = d1;
		d1 = dist(x[left+1], y[left+1], x[left+2], y[left+2]);
		if(d > d1) d = d1;
		return d;
	}
	
	//divide
	mid = (right - left) / 2 + left;
	
	d1 = close(x, y, left, mid);
	d2 = close(x, y, mid+1, right);
	
	if(d1 > d2) d = d2;
	else d = d1;
	
	//combine
	d1 = close_strip(x, y, d, left, right, mid);
	if(d > d1) d = d1;

	return d;
}

int main(){
	long long x[100000], y[100000], n, i;

	scanf("%lld", &n);
	
	for(i=0;i<n;i++) scanf("%lld %lld", &x[i], &y[i]);
	
	merge_sort(0, n-1, x, y);
	
	printf("%.4lf", close(x, y, 0, n-1));
	
	return 0;
}
