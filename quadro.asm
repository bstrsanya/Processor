IN 
IN
IN 
POP CX
POP BX
POP AX

PUSH 0
PUSH AX
JE AX=0:

PUSH BX
PUSH BX
MUL
PUSH -4
PUSH AX
PUSH CX
MUL
MUL
SUB
POP DX

PUSH DX
PUSH 0
JA DX>0:

PUSH DX
PUSH 0
JE DX=0:

PUSH DX
PUSH 0
JB DX<0:

DX>0:
PUSH 0
PUSH BX
SUB
PUSH 0
PUSH DX
SQRT
SUB
ADD
PUSH 2
DIV
PUSH AX
DIV

PUSH 0
PUSH BX
SUB
PUSH DX
SQRT
ADD
PUSH 2
DIV
PUSH AX
DIV
OUT
OUT
HLT

DX=0:
PUSH 0
PUSH BX
SUB
PUSH 2
DIV
PUSH AX
DIV
OUT
HLT

DX<0:
PUSH 0
OUT
HLT

AX=0:
PUSH 0
PUSH BX
JE BX=0:
PUSH 0
PUSH CX
SUB
PUSH BX
DIV
OUT
HLT

BX=0:
PUSH 0
PUSH CX
JE CX=0:
PUSH 0
OUT
HLT

CX=0:
PUSH 666
OUT
HLT

