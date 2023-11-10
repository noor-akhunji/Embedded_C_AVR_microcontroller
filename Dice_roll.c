#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>

volatile uint8_t buttonPressed = 0;

void initPorts() {
    // Set pins 3-9 as outputs for seven LEDs
    DDRD |= 0xFE;
    
    // Set pin 2 as input for the pushbutton
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2); // Enable internal pull-up resistor

    // Set PB0 as output for the 6th LED
    DDRB |= (1 << PB0);

    // External Interrupt INT0 on falling edge
    EICRA |= (1 << ISC01);
    EIMSK |= (1 << INT0);

    // Initialize random number generator with seed
    srand(123); // You can change the seed value
}

void displayNumber(uint8_t number) {
    // Binary representation of numbers 1 to 6 on seven LEDs
    uint8_t patterns[] = {0b0000000, 0b1000000, 0b1100000, 0b1110000, 0b1111000, 0b1111100};

    // Display the corresponding pattern for the number on the first 5 LEDs
    PORTD = (PORTD & 0x01) | (patterns[number - 1] << 1);

    // Display the 6th LED on PB0
    if (number == 6) {
        PORTB |= (1 << PB0);
    } else {
        PORTB &= ~(1 << PB0);
    }
}

void turnOffLEDs() {
    // Turn off all LEDs on PD1-PD7
    PORTD &= 0x01;
    
    // Turn off the 6th LED on PB0
    PORTB &= ~(1 << PB0);
}

int main() {
    initPorts();
    sei(); // Enable global interrupts

    while (1) {
        if (buttonPressed) {
            // Generate a random number between 1 and 6
            uint8_t randomNumber = (rand() % 7) + 1;

            // Display the number on seven LEDs
            displayNumber(randomNumber);

            // Delay for a short time to display the result
            _delay_ms(1000);

            // Turn off all LEDs
            turnOffLEDs();

            buttonPressed = 0; // Reset buttonPressed flag
        }
    }

    return 0;
}

ISR(INT0_vect) {
    buttonPressed = 1;
}
