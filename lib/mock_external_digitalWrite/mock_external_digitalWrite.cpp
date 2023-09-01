#include "mock_external_digitalWrite.h"

bool mock_external_digitalWrite(uint8_t pin, uint8_t value) {
    // Remove flag
    pin = pin & ~PIN_EXTERNAL_FLAG;

    // Write as normal
    digitalWrite(pin, value);

    // Return new pin value for FAS callback
    return digitalRead(pin);
}
