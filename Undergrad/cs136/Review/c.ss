#lang scheme

(define (main count)
   (define cmd (read))
   (cond 
      [(eof-object? cmd) (printf "")]
      [(symbol=? cmd 'echo) (display (read))(newline) (main count)]
      [(symbol=? cmd 'count) (display count) (newline) (main (+ 1 count))]
      [else (main count)]
   ))
   

   
   
;;(main 1)

(< 1 -inf.0)
