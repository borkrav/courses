#lang scheme

(provide iempty iempty? icons ifirst irest ilength iappend)

(define-struct list-node (first rest length) #:mutable)

(define counter 1)

(define (icons number list)
  (define r (make-list-node number list counter))
  (set! counter (+ 1 counter))
  r
  )

(define (ifirst list)
  (list-node-first list)
  )

(define (irest list)
  (list-node-rest list)
  )

(define (iempty) 
  (define r (make-list-node null null null))
  (set! counter 1)
  r
  )

(define (iempty? list)
  (cond [(null? (list-node-first list)) true]
        [else false]
        )
  )

(define (ilength list)
  (cond [(boolean=? true (iempty? list)) 0]
        [else (list-node-length list)]
        
        )
  )



(define result 0)

(define (iappend list1 list2)
  (set! result (appender list1 list2))
  
  (cond [(and (boolean=? false (iempty? list1))
              (boolean=? true (iempty? list2)))
         (set-list-node-length! result (ilength list1))]
        
        [(and (boolean=? true (iempty? list1))
              (boolean=? false (iempty? list2)))
         (set-list-node-length! result (ilength list2))]
        
        [(and (boolean=? false (iempty? list1))
              (boolean=? false (iempty? list2)))
         (set-list-node-length! result (+ (ilength list1)(ilength list2)))]
        
        )
  
  result
  )

(define (appender list1 list2)
  (cond [(empty? list1) list2]
        [else (icons (ifirst list1) (appender (irest list1) list2))]
        )
  )

(define a (icons 1 (icons 2 (iempty))))
(define b (icons 5 (icons 6 (iempty))))
(define c (iempty))

(define e (iappend a b))
(define f (iappend e c))


