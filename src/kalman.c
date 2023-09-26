#include "kalman.h"

void kalman_predict(Kalman* kalman) {
	model_update(&kalman->system);
}
