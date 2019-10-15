#include <chrono>
#include <cstdlib>
#include <cstdio>

int main(int argc, char** argv)
{
    int i, nbiter;
    if (argc != 2)
    {
        std::printf("Usage : \n%s suivi d'un entier \n(nombre de passages dans une boucle d'incrémentation d'un int)\n", argv[0]);
        exit(1);
    }
    nbiter = std::atoi(argv[1]);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for (i = 1; i < nbiter; i++) std::printf("%d %d\n", i, i*i);
    end = std::chrono::system_clock::now();
    int elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::printf("Temps requis pour calculer %d carres : %d \n", nbiter, elapsed_microseconds);

    return 0;
}
