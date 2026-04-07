#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

template <typename T>
class Statistiques
{
private:
    std::vector<T> donnees;

public:
    void ajouter(T valeur);
    void trie();
        T obtenirMax() const;
    double obtenirMoyenne() const;
};

template <typename T>
void Statistiques<T>::ajouter(T valeur)
{
    donnees.push_back(valeur);
}

template <typename T>
T Statistiques<T>::obtenirMax() const
{
    if (donnees.empty())
        return 0;
    return *std::max_element(donnees.begin(), donnees.end());
}

template <typename T>
double Statistiques<T>::obtenirMoyenne() const
{
    if (donnees.empty())
        return 0.0;
    T somme = std::accumulate(donnees.begin(), donnees.end(), T(0.0));
    return static_cast<double>(somme) / donnees.size();
}

template <typename T>
void Statistiques<T>::trie()
{
    std::sort(donnees.begin(), donnees.end());
}

int main()
{
    Statistiques<double> notes;
    notes.ajouter(12.5);
    notes.ajouter(18.0);
    notes.ajouter(7.5);
    notes.ajouter(14.0);
    notes.ajouter(11.0);
    notes.ajouter(19.5);
    notes.ajouter(5.0);
    notes.trie();
    std::cout << "notes max: " << notes.obtenirMax() << std::endl;
}