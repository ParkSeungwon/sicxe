macro mymacro a,b
	ldch a
	ldch b
MEND
	START 1000
	mymacro data,store
	mymacro store,store
	ldch data
	stch store
data byte 3
store byte C'A'
	end
