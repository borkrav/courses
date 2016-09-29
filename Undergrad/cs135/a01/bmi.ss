;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname bmi) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;;**************************************************************************************************************
;; Boris Kravchenko
;; 20332359
;; A00 - Body Mass Index Function
;;**************************************************************************************************************

(define (mass-conv mass)
  (* mass 0.45359237)) ;function that takes converts lb into kg

(define (height-conv height)
  (* height 0.0254)) ;function that converts inches into meters

(define (inch-combine feet inches)
  (+ (* feet 12) inches)) ;function that combines feet/inches into inches



(define (body-mass-index mass height) ; must enter mass in KG, height in M
  (/ mass (* height height))) ;function that calculates BMI

(define (body-mass-index-imperial mass feet inches) ; must enter mass in lb, height in feet and inches
  (body-mass-index 
   (mass-conv mass) (height-conv (inch-combine feet inches)))) ;function that calculates BMI using imperial units