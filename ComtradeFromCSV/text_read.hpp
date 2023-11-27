#ifndef TEXT_READ_H
#define TEXT_READ_H
#include "Header.h"

class Text_read
{
public:
	Text_read(std::string nameFile, std::string strPath);
	const int sign_quantity = 8;
	std::string Text_read_SIGCC = "";
	float Text_read_SIGB = 0.0;
	float Text_read_SIGSKEW = 0.0;
	char Text_read_SIGTYPE = 'A';
	float Text_read_SIGM = 0;
	float Kct = 12000;
	float Kvt = 20000/100;
};

#endif // TEXT_READ_H
