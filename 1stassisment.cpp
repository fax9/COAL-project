; Macro to display a string
display macro var
    lea dx, var
    mov ah, 9
    int 21h
endm

.model small
.stack 100h
.data

; Prompt messages
menu_msg db "Shop Management System", 13, 10
         db "1. Add Product Entries", 13, 10
         db "2. Add Employee Entries", 13, 10
         db "Enter choice (1-2): $"
error_msg db "Invalid Input! Try again.", 13, 10, "$"

.code
main proc
    mov ax, @data       ; Initialize data segment
    mov ds, ax

main_loop:
    ; Display menu
    lea dx, menu_msg
    display menu_msg
    call new_line

    ; Get user choice
    mov ah, 01h         ; Input a single character
    int 21h

    sub al, '0'         ; Convert ASCII to numeric

    ; Handle choices 1 or 2
    cmp al, 1
    je add_product
    cmp al, 2
    je add_employee

    ; Invalid input
    lea dx, error_msg
    display error_msg
    call new_line
    jmp main_loop

add_product:
    ; Placeholder for product functionality
    call new_line
    jmp main_loop

add_employee:
    ; Placeholder for employee functionality
    call new_line
    jmp main_loop

exit_program:
    mov ah, 4Ch
    int 21h

main endp

new_line proc
    mov dl, 13
    mov ah, 2
    int 21h
    mov dl, 10
    mov ah, 2
    int 21h
    ret

    new_line endp

end main