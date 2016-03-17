#include <iostream>

#include "headers/MainWindow.hpp"
#include <QApplication>
#include <iostream>
#include <GL/glut.h>

using namespace std;



int main(int argc, char *argv[]){

    glutInit(&argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();

    return 0;
}
