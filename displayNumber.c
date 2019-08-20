#define F_CPU 8000000  // Hz
#include <avr/io.h>
#include <math.h> // usage of pow() function from here
#include <util/delay.h>

// #define nop() {asm("nop");}

const uint8_t precision = 2;

const uint8_t digits[] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111  // 9
};

const uint8_t length(uint8_t number) {
	uint8_t counter = 0;
	if (number == 0) {
		++counter;
		} else {
		while (number != 0) {
			number /= 10;
			++counter;
		}
	};
	return counter;
}

void numberToArray(uint8_t number, uint8_t* n) {

	if (length(number) < precision) {
		for (uint8_t i = 0; i < (precision - length(number)); i++) {
			n[i] = 0;
		}
	}

	uint8_t denumerator, mod, nm;

	for (uint8_t i = 0; i < length(number); i++) {
		nm = number % (uint8_t)pow(10, length(number) - i);
		denumerator = (uint8_t)pow(10, length(nm) - 1);
		mod = nm % (uint8_t)pow(10, length(nm) - 1);
		n[precision - length(number) + i] = (nm - mod) / denumerator;
	}

}

void displayNumber(uint8_t number) {
	uint8_t n[precision];
	numberToArray(number, (uint8_t*)&n);
	for (uint8_t i = 0; i < precision; ++i) {
		PORTD = ~(digits[n[i]]);
		_delay_ms(250);
		PORTD = ~(0);
		_delay_ms(50);
	}
	PORTD = ~(0);
	_delay_ms(700);
	// delete[] n;
}

void display1DNumber(uint8_t number) {
	PORTD = ~(digits[number]);
	_delay_ms(250);
	PORTD = ~(0);
	_delay_ms(750);
}


int main(void) {
	// anable port output mode, pullup HIGH
	DDRD = 0xff;
	
	while (1) {
		for (int i = 0; i<20; i++) {
			// display1DNumber(i);
			displayNumber(i);
		}
	}
}
