// Including necessary header files
#include <stdint.h>
#include "TM4C123GH6PM.h"
#include "Port_Config.h"
#include "SysTick.h"
#include "scheduler.h"
#include "TM4C123GH6PM.h"  // This inclusion is redundant and can be removed.

// Enum to define possible LED states
typedef enum {
    WHITE,
    RED,
    GREEN,
    BLUE
} LEDState;

// Global variable to track the current state of the LED
LEDState currentState = WHITE;

// Function to configure initial GPIO settings for LED and switches
void setup() {
    // Enable clock for GPIOF (LEDs and switches are on Port F)
    SYSCTL_RCGCGPIO_R |= 0x20;

    // Set LED pins (PF1, PF2, PF3) as outputs
    GPIO_PORTF_DIR_R |= 0x0E;
    GPIO_PORTF_DEN_R |= 0x0E;

    // Set switch pins (PF0, PF4) as inputs with pull-ups
    GPIO_PORTF_DIR_R &= ~(0x11);
    GPIO_PORTF_DEN_R |= 0x11;
    GPIO_PORTF_PUR_R |= 0x11;
}

// Task function to read the state of the switches and change the LED state accordingly
void task_readSwitches() {
    // Check if both buttons (PF0 & PF4) are pressed
    if (!(GPIO_PORTF_DATA_R & 0x10) && !(GPIO_PORTF_DATA_R & 0x01)) {  
        currentState = WHITE;
    } 
    // Check if only Btn1 (PF4) is pressed
    else if (!(GPIO_PORTF_DATA_R & 0x10)) {  
        currentState = (currentState + 1) % 4;
    } 
    // Check if only Btn2 (PF0) is pressed
    else if (!(GPIO_PORTF_DATA_R & 0x01)) {  
        currentState = (currentState == WHITE) ? BLUE : currentState - 1;
    }
}

// Task function to set the LED state based on the value of currentState
void task_switchStates() {
    switch (currentState) {
        case WHITE:
            // Turn off all LEDs
            GPIO_PORTF_DATA_R &= ~(0x0E);
            break;
        case RED:
            // Set LED to RED
            GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~0x0E) | 0x02;
            break;
        case GREEN:
            // Set LED to GREEN
            GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~0x0E) | 0x08;
            break;
        case BLUE:
            // Set LED to BLUE
            GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~0x0E) | 0x04;
            break;
    }
}

// Main function to initialize and run the tasks
int main(void) {
    // Set up GPIO configurations
    setup();

    // Initialize tasks with their respective periods
    task_init(task_readSwitches, 1);   // Read switches every tick
    task_init(task_switchStates, 2);   // Update LED state every 2 ticks

    // Execute the scheduler to manage tasks
    task_sched();

    return 0;
}
