#include "header/donnee.h"
#include "header/comm.h"

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Création d'objets de communication et de données
    comm c;
    donnee d;

    // Variables pour stocker les noms de fichiers et leur contenu
    std::string monFichier;
    std::vector<char> contenuFichier;

    // Extensions des fichiers à envoyer
    const char *extensionJson = "jsn";
    const char *extensionJpg = "jpg";
    const char *extensionCpp = "cpp";

    // Configuration des données pour les images et animations
    d.setData(1, 200, 300, 1080, 1920, 1, 1, 1, 16/9, "1", "1", "1");
    d.setData(2, 200, 300, 1080, 1920, 2, 2, 2, 2, "2", "2", "2", "2", "2");

    // Initialisation de la communication et connexion au serveur
    c.init();
    c.connectToServer();

    // Écriture des données dans un fichier JSON
    d.writeData(1);
    monFichier = "../cmake-build-debug/output.json";

    // Récupération du contenu du fichier JSON
    contenuFichier = d.getData(monFichier);

    // Envoi de la taille du fichier, de l'extension et du contenu du fichier au serveur
    c.sendSize(contenuFichier);
    c.sendExtension(const_cast<char *>(extensionJpg));
    c.sendMessage(contenuFichier);

    // Fermeture de la connexion
    c.closeConnection();

    return 0;
}
