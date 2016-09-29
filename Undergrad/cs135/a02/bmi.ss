;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname bmi) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;;**************************************************************************************************************
;; CS 135 Assignment 2, Question 2
;; Boris Kravchenko 20332359
;; Body Mass Index Function
;;**************************************************************************************************************

;Defined constants
(define mass-conv 0.45359237) ;number used for mass conversion
(define height-conv 0.0254) ;number used for height conversion

; body-mass-index: num num -> num
; a function that takes two numbers, mass(kg) and heigh (h) and computes the body mass index value

;example
(check-expect (body-mass-index 100 1) 100)

(define (body-mass-index mass height) ; must enter mass in KG, height in M
  (/ mass (* height height))) ;function that calculates BMI

;tests
(check-expect (body-mass-index 81 1.8) 25.0)
(check-expect (body-mass-index 100 2) 25.0) 


; bmi-classify: num num -> symbol
; a function that takes two numbers, mass(kg) and height(m) and computes the body mass index category
;examples

(check-expect (bmi-classify 70 1.8) 'Normal)
(check-expect (bmi-classify 100 1.8) 'Obese)

(define (bmi-classify mass height)
  (cond [(and (< 0 (body-mass-index mass height)) 
              (>= 18.5 (body-mass-index mass height)))
         'Underweight]
        
        [(and (< 18.5 (body-mass-index mass height))
              (>= 25.0 (body-mass-index mass height))) 
         'Normal]
        
        [(and (< 25.0 (body-mass-index mass height))
              (>= 30.0 (body-mass-index mass height)))
         'Overweight]
        
        [(< 30.0 (body-mass-index mass height))
         'Obese]
        
        [else 'Error]))


;tests                               
(check-expect (bmi-classify -100 -10) 'Error)
(check-expect (bmi-classify 10 10) 'Underweight)
(check-expect (bmi-classify 70  1.75) 'Normal)
(check-expect (bmi-classify 85 1.75) 'Overweight)
(check-expect (bmi-classify 130 1.75) 'Obese)
(check-expect (bmi-classify 59.94 1.8) 'Underweight) ;bmi of 18.5
(check-expect (bmi-classify 81 1.8) 'Normal) ;bmi of 25.0
(check-expect (bmi-classify 97.2 1.8) 'Overweight) ;bmi of 30.0

; body-mass-index2: num num -> num
; a function that takes in a mass and height, and determines the units the user is inputting by checking which range the height falls into. It returns the calculated the body mass index.  Mass can be in kg or lb, height can be in meters, inches or feet.

;example
(check-expect (body-mass-index 81 1.8) 25.0)
(check-expect (body-mass-index2 66.15 2.1) 15.0)

(define (body-mass-index2 mass height)
  (cond [(and (< 1.2 height) 
              (>= 2.5 height)) 
         (body-mass-index mass height)]
        
        [(and (< 4 height) 
              (>= 8 height))
         (body-mass-index (* mass mass-conv) (* (* 12 height) height-conv))]
        
        [(and (< 48 height) 
              (>= 96 height)) 
         (body-mass-index (* mass mass-conv) (* height height-conv))]
        
        [else 0])
  )


;tests
(check-expect (body-mass-index2 -10 -10) 0)
(check-expect (body-mass-index2  100 2) 25)
; note, operations with primitive operators are used to state the exact answer.
(check-expect (body-mass-index2 100 5) ( / (* 100 0.45359237) (sqr (* (* 12 5) 0.0254))))  
(check-expect (body-mass-index2 180 60) ( / (* 180 0.45359237) (sqr (*  60 0.0254))))
(check-expect (body-mass-index2 60 2.5) 9.6)
(check-expect (body-mass-index2 260 8) ( / (* 260 0.45359237) (sqr (* (* 12 8) 0.0254))))
(check-expect (body-mass-index2 300 96) ( / (* 300 0.45359237) (sqr (*  96 0.0254))))


