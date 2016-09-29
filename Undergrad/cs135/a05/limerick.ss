;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname limerick) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
; a line is either
; * (cons n empty) where n is a string
; * (cons n nelos) where nelos is a non-empty list of strings

;;my-line-fn: line -> any
;(define (my-line-fn line)
;  (cond [(empty? (rest (line)))...]
;        [else (first (line))...
;              ...(my-line-fn (rest line))...]))

;count-syllables line -> nat
;a function that takes in a line and produces the number of syllables it contains
;example
(check-expect (count-syllables (cons "a" empty)) 1)
(check-expect (count-syllables (cons "a" (cons "b" empty))) 2)

(define (count-syllables line)
  (cond [(empty? (rest line)) 1]
        [else (+ 1 (count-syllables (rest line)))]))

;tests
(check-expect (count-syllables (cons "aa" (cons "bb" (cons "cc" (cons "dd" (cons "ee" (cons "ff" (cons "gg" empty)))))))) 7)
(check-expect (count-syllables (cons "aa" empty)) 1)

  

