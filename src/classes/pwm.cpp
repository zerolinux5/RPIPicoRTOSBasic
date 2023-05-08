// Pico
#include "hardware/clocks.h"
#include "hardware/pwm.h"

#include "pwm.hpp"

uint32_t PWM::pwm_get_wrap(uint slice_num) {
    valid_params_if(PWM, slice_num >= 0 && slice_num < NUM_PWM_SLICES);
    return pwm_hw->slice[slice_num].top;
}

uint32_t PWM::pwm_set_freq(uint slice_num, uint chan, uint32_t f) {
    uint32_t divider16 = clock / f / 4096 + (clock % (f * 4096) != 0);

    if (divider16 / 16 == 0) {
        divider16 = 16;
    }
    uint32_t wrap = clock * 16 / divider16 / f - 1;
    pwm_set_clkdiv_int_frac(slice_num, divider16 / 16, divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);
    return wrap;
}

void PWM::pwm_set_duty(uint slice_num, uint chan, int d) {
    pwm_set_chan_level(slice_num, chan, pwm_get_wrap(slice_num) * d / 100);
}

uint32_t PWM::pwm_set_freq_duty(uint slice_num, uint chan, uint32_t f, int d) {
    PWM::pwm_set_duty(slice_num, chan, d);
    uint32_t resolution = PWM::pwm_set_freq(slice_num, chan, f);
    return resolution;
}