[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[OPTIMIZE 1]
[OPTION 1]
[BITS 32]
	EXTERN	_e_vram
[FILE "func.c"]
[SECTION .text]
	GLOBAL	_mino_clear
_mino_clear:
	PUSH	EBP
	XOR	ECX,ECX
	MOV	EBP,ESP
	PUSH	ESI
	PUSH	EBX
	XOR	EBX,EBX
	MOV	ESI,DWORD [8+EBP]
L11:
	XOR	EDX,EDX
	LEA	EAX,DWORD [ESI+ECX*4]
L10:
	INC	EDX
	MOV	DWORD [EAX],0
	ADD	EAX,4
	CMP	EDX,11
	JLE	L10
	INC	EBX
	ADD	ECX,10
	CMP	EBX,9
	JLE	L11
	POP	EBX
	POP	ESI
	POP	EBP
	RET
	GLOBAL	_map_clear
_map_clear:
	PUSH	EBP
	XOR	ECX,ECX
	MOV	EBP,ESP
	PUSH	ESI
	PUSH	EBX
	XOR	EBX,EBX
	MOV	ESI,DWORD [8+EBP]
L26:
	XOR	EDX,EDX
	LEA	EAX,DWORD [ESI+ECX*4]
L25:
	INC	EDX
	MOV	DWORD [EAX],0
	ADD	EAX,4
	CMP	EDX,9
	JLE	L25
	INC	EBX
	ADD	ECX,10
	CMP	EBX,11
	JLE	L26
	POP	EBX
	POP	ESI
	POP	EBP
	RET
	GLOBAL	_putblock
_putblock:
	PUSH	EBP
	MOV	EBP,ESP
	PUSH	EDI
	PUSH	ESI
	PUSH	EBX
	PUSH	EDX
	IMUL	EAX,DWORD [8+EBP],10
	IMUL	ESI,DWORD [12+EBP],10
	LEA	EDX,DWORD [10+EAX]
	LEA	EBX,DWORD [11+EAX]
	ADD	EAX,20
	MOV	DWORD [-16+EBP],EDX
	CMP	EBX,EAX
	JGE	L44
L42:
	LEA	EDX,DWORD [1+ESI]
	LEA	EAX,DWORD [10+ESI]
	CMP	EDX,EAX
	JGE	L46
	MOV	EAX,EDX
	IMUL	EAX,EAX,320
	LEA	ECX,DWORD [EBX+EAX*1]
L41:
	CMP	EBX,199
	JG	L38
	MOV	EDI,DWORD [_e_vram]
	MOV	AL,BYTE [16+EBP]
	MOV	BYTE [ECX+EDI*1],AL
L38:
	INC	EDX
	LEA	EAX,DWORD [10+ESI]
	ADD	ECX,320
	CMP	EDX,EAX
	JL	L41
L46:
	MOV	EAX,DWORD [-16+EBP]
	INC	EBX
	ADD	EAX,10
	CMP	EBX,EAX
	JL	L42
L44:
	POP	EAX
	POP	EBX
	POP	ESI
	POP	EDI
	POP	EBP
	RET
	GLOBAL	_putmino
_putmino:
	PUSH	EBP
	MOV	EBP,ESP
	PUSH	EDI
	PUSH	ESI
	PUSH	EBX
	PUSH	ECX
	PUSH	ECX
	MOV	EDI,DWORD [8+EBP]
	MOV	DWORD [-16+EBP],0
	MOV	DWORD [-20+EBP],0
L57:
	MOV	EAX,DWORD [-20+EBP]
	XOR	ESI,ESI
	LEA	EBX,DWORD [EDI+EAX*4]
L56:
	MOV	EAX,DWORD [EBX]
	ADD	EBX,4
	IMUL	EAX,DWORD [480+EDI]
	PUSH	EAX
	MOV	EAX,DWORD [-16+EBP]
	ADD	EAX,DWORD [488+EDI]
	PUSH	EAX
	MOV	EAX,DWORD [484+EDI]
	ADD	EAX,ESI
	INC	ESI
	PUSH	EAX
	CALL	_putblock
	ADD	ESP,12
	CMP	ESI,2
	JLE	L56
	INC	DWORD [-16+EBP]
	ADD	DWORD [-20+EBP],10
	CMP	DWORD [-16+EBP],2
	JLE	L57
	LEA	ESP,DWORD [-12+EBP]
	POP	EBX
	POP	ESI
	POP	EDI
	POP	EBP
	RET
	GLOBAL	_putgrid
_putgrid:
	PUSH	EBP
	MOV	EBP,ESP
	PUSH	EDI
	PUSH	ESI
	XOR	EDI,EDI
	PUSH	EBX
	PUSH	ESI
	XOR	ESI,ESI
L74:
	XOR	EBX,EBX
L73:
	MOV	EAX,ESI
	MOV	ECX,10
	CDQ
	IDIV	ECX
	TEST	EDX,EDX
	JE	L72
	MOV	EAX,EBX
	CDQ
	IDIV	ECX
	TEST	EDX,EDX
	JNE	L69
L72:
	LEA	EAX,DWORD [EBX+EDI*1]
	ADD	EAX,DWORD [_e_vram]
	MOV	BYTE [10+EAX],7
L69:
	INC	EBX
	CMP	EBX,100
	JLE	L73
	INC	ESI
	ADD	EDI,320
	CMP	ESI,120
	JLE	L74
	POP	EBX
	POP	EBX
	POP	ESI
	POP	EDI
	POP	EBP
	RET
	GLOBAL	_putmap
_putmap:
	PUSH	EBP
	MOV	EBP,ESP
	PUSH	EDI
	PUSH	ESI
	PUSH	EBX
	PUSH	EDI
	XOR	EDI,EDI
	MOV	DWORD [-16+EBP],0
L89:
	MOV	EAX,DWORD [-16+EBP]
	MOV	EDX,DWORD [8+EBP]
	XOR	ESI,ESI
	LEA	EBX,DWORD [EDX+EAX*4]
L88:
	PUSH	DWORD [EBX]
	PUSH	EDI
	ADD	EBX,4
	PUSH	ESI
	INC	ESI
	CALL	_putblock
	ADD	ESP,12
	CMP	ESI,9
	JLE	L88
	INC	EDI
	ADD	DWORD [-16+EBP],10
	CMP	EDI,11
	JLE	L89
	LEA	ESP,DWORD [-12+EBP]
	POP	EBX
	POP	ESI
	POP	EDI
	POP	EBP
	RET
	GLOBAL	_judge_set
_judge_set:
	PUSH	EBP
	MOV	EDX,1
	MOV	EBP,ESP
	PUSH	EDI
	PUSH	ESI
	PUSH	EBX
	PUSH	EBX
	PUSH	EBX
	MOV	EDI,DWORD [12+EBP]
	MOV	ECX,DWORD [488+EDI]
	MOV	EAX,DWORD [504+EDI]
	ADD	EAX,ECX
	CMP	EAX,11
	JG	L94
	MOV	EDX,3
L105:
	DEC	EDX
	JNS	L105
	SAL	ECX,2
	XOR	EDX,EDX
	MOV	DWORD [-20+EBP],ECX
	XOR	ESI,ESI
L116:
	XOR	ECX,ECX
L115:
	LEA	EAX,DWORD [ECX+ESI*1]
	CMP	DWORD [EDI+EAX*4],1
	JE	L134
L112:
	INC	ECX
	CMP	ECX,3
	JLE	L115
	INC	EDX
	ADD	ESI,10
	ADD	DWORD [-20+EBP],4
	CMP	EDX,3
	JLE	L116
	XOR	EDX,EDX
L94:
	MOV	EAX,EDX
	POP	EDX
	POP	ECX
	POP	EBX
	POP	ESI
	POP	EDI
	POP	EBP
	RET
L134:
	CMP	DWORD [40+EDI+EAX*4],0
	JNE	L112
	MOV	EAX,DWORD [484+EDI]
	MOV	EBX,DWORD [8+EBP]
	ADD	EAX,ECX
	IMUL	EAX,EAX,40
	ADD	EAX,DWORD [-20+EBP]
	CMP	DWORD [40+EAX+EBX*1],1
	JNE	L112
	MOV	EDX,1
	JMP	L94
	GLOBAL	_rotate_mino
_rotate_mino:
	PUSH	EBP
	MOV	EBP,ESP
	MOV	ECX,DWORD [8+EBP]
	MOV	EAX,DWORD [480+ECX]
	DEC	EAX
	CMP	EAX,6
	JA	L135
	JMP	DWORD [L145+EAX*4]
[SECTION .data]
	ALIGNB	4
L145:
	DD	L142
	DD	L142
	DD	L135
	DD	L142
	DD	L142
	DD	L143
	DD	L142
[SECTION .text]
L142:
	MOV	EAX,DWORD [48+ECX]
	MOV	EDX,DWORD [40+ECX]
	MOV	DWORD [40+ECX],EAX
	MOV	EAX,DWORD [128+ECX]
	MOV	DWORD [48+ECX],EAX
	MOV	EAX,DWORD [120+ECX]
	MOV	DWORD [128+ECX],EAX
	MOV	DWORD [120+ECX],EDX
	MOV	EAX,DWORD [88+ECX]
	MOV	EDX,DWORD [44+ECX]
	MOV	DWORD [44+ECX],EAX
	MOV	EAX,DWORD [124+ECX]
	MOV	DWORD [88+ECX],EAX
	MOV	EAX,DWORD [80+ECX]
	MOV	DWORD [124+ECX],EAX
	MOV	DWORD [80+ECX],EDX
L135:
	POP	EBP
	RET
L143:
	MOV	EAX,DWORD [132+ECX]
	MOV	EDX,DWORD [12+ECX]
	MOV	DWORD [12+ECX],EAX
	MOV	DWORD [ECX],EDX
	MOV	EAX,DWORD [120+ECX]
	MOV	DWORD [120+ECX],EDX
	MOV	DWORD [132+ECX],EAX
	MOV	EDX,DWORD [52+ECX]
	MOV	EAX,DWORD [128+ECX]
	MOV	DWORD [4+ECX],EDX
	MOV	DWORD [52+ECX],EAX
	MOV	EAX,DWORD [80+ECX]
	MOV	DWORD [128+ECX],EAX
	MOV	DWORD [80+ECX],EDX
	MOV	EAX,DWORD [124+ECX]
	MOV	EDX,DWORD [92+ECX]
	MOV	DWORD [92+ECX],EAX
	MOV	DWORD [8+ECX],EDX
	MOV	EAX,DWORD [40+ECX]
	MOV	DWORD [40+ECX],EDX
	MOV	DWORD [124+ECX],EAX
	MOV	EDX,DWORD [48+ECX]
	MOV	EAX,DWORD [88+ECX]
	MOV	DWORD [44+ECX],EDX
	MOV	DWORD [48+ECX],EAX
	MOV	EAX,DWORD [84+ECX]
	MOV	DWORD [88+ECX],EAX
	MOV	DWORD [84+ECX],EDX
	JMP	L135
	GLOBAL	_mino_o
_mino_o:
	PUSH	EBP
	MOV	EBP,ESP
	MOV	EAX,DWORD [8+EBP]
	MOV	DWORD [480+EAX],3
	MOV	DWORD [44+EAX],1
	MOV	DWORD [48+EAX],1
	MOV	DWORD [84+EAX],1
	MOV	DWORD [88+EAX],1
	MOV	DWORD [492+EAX],1
	MOV	DWORD [496+EAX],1
	MOV	DWORD [500+EAX],2
	MOV	DWORD [504+EAX],2
	POP	EBP
	RET
	GLOBAL	_mino_t
_mino_t:
	PUSH	EBP
	MOV	EBP,ESP
	MOV	EAX,DWORD [8+EBP]
	MOV	DWORD [480+EAX],5
	MOV	DWORD [4+EAX],1
	MOV	DWORD [40+EAX],1
	MOV	DWORD [44+EAX],1
	MOV	DWORD [48+EAX],1
	MOV	DWORD [492+EAX],0
	MOV	DWORD [496+EAX],1
	MOV	DWORD [500+EAX],2
	MOV	DWORD [504+EAX],2
	POP	EBP
	RET
