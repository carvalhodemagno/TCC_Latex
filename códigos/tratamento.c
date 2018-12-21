#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DIM 2			// dimensão do espaço

double A [DIM] = {0, 0};	// ponto inicial
double B [DIM] = {1, 1};	// ponto final

// cálculo raiz quadrada
double raiz (double val) {
	double r = val/10;
	double dx;
	double diff;
	double min_tol = 0.00001;
	int i, flag = 0;
	if ( val == 0 ) r = 0;
	else {
		for (i = 0; i < 20; ++i)
	        if (!flag) {
			dx = ( val - ( r*r ) ) / ( 2.0*r );
			r = r + dx;
			diff = val - ( r*r );
			if ( fabs( diff ) <= min_tol ) flag = 1;
		}
		else r = r;
	}
	return r;
}

// cálculo distância euclidiana entre dois pontos
double dist (double P1 [DIM], double P2 [DIM]) {
	double d = 0.0;
	for (int i=0; i<DIM; i++) {
		d = d + ( (P1[i]-P2[i]) * (P1[i]-P2[i]) );
	}
	return raiz (d);
}

int main(int argc, char *argv[]) {
	FILE * fp;
	FILE * fp2;
	char aux;
	char p[100];

	int prec;
	int n;
	if (argc != 3) return 1;
	sscanf(argv[1], "%d", &prec);
	sscanf(argv[2], "%d", &n);
	
	int k = 0, x = 2, i, j;
	while (x < n){
		x = x*2;
	}

	double L[n][DIM];

	fp2 = fopen("output.txt","w+");
	if (fp2==NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
		return 0;				
	}	
	fp = fopen ("x.txt", "r");
	if (fp == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
		fclose(fp2);
		return 0;
	}
	else {
		fscanf(fp,"%c",&aux);
		while (aux != '{'){
			fscanf(fp,"%c",&aux);
		}
		for (i = 0; i < 2*x; i++){
			fscanf(fp,"%s",&p);
			p[(strlen(p)-1)] = '\0';
			if (i < x){
				if (k < n){
					L[k][0] = atof(p)/prec;
					fprintf(fp2,"%.3f\n",L[k][0]);
					k++;
				}
			}
			else {
				if (k < 2*n){
					L[k-n][1] = atof(p)/prec;
					fprintf(fp2,"%.3f\n",L[k-n][1]);
					k++;
				}
			}
		}
	}
	fclose(fp);
		
	// cálculo da função de custo
	double C[DIM];
	double J = 0.0;
	for (i=0; i<n; i++) {
		for (j=0; j<DIM; j++)
			C[j] = L[i][j];
		J = J + dist(A,C);
		for (j=0; j<DIM; j++)
			A[j] = L[i][j];
	}
	J = J + dist(C,B) - 0.001;
	fprintf(fp2,"%.5f\n",J);
	fclose(fp2);
	return 0;
}
