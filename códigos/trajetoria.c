#define DIM 2		// dimensão do espaço
#define n 2
#define p 10
#define J_i 2

int nondet_int();
int x [n][3];		// variáveis a serem definidas para minimizar a função objetivo
int Pi [DIM] = {0, 0};	// ponto inicial
int Pf [DIM] = {1, 1};	// ponto final

double eps = 0.0;
double delta = 0.25;

// valor absoluto
double abs (double val) {
	if (val < 0) return -val;
	else return val;
}

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
			if ( abs( diff ) <= min_tol ) flag = 1;
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

// restrições para desviar obstáculos circulares
void rest_pontos (int P1 [DIM], int i, double x0, double y0, double r) {
	double lambda = delta;
	while (lambda < 1.0) {
		__ESBMC_assume ( ((((1.0-lambda)*P1[0] + lambda*x[i][0]) - x0)*(((1.0-lambda)*P1[0] + lambda*x[i][0]) - x0) + (((1.0-lambda)*P1[1] + lambda*x[i][1]) - y0)*(((1.0-lambda)*P1[1] + lambda*x[i][1]) - y0)) > (r + eps)*(r + eps) );
		lambda = lambda + delta;
	}
}

// código principal
int main() {
	int i, j;
	int A [DIM], B [DIM];
	for (j=0; j<DIM; j++){
		A[j] = Pi[j]*p;
		B[j] = Pf[j]*p;
	}

	// variáveis a modificadas a cada execução do código para aumentar a precisão
	// limites das coordenadas (x,y)
	int lim [DIM][2] = { 0*p, 1*p, 0*p, 1*p};

	// declaração dos estados, coordenadas x=x[i][0] e y=x[i][1] como não-determinísticos
	for (i=0; i<n; i++)
		for(j=0; j<DIM; j++)
			x[i][j] = nondet_int();

	// restrições dos limites das coordenadas
	for (i=0; i<n; i++) {
		__ESBMC_assume ( (x[i][0] >= lim[0][0]) && (x[i][0] <= lim[0][1]) );
		__ESBMC_assume ( (x[i][1] >= lim[1][0]) && (x[i][1] <= lim[1][1]) );
	}

	// garante que nenhum ponto gerado seja repetido e
	// os obstáculos não sejam violadas por segmentos de retas formados por dois pontos concecutivos
	__ESBMC_assume ( (x[0][0] != A[0]) || (x[0][1] != A[1]) );
	rest_pontos (A, 0, 0.5*p, 0.5*p, 0.3*p);

	for (i=1; i<n; i++) {
		__ESBMC_assume ( (x[i][0] != x[i-1][0]) || (x[i][1] != x[i-1][1]) );
		rest_pontos (x[i-1], i, 0.5*p, 0.5*p, 0.3*p);
	}

	__ESBMC_assume ( (x[n-1][0] != B[0]) || (x[n-1][1] != B[1]) );
	rest_pontos (B, n-1, 0.5*p, 0.5*p, 0.3*p);

	// cálculo da função de custo
	double J = 0.0;
	double Aux1[DIM];
	double Aux2[DIM];

	for (j=0; j<DIM; j++)	
		Aux1[j] = A[j]/p;
	for (i=0; i<n; i++) {
		for (j=0; j<DIM; j++)
			Aux2[j] = (double) x[i][j]/p;
		J = J + dist(Aux1,Aux2);
		for (j=0; j<DIM; j++)
			Aux1[j] = Aux2[j];
	}
	for (j=0; j<DIM; j++)
		Aux2[j] = B[j]/p;
	J = J + dist(Aux1,Aux2);
	
	// restrição para excluir estados onde J>=J_i
	__ESBMC_assume ( J < J_i );

	assert ( J > J_i );
	return 0;
}
