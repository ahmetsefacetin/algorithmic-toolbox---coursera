#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long min(long long x, long long y, long long z){
	long long min = x;
	if(min > y) min = y;
	if(min > z) min = z;
	return min;
}

long long max(long long x, long long y, long long z){
	long long max = x;
	if(max < y) max = y;
	if(max < z) max = z;
	return max;
}

//sorunlu
void reconstruct_alignment(long long dist[][100], long long n, char* str1, long long m, char* str2){
	char alignment1[n+m+1], alignment2[n+m+1];
	long long i = n, j = m, index = 0;
	
	while(i > 0 || j > 0){
		if(i > 0 && dist[i][j] == dist[i-1][j] + 1){
			alignment1[index] = str1[i-1];
			alignment2[index] = '-';
			i--;
		}
		else if(j > 0 && dist[i][j] == dist[i][j-1] + 1){
			alignment1[index] = '-';
			alignment2[index] = str2[j-1];
			j--;
		}
		else{
			alignment1[index] = str1[i-1];
			alignment2[index] = str2[j-1];
			i--;
			j--;
		}
		index++;
	}
	
	alignment1[index] = '\0';
	alignment2[index] = '\0';
	
	strrev(alignment1);
	strrev(alignment2);
	
	printf("%s\n", alignment1);
	printf("%s\n", alignment2);
}

/*
minimum edit distance:
problem: Verilen iki stringin birincisinden ikincisini oluþturmak istiyoruz. Bunu yaparken minimum edit sayýsýný bulmak istiyoruz. Minimum 
operasyon sayýsýný veren çözüm için eðer nicelik olarak ilk stringde olup ikincide olmayan bir harf varsa bunu ilkinden silmek için ilk 
stringin harfini alacaz ikincisininkini almýycaz (deletion). Veya tam tersi, nitelik olarak ikincide olan ve birincide olmayan bir
harf için ikincininkini alýp birincisi için boþluk koyucaz, eksik harfi ifade edecek bu (insertion). Veya replace etmemiz gereken durum
olacak, bunda iki stringden de harf alýcaz. (Bu iþlemlerin sonunda minimum operasyon sayýsýný verecek bir optimal alignment oluþacak) 

Proof and algorithm: elimizdeki iki string için optimum alignment yapýldýðýnda son sütunda ya iki stringin son harfleri ya ilk stringin son 
harfi ve boþluk ya da ikinci stringin son harfi ve boþluk olacak. Ýki boþluk olma þansý yok. Yani son sütun öncesini bir sub problem olarak
düþünürsen son sütun öncesi alýnan ceza artý bu üç durumdan hangisi minimumsa onun cezasý toplamý bize min cezayý verecek. P[i][j]'yi ilk 
stringin ilk i harfi ve ikinci stringin ilk j harfi için yapýlan optimal alignment için minimum maliyet olarak tanýmlansýn. i ve j deki 
harfler için yukarda bahsettiðim gibi oluþabilecek 3 durum var. Bu üç durum sonunda oluþabilecek 3 farklý maliyeti yazalým:

1- Birincinin i'sini alýp ikincinin j'sini almazsak P[i][j] = P[i][j-1] + (gap penalty) olur.
2- Birincinin i'sini almayýp ikincinin j'sini alýrsak P[i][j] = P[i-1][j] + (gap penalty) olur. 
3a- Ýkisini de alýrýz ama mismatch varsa P[i][j] = P[i-1][j-1] + (mismatch penalty) olur. 
3b- Ýkisini de alýrýz ama mismatch yoksa P[i][j] = P[i-1][j-1] olur. 

Eðer match varsa 1, 2 ve 3b'den minimum olan P[i][j]'ye atanýr. match yoksa 1, 2 ve 3a'dan minimumu P[i][j]'ye atanýr. 
Ýþte burada dynamic programming'in güzelliði ortaya çýkýyor. P'yi iki boyutlu bir matris olarak oluþturursal ve iç içe iki for yaparsak iþlem
tamam. Çünkü her halükarda içeri girdiðimizde daha önceki iterasyonlarda hesapladýðýmýz deðerlerle karþýlaþtýrma yapýcaz.

Analysis: O(n*m)
*/

long long edit_dist(long long n, char* str1, long long m, char* str2){
	long long i, j, dist[n+1][m+1];
	
	for(i=0;i<=n;i++) dist[i][0] = i; //diðer string boþ olduðundan her türlü diðer stringdeki harf sayýsý kadar insertion/deletion olacak.
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
	reconstruct_alignment(dist, n, str1, m, str2);
	
	return dist[n][m];
}

//minimum penalty: gap penalty = 1, mismatch penalty = 1, Gördüðün gibi edit distance'ýn týpatýp aynýsý, Sadece insertion ve deletion için bir
//gap penalty ve replace için bir mismatch penalty deðiþkeni var
long long minimum_penalty(long long n, char* str1, long long m, long long *str2, long long gp, long long mp){
	long long i, j, dist[n+1][m+1];
	
	for(i=0;i<=n;i++) dist[i][0] = i * gp;
	for(i=0;i<=m;i++) dist[0][i] = i * gp;
	
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(str1[i-1] == str2[j-1]){
				dist[i][j] = min(dist[i][j-1] + gp, dist[i-1][j] + gp, dist[i-1][j-1]);
			}
			else{
				dist[i][j] = min(dist[i][j-1] + gp, dist[i-1][j] + gp, dist[i-1][j-1] + mp);
			}
		}
	}
	
	return dist[n][m];
}

//longest common subsequence
//edit distance'dan farký: bunda max uzunluðu elde etmeye çalýþtýðýmýzdan gap sonucunda ve mismatch'da biþey eklemiyoruz, match sýrasýnda +1 
//ekliyoruz ve bunlar arasýnda max'a bakýyoruz. 

long long lcs(long long n, char* str1, long long m, char* str2){
	long long i, j, dist[n+1][m+1];
	
	for(i=0;i<=n;i++) dist[i][0] = 0;
	for(i=0;i<=m;i++) dist[0][i] = 0;
	
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(str1[i-1] == str2[j-1]){
				dist[i][j] = max(dist[i][j-1], dist[i-1][j], dist[i-1][j-1] + 1);			
			}
			else{
				dist[i][j] = max(dist[i][j-1], dist[i-1][j], dist[i-1][j-1]);	
			}
		}
	}
	
	return dist[n][m];
}

int main(){
	long long n, m;
	char *str1, *str2;
	
	printf("length of first string: ");
	scanf("%lld", &n);
	str1 = (char*) malloc((n+1)*sizeof(char));
	printf("first string: ");
	scanf("%s", str1);
	
	printf("length of second string: ");
	scanf("%lld", &m);
	str2 = (char*) malloc((m+1)*sizeof(char));
	printf("second string: ");
	scanf("%s", str2);
	
	printf("\nminimum edit distance: %lld", edit_dist(n, str1, m, str2));
	
	printf("\nlongest common subsequence: %lld", lcs(n, str1, m, str2));
	
	return 0;
}
