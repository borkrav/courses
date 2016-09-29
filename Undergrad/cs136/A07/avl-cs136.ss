#lang scheme
;; AVL Tree Code Version 0.1
;; Copyright Gordon V. Cormack, 2008, 2010
;; For use by students in CS136 Winter 2010
;; Any other use, or publication, prohibited
;; provides immutable tree operations from "pointerplay.ss"
;; provides AVL operations (insertavl t) and (deleteavl t)
;;   with worst-case running time O(log n) where n is the number
;;   of nodes in t

(provide node-data node-left node-right pprint) ;; pointerplay operations
(provide insertavl deleteavl)                   ;; avl operations

;; (insertavl t k) inserts key k into avl tree t, produces new avl tree
;; (deleteavl t k) deletes key k from avl tree t, procudes new avl tree

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; this is the implementation of the various AVL tree operations
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define-struct node (data height left right))

(define (height t) (if (empty? t) 0 (node-height t)))

(define (build-node d L R) (make-node d (add1 (max (height L) (height R))) L R))

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
    [(< d (node-data t)) (rebalance (subst-L t (insertavl (node-left t) d)))]
    [else (rebalance (subst-R t (insertavl (node-right t) d)))]))

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
    [(< d (node-data t)) (rebalance (subst-L t (deleteavl (node-left t) d)))]
    [(> d (node-data t)) (rebalance (subst-R t (deleteavl (node-right t) d)))]
    [(empty? (node-right t)) (rebalance (node-left t))]
    [(empty? (node-left t)) (rebalance (node-right t))]
    [else
      (rebalance
        (build-node (get_rightmost (node-left t)) (remove_rightmost (node-left t)) (node-right t)))]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; pprint stuff directly copied from pointerplay.ss
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define counter 0)

(define alist (list (list empty 'null)))

(define (traverse x plst)
  (cond
    [(or (empty? x) (assv x alist) (assv x plst)) plst]
    [else (set! counter (add1 counter))
          (let ([res (traverse (node-left x)
                               (cons (list x counter) plst))])
            (traverse (node-right x) res))]))

(define (preset)
  (set! counter 0)
  (set! alist (list (list empty 'null))))

(define (pprint label x)
  (let ([res (traverse x empty)])
    (set! alist (append res alist))
    (for-each print-item res)
    (printf "~a:\t#~a\n" label (second (assv x alist)))))

(define (print-item p)
  (printf "#~a:\t~a\t#~a\t#~a\n"
          (second p)
          (node-data (first p))
          (second (assv (node-left (first p)) alist))
          (second (assv (node-right (first p)) alist))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; end of pprint stuff copied from pointerplay.ss
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
