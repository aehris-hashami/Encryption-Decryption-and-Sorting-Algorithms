INCLUDE Irvine32.inc

.data
    dimension DWORD ?
    plaintext BYTE 256 DUP(0)
    ciphertext BYTE 256 DUP(0)
    deciphertext BYTE 256 DUP(0)
    promptText BYTE "Enter text: ", 0
    cipherTextMsg BYTE "Cipher text generated: ", 0
    decryptedTextMsg BYTE "Decrypted text generated: ", 0

.code
main PROC
    ; Seed random number generator
    invoke GetTickCount
    invoke srand, eax

    ; Generate random dimension
    invoke rand
    mov eax, 4
    xor edx, edx
    div eax
    add eax, 2
    mov dimension, eax

    ; Generate shuffled identity matrix
    invoke gen_rand_indicies, dimension
    invoke gen_shuffling_transformation_mat, eax, dimension

    ; Print the matrix
    mov ecx, dimension
print_matrix:
    push ecx
    mov ecx, dimension
    mov ebx, eax ; pointer to matrix
print_row:
    ; Print each element in the row
    ; (Assuming a function to print integers exists)
    invoke print_int, [ebx]
    add ebx, 4
    loop print_row
    ; Print newline
    invoke print_newline
    pop ecx
    loop print_matrix

    ; Get plaintext input from user
    invoke StdOut, addr promptText
    invoke StdIn, addr plaintext, 256

    ; Encrypt the plaintext
    invoke encrypt, addr plaintext, eax
    invoke StdOut, addr cipherTextMsg
    invoke StdOut, addr ciphertext

    ; Decrypt the ciphertext
    invoke decrypt, addr ciphertext, eax
    invoke StdOut, addr decryptedTextMsg
    invoke StdOut, addr deciphertext

    ; Exit program
    invoke ExitProcess, 0
main ENDP

; Utility procedures
; Function to find an integer in a vector
find PROC
    ; Parameters: 
    ;   EAX - pointer to vector
    ;   EDX - search key
    ; Returns: 
    ;   AL - 1 if found, 0 if not found
    PUSH EDI
    MOV EDI, [EAX] ; Load vector size
    ADD EAX, 4     ; Move to the first element
    XOR ECX, ECX   ; Initialize index to 0

find_loop:
    CMP ECX, EDI
    JGE not_found   ; If index >= size, not found
    MOV EBX, [EAX]  ; Load current element
    CMP EBX, EDX    ; Compare with search key
    JE found        ; If equal, found
    ADD EAX, 4      ; Move to next element
    INC ECX         ; Increment index
    JMP find_loop

found:
    MOV AL, 1       ; Set return value to true
    JMP end_find

not_found:
    XOR AL, AL      ; Set return value to false

end_find:
    POP EDI
    RET
find ENDP

; Function to generate random indices
gen_rand_indicies PROC
    ; Parameters:
    ;   EAX - dimensions
    ; Returns:
    ;   EAX - pointer to vector of random indices
    PUSH EDI
    PUSH ESI
    PUSH EBX
    CALL Randomize   ; Seed the random number generator
    MOV EDI, EAX    ; Store dimensions
    ; Allocate memory for vector
    MOV EAX, EDI
    SHL EAX, 2      ; Multiply by 4 (size of int)
    CALL HeapAlloc   ; Allocate memory
    MOV ESI, EAX    ; Store pointer to vector

    XOR ECX, ECX    ; Initialize index to 0

gen_rand_loop:
    CALL RandomRange ; Get random number in range [0, dimensions)
    MOV EBX, EAX    ; Store random number
    PUSH ESI        ; Save vector pointer
    PUSH EBX        ; Push random number
    CALL find       ; Check if it exists in the vector
    POP EBX
    POP ESI
    TEST AL, AL
    JZ add_index    ; If not found, add to vector
    DEC ECX         ; Decrement index if found
    JMP gen_rand_loop

