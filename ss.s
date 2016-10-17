	start 1000
first lda zero
loop ldx index
	lda sum2
	addx newd 
	sta sum2
	lda index
	add three
	sta index
	comp d12
	jlt loop
table  word 4
	word 3
	word 2
	word 1
newd word 2
	word 2
	word 2
	word 2
	word 2
d12 word f
zero word 0
temp word 0
index resw 1
sum2 resw 1
three word 3
	end first

	start 1000
	ldch data
	stch store
data byte 3
store byte 1
	end
	start 1000
first lda zero
	sta index
loop ldx index
	lda temp
	addx table
	sta temp
	lda index
	add three
	sta index
	comp d12
	jlt loop
	lda temp
	sta sum
table  word 4
	word 3
	word 2
	word 1
newd word 2
	word 2
	word 2
	word 2
	word 2
d12 word c
zero word 0
temp word 0
sum resw 1
index resw 1
sum2 resw 1
three word 3
	end first

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
cha resb 1
	end first

