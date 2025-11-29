/*
Prefiksno drvo: Autocorrect [1.5 poen]
    Tekst zadatka
        Dat je niz stringova words, duzine n koji predstavlja recnik poznatih reci. Koris-
        nik sa standardnog ulaza unosi m reci iz recnika i povremeno moze pogresiti. Za
        svaku unetu rec koja ne pripada recniku, a u kojoj je korisnik pogresio na tacno
        jednom mestu, ispisati spisak svih mogu´cih reci iz recnika na koje je korisnik
        potencijalno mislio. Smatrati da korisnik uvek unosi rec sa jednakim brojem
        karaktera kao ispravna rec, tj. da samo moze pogresiti pri kucanju karaktera.
        Korisnik moze uneti proizvoljnu rec - potrebno je detektovati iskljucivo reci koje
        sadrze jedan pogresan karakter. U ostalim slucajevima ispisati prazan red.
        Opis ulaza i izlaza
        Ulaz: Na standardni ulaz unosi se broj n, a potom n stringova koji predstavl-
        jaju niz words. Nakon toga, unosi se broj m, a potom m reci.
        Izlaz: Na standardni izlaz za svaku od unetih m reci potrebno je ispisati sve
        reci (odvojene razmakom) u skladu sa uslovima zadatka.
    Primer
        Ulaz:
            6
            mikro
            makro
            mleko
            red
            sed
            sistem
            4
            mekro
            sleko
            red
            ped
        Izlaz:
            makro mikro
            mleko
            sed red
*/