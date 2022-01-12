;Written by Thien K. M. Bui
; Last modified 01/11/2022
; HW03 CS251 Winter 2022, bst assignment

; entry
; param bst  
; return the root node of provided bst 
(define entry 
    (lambda (bst)
        (cond 
            ;if not a list, return #f
            ((not (list? bst)) #f)
            ((not (= (length bst) 3)) #f)
            ;check the 2nd element
            ((not (list? (car (cdr bst)))) #f)
            ;check the 3rd element of a list 
            ((not (list? (car (cdr (cdr bst))))) #f)
            (else (car bst)))))

;left 
;param bst
; return left subtree of provided bst
(define left 
    (lambda (bst)
        (cond 
            ((not (list? bst)) #f)
            ((not (= (length bst) 3)) #f)
            ;check the 2nd element
            ((not (list? (car (cdr bst)))) #f)
            ;check the 3rd element of a list 
            ((not (list? (car (cdr (cdr bst))))) #f)
            (else (car (cdr bst))))))

;right
;param bst
;return the right subtree of provided bst
(define right 
    (lambda (bst)
        (cond 
            ((not (list? bst)) #f)
            ((not (= (length bst) 3)) #f)
            ;check the 2nd element
            ((not (list? (car (cdr bst)))) #f)
            ;check the 3rd element of a list 
            ((not (list? (car (cdr (cdr bst))))) #f)
            (else (car (cdr (cdr bst)))))))

;make-bst 
; param: root node, left-bst, right-bst
; return new tree whose node is elt, left subtree is left-bst, right subtree is right-bst
(define make-bst
    (lambda (elt left-bst right-bst) 
        (cond 
            ;if elt is bad
            ( (not (integer? elt)) #f)
            ;if left-bst is bad (not of length 3 and 0 or not a list)
            ( (or (not (list? left-bst)) (and (not (= (length left-bst) 0)) (not (= (length left-bst) 3))) (not (list? left-bst))) #f)
            ;if right-bst is bad
            ( (or (not (list? right-bst)) (and (not (= (length right-bst) 0)) (not (= (length right-bst) 3))) (not (list? right-bst))) #f)   
            (else  (list elt left-bst right-bst)))))

;pre-order
; param: bst
; return all nodes within bst in pre-order 
(define preorder
    (lambda (bst)
        ;return bst
        ;make list of pre-order(left-subtree)
        ;make list of pre-order(right-subtree)

        ;use cons
        (if (null? bst)
            '()
            (append (entry bst) (preorder (left bst)) (preorder (right bst))))))

            
; (preorder '(1 (2 () ()) (3 () ())))