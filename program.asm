push 0
pop AX
7:
pushr AX
pushr AX
mul
out

pushr AX
push 1
add
pop AX

pushr AX 
push 10
jb 7:

hlt