section .data
kmh_to_mps: dd 0.2777778

section .text
    global compute_acceleration
	bits 64
	default rel

compute_acceleration:
    mov r9d, 0            ; i = 0 

loop:
    cmp r9d, r8d  ;Compare current car i (r9d) with total cars r8d
    jge done		

    mov eax, r9d
    imul eax, 12
    mov r10, rax

    ; Load Vi, Vf, and T into xmm0, xmm1, and xmm2 registers
    movss xmm0, [rcx + r10 + 0] ;vi
    movss xmm1, [rcx + r10 + 4]	;vf
    movss xmm2, [rcx + r10 + 8]	;t
  
    movss xmm3, dword [rel kmh_to_mps]

    ; Convert km/h to m/s   & Multiply Vi and Vf by it
    mulss xmm0, xmm3	  	; Vi in m/s
    mulss xmm1, xmm3		; Vf in m/s

    ; acceleration = (Vf - Vi) / T
    subss xmm1, xmm0
    divss xmm1, xmm2

    ; Convert to int
    cvtss2si eax, xmm1
    
    mov [rdx + r9*4], eax

    inc r9d  ;Increase i
    jmp loop

done:
    ret


