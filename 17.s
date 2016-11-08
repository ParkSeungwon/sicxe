 start 1000
 ldch byte
 ldx index
loop stx index
 ldch index
 wd index
 jsub 20
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
index word 1021
 end 
