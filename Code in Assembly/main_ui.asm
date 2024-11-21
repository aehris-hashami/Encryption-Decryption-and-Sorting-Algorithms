INCLUDE Irvine32.inc
TITLE COAL_PROJECT

.data
    MAX_SIZE = 80
    rows BYTE 0
    cols BYTE 0

    border BYTE MAX_SIZE DUP('-'), 0

    msg_title_signup BYTE "=== SIGN-UP PAGE ===", 0
    msg_title_login BYTE "=== LOG-IN PAGE ===", 0

    msg_intro_signup BYTE "Here you can enter your credentials to create a new account.", 0
    msg_intro_login BYTE "Here you can enter credentials of your existing account.", 0
    msg_username BYTE "Username: ", 0
    msg_password BYTE "Password: ", 0

    msg_signup_success BYTE "Your credentials have been registered successfully!", 0
    msg_login_success BYTE "You have been logged in successfully!", 0

    username BYTE MAX_SIZE+1 DUP(?)
    password BYTE MAX_SIZE+1 DUP(?)

.code
    print_tabbed PROC
        enter 1,0
        push eax
        push ecx
        push edx

        mov dl, [ebp+16]
        mov cl, [ebp+12]
        shr dl, cl
        mov [ebp-1], dl

        call GetMaxXY

        movzx eax, al
        mov cl, 1
        shr dl, cl
        shr al, cl
        mov dh, al
        dec al
        dec dl

        sub dl, [ebp-1]

        mov cl, [ebp+8]
        add rows, cl

        add dh, rows
        inc rows
        call Gotoxy

        mov edx, [ebp+20]
        call WriteString

        pop edx
        pop ecx
        pop eax
        leave
        ret 16
        
    print_tabbed ENDP

    read_string PROC
        enter 0,0
        push ecx
        push edx

        mov ecx, MAX_SIZE
        mov edx, [ebp+8]
        call ReadString

        pop edx
        pop ecx
        leave
        ret 4
    read_string ENDP

    center_rows PROC
        enter 0,0
        push eax
        push ecx
        push edx

        call GetMaxXY

        movzx eax, al
        mov cl, 3
        shr al, cl
        mov rows, al
        neg rows

        pop edx
        pop ecx
        pop eax
        leave
        ret
    center_rows ENDP

    delay_time PROC
        enter 0,0
        push eax

        mov eax, [ebp+8]
        call Delay

        pop eax
        leave
        ret
    delay_time ENDP

    SignUp_UI PROC
        enter 0,0

        call Clrscr
        call center_rows

        push OFFSET msg_title_signup
        push LENGTHOF msg_title_signup
        push 1
        push 0
        call print_tabbed

        push OFFSET msg_intro_signup
        push LENGTHOF msg_intro_signup
        push 1
        push 0
        call print_tabbed

        push OFFSET msg_username
        push LENGTHOF msg_username
        push 0
        push 2
        call print_tabbed

        push OFFSET username
        call read_string

        push OFFSET msg_password
        push LENGTHOF msg_password
        push 0
        push 0
        call print_tabbed

        push OFFSET password
        call read_string

        push OFFSET msg_signup_success
        push LENGTHOF msg_signup_success
        push 1
        push 1
        call print_tabbed

        push OFFSET border
        push LENGTHOF border
        push 1
        push 1
        call print_tabbed

        call CRLF
        call WaitMsg

        leave
        ret
    SignUp_UI ENDP

    Login_UI PROC
        enter 0,0

        call Clrscr
        call center_rows

        push OFFSET msg_title_login
        push LENGTHOF msg_title_login
        push 1
        push 0
        call print_tabbed

        push OFFSET msg_intro_login
        push LENGTHOF msg_intro_login
        push 1
        push 0
        call print_tabbed

        push OFFSET msg_username
        push LENGTHOF msg_username
        push 0
        push 2
        call print_tabbed

        push OFFSET username
        call read_string

        push OFFSET msg_password
        push LENGTHOF msg_password
        push 0
        push 0
        call print_tabbed

        push OFFSET password
        call read_string

        call CRLF
        call WaitMsg

        leave
        ret
    Login_UI ENDP

    Run_UI PROC
        enter 0,0

        call SignUp_UI
        call Login_UI

        leave
        ret
    Run_UI ENDP

    main PROC
        call Run_UI
        call exitProcess
    main ENDP
END main
