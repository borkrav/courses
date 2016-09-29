#lang scheme
(require "pointerplay.ss")
(provide printbst memberbst test insertbst betweenbst)

(define (printbst t)
  (define (bst-printer t counter)
    (cond [(empty? t) (printf"")]
          [else
           (bst-printer (node-right t) (+ counter 1))
           (display (node-printer (node-data t) (* 2 counter)))
           (newline)
           (bst-printer (node-left t) (+ counter 1))]
          )
    )
  
  (define (node-printer value depth)
    (cond [(= 0 depth) value]
          [else (display " ")
                (node-printer value (- depth 1))]
          )
    )
  
  (bst-printer t 0)
  
  )


(define (memberbst i t)
  (cond [(empty? t) false]
        [(= i (node-data t)) true]
        [(< i (node-data t)) (memberbst i (node-left t))]
        [else (memberbst i (node-right t))]
        )
  )

(define (insertbst i t)
  (cond [(empty? t) (make-node i empty empty)]
        [(> (node-data t) i) (make-node (node-data t) (insertbst i (node-left t)) (node-right t))] ; go left
        [(< (node-data t) i) (make-node (node-data t) (node-left t) (insertbst i (node-right t)))] ; go right       
        )
  )

(define (betweenbst i j t)
  (cond [(empty? t) false]
        [(or (and (>= (node-data t) i) (<= (node-data t) j))
             (= (node-data t) i)
             (= (node-data t) j)) true]
        [(> (node-data t) j) (betweenbst i j (node-left t))] ;go left
        [(< (node-data t) i) (betweenbst i j (node-right t))] ;go right
        )
  )


(define test (make-node 4 (make-node 2 (make-node 1 empty empty) (make-node 3 empty empty))(make-node 6 (make-node 5 empty empty) (make-node 7 empty empty))))

