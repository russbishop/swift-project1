;;; kernel/init/main.asm
;;;
;;; Created by Simon Evans on 13/11/2015.
;;; Copyright © 2015 Simon Evans. All rights reserved.
;;;
;;; Entry point from jump into long mode. Minimal setup
;;; before calling SwiftKernel.startup

        BITS 64

        DEFAULT REL
        SECTION .text

        extern _kernel_stack
        extern init_mm
        extern _bss_start
        extern _kernel_end
        extern _TF11SwiftKernel7startupFT_T_ ; SwiftKernel.startup () -> ()
        extern initial_tls_end_addr

        global main

        ;; Entry point after switching to Long Mode
main:
        mov     rsp, _kernel_stack      ; Set the stack to just after the BSS
        mov     rbp, rsp

        ;; Clear the BSS
        xor     rax, rax
        mov     rdi, _bss_start
        mov     rcx, _kernel_end
        sub     rcx, rdi
        shr     rcx, 3
        rep     stosq
        call    enable_sse

        ;; Setup TLS - Update the GDT entry for select 0x18 to have the address
        ;; of initial_tls_end which is allocated in the bss for the 1st TLS
        sgdt    [tempgdt]
        mov     ebx, [tempgdt.base]
        add     ebx, 0x18
        xor     rdx, rdx
        mov     eax, [initial_tls_end_addr]
        mov     edx, eax
        mov     [eax], eax
        mov     ecx, eax
        shl     ecx, 16         ; ecx hold low 32bit of descriptor (limit  = 0)
        mov     [ebx], ecx
        mov     ecx, eax
        shr     ecx, 16
        and     ecx, 0xff
        or      ecx, 0x9200
        and     eax, 0xff000000
        or      eax, ecx
        mov     [ebx+4], eax

        mov     ax,0x18
        mov     fs,ax

        mov     [fs:0], rdx

        call    init_mm                 ; required for malloc/free
        call    _TF11SwiftKernel7startupFT_T_   ; SwiftKernel.startup
        hlt

        ;; SSE instuctions cause an undefined opcode until enabled in CR0/CR4
        ;; Swift requires this at it uses the SSE registers
enable_sse:
        mov     rax, cr0
        and     ax, 0xFFFB		; Clear coprocessor emulation CR0.EM
        or      ax, 0x2                 ; Set coprocessor monitoring CR0.MP
        mov     cr0, rax
        mov     rax, cr4
        or      ax, 3 << 9		; Set CR4.OSFXSR and CR4.OSXMMEXCPT
        mov     cr4, rax
        ret


        SECTION .bss

tempgdt:
.length:        resw    1
.base:          resq    1
