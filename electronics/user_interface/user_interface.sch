EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SquantorLabels:VYYYYMMDD N2
U 1 1 5A1357A5
P 900 7650
F 0 "N2" H 900 7750 60  0000 C CNN
F 1 "V20200514" H 900 7650 60  0000 C CNN
F 2 "SquantorLabels:Label_version" H 900 7650 60  0001 C CNN
F 3 "" H 900 7650 60  0001 C CNN
	1    900  7650
	1    0    0    -1  
$EndComp
$Comp
L SquantorLabels:OHWLOGO N1
U 1 1 5A135869
P 900 7300
F 0 "N1" H 900 7450 60  0000 C CNN
F 1 "OHWLOGO" H 900 7150 60  0000 C CNN
F 2 "Symbols:OSHW-Symbol_6.7x6mm_SilkScreen" H 900 7300 60  0001 C CNN
F 3 "" H 900 7300 60  0001 C CNN
	1    900  7300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 5EBB1AC4
P 1100 1000
F 0 "J1" H 1100 1300 50  0000 C CNN
F 1 "Conn_01x06" H 1100 600 50  0000 C CNN
F 2 "Connector_JST:JST_PH_S6B-PH-K_1x06_P2.00mm_Horizontal" H 1100 1000 50  0001 C CNN
F 3 "~" H 1100 1000 50  0001 C CNN
	1    1100 1000
	-1   0    0    -1  
$EndComp
Text Label 3000 1200 0    50   ~ 0
VDD
Text Label 1350 800  0    50   ~ 0
VDD_BACKLIGHT
Wire Wire Line
	1300 800  1350 800 
Wire Wire Line
	1300 1000 1350 1000
Wire Wire Line
	1350 1100 1300 1100
Wire Wire Line
	1300 1200 1350 1200
Wire Wire Line
	1350 1300 1300 1300
$Comp
L Device:Ferrite_Bead_Small FB1
U 1 1 5EBDBD2C
P 2750 1200
F 0 "FB1" V 2700 1100 50  0000 C CNN
F 1 "600" V 2800 1300 50  0000 C CNN
F 2 "SquantorRcl:L_0603" V 2680 1200 50  0001 C CNN
F 3 "~" H 2750 1200 50  0001 C CNN
	1    2750 1200
	0    1    1    0   
$EndComp
Text Label 2550 1400 2    50   ~ 0
VSS
Wire Wire Line
	2650 1400 2550 1400
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J2
U 1 1 5EBE0632
P 1050 1850
F 0 "J2" H 1100 2150 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 1050 1550 50  0000 C CNN
F 2 "SquantorConnectors:Header-0254-2X05-H010" H 1050 1850 50  0001 C CNN
F 3 "~" H 1050 1850 50  0001 C CNN
	1    1050 1850
	1    0    0    -1  
$EndComp
Text Label 850  2300 0    50   ~ 0
VSS
Wire Wire Line
	850  1650 800  1650
Wire Wire Line
	800  1650 800  1750
Wire Wire Line
	800  2300 850  2300
Wire Wire Line
	850  2050 800  2050
Connection ~ 800  2050
Wire Wire Line
	800  2050 800  2300
Wire Wire Line
	850  1950 800  1950
Connection ~ 800  1950
Wire Wire Line
	800  1950 800  2050
Wire Wire Line
	850  1850 800  1850
Connection ~ 800  1850
Wire Wire Line
	800  1850 800  1950
Wire Wire Line
	850  1750 800  1750
Connection ~ 800  1750
Wire Wire Line
	800  1750 800  1850
Text Label 1400 1650 0    50   ~ 0
VDD_BACKLIGHT
Wire Wire Line
	1300 900  1350 900 
Text Label 1350 900  0    50   ~ 0
VDD_RAW
Text Label 1400 1750 0    50   ~ 0
VDD_RAW
Text Label 1400 1850 0    50   ~ 0
SDA_RAW
Text Label 1400 1950 0    50   ~ 0
SCL_RAW
Text Label 1400 2050 0    50   ~ 0
!INT_RAW
Wire Wire Line
	1350 1650 1400 1650
Wire Wire Line
	1400 1750 1350 1750
Wire Wire Line
	1350 1850 1400 1850
Wire Wire Line
	1400 1950 1350 1950
Wire Wire Line
	1350 2050 1400 2050
Text Label 2550 1200 2    50   ~ 0
VDD_RAW
Wire Wire Line
	2650 1200 2550 1200
Wire Wire Line
	2850 1200 2950 1200
$Comp
L Device:C_Small C1
U 1 1 5EBF6E62
P 2750 1400
F 0 "C1" V 2700 1300 50  0000 C CNN
F 1 "10u" V 2800 1500 50  0000 C CNN
F 2 "SquantorRcl:C_0603" H 2750 1400 50  0001 C CNN
F 3 "~" H 2750 1400 50  0001 C CNN
	1    2750 1400
	0    1    1    0   
$EndComp
Wire Wire Line
	2850 1400 2950 1400
Wire Wire Line
	2950 1400 2950 1200
Connection ~ 2950 1200
Wire Wire Line
	2950 1200 3000 1200
