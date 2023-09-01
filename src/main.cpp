#include <Arduino.h>

#include "mock_external_digitalWrite.h"
#include "pins.h"

FastAccelStepperEngine engine;

FastAccelStepper* stepper = nullptr;

void setup() {
    Serial.begin(115200);
    Serial.println("Started.");

    pinMode((fake_external_enable_pin & ~PIN_EXTERNAL_FLAG), OUTPUT);
    pinMode(victim_pin_0, OUTPUT);
    digitalWrite(victim_pin_0, LOW);

    engine.init();
    engine.setExternalCallForPin(mock_external_digitalWrite);

    stepper = engine.stepperConnectToPin(step_pin);
    stepper->setEnablePin(fake_external_enable_pin);
    stepper->setAutoEnable(true);
    stepper->setAcceleration(5000);
}

void loop() {
    Serial.println("loop started.");
    stepper->setSpeedInHz(1000);
    stepper->runForward();
    vTaskDelay(2000);
    stepper->stopMove();
    while (stepper->isRunning())
        ;
    vTaskDelay(2000);
}
