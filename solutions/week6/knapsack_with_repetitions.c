#include <stdio.h>

/*
Herhangi bir problem için bir dp algoritma geliþtirmek için problemin çözülmüþ, yani optimal hali için yorum yapmak lazým. Çünkü herhangi 
bir dp algosunun her adýmýnda optimal hali elde etmek için önceden hesapladýðýmýz optimal halleri kullanýcaz. Mesela bu problemin çözümü 
için þunu düþünmelisin: 

W üst sýnýrýný aþmayan bir aðýrlýða sahip olabilecek maksimum deðerde, yani optimal bir çözüm var elimizde. Þimdi ben bu çözümün içinde nicelik
olarak en az bir tane olan bir parçadan bir adet çýkarayým. Bu parçanýn aðýrlýðý w[i] olsun. Dönüm noktasýna geldik. Kalan aðýrlýk, yani
W - w[i], bu aðýrlýk için optimal çözümdür. Olmadýðýný düþünelim: W - w[i] aðýrlýðýnda daha büyük deðerde bir çözüm varsa ve bu çözüme W 
aðýrlýðý için optimal çözüm varsaydýðýmýz çözümden çýkardýðýmýz parçayý koyarsak W aðýrlýkta optimal varsaydýðýmýz çözümden daha büyük deðerde
bir çözüm elde ederiz. Ýþte bu çeliþki yaratýr. Çünkü baþtaki W aðýrlýktaki çözümün optimal olduðunu kabul ettik. Anlayacaðýn gibi her bir yeni
aðýrlýðýn optimal çözümü için önceden hesapladýðmýz aðýrlýklarýn optimal çözümlerini kullanýcaz. Yani þöyle bir genel formül yazabiliriz: 
value(W) = value(W - w[i]) + v[i]. Aðýrlýðý W'dan büyük olmayan her item için bu iþlemi yapýp max olaný value(W)'e atýycaz. 
  
Analysis: W'ya kadar her bir aðýrlýk için optimal çözümü bulucaz. bunun için dýþ döngüde W kadar döneriz. Her bir value(W) için item sayýsý, n, 
kadar tur atýp value(W - w[i]) + v[i] 'nin max olanýný value(W)'ya atýycaz. Yani O(n*W)... (Deðilmiþ. üstelmiþ. stackoverdan bak...)
*/

long long with_r(long long n, long long* v, long long* w, long long W){
	long long arr[W+1], i, j, max;
	arr[0] = 0;
	
	for(i=1;i<=W;i++){
		arr[i] = 0;
		for(j=0;j<n;j++){
			if(i >= w[j]){
				max = arr[i - w[j]] + v[j];
				if(max > arr[i]) arr[i] = max;
			}
		}
	}
	for(i=0;i<=W;i++) printf("%lld ", arr[i]);
	return arr[W];
}

int main(){
	long long n = 4, v[100] = {30,14,16,9}, w[100] = {6,3,4,2}, W = 10, i;
	
//	scanf("%lld", &W);
//	
//	scanf("%lld", &n);
//	
//	for(i=0;i<n;i++) scanf("%lld %lld", &w[i], &v[i]);
	
	printf("\n%lld", with_r(n, v, w, W));
	
	return 0;
}
