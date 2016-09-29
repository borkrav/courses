#lang scheme

(provide iempty iempty? icons_destroy ifirst irest_destroy ilength icopy iappend_destroy)

(define-struct list-node (first rest length tail) #:mutable #:transparent)

(define counter 1)
(define tail null)

(define (icons_destroy number list)
  (define r (make-list-node number (unbox list) counter null))
  (set! counter (+ 1 counter))
  (cond [(boolean=? (iempty? list) #t) (set! tail r)])
  (set-list-node-tail! r tail)      
  (box r)
  )

(define (ifirst list)
  (list-node-first (unbox list))
  )

(define (irest_destroy list)
  (define r (list-node-rest (unbox list)))
  (set-list-node-length! r (- (ilength list) 1))
  (set-list-node-tail! r (list-node-tail (unbox list)))
  (box r)
  )

(define (iempty) 
  (define r (box (make-list-node null null null null)))
  (set! counter 1)
  r
  )

(define (iempty? list)
  (cond [(null? (list-node-first (unbox list))) true]
        [else false]
        )
  )

(define (ilength list)
  (cond [(boolean=? true (iempty? list)) 0]
        [else (list-node-length (unbox list))]
        
        )
  )

(define (icopy list)
  
  (define copy (iempty))
  (define (copier list result)
    (cond [(iempty? list) (iempty)]
          [else
           (set! copy (icons_destroy (ifirst list) result))
           (copier (irest_destroy list) copy)])
    
    )
  (copier list copy)
  (copier copy (iempty))
  copy
  
  )


(define result 0)

(define (iappend_destroy list1 list2)
  
  
  (cond [(and (boolean=? false (iempty? list1))
              (boolean=? true (iempty? list2)))
         (set! result list1)
         (set-list-node-length! (unbox result) (ilength list1))]
        
        [(and (boolean=? true (iempty?  list1))
              (boolean=? false (iempty? list2)))
         (set! result list2)
         (set-list-node-length! (unbox result) (ilength list2))]
        
        [(and (boolean=? false (iempty? list1))
              (boolean=? false (iempty? list2)))
         
         (set-list-node-rest! (list-node-tail (unbox list1)) (unbox list2))
         
         (set! result list1)
         (set-list-node-length! (unbox result) (+ (ilength list1)(ilength list2)))
         (set-list-node-tail! (unbox result) (list-node-tail (unbox list2)))]
        
        [else 
         (set! result (iempty))]
        
        )
  
  result
  )

