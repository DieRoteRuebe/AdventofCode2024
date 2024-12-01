.intel_syntax noprefix
#incoming args:
#RDI  int* inArray1
#RSI  int* inArray2
#RDX  int size


#used register:
#rax    ----- Only used to return and for multiplication
#rbx    ----- Keep open for possible basepointer usage
#rdi    int* inArray1
#rsi    int* inArray2
#rdx    int size
#rcx    element to count
#r9     to lea elements
#r10    current sum
#r11    hitCounter
#r12    elementArr1
#r13    elementArr2
#r14    int Counter1
#r15    int Counter2
.text

.global calcSimularities

calcSimularities:
    #Save callers Stack, we dont need to save the args since we wont move them
    #We dont need to save r11-r9 since those are volatiles -> lost anyways
    push rbp
    push r15
    push r14
    push r13
    push r12
    #prepare for while loop:
    mov r14, 0      #Counter1
    mov r15, 0      #Counter2
    xor rax, rax    #retval and sum
    jmp _OutterWhile


_OutterWhile:
    #RDX = int size
    cmp r14, rdx    #return if counter1 = size
    je _ret         #return if counter2 = size
    cmp r15, rdx
    je _ret

_firstInnerWhile:
    #RDI  int* inArray1
    #RSI  int* inArray2
    lea r9, [rdi+r14*4]         #lea the element from arr1 on rbx
    mov r12d, dword ptr[r9]     #r12d = num1
    lea r9, [rsi+r15*4]         #lea the elemnt from arr2 on rbx
    mov r13d, dword ptr[r9]     #r13d = num2
    cmp r12, r13
    jl _num1_le_num2
    cmp r12, r13
    jg _num2_le_num1
    jmp _equal

_num1_le_num2:
    inc r14
    jmp _OutterWhile

_num2_le_num1:
    inc r15
    jmp _OutterWhile

_equal:
    mov r11, 0                  #init hitCounter = number of same elements in array1
    mov ecx, r13d               #cmp with element_to_count
_firstInnerCountElements:
    cmp r14, rdx                #check if counter1 = size
    je _secondInnerCountElements
    lea r9, [rdi+r14*4]         #load the memoryadress of corresponding element
    mov r12d, dword ptr[r9]     #mov the element out of mem into register
    cmp r12d, ecx               #cmp with element_to_count
    jne _secondInnerCountElements
    inc r11                     #if same element inc hitCounter
    inc r14                     #inc index -> counter1
    jmp _firstInnerCountElements

_secondInnerCountElements:
    cmp r15, rdx                #check if counter2 = size
    je _OutterWhile             
    lea r9, [rsi+r15*4]         #load the memoryadress of corresponding element
    mov r12d, dword ptr[r9]     #mov the element out of mem into register
    cmp r12d, ecx               #cmp with element_to_count
    jne _OutterWhile
    inc r15                     #inc index -> counter2
    push rdx                    #save rdx in case of mul overflow
    xor rax, rax                #xor out rax to 0
    mov eax, ecx                #mov element_to_count into eax
    mul r11                     #mul eax with hitCounter in r11
    add r10, rax                #add the multiplication to sum 
    pop rdx                     #restore rdx
    jmp _secondInnerCountElements



_ret:
    #We need to pop the registers in reverse from the stack so the caller has his values back
    pop r12
    pop r13
    pop r14
    pop r15
    pop rbp
    mov rax, r10
    ret
