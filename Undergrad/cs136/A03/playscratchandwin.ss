#lang scheme

;; (playgame n) draws as many cards as necessary to accumulate n
;;              distinct ones, and produces cardlist such that
;;              (collect-prize cardlist) produces 'prize

(require "scratchandwin.ss")
;(require "prize.ss") ; for testing
(provide playgame)

(define (playgame n)
  
  (define goal (build-list n (lambda (x) (+ 1 x))))
  
  (define (playgame-tail n goal card-list)
    
    (define card (drawcard n))
    (define s-card (first (scratch card)))
    
    (cond [(empty? goal) card-list]
          [(member s-card goal) (playgame-tail n (remove s-card goal) (cons card card-list))]
          [else (playgame-tail n goal card-list)]
          
          )
    )
  (playgame-tail n goal empty)
  
  )

;O(n^2) so far
