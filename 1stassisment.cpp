.model small
.stack 100h
.data

; Prompt messages
menu_msg db "Shop Management System", 13, 10
         db "1. Add Product Entries", 13, 10
         db "2. Add Employee Entries", 13, 10
         db "3. Exit Program", 13, 10
         db "Enter choice (1-3): $"

error_msg db "Invalid Input! Try again.", 13, 10, "$"

.code
main proc
    ; Initialize the data segment
    mov ax, @data
    mov ds, ax

main_loop:
    ; Display the menu
    lea dx, menu_msg
    mov ah, 09h
    int 21h

    ; Prompt user for choice
    mov ah, 01h
    int 21h
    sub al, '0'                 

    ; Compare user's choice and branch accordingly
    cmp al, 1
    je add_product
    cmp al, 2
    je add_employee
    cmp al, 3
    je exit_program

    ; If invalid input, display error message
    lea dx, error_msg
    mov ah, 09h
    int 21h
    jmp main_loop

;---------------------------------------------------
; Procedure to add a product entry (Day 3 onwards)
add_product:
    ; For now, just a placeholder to show functionality
    lea dx, error_msg
    mov ah, 09h
    int 21h
    call new_line
    jmp main_loop

;---------------------------------------------------
; Procedure to add an employee entry (Day 3 onwards)
add_employee:
    ; For now, just a placeholder to show functionality
    lea dx, error_msg
    mov ah, 09h
    int 21h
    call new_line
    jmp main_loop

;---------------------------------------------------
; Exit Program Procedure
exit_program:
    mov ah, 4Ch                
    int 21h

;---------------------------------------------------
; New line for better readability
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
