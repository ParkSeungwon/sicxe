macro mymacro a,b
	ldch	a
	ldch	b
MEND
	START	1000
	mymacro	data,store
	mymacro	store,store
	mymacro	fix,data
	ldch	data
	stch	store
data	byte	3
store	byte	C'A'
fix	byte	c't'
	end
