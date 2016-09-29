#lang scheme
(require "ordered-set.ss" "total-order.ss")

(define set os-empty)
(define temp-info 0)

(define (main set)
  (define cmd (read))
  (define name null)
  (define score null)
  
  (cond [(eof-object? cmd) (printf "")]
  
        [(symbol=? 'score cmd)   ;score/name entery algorithm
        
        (set! name (read))
        (set! score (read))
        
        (cond [(os-member set (to-hide name))
         (set! temp-info (to-info (os-before set (to-hide (string->symbol (string-append (symbol->string name) "!"))))))
         (cond [(> score temp-info)  
                 (set! set (os-difference set (os-singleton (to-create name 0))))
                 (set! set (os-union (os-singleton (to-create name score)) set))
                 (main set)]
               [else (main set)])]
        [else
        (set! set (os-union set (os-singleton (to-create name score))))
        (main set)])]
        
        
                                                 
        [(symbol=? 'best cmd)
         (set! name (read))
         
         (cond [(os-member set (to-hide name))
                (set! score (to-info (os-before set (to-hide (string->symbol (string-append (symbol->string name) "!"))))))
                (printf "best ~a ~a" name score) (newline) (main set)]
               [else (printf "best ~a ?" name) (newline) (main set)])]
        
        [(symbol=? 'highscore cmd) (printf "highscore ~a" (to-info (os-op set))) (newline) (main set)]
        

        )
  )

(define (os-print set)
  (cond [(string=? (symbol->string (to-unhide to-max-ident)) (symbol->string (to-unhide (os-max set)))) (printf "")]
        [else 
         (printf "~a ~a" (to-unhide (os-min set)) (to-info (os-min set)))
         (newline)
         (os-print (os-difference set (os-singleton (os-min set))))]
        )
  )


(main set)




