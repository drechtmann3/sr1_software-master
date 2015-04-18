
// Baud rate for motor controller, fastest we have tried:
#define NGMEV_BAUDRATE 19200 // bits/s

// Used when querying/setting registers, look in sci_funcs.c
#define NGMEV_VALUE_IN_RAM 1
#define NGMEV_VALUE_IN_EEPROM 0

// === RAM REGISTERS on the NGM EV C200===
// Unsigned Integers
#define SI_DESIREDSPEED 0x00 //*****IMPORTANT: The desired speed in dHz, for speed control mode.
#define SI_THRILIMIT 0x01 // Serial throttle current limit in (dA)
#define SI_BRKILIMIT 0x02 // Serial regen current limit in (dA)
#define SI_KP 0x03 // Proportional coefficient for speed control error squared term
#define SI_KI 0x04 // Integral coefficient for speed control error term
#define SI_KT 0x05 // Phase current to speed error speed control coefficient
#define SI_MAXSPEEDERROR 0x07// Speed error clamping value, dampens response to large step changes in the desired speed.
#define SI_PHASEIRAMP 0x09 // Ramp rate for serial phaseI input, deciA/(seconds/60).
					       // How fast serial input for current is set to actual current. Torque-control mode.
#define SI_SPEEDRAMP 0x0A // Ramp rate for serial speed input, deci-hz electrical/(seconds/15)
#define IN_DESIREDSPEED 0x0B // Desired speed set to motor, read only.
#define AM_SPEED 0x0C // ***IMPORTANT: Actual speed (deci-Hz) the motor is turning at. Absolute value. Read only. Works even when
					  // motor is disabled, but on.
#define SV_TARGETPHASEI 0x10 // Target current (dA) set to motor, read only.
#define SV_THERMALLIMITMOTOR 0x11 // Thermal motor current limit (dA)
#define SV_HEATSINKDERATING 0x12 // Heatsink thermal derating ratio
#define SV_MAXTHRI 0x13 // Current Maximum throttle current (dA), read only.
#define SV_MAXRGNI 0x14 // Maximum regen current (dA), read only.
#define AI_THR 0x17 // Discrete throttle in read from analog input, read only.
#define AM_RGN 0x18 // Discrete regen analog innput measurement value, read only.
#define IN_RGNILIMIT 0x1C // Discrete regen current limit I (dA)

// Signed Integers
#define SI_DESIREDPHASEI 0x60 //*****IMPORTANT: Serial phase current input (dA). Commanding 08! forces desired current to 0.
#define IN_DESIREDPHASEI 0x61 //***IMPORTANT: Desired phase current in (dA) the motor controller desires to be sent to the motor, read only. Best approximation of how much current motor is actually using.
#define AM_SUPPLYV 0x64 // Measured supply voltage (dV) of motor, read only.
#define AM_MOTORT 0x65 // Measured motor temp (degrees C * 10)
#define AM_HTSINKT 0x66 // Measured heatsink temp (degrees C * 10)
#define AM_SUPPLYI 0x67 // Measured logic supply current (mA) for motor *controller*, not actual motor.

// Unsigned bytes and Boolean
#define SI_MINFANSPEED 0x90 // Minimum fan speed (0-3)
#define SV_DRIVESTATE 0x96 //*****IMPORTANT: Operating status of controller, refer below for possible values.
#define BM_OBSERVEDDIR 0x97 // Observed direction of rotation
#define SV_FAULT1LATCH 0x98 // Latched values of below: (stored when controller is disabled).
#define SV_FAULT1 0x99 // Bit-coded fault indications that prevent operation
#define SV_FAULT2 0x9A // Bit-coded fault indications of sensor problems
#define SV_FAULT3 0x9B // Bit-coded fault indications of warnings
#define SV_FAULT4 0x9C // Bit-coded fault indications of current limiting
#define SV_FANSPEED 0x9D // Actual fan speed setting
#define IN_DISABLE 0x9E // Disable input, equal to [CB_DISABLE] | [BI_DISABLE] | wrong direction, read only.
#define IN_THRENABLE 0x9F // Throttle enable input, true when [CB_THRENABLE] AND [BI_THRENABLE], read only.
#define IN_FORWARD 0xA0 // Input direction seen by controller, read only.
#define SV_FORWARD 0xA1 // Actual operating direction
#define SV_SPEEDCONTROL 0xA2 // When true, speed control, read-only
#define BI_DISABLE 0xAA // State of digital disable input
#define BI_THRENABLE 0xAB // State of throttle enable input, from discrete interface, read only.
#define BI_FORWARD 0xAC // State of forward input
#define CB_DISABLE 0xAD // Serial disable input, set with a COMMAND! (00! clears CB_DISABLE, 01! sets CB_DISABLE).
#define CB_THRENABLE 0xAE // Serial throttle enable input (02! enables CB_THRENBLE, 03! clears it, forcing throttle input to 0).

