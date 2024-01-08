#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>


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
// activation step function
// dot product of nv_size
#define THRESHOLD 0.5

typedef struct conn_matrix {
        int m;
        int n;
	float arr[NV_SIZE * A_I];
} conn_matrix;

typedef struct neuron_v {
        int l;
	bool v[NV_SIZE];
} neuron_v;
void test(void);
void print_nv(neuron_v *nv);
void print_matrix(conn_matrix *m);
bool *apply_conns(conn_matrix *c, neuron_v *nv);
float dot(neuron_v *nv, float *conn_row);
void fail(void);
void randomize_matrix(conn_matrix *m);
void gen_training(void);
char *gen_row(void);
// each row should have NV_SIZE 1s or 0s at random
// plus the catagory


int main(void) {
	test();
}

void test(void) {
        conn_matrix *a_1 = calloc(1, sizeof(conn_matrix));
        a_1->m = A_I;
        a_1->n = NV_SIZE;

        neuron_v *retina = calloc(1, sizeof(neuron_v));
        retina->l = NV_SIZE;
        for (int i = 0; i < NV_SIZE; i++){
                retina->v[i] = true;
        }

        randomize_matrix(a_1);
        print_matrix(a_1);
        print_nv(retina);

        bool *res = apply_conns(a_1, retina);
        fprintf(stderr, "res  ");
        for (int i = 0; i < NV_SIZE; i++){
                fprintf(stderr, "%i ", res[i]);
        }
        fprintf(stderr, "\n");

        free(res);
        free(a_1);
        free(retina);
}

char *gen_row(void) {

}

void gen_training(void) {

}

void fail(void) {
	perror("exiting");
	exit(1);
}

// factor is required to adjust threshold for number of elements in dot product
bool activation(float value, int factor) {
        if (value > THRESHOLD * factor){ return true; };
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
bool *apply_conns(conn_matrix *c, neuron_v *nv) {
        bool *ret = malloc(c->m * sizeof(float));
        for (int i = 0; i < c->m; i++) {
                ret[i] = activation(dot(nv, &(c->arr[c->n * i])), NV_SIZE);
        }
        return ret;
}

void print_matrix(conn_matrix *m) {
        fprintf(stderr, "m=%i x n=%i matrix\n", m->m, m->n);
        const int num_cols = m->n;
        for (int i = 0; i < m->m; i++){
                fprintf(stderr, "\t");
                for (int j = 0; j < m->n; j++){
                        fprintf(stderr, "%i%i: %.3f  ", i, j, m->arr[i * num_cols + j]);
                }
                fprintf(stderr, "\n");
        }
}

void print_nv(neuron_v *nv) {
        fprintf(stderr, "l=%i neuron vector\n", nv->l);
        fprintf(stderr, "\t");
        for (int i = 0; i < nv->l; i++){
                fprintf(stderr, "%i: %i  ", i, nv->v[i]);
        }
        fprintf(stderr, "\n");
}

// initialize each cell with a random float value between 0 exclusive and 1 inclusive
// TODO exclude 0
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

