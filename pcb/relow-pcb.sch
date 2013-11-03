EESchema Schematic File Version 2
LIBS:power
LIBS:analog-ic
LIBS:avr-mcu
LIBS:bluegiga
LIBS:connector
LIBS:freescale-ic
LIBS:maxim-ic
LIBS:micrel-ic
LIBS:microchip-ic
LIBS:standard
LIBS:stmicro-mcu
LIBS:sharp-relay
LIBS:ti-ic
LIBS:relow-pcb-cache
EELAYER 27 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "reflow pcb"
Date "3 nov 2013"
Rev "0.1"
Comp "Wiley Cousins, LLC."
Comment1 "github.com/mcous/reflow"
Comment2 "shared under the terms of the Creative Commons Attribution Share-Alike 3.0 license"
Comment3 "open source hardware"
Comment4 ""
$EndDescr
$Comp
L 2PIN_FEMALE J?
U 1 1 52758308
P 4300 4150
F 0 "J?" H 4100 4100 60  0000 C CNN
F 1 "TOASTER" H 3950 4200 60  0000 C CNN
F 2 "~" H 4250 3950 60  0000 C CNN
F 3 "~" H 4250 3950 60  0000 C CNN
	1    4300 4150
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 4050 4100 4050
Wire Wire Line
	4100 4050 4100 4100
Wire Wire Line
	4100 4100 4200 4100
Wire Wire Line
	4200 4200 4100 4200
Wire Wire Line
	4100 4200 4100 4250
Wire Wire Line
	4100 4250 4000 4250
$Comp
L AD849X IC?
U 1 1 5275D64C
P 7600 2900
F 0 "IC?" H 7400 3350 60  0000 C CNN
F 1 "AD8495" H 7650 2550 60  0000 C CNN
F 2 "" H 7600 2900 60  0000 C CNN
F 3 "" H 7400 3350 60  0000 C CNN
F 4 "Analog Devices" H 7500 3450 60  0001 C CNN "Manufacturer"
F 5 "AD8495ARMZ" H 7600 3550 60  0001 C CNN "Part"
	1    7600 2900
	1    0    0    -1  
$EndComp
$Comp
L SX12S01 K?
U 1 1 5275D7C5
P 3600 4150
F 0 "K?" H 3400 4350 60  0000 C CNN
F 1 "S212S01" H 3600 3950 60  0000 C CNN
F 2 "~" H 3600 4150 60  0000 C CNN
F 3 "~" H 3600 4150 60  0000 C CNN
F 4 "Sharp Microelectronics" H 3600 3750 60  0001 C CNN "Manufacturer"
F 5 "S212S01F" H 3600 3850 60  0001 C CNN "Part"
	1    3600 4150
	1    0    0    -1  
$EndComp
$Comp
L THERMOCOUPLE TC?
U 1 1 5275D8BF
P 5700 3050
F 0 "TC?" H 5400 3100 60  0000 C CNN
F 1 "THERMOCOUPLE" H 5150 3000 60  0000 C CNN
F 2 "" H 5700 3050 60  0000 C CNN
F 3 "" H 5700 3050 60  0000 C CNN
	1    5700 3050
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5275E0D8
P 7100 2700
F 0 "C?" V 7400 2800 60  0000 C CNN
F 1 "0.1uF" V 7300 2800 60  0000 C CNN
F 2 "~" H 7100 2700 60  0000 C CNN
F 3 "~" H 7100 2700 60  0000 C CNN
	1    7100 2700
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 5275E114
P 6950 3050
F 0 "C?" V 6750 3000 60  0000 C CNN
F 1 "10uF" V 6650 3000 60  0000 C CNN
F 2 "~" H 6950 3050 60  0000 C CNN
F 3 "~" H 6950 3050 60  0000 C CNN
	1    6950 3050
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 5275E141
P 6650 2900
F 0 "C?" V 6800 3050 60  0000 C CNN
F 1 "1uF" V 6700 3050 60  0000 C CNN
F 2 "~" H 6650 2900 60  0000 C CNN
F 3 "~" H 6650 2900 60  0000 C CNN
	1    6650 2900
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 5275E1AA
P 6650 3200
F 0 "C?" V 6650 3350 60  0000 C CNN
F 1 "1uF" V 6550 3350 60  0000 C CNN
F 2 "~" H 6650 3200 60  0000 C CNN
F 3 "~" H 6650 3200 60  0000 C CNN
	1    6650 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7200 3000 7100 3000
Wire Wire Line
	7100 3000 7100 2950
Wire Wire Line
	7100 2950 6800 2950
