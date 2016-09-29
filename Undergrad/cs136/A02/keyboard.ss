#lang scheme

(provide get-keystroke clear-screen)

;; A module to do some system-dependent interaction stuff
;;
;; (get-keystroke) immediately produces the character 
;;                 representing the next key
;;                 does not use (and does not work in)
;;                 DrScheme interaction panel
;;                 Must be used in a Unix (Solaris) or
;;                 linux or MacOS Terminal window
;;                 Microsoft users are out of luck

;; (clear-screen) erases the text on the terminal
;;                produces (void)

;;
;; It is not necessary to know how this module is 
;;    implemented in order to use it, to do the assignment
;;    or to write the exam.

;; There is a danger that you will confuse yourself by
;; trying to figure it out.

;; With that warning, here it is:
;;













(require scheme/system)

(file-stream-buffer-mode (current-input-port) 'none)
(file-stream-buffer-mode (current-output-port) 'none)

(define inchar 0)

(define (get-keystroke)
  (define x (system "stty cbreak -echo"))
  (define inchar (read-char))
  (define y (system "stty sane"))
  inchar)

(define (clear-screen)
  (void (system "clear")))
