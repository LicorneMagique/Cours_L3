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
        bool was_active;
        int occurence_pas;
};

class Table
{
    public :
        // Constructeur ---- Destructeur
        Table(int(Key, int), int(Key, int, int, int, int(Key, int)), const int);
        ~Table();

        // Fonctions passées au constructeur
        int (*hash)(Key, int);
        int (*pas)(Key, int, int, int, int(Key, int)); // re_hashage

        // Fonctions de manipulation de la table
        void add(const Key, const Value);
        void remove(const Key);
        void show();
        int getEchec();
        int getOccurence();
        int getSize();
        int search(const Key);
        Node getNode(const Key);
        std::string getInfo();

    private :
        Node* tab;
        int size;
        int echec;
};

#endif
