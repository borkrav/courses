#lang scheme
(require "ordered-set.ss" "total-order.ss")

(define set os-empty)
(define temp-info 0)
(define leaderset os-empty)
(define highscore 0)

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
        
        [(symbol=? 'highscore cmd) (cond [(= (to-info (os-op set)) -1000000000) (printf "highscore ?") (newline) (main set)]
                                         [else (printf "highscore ~a" (to-info (os-op set))) (newline) (main set)])]
                
                
        [(symbol=? 'disqualify cmd)
         (set! name (read))
         (set! set (os-difference set (os-singleton (to-create name 0))))
         (main set)]
         
        [(symbol=? 'leaders cmd)
         (set! leaderset set)
         (set! highscore (to-info (os-op leaderset)))
         (printf "leaders")
         (cond [(not (symbol=? '? (to-unhide (os-op leaderset)))) (display (leadhelper leaderset))]
               [else (printf " ?")])
         (newline)
         (main set)]         

        )
  )
  
(define (leadhelper set)
  (define leader (os-op set))
  (cond [(and (= highscore (to-info leader))) 
         (printf " ~a" (to-unhide leader))
         (leadhelper (os-difference set (os-singleton leader)))]
        [else ""])
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