Text Label 2550 1600 2    50   ~ 0
VDD
Text Label 2950 1600 0    50   ~ 0
!INT
$Comp
L Device:R R1
U 1 1 5EC0908F
P 2750 1600
F 0 "R1" V 2700 1450 50  0000 C CNN
F 1 "4.7K" V 2750 1600 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 2680 1600 50  0001 C CNN
F 3 "~" H 2750 1600 50  0001 C CNN
	1    2750 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 1600 2600 1600
Wire Wire Line
	2900 1600 2950 1600
$Comp
L SquantorNxp:PCF8574 U1
U 1 1 5EC0DA0B
P 4550 1400
F 0 "U1" H 4550 1850 50  0000 C CNN
F 1 "PCF8574" H 4550 850 50  0000 C CNN
F 2 "SquantorIC:SOT162-1-NXP" H 4580 1550 20  0001 C CNN
F 3 "" H 4550 1400 60  0000 C CNN
	1    4550 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5EC0FAF3
P 4550 800
F 0 "C2" V 4500 700 50  0000 C CNN
F 1 "1u" V 4600 900 50  0000 C CNN
F 2 "SquantorRcl:C_0603" H 4550 800 50  0001 C CNN
F 3 "~" H 4550 800 50  0001 C CNN
	1    4550 800 
	0    1    1    0   
$EndComp
Text Label 4200 1800 2    50   ~ 0
VSS
Text Label 4900 1100 0    50   ~ 0
VDD
Text Label 4400 800  2    50   ~ 0
VSS
Text Label 4700 800  0    50   ~ 0
VDD
Wire Wire Line
	4400 800  4450 800 
Wire Wire Line
	4650 800  4700 800 
Wire Wire Line
	4200 1800 4250 1800
Wire Wire Line
	4850 1100 4900 1100
Text Label 4900 1200 0    50   ~ 0
SDA
Text Label 4900 1300 0    50   ~ 0
SCL
Text Label 4900 1400 0    50   ~ 0
!INT
Text Label 1350 1000 0    50   ~ 0
VSS
Text Label 1350 1100 0    50   ~ 0
SDA_RAW
Text Label 1350 1200 0    50   ~ 0
SCL_RAW
Text Label 1350 1300 0    50   ~ 0
!INT_RAW
$Comp
L Device:R R2
U 1 1 5EC166A9
P 2750 1800
F 0 "R2" V 2700 1650 50  0000 C CNN
F 1 "100" V 2750 1800 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 2680 1800 50  0001 C CNN
F 3 "~" H 2750 1800 50  0001 C CNN
	1    2750 1800
	0    1    1    0   
$EndComp
Text Label 2550 1800 2    50   ~ 0
SDA_RAW
Text Label 2550 1900 2    50   ~ 0
SCL_RAW
Text Label 2550 2000 2    50   ~ 0
!INT_RAW
$Comp
L Device:R R3
U 1 1 5EC16E6A
P 2750 1900
F 0 "R3" V 2700 1750 50  0000 C CNN
F 1 "100" V 2750 1900 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 2680 1900 50  0001 C CNN
F 3 "~" H 2750 1900 50  0001 C CNN
	1    2750 1900
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5EC171A8
P 2750 2000
F 0 "R4" V 2700 1850 50  0000 C CNN
F 1 "100" V 2750 2000 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 2680 2000 50  0001 C CNN
F 3 "~" H 2750 2000 50  0001 C CNN
	1    2750 2000
	0    1    1    0   
$EndComp
Text Label 2950 1800 0    50   ~ 0
SDA
Text Label 2950 1900 0    50   ~ 0
SCL
Text Label 2950 2000 0    50   ~ 0
!INT
Wire Wire Line
	2550 1800 2600 1800
Wire Wire Line
	2600 1900 2550 1900
Wire Wire Line
	2550 2000 2600 2000
Wire Wire Line
	2900 1800 2950 1800
Wire Wire Line
	2950 1900 2900 1900
Wire Wire Line
	2900 2000 2950 2000
Wire Wire Line
	4850 1200 4900 1200
Wire Wire Line
	4900 1300 4850 1300
Wire Wire Line
	4850 1400 4900 1400
$Comp
L Device:R R5
U 1 1 5EC1E859
P 4050 1100
F 0 "R5" V 4000 950 50  0000 C CNN
F 1 "4.7K" V 4050 1100 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 3980 1100 50  0001 C CNN
F 3 "~" H 4050 1100 50  0001 C CNN
	1    4050 1100
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5EC1EF6C
P 4050 1200
F 0 "R6" V 4000 1050 50  0000 C CNN
F 1 "4.7K" V 4050 1200 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 3980 1200 50  0001 C CNN
F 3 "~" H 4050 1200 50  0001 C CNN
	1    4050 1200
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5EC1F275
P 4050 1300
F 0 "R7" V 4000 1150 50  0000 C CNN
F 1 "4.7K" V 4050 1300 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 3980 1300 50  0001 C CNN
F 3 "~" H 4050 1300 50  0001 C CNN
	1    4050 1300
	0    1    1    0   
$EndComp
Text Label 3800 1100 2    50   ~ 0
VSS
Wire Wire Line
	3800 1100 3850 1100
Wire Wire Line
	3900 1200 3850 1200
Wire Wire Line
	3850 1200 3850 1100
Connection ~ 3850 1100
Wire Wire Line
	3850 1100 3900 1100
Wire Wire Line
	3900 1300 3850 1300
Wire Wire Line
	3850 1300 3850 1200
Connection ~ 3850 1200
Wire Wire Line
	4200 1100 4250 1100
