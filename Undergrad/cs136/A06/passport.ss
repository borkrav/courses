#lang scheme

(require "ilist_destructive.ss")

(define line (iempty))

(define (passport-office)
   (define cmd (read))
   (define name null)
   (cond [(eof-object? cmd) (printf "")] ;exits and returns nothing
   
         [(symbol=? 'enter cmd) 
         (set! name (read))
         (set! line (iappend_destroy line (icons_destroy name (iempty))))
         (printf "seat ~a" name)
         (newline)
         (passport-office)]
         
         [(symbol=? 'serve cmd)
         
         (cond [(iempty? line) 
                     (printf "serve ?")
                     (newline)]
         
               [else (printf "serve ~a" (ifirst line))
                     (newline)
                     (set! line (irest_destroy line))])
                     
                     
         (passport-office)]

         [else (passport-office)] 
   )
   
)

(passport-office)   



