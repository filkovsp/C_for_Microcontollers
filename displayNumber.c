/*
	This code, when compiled and uploaded into ATmega8 microcontroller will count from 0 to 20.
	Given that 7-Segment LED indicator connected to PORTD of the microcontroller:

	 _________________            __________________
	|                 |          |    |             |
	|    --- A ---    |--A-------|PD0 |  ATmega8    |
	|   |         |   |--B-------|PD1 |             |
	|   F         B   |--C-------|PD2 |             |
	|   |         |   |--D-------|PD3 |             |
	|     -- G --     |--E-------|PD4 |             |
	|   |         |   |--F-------|PD5 |             |
	|   E         C   |--G-------|PD6 |             |
	|   |         |   |-(dp)-----|PD7 |             |
	|    --- D --- dp |          |    |  VCC    GND |
	|_________________|          |____|_____________|   
	         |                            |      |      .--> GND
	        C/C                           |     _|_    _|_
                 |             1k             |              
                 `-----------/\/\/\-----------`----------------> VCC
	
	C/C = Common Cathode
	(dp) -> PD7 (optional)
	
	Resistor 1k is shown here connected to C/C just for simplisity. 
	In fact there must be 8 resistors nominal from 330 to 1k between LED's [A-G,dp] and [PD0-PD6,PD7].
	And then LED's C/C connected to VCC directly.
	
	Multi-digit number will be displayed as series of N=precision numbers with short pause between them.
	Precision is the number of digits with leading zeros we want our counter (from 0 to 20) to be represented.
	If precision = 3 then "9" will be reflected at the display as the series:
	"0" + pause(50 msec) + "0" + pause(50 msec) + "9", eash number shows up and being displayed for 250 msec.


 */
#define F_CPU 8000000  // Hz
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h> // contains pow() aka power x^y

// #define nop() {asm("nop");}

// parameter for conversion a number into an array, sets length of the array.
const uint8_t precision = 3;

// byte-codes for [0-9] digits to be displayed at the 7-Segment Display, connected to the microcontroller's PORT.
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

/*
	returns lengths of integer number in digits. e.g: length(999) --> 3
 */
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

/* 
	Converts multiple-digit integer number into an array of integers sized as precision.
	If length of number less than precision, then adds leading zeros.
	e.g: precision = 3, then number = 99 --> array: [0, 9, 9]
 */
uint8_t* numberToArray(uint8_t number) {
	
	uint8_t* n = (uint8_t*)malloc(precision * sizeof(uint8_t));
	
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
	
	return n;
}

/* 
	Displays multiple-digit (integer) number represented as an array. e.g.: 1234 --> [1,2,3,4]
	If length of number less than precision, then adds leading zeros.
 */
void displayNumber(uint8_t number) {
	
	uint8_t* n = numberToArray(number);
	
	for (uint8_t i = 0; i < precision; ++i) {
		PORTD = ~(digits[n[i]]);
		_delay_ms(250);
		PORTD = ~(0);
		_delay_ms(50);
	}
	PORTD = ~(0);
	_delay_ms(700);
	
	free(n);
	// malloc()/free() is the same as new()/delete()
	// this requires #include <stdlib.h>
}

/* 
	Displays single-digit numbers [0-9]:
 */
void displayOneDigitNumber(uint8_t number) {
	PORTD = ~(digits[number]);
	_delay_ms(250);
	PORTD = ~(0);
	_delay_ms(750);
}


int main(void) {
	DDRD = 0xff;
	
	while (1) {
		for (int i = 0; i<20; i++) {
			// displayOneDigitNumber(i);
			displayNumber(i);
		}
	}
}
