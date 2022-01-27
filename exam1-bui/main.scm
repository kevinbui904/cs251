;;Written by Thien K. M. Bui
;;Programming Languages exam1 
;;Carleton College Winter '22
;;Last editted 01/27/2022


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

;index
;param: lst and val
;return: true if the value is found in the top level of the list, false otherwise
(define index 
    (lambda (lst val)
        (index-helper lst val 0)
        ))
        

;index-helper
;param: list lst, value val, integer counter
;return: + 1 to counter everytime the function is called
(define index-helper
    (lambda (lst val index)
        (if (null? lst) 
            #f 
            (if (equal? (car lst) val)
                index
                (index-helper (cdr lst) val (+ 1 index))
            ))))

;indices
;param: list lst, value val
;return: list of all indices in which the value occur 
(define indices 
    (lambda (lst val)
        (indices-helper lst val '() 0)
        ))

;indices-helper
;param: list lst, value val, indices list
;return: list of all indices in which the value occur 
(define indices-helper 
    (lambda (lst val indices_lst index)
        (if (null? lst)
            indices_lst
            (if (equal? (car lst) val)
                (indices-helper (cdr lst) val (append indices_lst (list index)) (+ 1 index))
                (indices-helper (cdr lst) val indices_lst (+ 1 index))
            ))))

;indices-lazy
;param: lazy-list lazy, value val
;return: lazy list containing all occurence(s) of the value val in input lazy
(define indices-lazy
    (lambda (lazy val)
        (indices-lazy-helper lazy val 0)))

;indices-lazy-helper
;param: lazy-list lazy, value val, integer index
;return: lazy list containing all occurence(s) of the value val in input lazy
(define indices-lazy-helper
    (lambda (lazy val index)
        (if (not lazy)
            #f
            (if (equal? (car lazy) val)
                (cons index (lambda () (indices-lazy-helper ((cdr lazy)) val (+ 1 index)))) 
                (indices-lazy-helper ((cdr lazy)) val (+ 1 index))
            ))))


;reverse-lazy-list
;param: lazy-list lazy
;return: a normal list with all elements in lazy in reverse order
(define reverse-lazy-list
    (lambda (lazy)
        (if (not lazy)
            '() 
            (if (not ((cdr lazy)))
                (list (car lazy))
                (append (reverse-lazy-list ((cdr lazy))) (list (car lazy)))
                ))))

;curry5-reverse-list
;param: curried function receiving 5 parameters
;return: list of all the parameters in reverse order
(define curry5-reverse-list
    (lambda (a)
        (lambda (b)
            (lambda (c)
                (lambda (d)
                    (lambda (e)
                        (list e d c b a)))))))

;sum-every-nth
;param: list lst, integer n
;return: sum of every nth element in the list 
(define sum-every-nth
    (lambda (lst n)
        (cond 
            ((equal? n 0) 0)
            ((> n (length lst)) 0)
            ((> n 0) (sum-every-nth-helper lst n n 0 ))
            ((> (* n -1) 0) (sum-every-nth-helper (reverse lst) (* n -1) (* n -1) 0))
            (else 0)
        
        )))

;sum-every-nth-helper
;param: list lst, integer n, integer sum
;return: sum of every nth element in list
;return 0 if: lst is empty, n is larger than length of lst, n is 0
(define sum-every-nth-helper 
    (lambda (lst n current_n currentSum)
        (if (null? lst)
            currentSum
            (if (or (equal? current_n 0) (equal? current_n 1))
                (sum-every-nth-helper (cdr lst) n n (+ currentSum (car lst)))
                (sum-every-nth-helper (cdr lst) n (- current_n 1) currentSum)
            ))))

;sum-every-nth-lazy
;param: lazy-list lazy, integer n
;return: sum of every nth element in the lazy list
;return 0 if: lazy is empty, n is 0, n is less than 0
(define sum-every-nth-lazy
    (lambda (lazy n)
        (cond 
            ((not lazy) 0)
            ((equal? n 0) 0)
            ((< n 0) #f)
            (else (sum-every-nth-lazy-helper lazy n n 0))
        )))

;sum-every-nth-lazy-helper
;param: lazy-list lazy, integer n
;return: sum of every nth element in the lazy list
;return 0 if: n is larger than the number of elements encountered in lazy
(define sum-every-nth-lazy-helper
    (lambda (lazy n current_n currentSum)
        (if (not lazy)
            currentSum
            (if (or (equal? current_n 1) (equal? current_n 0))
                (sum-every-nth-lazy-helper ((cdr lazy)) n n (+ currentSum (car lazy)))
                (sum-every-nth-lazy-helper ((cdr lazy)) n (- current_n 1) currentSum)
        ))))

;my-sum
;param: list lst
;return: sum of all elements in the list
(define my-sum-optimized
  (lambda (lst)
    (if (null? lst)
        0
        (my-sum-helper lst 0))))

;my-sum-helper
;param: list lst, currentSum
;return: sum of all elements in the list
(define my-sum-helper 
    (lambda (lst currentSum)
        (if (null? lst)
            currentSum
            (my-sum-helper (cdr lst) (+ (car lst) currentSum))
        )))