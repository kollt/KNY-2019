.586
.model flat, stdcall

includelib libucrt.lib
includelib kernel32.lib
includelib D:\KNY1-2019\Debug\Lib.lib

ShowInt PROTO : DWORD, : DWORD, : DWORD
ShowChar PROTO : DWORD, : DWORD
CharToInt PROTO : DWORD, : DWORD
ShowString PROTO : DWORD, : DWORD, : DWORD
ShowBool PROTO : DWORD, : DWORD
inv PROTO : DWORD
StringToInt PROTO : DWORD, : DWORD
translate PROTO : DWORD, : DWORD, : DWORD
cmpstr PROTO : DWORD, : DWORD
cmpuint PROTO : DWORD, : DWORD
ExitProcess PROTO : DWORD
stop PROTO
funcfa PROTO

.stack 4096

.const
L1 DWORD 44427295
systemL1 DWORD 10
L2 DWORD 4967295
systemL2 DWORD 10
L3 DWORD 429295
systemL3 DWORD 10

.data
fab DWORD 0
systemfab DWORD 10
genla DWORD 0
systemgenla DWORD 10
genlb DWORD 0
systemgenlb DWORD 10
genlc DWORD 0
systemgenlc DWORD 10

.CODE
funcfa PROC 
push L1
pop eax
mov fab,eax
push fab
pop eax
RET
funcfa ENDP

MAIN:
