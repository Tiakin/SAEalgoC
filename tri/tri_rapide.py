def tri_rapide(tableau, debut, fin):
    """
    Trie tableau entre les indices 
    debut (inclus) et fin (exclu)
    """
    # Cas de base
    if fin - debut < 2:
        return

    pivot = tableau[fin - 1]
    curseur = debut

    # Partition du tableau
    
    for i in range(debut, fin - 1):
        if tableau[i] <= pivot:
            tableau[i], tableau[curseur] = tableau[curseur], tableau[i]
            curseur += 1

    # Positionnement définitif du pivot
    tableau[fin - 1], tableau[curseur] = tableau[curseur], tableau[fin - 1]

    # Appels récursifs
    tri_rapide(tableau, debut, curseur)
    tri_rapide(tableau, curseur + 1, fin)