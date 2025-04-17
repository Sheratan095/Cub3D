[x] use t_vars *vars instead of t_vars vars in main

[] Empty lines in map?

[x] multiple definition of the same asset -> load the last definition
	=> ora legge tutto il file fino a che non trovo tutti gli asset,
		da lì in poi è tutta mappa. andrebbe cambiata la fine del ciclo di lettura e andrebbe fatto finire quando inzia la mappa

[x] printf for error that already print Error\n and then \n

[X] ?? "NO ./path_to_the_north_texture.xpm " return an error beacuse ther's \n at the end that is
		considered as a new splitted part of the line, the if on asset loading fail

[x] SO ./assets/dasda.xpm just print "can't open
	file", it should print invalid declaration...

[x] universal printf with different fd

------------------------------------------------------------

STRICT=0: il programma fallisce solo quando non tutti gli asset sono
		dichiarati almeno una volta correttamente oppure la mappa è sbagliata
STRICT=1: il programma fallisce in tutti i casi precedenti e 
			in caso di almeno un'errata dicharazione oppure una linea sbagliata e così via