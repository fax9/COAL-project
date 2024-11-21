; Macro to display a string
display macro var
    lea dx, var
    mov ah, 9
    int 21h
endm

.model small
.stack 100h
.data

menu_msg db "Shop Management System", 13, 10
         db "1. Add Product Entries", 13, 10
         db "2. Add Employee Entries", 13, 10
         db "Enter choice (1-2): $"
error_msg db "Invalid Input! Try again.", 13, 10, "$"

product_names db 100*32 dup(' ')
product_quantities dw 100 dup(0)
product_prices dw 100 dup(0)
numb dw 0

employee_names db 100*32 dup(' ')
employee_ids dw 100 dup(0)
employee_numbers dw 100 dup(0)
emp dw 0

name_prompt db "Enter Name: $", 13, 10
quantity_prompt db "Enter Quantity: $", 13, 10
price_prompt db "Enter Price: $", 13, 10
id_prompt db "Enter CNIC: $", 13, 10
phone_prompt db "Enter Phone Number: $", 13, 10

.code
main proc
    mov ax, @data
    mov ds, ax

main_loop:
    lea dx, menu_msg
    display menu_msg
    call new_line

    mov ah, 01h
    int 21h
    sub al, '0'

    cmp al, 1
    je add_product
    cmp al, 2
    je add_employee

    lea dx, error_msg
    display error_msg
    call new_line
    jmp main_loop

add_product:
    call new_line
    lea dx, name_prompt
    display name_prompt
    call get_string

    mov bx, numb
    shl bx, 5
    lea si, product_names
    add si, bx
    mov cx, 32
    rep movsb

    lea dx, quantity_prompt
    display quantity_prompt
    call get_number
    mov bx, numb
    shl bx, 1
    mov product_quantities[bx], ax

    lea dx, price_prompt
    display price_prompt
    call get_number
    mov product_prices[bx], ax

    inc numb
    call new_line
    jmp main_loop

add_employee:
    call new_line
    lea dx, name_prompt
    display name_prompt
    call get_string

    mov bx, emp
    shl bx, 5
    lea si, employee_names
    add si, bx
    mov cx, 32
    rep movsb

    lea dx, id_prompt
    display id_prompt
    call get_number
    mov bx, emp
    shl bx, 1
    mov employee_ids[bx], ax

    lea dx, phone_prompt
    display phone_prompt
    call get_number
    mov employee_numbers[bx], ax

    inc emp
    call new_line
    jmp main_loop

exit_program:
    mov ah, 4Ch
    int 21h

main endp

get_string:
    input_buffer db 32, ?
                db 32 dup(' ')
    lea dx, input_buffer
    mov ah, 0Ah
    int 21h
    ret

get_number:
    xor ax, ax
    mov ah, 01h
    int 21h
    sub al, '0'
    mov ah, 0
    ret

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
