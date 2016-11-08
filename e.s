 start 1000
first stl retadr
cloop jsub rdrec
 lda length
 comp zero
 jeq endfil
 jsub wrrec
 j cloop
endfil lda eof
 sta buffer
 lda three
 sta length
 jsub wrrec
 ldl retadr
 rsub 
 byte 45
 byte 4f
 byte 46
three word 3
zero word 0
retadr resw 1
length resw 1
buffer resb 4096
 byte 74
 byte 68
 byte 69
 byte 73
 byte 5f
 byte 69
 byte 73
 byte 5f
 byte 61
 byte 5f
 byte 74
 byte 65
 byte 73
 byte 74
 byte 5f
 byte 73
 byte 74
 byte 72
 byte 69
 byte 6e
 byte 67
 end 
