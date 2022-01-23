;;Written by Thien K. M. Bui
;;Programming Languages exam1 
;;Carleton College Winter '22
;;Last editted 01/21/2022


;reverse-reverse
;param: list of lists lst
;return: flat list with all items and subitems in lst being reversed
(define reverse-reverse 
    (lambda (lst)
        (reverse-reverse-helper (reverse lst))))

;reverse-reverse-helper
;param: list of lists
;return: will reverse ALL sublists and turn them into 1 flat list 
(define reverse-reverse-helper
    (lambda (lst)
            (if (null? lst) 
            '()
            (append (reverse (car lst)) (reverse-reverse-helper (cdr lst))))))

;search
;param: list of lists lst, value val
;return: true if the value is found in the list of lists, otherwise false
(define search 
    (lambda (lst val)
        (if (and (not (null? lst)) (list? lst))
            (or (search (car lst) val) (search (cdr lst) val))
            (if (equal? lst val)
                #t 
                #f)
                )))

