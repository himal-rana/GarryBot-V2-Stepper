#ifndef DISPLAY_H
#define DISPLAY_H

void displayInit();
void displayShow(
    float angle,
    float kp,
    float ki,
    float kd,
    int motorOutput,
    int leftPWM,
    int rightPWM
);
#endif // DISPLAY_H
