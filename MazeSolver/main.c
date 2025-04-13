#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct BMatrix {
	bool** vals;
	size_t ysize;
	size_t xsize;
};

struct Int2 {
	int y;
	int x;
};

struct Int2* int2new(int y, int x) {
	struct Int2* nint2 = (struct Int2*)malloc(sizeof(struct Int2));

	nint2->x = x;
	nint2->y = y;
}

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

struct BMatrix* matcopy(struct BMatrix* mat) {
	struct BMatrix* rmat = matnew(mat->ysize, mat->xsize);

	for (int i = 0; i < mat->ysize; i++) {
		memcpy(rmat->vals[i], mat->vals[i], sizeof(mat->vals[i]));
	}

	return rmat;
}

void matprint(struct BMatrix* mat) {
	for (int i = 0; i < mat->ysize; i++) {
		for (int j = 0; j < mat->xsize; j++) {
			printf("%d ", mat->vals[i][j]);
		}
		printf("\n");
	}
}

struct Int2** matbfs(struct BMatrix* mat, struct Int2* start, struct Int2* end) {
	struct Int2** ret = (struct Int2**)calloc(mat->xsize * mat->ysize, sizeof(struct Int2*));
	struct Int2** queu = (struct Int2**)calloc(mat->xsize * mat->ysize, sizeof(struct Int2*));
	int* roots = (int*)calloc(mat->xsize * mat->ysize, sizeof(int));
	struct Int2* ncp;
	struct Int2* cp;

	struct BMatrix* visited = matcopy(mat);

	unsigned int rid = 0, wid = 0;
	queu[wid] = end;
	roots[wid++] = -1;
	visited->vals[end->y][end->x] = 1;

	while (wid > rid) {
		cp = queu[rid++];
		visited->vals[cp->y][cp->x] = 1;

		if (cp->y == start->y && cp->x == start->x) {
			rid--;
			for (int i = 0; rid + 1; i++) {
				ret[i] = queu[rid];
				rid = roots[rid];
			}
			break;
		}

		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				ncp = (struct Int2*)malloc(sizeof(struct Int2));
				ncp->y = cp->y + i * (cp->y + i < mat->ysize && cp->y + i > -1);
				ncp->x = cp->x + j * (cp->x + j < mat->xsize && cp->x + j > -1);

				if (visited->vals[ncp->y][ncp->x]) {
					continue;
				}

				queu[wid] = ncp;
				roots[wid++] = rid - 1;
				visited->vals[ncp->y][ncp->x] = 1;
			}
		}
	}

	return ret;
}

void delay(unsigned int ms) {
	clock_t sc = clock();
	while (clock() < sc + ms);
}

int main() {
	struct BMatrix* mat = matnew(3, 3);
	mat->vals[0][1] = 1;
	mat->vals[1][1] = 1;

	struct Int2* start = (struct Int2*)malloc(sizeof(struct Int2));
	start->y = 0;
	start->x = 0;

	struct Int2* end = (struct Int2*)malloc(sizeof(struct Int2));
	end->y = 2;
	end->x = 2;

	struct Int2** steps = matbfs(mat, start, end);

	for (int i = 0; i < 4; i++) {
		printf("%d %d\n", steps[i]->y, steps[i]->x);
	}

	return 0;
}