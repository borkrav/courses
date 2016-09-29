#lang scheme

(provide get-keystroke clear-screen)

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
