	start 1000
first lda   seven
	sta alpha
	lda two
	add incr
	sta beta
	lda gamma
	sub two
	sta delta
	ldch charx
	stch cha
seven word 7
two word 2
alpha resw 1
beta resw 1
gamma word 10
delta resw 1
incr word 3
cha resb 1
charx byte 78
	end first

