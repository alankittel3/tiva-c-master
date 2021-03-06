//*****************************************************************************
//
// buttons.h - Prototypes for the evaluation board buttons driver.
//
// Copyright (c) 2012-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.0.12573 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#ifndef __BUTTONS_H__
#define __BUTTONS_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Defines for the hardware resources used by the pushbuttons.
//
// The switches are on the following ports/pins:
//
// PF4 - Left Button
// PF0 - Right Button
//
// The switches tie the GPIO to ground, so the GPIOs need to be configured
// with pull-ups, and a value of 0 means the switch is pressed.
//
//*****************************************************************************
#define BUTTONS_GPIO_PERIPH_A    SYSCTL_PERIPH_GPIOA
#define BUTTONS_GPIO_PERIPH_F    SYSCTL_PERIPH_GPIOF
#define BUTTONS_GPIO_BASE_A      GPIO_PORTA_BASE
#define BUTTONS_GPIO_BASE_F      GPIO_PORTF_BASE

#define NUM_BUTTONS             7
#define P1_START                GPIO_PIN_2
#define P2_START                GPIO_PIN_3
#define JOYSTICK_UP             GPIO_PIN_4
#define JOYSTICK_DOWN           GPIO_PIN_5
#define JOYSTICK_LEFT           GPIO_PIN_6

#define JOYSTICK_RIGHT          GPIO_PIN_0
#define JOYSTICK_FIRE           GPIO_PIN_1

//#define JOYSTICK_RIGHT          GPIO_PIN_5
//#define JOYSTICK_FIRE           GPIO_PIN_6
//#define DIAL_INCREMENT          GPIO_PIN_0
//#define DIAL_DECREMENT          GPIO_PIN_1

#define ALL_BUTTONS             (P1_START | P2_START | JOYSTICK_UP |\
  JOYSTICK_DOWN | JOYSTICK_LEFT | JOYSTICK_RIGHT | JOYSTICK_FIRE)
#define BUTTONS_A               (P1_START | P2_START | JOYSTICK_UP | JOYSTICK_DOWN | JOYSTICK_LEFT)
#define BUTTONS_F               (JOYSTICK_RIGHT | JOYSTICK_FIRE)

//*****************************************************************************
//
// Useful macros for detecting button events.
//
//*****************************************************************************
#define BUTTON_PRESSED(button, buttons, changed)                              \
        (((button) & (changed)) && ((button) & (buttons)))

#define BUTTON_RELEASED(button, buttons, changed)                             \
        (((button) & (changed)) && !((button) & (buttons)))

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Functions exported from buttons.c
//
//*****************************************************************************
extern void ButtonsInit(void);
extern uint8_t ButtonsPoll(uint8_t *pui8Delta,
                             uint8_t *pui8Raw);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************

#endif // __BUTTONS_H__
