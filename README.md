# Embedded_C_AVR_microcontroller

AVR Dice Roll Simulator & PWM Generation 🚀
This repository contains two separate AVR-based embedded systems projects showcasing key microcontroller concepts:

1. Dice Roll Simulator
2. PWM Signal Generator with Dynamic Duty Cycle Adjustment
   
# 1️⃣ AVR Dice Roll Simulator 🎲
Simulate a dice roll using an ATmega microcontroller, push button, and LEDs. 

This project demonstrates:
- External Interrupt Handling: Rolling the dice with a button press.
- Random Number Generation: Using rand() to generate values between 1 and 6.
- LED Control: Displaying results with six LEDs.

How It Works:
- Press the button connected to pin PD2.
- A random number (1–6) is generated and displayed on the LEDs.
- LEDs turn off after a 1-second delay, ready for the next roll.

Features:
- Interrupt-driven button press detection.
- Randomized dice values for every roll.
- Clear and concise LED-based visual feedback.

# 2️⃣ PWM Signal Generator with Dynamic Duty Cycle 📶 Generate a pulse-width modulation (PWM) signal with variable duty cycles using Timer 0 on an ATmega microcontroller. 

This project highlights:
- PWM Signal Generation: Using Timer 0 in Fast PWM mode.
- Dynamic Duty Cycle Adjustment: Cycles through preset duty cycles (0%, 25%, 62.5%, 87.5%) with each button press.
- Pushbutton Input Handling: Incrementing the duty cycle index while avoiding bounce issues.

How It Works:
- Timer 0 is configured in Fast PWM mode with a prescaler of 8.
- A push button toggles between four predefined duty cycles.
- The waveform can be observed on pin PD6.

Features:
- Interrupt-driven Timer 0 overflow for smooth PWM operation.
- Visual debugging on PD6 (toggle for oscilloscope monitoring).
- Debounced button press for seamless duty cycle adjustments.

Combined Requirements:
- ATmega microcontroller (e.g., ATmega328P).
- LEDs for the Dice Roll Simulator.
- Oscilloscope (optional) for monitoring PWM waveforms.
- Pushbutton for user input.

Usage Instructions:
- Clone the repository.
- Navigate to the respective project's folder.
- Compile and upload the code using AVRDUDE or a similar tool.
- Connect the circuit as per the pin configuration in the code.
