
.586
	.model flat, stdcall
	ExitProcess PROTO :DWORD

funcfs PROTO:DWORD, :DWORD 

.stack 4096

.const
L1 DWORD 1

.data
fsc DWORD 0
fsd DWORD 0
.CODE
funcfs PROC fsa:DWORD,fsb :DWORD 
mov fsd,1
mov eax,fsb
and eax,fsa
or eax,fsd
mov fsc,eax
mov eax,fsa
and eax,fsc
mov fsd,eax
mov eax,fsa
or eax,fsd
mov fsb,eax
RET
funcfs ENDP
