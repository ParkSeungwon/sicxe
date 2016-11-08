	start 1000
RDREC     LDX       ZERO           
         LDA       ZERO           
RLOOP       TD         INPUT           
        JEQ       RLOOP          
            RD        INPUT           
          COMP   ZERO            
        JEQ       EXIT              
        STCH    BUFFER     
       TIX       MAXLEN       
       JTL       RLOOP           
EXIT          STX      LENGTH        
      RSUB                          
INPUT       BYTE    F1
MAXLEN  WORD   4096               
WRREC   LDX      ZERO            
WLOOP   TD        OUTPUT        
    JEQ       WLOOP         
         LDCH   BUFFER     
        WD       OUTPUT        
       TIX       LENGTH        
      JLT       WLOOP          
       RSUB                          
OUTPUT  BYTE    05
      END                  
