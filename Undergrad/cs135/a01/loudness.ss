;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname loudness) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;;**************************************************************************************************************
;; Boris Kravchenko
;; 20332359
;; A00 - Loudness Calculator
;;**************************************************************************************************************


(define reference 2e-5) ; reference value of 2e-5 pascals

(define (pressure->loudness pressure)
  (* 20 (/ (log (/ pressure reference)) (log 10)))) ; converts pressure into decibels
