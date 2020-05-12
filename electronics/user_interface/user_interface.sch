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
L Connector_Generic:Conn_01x06 J?
U 1 1 5EBB1AC4
P 700 1000
F 0 "J?" H 618 1417 50  0000 C CNN
F 1 "Conn_01x06" H 618 1326 50  0000 C CNN
F 2 "" H 700 1000 50  0001 C CNN
F 3 "~" H 700 1000 50  0001 C CNN
	1    700  1000
	-1   0    0    -1  
$EndComp
Text Label 950  1000 0    50   ~ 0
VSS
Text Label 950  900  0    50   ~ 0
VDD
Text Label 950  800  0    50   ~ 0
VDD_BACKLIGHT
Text Label 950  1100 0    50   ~ 0
SDA
Text Label 950  1200 0    50   ~ 0
SCL
Text Label 950  1300 0    50   ~ 0
!INT
Wire Wire Line
	900  800  950  800 
Wire Wire Line
	950  900  900  900 
Wire Wire Line
	900  1000 950  1000
Wire Wire Line
	950  1100 900  1100
Wire Wire Line
	900  1200 950  1200
Wire Wire Line
	950  1300 900  1300
$EndSCHEMATC
