INCLUDE Irvine32.inc
TITLE COAL_PROJECT

print_tabbed PROTO, str_ptr: PTR BYTE, indent: BYTE, newline: BYTE
print_centered PROTO, str_ptr: PTR BYTE, indent: BYTE, newline: BYTE
read_string PROTO, input_buffer: PTR BYTE
center_rows PROTO
delay_time PROTO, seconds: DWORD

; =============================================
; MASM Proecdures to be called in C++ code
; =============================================

Cipher_UI PROTO
Show_Ciphertext PROTO, ptr_cipher_pass: PTR BYTE
SignUp_UI PROTO, ptr_username: PTR BYTE, ptr_password: PTR BYTE
Login_UI PROTO, ptr_username: PTR BYTE, ptr_password: PTR BYTE
;Run_UI PROTO

.data
    MAX_SIZE = 80
    NUM_CIPHERS = 6
    rows BYTE 0
    cols BYTE 0

    border BYTE MAX_SIZE DUP('-'), 0

    msg_title_cipher_type BYTE "=== CIPHER SELECTION ===", 0
    msg_title_signup BYTE "=== SIGN-UP PAGE ===", 0
    msg_title_login BYTE "=== LOG-IN PAGE ===", 0

    msg_intro_cipher_type BYTE "Following ciphers are available to use:", 0

    CipherStruct STRUCT
        shift BYTE "1- Shift", 0
        subst BYTE "2- Substitution", 0
        permu BYTE "3- Permutation", 0
        vigen BYTE "4- Vigenere", 0
        hill BYTE "5- Hill", 0
        exit_all BYTE "6- EXIT PROGRAM", 0
    CipherStruct ENDS

    cipher_list CipherStruct <>

    msg_ask_cipher BYTE "Which cipher do you want to use for encryption? (1-6): ", 0
    msg_intro_signup BYTE "Here you can enter your credentials to create a new account.", 0
    msg_intro_login BYTE "Here you can enter credentials of your existing account.", 0
    msg_username BYTE "Username: ", 0
    msg_password BYTE "Password: ", 0

    msg_invalid_input BYTE "Provided option does not exist. Please try again.", 0
    msg_username_fail BYTE "The username you have entered is invalid. Please try again.", 0
    msg_password_fail BYTE "The password you have entered is invalid. Please try again.", 0
    msg_signup_success BYTE "Your credentials have been registered successfully!", 0
    msg_encrypt_pass BYTE "Your encrypted password is:", 0
    msg_login_success BYTE "You have been logged in successfully!", 0

    username BYTE MAX_SIZE+1 DUP(0)
    password BYTE MAX_SIZE+1 DUP(0)

    secret_name BYTE MAX_SIZE+1 DUP(0)
    secret_pass BYTE MAX_SIZE+1 DUP(0)

    cipher_pass BYTE MAX_SIZE+1 DUP(0)

