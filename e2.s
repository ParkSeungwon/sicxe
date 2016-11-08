 start 1000
rdrec ldx zero
 lda zero
rloop td input
 jeq rloop
 rd input
 comp zero
 jeq exit
 stch buffer
 tix maxlen
 jtl rloop
exit stx length
 rsub 
input byte f1
maxlen word 4096
wrrec ldx zero
wloop td output
 jeq wloop
 ldch buffer
 wd output
 tix length
 jlt wloop
 rsub 
output byte 05
 end 
