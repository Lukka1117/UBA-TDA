extern strcmp
global invocar_habilidad

; Completar las definiciones o borrarlas (en este ejercicio NO serán revisadas por el ABI enforcer)
DIRENTRY_NAME_OFFSET EQU 0
DIRENTRY_PTR_OFFSET EQU 16
DIRENTRY_SIZE EQU 24

FANTASTRUCO_DIR_OFFSET EQU 0
FANTASTRUCO_ENTRIES_OFFSET EQU 8
FANTASTRUCO_ARCHETYPE_OFFSET EQU 16
FANTASTRUCO_FACEUP_OFFSET EQU 24
FANTASTRUCO_SIZE EQU 32

section .rodata
; Acá se pueden poner todas las máscaras y datos que necesiten para el ejercicio

section .text

; void invocar_habilidad(void* carta, char* habilidad);
invocar_habilidad:
	; Te recomendamos llenar una tablita acá con cada parámetro y su
	; ubicación según la convención de llamada. Prestá atención a qué
	; valores son de 64 bits y qué valores son de 32 bits o 8 bits.
	;
	; rdi/m64 = void*    card ; Vale asumir que card siempre es al menos un card_t*
	; rsi/m64 = char*    habilidad
	push rbp
	mov rbp,rsp
	push rbx
	push r12
	push r13
	push r14
	push r15
	sub rsp, 8

	mov r12, RDI ; puntero a carta
	mov r13, RSI ; puntero a nombre de habilidad
	xor r14, r14
	mov R14W, word[R12 + FANTASTRUCO_ENTRIES_OFFSET] ; R14W CANTIDAD DE ENTRADAS
	mov r15, [r12] ; r15 es puntero a array de direntries
	xor rbx, rbx

	.ciclo:
	cmp rbx, R14
	je .verEnArquetipo
	cmp r15, 0
	je .verEnArquetipo
	mov R8, RBX
	imul r8, 8 ;R8 es posicion * tam de punteros(8) entonces es offset de direntry a examinar
	mov RDI, r13
	mov R9, qword[r15 + r8] ; R9 ES MI PUNTERO A DIRENTRY A EXAMINAR
	mov RSI, R9
	push R9
	sub rsp, 8
	call strcmp
	add rsp, 8
	pop R9
	inc RBX
	cmp eax, 0
	jne .ciclo

	mov r8, qword[R9 + DIRENTRY_PTR_OFFSET] ; rdi tiene puntero a func
	mov rdi, r12
	call r8
	jmp .fin

	.verEnArquetipo:
	mov rsi, r13
	mov rdi, qword[R12+ FANTASTRUCO_ARCHETYPE_OFFSET]
	cmp rdi, 0
	je .fin
	call invocar_habilidad

	.fin:
	add rsp, 8
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	pop rbp
	ret ;No te olvides el ret!