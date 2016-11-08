 start 1000
first stl retadr
cloop jsub 2
 lda length
 comp zero
 jeq endfil
 jsub 4
 j cloop
endfil lda eof
 sta buffer
 lda three
 sta length
 jsub 3
 ldl retadr
 rsub zero
eof byte 45
 byte 4f
 byte 46
three word 3
zero word 0
retadr resw 1
length resw 1
buffer resb 256
 end start
