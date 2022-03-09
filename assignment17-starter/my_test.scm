(define append-list
  (lambda (lst1 lst2)
    (if (null? lst1)
        lst2
        (cons (car lst1) (append-list (cdr lst1) lst2)))))

(define reverse-list
  (lambda (lst)
    (if (null? lst)
        lst
        (append-list (reverse-list (cdr lst)) (cons (car lst) (quote ()))))))

(append-list (reverse-list (quote ())) (cons (car (quote (1))) (quote ())))



; (append-list (quote ()) (quote (1)))
; (reverse-list (quote (1)))
; (reverse-list (quote (("computer" "science") "is" "awesome"))))