Wire Wire Line
	4250 1200 4200 1200
Wire Wire Line
	4200 1300 4250 1300
$Comp
L SquantorNxp:PCF8574 U2
U 1 1 5EC27FB3
P 4550 2800
F 0 "U2" H 4550 3250 50  0000 C CNN
F 1 "PCF8574" H 4550 2250 50  0000 C CNN
F 2 "SquantorIC:SOT162-1-NXP" H 4580 2950 20  0001 C CNN
F 3 "" H 4550 2800 60  0000 C CNN
	1    4550 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5EC27FBD
P 4550 2200
F 0 "C3" V 4500 2100 50  0000 C CNN
F 1 "1u" V 4600 2300 50  0000 C CNN
F 2 "SquantorRcl:C_0603" H 4550 2200 50  0001 C CNN
F 3 "~" H 4550 2200 50  0001 C CNN
	1    4550 2200
	0    1    1    0   
$EndComp
Text Label 4200 3200 2    50   ~ 0
VSS
Text Label 4900 2500 0    50   ~ 0
VDD
Text Label 4400 2200 2    50   ~ 0
VSS
Text Label 4700 2200 0    50   ~ 0
VDD
Wire Wire Line
	4400 2200 4450 2200
Wire Wire Line
	4650 2200 4700 2200
Wire Wire Line
	4200 3200 4250 3200
Wire Wire Line
	4850 2500 4900 2500
Text Label 4900 2600 0    50   ~ 0
SDA
Text Label 4900 2700 0    50   ~ 0
SCL
Text Label 4900 2800 0    50   ~ 0
!INT
Wire Wire Line
	4850 2600 4900 2600
Wire Wire Line
	4900 2700 4850 2700
Wire Wire Line
	4850 2800 4900 2800
$Comp
L Device:R R8
U 1 1 5EC27FD5
P 4050 2500
F 0 "R8" V 4000 2350 50  0000 C CNN
F 1 "4.7K" V 4050 2500 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 3980 2500 50  0001 C CNN
F 3 "~" H 4050 2500 50  0001 C CNN
	1    4050 2500
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 5EC27FDF
P 4050 2600
F 0 "R9" V 4000 2450 50  0000 C CNN
F 1 "4.7K" V 4050 2600 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 3980 2600 50  0001 C CNN
F 3 "~" H 4050 2600 50  0001 C CNN
	1    4050 2600
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 5EC27FE9
P 4050 2700
F 0 "R10" V 4000 2550 50  0000 C CNN
F 1 "4.7K" V 4050 2700 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 3980 2700 50  0001 C CNN
F 3 "~" H 4050 2700 50  0001 C CNN
	1    4050 2700
	0    1    1    0   
$EndComp
Text Label 3800 2600 2    50   ~ 0
VSS
Wire Wire Line
	3900 2600 3850 2600
Wire Wire Line
	3900 2700 3850 2700
Wire Wire Line
	3850 2700 3850 2600
Wire Wire Line
	4200 2500 4250 2500
Wire Wire Line
	4250 2600 4200 2600
Wire Wire Line
	4200 2700 4250 2700
Wire Wire Line
	3800 2600 3850 2600
Connection ~ 3850 2600
Text Label 3800 2500 2    50   ~ 0
VDD
Wire Wire Line
	3800 2500 3900 2500
$Comp
L SquantorPCBOutline:Drill_Hole_no_metal H2
U 1 1 5EBF62F7
P 1850 7550
F 0 "H2" H 1600 7650 60  0000 L CNN
F 1 "M3" H 2000 7450 60  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 1850 7550 60  0001 C CNN
F 3 "" H 1850 7550 60  0001 C CNN
	1    1850 7550
	1    0    0    -1  
$EndComp
$Comp
L SquantorPCBOutline:Drill_Hole_no_metal H1
U 1 1 5EBF718B
P 1450 7550
F 0 "H1" H 1200 7650 60  0000 L CNN
F 1 "M3" H 1600 7450 60  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 1450 7550 60  0001 C CNN
F 3 "" H 1450 7550 60  0001 C CNN
	1    1450 7550
	1    0    0    -1  
$EndComp
$Comp
L SquantorPCBOutline:Drill_Hole_no_metal H3
U 1 1 5EBF7413
P 2250 7550
F 0 "H3" H 2000 7650 60  0000 L CNN
F 1 "M3" H 2400 7450 60  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 2250 7550 60  0001 C CNN
F 3 "" H 2250 7550 60  0001 C CNN
	1    2250 7550
	1    0    0    -1  
$EndComp
$Comp
L SquantorPCBOutline:Drill_Hole_no_metal H4
U 1 1 5EBF8235
P 2650 7550
F 0 "H4" H 2400 7650 60  0000 L CNN
F 1 "M3" H 2800 7450 60  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 2650 7550 60  0001 C CNN
F 3 "" H 2650 7550 60  0001 C CNN
	1    2650 7550
	1    0    0    -1  
$EndComp
$Comp
L SquantorSwitches:2pin_tact_switch S1
U 1 1 5EC01DC3
P 1650 2650
F 0 "S1" H 1500 2750 60  0000 C CNN
F 1 "Cherry Blue" H 1650 2600 60  0000 C CNN
F 2 "MX_Only:MXOnly-1U-NoLED" H 1650 2650 60  0001 C CNN
F 3 "" H 1650 2650 60  0001 C CNN
	1    1650 2650
	1    0    0    -1  
