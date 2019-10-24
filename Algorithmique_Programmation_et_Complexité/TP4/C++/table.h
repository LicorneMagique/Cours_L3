#ifndef _TABLE
#define _TABLE

typedef unsigned int Key;
typedef double Value;

class Node
{
    friend class Table;
    public:
        Node();
    private :
        Key key;
        Value value;
        bool active;
        int occurence_pas;
};

class Table
{
    public :
        // Constructeur ---- Destructeur
        Table(int(Key, int), int(Key, int, int, int), const int);
        ~Table();

        // Fonctions passées au constructeur
        int (*hash)(Key, int);
        int (*pas)(Key, int, int, int); // re_hashage

        // Fonctions de manipulation de la table
        void add(const Key, const Value);
        void remove(const Key);
        void show();
        int getOccurence();
        int search(const Key);
        Node getNode(const Key);

    private :
        Node* tab;
        int size;
};

#endif
