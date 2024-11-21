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
menu_msg db "Shop Management System",13,10
         db "1. Add Product Entries", 13, 10
         db "2. Add Employee Entries", 13, 10
         db "3. Exit Program", 13, 10
         db "Enter choice (1-3): $"

product_entry_msg db "Enter Product Information", 13, 10, "$"
employee_entry_msg db "Enter Employee Information", 13, 10, "$"
name_prompt db "Enter Name: $", 13, 10
quantity_prompt db "Enter Quantity: $", 13, 10
price_prompt db "Enter Price: $", 13, 10
id_prompt db "Enter CNIC: $", 13, 10
phone_prompt db "Enter Phone Number: $", 13, 10
next_entry_msg db "Add another entry? (y/n): $", 13, 10
error_msg db "Invalid Input! Try again.", 13, 10, "$"

; Data arrays for products and employees
product_names db 100*32 dup(' ')       ; Product name entries
product_quantities dw 100 dup(0)       ; Product quantities
product_prices dw 100 dup(0)           ; Product prices
numb dw 0                              ; Product count

employee_names db 100*32 dup(' ')      ; Employee name entries
employee_ids dw 100 dup(0)             ; Employee IDs
employee_numbers dw 100 dup(0)         ; Employee phone numbers
emp dw 0                               ; Employee count

; Input buffer for temporary input
input_buffer db 32, ?                   ; First byte specifies max length (32)
db 32 dup(' ')                          ; Buffer space for input

.code
main proc
    mov ax, @data
    mov ds, ax

main_loop:
    ; Display menu
    lea dx, menu_msg
    display menu_msg
    call new_line

    ; Get user choice
    mov ah, 01h
    int 21h
    sub al, '0'

    cmp al, 1
    je add_product
    cmp al, 2
    je add_employee
    cmp al, 3
    je exit_program

    lea dx, error_msg
    display error_msg
    call new_line
    jmp main_loop

;---------------------------------------------------
; Procedure to add a product entry
add_product:
    call new_line
    lea dx, product_entry_msg
    display product_entry_msg
    call new_line
    mov bx, numb               ; Load current product count as index

    ; Prompt for product name
    lea dx, name_prompt
    display name_prompt
    call get_string
    call new_line
    mov di, bx
    shl di, 5                  ; di = bx * 32 for 32-byte entries
    lea si, product_names
    add si, di
    mov cx, 32
    rep movsb                  ; Store name in product_names[bx]

    ; Prompt for quantity
    lea dx, quantity_prompt
    call new_line
    display quantity_prompt
    call get_number
    mov product_quantities[di], ax

    ; Prompt for price
    call new_line
    lea dx, price_prompt
    display price_prompt
    call get_number
    mov product_prices[di], ax
    call new_line
    inc numb                   ; Increment product count
    call continue_prompt
    jmp main_loop

;---------------------------------------------------
; Procedure to add an employee entry
add_employee:
    call new_line
    lea dx, employee_entry_msg
    display employee_entry_msg

    mov bx, emp                ; Load current employee count as index
    call new_line

    ; Prompt for employee name
    lea dx, name_prompt
    display name_prompt
    call get_string
    call new_line
    mov di, bx
    shl di, 5                  ; di = bx * 32 for 32-byte entries
    lea si, employee_names
    add si, di
    mov cx, 32
    rep movsb                  ; Store name in employee_names[bx]

    ; Prompt for employee ID
    call new_line
    lea dx, id_prompt
    display id_prompt
    call get_number
    mov di, bx
    shl di, 1                  ; di = bx * 2 for word-sized entries
    mov employee_ids[di], ax   ; Store ID in employee_ids[bx]
    call new_line

    ; Prompt for phone number
    call new_line
    lea dx, phone_prompt
    display phone_prompt
    call get_number
    mov employee_numbers[di], ax  ; Store phone number in employee_numbers[bx]
    call new_line

    inc emp                    ; Increment employee count
    call continue_prompt
    jmp main_loop

;---------------------------------------------------
; Exit Program Procedure
exit_program:
    mov ah, 4Ch                ; DOS terminate program function
    int 21h

;---------------------------------------------------
; Continue Prompt to ask for another entry
continue_prompt:
    lea dx, next_entry_msg
    mov ah, 09h
    int 21h

    mov ah, 01h               ; Read user's response
    int 21h
    cmp al, 'n'
    je exit_program            ; Exit if 'n' is entered
    cmp al, 'y'
    call new_line
    call new_line
    je main_loop               ; Go back to main menu if 'y' is entered
    jmp continue_prompt        ; Repeat prompt if invalid input
    ret

;---------------------------------------------------
; Get String Procedure (for name entry)
get_string:
    ; Clear the input buffer before getting input
    mov si, offset input_buffer + 1
    mov cx, 32
    mov al, ' '                ; Fill buffer with spaces
    rep stosb
    lea dx, input_buffer       ; Point DX to the input buffer
    mov ah, 0Ah                ; Buffered input for string
    int 21h
    ret

;---------------------------------------------------
; Get Number Procedure (for quantity/price/ID/phone)
get_number:
    xor ax, ax
    mov ah, 01h
    int 21h
    sub al, '0'
    mov ah, 0
    ret

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
