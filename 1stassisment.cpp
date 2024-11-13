; Macro to display a string
display macro var
    lea dx, var      
    mov ah, 9        
    int 21h          
endm

.model small
.stack 100h
.data
