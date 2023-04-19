

#ifndef PROJET_COMM_DONNEE_H
#define PROJET_COMM_DONNEE_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct ParamImg {
    int nbPixel;
    int posX;
    int posY;
    int height;
    int width;
    int ratio;
};


class donnee {
private :

    int numberScreen;
    int widthMur, heightMur;
    int state_vec;
    std::vector<int> vec;

    ParamImg Param{};
    string nom;
    string num;
    string temp_nom;
    string fileName;
    string data;
    vector<char> message;

public :
    std::string donnee::create_image_block(int n);
    std::vector<char> getdata(const std::string&);
    void setdata(int, int, int, int, int, int, int, int);
    int writedata();

    void testJson();
};


#endif //PROJET_COMM_DONNEE_H
