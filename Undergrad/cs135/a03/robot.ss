;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname robot) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
; robot posn symbol num -> posn
; a function that takes the current position of the robot, as well as the direction and magnitude of motion. It then it moves the current position in the specified direction and returns the new postion.

;examples
(check-expect (robot (make-posn 0 0) 'north 10) (make-posn 0 10))
(check-expect (robot (make-posn 0 0) 'south 5) (make-posn 0 -5))

(define (robot current-posn direction distance)
  (cond [(symbol=? direction 'north) (make-posn (posn-x current-posn) (+ (posn-y current-posn) distance))]
        [(symbol=? direction 'south) (make-posn (posn-x current-posn) (- (posn-y current-posn) distance))]
        [(symbol=? direction 'east) (make-posn (+ (posn-x current-posn) distance) (posn-y current-posn))]
        [(symbol=? direction 'west) (make-posn (- (posn-x current-posn) distance) (posn-y current-posn))]))

;tests
(check-expect (robot (make-posn -10 -15) 'north 30) (make-posn -10 15))
(check-expect (robot (make-posn -1 -1) 'south 10) (make-posn -1 -11))
(check-expect (robot (make-posn 30 20) 'east 70) (make-posn 100 20))
(check-expect (robot (make-posn 50 60) 'west 50) (make-posn 0 60))