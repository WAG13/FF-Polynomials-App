#pragma once

#include <math.h>
#include <utility>
#include <string>
#include <vector>
#include <sstream>

namespace utils {
	/* 1 string to coeff*/
	std::vector<std::vector<long long>> coefStr(const std::string str, char X = 'x');
	
	/* 2 Euclidean algorithm */
	std::vector<long long> euclideanAlgorithm(long long a, long long b, long long prime);

	/*! #9
	* @brief Function to check if n is prime or not
	*/
	bool isPrime(int n);

	/*! #9
	* @brief Mobius Function
	*/
	int mobius(int N);

	/*! #6
	* @brief Inverse for numbers
	*/
	long long inverse(long long number, long long prime);

	/*! #6
	* @brief Division for numbers in field
	*/
	long long division_for_numbers(long long a, long long b, long long prime);

	template<typename T>
	T gcd(const T& num1, const T& num2) {
		T a;
		T b;
		if (num1 > num2) {
			a = num1;
			b = num2;
		}
		else {
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