add_index:
    MOV [ESI + ECX*4], EBX ; Add random number to vector
    INC ECX
    CMP ECX, EDI
    JL gen_rand_loop

    MOV EAX, ESI    ; Return pointer to vector
    POP EBX
    POP ESI
    POP EDI
    RET
gen_rand_indicies ENDP

; Function to generate shuffling transformation matrix
gen_shuffling_transformation_mat PROC
    ; Parameters:
    ;   EAX - pointer to random indices
    ;   EDX - dimensions
    ; Returns:
    ;   EAX - pointer to shuffling matrix
    PUSH EDI
    PUSH ESI
    PUSH EBX
    MOV EDI, EDX    ; Store dimensions
    ; Allocate memory for matrix
    MOV EAX, EDI
    IMUL EAX, EDI   ; EAX = dimensions * dimensions
    SHL EAX, 2      ; Multiply by 4 (size of int)
    CALL HeapAlloc   ; Allocate memory
    MOV ESI, EAX    ; Store pointer to matrix

    ; Initialize matrix to zero
    XOR ECX, ECX
init_matrix:
    CMP ECX, EDI
    JGE end_init
    MOV EAX, ESI
    ADD EAX, ECX
    IMUL EAX, EDI
    ADD EAX, ECX
    MOV DWORD PTR [EAX], 0 ; Set to 0
    INC ECX
    JMP init_matrix

end_init:
    ; Fill the shuffling matrix
    MOV ECX, 0
fill_matrix:
    CMP ECX, EDI
    JGE end_fill
    MOV EAX, [EAX + ECX*4] ; Get random index
    MOV [ESI + EAX*4 + ECX*4*EDI], 1 ; Set matrix value to 1
    INC ECX
    JMP fill_matrix

end_fill:
    MOV EAX, ESI    ; Return pointer to matrix
    POP EBX
    POP ESI
    POP EDI
    RET
gen_shuffling_transformation_mat ENDP

; Function to get substring
substring PROC
    ; Parameters:
    ;   EAX - pointer to string
    ;   EDX - start index
    ;   ECX - end index
    ; Returns:
    ;   EAX - pointer to substring
    PUSH EDI
    PUSH ESI
    PUSH EBX
    ; Allocate memory for substring
    MOV EDI, ECX
    SUB EDI, EDX
    ADD EDI, 1      ; Length of substring
    SHL EDI, 2      ; Multiply by 4 (size of char)
    CALL HeapAlloc   ; Allocate memory
    MOV ESI, EAX    ; Store pointer to substring

    ; Copy substring
    MOV EBX, EDX
    SUB EBX, 1      ; Adjust for 0-based index
copy_loop:
    CMP EBX, ECX
    JGE end_copy
    MOV AL, [EAX + EBX] ; Get character
    MOV [ESI], AL
    INC ESI
    INC EBX
    JMP copy_loop

end_copy:
    MOV BYTE PTR [ESI], 0 ; Null-terminate the string
    MOV EAX, ESI    ; Return pointer to substring
    POP EBX
    POP ESI
    POP EDI
    RET
substring ENDP

; Function to shard string
string_sharding PROC
    ; Parameters:
    ;   EAX - pointer to plaintext
    ;   EDX - letters per segment
    ; Returns:
    ;   EAX - pointer to vector of shards
    PUSH EDI
    PUSH ESI
    PUSH EBX
    ; Calculate number of shards
    MOV EDI, EAX
    CALL StrLength
    MOV EBX, EDX
    XOR ECX, ECX
    ; Calculate number of segments
    MOV EDX, EAX
    MOV EAX, EBX
    DIV EAX
    ADD ECX, EAX
    ; Check for remainder
    CMP EDX, 0
    JZ no_remainder
    INC ECX
no_remainder:
    ; Allocate memory for shards
    SHL ECX, 2      ; Multiply by 4 (size of pointer)
    CALL HeapAlloc   ; Allocate memory
    MOV ESI, EAX    ; Store pointer to shards

    ; Create shards
    MOV EAX, EDI
    MOV EDX, EBX
    XOR EBX, EBX
