 START   1000           
FIRST      STL       RETADR     
CLOOP    JSUB     RDREC        
	LDA       LENGTH     
	COMP    ZERO           
   JEQ       ENDFIL        
    JSUB     WRREC        
     J            CLOOP         
ENDFIL   LDA      EOF              
	STA      BUFFER       
	LDA      THREE          
	STA       LENGTH       
	JSUB      WRREC        
    LDL       RETADR       
    RSUB
EOF          BYTE      C'E'
	BYTE      C'O'
	BYTE      C'F'
THREE      WORD    3 
ZERO        WORD    0
RETADR   RESW     1
LENGTH   RESW     1
BUFFER    RESB      4096         
   end
