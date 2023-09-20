#include <stdlib.h>
#include "model.h"

void model_update(Model* model) {
	// x_{k+1} = Ax_k + Bu_k

	// Ax_k
	for(int i = 0; i < model->states; i++) {
		for(int j = 0; j < model->states; j++)
			model->x[i] += model->A[i][j] * model->x[j];
	}

	// Bu
	for(int i = 0; i < model->inputs; i++) {
		for(int j = 0; j < model->inputs; j++)
			model->x[i] += model->B[i][j] * model->u[j];
	}
}

double* model_output(Model* model) {
	// y = Cx_k + Du_k
	double* y = (double*) malloc(model->states * sizeof(double));

	// Cx_k
	for(int i = 0; i < model->outputs; i++) {
		for(int j = 0; j < model->states; j++)
			y[i] += model->C[i][j] * model->x[j];
	}

	// Bu
	for(int i = 0; i < model->inputs; i++) {
		for(int j = 0; j < model->inputs; j++)
			y[i] += model->B[i][j] * model->u[j];
	}	
}
