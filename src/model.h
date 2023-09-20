#ifndef _MODEL_H
#define _MODEL_H

// models a system in discrete state space
typedef struct Model {
	const int states; // amount of states. Has to match exactly
	const int inputs; // amount of inputs. Has to match exactly
	const int outputs; // amount of outputs. Has to match exactly
	const double** A; // system matrix
	const double** B; // input matrix
	const double** C; // output matrix
	const double** D; // feedthrough matrix
	double* x; // state vector
	double* u; // input vector
} Model;

// updates the model state vector at timestep k+1
void model_update(Model* model);

// returns the output of the system at timestep k
double* model_output(Model* model);

#endif
