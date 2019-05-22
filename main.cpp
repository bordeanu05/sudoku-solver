#include <bits/stdc++.h>
using namespace std;

ifstream f("date.in");
ofstream g("date.out");

// !Incep indexarea de la 0!


int mat[9][9];

/*
    Matricea arata astfel:

     0  1  2  3  4  5  6  7  8

  0  00 01 02 03 04 05 06 07 08
  1  10 11 12 13 14 15 16 17 18
  2  20 21 22 23 24 25 26 27 28
  3  30 31 32 33 34 35 36 37 38
  4  40 41 42 43 44 45 46 47 48
  5  50 51 52 53 54 55 56 57 58
  6  60 61 62 63 64 65 66 57 68
  7  70 71 72 73 74 75 76 77 78
  8  80 81 82 83 84 85 86 87 88

        Putem observa ca daca impartim matricea in 9 patrate de dimensiuni 3x3,
    coltul din stanga sus la fiecare patrat poate sa fie:
    -00, 03, 06
    -30, 33, 36
    -60, 63, 66
        Se vede ca *virgula* colturile au i-ul sau j-ul 0, 3 sau 6, asa ca am creat un
    vector in care tin aceste valori si pe care il parcurg ca sa aflu in care patrat ma aflu

        Parcurgand vectorul iau valorile mai mici decat indexii primiti
    exemplu: i = 1 si j = 3
    -avand i-ul egal cu 1 noi o sa luam 0, acesta fiind mai mic decat 1
    -acelasi lucru il facem si cu j, acesta fiind egal cu 3, noi vom lua tot valoarea 0,
    aceasta fiind strict mai mica
*/
int colturi3X3[3] = { 0, 3, 6 };

// Citesc matricea
void Citire()
{
    for(int i = 0; i<9; ++i)
        for(int j = 0; j<9; ++j)
            f >> mat[i][j];
}

// Afisez matricea rezolvata
void Afisare()
{
    for(int i = 0; i<9; ++i){
        for(int j = 0; j<9; ++j)
            g << mat[i][j] << ' ';
        g << '\n';
    }
}

// Verificam daca mai gasim un numar identic cu x pe aceeasi coloana
bool SeAflaPeColoana(int x, int ii, int j)
{
    for(int i = 0; i<9; ++i)
        if(mat[i][j] == x && i!=ii) return true;
    return false;
}

// Verificam daca mai gasim un numar identic cu x
bool SeAflaPeRand(int x, int i, int jj)
{
    for(int j = 0; j<9; ++j)
        if(mat[i][j] == x && j!=jj) return true;
    return false;
}

//  Folosesc asta ca sa parcurg vectorul care contine colturile de la patrate
int CelMaiStanga(int x)
{
    for(int i = 2; i>=0; --i){
        if(colturi3X3[i]<=x) return i;
    }
}

// Verific daca mai exista ceva cu valoarea egala cu x in submatricea de 3x3
bool SeAflaIn3X3(int x, int ii, int jj)
{
    int coltI = colturi3X3[CelMaiStanga(ii)];
    int coltJ = colturi3X3[CelMaiStanga(jj)];

    // luam cate 3 randuri a 3 coloane sa vedem daca exista x
    for(int i = coltI; i<coltI+3; ++i)
        for(int j = coltJ; j<coltJ+3; ++j)
            if(mat[i][j] == x && (i!=ii || j!=jj)) return true;

    return false;
}

//  Combin functiile de verificare ca sa fie mai compact si
// sa fie mai usor de citit
bool SePoateFolosi(int x, int i, int j)
{
    if(!SeAflaPeColoana(x, i, j) &&
       !SeAflaPeRand(x, i, j) &&
       !SeAflaIn3X3(x, i, j)) return true;
    return false;
}

// Verificat daca matricea a fost deja rezolvata
bool VerificaRezolvat()
{
    for(int i = 0; i<9; ++i)
        for(int j = 0; j<9; ++j)
            if(mat[i][j]==0) return false;
    return true;
}

//   Incrementam i-ul si j-ul (acestea fiind referinte, vom modifica variabilele in sine)
// pana cand ajungem la urmatorul element egal cu 0
void GasesteZero(int &ii, int &jj)
{
    bool gasit = false;
    for(int i = 0; i<9 && !gasit; ++i)
        for(int j = 0; j<9 && !gasit; ++j)
            if(mat[i][j]==0){
                ii = i;
                jj = j;
                gasit = true;
            }
}

/*
        Algoritmul de rezolvare (Backtracking + Recursivitate)

    -Verificam daca matricea este deja rezolvata
    -Gasim i-ul si j-ul elementului cu valoarea 0
    -Parcurgem numerele de la 1 la 9
    -Verificam pentru fiecare numar daca se poate folosi
        -Daca nu se poate: -Trecem la urmatorul numar
        -Daca se poate: -Punem numarul in locul liber din matrice
                        -Reapelam functia: -va testa fiecare posibilitate
                                           (functia reapelata se va reapela pana cand vom gasi
                                            o solutie)
                                           -daca functia VerificaRezolvat() de la inceput
                                           devine true, inseamna ca am gasit o solutie

    Obs: In loc de recursivitate puteam folosi mai multe for-uri (mult prea multe),
        dar e mult mai usor folosind recursivitatea
*/
bool Rezolva()
{
    if(VerificaRezolvat())
        return true;
    int ii, jj;
    GasesteZero(ii, jj);

    for(int z = 1; z<=9; ++z){
        if(SePoateFolosi(z, ii, jj)){
            mat[ii][jj] = z;

            if(Rezolva())
                return true;

            mat[ii][jj] = 0;
        }
    }

    return false;
}

int main()
{
    Citire();
    Rezolva();
    Afisare();
}
