#lang scheme
(require "avl-cs136.ss")
(provide bet winner?)

(define betlist empty)

(define (bet mid)
  (cond [(betweenbst (- mid 5) (+ mid 5) betlist) false]
        [else (set! betlist (insertavl betlist mid))
              true]
        )
  )

(define (winner? score)
  (cond [(betweenbst (- score 5) (+ score 5) betlist) true]
        [else false]
        )
  )

; search algorithm for any BST, works for AVL implementation
(define (betweenbst i j t)
  (cond [(empty? t) false]
        [(or (and (>= (node-data t) i) (<= (node-data t) j))
             (= (node-data t) i)
             (= (node-data t) j)) true]
        [(> (node-data t) j) (betweenbst i j (node-left t))] ;go left
        [(< (node-data t) i) (betweenbst i j (node-right t))] ;go right
        )
  )