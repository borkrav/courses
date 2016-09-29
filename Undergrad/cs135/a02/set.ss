;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname set) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;;**************************************************************************************************************
;; CS 135 Assignment 2, Question 3
;; Boris Kravchenko 20332359
;; Set Game Function
;;**************************************************************************************************************

; set-test: symbol symbol sybmol sybmol symbol symbol sybmol symbol symbol symbol symbol symbol -> string
; a function that takes in 12 symbols, 1-4 describe colour, shape, fill and number of first card, 5-8 describe second card, 9-12 describe third. A string is returned that says if the cards form a set, or if there is a problem.

;examples
(check-expect (set-test 'green 'diamond 'hollow 'one 'green 'diamond 'hollow 'two 'green 'diamond 'hollow 'three) "set")
(check-expect (set-test 'red 'oval 'solid 'one 'red 'diamond 'solid 'two 'green 'squiggle 'solid 'three) "Problem with colours")
(check-expect (set-test 'red 'oval 'hollow 'three 'green 'diamond 'lines 'three 'purple 'squigle 'solid 'three) "set")


(define (set-test col-1 shape-1 fill-1 num-1 col-2 shape-2 fill-2 num-2 col-3 shape-3 fill-3 num-3)
  (cond
    [(or (and (equal? col-1 col-2) (not (equal? col-1 col-3))) 
         (and (equal? col-2 col-3) (not (equal? col-2 col-1)))
         (and (equal? col-1 col-3) (not (equal? col-1 col-2))))
     "Problem with colours"]
    
    [(or (and (equal? shape-1 shape-2) (not (equal? shape-1 shape-3)))
         (and (equal? shape-2 shape-3) (not (equal? shape-2 shape-1)))
         (and (equal? shape-1 shape-3) (not (equal? shape-1 shape-2))))
     "Problem with shapes"]
    
    [(or (and (equal? fill-1 fill-2) (not (equal? fill-1 fill-3)))
         (and (equal? fill-2 fill-3) (not (equal? fill-2 fill-1)))
         (and (equal? fill-1 fill-3) (not (equal? fill-1 fill-2))))
     "Problem with fills"]
    
    [(or (and (equal? num-1 num-2) (not (equal? num-1 num-3)))
         (and (equal? num-2 num-3) (not (equal? num-2 num-1)))
         (and (equal? num-1 num-3) (not (equal? num-1 num-2))))
     "Problem with numbers"]
    
    [else "Set"]))

;; first condition checks if there are colour problems, if there are 2 same and one different, second does the same for shapes, third does colours and forth does fills. If there are no problems, it's a set.


;tests
(check-expect (set-test 'red 'oval 'solid 'one 'red 'oval 'solid 'one 'green 'oval 'solid 'one) "Problem with colours")
(check-expect (set-test 'red 'oval 'solid 'one 'red 'diamond 'solid 'two 'red 'oval 'solid 'three) "Problem with shapes")
(check-expect (set-test 'red 'oval 'solid 'one 'red 'oval 'lines 'two 'red 'oval 'solid 'three) "Problem with fills")
(check-expect (set-test 'red 'oval 'solid 'one 'red 'oval 'solid 'two 'red 'oval 'solid 'one) "Problem with numbers")
(check-expect (set-test 'red 'diamond 'hollow 'one 'green 'oval 'solid 'two 'purple 'squigly 'lines 'three) "set")
(check-expect (set-test 'red 'oval 'solid 'one 'green 'oval 'solid 'two 'purple 'oval 'solid 'three) "set")
(check-expect (set-test 'red 'diamond 'lines 'one 'red 'oval 'lines 'two 'green 'diamond 'solid 'one) "Problem with colours")