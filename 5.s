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

