.intel_syntax noprefix
#incoming args:
#RDI  int* inArray1
#RSI  int size_array1
#RDX  int* inArray2
#RCX  int size_array2

.text

.global calcDistance


calcDistance:
    #Save callers Stack, we dont need to save the args since we wont move them
    #We dont need to save r11-r9 since those are volatiles -> lost anyways
    push rbp
    push r15
    push r14
    push r13
    push r12
    
    #compare the sizes first if not even return -1 = error:
    cmp rsi, rcx
    je _prepareforloop
    mov rax, -1

_ret_calcDistance:
    #We need to pop the registers in reverse from the stack so the caller has his values back
    pop r12
    pop r13
    pop r14
    pop r15
    pop rbp
    ret

_prepareforloop:
    mov r14, 0 #Element counter for arr1 
    mov r15, 0 #Element counter for arr2
    xor rax, rax
    jmp _forLoopHead

_calculation:
    #RDI  int* inArray1
    #RDX  int* inArray2
    lea r9, [rdi+r14*4] #lea the element from arr1 on r9
    mov r11d, dword ptr[r9]
    lea r10, [rdx+r15*4] #lea the elemnt from arr2 on r10
    mov r13d, dword ptr[r10]
    #increment both counters
    inc r14 
    inc r15
    cmp r11, r13
    jle _r11dLessThenr13d

_r13dLessThenr11d:
    sub r11, r13
    add rax, r11
    jmp _forLoopHead

_r11dLessThenr13d:
    sub r13, r11
    add rax, r13

_forLoopHead:
    #RSI  int size_array1
    #RCX  int size_array2
    #We only need one of two sizes since they are even
    cmp r15, rsi
    jl _calculation            #if less then or equal -> Calculate the distance
    jmp _ret_calcDistance       #if went trought the array simply return -> sum sits alrdy on rax

