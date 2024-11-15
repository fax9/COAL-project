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

; Input buffer for temporary input
input_buffer db 32, ?             
db 32 dup(' ')                     

; Prompt messages
menu_msg db "Shop Management System",13 ,10
         db "1. Add Product Entries", 13, 10
         db "2. Add Employee Entries", 13, 10
         db "Enter choice (1-2): $"
product_entry_msg db "Enter Product Information", 13, 10, "$"
employee_entry_msg db "Enter Employee Information", 13, 10, "$"
name_prompt db "Enter Name: $", 13, 10
id_prompt db "Enter CNIC: $", 13, 10
quantity_prompt db "Enter Quantity: $", 13, 10
price_prompt db "Enter Price: $", 13, 10
phone_prompt db "Enter Phone Number: $", 13, 10
next_entry_msg db "Add another entry? (y/n): $", 13, 10
error_msg db "Invalid Input! Try again.", 13, 10, "$"

.code
main proc
