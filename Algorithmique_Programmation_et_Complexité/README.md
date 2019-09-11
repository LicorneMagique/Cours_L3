# Source

<https://perso.liris.cnrs.fr/raphaelle.chaine/index.html#teaching>

## Cours 1

### Notes

Langages C et C++, plutôt C++ : <https://openclassrooms.com/fr/courses/1894236-programmez-avec-le-langage-c>

*Introduction à l'algorithmique* très bon livre sur l'algorithmique mais il n'apporte rien pour la programmation

On va travailler sur la façon dont on implémente les types de données abstraites (collection, liste, file, pile, file de priorité, table, arbre, graphe...)

```c
/* Pointeurs */
int i = 5;
int * pi; // Adresse d'une variable int
pi = &i; // Affectation de l'adresse de i à pi
*pi = 10; // i = 10
*pi; // Déréférencement du pointeur
```

Revoir les fonctions C suivantes

- scanf
- printf
- fscanf
- fread
- fwrite
- feof
- fopen
- fclose

```c
/* Chaînes de caractères */
int tab[4];
char st1[20] = {'S', 'o', 'l', 'e', 'i', 'l', '\0'};
char st2[] = "Jojo";
char * p = "Titi";
```

Revoir l'écriture d'un makefile

Les variables qui sont dans un tas survivent à l'empilement d'environnements, mais il faut stocker leur adresse dans un pointeur dont la survie dépend de l'environnement

```c
/* Référence */

// Une référence c'est une deuxième façon d'appeler une variable
int a = 4;
int& b = a; // b est une autre façon de parler de 'a'

// Utilité 1
const int& c = a; // "c" permet d'accéder à "a" en lecture seule grâce au mot clé "const"

```

```c
/* Exemple d'utilisation */

// Utilité 2 : le swap
void swap(int& a, int& b) // ça évite de manipuler les pointeurs
{
    int c;
    c = a;
    a = b;
    b = c;
}

int aa = 4, bb = 5;
swap(aa, bb);

```
