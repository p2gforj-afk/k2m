.data 0
.global TabSrc
	11 16 5 7 8 12 15 3 1 14 19 9 2 6 4 13
.global Seuil
	10
.global NbSupp
	0
.global NbInf
	0
.alias NbValeurs 16
.program 100
	li R1, TabSrc
	li R2, (Seuil)
	li R3, NbValeurs
	li R10, 0
	li R11, 0
.boucle1
	li R0, (R1)
	sub R4, R0, R2
	brp R4, Supp
	add R10, R10, 1
	br suite
.S
	add R11, R11, 1
	add R1, R1, 1
	sub R3, R3, 1
	brnz R3, boucle1
	si (NbSupp), R11
	si (NbInf), R10
	exit
.end