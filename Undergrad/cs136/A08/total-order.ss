#lang scheme

;; Total Order ADT used by Ordered Set ADT

;; Must provide:
;;   a membership predicate
;;   a total order
;;   min and max functions with identities
;;   user-defined associative operator and identity
;;
;;   any other operations required by the user
;;       e.g. to-hide and to-unhide

(provide to? to< to<= to> to> to>= to= to!= to-min to-min-ident 
         to-max to-max-ident to-op to-op-ident to-hide to-unhide to-info to-create)

;; For this example, we use a number hidden in a struct

   (define-struct to-rep (number info))
   (define (to-unhide x) (to-rep-number x))
   (define (to-info x) (to-rep-info x))
   (define (to-hide x) (make-to-rep x 1))
   (define (to-create x y) (make-to-rep x y))

;; membership predicate

   (define (to? x) (and (to-rep? x) (symbol? (to-unhide x))))

;; defining relation must be total, reflexive, transitive
   (define (to<= a b) 
     (cond
       [(string=? (symbol->string (to-unhide a)) (symbol->string (to-unhide to-min-ident))) false]
       [(string=? (symbol->string (to-unhide b)) (symbol->string (to-unhide to-min-ident))) true]
       [(string=? (symbol->string (to-unhide b)) (symbol->string (to-unhide to-max-ident))) false]
       [(string=? (symbol->string (to-unhide a)) (symbol->string (to-unhide to-max-ident))) true]
       [else (string<=? (symbol->string(to-unhide a)) (symbol->string(to-unhide b)))]))

;; derived relations
   (define (to> a b) (not (to<= a b)))
   (define (to= a b) (and (to<= a b) (to<= b a)))
   (define (to>= a b) (to<= b a))
   (define (to< a b) (to> b a))
   (define (to!= a b) (not (to= a b)))

;; min/max functions and identities
   
   (define (to-min a b) (if (to< a b) a b))
   (define to-min-ident (to-hide '!))

   (define (to-max a b) (if (to< a b) b a))
   (define to-max-ident (to-hide '~))

;; user-defined associative operator and identity

;; for this example we just add the secret numbers

   (define name 0)
   (define score 0)
   
   (define (to-op a b) 
    
   (cond
       [(< (to-rep-info a) (to-rep-info b))
        (set! name (to-unhide b))
        (set! score (to-info b))]
       [else (set! name (to-unhide a))
             (set! score (to-info a))])
        
   (to-create name score))
  
   (define to-op-ident (to-create '? -1000000000))

