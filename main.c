#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

#define THRESHOLD 0.5

// LATER change this so that each 'bool' is sizeof float
// then I can just & nv with row of matrix to get dot product in one operation
// very clever hmmm
#define bool int
#define false 0
#define true 1

// size of neuron vector
#define NV_SIZE 10
// number of connections in each layer: this defines the size of the next neuron vector
#define A_I NV_SIZE
// A_I and A_II (same size)
#define A_II A_I

typedef struct conn_matrix {
        int m;
        int n;
	float arr[NV_SIZE * A_I];
} conn_matrix;

typedef struct neuron_v {
        int l;
	bool v[NV_SIZE];
} neuron_v;

void fail(void) {
	perror("exiting");
	exit(1);
}

bool activation(float f) {
        if (f > THRESHOLD){ return true; };
        return false;
}

// dot product
float dot(neuron_v *nv, float *conn_row) {
        // conn_row MUST HAVE SAME LEN AS NV
        // i.e. connection matrix must have nv_len columns
        float sum = 0.F;
        for (int i = 0; i < nv->l; i++) {
                // since the 'neurons' are either zero or one
                // this could just be &
                sum += nv->v[i] * (conn_row[i]);
        }
        return sum;
}

// apply conns to a nv and return the result as an array of floats
// of size conns.m
float *apply_conns(conn_matrix *c, neuron_v *nv) {
        float *ret = malloc(c->m * sizeof(float));
        for (int i = 0; i < c->m; i++) {
                ret[i] = dot(nv, &(c->arr[c->n * i]));
        }
        return ret;
}

void print_matrix(conn_matrix *m) {
        printf("m=%i x n=%i matrix\n", m->m, m->n);
        const int num_cols = m->n;
        for (int i = 0; i < m->m; i++){
                printf("\t");
                for (int j = 0; j < m->n; j++){
                        printf("%i%i: %.3f  ", i, j, m->arr[i * num_cols + j]);
                }
                printf("\n");
        }
}

void print_nv(neuron_v *nv) {
        printf("l=%i neuron vector\n", nv->l);
        printf("\t");
        for (int i = 0; i < nv->l; i++){
                printf("%i: %i  ", i, nv->v[i]);
        }
        printf("\n");
}

// initialize each cell with a random float value between 0 exclusive and 1 inclusive
void randomize_matrix(conn_matrix *m) {
	int rand = open("/dev/urandom", O_RDONLY);
	if (rand < 0) { fail(); }
        unsigned int data;
        int res;
        for (int i = 0; i < m->m * m->n; i++){
                res = read(rand, &data, sizeof(data));
                if (res < 0) { fail(); }
                m->arr[i] = (float) data / UINT_MAX;
        }
}

int main(void) {
        conn_matrix *a_1 = calloc(1, sizeof(conn_matrix));
        a_1->m = A_I;
        a_1->n = NV_SIZE;

        neuron_v *retina = calloc(1, sizeof(neuron_v));
        retina->l = NV_SIZE;
        retina->v[0] = true;
        retina->v[1] = false;
        retina->v[2] = true;

        randomize_matrix(a_1);
        print_matrix(a_1);
        print_nv(retina);

        float *res = apply_conns(a_1, retina);
        printf("res  ");
        for (int i = 0; i < NV_SIZE; i++){
                printf("%f ", res[i]);
        }
        printf("\n");

        free(res);
        free(a_1);
        free(retina);
}
