#include <Arduino.h>
#include <FastAccelStepper.h>
#include <unity.h>

#include "mock_external_digitalWrite.h"
#include "pins.h"

FastAccelStepperEngine engine;

FastAccelStepper* stepper = nullptr;

void setUp(void) {}

void test_stepper_setup_success(void) { TEST_ASSERT(stepper); }

void test_victim_still_low(void) { TEST_ASSERT_EQUAL(LOW, digitalRead(victim_pin_0)); }

void test_broken_internal_auto_enable(void) {
    RUN_TEST(test_victim_still_low);

    stepper->setSpeedInHz(100);  // Arbitrary value.
    stepper->runForward();
    vTaskDelay(100);
    RUN_TEST(test_victim_still_low);  // Fails
    vTaskDelay(100);

    stepper->stopMove();
    while (stepper->isRunning())
        ;
    vTaskDelay(100);

    RUN_TEST(test_victim_still_low);
}

void setup(void) {
    pinMode(internal_enable_pin, OUTPUT);
    pinMode(victim_pin_0, OUTPUT);
    digitalWrite(victim_pin_0, LOW);

    engine.init();

    stepper = engine.stepperConnectToPin(step_pin);
    stepper->setEnablePin(internal_enable_pin);
    stepper->setAutoEnable(true);
    stepper->setAcceleration(10000);

    delay(2000);

    UNITY_BEGIN();

    RUN_TEST(test_stepper_setup_success);
    test_broken_internal_auto_enable();

    UNITY_END();
}

void loop(void) {}