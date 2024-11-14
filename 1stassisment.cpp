; Macro to display a string
display macro var
    lea dx, var      
    mov ah, 9        
    int 21h          
endm

.model small
.stack 100h
.data

; Counter variables for product and employee entries
numb dw 0        
emp dw 0          

; Product data arrays
product_names db 100*32 dup(' ')  
product_ids dw 100 dup(0)          
product_quantities dw 100 dup(0)  
product_prices dw 100 dup(0)       

; Employee data arrays
employee_names db 100*32 dup(' ')  
employee_ids dw 100 dup(0)         
employee_numbers dw 100 dup(0)     
