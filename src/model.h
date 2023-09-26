#ifndef _MODEL_H
#define _MODEL_H

// models a discrete system in state space
typedef struct Model {
	const int states; // amount of states. Has to match exactly
	const int inputs; // amount of inputs. Has to match exactly
	const int outputs; // amount of outputs. Has to match exactly
	double** A; // system matrix. states x states
	double** B; // input matrix. states x inputs
	double** C; // output matrix. outputs x states
	double** D; // feedthrough matrix. outputs x inputs
	double* x; // state vector
	double* u; // input vector
} Model;

// updates the model state vector at timestep k+1
void model_update(Model* model);

// returns the output of the system at timestep k
double* model_output(Model* model);

// frees the model data from memory
void model_free(Model* model);

#endif
