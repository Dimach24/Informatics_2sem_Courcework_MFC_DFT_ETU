#include "pch.h"		//for gtest

#include <process.h>	// for 'system'
#include <fstream>		// for file reading
#include <cmath>		// for pi constant and
						// trigonometry

/// <summary>
/// asks python file to generate the tests
/// </summary>
void genTest() {
	system("python \"./the standard.py\"");
}

/// <summary>
/// DFT function that copied from the project
/// </summary>
/// <param name="samples">a vector of samples</param>
/// <param name="m">number of dft sample to calculate</param>
/// <returns>absolute value of the DFT m sample</returns>
double dft(const std::vector<double>& samples, int m) {
	size_t N = samples.size(); // getting number of samples

	// real and imaginary parts
	double re = 0, im = 0;

	// for each sample
	for (size_t n = 0; n < N; n++) {
		// summing
		re += samples[n] * cos(2 * M_PI * m * n / N);
		im += samples[n] * sin(-2 * M_PI * m * n / N);
	}
	// return the abs(X)
	return sqrt(re * re + im * im);
}
/// <summary>
/// Reads 'n' numbers from the stream
/// </summary>
/// <param name="in">stream to read</param>
/// <param name="out">output vector</param>
/// <param name="n">amount of numbers</param>
void readTheTestLine(std::istream& in, std::vector<double>& out, int n) {
	// reserving memory
	out.resize(n);
	// for each i = 0, 1, ..., n-1
	for (int i = 0; i < n; i++) {
		// read a number from the stream to the vector[i]
		in >> out[i];
	}
}

/// <summary>
/// Calculates dft absolute values
/// </summary>
/// <param name="signal">a vector of source data</param>
/// <param name="out">a place for result</param>
void genDft(const std::vector<double>& signal, std::vector<double>& out) {
	// get samples amount
	int N = signal.size();
	// reserve memory
	out.resize(N);
	// for each i = 0, 1, ..., N-1
	for (int i = 0; i < N; i++) {
		// calculate DFT sample and 
		// write it to the vector
		out[i] = dft(signal, i);
	}
}
/// <summary>
/// Check if test passed successfully
/// </summary>
/// <param name="a">expecting value</param>
/// <param name="b">calculated value</param>
void check(const std::vector<double>& a, const std::vector<double>& b) {
	// for each i = 0, 1, ..., a.size()-1
	for (int i = 0; i < a.size(); i++) {
		ASSERT_NEAR(a[i], b[i],1e-10);
	}
}

TEST(DFT_test, RandomTest) {
	genTest();
	std::ifstream fin("./test.txt");
	std::vector<double> signal;
	std::vector<double> true_dft;
	std::vector<double> calculated_dft;

	size_t N = 1000;
	size_t tests = 100;
	for (int i = 0; i < tests; i++) {
		readTheTestLine(fin, signal, N);
		readTheTestLine(fin, true_dft, N);
		genDft(signal, calculated_dft);
		check(true_dft, calculated_dft);
	}

	fin.close();
}