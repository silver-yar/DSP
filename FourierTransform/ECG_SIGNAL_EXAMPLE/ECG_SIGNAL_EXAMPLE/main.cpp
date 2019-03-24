/* Inverse Discrete Fourier Transform [ Freq Domain -> Time Domain ] */

#define _USE_MATH_DEFINES
#define SIG_LENGTH 640 

#include <iostream>
#include <math.h>
#include <fstream>


using namespace std;

extern double _640_points_ecg_[SIG_LENGTH];

double Output_ReX[SIG_LENGTH];
double Output_ImX[SIG_LENGTH];
double Output_Mag[SIG_LENGTH];
double Output_IDFT[SIG_LENGTH];

// DFT ALGORITHM, FREQ DOMAIN OUTPUT MAGNITUDE, IDFT ALGORITHM
void calc_sig_dft(double* psig_src_arr, double* psig_dest_rex_arr, double* psig_dest_imx_arr, int sig_length);
void get_dft_output_mag(double* psig_dest_mag_arr, double* psig_src_rex_arr, double* psig_src_imx_arr);
void calc_sig_idft(double* pidft_out_arr, double* psig_src_rex_arr, double* psig_src_imx_arr, int idft_length);


int main()
{
	ofstream file1, file2, file3, file4, file5;

	calc_sig_dft((double*)&_640_points_ecg_[0], 
				 (double*)&Output_ReX[0], 
				 (double*)&Output_ImX[0], 
				 (int)SIG_LENGTH);

	get_dft_output_mag((double*)&Output_Mag[0], (double*)&Output_ReX[0], (double*)&Output_ImX[0]);

	calc_sig_idft((double*)&Output_IDFT[0], 
				  (double*)&Output_ReX[0], 
				  (double*)&Output_ImX[0], 
				  (int)SIG_LENGTH);

	file1.open("input_signal.dat");
	file2.open("output_rex.dat");
	file3.open("output_imx.dat");
	file4.open("output_mag.dat");
	file5.open("output_idft.dat");

	for (int i = 0; i < SIG_LENGTH; i++) {
		file1 << _640_points_ecg_[i] << endl;

		file2 << Output_ReX[i] << endl;
		file3 << Output_ImX[i] << endl;
		file4 << Output_Mag[i] << endl;

		file5 << Output_IDFT[i] << endl;
	}

	file1.close();
	file2.close();
	file3.close();
	file4.close();
	file5.close();

	return 0;
}

/*********************************************************************
/ DFT ALGORITHM 
/
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
/ FREQUENCY DOMAIN OUTPUT MAGNITUDE
/
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

/*********************************************************************
/ IDFT ALGORITHM
/
/ Inputs:
/ 1.) Output Time Domain Signal,
/ 2.) Signal Real Part ReX,
/ 3.) Signal Imaginary Part ImX,
/ 4.) Time Domain Signal Length
/
/ Goal: Calculate DFT for Input Signal
/*********************************************************************/
void calc_sig_idft(double* pidft_out_arr, 
				   double* psig_src_rex_arr, 
				   double* psig_src_imx_arr, 
				   int idft_length)
{
	int i, k;

	for (k = 0; k < idft_length; k++) {
		psig_src_rex_arr[k] = psig_src_rex_arr[k] / (idft_length / 2);
		psig_src_imx_arr[k] = psig_src_imx_arr[k] / (idft_length / 2);
	}

	for (k = 0; k < idft_length; k++) {
		pidft_out_arr[k] = 0;
		// cout << "output: " << pidft_out_arr[k] << endl;
	}

	for (k = 0; k < idft_length / 2; k++) {
		for (i = 0; i < idft_length; i++) {
			pidft_out_arr[i] = pidft_out_arr[i] + psig_src_rex_arr[k] * cos(2 * M_PI * k * i / idft_length) 
												+ psig_src_imx_arr[k] * sin(2 * M_PI * k * i / idft_length);
		}
	}
}