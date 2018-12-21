#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	
	FILE * fp;
	FILE * fp2;
	char url[1][12] = {"teste.txt"};
	char var[1] = {' '};
	int i=0;
	char p;
	int val;

	if (argc != 1) return 1;

	fp = fopen (url[i], "r");
	if (fp == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	else {
		fscanf(fp,"%c",&p);
		while (p != var[i]){
			fscanf(fp,"%c",&p);
		}
		fscanf(fp,"%c",&p);
		if (p == 'F') val = 0;			
			else val = 1;
	}
	fclose(fp);
	return val;
}
