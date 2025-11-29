/*
Union-find: Relacije [1.5 poen]
    Tekst zadatka
        Dat je niz stringova eq koji predstavlja niz relacija izmedju promenljivih (mala
        slova abecede, u opsegu ’a’-’z’) u obliku x==y ili x!=y. Potrebno je utvrditi
        da li je mogu´ce dodeliti cele brojeve svim promenljivim tako da su sve zadate
        relacije ispunjene. Vrati true ako je to mogu´ce, inace false.
    Opis ulaza i izlaza
        Ulaz: Na standardni ulaz unosi se broj n, a potom n stringova koji predstavl-
              jaju niz eq.
        Izlaz: Na standardni izlaz ispisati true ili false u skladu sa uslovima zadatka.
    Primer 1
        Ulaz:
            2
            a==b
            b!=a
        Izlaz:
            false
    Primer 2
        Ulaz:
            5
            a==b
            c==d
            b!=c
            d==e
            a!=e
        Izlaz:
            true
*/