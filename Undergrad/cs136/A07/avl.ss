#lang scheme
(require "pointerplay.ss")
(provide avl?)
;(require "bst-stuff.ss") ;;stuff for testing

;checks if t follows the bst ordering invariant
(define (bst-checker list)
  (cond [(empty? list) true]
        [(empty? (rest list)) true]
        [(>= (first list) (second list)) false]
        [else (bst-checker (rest list))]
  
  )
)

(define (bst? t)
  (bst-checker (flatten-bst t))
  )

(define (flatten-bst t)
  (cond [(empty? t) empty]
        [else (append (flatten-bst (node-left t)) (list (node-data t)) (flatten-bst (node-right t)))]
        )
  )
   
(define (tree-height t)
  (cond [(empty? t) 0]
        [else (max (+ 1 (tree-height (node-left t))) (+ 1 (tree-height (node-right t))))]
        )
  )

(define (avl? t)
  (cond [(empty? t) true]
        [(and (empty? (node-left t)) (< 1 (tree-height (node-right t)))) false]
        [(and (empty? (node-right t)) (< 1 (tree-height (node-left t)))) false]
        [(< 1 (abs (- (tree-height (node-left t)) (tree-height (node-right t))))) false]
        [else (and (bst? t) (avl? (node-left t)) (avl? (node-right t)))]
        )
  )