shard_loop:
    CMP EBX, ECX
    JGE end_shard
    PUSH EAX
    PUSH EBX
    CALL substring   ; Get substring
    MOV [ESI + EBX*4], EAX ; Store pointer to shard
    POP EBX
    POP EAX
    ADD EAX, EDX
    INC EBX
    JMP shard_loop

end_shard:
    MOV EAX, ESI    ; Return pointer to shards
    POP EBX
    POP ESI
    POP EDI
    RET
string_sharding ENDP

; Function to apply transformation
applying_transformation PROC
    ; Parameters:
    ;   EAX - pointer to matrix
    ;   EDX - pointer to string
    ; Returns:
    ;   EAX - pointer to result string
    PUSH EDI
    PUSH ESI
    PUSH EBX
    ; Allocate memory for result
    CALL HeapAlloc
    MOV ESI, EAX    ; Store pointer to result

    ; Apply transformation
    MOV EAX, [EAX]  ; Get matrix size
    XOR ECX, ECX
transform_loop:
    CMP ECX, EAX
    JGE end_transform
    ; Inner loop
    MOV EDI, [EAX + ECX*4] ; Get row
    XOR EBX, EBX
inner_loop:
    CMP EBX, EAX
    JGE end_inner
    ; Check if matrix value is non-zero
    MOV EDX, [EDI + EBX*4]
    TEST EDX, EDX
    JZ skip
    ; Multiply and add to result
    MOV AL, [EDX + EBX]
    ADD [ESI], AL
skip:
    INC EBX
    JMP inner_loop

end_inner:
    INC ECX
    JMP transform_loop

end_transform:
    MOV BYTE PTR [ESI], 0 ; Null-terminate the string
    MOV EAX, ESI    ; Return pointer to result
    POP EBX
    POP ESI
    POP EDI
    RET
applying_transformation ENDP

decrypt PROC
    ; Parameters: 
    ; ciphertext: string pointer
    ; mat: pointer to a 2D vector of integers

    ; Get the transpose of the matrix
    ; Call transpose function (assumed to be defined elsewhere)
    invoke transpose, mat, addr transpose_mat

    ; Print the transposed matrix
    mov ecx, [mat.size] ; Get the size of the matrix
    xor ebx, ebx        ; Initialize row index i to 0

print_transpose:
    cmp ebx, ecx
    jge end_print_transpose ; If i >= mat.size, exit loop

    ; Print each element in the transposed row
    invoke print_row, transpose_mat[ebx]

    inc ebx
    jmp print_transpose

end_print_transpose:
    ; Print a newline
    invoke StdOut, chr(10)

    ; Break down the cipher text into appropriate segments
    invoke string_sharding, ciphertext, mat.size, addr cipher_shards

    ; Apply transformation to individual cipher segments
    xor ebx, ebx        ; Initialize index for cipher_shards
    mov ecx, [cipher_shards.size] ; Get the size of cipher_shards

apply_transformation:
    cmp ebx, ecx
    jge end_apply_transformation ; If i >= cipher_shards.size, exit loop

    ; Apply transformation to each shard
    invoke applying_transformation, transpose_mat, cipher_shards[ebx], addr plain_shards[ebx]

    inc ebx
    jmp apply_transformation

end_apply_transformation:
    ; Concatenate all the transformed segments
    xor ebx, ebx        ; Initialize index for plain_shards
    mov ecx, [plain_shards.size] ; Get the size of plain_shards

    xor eax, eax        ; Initialize plaintext to empty string
concat_plaintext:
    cmp ebx, ecx
    jge end_concat_plaintext ; If i >= plain_shards.size, exit loop

    ; Concatenate each plain shard
    invoke strcat, plaintext, plain_shards[ebx]

    inc ebx
    jmp concat_plaintext

end_concat_plaintext:
    ; Return plaintext
    mov eax, plaintext
    ret
decrypt ENDP

END main

