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
P 850 7700
F 0 "N2" H 850 7800 60  0000 C CNN
F 1 "V20180826" H 850 7700 60  0000 C CNN
F 2 "SquantorLabels:Label_version" H 850 7700 60  0001 C CNN
F 3 "" H 850 7700 60  0001 C CNN
	1    850  7700
	1    0    0    -1  
$EndComp
$Comp
L SquantorLabels:OHWLOGO N1
U 1 1 5A135869
P 850 7350
F 0 "N1" H 850 7500 60  0000 C CNN
F 1 "OHWLOGO" H 850 7200 60  0000 C CNN
F 2 "Symbols:OSHW-Symbol_6.7x6mm_SilkScreen" H 850 7350 60  0001 C CNN
F 3 "" H 850 7350 60  0001 C CNN
	1    850  7350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 5EBB1AC4
P 750 850
F 0 "J1" H 750 1150 50  0000 C CNN
F 1 "Conn_01x06" H 750 450 50  0000 C CNN
F 2 "Connector_JST:JST_PH_S6B-PH-K_1x06_P2.00mm_Horizontal" H 750 850 50  0001 C CNN
F 3 "~" H 750 850 50  0001 C CNN
	1    750  850 
	-1   0    0    -1  
$EndComp
Text Label 1000 850  0    50   ~ 0
VSS
Text Label 3000 950  0    50   ~ 0
VDD
Text Label 1000 650  0    50   ~ 0
VDD_BACKLIGHT
Text Label 1000 950  0    50   ~ 0
SDA
Text Label 1000 1050 0    50   ~ 0
SCL
Text Label 1000 1150 0    50   ~ 0
!INT
Wire Wire Line
	950  650  1000 650 
Wire Wire Line
	950  850  1000 850 
Wire Wire Line
	1000 950  950  950 
Wire Wire Line
	950  1050 1000 1050
Wire Wire Line
	1000 1150 950  1150
$Comp
L Device:Ferrite_Bead_Small FB1
U 1 1 5EBDBD2C
P 2750 950
F 0 "FB1" V 2700 850 50  0000 C CNN
F 1 "600" V 2800 1050 50  0000 C CNN
F 2 "SquantorRcl:L_0603" V 2680 950 50  0001 C CNN
F 3 "~" H 2750 950 50  0001 C CNN
	1    2750 950 
	0    1    1    0   
$EndComp
Text Label 2550 1150 2    50   ~ 0
VSS
Wire Wire Line
	2650 1150 2550 1150
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J?
U 1 1 5EBE0632
P 1050 1700
F 0 "J?" H 1100 2000 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 1050 1400 50  0000 C CNN
F 2 "SquantorConnectors:Header-0254-2X05-H010" H 1050 1700 50  0001 C CNN
F 3 "~" H 1050 1700 50  0001 C CNN
	1    1050 1700
	1    0    0    -1  
$EndComp
Text Label 850  2150 0    50   ~ 0
VSS
Wire Wire Line
	850  1500 800  1500
Wire Wire Line
	800  1500 800  1600
Wire Wire Line
	800  2150 850  2150
Wire Wire Line
	850  1900 800  1900
Connection ~ 800  1900
Wire Wire Line
	800  1900 800  2150
Wire Wire Line
	850  1800 800  1800
Connection ~ 800  1800
Wire Wire Line
	800  1800 800  1900
Wire Wire Line
	850  1700 800  1700
Connection ~ 800  1700
Wire Wire Line
	800  1700 800  1800
Wire Wire Line
	850  1600 800  1600
Connection ~ 800  1600
Wire Wire Line
	800  1600 800  1700
Text Label 1400 1500 0    50   ~ 0
VDD_BACKLIGHT
Wire Wire Line
	950  750  1000 750 
Text Label 1000 750  0    50   ~ 0
VDD_RAW
Text Label 1400 1600 0    50   ~ 0
VDD_RAW
Text Label 1400 1700 0    50   ~ 0
SDA
Text Label 1400 1800 0    50   ~ 0
SCL
Text Label 1400 1900 0    50   ~ 0
!INT
Wire Wire Line
	1350 1500 1400 1500
Wire Wire Line
	1400 1600 1350 1600
Wire Wire Line
	1350 1700 1400 1700
Wire Wire Line
	1400 1800 1350 1800
Wire Wire Line
	1350 1900 1400 1900
Text Label 2550 950  2    50   ~ 0
VDD_RAW
Wire Wire Line
	2650 950  2550 950 
Wire Wire Line
	2850 950  2950 950 
$Comp
L Device:C_Small C?
U 1 1 5EBF6E62
P 2750 1150
F 0 "C?" V 2700 1050 50  0000 C CNN
F 1 "10u" V 2800 1250 50  0000 C CNN
F 2 "SquantorRcl:C_0805" H 2750 1150 50  0001 C CNN
F 3 "~" H 2750 1150 50  0001 C CNN
	1    2750 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	2850 1150 2950 1150
Wire Wire Line
	2950 1150 2950 950 
Connection ~ 2950 950 
Wire Wire Line
	2950 950  3000 950 
$EndSCHEMATC
