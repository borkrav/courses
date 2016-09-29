#lang scheme

(require "total-order.ss")
(require "ordered-set.ss")

(define e os-empty)
(define s (os-singleton (to-hide 1)))
(define t (os-singleton (to-hide 2)))
(define st (os-union s t))
(define stt (os-union st t))
(define stts (os-difference st s))
(display (to-unhide (os-min st)))
(display (to-unhide (os-max st)))
(display (to-unhide (os-after st to-max-ident)))
(display (to-unhide (os-after st (os-after st to-max-ident))))
(display (to-unhide (os-after st (os-after st (os-after st to-max-ident)))))
(display (to-unhide (os-op st)))
