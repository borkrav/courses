#lang scheme
(require "pointerplay.ss")
;(require "bst-stuff.ss") ;;stuff for testing
(provide betweenbst)

(define (betweenbst i j t)
  (cond [(empty? t) false]
        [(or (and (>= (node-data t) i) (<= (node-data t) j))
             (= (node-data t) i)
             (= (node-data t) j)) true]
        [(> (node-data t) j) (betweenbst i j (node-left t))] ;go left
        [(< (node-data t) i) (betweenbst i j (node-right t))] ;go right
        )
  )

