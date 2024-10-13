include Irvine.inc

;   Hello there, this is a project
;that will is created using Assembly
;Language on microsoft using the
;MASM library.
;   The IDE is used to create this 
;is Visual Studio 19

.data
    hello byte "Hello",0

.code 
    mian PROC
        
        xor edx, edx
        mov dl, offset hello
        call writestring
        exit
    main ENDP
    END main