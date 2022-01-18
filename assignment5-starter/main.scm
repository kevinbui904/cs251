; Written by Thien K. M. Bui
; Assignment 5, Carleton College CS251 Winter '22
; Last editted 1/17/21

;curry3
;param: 1 parameter, my_function 
;if called 3 times, the curried value would be returned (e.g. ((((curry 3 *) 2) 3) 4) --> 24
(define curry3
    (lambda (my_function)
        (lambda (args1)
            (lambda (args2)
                (lambda (args3)
                    (my_function args1 args2 args3))))))
        ; (lambda (args1)
        ;     (lambda (args2)
        ;         (lambda (args3)
        ;             (my_function args1 ))))))

;uncurry3 
;param: three-arguments curried function and 3 args
;return: uncurried version of says function
(define uncurry3 
    (lambda (my_curried_function)
        (lambda (args1 args2 args3)
            (((my_curried_function args1) args2) args3))))

;uncurry
;param: curried function of n param and n params
;return: uncurried version of the function and apply to remaining args
(define uncurry
    (lambda (curried_function)
        (lambda args
            (if (null? args)
                ;at the end, return the curried_function to be called
                curried_function
                ;uncurry (curried_function) pattern is used to "get out of the previous curry"
                ;apply is here to call the uncurry function, otherwise you'd need to call it yourself (remove apply and then call curry however many time to test)
                (apply (uncurry (curried_function (car args))) (cdr args))))))
                

;my-filter
;param: filter function and a list for the filter to apply to
;return: list containing filtered members
(define my-filter 
    (lambda (filter_function lst)
        (cond 
            ;if list is null, return ()
            ((null? lst) '())
            ((filter_function (car lst)) (append (list (car lst)) (my-filter filter_function (cdr lst))))
            (else (my-filter filter_function (cdr lst))))))


;union
;param: lst1 and lst2 
;return: list with all non-duplicate members of lst1 and lst2
(define union 
    (lambda (lst1 lst2)
        (append lst1 (my-filter (union-filter lst1) lst2))))

;union-filter
;param: filter (list) containing non-duplicated members and another list (second list is curried)
;return: filter function that return false if list2 contains a duplicate member from lst1
(define union-filter 
    (lambda (filter)
        (lambda (compare_to)
            (cond 
                ((null? filter) #t)
                ((equal? (car filter) compare_to) #f)
                (else ((union-filter (cdr filter)) compare_to))))))

;intersect
;param: lst1 and lst2
;return: list with only duplicate members of lst1 and lst2 
(define intersect 
    (lambda (lst1 lst2)
    ;run the filter twice to catch the no-duplicate case
        (my-filter (intersect-filter lst2) (my-filter (intersect-filter lst1) lst2))))

;intersect-filter
;param: filter(list) containing non-duplicated members and another list (second list is curried)
;return: filter function that return true if list2 contains a duplicate member from list1
(define intersect-filter 
    (lambda (filter)
        (lambda (compare_to)
            (cond 
                ((null? filter) #f)
                ((equal? (car filter) compare_to) #t)
                (else ((intersect-filter (cdr filter)) compare_to))))))