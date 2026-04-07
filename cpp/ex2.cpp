#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Book {
  std::string titre;
  std::string auteur;
  int isbn;
  int annee;
  bool is_available = true;
};

class Member {
private:
  std::string name;
};

class Library {
private:
  std::vector<Book> livres;
  std::vector<std::unique_ptr<Member>> membre;

public:
  void addLivre(const Book &livre) { livres.push_back(livre); }

  void display() {
    for (const auto &livre : livres) {
      std::cout << "Titre: " << livre.titre << std::endl;
      std::cout << "Auteur: " << livre.auteur << std::endl;
      std::cout << "ISBN: " << livre.isbn << std::endl;
      std::cout << "Année: " << livre.annee << std::endl;
      std::cout << "Disponible: " << (livre.is_available ? "Oui" : "Non")
                << std::endl;
      std::cout << std::endl;
    }
  }

  void recherche(const std::string &search) {
    auto it = std::find_if(
        livres.begin(), livres.end(),
        [&search](const Book &livre) { return livre.titre == search; });

    std::cout << "Livre trouvé:" << std::endl;
    std::cout << "Titre: " << (*it).titre << std::endl;
    std::cout << "Auteur: " << (*it).auteur << std::endl;
  }
};

int main() {
  Library librairie;

  Book livre1{"un beau livre", "toto", 123, 2075};
  Book livre2{"un autre beau livre", "tata", 321, 2005};
  Book livre3{"un beau livre", "titi", 999, 2175};

  librairie.addLivre(livre1);
  librairie.addLivre(livre2);
  librairie.addLivre(livre3);

  librairie.display();

  librairie.recherche("un beau livre");

  return 0;
}
