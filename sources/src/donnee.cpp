#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "../header/donnee.h"
#include "../header/json.hpp"

nlohmann::json j;

// Fonction pour lire les données d'un fichier et les stocker dans un std::vector<char>
vector<char> donnee::getData(const std::string &nomFichier) {
    std::string fileName = nomFichier;

    // Ouvrir le fichier en mode binaire
    std::ifstream fichier(fileName, std::ios::binary);

    // Vérifier si le fichier est ouvert correctement
    if (!fichier.is_open()) {
        std::cout << "Erreur lors de l'ouverture du fichier : " << fileName << std::endl;
        return std::vector<char>(); // Retourner un vecteur vide en cas d'erreur
    }

    // Lire le contenu du fichier dans un std::vector<char>
    std::vector<char> contenuFichier((std::istreambuf_iterator<char>(fichier)), std::istreambuf_iterator<char>());

    // Fermer le fichier
    fichier.close();

    return contenuFichier;
}

// Fonction pour définir les données à l'aide de paramètres spécifiés
void donnee::setData(int numberScreen_, int posX_, int posY_, int heightImage_, int WidthImage_, int numberPixel_, int heightWall_, int widthWall_, string rotationSpeed_,
                     string rotationDirection_, string rotationAxis_, string translationSpeed_,
                     string translationDirection_) {
    // Affectation des valeurs aux membres de la structure Image
    Image.numberPixel = numberPixel_;
    Image.posX = posX_;
    Image.posY = posY_;
    Image.heightImage = heightImage_;
    Image.widthImage = WidthImage_;

    // Affectation des valeurs aux membres de la classe
    widthWall = widthWall_;
    heightWall = heightWall_;


    // Affectation des valeurs aux membres de la structure animation
    animation.rotationSpeed = rotationSpeed_;
    animation.rotationDirection = rotationDirection_;
    animation.rotationAxis = rotationAxis_;
    animation.translationSpeed = translationSpeed_;
    animation.translationDirection = translationDirection_;

    // Construction du nom de la variable pour  obtenir : "image n" avec n pour numero d'ecran
    std::string nom = "image";
    std::string numeroecr = std::to_string(numberScreen_);
    nomVariable = nom.append(numeroecr);

    // Ajout des valeurs aux vecteurs paramImage et paramAnimation
    paramImage.push_back(Image.numberPixel );
    paramImage.push_back(Image.heightImage );
    paramImage.push_back(Image.widthImage );
    paramImage.push_back(Image.posX );
    paramImage.push_back(Image.posY );

    paramAnimation.push_back(animation.rotationSpeed );
    paramAnimation.push_back(animation.rotationDirection );
    paramAnimation.push_back(animation.rotationAxis );
    paramAnimation.push_back(animation.translationSpeed );
    paramAnimation.push_back(animation.translationDirection );


    // Affichage des valeurs des vecteurs paramImage et paramAnimation
    try {
        std::cout << "paramImage: ";
        for (const auto& element : paramImage) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

        std::cout << "paramAnimation: ";
        for (const auto& element : paramAnimation) {
            std::cout << element << " ";
        }
        std::cout << std::endl;

    } catch (const std::out_of_range& e) {
        std::cout << "Erreur : " << e.what() << std::endl;
    };

}

