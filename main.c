
//
#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

int bitmap[10][16] /* = {			   {
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0
	0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0

} */;

void disp(void)
{
	int row, col;

	for (row = 0; row < 10; ++row) {
		for (col = 0; col < 16; ++col)
			printf("%2d", bitmap[row][col]);
		printf("\n");
	}
}

void flood(int row, int col)
{
	if (row < 0 || row > 10 || col < 0 || col > 16)
		return;

	if (bitmap[row][col] == 0)
		return;
	// c object oriented bir dil olsaydı tam burdan her şekil için ayrı bir liste oluşturup o listeye eleman eklerdim. 
	bitmap[row][col] = 0;

	flood(row + 1, col);
	flood(row - 1, col);
	flood(row, col - 1);
	flood(row, col + 1);
}

int get_count(void)
{
	int row, col;
	int count = 0;

	for (row = 0; row < 10; ++row)
		for (col = 0; col < 16; ++col) {
			if (bitmap[row][col] == 1) {
				++count;
				flood(row, col);
			}
		}

	return count;
}

void read_bitmap(char location[50])
{
	FILE *f;
	int val;
	int i, k;

	if ((f = fopen(location, "r")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < 10; ++i) {
		for (k = 0; k < 16; ++k) {
			fscanf(f, "%d", &val);
			bitmap[i][k] = val;
		}
	}

	fclose(f);
}

int main(void)
{
	char location[50];
	printf("hos geldiniz lutfen dosyanin bulundugu lokasyonu giriniz "); 
	scanf("%s", location);
	read_bitmap(location);
	printf("Resimdeki sekil sayisi:");
	printf("%d\n", get_count());

	return 0;
}
