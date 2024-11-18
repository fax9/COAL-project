.data
; Product data arrays
product_names db 100*32 dup(' ')   ; Array for 100 product names, each 32 bytes
product_quantities dw 100 dup(0)   ; Array for 100 product quantities
product_prices dw 100 dup(0)       ; Array for 100 product prices
numb dw 0                          ; Product count

name_prompt db "Enter Product Name: $", 13, 10
quantity_prompt db "Enter Quantity: $", 13, 10
price_prompt db "Enter Price: $", 13, 10

.code
add_product:
    call new_line
    lea dx, name_prompt
    display name_prompt
    call get_string

    mov bx, numb
    shl bx, 5                ; bx = numb * 32 for 32-byte entries
    lea si, product_names
    add si, bx
    mov cx, 32
    rep movsb                ; Store product name in product_names[numb]

    ; Enter quantity
    lea dx, quantity_prompt
    display quantity_prompt
    call get_number
    mov bx, numb
    shl bx, 1                ; bx = numb * 2 for word entries
    mov product_quantities[bx], ax

    ; Enter price
    lea dx, price_prompt
    display price_prompt
    call get_number
    mov product_prices[bx], ax

    inc numb
    call new_line
    jmp main_loop

get_string:
    ; Temporary buffer for string input
    input_buffer db 32, ?              ; First byte: max length (32)
                db 32 dup(' ')
    lea dx, input_buffer
    mov ah, 0Ah
    int 21h
    ret

get_number:
    ; Simple number input using AX
    xor ax, ax
    mov ah, 01h
    int 21h
    sub al, '0'
    mov ah, 0
    ret
