#include <iostream>
#include <fstream>
#include <math.h>
#define SIG_LENGTH 320

using namespace std;

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double OutputSignal_MA[SIG_LENGTH];

void moving_average(double* psig_src_arr, double* psig_out_arr, uint32_t signal_length, uint32_t filter_pts);

int main() {

	ofstream file1, file2;

	moving_average((double*)&InputSignal_f32_1kHz_15kHz[0], (double*)&OutputSignal_MA[0], SIG_LENGTH, 11);

	file1.open("moving_average.dat");
	file2.open("input_signal.dat");

	for (int i = 0; i < SIG_LENGTH; i++) {
		file1 << OutputSignal_MA[i] << endl;
		file2 << InputSignal_f32_1kHz_15kHz[i] << endl;
	}

	file1.close();
	file2.close();

	return 0;
}

void moving_average(double* psig_src_arr, double* psig_out_arr, uint32_t signal_length, uint32_t filter_pts)
{
	int i, j;

	for (i = (int) floor(filter_pts / 2); i < (int) (signal_length - floor(filter_pts / 2) - 1); i++) {
		psig_out_arr[i] = 0;

		for (j = -1 * (int) ((filter_pts / 2)); j < (int) floor(filter_pts / 2); j++) {
			psig_out_arr[i] = psig_out_arr[i] + psig_src_arr[i + j];
		}

		psig_out_arr[i] = psig_out_arr[i] / filter_pts;
	}
}