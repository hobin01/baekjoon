#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <string>

using namespace std;

typedef complex<double> cpx;

const double PI = acos(-1);

void FFT(vector<cpx>& f, cpx w)
{
	// f(x) = a_(n-1) x^(n-1) + ... + a_0 = f_even(x^2) + x*f_odd(x^2)
	// f_even = a_(n-2) x^(n/2-1) + ... + a_2 x + a_0
	// f_odd = a_(n-1) x^(n/2-1) + ... + a_3 x + a_1
	// f(w) = f_even(w^2) + w f_odd(w^2)
	// f(-w) = f_even(w^2) - w f_odd(w^2)

	int n = f.size();

	// base case (상수식)
	if (n == 1)
		return;

	// 다항식 even, odd 분리
	vector<cpx> even(n / 2);
	vector<cpx> odd(n / 2);

	for (int i = 0; i < n; i++) {
		if (i % 2 == 0)
			even[i / 2] = f[i];
		else
			odd[i / 2] = f[i];
	}

	// 각각 DFT 진행 (divide)
	FFT(even, w * w);
	FFT(odd, w * w);

	// conquer
	cpx wp(1, 0); // wp = 1 + 0*i

	for (int i = 0; i < n / 2; i++) {
		// f(w) = f_even(w^2) + w f_odd(w^2)
		f[i] = even[i] + wp * odd[i];

		// f(-w) = f_even(w^2) - w f_odd(w^2)
		f[i + n / 2] = even[i] - wp * odd[i];

		wp *= w;
	}
}

// 두 다항식 곱 리턴
// i 번째 원소는 x^i 계수
vector<cpx> multiply(vector<cpx> a, vector<cpx> b)
{
	int n = 1;
	// 다항식 길이보다 큰 최소 2의 거듭제곱을 n으로
	while ((n < a.size() + 1) || (n < b.size() + 1))
		n *= 2;
	n *= 2;

	a.resize(n);
	b.resize(n);

	vector<cpx> c(n); // c = a * b

	cpx w(cos((2 * PI) / n), sin((2 * PI) / n)); // base (root of unity)

	// FFT로 다항식 DFT 진행
	FFT(a, w);
	FFT(b, w);

	// DFT 결과 곱하면 c의 DFT 값
	for (int i = 0; i < n; i++) {
		c[i] = a[i] * b[i];
	}

	// IDFT로 (역변환) c의 다항식 형태 복원
	FFT(c, cpx(1, 0) / w);

	for (int i = 0; i < n; i++) {
		c[i] /= cpx(n, 0);

		// 다항식 계수가 정수일 때 시행, 실수나 복소수면 그대로 두면 됨
		c[i] = cpx(round(c[i].real()), round(c[i].imag()));
	}

	return c;
}

vector<cpx> stringToComplexVectorBasedDecimal(string s)
{
	int length = s.size();

	vector<cpx> f(length);

	for (int i = 0; i < length; i++) {
		int num = s[length - i - 1] - '0';
		f[i] = cpx(num, 0);
	}

	return f;
}

string ComplexVectorBasedDecimalToString(vector<cpx> f)
{
	string s = "";

	int dec = 10;
	for (int i = 0; i < f.size(); i++) {
		if (f[i].real() >= dec) {
			if (i == f.size() - 1)
				f.push_back(cpx((int)f[i].real() / dec, 0));
			else
				f[i + 1] += cpx((int)f[i].real() / dec, 0);
			f[i] = cpx((int)f[i].real() % dec, 0);
		}
	}

	reverse(f.begin(), f.end());

	int zeroCheck = 0;
	for (int i = 0; i < f.size(); i++) {
		if (f[i].real() != 0) {
			zeroCheck = i;
			break;
		}
	}

	for (int i = zeroCheck; i < f.size(); i++) {
		s += to_string((int)f[i].real());
	}

	return s;
}

int main()
{
	string s1, s2;

	cin >> s1 >> s2;

	if (s1 == "0" || s2 == "0") {
		cout << 0;
		return 0;
	}

	vector<cpx> A = stringToComplexVectorBasedDecimal(s1);
	vector<cpx> B = stringToComplexVectorBasedDecimal(s2);

	vector<cpx> C = multiply(A, B);

	string res = ComplexVectorBasedDecimalToString(C);

	cout << res;
}