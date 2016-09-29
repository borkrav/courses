#lang scheme

(require "scanner.ss")

(define (add4) (set! linecount (+ 4 linecount)))


(define tokenline 0)
(define id 'blank)
(define value 0)
(define stringline 'blank)

(define-struct line (number tokenline) #:transparent)
(define program empty)
(define linecount 0)
(define linecurrent 0)
(define labeltable (make-hash))
(define exit 0)
(define type 0)

;;pass 1 analizes the lines, doing labels and saving instructions
(define (pass1)
  
  (set! stringline (read-line))
  
  (cond
    [(eof-object? stringline) (set! program (reverse program)) (pass2)]
    [(string=? stringline "") (pass1)]
    [else (set! tokenline (scan stringline))
          
          (cond[(empty? tokenline) (pass1)]
               [else (analyze)])]))



; looks at current line, saves labels and instructions if valid, exits otherwise
(define (analyze)
  (set! id (token-kind (first tokenline)))
  (set! type (token-lexeme (first tokenline)))
  
  ;.word
  (cond
    [(and (symbol=? id 'dotword) 
          (not (empty? (rest tokenline))) 
          (= 2 (length tokenline))
          (or (symbol=? (token-kind (second tokenline)) 'hexint)
              (symbol=? (token-kind (second tokenline)) 'int)
              (symbol=? (token-kind (second tokenline)) 'id)))
     (add-line)
     
     ]
    
    ;jr and jalr
    
    [(and (symbol=? id 'id)
          (or (string=? (list->string type) "jr")(string=? (list->string type) "jalr"))
          (symbol=? (token-kind (second tokenline)) 'register))
   
     (add-line)]
    
    
    
    [(symbol=? id 'label)
     
     (set! value (token-lexeme (first tokenline))) ;these lines remove the colon
     (reverse value)
     (set! value (rest (reverse value)))
     (set! value (list->string (reverse value)))
     
     (cond [(not (= -1 (hash-ref labeltable value -1))) (fprintf (current-error-port) "ERROR: repeat label")(set! exit 1)]
           [else (hash-set! labeltable value linecount)])
     
     
     (cond [(= 1 exit) (display "")]
           [(< 1 (length tokenline)) ;if there's something after the label, send it to the analyzer
            (set! tokenline (rest tokenline))
            ; (display tokenline)
            (analyze)]
           [else (pass1)])
     
     ]
    
    [else (fprintf (current-error-port) "ERROR: invalid input")]
    )
  )


(define (add-line)
  (set! program (cons (make-line linecount tokenline) program))
  (add4)
  (pass1))



;converts the program to ML
(define (pass2)
  (cond [(empty? program) (display "")]
        
        [else (set! tokenline (line-tokenline (first program)))
              (set! id (token-kind (first tokenline)))
              (set! type (token-lexeme (first tokenline)))
              (set! linecurrent (line-number (first program)))
              (set! program (rest program))
              
              (cond
                ;.word
                [(symbol=? id 'dotword)
                 (cond [(symbol=? (token-kind (second tokenline)) 'id) 
                        (grab-label)]            
                       [else (set! value (token-lexeme (second tokenline)))])    
                 (cond [(= -1 value) (fprintf (current-error-port) "ERROR: undefined label")]) 
                 (cond [(< value 0) (write-ml (+ (expt 2 31) (- #x80000000 (- 0 value))))]
                       [else (write-ml value)])
                 (pass2)]
                
                ;jr
                [(string=? (list->string type) "jr")
                 (set! value (token-lexeme (second tokenline)))
                 (set! value (bitwise-ior (arithmetic-shift value 21) 8))
                 (write-ml value)
                 (pass2)]
                 
                 ;jalr
                [(string=? (list->string type) "jalr")
                 (set! value (token-lexeme (second tokenline)))
                 (set! value (bitwise-ior (arithmetic-shift value 21) 9))
                 (write-ml value)
                 (pass2)]
                

                [else (fprintf (current-error-port) "ERROR: invalid input")])
              
              ]
        
        
        )
  )

(define (grab-label)
  (set! value (list->string (token-lexeme (second tokenline))))
  (set! value (hash-ref labeltable value -1)))


(define (write-ml word)
  (write-byte (bitwise-and (arithmetic-shift word -24) #xff))
  (write-byte (bitwise-and (arithmetic-shift word -16) #xff))
  (write-byte (bitwise-and (arithmetic-shift word -8) #xff))
  (write-byte (bitwise-and word #xff)))


(define (print-hash)
  (hash-for-each labeltable 
                 (lambda (x y)
                   (fprintf (current-error-port) "~a ~a\n" x y))))



(define (write-binary value)
  (define length (- 32 (integer-length value)))
  (define (pad counter)
    (cond [(= counter 0) (display "")]
          [else (display 0)
                (pad (- counter 1))
                ]
          )
    )
  (pad length)
  
  (display (format "~b\n" value)))






(pass1)

