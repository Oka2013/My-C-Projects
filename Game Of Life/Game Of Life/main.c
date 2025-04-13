#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Matrix {
	bool** vals;
	size_t xsize;
	size_t ysize;
};

struct Matrix* new_matrix(size_t xsize, size_t ysize) {
	struct Matrix* nmatrix = (struct Matrix*)calloc(1, sizeof(struct Matrix));

	nmatrix->xsize = xsize;
	nmatrix->ysize = ysize;

	nmatrix->vals = (bool**)calloc(ysize, sizeof(bool*));

	for (int i = 0; i < ysize; i++) {
		nmatrix->vals[i] = (bool*)calloc(xsize, sizeof(bool));
	}

	return nmatrix;
}

int adj_count(struct Matrix* matrix, int xid, int yid) {
	int ret = 0;

	bool ml = xid > 0;
	bool mr = xid < matrix->xsize - 1;
	bool md = yid > 0;
	bool mu = yid < matrix->ysize - 1;

	ret += ml ? matrix->vals[xid - 1][yid] : 0;
	ret += mr ? matrix->vals[xid + 1][yid] : 0;
	ret += md ? matrix->vals[xid][yid - 1] : 0;
	ret += mu ? matrix->vals[xid][yid + 1] : 0;
	ret += ml && md ? matrix->vals[xid - 1][yid - 1] : 0;
	ret += ml && mu ? matrix->vals[xid - 1][yid + 1] : 0;
	ret += mr && md ? matrix->vals[xid + 1][yid - 1] : 0;
	ret += mr && mu ? matrix->vals[xid + 1][yid + 1] : 0;

	return ret;
}

struct Matrix* apply_algo(struct Matrix* matrix) {
	int tadj;
	bool tval;
	struct Matrix* nmatrix = new_matrix(matrix->xsize, matrix->ysize);

	for (int i = 0; i < matrix->ysize; i++) {
		for (int j = 0; j < matrix->xsize; j++) {
			tval = matrix->vals[i][j];
			tadj = adj_count(matrix, i, j);

			nmatrix->vals[i][j] = tadj > (!tval + 1) && tadj < 4;
		}
	}

	return nmatrix;
}

void matdel(struct Matrix* matrix) {
	int i = 0;
	while (i < matrix->ysize) {free(matrix->vals[i++]);}
	free(matrix->vals);
	free(matrix);
}

void print_mat(struct Matrix* matrix) {
	for (int i = 0; i < matrix->ysize; i++) {
		for (int j = 0; j < matrix->xsize; j++) {
			printf("%d ", matrix->vals[i][j]);
		}
		printf("\n");
	}
}

int main() {
	struct Matrix* matrix = new_matrix(100, 100);
	struct Matrix* tmatrix;

	matrix->vals[0][1] = 1;
	matrix->vals[1][2] = 1;
	matrix->vals[2][0] = 1;
	matrix->vals[2][1] = 1;
	matrix->vals[2][2] = 1;

	for (int i = 0; i < 10; i++) {
		tmatrix = apply_algo(matrix);
		matdel(matrix);
		matrix = tmatrix;

		print_mat(matrix);
		printf("------------------------------------------------------------------------\n");
	}
}