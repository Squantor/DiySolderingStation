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
L SquantorPCBOutline:Drill_Hole_no_metal H?
U 1 1 5EBF62F7
P 1500 7550
F 0 "H?" H 1250 7650 60  0000 L CNN
F 1 "M3" H 1650 7450 60  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 1500 7550 60  0001 C CNN
F 3 "" H 1500 7550 60  0001 C CNN
	1    1500 7550
	1    0    0    -1  
$EndComp
$Comp
L SquantorPCBOutline:Drill_Hole_no_metal H?
U 1 1 5EBF718B
P 1500 7200
F 0 "H?" H 1250 7300 60  0000 L CNN
F 1 "M3" H 1650 7100 60  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 1500 7200 60  0001 C CNN
F 3 "" H 1500 7200 60  0001 C CNN
	1    1500 7200
	1    0    0    -1  
$EndComp
$Comp
L SquantorPCBOutline:Drill_Hole_no_metal H?
U 1 1 5EBF7413
P 1950 7200
F 0 "H?" H 1700 7300 60  0000 L CNN
F 1 "M3" H 2100 7100 60  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 1950 7200 60  0001 C CNN
F 3 "" H 1950 7200 60  0001 C CNN
	1    1950 7200
	1    0    0    -1  
$EndComp
$Comp
L SquantorPCBOutline:Drill_Hole_no_metal H?
U 1 1 5EBF8235
P 1950 7550
F 0 "H?" H 1700 7650 60  0000 L CNN
F 1 "M3" H 2100 7450 60  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 1950 7550 60  0001 C CNN
F 3 "" H 1950 7550 60  0001 C CNN
	1    1950 7550
	1    0    0    -1  
$EndComp
$EndSCHEMATC
