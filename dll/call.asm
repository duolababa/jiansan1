; �� .asm �ļ���ӵ�����һ��
; �Ҽ������ļ�-����-����-
; ������:�Զ������ɹ���
; ���������ų�:��

; Ȼ����������������
; ������: ml64 /Fo $(IntDir)%(fileName).obj /c /Cp %(fileName).asm
; ���: $(IntDir)%(fileName).obj;%(Outputs)
; ���Ӷ���: ��


;extern g_Packet_Point:qword

extern g_RCX:qword
extern g_CALL1:qword
extern g_CALL2:qword
extern g_CALL3:qword



.CODE


SendPacket proc;HOOK��ӡ���� rcx=����RCX rdx=�������ֽڼ�ָ��  ����RCXֵ = ����RCX ����CALL1 ����CALL2 ����CALL3 ����Ҫ�ȸ�ֵ

sub rsp,178h
lea rcx,[rsp+30h]
mov rax,g_CALL1
call rax
lea rdx,[rsp+30h]
mov rbx,g_RCX
mov rcx,rbx
mov rax,g_CALL2
call rax
mov r8,[rsp+38h]
mov rdx,[rsp+30h]
sub r8,rdx
lea rcx,[rbx+00000108h]
mov rax,g_CALL3
call rax
add rsp,178h
ret


SendPacket endp



JIEMI proc;


mov eax,dword ptr [rcx+18h]
mov r11,rdx
mov rdx,rcx
cmp eax,dword ptr [rcx+44h]
je a1
mov r9,qword ptr [rcx+50h]
lea r10,qword ptr [rcx+48h]
mov rax,r11
sar rax,20h
imul r8d,eax,17h
movsxd rax,dword ptr [rdx+58h]
dec rax
add r8d,r11d
movsxd rcx,r8d
and rcx,rax
test r9,r9
cmovne r10,r9
mov eax,dword ptr [r10+rcx*4]
mov ecx,eax
cmp eax,-1h
je a1
mov r9,qword ptr [rdx+10h]

a3:
movsxd rdx,ecx
lea r8,qword ptr [rdx+rdx*2]
cmp qword ptr [r9+r8*8],r11
je a2
mov ecx,dword ptr [r9+r8*8+10h]
cmp ecx,-1h
jne a3
a1:
xor eax,eax
ret 
a2:
cmp ecx,-1h
je a1
cmp eax,-1h
je a4


a6:
movsxd rcx,eax
lea rdx,qword ptr [rcx+rcx*2]
cmp qword ptr [r9+rdx*8],r11
lea rcx,qword ptr [r9+rdx*8]
je a5
mov eax,dword ptr [rcx+10h]
cmp eax,-1h
jne a6
xor ecx,ecx
mov rax,qword ptr [rcx+8h]
ret 
a5:
cmp eax,-1h
jne a7
a4:
xor ecx,ecx
a7:
mov rax,qword ptr [rcx+8h]
ret 


JIEMI endp


END

