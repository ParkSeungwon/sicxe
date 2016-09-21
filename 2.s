	start	1000
first	lda data1
	add data2
	sta sum
	lda data1
	sub data2
	sta diff
data1 word 8
data2 word 7
sum resw 1
diff resw 1
	end	first
