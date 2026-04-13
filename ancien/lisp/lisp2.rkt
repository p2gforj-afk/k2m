#lang racket
(require racket/stream)

; Pb 1

(define(somme h l)
  (f + h 0 l))
   
(define(append l1 l2)
  (f cons id l2 l1))

(define(map h l)
  (f cons h '() l))

(define(f op1 op2 neutre l)
  (if (null? l)
      neutre
      (op1 (op2 (car l))
           (f op1 op2 neutre (cdr l)))))

(define(id x) (x))

; Pb 2

(define (entiers-naturels n)
  (stream-cons n
               (entiers-naturels (+ n 1))))

(define (un-sur-n stream)
  (stream-map (lambda (x) (/ 1 (* x x)))
              stream))

(define suite-harmonique
  (un-sur-n(entiers-naturels 1)))

(define (somme-harmonique stream n)
  (if (= n 0)
      0
      (+ (stream-first stream)
         (somme-harmonique(stream-rest stream)(- n 1)))))

(define (harmonique n)
  (somme-harmonique suite-harmonique n))

; Pb 3

(define (atom? l)
  (not (list? l)))

;--------- FILTRAGE énoncé l selon gabarit f
(define (filtre f p)
  (cond
    ; filtre et phrase vide
    ((and(null? f)(null? p)) #t)

    ;filte vide et phrase non vide
    ((null? f) #f)

    ;cas *
    ((eq? (car f) '*)
     (etoile (cdr f) p))

    ;phrase vide et filtre non vide -mais sans *-
    ((null? p) #f)
    
    ;cas ?
    ((eq? (car f) '?)
     (filtre (cdr f) (cdr p)))
     
    ;cas () - plusieur mot
    ((list? (car f))
     (if (member(car p) (car f))
          (filtre (cdr f) (cdr p))
          #f))
     
    ;cas () - mot exact
    ((eq? (car f) (car p))
     (filtre (cdr f) (cdr p)))
     
    ;echec
    (else #f)))
    
(define (etoile f p)
  (cond
    ; * = 0 mot
    ((filtre f p) #t)
    ; plus de mot a consommer
    ((null? p) #f)
    ; on consomme un mot
    (else (etoile f (cdr p)))))
    
;--------- ECHANGES avec réponses types en fonction différents gabarits
(define (echanges n phrase)
  (begin
	(cond
          
;; émotions
((filtre '(je * triste *) phrase)
 (display "Pourquoi êtes-vous triste ?"))

((filtre '(je * heureux *) phrase)
 (display "Qu'est-ce qui vous rend heureux ?"))

((filtre '(je * fatigué *) phrase)
 (display "Dormez-vous suffisamment ?"))

((filtre '(je * stressé *) phrase)
 (display "Qu'est-ce qui vous stresse ?"))

((filtre '(je * déprimé *) phrase)
 (display "Depuis combien de temps ?"))

((filtre '(je * anxieux *) phrase)
 (display "Qu'est-ce qui vous rend anxieux ?"))

((filtre '(je * peur *) phrase)
 (display "Les peurs peuvent être difficiles à expliquer."))

((filtre '(je * colère *) phrase)
 (display "Qu'est-ce qui provoque cette colère ?"))

((filtre '(je * seul *) phrase)
 (display "La solitude peut être pesante."))

((filtre '(je * perdu *) phrase)
 (display "Dans quel sens vous sentez-vous perdu ?"))

;; famille
((filtre '(* mère *) phrase)
 (display "Parlez-moi de votre mère."))

((filtre '(* père *) phrase)
 (display "Quelle relation avez-vous avec votre père ?"))

((filtre '(* famille *) phrase)
 (display "Votre famille est-elle importante pour vous ?"))

((filtre '(* enfance *) phrase)
 (display "Comment était votre enfance ?"))

((filtre '(* frère *) phrase)
 (display "Vous entendez-vous bien avec votre frère ?"))

((filtre '(* soeur *) phrase)
 (display "Vous êtes proche de votre sœur ?"))

;; relations
((filtre '(* ami *) phrase)
 (display "Les amis sont précieux."))

((filtre '(* relation *) phrase)
 (display "Les relations humaines sont complexes."))

((filtre '(* amour *) phrase)
 (display "Que signifie l'amour pour vous ?"))

((filtre '(* couple *) phrase)
 (display "Les relations de couple demandent de la communication."))

;; travail
((filtre '(je * travail *) phrase)
 (display "Votre travail vous plaît-il ?"))

((filtre '(je * travailler *) phrase)
 (display "Pourquoi travaillez-vous dans ce domaine ?"))

((filtre '(* patron *) phrase)
 (display "Votre patron vous met-il la pression ?"))

((filtre '(* collègue *) phrase)
 (display "Vos collègues sont-ils sympathiques ?"))

;; études
((filtre '(je * étudie *) phrase)
 (display "Qu'étudiez-vous ?"))

((filtre '(* université *) phrase)
 (display "Comment se passe l'université ?"))

((filtre '(* école *) phrase)
 (display "Aimez-vous apprendre ?"))

((filtre '(* professeur *) phrase)
 (display "Que pensez-vous de vos professeurs ?"))

;; informatique
((filtre '(* programmation *) phrase)
 (display "Quel langage utilisez-vous ?"))

((filtre '(* racket *) phrase)
 (display "Racket est inspiré de Scheme."))

((filtre '(* scheme *) phrase)
 (display "Scheme est très élégant."))

((filtre '(* bug *) phrase)
 (display "Les bugs font partie du développement."))

((filtre '(* ordinateur *) phrase)
 (display "Utilisez-vous souvent votre ordinateur ?"))

((filtre '(* intelligence artificielle *) phrase)
 (display "Les IA vous fascinent-elles ?"))

;; loisirs
((filtre '(* musique *) phrase)
 (display "Quel genre de musique aimez-vous ?"))

((filtre '(* film *) phrase)
 (display "Quel est votre film préféré ?"))

((filtre '(* série *) phrase)
 (display "Quelle série regardez-vous ?"))

((filtre '(* livre *) phrase)
 (display "Quel livre vous a marqué ?"))

((filtre '(* jeu *) phrase)
 (display "Jouez-vous souvent ?"))

((filtre '(* sport *) phrase)
 (display "Quel sport pratiquez-vous ?"))

;; nourriture
((filtre '(* manger *) phrase)
 (display "Quel est votre plat préféré ?"))

((filtre '(* cuisine *) phrase)
 (display "Aimez-vous cuisiner ?"))

((filtre '(* restaurant *) phrase)
 (display "Quel restaurant aimez-vous ?"))

;; voyage
((filtre '(* voyage *) phrase)
 (display "Aimez-vous voyager ?"))

((filtre '(* vacances *) phrase)
 (display "Où partez-vous en vacances ?"))

((filtre '(* pays *) phrase)
 (display "Quel pays aimeriez-vous visiter ?"))

;; philosophie
((filtre '(* vie *) phrase)
 (display "La vie est pleine de surprises."))

((filtre '(* mort *) phrase)
 (display "La mort est un sujet profond."))

((filtre '(* sens *) phrase)
 (display "Cherchez-vous un sens à tout cela ?"))

((filtre '(* bonheur *) phrase)
 (display "Qu'est-ce que le bonheur pour vous ?"))

((filtre '(* rêve *) phrase)
 (display "Rêvez-vous souvent ?"))

;; logique conversationnelle
((filtre '(oui *) phrase)
 (display "Vous semblez sûr de vous."))

((filtre '(non *) phrase)
 (display "Pourquoi dites-vous non ?"))

((filtre '(peut-être *) phrase)
 (display "Vous semblez hésiter."))

((filtre '(je pense *) phrase)
 (display "Pourquoi pensez-vous cela ?"))

((filtre '(je crois *) phrase)
 (display "Qu'est-ce qui vous fait croire cela ?"))

((filtre '(je veux *) phrase)
 (display "Pourquoi voulez-vous cela ?"))

((filtre '(je ne sais pas *) phrase)
 (display "Prenez votre temps pour réfléchir."))

((filtre '(?) phrase)
 (display "Soyez plus explicite."))

(else
 (display "Je ne vous comprends pas très bien."))
)
	(newline)
	(if (> n 1)
		(echanges (- n 1) (read))
                ( void )
        )
    )
 )
;--------- CONSULTATION qui encapsule ECHANGES 
(define (Freud n)
	(begin (display "Allongez-vous et causons.") (newline)
               (echanges n (read))
               (display "Bon, à la prochaine fois, c'est ")
               (display  (* n 10))
               (display  " €") 
               (newline)
	))
                                                   
