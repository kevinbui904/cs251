; Written by Thien K. M Bui 
; Last updated 01/09/2022
; HW02 CS251 Winter 2022

; sum 
; param: list of integers 
; return: sum of all integers in list 

(define sum 
    (lambda (currentList)
        (if (equal? (length currentList) 0)
            0 
            (+ (car currentList) (sum (cdr currentList))))))

; keep-first-n 
; param: list of items, integer n 
; return: items in list up to n provided index, 
;     if n is 0, bigger than length of list, or negative, return empty list 

(define keep-first-n 
    (lambda (index currentList)
        (cond 
            ((<= index 0) '())
            ((> index (length currentList)) '())
            (else (cons (car currentList) (keep-first-n (- index 1) (cdr currentList)))))))