$EndComp
Text Label 1350 2650 2    50   ~ 0
VSS
Wire Wire Line
	1350 2650 1400 2650
$Comp
L Device:R R12
U 1 1 5EC0EE14
P 2150 2850
F 0 "R12" V 2100 2700 50  0000 C CNN
F 1 "TBD" V 2150 2850 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 2080 2850 50  0001 C CNN
F 3 "~" H 2150 2850 50  0001 C CNN
	1    2150 2850
	0    1    1    0   
$EndComp
$Comp
L Device:R R11
U 1 1 5EC0F669
P 1650 2850
F 0 "R11" V 1600 2700 50  0000 C CNN
F 1 "TBD" V 1650 2850 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 1580 2850 50  0001 C CNN
F 3 "~" H 1650 2850 50  0001 C CNN
	1    1650 2850
	0    1    1    0   
$EndComp
Text Label 1350 2850 2    50   ~ 0
VDD
Wire Wire Line
	1350 2850 1500 2850
Wire Wire Line
	2000 2850 1950 2850
$Comp
L Device:C_Small C4
U 1 1 5EC166D4
P 2500 2850
F 0 "C4" V 2550 2950 50  0000 C CNN
F 1 "100n" V 2450 2700 50  0000 C CNN
F 2 "SquantorRcl:C_0603" H 2500 2850 50  0001 C CNN
F 3 "~" H 2500 2850 50  0001 C CNN
	1    2500 2850
	0    -1   -1   0   
$EndComp
Text Label 2650 2850 0    50   ~ 0
VSS
Wire Wire Line
	2300 2850 2350 2850
Wire Wire Line
	2350 2850 2400 2850
Wire Wire Line
	2600 2850 2650 2850
$Comp
L Device:D D1
U 1 1 5EC1C3D1
P 2150 2650
F 0 "D1" H 2050 2600 50  0000 C CNN
F 1 "RB521S-30" H 2150 2524 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 2150 2650 50  0001 C CNN
F 3 "~" H 2150 2650 50  0001 C CNN
	1    2150 2650
	-1   0    0    1   
$EndComp
Wire Wire Line
	1950 2850 1950 2650
Wire Wire Line
	1950 2650 2000 2650
Wire Wire Line
	2300 2650 2350 2650
Wire Wire Line
	2350 2650 2350 2850
Connection ~ 2350 2850
Text Label 2400 2650 0    50   ~ 0
Button_00
Wire Wire Line
	1900 2650 1950 2650
Connection ~ 1950 2650
Wire Wire Line
	1950 2850 1800 2850
Connection ~ 1950 2850
Text Label 3950 2800 2    50   ~ 0
Button_00
Text Label 3950 2900 2    50   ~ 0
Button_01
Text Label 3950 3000 2    50   ~ 0
Button_02
Text Label 3950 3100 2    50   ~ 0
Button_03
Wire Wire Line
	3950 2800 4250 2800
Wire Wire Line
	4250 2900 3950 2900
Wire Wire Line
	3950 3000 4250 3000
Wire Wire Line
	4250 3100 3950 3100
Wire Wire Line
	2400 2650 2350 2650
Connection ~ 2350 2650
$Comp
L SquantorSwitches:2pin_tact_switch S2
U 1 1 5EC685E5
P 1650 3300
F 0 "S2" H 1500 3400 60  0000 C CNN
F 1 "Cherry Blue" H 1650 3250 60  0000 C CNN
F 2 "MX_Only:MXOnly-1U-NoLED" H 1650 3300 60  0001 C CNN
F 3 "" H 1650 3300 60  0001 C CNN
	1    1650 3300
	1    0    0    -1  
$EndComp
Text Label 1350 3300 2    50   ~ 0
VSS
Wire Wire Line
	1350 3300 1400 3300
$Comp
L Device:R R16
U 1 1 5EC685F1
P 2150 3500
F 0 "R16" V 2100 3350 50  0000 C CNN
F 1 "TBD" V 2150 3500 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 2080 3500 50  0001 C CNN
F 3 "~" H 2150 3500 50  0001 C CNN
	1    2150 3500
	0    1    1    0   
$EndComp
$Comp
L Device:R R13
U 1 1 5EC685FB
P 1650 3500
F 0 "R13" V 1600 3350 50  0000 C CNN
F 1 "TBD" V 1650 3500 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 1580 3500 50  0001 C CNN
F 3 "~" H 1650 3500 50  0001 C CNN
	1    1650 3500
	0    1    1    0   
$EndComp
Text Label 1350 3500 2    50   ~ 0
VDD
Wire Wire Line
	1350 3500 1500 3500
Wire Wire Line
	2000 3500 1950 3500
$Comp
L Device:C_Small C5
U 1 1 5EC68608
P 2500 3500
F 0 "C5" V 2550 3600 50  0000 C CNN
F 1 "100n" V 2450 3350 50  0000 C CNN
F 2 "SquantorRcl:C_0603" H 2500 3500 50  0001 C CNN
F 3 "~" H 2500 3500 50  0001 C CNN
	1    2500 3500
	0    -1   -1   0   
$EndComp
Text Label 2650 3500 0    50   ~ 0
VSS
Wire Wire Line
	2300 3500 2350 3500
Wire Wire Line
	2350 3500 2400 3500
Wire Wire Line
	2600 3500 2650 3500