// Fonction qui écrit les données dans un fichier JSON
void donnee::writeData(int numberScreen) {
    int nombreEcrant = numberScreen ;
    std::ostringstream json_output;
    json_output << "{" << std::endl;
    json_output << "  \"setting\": {" << std::endl;

    try {
        for (int i = 1; i <= nombreEcrant; ++i) {

            std::string height = std::to_string(paramImage.at(((i-1)*5)+1));                                                                                                                      //certainement inaxesible
            std::string width = std::to_string(paramImage.at(((i-1)*5)+2));
            std::string nbPixel = std::to_string(paramImage.at(((i-1)*5)+3));
            std::string posX = std::to_string(paramImage.at(((i-1)*5)+4));
            std::string posY = std::to_string(paramImage.at(((i-1)*5)+5));

            std::string rotation_speed = paramAnimation.at(((i-1)*5)+1);
            std::string rotation_direction = paramAnimation.at(((i-1)*5)+2);
            std::string rotation_axis = paramAnimation.at(((i-1)*5)+3);
            std::string translation_speed = paramAnimation.at(((i-1)*5)+4);
            std::string translation_direction = paramAnimation.at(((i-1)*5)+5);

            json_output << createImageBlock(i, height, width, nbPixel, posX, posY,rotation_speed,
                                            rotation_direction, rotation_axis,translation_speed, translation_direction);

            if (i != nombreEcrant) {
                json_output << "," << std::endl;
            }
        }
    }
    catch (const std::out_of_range &e) {
        std::cout << "Erreur zone 1 : " << e.what() << std::endl;
    }
    // Crée et ajoute des blocs d'image pour chaque écran dans le fichier JSON


    json_output << std::endl << "  }," << std::endl;
    json_output << "   \"dictionary \":{" << std::endl;
    json_output << "      \"name\":\"translation\"," << std::endl;
    json_output << "      \"type\":\".so\"," << std::endl;
    json_output << "      \"executable\":\"translationCode\"," << std::endl;
    json_output << "      \"param\":{" << std::endl;
    json_output << "         \"number\":4," << std::endl;
    json_output << "         \"parm1\":\"newParam\"," << std::endl;
    json_output << "         \"parm2\":\"newParam\"," << std::endl;
    json_output << "         \"parm3\":\"newParam\"," << std::endl;
    json_output << "         \"parm4\":\"newParam\"" << std::endl;
    json_output << "    }" << std::endl;
    json_output << "  }" << std::endl;
    json_output << "}";

try {
    // Écrit le contenu de json_output dans le fichier "output.json" et ferme le fichier
    std::ofstream output_file("output.json");
    output_file << std::setprecision(5) << json_output.str();
    output_file.close();
}
catch (const std::out_of_range &e) {
    std::cout << "Erreur : " << e.what() << std::endl;
}
    std::cout << "JSON output saved to output.json" << std::endl;
}

// Fonction qui crée un bloc d'image en format JSON en utilisant les paramètres fournis
std::string donnee::createImageBlock(int n, const std::string& height, const std::string& width,
                                     const std::string& nbPixel, const std::string& posX, const std::string& posY,
                                     const std::string& rotation_speed, const std::string& rotation_direction,
                                     const std::string& rotation_axis, const std::string& translation_speed,
                                     const std::string& translation_direction) {
    // Crée un flux de sortie pour construire le bloc d'image
    std::ostringstream image_block;
    image_block << "    \"image " << n << "\": {" << std::endl;
    image_block << "      \"Height\": " << height << "," << std::endl;
    image_block << "      \"Width\": " << width << "," << std::endl;
    image_block << "      \"nbPixel\": " << nbPixel << "," << std::endl;
    image_block << "      \"posX\": " << posX << "," << std::endl;
    image_block << "      \"posY\": " << posY << "," << std::endl;
    image_block << "      \"animation\":{" << std::endl;
    image_block << "        \"rotation\":{" << std::endl;
    image_block << "          \"speed\": \"" << rotation_speed << "\"," << std::endl;
    image_block << "          \"direction\":\"" << rotation_direction << "\"," << std::endl;
    image_block << "          \"rotation axis\":\"" << rotation_axis << "\"" << std::endl;
    image_block << "        } ," << std::endl;
    image_block << "        \"translation\":{" << std::endl;
    image_block << "          \"speed\":\"" << translation_speed << "\"," << std::endl;
    image_block << "          \"direction\":\"" << translation_direction << "\"" << std::endl;
    image_block << "        }" << std::endl;
    image_block << "      }" << std::endl;
    image_block << "    }";

    // Retourne le bloc d'image sous forme de chaîne de caractères
    return image_block.str();
}


