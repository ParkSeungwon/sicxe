 start 1000
loop ldch string,x
 wd string
 jsub 20
 comp end_string
 jeq quit
 j loop
quit lda string
data word 0
string byte c'Hello.'
end_string word 2e
 end 