$Comp
L Device:D D2
U 1 1 5EC68616
P 2150 3300
F 0 "D2" H 2050 3250 50  0000 C CNN
F 1 "RB521S-30" H 2150 3174 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 2150 3300 50  0001 C CNN
F 3 "~" H 2150 3300 50  0001 C CNN
	1    2150 3300
	-1   0    0    1   
$EndComp
Wire Wire Line
	1950 3500 1950 3300
Wire Wire Line
	1950 3300 2000 3300
Wire Wire Line
	2300 3300 2350 3300
Wire Wire Line
	2350 3300 2350 3500
Connection ~ 2350 3500
Text Label 2400 3300 0    50   ~ 0
Button_01
Wire Wire Line
	1900 3300 1950 3300
Connection ~ 1950 3300
Wire Wire Line
	1950 3500 1800 3500
Connection ~ 1950 3500
Wire Wire Line
	2400 3300 2350 3300
Connection ~ 2350 3300
$Comp
L SquantorSwitches:2pin_tact_switch S3
U 1 1 5EC702DD
P 1650 3950
F 0 "S3" H 1500 4050 60  0000 C CNN
F 1 "Cherry Blue" H 1650 3900 60  0000 C CNN
F 2 "MX_Only:MXOnly-1U-NoLED" H 1650 3950 60  0001 C CNN
F 3 "" H 1650 3950 60  0001 C CNN
	1    1650 3950
	1    0    0    -1  
$EndComp
Text Label 1350 3950 2    50   ~ 0
VSS
Wire Wire Line
	1350 3950 1400 3950
$Comp
L Device:R R17
U 1 1 5EC702E9
P 2150 4150
F 0 "R17" V 2100 4000 50  0000 C CNN
F 1 "TBD" V 2150 4150 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 2080 4150 50  0001 C CNN
F 3 "~" H 2150 4150 50  0001 C CNN
	1    2150 4150
	0    1    1    0   
$EndComp
$Comp
L Device:R R14
U 1 1 5EC702F3
P 1650 4150
F 0 "R14" V 1600 4000 50  0000 C CNN
F 1 "TBD" V 1650 4150 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 1580 4150 50  0001 C CNN
F 3 "~" H 1650 4150 50  0001 C CNN
	1    1650 4150
	0    1    1    0   
$EndComp
Text Label 1350 4150 2    50   ~ 0
VDD
Wire Wire Line
	1350 4150 1500 4150
Wire Wire Line
	2000 4150 1950 4150
$Comp
L Device:C_Small C6
U 1 1 5EC70300
P 2500 4150
F 0 "C6" V 2550 4250 50  0000 C CNN
F 1 "100n" V 2450 4000 50  0000 C CNN
F 2 "SquantorRcl:C_0603" H 2500 4150 50  0001 C CNN
F 3 "~" H 2500 4150 50  0001 C CNN
	1    2500 4150
	0    -1   -1   0   
$EndComp
Text Label 2650 4150 0    50   ~ 0
VSS
Wire Wire Line
	2300 4150 2350 4150
Wire Wire Line
	2350 4150 2400 4150
Wire Wire Line
	2600 4150 2650 4150
$Comp
L Device:D D3
U 1 1 5EC7030E
P 2150 3950
F 0 "D3" H 2050 3900 50  0000 C CNN
F 1 "RB521S-30" H 2150 3824 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 2150 3950 50  0001 C CNN
F 3 "~" H 2150 3950 50  0001 C CNN
	1    2150 3950
	-1   0    0    1   
$EndComp
Wire Wire Line
	1950 4150 1950 3950
Wire Wire Line
	1950 3950 2000 3950
Wire Wire Line
	2300 3950 2350 3950
Wire Wire Line
	2350 3950 2350 4150
Connection ~ 2350 4150
Text Label 2400 3950 0    50   ~ 0
Button_02
Wire Wire Line
	1900 3950 1950 3950
Connection ~ 1950 3950
Wire Wire Line
	1950 4150 1800 4150
Connection ~ 1950 4150
Wire Wire Line
	2400 3950 2350 3950
Connection ~ 2350 3950
$Comp
L SquantorSwitches:2pin_tact_switch S4
U 1 1 5EC70324
P 1650 4600
F 0 "S4" H 1500 4700 60  0000 C CNN
F 1 "Cherry Blue" H 1650 4550 60  0000 C CNN
F 2 "MX_Only:MXOnly-1U-NoLED" H 1650 4600 60  0001 C CNN
F 3 "" H 1650 4600 60  0001 C CNN
	1    1650 4600
	1    0    0    -1  
$EndComp
Text Label 1350 4600 2    50   ~ 0
VSS
Wire Wire Line
	1350 4600 1400 4600
$Comp
L Device:R R18
U 1 1 5EC70330
P 2150 4800
F 0 "R18" V 2100 4650 50  0000 C CNN
F 1 "TBD" V 2150 4800 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 2080 4800 50  0001 C CNN
F 3 "~" H 2150 4800 50  0001 C CNN
	1    2150 4800
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 5EC7033A
P 1650 4800
F 0 "R15" V 1600 4650 50  0000 C CNN
F 1 "TBD" V 1650 4800 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 1580 4800 50  0001 C CNN
F 3 "~" H 1650 4800 50  0001 C CNN
	1    1650 4800
	0    1    1    0   
