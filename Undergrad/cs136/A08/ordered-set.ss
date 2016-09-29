#lang scheme

;; Ordered set ADT
;; based on

;; AVL Tree Code Version 0.1
;; Copyright Gordon V. Cormack, 2008, 2010
;; For use by students in CS136 Winter 2010
;; Any other use, or publication, prohibited
;; provides immutable tree operations from "pointerplay.ss"
;; provides AVL operations (insertavl t) and (deleteavl t)
;;   with worst-case running time O(log n) where n is the number
;;   of nodes in t

;; user must define total-order.ss

(require "total-order.ss")

;; ordered set operations

(provide os-empty os-singleton os-member os-union os-intersection
         os-difference os-min os-max os-after os-before os-op)  

;; os-empty         an empty set
;; (os-singleton e) produces a set with one element e
;; (os-member s e)  produces true if e is a member of s; false otherwise
;; (os-union s t)   produces union of s and t in time 
;;                                  O(min(|s|,|t|) log max(|s|,|t|)
;; (os-intersection s t) produces intersection of s and t in time 
;;                                  O(min(|s|,|t|) log max(|s|,|t|)
;; (os-difference s t)   produces difference  s \ t in time 
;;                                  O(min(|s|,|t|) log max(|s|,|t|)
;; (os-min s)       produces the to-min element of s, or to-min-ident
;;                        running time:  O(log |s|)
;; (os-max s)       produces the to-max element of s, or to-max-ident
;;                        running time:  O(log |s|)
;; (os-after s e)   produces the to-min element os s which is to> than e
;;                        running time:  O(log |s|)
;; (os-before s e)  produces the to-max element os s which is to< than e
;;                        running time:  O(log |s|)
;; (os-op)          produces the result of applying to-op over all e in s
;;                        running time:  O(1)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; this is the implementation of the various AVL tree operations
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-struct node (data height op-val left right))

(define (height t) (if (empty? t) 0 (node-height t)))

(define (build-node d L R) (make-node d (add1 (max (height L) (height R))) (to-op (to-op (os-op L) d) (os-op R)) L R))

(define (subst-L t p) (build-node (node-data t) p (node-right t)))

(define (subst-R t p) (build-node (node-data t) (node-left t) p))

(define (raise_right t)
  (define tt (subst-R t (node-left (node-right t))))
  (subst-L (node-right t) tt))

(define (raise_left t)
  (define tt (subst-L t (node-right (node-left t))))
  (subst-R (node-left t) tt))

(define (rebalance t)
  (cond
    [(empty? t) t]
    [(> (height (node-left t)) (add1 (height (node-right t))))
       (raise_left 
         (if (> (height (node-right (node-left t))) (height (node-left (node-left t))))
             (subst-L t (raise_right (node-left t))) t))]
    [(> (height (node-right t)) (add1 (height (node-left t))))
       (raise_right 
         (if (> (height (node-left (node-right t))) (height (node-right (node-right t))))
             (subst-R t (raise_left (node-right t))) t))]
    [else t]))

(define (insertavl t d)
  (cond
    [(empty? t) (build-node d empty empty)]
    [(to< d (node-data t)) (rebalance (subst-L t (insertavl (node-left t) d)))]
    [(to> d (node-data t)) (rebalance (subst-R t (insertavl (node-right t) d)))]
    [else t]))

(define (get_rightmost t)
  (cond
    [(empty? (node-right t)) (node-data t)]
    [else (get_rightmost (node-right t))]))

(define (remove_rightmost t)
  (cond
    [(empty? (node-right t)) (node-left t)]
    [else (rebalance (subst-R t (remove_rightmost (node-right t))))]))

(define (deleteavl t d)
  (cond
    [(empty? t) t]
    [(to< d (node-data t)) (rebalance (subst-L t (deleteavl (node-left t) d)))]
    [(to> d (node-data t)) (rebalance (subst-R t (deleteavl (node-right t) d)))]
    [(empty? (node-right t)) (rebalance (node-left t))]
    [(empty? (node-left t)) (rebalance (node-right t))]
    [else
      (rebalance
        (build-node (get_rightmost (node-left t)) (remove_rightmost (node-left t)) (node-right t)))]))

(define os-empty empty)
(define (os-singleton x) (if (to? x) (insertavl empty x) (void)))
(define (os-member t d)
  (cond
    [(empty? t) false]
    [(to< d (node-data t)) (os-member (node-left t) d)]
    [(to> d (node-data t)) (os-member (node-right t) d)]
    [else true]))

(define (os-min t)
  (cond
    [(empty? t) to-min-ident]
    [else (to-min (node-data t) (os-min (node-left t)))]))
(define (os-max t)
  (cond
    [(empty? t) to-max-ident]
    [else (to-max (node-data t) (os-max (node-right t)))]))

(define (os-after t d)
  (cond
    [(empty? t) to-min-ident]
    [(to> (node-data t) d) (to-min (node-data t) (os-after (node-left t) d))]
    [else (os-after (node-right t) d)]))

(define (os-before t d)
  (cond
    [(empty? t) to-max-ident]
    [(to< (node-data t) d) (to-max (node-data t) (os-before (node-right t) d))]
    [else (os-before (node-left t) d)]))

(define (os-union x y)
  (if (<= (height x) (height y)) (os-union-helper x y) (os-union-helper y x)))
(define (os-union-helper small big)
  (if (empty? small) 
    big
    (insertavl 
      (os-union-helper 
        (node-right small) 
        (os-union-helper (node-left small) big)) 
      (node-data small))))

(define (os-intersection x y)
  (if (<= (height x) (height y)) (os-intersection-helper x x y)
                      (os-intersection-helper y y x)))
(define (os-intersection-helper acc small big)
  (cond
    [(empty? small) acc]
    [(os-member big (node-data small)) (os-intersection-helper (os-intersection-helper acc (node-left small) big) (node-right small) big)]
    [else (os-intersection-helper (os-intersection-helper (deleteavl acc (node-data small)) (node-left small) big) (node-right small) big)]))


(define (os-difference x y)
  (if (<= (height x) (height y)) (os-difference-helper x x y)
                      (os-difference-helper x y x)))
(define (os-difference-helper acc small big)
  (cond
    [(empty? small) acc]
    [(not (os-member big (node-data small))) (os-difference-helper (os-difference-helper acc (node-left small) big) (node-right small) big)]
    [else (os-difference-helper (os-difference-helper (deleteavl acc (node-data small)) (node-left small) big) (node-right small) big)]))

(define (os-op-slow t)
  (cond
    [(empty? t) to-op-ident]
    [else (to-op (to-op (os-op (node-left t)) (node-data t)) (os-op (node-right t)))]))

(define (os-op t)
  (cond
    [(empty? t) to-op-ident]
    [else (node-op-val t)]))

(define (print t)
  (cond
    [(empty? t) (void)]
    [else
      (print (node-left t))
      (printf "~a\n" (to-unhide (node-data t)))
      (print (node-right t))]))
