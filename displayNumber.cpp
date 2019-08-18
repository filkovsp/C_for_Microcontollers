// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>

#define presision 2
// #define arr[presision];

char words[][6] = {
	"zero",
	"one",
	"two",
	"three",
	"foour",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

uint8_t digits[] = {
	0, // 0b00111111, // 0
	1, // 0b00000110, // 1
	2, // 0b01011011, // 2
	3, // 0b01001111, // 3
	4, // 0b01100110, // 4
	5, // 0b01101101, // 5
	6, // 0b01111101, // 6
	7, // 0b00000111, // 7
	8, // 0b01111111, // 8
	9  // 0b01101111  // 9
};

uint8_t length(uint8_t number) {
	uint8_t counter = 0;
	if (number == 0) {
		++counter;
	} else {
		while (number != 0) {
			// n = n/10
			number /= 10;
			++counter;
		}
	};
	return counter;
}

uint8_t *numberToArray(uint8_t number) {

	uint8_t n[presision];
	// uint8_t *np = &n;

	if (length(number) < presision) {
		for (int i = 0; i < (presision - length(number)); i++) {
			n[i] = 0;
		}
	
	}

	// if (length(number) < presision) {
	// 	for (uint8_t i = 0; i < sizeof(n); i++) {
	// 		n[i] = 0;
	// 	}
	// }

	for (uint8_t i = (presision - length(number)); i < presision; i++) {
		n[i] = (number - (number % (uint8_t)pow(10, length(number) - i))) / pow(10, length(number) - i);
	}

	return n;
}

void display1DNumber(uint8_t number) {	
	printf("Displaied number: %d\n", digits[number]);
	printf("Displaied number: %s\n", words[number]);

}

void displayNumber(uint8_t arr[]) {
	// https://www.quora.com/What-is-the-equivalent-of-array-length-used-in-Java-in-C++
	// uint8_t size = *(&number_ptr + 1) - number_ptr;
	// uint8_t size = (uint8_t)sizeof(&number_ptr)/(uint8_t)sizeof((number_ptr+1));
	for (uint8_t i = 0; i < presision; i++) {
		printf("Displaied number: %d\n", digits[arr[i]]);
	}
}

void diaplayWord(uint8_t *word_ptr) {
	//
}

int main() {

	while (1) {
		for (int i = 0; i < 10; i++) {
			// display1DNumber(i);
			uint8_t *number = numberToArray(i);
			
			uint8_t arr[presision];
			for (uint8_t i = 0; i < presision; i++) {
				arr[i] = number[i];
			}
			
			displayNumber(arr);
		}
	}
}
