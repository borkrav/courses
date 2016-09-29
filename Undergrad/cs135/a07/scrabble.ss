;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname scrabble) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
(define tiles (list '("A" 1)
                    '("B" 3)
                    '("C" 3)
                    '("D" 2)
                    '("E" 1)
                    '("F" 4)
                    '("G" 2)
                    '("H" 4)
                    '("I" 1)
                    '("J" 8)
                    '("K" 5)
                    '("L" 1)
                    '("M" 3)
                    '("N" 1)
                    '("O" 1)
                    '("P" 3)
                    '("Q" 10)
                    '("R" 1)
                    '("S" 1)
                    '("T" 1)
                    '("U" 1)
                    '("V" 4)
                    '("W" 4)
                    '("X" 8)
                    '("Y" 4)
                    '("Z" 10)))


;scrabble-score: string (listof symbols) -> nat
;a function that takes in a string and a list containing symbols for the board layout, and returns a calculated scrabble score
;examples
(check-expect (scrabble-score "PaNCAKE" '(DL P P P DW P P)) 84)

(define (scrabble-score word board)
  (cond [(empty? word) 0] 
        [else (bingo-calculator (multiplier-calculator (base-score-calculator (explode word) board) board) (explode word))]))

(check-expect (scrabble-score "ZZZZZZZ" '(TW TL TW TL TW TL TW)) 10580)
(check-expect (scrabble-score "NOMNOMNOM" '(TW P P P P P P P TW)) 185)
(check-expect (scrabble-score "a" '(P)) 0)
(check-expect (scrabble-score "" '(empty)) 0)

;base-score-calculation: (listof strings) (listof symbols) -> nat
;a function that takes in a the letters and the board layout symbols, and outputs the base score, only counting the letter values and the letter multipliers
;examples
(check-expect (base-score-calculator (list "P" "a" "N" "C" "A" "K" "E") '(DL P P P DW P P)) 17)

(define (base-score-calculator letters board)
  (cond [(empty? letters) 0]
        [(symbol=? (first board) 'DL) (+ (* 2 (get-value (first letters) tiles)) (base-score-calculator (rest letters) (rest board)))]
        [(symbol=? (first board) 'TL) (+ (* 3 (get-value (first letters) tiles)) (base-score-calculator (rest letters) (rest board)))]
        [else (+ (get-value (first letters) tiles) (base-score-calculator (rest letters) (rest board)))]
        )
  )

(check-expect (base-score-calculator (list "Z" "Z" "Z" "Z" "Z" "Z" "Z") '(TW TL TW TL TW TL TW)) 130)
(check-expect (base-score-calculator (list "N" "O" "M" "N" "O" "M" "N" "O" "M") '(TW P P P P P P P TW)) 15)
(check-expect (base-score-calculator (list "a") '(P)) 0)
(check-expect (scrabble-score (list) '(empty)) 0)

;multiplier-calculation: nat (listof symbols) -> nat
;a fuction that takes in a pre-calculated score and multiplies it using the double word / triple word tile values
;examples
(check-expect (multiplier-calculator 10 '(TW TL TW TL TW TL TW)) 810)

(define (multiplier-calculator score board)
  (cond [(empty? board) score]
        [(symbol=? (first board) 'DW) (* 2 (multiplier-calculator score (rest board)))]
        [(symbol=? (first board) 'TW) (* 3 (multiplier-calculator score (rest board)))]
        [else (multiplier-calculator score (rest board))]
        ))
(check-expect (multiplier-calculator 100 '(P)) 100)
(check-expect (multiplier-calculator 0 '()) 0)

;bingo-calculator: nat (listof strings) -> nat
;a fuction that takes in a pre-calculated score and the letters used, and adds 50 to the score if 7 letters have been used
;examples
(check-expect (bingo-calculator 30 (list "P" "a" "N" "C" "A" "K" "E")) 80)

(define (bingo-calculator score letters)
  (cond [(>= (length letters) 7) (+ 50 score)]
        [else score]))

(check-expect (bingo-calculator 1 (list "Z" "Z" "Z" "Z" "Z" "Z" "Z")) 51)
(check-expect (bingo-calculator 1 (list "N" "O" "M" "N" "O" "M" "N" "O" "M")) 51)
(check-expect (bingo-calculator 0 (list)) 0)

;get-value: string al -> nat
;a function that takes in the letter and the tiles assossiation list, and extracts the point value that's assissiated to that letter
;examples
(check-expect (get-value "P" tiles) 3)

(define (get-value letter tiles)
  (cond [(empty? tiles) 0]
        [(string=? letter (first (first tiles))) (second (first tiles))]
        [else (get-value letter (rest tiles))]
        )
  )

(check-expect (get-value "A" tiles) 1)
(check-expect (get-value "a" tiles) 0)
(check-expect (get-value "Z" tiles) 10)

