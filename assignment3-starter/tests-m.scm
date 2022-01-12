;; DO NOT CHANGE THESE TESTS.

;; Module to include testing code
(use-modules (srfi srfi-64))

;; Basic tests for entry, left, right
(test-equal 1
             (entry '(1 () ())))
(test-equal '(2 () ())
             (left '(1 (2 () ()) (3 () ()))))
(test-equal '(3 () ())
             (right '(1 (2 () ()) (3 () ()))))

;; Basic tests for make-bst
(test-equal '(3 () ())
             (make-bst 3 '() '()))

(test-equal '(3 (1 () (2 () ())) (6 (4 () ()) (18 () ())))
             (make-bst 3 '(1 () (2 () ())) '(6 (4 () ()) (18 () ()))))

;; Basci test for orderings
(test-equal '(1 2 3)
             (preorder '(1 (2 () ()) (3 () ()))))

(let ((test-tree '(8 (4 () (6 () (7 () ())))
                    (28 (22 () (23 () ())) ()))))
 (test-equal  '(8 4 6 7 28 22 23)
               (preorder test-tree))
 )

 (test-equal '(2 1 3)
   (inorder '(1 (2 () ()) (3 () ()))))

 (test-equal '(2 3 1)
   (postorder '(1 (2 () ()) (3 () ()))))

;; Basic tests for insert
(test-equal '(5 () ())
             (insert 5 '()) )
(test-equal  '(6 (5 () ()) ())
              (insert 5 '(6 () ())))
(test-equal  '(4 () (5 () ()))
              (insert 5 '(4 () ())))
(test-equal '(8 (4 () (6 () (7 () ()))) (28 (22 (10 () ()) (23 () ())) ()))
             (insert 10 '(8 (4 () (6 () (7 () ()))) (28 (22 () (23 () ())) ()))))

 ;; Advanced tests for orderings
(let ((test-tree '(8 (4 () (6 () (7 () ())))
                     (28 (22 () (23 () ())) ()))))
  (test-equal '(4 6 7 8 22 23 28)
    (inorder test-tree))
  (test-equal '(7 6 4 23 22 28 8)
    (postorder test-tree) )
  )

 ;; Advanced tests for entry, left, right (edge cases)
 (test-assert (not (entry '(a b c))))
 (test-assert (not (left '(a b c))))
 (test-assert (not (right '(a b c))))
 (test-assert (not (entry '())))
 (test-assert (not (left '())))
 (test-assert (not (right '())))

 ;; Advanced tests for make-bst (edge cases)
 (test-assert (not (make-bst 1 2 3)))
 (test-assert (not (make-bst 1.5 '() '())))
 (test-assert (not (make-bst 'a '() '())))
 (test-assert (not (make-bst 1 '(2) '())))
 (test-assert (not (make-bst 1 '() '(3))))
 (test-assert (not (make-bst 1 '(5 6 7) '(2 3 4))))

;; Advanced tests for orderings (edge cases)
 (test-equal '(1)
   (preorder '(1 () ())))
 (test-equal '(1)
   (inorder '(1 () ())))
 (test-equal '(1)
   (postorder '(1 () ())))
 (test-equal '()
   (preorder '()))
 (test-equal '()
   (inorder '()))
 (test-equal '()
   (postorder '()))
