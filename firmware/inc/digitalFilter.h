/****************************************************************************
 * digitalFilter.h
 * openacousticdevices.info
 * May 2022
 *****************************************************************************/

#ifndef __DIGITAL_FILTER_H
#define __DIGITAL_FILTER_H

#include <stdint.h>

/* Apply filters */

void DigitalFilter_reset();

void DigitalFilter_applyFilter(int16_t *source, int16_t *dest, uint32_t sampleRateDivider, uint32_t size);

/* Set filter constants */

void DigitalFilter_setAdditionalGain(float gain);

void DigitalFilter_setHighPassFilterConstants(float g, float c);

#endif /* __DIGITAL_FILTER_H */
