#include <stdio.h>

/*
Problem: her bir itemdan yalnýzca bir defa kullanma iznimiz var. with ile ayný onun dýþýnda... 

with'deki algonun burada patlama sebebi: o algoda her bir aðýrlýk için her bir item'ý gezip W - wi optimal çözümüne i'yi ekleyip hangi i için 
bu durum max ona bakýyoduk. Ancak bunu yaparken W - wi optimal çözümünde i. item kullanýlmýþ mý bilemeyiz. 

Algorithm: with'deki algo bunda patladýðýndan sýfýrdan yine bir dp algo geliþtirme için genel yaklaþýmý kullanýcaz, yani son ürünü inceleyip
önceki hesaplamalarla olan baðlantýsýna bakýcaz.

Son üründe yani çýktýda bulunan itemlara S kümesi diyelim. Bu küme bize verilen W sýnýrýný aþmayan en deðerli çözüm. Þimdi bu kümede bize 
verilen itemlardan sonuncusunun yani n. bulunmadýðýný varsay: Bu demektir ki S kümesi, n itemýn da gözden geçirilip n. haricinde n-1'i 
kullanýlarak W aðýrlýðý için optimal çözümdür. Þimdi varsayalým ki n. yani son item, S kümesinde var: n. itemýn aðýrlýðýna wn dersek, bu 
demektir ki W - wn aðýrlýðý için optimal çözüm S - {n}'dir. Bunun contradiction ile ispatýný with repetitions için yaptým. Gördüðün gibi 
optimal çözüm için yalnýzca iki ihtimal var. Bu ihtimallerden hangisi daha iyiyse optimal çözüm odur.

Þimdi bu çýkarýmýmýzý genelliycez. Bunun için bir gösterime ihtiyaç var: V[i][x]; ilk i item gözden geçirilip, x aðýrlýðý için optimal value'yu
ifade etsin. Yukardaki çýkarýma göre V[i][x]; i dahil deðilse V[i-1][x], i dahilse V[i-1][x - wi] + vi ikilisinden hangisi daha optimalse, 
büyükse ona eþit. i'nin dahil olduðu durumdaki V[i-1][x - wi], daha önce hesapladýðýmýz x - wi aðýrlýðýndaki optimal çözüm. Yani onun üstüne wi 
aðýrlýðýndaki vi deðerindeki i'yi koyarak x aðýrlýðý için optimal çözüm bu mu yoksa daha önceden i. item öncesindeki i-1 item kullanarak 
hesapladýðýmýz V[i-1][x] mi diye bakýcaz.

Aslýnda gösterimden matrix kullanýcamýz belli, ama nasýl kullanýcaz: matrisin satýrý o anki x aðýrlýðýnýn çözümü için kullanýlan eleman sayýsýný
tutuyor. Mesela i = 0 ken hiç eleman olmadýðýndan tüm x'ler 0. Sütunlar ise her bir x'i tutuyor. with'deki çözümün tersine bunda dýþarda item
için olan döngü varken içerde aðýrlýklar için olan döngü var. Sebebi çok basit: ilk i elemaný kullanarak her bir aðýrlýk için optimal çözümü 
buluyoruz. Bu sayede ayný elemandan iki kez kullanýlmadýðýndan emin oluyoruz. Ayrýca genellediðimiz çözümde ilk i-1 item kullanýlan çözüme 
bakýyoruz, yani bir önceki row önemli. O rowun tamamen hesaplanmýþ olmasý lazým.

Bahsettiðim iki ihtimali örneklemek gerekirse mesela w = {1,3,4,5} olsun. W = 8 için, son item'a geldiðimizde ya 1 + 3 + 4 = 8'lik çözümü ya da
(8 - 5) + 5 = 8'lik çözümü kullanýcaz. (itemlar sýralý olmak zorunda deðil görmesi kolay olsun diye sýralý verdim.

Analysis: dýþardaki döngüdeki toplam n kez olan her bir tur için içerde W kadar dönüyoruz ve içerde sabit iþ yapýyoruz. Yani O(n*W)... 
(Deðilmiþ. üstelmiþ. stackoverdan bak...)
*/

