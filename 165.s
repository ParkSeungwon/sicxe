 start 1000
loop ldch string,x
 wd string
 jsub 20
 comp end_string
 stx garage
 ldx three
 sta store,x
 jsub 20
 jsub 20
 jsub 20
 stl store,x
 ldx garage
 jeq quit
 j loop
 ldx three
 lda store,x
 jsub 20
 jsub 20
 jsub 20
 ldl store,x
 ldx garage
quit word 0
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
 byte 21
garage resw 3
three word 3
 end 