.code
    print_tabbed PROC str_ptr: PTR BYTE, indent: BYTE, newline: BYTE
        pushad

        call GetMaxXY
        mov cl, 1

        shr al, cl

        mov dh, al

        mov cl, newline
        add rows, cl

        add dh, rows
        inc rows

        mov al, indent
        mov cl, 1
        mul cl
        mov cl, al

        shr dl, cl
        call Gotoxy

        mov edx, str_ptr
        call WriteString

        popad
        ret
    print_tabbed ENDP


    print_centered PROC str_ptr: PTR BYTE, indent: BYTE, newline: BYTE
        LOCAL shift_value: BYTE
        LOCAL length_str: BYTE
        pushad

        mov edx, str_ptr
        call StrLength
        mov length_str, al

        mov dl, length_str
        mov cl, indent
        shr dl, cl
        mov shift_value, dl

        call GetMaxXY

        mov cl, 1

        shr dl, cl
        shr al, cl

        mov dh, al
        dec dl

        sub dl, shift_value

        mov cl, newline
        add rows, cl

        add dh, rows
        inc rows
        call Gotoxy

        mov edx, str_ptr
        call WriteString

        popad
        ret
    print_centered ENDP


    read_string PROC input_buffer: PTR BYTE
        pushad

        mov ecx, MAX_SIZE
        mov edx, input_buffer
        call ReadString

        popad
        ret
    read_string ENDP


    center_rows PROC
        enter 0,0
        pushad

        call GetMaxXY

        movzx eax, al
        mov cl, 3
        shr al, cl
        mov rows, al
        neg rows

        popad
        leave
        ret
    center_rows ENDP


    delay_time PROC seconds: DWORD
        push eax

        mov eax, seconds
        call Delay

        pop eax
        ret
    delay_time ENDP


    Cipher_UI PROC
        enter 0,0

        ui_loop:
        call Clrscr
        call center_rows

        invoke print_centered, OFFSET msg_title_cipher_type, 1, 0
        invoke print_centered, OFFSET msg_intro_cipher_type, 1, 1

        mov ebx, OFFSET cipher_list
        mov ecx, NUM_CIPHERS

        loop_ciphers:
            invoke print_tabbed, ebx, 2, 1

            mov edx, ebx
            call StrLength
            inc eax

            add ebx, eax

        loop loop_ciphers

        invoke print_centered, OFFSET msg_ask_cipher, 1, 2
        call ReadInt

        cmp eax, 0
        jle invalid_input

        cmp eax, 6
        je exit_code

        cmp eax, 6
        jg invalid_input

        leave
        ret

        exit_code:
        invoke ExitProcess, 0

        invalid_input:
        invoke print_centered, OFFSET msg_invalid_input, 1, 2
        call CRLF
        call WaitMsg
        jmp ui_loop
    Cipher_UI ENDP
    

    Show_Ciphertext PROC ptr_cipher_pass: PTR BYTE
        invoke print_centered, OFFSET msg_encrypt_pass, 1, 1
        invoke print_centered, ptr_cipher_pass, 1, 0

        ret
    Show_Ciphertext ENDP


    SignUp_UI PROC ptr_username: PTR BYTE, ptr_password: PTR BYTE
        call Clrscr
        call center_rows

        invoke print_centered, OFFSET msg_title_signup, 1, 0
        invoke print_centered, OFFSET msg_intro_signup, 1, 0

        invoke print_centered, OFFSET msg_username, 0, 2
        invoke read_string, OFFSET username

        invoke Str_copy, OFFSET username, ptr_username

        invoke print_centered, OFFSET msg_password, 0, 0
        invoke read_string, OFFSET password

        invoke Str_copy, OFFSET password, ptr_password

        invoke print_centered, OFFSET msg_signup_success, 1, 1
        invoke print_centered, OFFSET border, 1, 1

        call CRLF
        call WaitMsg

        ret
    SignUp_UI ENDP


    Login_UI PROC ptr_username: PTR BYTE, ptr_password: PTR BYTE
        ui_loop:
        call Clrscr
        call center_rows

        invoke print_centered, OFFSET msg_title_login, 1, 0
        invoke print_centered, OFFSET msg_intro_login, 1, 0

        invoke print_centered, OFFSET msg_username, 0, 2
        invoke read_string, OFFSET username

        invoke Str_compare, OFFSET username, ptr_username
        jne invalid_username

        invoke print_centered, OFFSET msg_password, 0, 0
        invoke read_string, OFFSET password

        invoke Str_compare, OFFSET password, ptr_password
        jne invalid_password

        jmp exit_ui_loop

        invalid_username:
        invoke print_centered, OFFSET msg_username_fail, 1, 2
        call CRLF
        call WaitMsg
        jmp ui_loop

        invalid_password:
        invoke print_centered, OFFSET msg_password_fail, 1, 2
        call CRLF
        call WaitMsg
        jmp ui_loop

        exit_ui_loop:
        invoke print_centered, OFFSET msg_login_success, 1, 2
        invoke print_centered, OFFSET border, 1, 1
        call CRLF
        call WaitMsg

        ret
    Login_UI ENDP

    ;Run_UI PROC
    ;    enter 0,0

    ;    call SignUp_UI
    ;    call Login_UI

    ;    leave
    ;    ret
    ;Run_UI ENDP

END
