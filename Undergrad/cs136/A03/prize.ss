#lang scheme


;; (collect-prize cardlist) consumes a list of n cards, each created by (drawcard n),
;;                  where each card has a distinct secret number.  Produces 'prize
;;                  if cardlist is correct.  For any other input, regardless of
;;                  what it is, produces 'fraud.  That is, if cardlist is not a list,
;;                  or does not contain n elements, or the elements are not produced
;;                  by (drawcard n), or the secret numbers are not distinct.

;(secret n)

(require "scratchandwin.ss")
(provide collect-prize)

;testing stuff
;(define a (drawcard 3))
;(define b (drawcard 3))
;(define c (drawcard 3))
;(define d (drawcard 3))
;(define e (drawcard 3))
;(define f (drawcard 3))
;(scratch a)
;(scratch b)
;(scratch c)
;(scratch d)
;(scratch e)
;(scratch f)



(define (collect-prize cardlist)
  
  (define cards 
    (cond [(list? cardlist) (scratch-all-cards cardlist)]
          [else 'fraud]))
  
  
  (cond [(empty? cards) 'prize]
        [(and (list? cards) (not (check-for-fraud cards))) 
         
         
         (cond [(and (= (length cards) (second (first cards)))
                     (check-secret-list (sort (first (separate-list cards empty empty)) <))
                     (check-n-list (second (separate-list cards empty empty)) (length cards))
                     )
                'prize]
               [else 'fraud])]
            
        [else 'fraud])
    
  )
  
  
  (define (scratch-all-cards cardlist)
    (cond [(empty? cardlist) empty]
          [else (cons (scratch (first cardlist)) (scratch-all-cards (rest cardlist)))]
          ))
  
  (define (check-for-fraud cards)
    (cond [(empty? cards) false]
          [(not (list? (first cards))) true]
          [else (check-for-fraud (rest cards))]))
  
  ;separates the cardlist into two lists, the n-list and the prize list
  (define (separate-list list list1 list2)
    (cond [(empty? list) (cons list1 (cons list2 empty))]
          [else (separate-list (rest list) (cons (first (first list)) list1) (cons (second (first list)) list2))]))
  
  ;checks if all values in the n list equal to the n value
  (define (check-n-list n-list should-be)
    (cond [(empty? n-list) true]
          [(= (first n-list) should-be) (check-n-list (rest n-list) should-be)]
          [else false]))
  
  ;checks if all values in the sorted secret list are distinct
  (define (check-secret-list s-list)
    (cond [(empty? list) true]
          [(empty? (rest s-list)) true]
          [(< (first s-list) (second s-list)) (check-secret-list (rest s-list))]
          [else false]))
  
  
  