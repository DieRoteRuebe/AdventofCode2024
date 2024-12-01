.intel_syntax noprefix
#RDI  int* Array
#RSI  int ArraySize
#RDX  int start
#RCX  int end

.text

.global quickSort


quickSort:
    #Save callers Stack and save the incoming args
    push rbp
    push r15
    push r14
    push r13
    push r12
    sub rsp, 0x40
    mov dword ptr[rsp+0x0], esi
    mov dword ptr[rsp+0x8], edx
    mov dword ptr[rsp+0x10], ecx



    mov esi, dword ptr[rsp+0x8]
    mov edx, dword ptr[rsp+0x10]
    call _void_quicksort 
    add rsp, 0x40
    pop r12
    pop r13
    pop r14
    pop r15
    pop rbp
    ret
    


_void_quicksort:
    #save the old stack since were one stack deeper
    push rbp
    mov rbp, rsp

    #incoming args:
    #Array: RDI
    #int left: RSI
    #int pivot: RDX
    
    cmp rsi, rdx
    jge _ret_quicksort
    
    call _int_partition
    #int new_pivot: RAX -> Ret from _int_partition
    push rax
    push rdx
    mov rdx, rax
    dec rdx
    #array, left, new_piviot-1
    call _void_quicksort
    pop rdx
    pop rax
    inc rax
    mov rsi, rax
    call _void_quicksort

_ret_quicksort:
    mov rsp, rbp
    pop rbp
    ret



_int_partition:
    push rbp
    mov rbp, rsp
    #Array: RDI
    #int left: RSI
    #int pivot: RDX
    
    #int low: R15
    mov r15, rsi
    dec r15
    #int high: R14
    mov r14, rdx
    dec r14
    #int j = left
    mov r13, rsi
    jmp _forLoopHead
    
_in_forLoop:
    lea r9, [rdi+r13*4]
    mov eax, dword ptr[r9]
    lea r10, [rdi+rdx*4]
    mov ecx, dword ptr[r10]
    inc r13
    cmp rax, rcx
    jg _forLoopHead
    inc r15
    lea r10, [rdi+r15*4]
    mov ecx, dword ptr[r10]
    mov [r9], ecx
    mov [r10], eax

_forLoopHead:
    cmp r13, r14
    jle _in_forLoop
    
    mov rax, r15
    inc rax
    lea r9, [rdi+rax*4]
    mov ecx, dword ptr[r9]
    lea r10, [rdi+rdx*4]
    mov ebx, dword ptr[r10]
    mov [r9], ebx
    mov [r10], ecx

_ret_partition:
    mov rsp, rbp
    pop rbp
    ret

