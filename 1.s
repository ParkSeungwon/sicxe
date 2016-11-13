macro save store,three
 stx store
 ldx three
 sta store,x
 jsub 2
 jsub 2
 jsub 2
 stl store,x
 ldx store
mend
macro load store,three
 ldx three
 lda store,x
 jsub 2
 jsub 2
 jsub 2
 ldl store,x
 ldx store
mend
 start 1000
loop ldch string,x
 wd string
 jsub 2 //x++
 comp end_string
 save garage,three
 jeq quit
 j loop
 load garage,three
quit word 0
string byte c'Hello'
 byte 20
 byte c'World!'
end_string byte 0
 byte 0
 byte c'!'
garage resw 3
three word 3
 end 
