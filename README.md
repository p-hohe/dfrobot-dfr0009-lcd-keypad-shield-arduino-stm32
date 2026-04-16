# dfrobot-dfr0009-lcd-keypad-shield-arduino-stm32
Example project demonstrating the DFRobot DFR0009 (1602 LCD Keypad Shield) on Arduino UNO and STM32 BL475E-IOT01A, including display control and button input.

# DFRobot DFR0009 LCD Keypad Shield – Arduino & STM32

## Overview

This repository contains example and test programs for the DFRobot DFR0009 (1602 LCD Keypad Shield).
The shield is tested on two platforms:

* Arduino UNO (Arduino IDE)
* STM32 BL475E-IOT01A (STM32CubeIDE)

The project demonstrates basic LCD output and button input using the analog keypad interface.

---

## Hardware

* DFRobot DFR0009 LCD Keypad Shield (1602 LCD)
* Arduino UNO
* STM32 BL475E-IOT01A

---

## Project Structure

* `/arduino` → Arduino IDE project (Arduino UNO)
* `/stm32` → STM32CubeIDE project (STM32 BL475E-IOT01A)

---

## Functionality

Both implementations provide:

* LCD initialization and text display
* Reading button inputs via analog values (ADC)
* Displaying button name and ADC value on the LCD

---

## Known Issue (STM32)

When using the STM32 board, there is a problem with the **SELECT button**:

* The SELECT button produces an ADC value very close to the **NONE state**
* Therefore, it cannot be reliably distinguished
* As a result, the SELECT button is **not detected correctly**

Measured ADC values (approx.):

* RIGHT: ~0
* UP: ~1220
* DOWN: ~2470
* LEFT: ~3790
* SELECT: ~4095
* NONE: ~4095

SELECT and NONE are effectively identical in this setup.

---

## Arduino UNO

The Arduino implementation works as expected:

* All buttons (including SELECT) are correctly detected
* No issues observed

---

## STM32 Implementation Details

The STM32 version uses:

* ADC (12-bit resolution)
* Averaging of multiple samples
* Threshold-based button detection
* Simple debouncing logic

Example of button mapping:

```c
if (adc < 200)   return BTN_RIGHT;
if (adc < 1800)  return BTN_UP;
if (adc < 3200)  return BTN_DOWN;
if (adc < 3800)  return BTN_LEFT;
if (adc < 4090)  return BTN_SELECT;
return BTN_NONE;
```

---

## Possible Cause

The issue with the SELECT button may be caused by:

* ADC reference differences between Arduino and STM32

---

## Notes

This repository is intended for testing, educational purposes, and basic hardware validation.
