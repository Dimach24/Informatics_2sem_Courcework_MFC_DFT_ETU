#include "pch.h"
#include <process.h>
#include <fstream>

#define PI 3.141592653589793238463

void genTest() {
	system("python \"./the standard.py\"");
}

double dft(const std::vector<double>& samples,int m) {
	size_t N = samples.size();

	// real and imaginary parts
	double re = 0, im = 0;

	// for each sample
	for (size_t n = 0; n < N; n++) {
		// summing
		re += samples[n] * cos(2 * PI * m * n / N);
		im += samples[n] * sin(-2 * PI * m * n / N);
	}
	// return the abs(X)
	return sqrt(re * re + im * im);
}

void readTheTestLine(std::istream& in, std::vector<double>& out, int n) {
	out.resize(n);
	for (int i = 0; i < n; i++) {
		in >> out[i];
	}
}

void genDft(const std::vector<double>& signal, std::vector<double>& out) {
	int N = signal.size();
	out.resize(N);
	for (int i = 0; i < N; i++) {
		out[i] = dft(signal, i);
	}
}

void check(const std::vector<double>& a, const std::vector<double>& b) {
	for (int i = 0; i < a.size(); i++) {
		double	first = round(a[i] * 1e7) * 1e-7,
				second = round(b[i] * 1e7) * 1e-7;
		EXPECT_DOUBLE_EQ(first, second);
	}
}

TEST(TestCaseName, TestName) {
  genTest();
  std::ifstream fin("./test.txt");
  std::vector<double> signal;
  std::vector<double> true_dft;
  std::vector<double> calculated_dft;
  
  for (int i = 0; i < 100; i++) {
	  readTheTestLine(fin, signal, 100);
	  readTheTestLine(fin, true_dft, 100);
	  genDft(signal, calculated_dft);
	  check(true_dft, calculated_dft);
  }

  fin.close();
}