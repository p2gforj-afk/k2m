.data 	0
.global values 
	10 20 30  40 50 60 70 80 90 100 110 120 130 140 150 160 
.global racines
	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
.alias n 16
.program 100
	li R1, values
	li R2, racines
	li R3, n
	li R5, 2
.boucle1
	li R4, 1
	li R6, -1
	li R8, (R1)
.boucle2
	sub R8, R8, R4
	add R4, R4, R5
	add R6, R6, 1
	brp R8, boucle2
	si (R2), R6
	add R1, R1, 1
	add R2, R2, 1
	add R8, R8, 1
	sub R3, R3, 1
	brnz R3, boucle1
	exit
.end

