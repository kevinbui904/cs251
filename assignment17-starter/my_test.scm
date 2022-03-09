(define append-list
  (lambda (lst1 lst2)
    (if (null? lst1)
        lst2
        (cons (car lst1) (append-list (cdr lst1) lst2)))))

(define reverse-list
  (lambda (lst)
    (if (null? lst)
        lst
        (append-list (reverse-list (cdr lst)) (cons (quote (3 4)) (quote ()))))))


(define test
  (lambda (lst)
    (if (null? lst)
      lst
      lst
      )))

(define x ())
(quote 9)
; (append-list (reverse-list (cdr (quote (1)))) (cons (car (quote (1))) (quote ())))

; (test (quote (2 3 4 5)))

; (append-list (quote ()) (quote (1)))
(reverse-list (quote (9)))
; (reverse-list (quote (("computer" "science") "is" "awesome"))))

