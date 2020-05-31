#include <math.h>
#include <utility>

namespace utils {

	



	template<typename T>
	T gcd(const T& num1, const T& num2) {
		T a;
		T b;
		if (num1 > num2) {
			a = num1;
			b = num2;
		} else {
			a = num2;
			b = num1;
		}
	
		while (b > 0) {
			T tmp = b;
			b = a % b;
			a = tmp;
		}
		return a;
	}
	
	/*
	 * @author Hryshchenko Yurii
	 * @brief Euler's totient function (counts integers from 1 to n that are co-prime to n)
	 */
	
	template<typename T>
	T euler(const T& n) {
		T result = 1;
		for (T i = 2; i < n; i++) {
			if (gcd<T>(i, n) == 1)
				result++;
		}
		return result;
	}
	/*! #6
	* @brief Inverse for numbers
	*/
	static long long inverse(long long number, long long prime) {
		long long a = number;
		long long b = prime;
		long long a_1 = 1;
		long long b_1 = 0;
		long long result = 0;
		while ((a != 1) && (b != 1)) {
			if ((a == 0) || (b == 0)) {
				return 0;
			}
			if (a >= b) {
				while (a >= b) {
					a -= b;
					a_1 -= b_1;
				}
			}
			else {
				while (b >= a) {
					b -= a;
					b_1 -= a_1;
				}
			}
		}
		if (a == 1) {
			result = a_1;
		}
		else {
			result = b_1;
		}
		result %= prime;
		if (result < 0) {
			result += prime;
		}
		return result;
	}
	/*! #6
	* @brief Division for numbers in field
	*/
	static long long division_for_numbers(long long a, long long b, long long prime) {
		a *= inverse(b, prime);
		return a;
	}
}
