#lang scheme
(require "pointerplay.ss")
(require "bst-stuff.ss") ;;stuff for testing

;checks if t follows the bst ordering invariant
(define (bst? t)
  (cond [(empty? t) true]
        [(and (empty? (node-left t)) (empty? (node-right t))) true]
        [(and (empty? (node-left t)) (>= (node-data t) (node-data (node-right t)))) false]
        [(and (empty? (node-right t)) (<= (node-data t) (node-data (node-left t)))) false]
        [(or (>= (node-data t) (node-data (node-right t))) (<= (node-data t) (node-data (node-left t)))) false]
        [else (and (bst? (node-left t)) (bst? (node-right t)))]
        )
  )

(define (lptsize t)
  (cond [(not (lpt? t)) false]
        [(empty? t) 0]
        [(else (+ 1 (lptsize (node-left t)) (lptsize (node-right t))))]
        )
  )

(define (lpt? t)
  (cond [(bst? t)]