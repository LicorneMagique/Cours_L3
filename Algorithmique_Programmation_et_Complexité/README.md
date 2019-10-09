# Source

<https://perso.liris.cnrs.fr/raphaelle.chaine/index.html#teaching>

## Cours 1

### Notes cours 1

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

```c++
/* Référence */

// Une référence c'est une deuxième façon d'appeler une variable
int a = 4;
int& b = a; // b est une autre façon de parler de 'a'

// Utilité 1
const int& c = a; // "c" permet d'accéder à "a" en lecture seule grâce au mot clé "const"

```

```c++
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

## Cours 2

### Module

Le module contient deux fichiers :

- **module.h(pp)**  
    Ce fichier permet de dire ce que permet de faire le module, il contient :
  - Une **interface**
  - Des **déclarations**
  - Des "**promesses**" (spec)

- **module.c(pp)**  
    Ce fichier permet d'implémenter les fonctions et procédures du module. Il génère un fichier module.o

---

### Notes cours 2

#### Makefile

```makefile
# La ligne suivante est appelée lorsqu'on utilise la commande "make"
menu : menu.o # On veut créer le fichier "menu", pour ça on a besoin du fichier "menu.o"
    g++ menu.o -o menu -std=c++14 # Commande à utiliser pour créer le fichier menu

menu.o : menu.cpp # Pour créer le fichier "menu.o" on a besoin du fichier "menu.ccp"
    g++ -Wall -pedantic -c menu.cpp -std=c++14 # Commande à utiliser pour créer le fichier "menu.o"

# La ligne suivante est appelée lorsqu'on utilise la commande "make clean"
clean :
    rm menu.o menu
```

#### Surcharge d'opérateur

L'objectif est d'utiliser les conversions implicites du c++ pour effectuer des opérations sur de nouveaux types abstraits

```c++
// Fichier Point3D.hpp

#include <iostream>

class Point3D
{
    public:
        Point3D(double nb1, double nb2, double nb3);
        Point3D(double nb);
        Point3D& operator = (const Point3D& other);
        Point3D& operator + (const Point3D& other);
        Point3D& operator - (const Point3D& other);
        Point3D& operator * (const Point3D& other);
        friend std::ostream& operator << (std::ostream&, const Point3D& other);
        friend std::istream& operator >> (std::istream&, Point3D& other);

    private:
        double x, y, z;
};
```

```c++
// Fichier Point3D.cpp

#include "Point3D.h"
#include <iostream>

using namespace std;

Point3D::Point3D(double nb1, double nb2, double nb3)
{
    this->x = nb1;
    this->y = nb2;
    this->z = nb3;
}

Point3D::Point3D(double nb)
{
    this->x = nb;
    this->y = nb;
    this->z = nb;
}

Point3D& Point3D::operator = (const Point3D& other)
{
    if (this == &other)
        return *this;
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}

Point3D& Point3D::operator + (const Point3D& other)
{
    return *(new Point3D(this->x + other.x, this->y + other.y, this->z + other.z));
}

Point3D& Point3D::operator - (const Point3D& other)
{
    return *(new Point3D(this->x - other.x, this->y - other.y, this->z - other.z));
}

Point3D& Point3D::operator * (const Point3D& other)
{
    return *(new Point3D(this->x * other.x, this->y * other.y, this->z * other.z));
}

ostream& operator << (ostream& sortie, const Point3D& p)
{
    sortie << "(" << p.x << ", " << p.y << ", " << p.z << ")" ;
    return sortie ;
}
```

```c++
// Fichier main.cpp

#include "Point3D.h"
#include <iostream>

using namespace std;

int main()
{
    Point3D p1 = Point3D(-1, 2, 3);
    Point3D p2 = Point3D(2, -1.5, 4);

    cout << "Voici p1 : " << p1 << endl
         << "Voici p2 : " << p2 << endl
         << "Voici p1 + p2 : " << p1 + p2 << endl
         << "Voici p1 + 2 : " << p1 + 2 << endl
         << "Voici p1 - p2 : " << p1 - p2 << endl
         << "Voici p1 - 2 : " << p1 - 2 << endl
         << "Voici p1 * p2 : " << p1 * p2 << endl
         << "Voici p1 * 4 : " << p1 * 4 << endl;

    return EXIT_SUCCESS;
}
```

## Cours 4

### Notes cours 4

Le **tri par insertion** est très efficace pour des données presque triées

Le **tri par tas** est parfait pour des données très désordonnées
