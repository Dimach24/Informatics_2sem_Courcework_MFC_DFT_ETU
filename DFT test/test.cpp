#include "pch.h"		//for gtest

#include <process.h>	// for 'system'
#include <fstream>		// for file reading

// for pi constant and
// trigonometry
#include <cmath>		

/// <summary>
/// Class of the tests
/// </summary>
class NumpyComparisonTest : public ::testing::Test
{
	/// <summary>
	/// On initialization
	/// </summary>
	void SetUp() override {
		genTest();
		fin.open("test.txt");
	}

	/// <summary>
	/// On destruction
	/// </summary>
	void TearDown() override {
		fin.close();
	}
public:
	/// <summary>
	/// vector of calculated values
	/// </summary>
	std::vector<double> calculated_dft;

	/// <summary>
	/// vector of read dft values
	/// </summary>
	std::vector<double> true_dft;

	/// <summary>
	/// Samples size
	/// </summary>
	size_t N = 1000;
protected:
	/// <summary>
	/// input file stream
	/// </summary>
	std::ifstream fin;
	
	/// <summary>
	/// vector of read samples 
	/// </summary>
	std::vector<double> samples;



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
	double dft(int m) {

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
	void readTheTestLine(std::vector<double>& out) {
		// reserving memory
		out.resize(N);
		// for each i = 0, 1, ..., n-1
		for (int i = 0; i < N; i++) {
			// read a number from the stream to the vector[i]
			fin >> out[i];
		}
	}

	/// <summary>
	/// Calculates dft absolute values
	/// </summary>
	/// <param name="signal">a vector of source data</param>
	/// <param name="out">a place for result</param>
	void genDft() {
		// reserve memory
		calculated_dft.resize(N);
		// for each i = 0, 1, ..., N-1
		for (int i = 0; i < N; i++) {
			// calculate DFT sample and 
			// write it to the vector
			calculated_dft[i] = dft(i);
		}
	}

	/// <summary>
	/// Calculates one test
	/// </summary>
	void calculate_one() {
		readTheTestLine(samples);
		readTheTestLine(true_dft);
		genDft();
	}
};

// Test it
TEST_F(NumpyComparisonTest, RandomTests) {
	// or each of 100 tests
	for (int i = 0; i < 100; i++) {
		// calculate one
		calculate_one();
		// comparison loop
		for (int i = 0; i < N; i++) {
			ASSERT_NEAR(true_dft[i], calculated_dft[i], 1e-10);
		}
	}
}