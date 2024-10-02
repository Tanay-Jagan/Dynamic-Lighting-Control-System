# Dynamic-Lighting-Control-System
Code Files for the Arduino Based Dynamic Lighting Control System I have developed. 
Files Include:
1. DC_LED_PWM_TEST - PWM based DC lighting regulation system
2. AC_Feasibility_Test - Phase shift based AC lighting regualtion system
3. AC_Power_Test - Modification of AC_Feasibility_Test to measure the power consumption of the bulb in relation to its brightness

All code files are in the .ino format

Experimental procedure details for AC_Power_Test:
The argument passed to the delayMicroseconds function on line 40was changed to take readings for different phase delays