// Unsigned Long Integers
#define NGMEV_PRODUCT 0xF8 // Returns product string // "EVC-200"
#define NGMEV_BUILD 0xF9 // Returns software build string // "Build xx"
#define NGMEV_BUILDDATE 0xFA // Returns build date string // "YYYYMMDD"






// === EEPROM REGISTERS on NGM EV C200 ===
// Unsigned Integers
#define CG_BAUDRATE 0x00 //***IMPORTANT: I/O baud rate. Fastest we have tested: 19200 bits per second
#define FS_ABSMINV 0x02 // Absolute minimum voltage for operation (dV)
#define CG_MINV 0x03 // Voltage at which max throttle current is zero (dV) We can't operate at below this voltage!
#define CG_MINVGUARD 0x04 // Voltage at which max throttle current limiting starts (dV), b/c voltage is too low.
#define CG_MAXVRGNGUARD 0x05 // High voltage cut-off start point for regen
#define CG_MAXVRGN 0x06 // Maximum voltage for regen
#define CG_MAXVGUARD 0x07 // Voltage at which max phase current limiting begins due to over voltage (dV)
#define CG_MAXV 0x08 // Voltage at which phase current is zero (dV), b/c voltage too high.
#define FS_ABSMAXVGUARD 0x09 // Voltage at absmaxthrI1 set point (dV)
#define FS_ABSMAXV 0x0A // Absolute maximum voltage for operation (dV)
#define FS_MINGUARDDELTA 0x0B // Minimum difference between minV and minVguard, also maxV
#define CG_MINFREQ 0x0C // Minimum commutation frequency for speed control
#define DF_KI 0x0D // Default value for SI_Ki, for speed control mode
#define DF_KP 0x0E // Default value for SI_Kp, for speed control mode
#define DF_KT 0x0F // Default value for SI_Kt, for speed control mode
#define DF_MAXSPDERROR 0x11 // Clamping value for speed error in speed control
#define SC_SUPPLYV 0x12 // Scale value for supply voltage
#define SC_SUPPLYI 0x13 // Scale value for supply current
#define FS_SCHTSINKT 0x15 // Scale value for heatsink temperature
#define CG_SCTHR_SPEED 0x16 // Scale value for throttle input into speed (speed control)
#define CG_SCTHR_TORQUE 0x17 // Scale value for throttle input into amps (torque control)
#define CG_SCRGN_TORQUE 0x18 // Scale value for regen input into amps
#define CG_SCMOTORT 0x1A // Scale value for motor temperature
#define CG_MAXMOTORI 0x1D //  Maximum motor current, throttle or regen (deci-Amps)
#define DF_PHASEIRAMP 0x1E // Default value for SI_PHASEIRAMP
#define DF_SPEEDRAMP 0x1F // Default value for SI_SPEEDRAMP
#define CG_SPEEDTHRESHOLD 0x21 // Safe speed for changing motor direction
#define CG_MINSUPPLYI 0x22 // Minimum supply current when fans are off
#define CG_MAXSUPPLYI 0x23 // Maximum supply current when fans are off
#define CG_MINFANSUPPLYI 0x24 // Minimum supply current when fans are on
#define CG_MAXFANSUPPLYI 0x25 // Maximum supply current when fans are on
#define CG_MAXTHRI0 0x36 // Maximum throttle current (dA)
#define CG_MAXTHRI1 0x37 // Maximum throttle current is between this and CG_MAXTHRI0 when AM_SUPPLYV is too high.
#define CG_MAXRGNI0 0x38 // Maximum regen current (dA)
#define CG_MAXRGNI1 0x39 // Current from which current is linearly derated whan AM_SUPPLYV is too high.
#define FS_ABSMAXTHRI0 0x3A // Factory set maximum value for [CG_maxthrI] (dA)
#define FS_ABSMAXTHRI1 0x3B // "
#define FS_ABSMAXRGNI0 0x3C // Factory set maximum value for [CG_maxrgnI] (dA)
#define FS_ABSMAXRGNI1 0x3D // "
#define CG_MOTORITCOEFF 0x3E // I^2t coefficient for estimating heatsink temp
#define FS_HSINKITCOEFF 0x3F // I^2t coefficient for estimating motor temp

