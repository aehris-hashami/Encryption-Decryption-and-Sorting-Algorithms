include irvine32.inc

.data
    ptxt byte "ABCDEFG",0

    ; ctxt byte lengthof ptxt

    promt_shift byte "Enter shift key: ",0
    shift_key dword ?


.code 
    main proc
        
        ; clearing registers
        xor eax, eax
        xor ebx, ebx
        xor ecx, ecx
        xor edx, edx
        

        ; displaying plain text
        mov edx, offset ptxt
        call writestring
        call crlf 

        ; prompt shift key
        mov edx, offset promt_shift
        call writestring
        call readint

        ; calculating shift modulo
        xor edx, edx
        mov ebx, 26
        div ebx

        ; applying encryption
        xor ecx, ecx
        xor eax, eax
        mov esi, ptr type byte ptxt 

        encrypt:

            mov al, [esi + ecx]
            add eax, edx
            mov [ptxt + ecx], al
        
        cmp ecx, lengthof ptxt
        jnz encrypt

        ; displaying cipher text
        mov edx, offset ptxt
        call writestring
        call crlf 

    main endp
end main