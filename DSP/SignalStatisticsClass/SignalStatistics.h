#pragma once
#ifndef SIGNALSTATISTICS_H
#define SIGNALSTATISTICS_H

class SignalStatistics {
private:
	double* sig_src_arr;
	int sig_length;

public:
	SignalStatistics(double * _sig_src_arr, int _sig_length);
	double calc_signal_mean();
	double calc_signal_variance();
	double calc_signal_std();

};
#endif // SIGNALSTATISTICS_H
