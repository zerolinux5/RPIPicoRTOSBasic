#pragma once

class PWM {
    static const uint32_t clock = 125000000;

public:
    uint32_t pwm_get_wrap(uint slice_num);
    uint32_t pwm_set_freq(uint slice_num, uint chan, uint32_t f);
    uint32_t pwm_set_freq_duty(uint slice_num, uint chan, uint32_t f, int d);
    void pwm_set_duty(uint slice_num, uint chan, int d);
};