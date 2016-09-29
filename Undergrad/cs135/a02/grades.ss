;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname grades) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;;**************************************************************************************************************
;; CS 135 Assignment 2, Question 4
;; Boris Kravchenko 20332359
;; Final mark calculator
;;**************************************************************************************************************

;final-CS135-grade num num num num num -> num
;a function that takes in the students midterm 1, midterm 2, assignmnent, exam and participation grades, and outputs a final average. If the student scored less then 50% overall on the exams, or scored less then 50% overall on assignments, the function outputs 46.

;examples
(check-expect (final-CS135-grade 90 80 70 60 50) 68.5)
(check-expect (final-CS135-grade 90 90 90 0 90) 46)

(define (final-CS135-grade m1 m2 as ex part)
  (cond 
    [(and (> (+ (* m1 0.1) (* m2 0.2) (* as 0.2) (* ex 0.45) (* part 0.05)) 46) 
          (or (> 50 as) (> 50 (/ (+ (* m1 0.1) (* m2 0.2) (* ex 0.45)) 0.75)))) 46]
    
    [else (+ (* m1 0.1) (* m2 0.2) (* as 0.2) (* ex 0.45) (* part 0.05))]))

;tests
(check-expect (final-CS135-grade 50 50 50 50 50) 50)
(check-expect (final-CS135-grade 70 80 0 100 90) 46)
(check-expect (final-CS135-grade 50 50 100 49 100) 46)
(check-expect (final-CS135-grade 11 22 0 0 55) 8.25)
(check-expect (final-CS135-grade 80 90 96 75 100) 83.95)


;clicker-marks num num -> num
;a function that takes in the number of right and wrong answers by a student, and computes a final participation mark. 40 questions have been asked, and only the top 75% are being considered. 

;examples
(check-expect (clicker-marks 40 0) 100)
(check-expect (clicker-marks 25 15) 275/3)

(define (clicker-marks right wrong)
  (* (/ (+ (* (cond
                [(< 30 right) 30]
                [else right]) 
              2)
           (cond 
             [(and (< 0 wrong)(< ( - 30 right) wrong)) (- 30 right)]
             [else wrong])) 
        60) 
     100)
  )

;tests
(check-expect (clicker-marks 0 0) 0)
(check-expect (clicker-marks 10 0) 100/3)
(check-expect (clicker-marks 0 40) 50)
(check-expect (clicker-marks 30 10) 100)
(check-expect (clicker-marks 15 15) 75)
(check-expect (clicker-marks 5 35) 175/3)