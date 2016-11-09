 start 1000
loop ldch string,x
 wd string
 jsub 20
 comp end_string
 jeq quit
 j loop
quit lda string
data word 0
string byte 48
 byte 65
 byte 6c
 byte 6c
 byte 6f
 byte 20
 byte 57
 byte 6f
 byte 72
 byte 6c
 byte 64
 byte 21
end_string byte 0
 byte 0
 word c'!'
 end 
