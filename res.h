#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "sys.h"

#include <SFML/Graphics.hpp>

class PackageFile
{
public:
	std::string * name;
	int fileposition;
	int filesize;
	int origsize;
};

class Package
{
private:
	std::string * filename;
	std::ifstream * file;
	std::vector<PackageFile*> * files;
	int fpos;
	int readint();
	short readshort();
	std::string * readstring(int sz);
	void skip(int sz);
public:
	Package(std::string fname);
	~Package();
	PackageFile * getfile(std::string name);
	char * getdata(PackageFile * f);
	std::string * gettextdata(PackageFile * f);

};

class Tile
{
public:
	unsigned short index;
	unsigned char blocking;
};

class Map
{
public:
	Map(char*, int);
	void loadlayer(Tile *, char *, int *);
	unsigned short height, width;
	std::string name;
	//Tile * layer1;
	//Tile * layer2;
	//Tile * layer3;
	Tile * layer[3];
};

class Resources
{
private:
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, Map*> maps;
	std::string filename;
	Package * package;
public:
	Resources(std::string filename);
	sf::Texture *getTexture(std::string);
	Map *getMap(std::string);
	sf::Font mainfont;
};
