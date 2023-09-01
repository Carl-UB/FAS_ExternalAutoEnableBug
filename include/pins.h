#include <FastAccelStepper.h>

#include <cstdint>

const uint8_t step_pin = 23;

// Minimum reproducible example uses a fake function that just removes external flag and passes
// straight to digitalWrite.
const uint8_t fake_external_enable_pin = 19 | PIN_EXTERNAL_FLAG;
const uint8_t internal_enable_pin = 19;

// This pin should be left alone but instead is written high while stepper is running.
const uint8_t victim_pin_0 = 0;
