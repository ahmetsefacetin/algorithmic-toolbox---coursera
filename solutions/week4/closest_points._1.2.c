#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Ýki boyutta en yakýn iki noktayý bulma, O(nlogn): Kýsaca closest_points_1.1 den farkýný anlatýcam. 1.1'de strip, yani combine kýsmýnda 
elimizdeki x kordinatýna göre sýralý noktalardan x'göre medyan ile farkýnýn mutlak deðeri d den küçük olanlarý seçip bunlarý y kordinatýna
göre sýralýyoduk. Bundaki sebep x'e göre medyanla arasýnda d'den fazla mesafe varsa ölçmeye gerek olmadýðý ve eðer d'den az mesafe varsa da
y'ye göre sýralandýklarý takdirde her bir nokta için en fazla 6 aday nokta bulunma durumunu verimli þekilde kullanmaktý.  

Þimdi 1.2'deki asýl olay y kordinatýna göre sýralama olayýný yalnýzca main'de yapmanýn yeterli olmasý fikri. Bunu yapmak içinse bize verilen 
noktalardan bir çift daha saklamak ve bu ayriyeten sakladýðýmýz çifti mainde y kordinatýna göre sýralayýp close fonksiyonuna ayrýca göndermek
gerekli. Divide kýsmýnda 1.1 de olmayan bir subroutine var ve asýl can alýcý noktayý bu oluþturuyor. Burada y'ye göre sýralý x2 ve y2'yi left
ve right þeklinde bölüyoruz. Bunu yapmadaki amaç recursive çaðrýlara x1 ve y1'i left ve right diye bölerken ayný bölme iþlemini x2 ve y2 için
de yapmak istememiz. 

Bunu yapmadýðmýz takdirde ilk iki recursive çaðrýda sýkýntý olmaz çünkü combine dýþýndaki iþlemleri x2, y2'den baðýmsýz yapýyoruz ancak combine
kýsmýnda büyük bir sýkýntý çýkar. Çünkü x2, y2'dekiler y'ye göre sýralý olduðundan x1'in mid'inden küçüklerin hepsinin x2'de midin saðýnda 
olduðunu düþün. Yani bize verilen noktalarýn ilk yarýsý için yapacaðýmýz combine iþleminde strip dizisine noktalarýn ilk yarýsýndaki hiçbir
eleman yerleþemiycek. Olmasý gereken x2 ve y2'dekilerin x1'in midinden küçük eþit olanlarý bir diziye büyükleri bir diziye yerleþtirmek ve 
bu dizileri sýrasýyla left kýsým için yapýlan çaðrýya ve right kýsým için yapýlan çaðrýya göndermek. Bu ayýrma sonrasýnda x2 ler sýrasýz olucak
ama x1'in ayrýlmýþ kýsýmlarýyla ayný elemanlardan oluþacak.  

Ayrýca 1.1'den farklý olan iki küçük önemli kýsým var. Divide'daki 1.1'de olmayan subroutine'de i'yi leftden deðil 0'dan baþlatma sebebi
x2 ve y2'lerin her çaðrý sýrasýnda iki ayrý diziye ayrýlmýþ olmasý. Yani atýyorum x2_left 5 elemanlý, x2_right 4 elemanlý birer dizi oluyolar.
Mesela right kýsým için bir çaðrýdayýz left=4, right = 7 olsun x2 de gezerken 0-4 arasýnda gezmeliyiz. Diðer türlü dizi dýþýna çýkarýz.
Ayný sebeple combine kýsmýnda yani close_strip de de 1.1 den farklý olarak leftden deðil 0'dan baþlýyoruz.

Analysis: main de n uzunluðunda iki diziyi sýralamak sebebiyle O(nlogn) karmaþýklýk var. recursive baðýntý ise T(n) = 2T(n/2) + O(n). Çünkü her
çaðrýda O(n)'lik bir subroutine'imiz var ve çaðrýnýn combine kýsmýnda da O(n) lik bir iþlem yapýyoruz. Baðýntýdan karmaþýklýk O(nlogn) geliyor.
Yani toplam karmaþýklýk O(nlogn)...
 
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

double close_strip(long long x1[], long long y1[], long long x2[], long long y2[], double d, long long left, long long right, long long mid){
	long long n = right-left+1, strip_x[n], strip_y[n], i, j=0;
	double min = d;
	
	for(i=0;i<n;i++){
		if(llabs(x1[mid] - x2[i]) < d){
			strip_x[j] = x2[i];
			strip_y[j] = y2[i];
			j++;
		}
	}
	
	n = j;
	
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

double close(long long x1[], long long y1[], long long x2[], long long y2[], long long left, long long right){
	double d, d1, d2;
	long long mid, i, j, k, n = right - left + 1;
	long long x2_left[n], y2_left[n], x2_right[n], y2_right[n]; // y ye göre sýralý listedeki elemanlarý x1[mid] 'den büyük küçük olmasýna göre ayýrcaz 
	
	//base case
	if(right - left == 1) return dist(x1[left], y1[left], x1[left+1], y1[left+1]);
	if(right - left == 2){
		d = dist(x1[left], y1[left], x1[left+1], y1[left+1]);
		d1 = dist(x1[left], y1[left], x1[left+2], y1[left+2]);
		if(d > d1) d = d1;
		d1 = dist(x1[left+1], y1[left+1], x1[left+2], y1[left+2]);
		if(d > d1) d = d1;
		return d;
	}
	
	//divide
	mid = (right - left) / 2 + left;
	
	//subroutine - x2 ve y2'yi ayýrmak için
	j=0, k=0;
	for(i=0;i<n;i++){
		if(x2[i] <= x1[mid] && j < n/2){
			x2_left[j] = x2[i];
			y2_left[j] = y2[i];
			j++;
		}
		else{
			x2_right[k] = x2[i];
			y2_right[k] = y2[i];
			k++;
		}
	}
	
	d1 = close(x1, y1, x2_left, y2_left, left, mid);
	d2 = close(x1, y1, x2_right, y2_right, mid+1, right);
	
	if(d1 > d2) d = d2;
	else d = d1;
	
	//combine
	d1 = close_strip(x1, y1, x2, y2, d, left, right, mid);
	if(d > d1) d = d1;
	
	return d;
}

int main(){
	long long *x1, *y1, *x2, *y2, n, i;

	scanf("%lld", &n);
	
	x1 = (long long*) malloc(n*sizeof(long long));
	y1 = (long long*) malloc(n*sizeof(long long));
	x2 = (long long*) malloc(n*sizeof(long long));
	y2 = (long long*) malloc(n*sizeof(long long));
	
	for(i=0;i<n;i++){
		scanf("%lld %lld", &x1[i], &y1[i]);
		x2[i] = x1[i];
		y2[i] = y1[i];
	}
	
	merge_sort(0, n-1, x1, y1); //x lere göre sýralý
	merge_sort(0, n-1, y2, x2); //y lere göre sýralý
	
	printf("%.4lf", close(x1, y1, x2, y2, 0, n-1));
	
	return 0;
}
