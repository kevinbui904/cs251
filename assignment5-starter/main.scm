; Written by Thien K. M. Bui
; Assignment 5, Carleton College CS251 Winter '22
; Last editted 1/17/21

;curry3
;param: 1 parameter, my_function 
;if called 3 times, the curried value would be returned (e.g. ((((curry 3 *) 2) 3) 4) --> 24
(define curry3
    (lambda (my_function)
        (lambda (curried1)
            (lambda (curried2)
                (lambda (curried3)
                    (my_function curried1 (my_function curried2 curried3)))))))

;uncurry3 
;param: three-arguments function
;return: uncurried version of says function
(define uncurry3 
    (lambda (my_function)
        (lambda (uncurried)
            (my_function uncurried))))