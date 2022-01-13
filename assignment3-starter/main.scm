;Written by Thien K. M. Bui and Victor Huang
; Last modified 01/12/2022
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
            ( (or (not (list? left-bst)) (and (not (= (length left-bst) 0)) (not (= (length left-bst) 3)))) #f)
            ;if right-bst is bad
            ( (or (not (list? right-bst)) (and (not (= (length right-bst) 0)) (not (= (length right-bst) 3)))) #f)
            ;check if left and right are valid bst, (if left-bst or right-bst is of length 3 but not a valid bst)
            ((and (list? left-bst) (= (length left-bst) 3) (not (valid-bst left-bst))) #f ) 
            ((and (list? right-bst) (= (length right-bst) 3) (not (valid-bst right-bst))) #f ) 
            (else  (list elt left-bst right-bst)))))

;valid-bst (not extra assignment)
;param: bst 
;return #t if bst are of valid structure (NOTE: does not check if nodes are in right order) 
(define valid-bst
    (lambda (bst) 
         (cond 
            ;if root is bad
            ( (not (integer? (entry bst))) #f)
            ;if left-bst is bad (not of length 3 and 0 or not a list)
            ( (or (not (list? (left bst))) (and (not (= (length (left bst)) 0)) (not (= (length (left bst)) 3))) ) #f)
            ;if right-bst is bad
            ( (or (not (list? (right bst))) (and (not (= (length (right bst)) 0)) (not (= (length (right bst)) 3))) ) #f)
            
            ;if left and right nodes are both final
            ( (and (and (list? (left bst)) (= (length (left bst)) 0)) (and (list? (right bst)) (= (length (right bst)) 0)) #t))
            ;if right node is final node 
            ( (and (list? (right bst)) (= (length (right bst)) 0))  (and #t (valid-bst (left bst))))
            ;if left node is final node
            ( (and (list? (left bst)) (= (length (left bst)) 0)) (and #t (valid-bst (right bst))))

            (else #t))))
         

;;Predorder Function (Advanced)
(define preorder
    (lambda (bst)
    (if (null? bst) ;;Check if bst is empty list. If true, return empty list, if not, recursivery run through bst via preorder
    '()
    (append (list (entry bst)) (preorder (left bst)) (preorder (right bst))))))


;;Inorder Function (Advanced)
(define inorder
    (lambda (bst)
    (if (null? bst) ;;Check if bst is empty list. If true, return empty list, if not, recursivery run through bst via inorder
    '()
    (append (inorder (left bst)) (list (entry bst)) (inorder (right bst))))))

;;Postorder Function (Advanced)
(define postorder
    (lambda (bst)
    (if (null? bst) ;;Check if bst is empty list. If true, return empty list, if not, recursivery run through bst via postorder
    '()
    (append (postorder (left bst)) (postorder (right bst)) (list (entry bst))))))

;;Insert Function (Basic)
;;param: integer v and a bst to insert into
;;return a new bst with integer v at the right place
(define insert
    (lambda (v bst)
    ;bst is an empty node
    (cond 
        ;bst is currently empty
        ((not (entry bst)) (list v '() '()))
        ((= v (entry bst)) bst)
        ((< v (entry bst)) (make-bst (entry bst) (insert v (left bst)) (right bst)))
        (else (make-bst (entry bst) (left bst) (insert v (right bst)))))))


