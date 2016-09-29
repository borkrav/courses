#lang scheme

(require "pointerplay.ss")

(define x (make-node 123 empty empty))

(define y (make-node 456 empty (make-node 789 empty empty)))

(define z (make-node 456 empty (make-node 789 empty (make-node 987 empty empty))))


(set-node-left! x y)
(set-node-right! x (node-right y))

(set-node-left! (node-right y) x)
(set-node-right! (node-right y) (node-right (node-right z)))

(set-node-left! (node-right z) (node-right y))

(pprint 'x x)
(pprint 'y y)
(pprint 'z z)