;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname extract) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;extract: (listof any) (listof nat) -> (listof any)
;a function that takes in a content list and a list of indecies, and returns the an extracted content list, only leaving the items at the indicies. 
;examples:
(check-expect (extract '(a b c d e f g h) '(0 2 4 6)) '(a c e g))

(define (extract c-list i-list)
  (extractor c-list i-list 0))


(define (extractor c-list i-list index)
  (cond [(or (empty? c-list) (empty? i-list)) empty]
        [(= (first i-list) index) (cons (first c-list) (extractor (rest c-list) (rest i-list) (add1 index)))]
        [else (extractor (rest c-list) i-list (add1 index))]
        )
  )

;tests        
(check-expect (extract (list) '(0 2 4 6)) (list))
(check-expect (extract '(a a a a ) (list)) (list))
(check-expect (extract '(q w e r t y u i o p) '(0 1 2 3 4 5 6 7 8 9)) '(q w e r t y u i o p))