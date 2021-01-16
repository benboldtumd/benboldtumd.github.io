TIOS	EQU $40		;Input Capture / Output Compare Select
TCNT	EQU $44		;Free-Running Cunter
TSCR	EQU $46		;Timer Enable / Disable Register
TCTL1	EQU $48		; } Output Compare Port T Behavior Registers
TCTL2	EQU $49		; }
TMSK1	EQU $4C		;Output Compare Interrupt Enable
TFLG1	EQU $4E		;Output Compare Flags
TC0	EQU $50		;Timer 0 capture/compare register

PortT	EQU $240
DDRT	EQU $242
PortA	EQU $00
DDRA	EQU $02

TC0V	EQU $3E6E	;Timer Overflow Interrupt Vector 
STACK	EQU $1FFF	;Define Stack area 

; *******************
; * SUBROUTINE ZONE *
; *******************
	org $1000

OC0ISS:	LDAA #%00000001	; } Reset Compare Flag for next interrupt
	STAA TFLG1	; }

	LDD TC0
	ADDD Period
	STD TC0

	; START area to execute each interrupt

	LDX Pointer
	LDY Count
	INY
	STY Count
	EXG Y,D
	LSRD
	CPD 0,X
	BLT Exit

	COM PortA

	LDAA TCTL2
	EORA #%00000001
	STAA TCTL2
	CLR Count
	CLR Count+1

	LDX Pointer
	INX
	INX
	STX Pointer
	CPX PtEnd
	BLT Exit

	LDX PtStart
	STX Pointer

	; END area to execute each interrupt

Exit	RTI

; *************
; * DATA ZONE *
; *************
Button	FDB $0017, $0164, $0017, $00A3, $0017, $00A3
	FDB $0017, $0061
	FDB $0017, $0061
	FDB $0017, $0061
	FDB $0017, $00a3
	FDB $0017, $00A3, $0017, $00A3, $0017, $00A3, $0017, $00A3, $0017, $00A3, $0017, $00A3, $0017, $00A3, $0017, $00A3, $0017, $00A3, $0017, $00A3

Period	FDB $00CF	; Enter this number:  ($12C/$67)*code  $12C = 40 kHz
Count	FDB $0000
Pointer FDB $0000
PtStart FDB $0000
PtEnd	FDB $0000

; ****************
; * MAIN PROGRAM *
; ****************
	org $2000
	LDS #STACK	;initialize stack 

	LDD #OC0ISS	;starting address of interrupt service subroutine
	STD TC0V	;store in vector area

	LDAA #%00000001	; } Enable Output Compare 0
	STAA TIOS	; }

	LDAA #%10000000	; } Enable Timer
	STAA TSCR	; }

	LDAA #%00000001	; } Behavior of Port T Bit 0
	STAA TCTL2	; }

	LDAA #%00000001	; } Enable Interrupts form Output Compare 0
	STAA TMSK1	; }

	LDAA #$FF	;Program Port T as output
	STAA DDRT
	STAA DDRA

	COM PortA

	LDD #Button
	STD PtStart
	STD Pointer
	ADDD #$0044	; 4*(length of sequence)
	STD PtEnd

	CLI ;Enable Interrupts (enabled when cleared)

LOOP	BRA LOOP	; Wait for interrupt