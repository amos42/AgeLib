;###################################################################
;-------------------------------------------------------------------
;
;                             AGE (Ver 1.0)
;                       (* =================== *)
;                           Amos Game Engine
;
; Author         : Chu, Kyong-min( Amos )
;
; Date           : 1997/02/08
; C Compiler     : WATCOM 10.5
; Assembler      : WASM 10.5
;
;-------------------------------------------------------------------
;###################################################################

.386
.model flat


.data


.code

;****************************
; 정수 Sqrt 함수를 구현한다.
; INT Sqrt( INT x )
;****************************
Sqrt_ proc
        push ebx
        push ecx
        push edx

        xor ecx, ecx
        mov ebx, 40000000h

LP1:
        mov edx, eax
        sub edx, ebx
        jl  LP2
        sub edx, ecx
        jl  LP2
        mov eax, edx
        shr ecx, 1
        or  ecx, ebx
        shr ebx, 2
        jnz LP1
        jmp LP3

LP2:
        shr ecx, 1
        shr ebx, 2
        jnz LP1

LP3:
        mov eax, ecx

        pop edx
        pop ecx
        pop ebx

        ret
Sqrt_ endp

public Sqrt_


        end


