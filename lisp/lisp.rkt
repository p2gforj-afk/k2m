#lang racket

; Exo 1
(define (dernier l)
  (if (null? (cdr l))
      (car l)
      (dernier (cdr l))
      )
  )

; Exo 2
(define (atom? x) (not (list? x)))

(define (aplatir x)(
  (cond ((null? x) '())
        ((atom? x) (cons x '())
      (#t (append (aplatir(car x))(aplatir(cdr x))))
      )
  )
  ))

; Exo 3
(define (max l)
  (if (null? (cdr l)) 
      (car l)
      (let ((m1 (car l))
            (m2 (max (cdr l))
           ))
           (if (> m1 m2)
               m1
               m2
               )
           )
  )
      )

(define (extrait l e)(if (= (car l) e)
                         (cdr l)
                      (cons(car l) (extrait (cdr l) e))
                      )
  )

(define (tri l)(if (null? l)
                   l
                   (let(m (max l))
                     (cons m(tri(extrait l m)))
                     )
                   )
  )

;Exo 4

(define (membre? e l) (cond
                        ((null? l) #f)
                        ((= (car l) e) #t)
                        (#t (membre? e (cdr l)))))

(define (ensemble? l) (cond
                        ((null? l) #t)
                        ((membre (car l)(cdr l)) #f)
                        (else (ensemble? (cdr l))
                              )))

(define (ensemble l) (cond
                       ((
