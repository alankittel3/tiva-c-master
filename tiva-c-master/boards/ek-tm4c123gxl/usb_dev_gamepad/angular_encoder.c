#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "angular_encoder.h"

static uint8_t g_ui8EncoderStates = ENCODER_PINS;

uint8_t
EncoderPoll(uint8_t *pui8Delta, uint8_t *pui8RawState) {
    uint32_t ui32Delta;
    uint32_t ui32Data;
    static uint8_t ui8SwitchClockA = 0;
    static uint8_t ui8SwitchClockB = 0;

    ui32Data = ROM_GPIOPinRead(ENCODER_GPIO_BASE, ENCODER_PINS);

    if(pui8RawState)
    {
        *pui8RawState = (uint8_t)~ui32Data;
    }

    ui32Delta = ui32Data ^ g_ui8EncoderStates;

    //
    // Increment the clocks by one.
    //
    ui8SwitchClockA ^= ui8SwitchClockB;
    ui8SwitchClockB = ~ui8SwitchClockB;

    //
    // Reset the clocks corresponding to switches that have not changed state.
    //
    ui8SwitchClockA &= ui32Delta;
    ui8SwitchClockB &= ui32Delta;

    //
    // Get the new debounced switch state.
    //
    g_ui8EncoderStates &= ui8SwitchClockA | ui8SwitchClockB;
    g_ui8EncoderStates |= (~(ui8SwitchClockA | ui8SwitchClockB)) & ui32Data;

    //
    // Determine the switches that just changed debounced state.
    //
    ui32Delta ^= (ui8SwitchClockA | ui8SwitchClockB);

    //
    // Store the bit mask for the buttons that have changed for return to
    // caller.
    //
    if(pui8Delta)
    {
        *pui8Delta = (uint8_t)ui32Delta;
    }

    //
    // Return the debounced buttons states to the caller.  Invert the bit
    // sense so that a '1' indicates the button is pressed, which is a
    // sensible way to interpret the return value.
    //
    return(~g_ui8EncoderStates);

}

void
EncoderInit(void) {
    ROM_SysCtlPeripheralEnable(ENCODER_GPIO_PERIPH);

    HWREG(ENCODER_GPIO_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(ENCODER_GPIO_BASE + GPIO_O_CR) |= 0x7F;
    HWREG(ENCODER_GPIO_BASE + GPIO_O_LOCK) = 0;

    ROM_GPIODirModeSet(ENCODER_GPIO_BASE, ENCODER_PINS, GPIO_DIR_MODE_IN);
    MAP_GPIOPadConfigSet(ENCODER_GPIO_BASE, ENCODER_PINS,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    g_ui8EncoderStates = ROM_GPIOPinRead(ENCODER_GPIO_BASE, ENCODER_PINS);
}
