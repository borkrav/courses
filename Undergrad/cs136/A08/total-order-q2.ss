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
         to-max to-max-ident to-op to-op-ident to-hide to-unhide)

;; For this example, we use a number hidden in a struct

   (define-struct to-rep (hidden))
   (define (to-unhide x) (to-rep-hidden x))
   (define (to-hide x) (make-to-rep x))

;; membership predicate

   (define (to? x) (and (to-rep? x) (number? (to-rep-hidden x))))

;; defining relation must be total, reflexive, transitive
  ;; (define (to<= a b) (<= (to-rep-hidden a) (to-rep-hidden b)))

(define (to<= a b)

  (cond
    [(= (to-unhide a) (to-unhide to-min-ident)) false]
    [(= (to-unhide b) (to-unhide to-min-ident)) true]
    [(= (to-unhide b) (to-unhide to-max-ident)) false]
    [(= (to-unhide a) (to-unhide to-max-ident)) true]
    [else (binary-lex (binary-digit-list (to-unhide a)) (binary-digit-list (to-unhide b)))]
    )
 )

(define (binary-lex a b)
  (cond
    [(and (empty? a) (empty? b)) true]
    [(empty? a) true]
    [(empty? b) false]
    [(< (first a) (first b)) true]
    [(> (first a) (first b)) false]
    [else (binary-lex (rest a) (rest b))]
    )
 )

(define (binary-digit-list n)
  (cond
    [(zero? n) empty]
    [(even? n) (cons 0 (binary-digit-list (quotient n 2)))]
    [else (cons 1 (binary-digit-list (quotient n 2)))]))



;; derived relations
   (define (to> a b) (not (to<= a b)))
   (define (to= a b) (and (to<= a b) (to<= b a)))
   (define (to>= a b) (to<= b a))
   (define (to< a b) (to> b a))
   (define (to!= a b) (not (to= a b)))

;; min/max functions and identities
   
   (define (to-min a b) (if (to< a b) a b))
   (define to-min-ident (make-to-rep +inf.0))

   (define (to-max a b) (if (to< a b) b a))
   (define to-max-ident (make-to-rep -inf.0))

;; user-defined associative operator and identity

;; for this example we just add the secret numbers

   (define (to-op a b) (to-hide (+ (to-rep-hidden a) (to-rep-hidden b))))
   (define to-op-ident (to-hide 0))
   
   
   
   
;(to<= to-min-ident (to-hide 10))
;(to<= (to-hide 10) to-max-ident)
