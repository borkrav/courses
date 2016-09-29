#lang scheme

;; (drawcard n) produces a new "scratch and win" lottery card which contains a
;;            secret number between 1 and n.

;; (scratch card) consumes a card that was produced by (drawcard n) for some n.
;;                Produces (list secret n) where secret is the secret number and
;;                n is the value such that (drawcard n) produced card.
;;                Produces 'fraud if card was not produced by drawcard.

(provide drawcard scratch)

(define-struct card (secret n))

(define (drawcard n)
  (make-card (+ 1 (random n)) n))

(define (scratch card)
  (cond [(and (card? card)(<= (card-secret card) (card-n card))) (list (card-secret card) (card-n card))]
        [else 'fraud]))