$EndComp
Text Label 1350 4800 2    50   ~ 0
VDD
Wire Wire Line
	1350 4800 1500 4800
Wire Wire Line
	2000 4800 1950 4800
$Comp
L Device:C_Small C7
U 1 1 5EC70347
P 2500 4800
F 0 "C7" V 2550 4900 50  0000 C CNN
F 1 "100n" V 2450 4650 50  0000 C CNN
F 2 "SquantorRcl:C_0603" H 2500 4800 50  0001 C CNN
F 3 "~" H 2500 4800 50  0001 C CNN
	1    2500 4800
	0    -1   -1   0   
$EndComp
Text Label 2650 4800 0    50   ~ 0
VSS
Wire Wire Line
	2300 4800 2350 4800
Wire Wire Line
	2350 4800 2400 4800
Wire Wire Line
	2600 4800 2650 4800
$Comp
L Device:D D4
U 1 1 5EC70355
P 2150 4600
F 0 "D4" H 2050 4550 50  0000 C CNN
F 1 "RB521S-30" H 2150 4474 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 2150 4600 50  0001 C CNN
F 3 "~" H 2150 4600 50  0001 C CNN
	1    2150 4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	1950 4800 1950 4600
Wire Wire Line
	1950 4600 2000 4600
Wire Wire Line
	2300 4600 2350 4600
Wire Wire Line
	2350 4600 2350 4800
Connection ~ 2350 4800
Text Label 2400 4600 0    50   ~ 0
Button_03
Wire Wire Line
	1900 4600 1950 4600
Connection ~ 1950 4600
Wire Wire Line
	1950 4800 1800 4800
Connection ~ 1950 4800
Wire Wire Line
	2400 4600 2350 4600
Connection ~ 2350 4600
$Comp
L Device:D_Zener D5
U 1 1 5ECC2688
P 1650 3000
F 0 "D5" H 1750 2950 50  0000 C CNN
F 1 "5V" H 1500 3050 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 1650 3000 50  0001 C CNN
F 3 "~" H 1650 3000 50  0001 C CNN
	1    1650 3000
	-1   0    0    1   
$EndComp
Text Label 1350 3000 2    50   ~ 0
VSS
Wire Wire Line
	1800 3000 1950 3000
Wire Wire Line
	1950 3000 1950 2850
Wire Wire Line
	1500 3000 1350 3000
$Comp
L Device:D_Zener D6
U 1 1 5ED07DE5
P 1650 3650
F 0 "D6" H 1750 3600 50  0000 C CNN
F 1 "5V" H 1500 3700 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 1650 3650 50  0001 C CNN
F 3 "~" H 1650 3650 50  0001 C CNN
	1    1650 3650
	-1   0    0    1   
$EndComp
Text Label 1350 3650 2    50   ~ 0
VSS
Wire Wire Line
	1800 3650 1950 3650
Wire Wire Line
	1950 3650 1950 3500
Wire Wire Line
	1500 3650 1350 3650
$Comp
L Device:D_Zener D7
U 1 1 5ED187C7
P 1650 4300
F 0 "D7" H 1750 4250 50  0000 C CNN
F 1 "5V" H 1500 4350 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 1650 4300 50  0001 C CNN
F 3 "~" H 1650 4300 50  0001 C CNN
	1    1650 4300
	-1   0    0    1   
$EndComp
Text Label 1350 4300 2    50   ~ 0
VSS
Wire Wire Line
	1800 4300 1950 4300
Wire Wire Line
	1950 4300 1950 4150
Wire Wire Line
	1500 4300 1350 4300
$Comp
L Device:D_Zener D8
U 1 1 5ED2BAE1
P 1650 4950
F 0 "D8" H 1750 4900 50  0000 C CNN
F 1 "5V" H 1500 5000 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 1650 4950 50  0001 C CNN
F 3 "~" H 1650 4950 50  0001 C CNN
	1    1650 4950
	-1   0    0    1   
$EndComp
Text Label 1350 4950 2    50   ~ 0
VSS
Wire Wire Line
	1800 4950 1950 4950
Wire Wire Line
	1950 4950 1950 4800
Wire Wire Line
	1500 4950 1350 4950
$Comp
L SquantorSwitches:Rotary_Encoder_Switch SW?
U 1 1 5EC17384
P 4200 6250
F 0 "SW?" V 4500 6100 50  0000 C CNN
F 1 "ALPS_EC11E18244A5" V 3700 6250 50  0000 C CNN
F 2 "SquantorSwitches:ALPS_EC11E_style5" V 4040 6100 50  0001 C CNN
F 3 "~" V 3940 6250 50  0001 C CNN
	1    4200 6250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4200 6550 4200 6650
Wire Wire Line
	4200 5950 4200 5900
Text Label 4200 5900 2    50   ~ 0
Rotary_shield
Text Label 4200 6650 0    50   ~ 0
Rotary_shield
Text Label 5900 5600 0    50   ~ 0
Rotary_shield
$Comp
L Device:D_Zener D?
U 1 1 5EC29DDE
P 5650 5500
F 0 "D?" H 5750 5450 50  0000 C CNN
F 1 "5V" H 5500 5550 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 5650 5500 50  0001 C CNN
F 3 "~" H 5650 5500 50  0001 C CNN
	1    5650 5500
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5EC2A428
P 5650 5700
F 0 "C?" V 5700 5800 50  0000 C CNN
F 1 "100n" V 5600 5550 50  0000 C CNN
F 2 "SquantorRcl:C_0603" H 5650 5700 50  0001 C CNN
F 3 "~" H 5650 5700 50  0001 C CNN
	1    5650 5700
	0    -1   -1   0   
