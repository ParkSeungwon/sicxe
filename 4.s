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

