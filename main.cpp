#include "texturepacker.h"
#include <QtWidgets/QApplication>
#include "NImage.h"

 

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);  
	TexturePacker w;
	w.show();
	return a.exec();
}
