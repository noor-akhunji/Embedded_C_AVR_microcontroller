#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL  // Assuming a 16 MHz clock frequency
#define PWM_FREQUENCY 61.04  // Desired PWM switching frequency in Hz

volatile uint8_t dutyCycleIndex = 0;

// Function to initialize Timer 0 for PWM
void initPWM() {
    // Set fast PWM mode with non-inverting output
    TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
    TCCR0B |= (1 << CS01);  // Set prescaler to 8 for 2 MHz clock (16 MHz / 8)

    // Enable interrupt on Timer 0 overflow
    TIMSK0 |= (1 << TOIE0);
}

// Function to update PWM duty cycle based on dutyCycleIndex
void updatePWM() {
    // Duty cycle values for 0%, 25%, 62.5%, and 87.5%
    uint8_t dutyCycle[] = {0, 64, 160, 224};
    OCR0A = dutyCycle[dutyCycleIndex];
}

// Function to initialize the pushbutton switch
void initPushButton() {
    // Set PORTB pin 0 as input (assuming the switch is connected to this pin)
    DDRB &= ~(1 << DDB0);

    // Enable internal pull-up resistor for the switch
    PORTB |= (1 << PORTB0);
}

// Function to check the pushbutton state
uint8_t isButtonPressed() {
    return bit_is_clear(PINB, PB0);
}

// Interrupt Service Routine for Timer 0 overflow
ISR(TIMER0_OVF_vect) {
    // Toggle PORTD pin 6 (for observing the waveform on an oscilloscope)
    PORTD ^= (1 << PORTD6);
}

int main() {
    // Set PORTD pin 6 as output
    DDRD |= (1 << DDD6);

    // Initialize PWM and pushbutton
    initPWM();
    initPushButton();

    // Enable global interrupts
    sei();

    while (1) {
        // Check if the pushbutton is pressed
        if (isButtonPressed()) {
            // Wait for button release to avoid multiple presses
            while (isButtonPressed())
                _delay_ms(10);

            // Increment duty cycle index and wrap around
            dutyCycleIndex = (dutyCycleIndex + 1) % 4;

            // Update PWM duty cycle
            updatePWM();
        }
    }

    return 0;
}