long long without_r(long long n, long long* v, long long* w, long long W){
	long long i, j; 
	long long arr[n+1][W+1]; //satýrlar current W için kullanýlan item sayýsýný, sütunlar her bir W'yu tutuyor.
	
	for(i=0;i<=W;i++) arr[0][i] = 0; //hiç item kullanmazsak her bir W için value 0 olur.
	for(i=0;i<=n;i++) arr[i][0] = 0; //kapasite 0'sa item sayýsýndan baðýmsýz sonuç 0 olur.
	
	for(i=1;i<=n;i++){
		for(j=1;j<=W;j++){
			arr[i][j] = arr[i-1][j]; //1. ihtimal, i'nin kullanýlmadýðý
			if(j >= w[i-1] && arr[i-1][j - w[i-1]] + v[i-1] > arr[i][j]){ //2. ihtimal, i'nin kullanýldýðý
				arr[i][j] = arr[i-1][j - w[i-1]] + v[i-1];
			}
		}
	}
	
	//reconstruction: çözümde kullanýlan itemlarýn indexlerini yazdýrmak için (backtracking technic)
	j = W;
	for(i=n;i>=0;i--){
		if(j >= w[i-1] && arr[i][j] == arr[i-1][j - w[i-1]] + v[i-1]){
			printf("%lld ", i-1);
			j -= w[i-1];
		}
	}
	
	return arr[n][W]; // n item'ýn da gözden geçirildiði W aðýrlýðýndaki optimal çözüm
}

/*
space optimized version of without repetitions: Bunda O(W)'lik bir yer karmaþýklýðý var. trick þu: yukardaki algoda göreceðin gibi dýþtaki 
döngünün her turunda yalnýzca bir üstteki rowla ilgileniyoruz. Bu sebeple yalnýzca tek row tutmak yeterli, W+1 tane de sütun olacak. Ýlk baþta 
tüm diziyi 0'a eþitliycez, bu hiç item kullanmadýðýmýz durumu gösteriyor. Sonrasýnda yalnýzca ilk itemý kullanarak hiç item kullanmadýðýmýz 
duruma göre güncelleme yapýyoruz. Sonra bu tur bitip ikinci itema geçince birinci itemýn kullanýmýna göre þekillenen dizide ikinci itema göre 
güncelleme yapýcaz... 

Ayrýca bunu sürdürebilmek için j'yi Wdan baþlatýp azaltarak gidicez. Bundaki sebep, bir tura baþladýðýmýzda önceki turdaki dizide güncelleme
yaptýðýmýzdan eðer 0 dan baþlayýp artýrýrsak sonraki j'lerde yeni itema göre güncellediðimiz bir indexi kullanmýþ olucaz. Yani ayný elemandan
birden fazla kez kullanmýþ olucaz. Ama j'yi azaltarak gidersek her baktýðýmýz index önceki turdaki index olacak.  
*/

long long without_r1(long long n, long long* v, long long* w, long long W){
	long long i, j; 
	long long arr[W+1]; 
	
	for(i=0;i<=W;i++) arr[i] = 0;
	
	for(i=0;i<n;i++){
		for(j=W;j>=0;j--){
			if(j >= w[i] && arr[j - w[i]] + v[i] > arr[j]){
				arr[j] = arr[j - w[i]] + v[i];
			}
		}
	}
	
	return arr[W];
}

int main(){
	long long n = 4, v[100] = {30,14,16,9}, w[100] = {6,3,4,2}, W = 10, i;
	
//	scanf("%lld", &W);
//	
//	scanf("%lld", &n);
//	
//	for(i=0;i<n;i++) scanf("%lld %lld", &w[i], &v[i]);
	
	printf("\n%lld", without_r1(n, v, w, W));
	
	return 0;
}