$EndComp
Text Label 5400 5600 2    50   ~ 0
VSS
Wire Wire Line
	5550 5700 5450 5700
Wire Wire Line
	5450 5700 5450 5600
Wire Wire Line
	5450 5500 5500 5500
Wire Wire Line
	5750 5700 5850 5700
Wire Wire Line
	5850 5700 5850 5600
Wire Wire Line
	5850 5500 5800 5500
Wire Wire Line
	5900 5600 5850 5600
Connection ~ 5850 5600
Wire Wire Line
	5850 5600 5850 5500
Wire Wire Line
	5400 5600 5450 5600
Connection ~ 5450 5600
Wire Wire Line
	5450 5600 5450 5500
$Comp
L Device:R R?
U 1 1 5EC8BB23
P 2150 5450
F 0 "R?" V 2100 5300 50  0000 C CNN
F 1 "TBD" V 2150 5450 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 2080 5450 50  0001 C CNN
F 3 "~" H 2150 5450 50  0001 C CNN
	1    2150 5450
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5EC8BB2D
P 1650 5450
F 0 "R?" V 1600 5300 50  0000 C CNN
F 1 "TBD" V 1650 5450 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 1580 5450 50  0001 C CNN
F 3 "~" H 1650 5450 50  0001 C CNN
	1    1650 5450
	0    1    1    0   
$EndComp
Text Label 1350 5450 2    50   ~ 0
VDD
Wire Wire Line
	1350 5450 1500 5450
Wire Wire Line
	2000 5450 1950 5450
$Comp
L Device:C_Small C?
U 1 1 5EC8BB3A
P 2500 5450
F 0 "C?" V 2550 5550 50  0000 C CNN
F 1 "100n" V 2450 5300 50  0000 C CNN
F 2 "SquantorRcl:C_0603" H 2500 5450 50  0001 C CNN
F 3 "~" H 2500 5450 50  0001 C CNN
	1    2500 5450
	0    -1   -1   0   
$EndComp
Text Label 2650 5450 0    50   ~ 0
VSS
Wire Wire Line
	2300 5450 2350 5450
Wire Wire Line
	2350 5450 2400 5450
Wire Wire Line
	2600 5450 2650 5450
$Comp
L Device:D D?
U 1 1 5EC8BB48
P 2150 5250
F 0 "D?" H 2050 5200 50  0000 C CNN
F 1 "RB521S-30" H 2150 5124 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 2150 5250 50  0001 C CNN
F 3 "~" H 2150 5250 50  0001 C CNN
	1    2150 5250
	-1   0    0    1   
$EndComp
Wire Wire Line
	1950 5450 1950 5250
Wire Wire Line
	1950 5250 2000 5250
Wire Wire Line
	2300 5250 2350 5250
Wire Wire Line
	2350 5250 2350 5450
Connection ~ 2350 5450
Text Label 2400 5250 0    50   ~ 0
Rotary_push_filtered
Wire Wire Line
	1900 5250 1950 5250
Connection ~ 1950 5250
Wire Wire Line
	1950 5450 1800 5450
Connection ~ 1950 5450
Wire Wire Line
	2400 5250 2350 5250
Connection ~ 2350 5250
$Comp
L Device:D_Zener D?
U 1 1 5EC8BB5E
P 1650 5600
F 0 "D?" H 1750 5550 50  0000 C CNN
F 1 "5V" H 1500 5650 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 1650 5600 50  0001 C CNN
F 3 "~" H 1650 5600 50  0001 C CNN
	1    1650 5600
	-1   0    0    1   
$EndComp
Text Label 1350 5600 2    50   ~ 0
VSS
Wire Wire Line
	1800 5600 1950 5600
Wire Wire Line
	1950 5600 1950 5450
Wire Wire Line
	1500 5600 1350 5600
$Comp
L Device:R R?
U 1 1 5ECA5BE7
P 2150 6150
F 0 "R?" V 2100 6000 50  0000 C CNN
F 1 "TBD" V 2150 6150 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 2080 6150 50  0001 C CNN
F 3 "~" H 2150 6150 50  0001 C CNN
	1    2150 6150
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5ECA5BF1
P 1650 6150
F 0 "R?" V 1600 6000 50  0000 C CNN
F 1 "TBD" V 1650 6150 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 1580 6150 50  0001 C CNN
F 3 "~" H 1650 6150 50  0001 C CNN
	1    1650 6150
	0    1    1    0   
$EndComp
Text Label 1350 6150 2    50   ~ 0
VDD
Wire Wire Line
	1350 6150 1500 6150
Wire Wire Line
	2000 6150 1950 6150
$Comp
L Device:C_Small C?
U 1 1 5ECA5BFE
P 2500 6150
F 0 "C?" V 2550 6250 50  0000 C CNN
F 1 "100n" V 2450 6000 50  0000 C CNN
F 2 "SquantorRcl:C_0603" H 2500 6150 50  0001 C CNN
F 3 "~" H 2500 6150 50  0001 C CNN
	1    2500 6150
	0    -1   -1   0   
