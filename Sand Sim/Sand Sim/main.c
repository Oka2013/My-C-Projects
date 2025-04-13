// Delay harici ben yazdým
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* patlas = " .";

struct BMatrix {
	bool** vals;
	size_t ysize;
	size_t xsize;
};

struct BMatrix* matnew(size_t ysize, size_t xsize) {
	struct BMatrix* nmat = (struct BMatrix*)malloc(sizeof(struct BMatrix));

	nmat->ysize = ysize;
	nmat->xsize = xsize;

	nmat->vals = (bool**)calloc(ysize, sizeof(bool*));
	for (int i = 0; i < ysize; i++) {
		nmat->vals[i] = (bool*)calloc(xsize, sizeof(bool));
	}

	return nmat;
}

void matdel(struct BMatrix* mat) {
	for (int i = 0; i < mat->ysize; i++) {
		free(mat->vals[i]);
	}
	free(mat->vals);
	free(mat);
}

bool* fmovab(struct BMatrix* mat, int i, int j) {
	bool cit = mat->vals[i][j];
	bool* movab = (bool*)calloc(3, sizeof(bool));

	movab[1] = cit && !mat->vals[i + 1][j];
	movab[0] = j > 0 ? cit && !mat->vals[i + 1][j - 1] : 0;
	movab[2] = j < mat->xsize - 1 ? cit && !mat->vals[i + 1][j + 1] : 0;

	return movab;
}

void logic1(struct BMatrix* mat, int i, int j) {
	int dir;
	bool* movab = fmovab(mat, i, j);

	if (movab[1]) { dir = 0; }
	else { dir = rand() % 2 * 2 - 1; }

	if (!movab[dir + 1]) {
		if (!movab[2 - dir - 1]) { return; }
		else { dir = 2 - dir - 1; }
	}

	mat->vals[i][j] = 0;
	mat->vals[i + 1][j + dir] = 1;
}

void logic(struct BMatrix* mat) {
	for (int i = (int)mat->ysize - 2; i > -1; i--) {
		for (int j = 0; j < mat->xsize; j++) {
			logic1(mat, i, j);
		}
	}
}

void matprint(struct BMatrix* mat) {
	for (int i = 0; i < mat->ysize; i++) {
		for (int j = 0; j < mat->xsize; j++) {
			printf("%c ", patlas[mat->vals[i][j]]);
		}
		printf("\n");
	}
}

void delay(unsigned int ms) {
	clock_t sc = clock();
	while (clock() < sc + ms);
}

int main() {
	srand(time(NULL));
	struct BMatrix* mat = matnew(10, 10);

	for (int i = 0; i < 100; i++) {
		mat->vals[0][rand() % 10] = 1;

		logic(mat);
		matprint(mat);
		printf("------------------------------------------\n");

		delay(50);
	}

	return 0;
}