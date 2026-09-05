#ifndef PID_H
#define PID_H

class PID
{
public:
    PID(float kp, float ki, float kd);

    int compute(float error, float dt);

    void reset();
    void setGains(float kp, float ki, float kd);

    float getKp() const;
    float getKi() const;
    float getKd() const;

private:
    float kp;
    float ki;
    float kd;

    float integral;
    float previousError;
};

#endif