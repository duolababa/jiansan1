EXTERN  g_hWowModuleBase:QWORD
.data
;g_hWowModuleBase            QWORD       0                   ;��Ϸģ���ַ
EXTERN mceshi:far
EXTERN callceshi:far

g_pHookCallBack             QWORD       0h					;�ص�
g_pHookCRC_01				QWORD       0h					;CRC��ַ


.code

Addasm proc
  push rcx
    push rdx
    sub rsp, 100h
    xor rax, rax
  
    call callceshi
    mov rax,qword ptr[mceshi]
    add rax, rcx
    add rax, rdx
    add rsp, 100h
    pop rdx
    pop rcx
    ret
Addasm endp


;�ص�
HookCallBack_1 PROC


	
    push rcx
	push rdx
	push r8
	push r9
	sub rsp,200h
	;param:address,crc_val,count,���(�����������ĸ�Hook��������)
	mov r9,rax
	mov r8,r8
	mov rdx,rdx
	mov rcx,rcx
	mov rax,g_pHookCallBack
	call rax
	mov qword ptr [rsp+38h], rax
	add rsp,200h
	pop r9
	pop r8
	pop rdx
	pop rcx
	
	;��ת��ԭ�ȵĵ�ִַ��
	mov qword ptr [rsp+38h], rax
	lea r8, qword ptr[rsp+30h]
	mov rax, qword ptr[rsp+48h]
	mov rax,g_hWowModuleBase
	add rax,g_pHookCRC_01
	add rax,0Fh
	push rax
	ret


HookCallBack_1 ENDP


HookCallBack_2 PROC


 	push rax								;����Ĵ���ԭ��ֵ
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	sub rsp,80h
	mov rcx,rcx
	mov rdx,rdx
	mov r8,r8
	mov r9,r9
	mov rax,g_pHookCallBack
	call rax
	add rsp,80h
	pop r15									;��ԭ�Ĵ���ԭ��ֵ
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax


	
	;��ת��ԭ�ȵĵ�ִַ��
	mov qword ptr[rsp+08h], rbx
	push rdi
	sub rsp, 50h
	mov rax, qword ptr[rsp+80h]
	mov rbx, r9
	mov r9, r8
	mov rax,g_hWowModuleBase
	add rax,g_pHookCRC_01
	add rax,18h
	push rax
	ret


HookCallBack_2 ENDP







;���ð汾,�����Ҫ���������ⲿ�汾����
setHookCallBackProc PROC
	push rbx
	lea rbx,g_pHookCallBack
	mov [rbx],rcx
	mov rax,g_pHookCallBack
	pop rbx
	ret
setHookCallBackProc ENDP


;g_pHookCRC_01
setHookCRC_01 PROC
	push rbx
	lea rbx,g_pHookCRC_01
	mov [rbx],rcx
	mov rax,g_pHookCRC_01
	pop rbx
	ret
setHookCRC_01 ENDP

setGameModule PROC
	push rbx
	lea rbx,g_hWowModuleBase
	mov [rbx],rcx
	mov rax,g_hWowModuleBase
	pop rbx
	ret
setGameModule ENDP
end