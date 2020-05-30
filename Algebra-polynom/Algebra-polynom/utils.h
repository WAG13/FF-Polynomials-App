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
}
