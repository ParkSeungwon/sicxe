macro mymacro a,b
	ldch a
	ldch b
MEND
	START 1000
	mymacro c,d
	mymacro e,f
	ldch data
	stch store
data byte 3
store byte 1
	end
