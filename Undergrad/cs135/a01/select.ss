;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname select) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;;**************************************************************************************************************
;; Boris Kravchenko
;; 20332359
;; A00 - Bonus - Arithmetic conditional
;;**************************************************************************************************************


(define (select a b c i)
  (+ (* a (/(* (- 1 i) (- 2 i)) (+ 2 i))) ; if i = 0, set coefficient of a to one. Otherwise (i = 1 or 2), set to zero
     (* b (* i (- 2 i)))                  ; if i = 1, set coefficient of b to one. Otherwise (i = 0 or 2), set to zero
     (* c (/ (* i (- i 1)) 2))))          ; if i = 2, set coefficient of c to one. Otherwise (i = 0 or 1), set to zero
     


   
      
                         