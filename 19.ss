 start 1000
 ldch byte
 ldx string
loop jsub 20
 stx index
 ldch index
 wd index
 comp end_string
 jeq quit
 j loop
quit lda index
data word 0
string byte 48
 byte 65
 byte 6c
 byte 6c
 byte 6f
 byte 2e
end_string byte 2e
index word 0
 end 
