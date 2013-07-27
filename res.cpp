#include "res.h"
#define SWSHORT(X) ((unsigned short)X>>8) | ((unsigned short)X<<8)
using namespace std;

bool endsWith (std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


/////////////////////////////////////////////
//           Package Functions
//
/////////////////////////////////////////////
int Package::readint()
{
	char buf[4];
	file->read(buf, 4);
	fpos += 4;
	return ((unsigned char)buf[0]) | ((unsigned char)buf[1] << 8) | ((unsigned char)buf[2] << 16) | ((unsigned char)buf[3] << 24);
}

short Package::readshort()
{
	char buf[2];
	file->read(buf, 2);
	fpos += 2;
	return (((unsigned char)buf[0]) | ((unsigned char)buf[1] << 8));
}

string * Package::readstring(int sz)
{
	char * buf = new char[sz+1];
	file->read(buf, sz);
	buf[sz] = '\0';
	string * str = new string(buf);
	delete buf;
	fpos += sz;
	return str;
}

void Package::skip(int sz)
{
	if(sz > 0)
	{
		file->seekg((int)file->tellg() + sz);
		fpos += sz;
	}
}

Package::Package(string fname)
{
	fpos = 0;
	file = new ifstream();
	files = new vector<PackageFile*>();
	file->open(fname.c_str(), ios::binary | ios::in);
	if(file->is_open())
	{
		int head = readint();
		while(head == 0x04034b50)
		{
			filename = new string(fname);
			skip(2*5 + 4); //Skip useless info
			unsigned int origsize = readint();
			unsigned int compsize = readint();
			int fnamesize = readshort();
			int extrasize = readshort();
			string * name = readstring(fnamesize);
			PackageFile * f = new PackageFile();
			f->name = name;
			f->origsize = origsize;
			f->filesize = compsize;
			skip(extrasize);
			f->fileposition = fpos;
			files->push_back(f);
			skip(compsize);
			head = readint();
		}
		file->close();
	}
}

Package::~Package()
{
	while(files->size() > 0)
	{
	    delete files->back()->name; // DELETING THIS CAUSES A SEGFAULT, WHY??????
		delete files->back();
		files->pop_back();
	}
	delete files;
	delete filename;
	if(file->is_open()) file->close();
	delete file;
}

PackageFile * Package::getfile(string name)
{
	for(unsigned int i = 0; i < files->size(); i++)
	{
		if(files->at(i)->name->compare(name) == 0)
		{
			return files->at(i);
		}
	}
	return NULL;
}

char * Package::getdata(PackageFile * f)
{
	if(f == NULL) return NULL;
	char * buf = NULL;
	while(file->is_open());
	file->open(filename->c_str(), ios::binary | ios::in);
	if(file->is_open())
	{
		buf = new char[f->filesize];
		file->seekg(f->fileposition);
		file->read(buf, f->filesize);
		file->close();
	}
	return buf;
}

string * Package::gettextdata(PackageFile * f)
{
	char * buf = (char *) malloc(f->filesize + 1);
	char * tbuf = getdata(f);
	memcpy(buf, tbuf, f->filesize);
	buf[f->filesize] = '\0';
	string * s = new string(buf);
	free(tbuf);
	free(buf);
	return s;
}

Resources::Resources(std::string fname)
{
	filename = fname;
	package = new Package(filename);
	for(auto pkg : *(package->files))
	{
		std::string filename = *(pkg->name);
		info("Loading Resource: %s", filename.c_str());
		
		if(endsWith(filename, "png"))
		{
			sf::Texture * tex = new sf::Texture();
			PackageFile * f = package->getfile(filename);
			char * data = package->getdata(f);
			tex->loadFromMemory(data, f->origsize);
			textures[filename] = tex;
		}
		else if(endsWith(filename, "map"))
		{
			PackageFile * f = package->getfile(filename);
			char * data = package->getdata(f);
			Map * map = new Map(data, f->origsize);
			maps[filename] = map;
		}
		else if(endsWith(filename, "lua") || endsWith(filename, "txt"))
		{
			PackageFile * f = package->getfile(filename);
			string * text = package->gettextdata(f);
			texts[filename] = text;
		}
	}

	if(!mainfont.loadFromFile("font.ttf"))
		info("Failed to load font.ttf");
}

sf::Texture* Resources::getTexture(std::string name)
{
	return textures[name];
}

Map* Resources::getMap(std::string name)
{
	return maps[name];
}

std::string *Resources::getText(std::string name)
{
	return texts[name];
}

Map::Map(char * data, int size)
{
	char head[9];
	char rawname[9];
	char * pos = data;
	memcpy(head, pos, 8); pos += sizeof(char) * 8;
	memcpy(rawname, pos, 8); pos += sizeof(char) * 8;
	head[8]=0;
	rawname[8]=0;
	name = rawname;
	memcpy(&width, pos, sizeof(short)); pos += sizeof(short);
	memcpy(&height, pos, sizeof(short)); pos += sizeof(short);
	layer[0] = new Tile[width * height];
	layer[1] = new Tile[width * height];
	layer[2] = new Tile[width * height];
	loadlayer(layer[0], &pos);
	loadlayer(layer[1], &pos);
	loadlayer(layer[2], &pos);
}

void Map::loadlayer(Tile * layer, char ** pos)
{
	for(int n = 0; n < width * height; n++)
	{
		memcpy(&layer[n].index, (*pos), sizeof(short));
		memcpy(&layer[n].blocking, (*pos+2), sizeof(char));
		*pos += sizeof(char) * 4;
	}
}
