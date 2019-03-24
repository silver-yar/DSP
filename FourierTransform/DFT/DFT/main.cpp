/* Discrete Fourier Transform [ Time Domain -> Freq Domain ] */

#define _USE_MATH_DEFINES
#define SIG_LENGTH 320 

#include <iostream>
#include <math.h>
#include <fstream>


using namespace std;

extern double InputSignal_f32_1kHz_15kHz[SIG_LENGTH];
double Output_ReX[SIG_LENGTH];
double Output_ImX[SIG_LENGTH];
double Output_Mag[SIG_LENGTH];

void calc_sig_dft(double* psig_src_arr, double* psig_dest_rex_arr, double* psig_dest_imx_arr, int sig_length);
void get_dft_output_mag(double* psig_dest_mag_arr, double* psig_src_rex_arr, double* psig_src_imx_arr);


int main()
{
	ofstream file1, file2, file3, file4;

	calc_sig_dft((double*)&InputSignal_f32_1kHz_15kHz[0], 
				 (double*)&Output_ReX[0], 
				 (double*)&Output_ImX[0], 
				 (int)SIG_LENGTH);

	get_dft_output_mag((double*)&Output_Mag[0], (double*)&Output_ReX[0], (double*)&Output_ImX[0]);

	file1.open("input_signal.dat");
	file2.open("output_rex.dat");
	file3.open("output_imx.dat");
	file4.open("output_mag.dat");

	for (int i = 0; i < SIG_LENGTH; i++) {
		file1 << InputSignal_f32_1kHz_15kHz[i] << endl;

		file2 << Output_ReX[i] << endl;
		file3 << Output_ImX[i] << endl;
		file4 << Output_Mag[i] << endl;
	}

	file1.close();
	file2.close();
	file3.close();
	file4.close();

	return 0;
}

/*********************************************************************
/ Inputs: 
/ 1.) Input Signal Array, 
/ 2.) Output Signal Real Part ReX, 
/ 3.) Output Signal Imaginary Part ImX, 
/ 4.) Signal Length 
/ 
/ Goal: Calculate DFT for Input Signal 
/*********************************************************************/
void calc_sig_dft(double* psig_src_arr, 
				  double* psig_dest_rex_arr, 
				  double* psig_dest_imx_arr, 
				  int sig_length) 
{
	// Local loop counter variables
	int i, j, k;

	for (j = 0; j < sig_length; j++) {
		// Initialization
		psig_dest_rex_arr[j] = 0;
		psig_dest_imx_arr[j] = 0;
	}

	for (k = 0; k < sig_length; k++) {
		for (i = 0; i < sig_length; i++) {
			// Calculate Real Part
			psig_dest_rex_arr[k] = psig_dest_rex_arr[k] + psig_src_arr[i] * cos(2 * M_PI * k * i / sig_length);

			// Calculate Imaginary Part
			psig_dest_imx_arr[k] = psig_dest_imx_arr[k] + psig_src_arr[i] * sin(2 * M_PI * k * i / sig_length);
		}
	}
}

/*********************************************************************
/ Inputs:
/ 1.) Output Sig Magnitude,
/ 2.) Output Signal Real Part ReX,
/ 3.) Output Signal Imaginary Part ImX,
/
/ Goal: Calculate DFT for Input Signal
/*********************************************************************/
void get_dft_output_mag(double* psig_dest_mag_arr, double* psig_src_rex_arr, double* psig_src_imx_arr)
{
	for (int x = 0; x < SIG_LENGTH / 2; x++) {
		psig_dest_mag_arr[x] = sqrt(pow(psig_src_rex_arr[x], 2) + pow(psig_src_imx_arr[x], 2));
	}
}