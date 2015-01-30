/****************************************************************************
 *
 *   Copyright (C) 2012-2013 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file drv_oreoled.h
 *
 * Oreo led device API
 */

#pragma once

#include <stdint.h>
#include <sys/ioctl.h>

/* more devices will be 1, 2, etc */
#define OREOLED_DEVICE_PATH "/dev/oreoled0"

/*
 * ioctl() definitions
 */

#define _OREOLEDIOCBASE		(0x2a00)
#define _OREOLEDIOC(_n)		(_IOC(_OREOLEDIOCBASE, _n))

/** set constant RGB values */
#define OREOLED_SET_RGB			_OREOLEDIOC(1)

/** run macro */
#define OREOLED_RUN_MACRO		_OREOLEDIOC(2)

/* Oreo LED driver supports up to 4 leds */
#define OREOLED_NUM_LEDS		4

/* instance of 0xff means apply to all instances */
#define OREOLED_ALL_INSTANCES	0xff

/* enum passed to OREOLED_SET_MODE ioctl()*/
enum oreoled_pattern {
	OREOLED_PATTERN_OFF,
	OREOLED_PATTERN_SINE,
	OREOLED_PATTERN_SOLID,
	OREOLED_PATTERN_SIREN,
	OREOLED_PATTERN_STROBE,
	OREOLED_PATTERN_FADEIN,
	OREOLED_PATTERN_FADEOUT,
	OREOLED_PATTERN_PARAMUPDATE,
	OREOLED_PATTERN_ENUM_COUNT
};

/* enum passed to OREOLED_SET_MODE ioctl()*/
enum oreoled_param {
	OREOLED_PARAM_BIAS_RED,
	OREOLED_PARAM_BIAS_GREEN,
	OREOLED_PARAM_BIAS_BLUE,
	OREOLED_PARAM_AMPLITUDE_RED,
	OREOLED_PARAM_AMPLITUDE_GREEN,
	OREOLED_PARAM_AMPLITUDE_BLUE,
	OREOLED_PARAM_PERIOD,
	OREOLED_PARAM_REPEAT,
	OREOLED_PARAM_PHASEOFFSET,
	OREOLED_PARAM_MACRO,
	OREOLED_PARAM_ENUM_COUNT
};

/* enum of available macros */
enum oreoled_macro {
	OREOLED_PARAM_MACRO_RESET,
	OREOLED_PARAM_MACRO_FWUPDATE,
	OREOLED_PARAM_MACRO_AUTOPILOT,
	OREOLED_PARAM_MACRO_CALIBRATE,
	OREOLED_PARAM_MACRO_POWERON,
	OREOLED_PARAM_MACRO_POWEROFF,
	OREOLED_PARAM_MACRO_RED,
	OREOLED_PARAM_MACRO_GREEN,
	OREOLED_PARAM_MACRO_BLUE,
	OREOLED_PARAM_MACRO_AMBER,
	OREOLED_PARAM_MACRO_WHITE,
	OREOLED_PARAM_MACRO_ENUM_COUNT
};

/* 
  structure passed to OREOLED_SET_RGB ioctl()
  Note that the driver scales the brightness to 0 to 255, regardless
  of the hardware scaling
 */
typedef struct {
	uint8_t instance;
	oreoled_pattern pattern;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} oreoled_rgbset_t;

/*
  structure passed to OREOLED_RUN_MACRO ioctl()
 */
typedef struct {
	uint8_t instance;
	oreoled_macro macro;
} oreoled_macrorun_t;