IN
POP CX

PUSH 0
POP AX
PUSH 0
POP BX

FUNC:
PUSH AX
PUSH 1
ADD
POP AX
PUSH AX
PUSH 35
JE NEWSTR:
CONTINUE:
PUSH AX
PUSH 17
SUB
POP DX
PUSH DX 
PUSH DX
MUL
PUSH BX
PUSH 17
SUB
POP DX
PUSH DX
PUSH DX
MUL
ADD
PUSH CX
PUSH CX
MUL
JB CIRCLE:
PUSH AX
PUSH BX
MUL
PUSH 1225
JE FINISH:
JMP FUNC:

CIRCLE:
PUSH BX
PUSH 35
MUL
PUSH AX
ADD
POP DX
PUSH 3
POP [DX]
JMP FUNC:

NEWSTR:
PUSH 0
POP AX
PUSH BX
PUSH 1
ADD
POP BX
JMP CONTINUE:

FINISH:
DRAW
HLT


