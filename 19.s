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
string byte c'Hello.'
end_string byte c'.'
index word 1021
 end
