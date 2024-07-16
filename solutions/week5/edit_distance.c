#include <stdio.h>

/*
minimum edit distance:
problem: Verilen iki stringin birincisinden ikincisini olu�turmak istiyoruz. Bunu yaparken minimum edit say�s�n� bulmak istiyoruz. Minimum 
operasyon say�s�n� veren ��z�m i�in e�er nicelik olarak ilk stringde olup ikincide olmayan bir harf varsa bunu ilkinden silmek i�in ilk 
stringin harfini alacaz ikincisininkini alm�ycaz (deletion). Veya tam tersi, nitelik olarak ikincide olan ve birincide olmayan bir
harf i�in ikincininkini al�p birincisi i�in bo�luk koyucaz, eksik harfi ifade edecek bu (insertion). Veya replace etmemiz gereken durum
olacak, bunda iki stringden de harf al�caz. (Bu i�lemlerin sonunda minimum operasyon say�s�n� verecek bir optimal alignment olu�acak) 

Proof and algorithm: elimizdeki iki string i�in optimum alignment yap�ld���nda son s�tunda ya iki stringin son harfleri ya ilk stringin son 
harfi ve bo�luk ya da ikinci stringin son harfi ve bo�luk olacak. �ki bo�luk olma �ans� yok. Yani son s�tun �ncesini bir sub problem olarak
d���n�rsen son s�tun �ncesi al�nan ceza art� bu �� durumdan hangisi minimumsa onun cezas� toplam� bize min cezay� verecek. P[i][j]'yi ilk 
stringin ilk i harfi ve ikinci stringin ilk j harfi i�in yap�lan optimal alignment i�in minimum maliyet olarak tan�mlans�n. i ve j deki 
harfler i�in yukarda bahsetti�im gibi olu�abilecek 3 durum var. Bu �� durum sonunda olu�abilecek 3 farkl� maliyeti yazal�m:

1- Birincinin i'sini al�p ikincinin j'sini almazsak P[i][j] = P[i][j-1] + (gap penalty) olur.
2- Birincinin i'sini almay�p ikincinin j'sini al�rsak P[i][j] = P[i-1][j] + (gap penalty) olur. 
3a- �kisini de al�r�z ama mismatch varsa P[i][j] = P[i-1][j-1] + (mismatch penalty) olur. 
3b- �kisini de al�r�z ama mismatch yoksa P[i][j] = P[i-1][j-1] olur. 

E�er match varsa 1, 2 ve 3b'den minimum olan P[i][j]'ye atan�r. match yoksa 1, 2 ve 3a'dan minimumu P[i][j]'ye atan�r. 
��te burada dynamic programming'in g�zelli�i ortaya ��k�yor. P'yi iki boyutlu bir matris olarak olu�turursal ve i� i�e iki for yaparsak i�lem
tamam. ��nk� her hal�karda i�eri girdi�imizde daha �nceki iterasyonlarda hesaplad���m�z de�erlerle kar��la�t�rma yap�caz.

Analysis: O(n*m)
*/

long long min(long long x, long long y, long long z){
	long long min = x;
	if(min > y) min = y;
	if(min > z) min = z;
	return min;
}

long long edit_dist(long long n, char* str1, long long m, char* str2){
	long long i, j, dist[n+1][m+1];
	
	for(i=0;i<=n;i++) dist[i][0] = i;
	for(i=0;i<=m;i++) dist[0][i] = i;
	
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(str1[i-1] == str2[j-1]){
				dist[i][j] = min(dist[i][j-1] + 1, dist[i-1][j] + 1, dist[i-1][j-1]);
			}
			else{
				dist[i][j] = min(dist[i][j-1] + 1, dist[i-1][j] + 1, dist[i-1][j-1] + 1);
			}
		}
	}
	
	return dist[n][m];
}

int main(){
	long long n, m;
	char str1[100], str2[100];
	
	scanf("%s", str1);
	scanf("%s", str2);
	
	while(str1[n++]);
	while(str2[m++]);
	
	printf("%lld", edit_dist(n-1, str1, m-1, str2));
	
	return 0;
}