$EndComp
Text Label 2650 6150 0    50   ~ 0
VSS
Wire Wire Line
	2300 6150 2350 6150
Wire Wire Line
	2350 6150 2400 6150
Wire Wire Line
	2600 6150 2650 6150
$Comp
L Device:D D?
U 1 1 5ECA5C0C
P 2150 5950
F 0 "D?" H 2050 5900 50  0000 C CNN
F 1 "RB521S-30" H 2150 5824 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 2150 5950 50  0001 C CNN
F 3 "~" H 2150 5950 50  0001 C CNN
	1    2150 5950
	-1   0    0    1   
$EndComp
Wire Wire Line
	1950 6150 1950 5950
Wire Wire Line
	1950 5950 2000 5950
Wire Wire Line
	2300 5950 2350 5950
Wire Wire Line
	2350 5950 2350 6150
Connection ~ 2350 6150
Text Label 2400 5950 0    50   ~ 0
Button_03
Wire Wire Line
	1900 5950 1950 5950
Connection ~ 1950 5950
Wire Wire Line
	1950 6150 1800 6150
Connection ~ 1950 6150
Wire Wire Line
	2400 5950 2350 5950
Connection ~ 2350 5950
$Comp
L Device:D_Zener D?
U 1 1 5ECA5C22
P 1650 6300
F 0 "D?" H 1750 6250 50  0000 C CNN
F 1 "5V" H 1500 6350 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 1650 6300 50  0001 C CNN
F 3 "~" H 1650 6300 50  0001 C CNN
	1    1650 6300
	-1   0    0    1   
$EndComp
Text Label 1350 6300 2    50   ~ 0
VSS
Wire Wire Line
	1800 6300 1950 6300
Wire Wire Line
	1950 6300 1950 6150
Wire Wire Line
	1500 6300 1350 6300
$Comp
L Device:R R?
U 1 1 5ECA5C3C
P 2150 6800
F 0 "R?" V 2100 6650 50  0000 C CNN
F 1 "TBD" V 2150 6800 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 2080 6800 50  0001 C CNN
F 3 "~" H 2150 6800 50  0001 C CNN
	1    2150 6800
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5ECA5C46
P 1650 6800
F 0 "R?" V 1600 6650 50  0000 C CNN
F 1 "TBD" V 1650 6800 50  0000 C CNN
F 2 "SquantorRcl:R_0603_hand" V 1580 6800 50  0001 C CNN
F 3 "~" H 1650 6800 50  0001 C CNN
	1    1650 6800
	0    1    1    0   
$EndComp
Text Label 1350 6800 2    50   ~ 0
VDD
Wire Wire Line
	1350 6800 1500 6800
Wire Wire Line
	2000 6800 1950 6800
$Comp
L Device:C_Small C?
U 1 1 5ECA5C53
P 2500 6800
F 0 "C?" V 2550 6900 50  0000 C CNN
F 1 "100n" V 2450 6650 50  0000 C CNN
F 2 "SquantorRcl:C_0603" H 2500 6800 50  0001 C CNN
F 3 "~" H 2500 6800 50  0001 C CNN
	1    2500 6800
	0    -1   -1   0   
$EndComp
Text Label 2650 6800 0    50   ~ 0
VSS
Wire Wire Line
	2300 6800 2350 6800
Wire Wire Line
	2350 6800 2400 6800
Wire Wire Line
	2600 6800 2650 6800
$Comp
L Device:D D?
U 1 1 5ECA5C61
P 2150 6600
F 0 "D?" H 2050 6550 50  0000 C CNN
F 1 "RB521S-30" H 2150 6474 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 2150 6600 50  0001 C CNN
F 3 "~" H 2150 6600 50  0001 C CNN
	1    2150 6600
	-1   0    0    1   
$EndComp
Wire Wire Line
	1950 6800 1950 6600
Wire Wire Line
	1950 6600 2000 6600
Wire Wire Line
	2300 6600 2350 6600
Wire Wire Line
	2350 6600 2350 6800
Connection ~ 2350 6800
Text Label 2400 6600 0    50   ~ 0
Button_03
Wire Wire Line
	1900 6600 1950 6600
Connection ~ 1950 6600
Wire Wire Line
	1950 6800 1800 6800
Connection ~ 1950 6800
Wire Wire Line
	2400 6600 2350 6600
Connection ~ 2350 6600
$Comp
L Device:D_Zener D?
U 1 1 5ECA5C77
P 1650 6950
F 0 "D?" H 1750 6900 50  0000 C CNN
F 1 "5V" H 1500 7000 50  0000 C CNN
F 2 "SquantorDiodes:SOD-523" H 1650 6950 50  0001 C CNN
F 3 "~" H 1650 6950 50  0001 C CNN
	1    1650 6950
	-1   0    0    1   
$EndComp
Text Label 1350 6950 2    50   ~ 0
VSS
Wire Wire Line
	1800 6950 1950 6950
Wire Wire Line
	1950 6950 1950 6800
Wire Wire Line
	1500 6950 1350 6950
Text Label 4550 6250 0    50   ~ 0
VSS
Text Label 4900 2900 0    50   ~ 0
Rotary_push_filtered
Text Label 3850 6350 2    50   ~ 0
VSS
Text Label 3850 6150 2    50   ~ 0
Rotary_push
Wire Wire Line
	3850 6150 3900 6150
Wire Wire Line
	3900 6350 3850 6350
$EndSCHEMATC