// Signed Integers
#define FS_OFSUPPLYV 0x60 // Offset value for supply voltage
#define FS_OFSUPPLYI 0x61 // Offset value for supply current
#define CG_OFMOTORT 0x64 // Offset value for motor temp
//65-67 CG_FANTEMP[3] Temperature transition points for fan control
#define CG_DEFAULT_MOTORT 0x71 // Assumed motor temp when sensor fails
//72-75 CG_TLIMTMTR[3] Motor Temperature transition points (deci-Celsius)
//7C-7D CG_TLIMIMTR[2] 0-256 % of current at the corresponding Temp. Implied denominator of 256

// Unsigned bytes and Boolean
#define CG_ECHO 0x90 //*IMPORTANT: When true, echo characters as they are received
#define CG_TEXTERRORS 0x91 // When true, send text messages for errors, else send two digit codes
#define CG_LINEFEEDS 0x92 // When true, use CR-LF combinations at end of lines
#define CG_MAXSCIIDLE 0x93 // Maximum idle time for serial interface watchdog fault in tenths of a second, 0 disables
#define CG_60DEGREEHALLS 0x95 // When true, assume hall-effect sensor are 60 electrical degrees apart
#define CG_INVERTDIR 0x97 // When true, reverse definition of forward
#define DF_SPEEDCONTROL 0x98 //**IMPORTANT: When true, power-up in speed control mode
#define CG_ENDISCRETE_THR 0x99 //*****IMPORTANT: When true, use discrete throttle and regen inputs. We do NOT want this, due to EMI! Everything must be serial!
#define CG_ENDISCRETE_DIR 0x9B //*****IMPORTANT: When true, use discrete direction input
#define CG_ENDISCRETE_THRENABLE 0x9C //*****IMPORTANT: When true, use discrete throttle enable input
#define CG_ENDISCRETE_DISABLE 0x9D //*****IMPORTANT: When true, use discrete disable input
#define CG_THRDEADBAND 0x9E // Offset (in counts) of throttle input
#define CG_RGNDEADBAND 0x9F // Offset (in counts) of regen input
#define CG_GAPDEADBAND 0xA0 // Offset (in counts) of gap input (not used)
#define CG_RTSUPPLYV 0xA1 // Filtering level for supply voltage (0:none to 4:max)
#define CG_RTSUPPLYI 0xA2 // Filtering level for supply current measurement
#define CG_RTHSINKT 0xA4 // Filtering level for heatsink temp measurement
#define CG_RTHTR 0xA5 // Filtering level for throttle input
#define CG_RTRGN 0xA6 // Filtering level for regen input
#define CG_RTMOTORT 0xA8 // Filtering level for motor temp measurement
#define CG_SOFTSTARTN 0xA9 // Speed of softstart operation (0:fastest ramp to 7:slowest ramp)
#define CG_NAUTORESETS 0xAA // Number of automatic reset attempts in four seconds
#define CG_MOTORTIMEC 0xB9 // Thermal time constant coefficient for motor
#define FS_HSINKTIMEC 0xBA // Thermal time constant coefficient for heatsink
#define CG_AISPDTOPWMFREQMULT 0xBB // Sets threshold for detecting max torque production

// Unsigned Longs
#define CG_SPDNUMERATOR 0xF0 // Numerator used for speed calculation


// Drive State Values
#define DS_POWERUP 32 // Initial state
//33-62 Powering up
#define DS_POWERUPEND 63 // Power-up period over
#define DS_SHUTDOWN 64 // Stopped and disabled
#define DS_DISABLECOAST 65 // Disabled but not stopped
#define DS_INTERLOCK 66 // Type 1 fault detected, waiting for disable command
#define DS_INTERLOCKCOAST 67 // Type 1 fault detected, waiting for disable command, not stopped
#define DS_STOPPED 74 // Enabled but not moving or throttling
#define DS_COASTING 75 // Enabled and moving but not throttling
#define DS_NO_LONGER_THR 76 // Leaving DS_thr mode
#define DS_NO_LONGER_BRK 77 // Leaving DS_brk mode
#define DS_THR 78 // Throttling
#define DS_BRK 79 // Braking
#define DS_PROGRAM 1 // Shutdown with programming enabled
