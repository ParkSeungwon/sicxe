 start 1000 X+1 routine
 sta backup
 stx backup2
 lda backup2
 add one
 sta backup2
 lda backup
 ldx backup2
 rsub 
backup word 0
backup2 word 0
one word 1
 end