Wire Wire Line
	6800 3150 7100 3150
Wire Wire Line
	7100 3150 7100 3100
Wire Wire Line
	7100 3100 7200 3100
Wire Wire Line
	6800 2950 6800 3000
Connection ~ 6950 2950
Wire Wire Line
	6800 3100 6800 3150
Connection ~ 6950 3150
Wire Wire Line
	6450 3100 6800 3100
Wire Wire Line
	6800 3000 6450 3000
$Comp
L R R?
U 1 1 5275E282
P 6300 3000
F 0 "R?" H 6200 3200 60  0000 C CNN
F 1 "4.7kΩ" H 6200 3100 60  0000 C CNN
F 2 "~" H 6300 3000 60  0000 C CNN
F 3 "~" H 6300 3000 60  0000 C CNN
	1    6300 3000
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5275E291
P 6300 3100
F 0 "R?" H 6200 3000 60  0000 C CNN
F 1 "4.7kΩ" H 6200 2900 60  0000 C CNN
F 2 "~" H 6300 3100 60  0000 C CNN
F 3 "~" H 6300 3100 60  0000 C CNN
	1    6300 3100
	1    0    0    -1  
$EndComp
Connection ~ 6650 3000
Connection ~ 6650 3100
Wire Wire Line
	5850 3000 6150 3000
Wire Wire Line
	5850 3100 6150 3100
$Comp
L GND #PWR?
U 1 1 5275E38B
P 6650 3400
F 0 "#PWR?" H 6650 3400 30  0001 C CNN
F 1 "GND" H 6650 3330 30  0001 C CNN
F 2 "" H 6650 3400 60  0000 C CNN
F 3 "" H 6650 3400 60  0000 C CNN
	1    6650 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 3400 6650 3300
$Comp
L GND #PWR?
U 1 1 5275E3B1
P 6650 2700
F 0 "#PWR?" H 6650 2700 30  0001 C CNN
F 1 "GND" H 6650 2630 30  0001 C CNN
F 2 "" H 6650 2700 60  0000 C CNN
F 3 "" H 6650 2700 60  0000 C CNN
	1    6650 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	6650 2700 6650 2800
$Comp
L R R?
U 1 1 5275E3E2
P 5950 3250
F 0 "R?" V 5950 3400 60  0000 C CNN
F 1 "1MΩ" V 5850 3450 60  0000 C CNN
F 2 "~" H 5950 3250 60  0000 C CNN
F 3 "~" H 5950 3250 60  0000 C CNN
	1    5950 3250
	0    -1   -1   0   
$EndComp
Connection ~ 5950 3100
$Comp
L GND #PWR?
U 1 1 5275E4C0
P 5950 3500
F 0 "#PWR?" H 5950 3500 30  0001 C CNN
F 1 "GND" H 5950 3430 30  0001 C CNN
F 2 "" H 5950 3500 60  0000 C CNN
F 3 "" H 5950 3500 60  0000 C CNN
	1    5950 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3500 5950 3400
$Comp
L GND #PWR?
U 1 1 5275E4E9
P 6950 2800
F 0 "#PWR?" H 6950 2800 30  0001 C CNN
F 1 "GND" H 6950 2730 30  0001 C CNN
F 2 "" H 6950 2800 60  0000 C CNN
F 3 "" H 6950 2800 60  0000 C CNN
	1    6950 2800
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR?
U 1 1 5275E4F8
P 6950 2600
F 0 "#PWR?" H 6950 2700 30  0001 C CNN
F 1 "VCC" H 6950 2700 30  0000 C CNN
F 2 "" H 6950 2600 60  0000 C CNN
F 3 "" H 6950 2600 60  0000 C CNN
	1    6950 2600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6950 2600 7200 2600
Connection ~ 7100 2600
Wire Wire Line
	6950 2800 7200 2800
Connection ~ 7100 2800
Text Label 8400 2600 2    60   ~ 0
TEMP
Wire Wire Line
	8400 2600 8000 2600
Wire Wire Line
	8000 2700 8100 2700
Wire Wire Line
	8100 2700 8100 2600
Connection ~ 8100 2600
$Comp
L GND #PWR?
U 1 1 5275E5BF
P 8100 2900
F 0 "#PWR?" H 8100 2900 30  0001 C CNN
F 1 "GND" H 8100 2830 30  0001 C CNN
F 2 "" H 8100 2900 60  0000 C CNN
F 3 "" H 8100 2900 60  0000 C CNN
	1    8100 2900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8100 2900 8000 2900
$EndSCHEMATC
