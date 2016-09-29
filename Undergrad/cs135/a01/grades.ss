;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname grades) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;;**************************************************************************************************************
;; Boris Kravchenko
;; 20332359
;; A00 - Mark Calculator
;;**************************************************************************************************************

(define participation 5) ; 5 percent for participation

(define (midterm-1 m1) ; calculates the % of mark gained from midterm 1
  (* m1 0.1))

(define (midterm-2 m2) ; calculates the % of mark gained from midterm 2
  (* m2 0.2))

(define (assignment as) ; calculates the % of mark gained from assigmnets
  (* as 0.2))

(define (exam ex) ; calculates the % of mark gained from the exam
  (* ex 0.45))

(define (final-CS135-grade m1 m2 as ex) 
  (+ (assignment as) (midterm-1 m1) (midterm-2 m2) (exam ex) participation)) ; adds the marks gained to get a final average

(define (final-exam-grade-needed-CS135 m1 m2 as)
 (/ (- 60 participation (assignment as) (midterm-1 m1) (midterm-2 m2)) 0.45)) ; subtracts all the marks gained from the passing grade, then divides the result by the exam weight