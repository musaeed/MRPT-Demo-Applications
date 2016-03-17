#include <QApplication>
#include <QDialog>
#include "GL_Widget.cpp"

using namespace std;
using namespace mrpt;
using namespace mrpt::gui;
using namespace mrpt::opengl;
using namespace mrpt::utils;

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    GLWidget widget;
    widget.showMaximized();
    glutInit(&argc, argv);
    return app.exec();
}
