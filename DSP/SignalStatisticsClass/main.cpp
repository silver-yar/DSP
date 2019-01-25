// SignalStatisticsClass.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "SignalStatistics.h"

using namespace std;

extern double InputSignal_f32_1kHz_15kHz[320];

int main()
{
	double mean;
	double variance;
	double std;
	SignalStatistics *testSignal = new SignalStatistics(&InputSignal_f32_1kHz_15kHz[0],
		(sizeof(InputSignal_f32_1kHz_15kHz) / sizeof(InputSignal_f32_1kHz_15kHz[0])));

	mean = testSignal->calc_signal_mean();
	variance = testSignal->calc_signal_variance();
	std = testSignal->calc_signal_std();

    cout << mean << endl;
	cout << variance << endl;
	cout << std << endl;

	return 0;
}
