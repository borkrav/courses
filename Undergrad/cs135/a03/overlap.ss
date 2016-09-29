;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname overlap) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;circles-overlap? posn num posn num -> boolean
;a predicate that takes in the position of the center of the first circle, radius of first circle, position of the center of sencond circlea and radius of second circle, and returns a boolean indicating whether or not they overlap

;example
(check-expect (circles-overlap? (make-posn 1 2) 10 (make-posn 3 4) 10) true)
(check-expect (circles-overlap? (make-posn -100 -100) 10 (make-posn 100 100) 10) false)

(define (circles-overlap? center-one radius-one center-two radius-two)
  (cond 
    [(<= (+ (sqr (- (posn-x center-one) 
                         (posn-x center-two)))
            (sqr (- (posn-y center-one) 
                         (posn-y center-two))))
         (sqr (+ radius-one radius-two))) true]
    
    [else false]))


;tests 
(check-expect (circles-overlap? (make-posn 0 0) 0 (make-posn 0 0) 0) true)
(check-expect (circles-overlap? (make-posn 1 1) 1 (make-posn 3 3) 1) false)
(check-expect (circles-overlap? (make-posn -2 -2) 2 (make-posn -1 -1) 2) true)
(check-expect (circles-overlap? (make-posn 1 1) 1.5 (make-posn 3 3) 1.5) true)
