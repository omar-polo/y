#ifndef I386_RTC_H
#define I386_RTC_H

#include "handler.h"

void rtc_init(uint32_t);

void irq_rtc(struct cpu_state);

#endif
