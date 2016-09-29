#lang scheme

;; full-simon.ss plays a simon game consisting of n rounds.
;;   The first round requires that the user press a sequence
;;   of length 1, the next round a sequence of length 2, and
;;   so on to the final round which requires that the user
;;   press a sequence of length n.   The sequence in each
;;   round is a prefix of the same random sequence of colors,
;;   each of which is one of ('red, 'blue, 'green, 'yellow)

;; the following functions are provided:
;;   (full-simon n)   Starts a new game with n rounds and produces
;;                    a list with one random color -- the sequence
;;                    that must be pressed in the first round

;;   (press c)   Consumes a color c (which must be one of 'red,
;;               'blue, 'green, 'yellow) and produces one of the
;;                following results:
;;
;;               'win -- the game is complete, and every round
;;                       has been played correctly
;;               'lose -- c is not the correct color
;;               'ok   -- c is the correct color, and the round is
;;                        not yet complete
;;                a list of colors -- c is the correct color, and
;;                        the round is complete, but the game
;;                        is not complete.  The list of colors
;;                        produced is the sequence that must 
;;                        be pressed in the next round.

;;   (score)  Produces the score for the most recently played game,
;;            as defined by the formula given in problem 1.  Note
;;            that for this game  maximum_presses is not equal to n

;;   (best-score) -- the highest score of any
;;            game played so far.  'undefined if no games have been played.

(provide full-simon press score best-score)

;; mutable variables that will keep track of score stuff
(define score-counter 'undefined)
(define best-score-counter 'undefined)
(define correct-presses 0)
(define maximum-presses 0)

;; helper function (random-color) produces a color
;;           from {red, blue, green, yellow}
(define (random-color)
  (define r (random 4))
  (cond
    [(= r 0) 'blue]
    [(= r 1) 'red]
    [(= r 2) 'yellow]
    [else 'green]))

;; Mutable variables that hold colour-related lists
(define round-colors empty)
(define colors empty)

;;mutable variables that hold round-related integers
(define current-round 0)
(define max-round 0)

;; (simple-simon n) provided by module; see interface
(define (full-simon n)
  (set! max-round n)
  (set! maximum-presses (* (+ 1 n) (/ n 2)))
  (build-list)
  )

;;build list - builds the color list for each round
(define (build-list)
  (set! current-round (add1 current-round))
  (cond [(empty? round-colors) (set! round-colors (cons (random-color) round-colors))]
        [else (set! round-colors (append round-colors (list (random-color))))])
  (set! colors round-colors)
  round-colors)


;; (press c) provided by module; see interface
(define (press c)
  (define shouldbe (first colors))
  (set! colors (rest colors))
  (cond
    [(equal? c shouldbe)
     (set! correct-presses (add1 correct-presses))
     (cond
       [(and (empty? colors) (= current-round max-round)) (reset-game) 'win]
       [(empty? colors) (build-list)]
       [else 'ok])]
    [else (reset-game) 'lose])
  )
;;resets game after player wins or looses - resets all the mutable variables to default values, and sets the score
(define (reset-game)
  (set-score) 
  (set! current-round 0)
  (set! max-round 0)
  (set! round-colors empty))     


;sets the score after the game has finished
(define (set-score)
  (set! score-counter (- (* 2 correct-presses) maximum-presses))
  (set! correct-presses 0)
  (set! maximum-presses 0)
  (set-best-score))


;sets best score after game has finished
(define (set-best-score)
  (cond [(and (<= 0 score-counter) (eq? best-score-counter 'undefined)) (set! best-score-counter score-counter)]
        [(and (number? best-score-counter) (< best-score-counter score-counter)) (set! best-score-counter score-counter)]
        [else best-score-counter]))

;functions that return score values
(define (score) score-counter)
(define (best-score) best-score-counter)

