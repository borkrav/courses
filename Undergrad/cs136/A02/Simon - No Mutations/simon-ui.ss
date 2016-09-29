#lang scheme

(require "keyboard.ss")
(require "simon.ss")

(define (display-colors c)
  (cond
    [(null? c) (void)]
    [true
     (clear-screen)
     (display (first c))
     (sleep 1)
     (clear-screen)
     (sleep .25)
     (display-colors (rest c))]))

(define (player i n pfn)
  (define k (get-keystroke))
  (define col
    (cond
      [(equal? k #\b) 'blue]
      [(equal? k #\r) 'red]
      [(equal? k #\y) 'yellow]
      [(equal? k #\g) 'green]
      [true 'black]))
  (define r (pfn col))
  (printf "For move number ~a you pressed ~a: " i k)
  (cond
    [(procedure? r) (printf "ok\n") (player (add1 i) n r)]
    [else (printf "~a\n" r)]))

(define (simon-ui)
  (display "Enter size of game (0 to quit), then hit enter: ")
  (let ([n (read)])
    (read-line)
    (cond
      [(= n 0) 'bye]
      [true
       (let ([seq-pressfn (simple-simon n)])
         (display-colors (first seq-pressfn))
         (player 1 n (second seq-pressfn))
         (simon-ui))])))

(simon-ui)