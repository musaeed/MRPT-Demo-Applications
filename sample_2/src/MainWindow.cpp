#include "../headers/MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Ready");
    ui->statusBar->setToolTip("Click the open button to open a gridmap file");
    ui->centralWidget->installEventFilter(this);

    ui->actionExit->setShortcut(Qt::Key_F4 | Qt::Key_Alt);
    ui->actionFull_Screen->setShortcut(Qt::Key_F11);
    ui->actionHelp->setShortcut(Qt::Key_F1);
    ui->actionOpen->setShortcut(Qt::Key_O | Qt::CTRL);
    ui->actionProperty_Editor->setShortcut(Qt::Key_P | Qt::CTRL);

}

MainWindow::~MainWindow()
{

    delete ui;

}


void MainWindow::on_actionOpen_triggered()
{
    QString name = QFileDialog::getOpenFileName(this, "Select gridmap file",tr("All files (*.*);;GRIDMAP(*.gridmap)") ,"GRIDMAP (*.gridmap)");

    if(name.isEmpty()){

        return;
    }

    openFile(name);

}

void MainWindow::openFile(QString filename){



    COccupancyGridMap2D gridmap;
    CFileGZInputStream in_s(filename.toStdString());
    in_s >> gridmap;
    CSetOfObjectsPtr gl_grid;
    if (!gl_grid)
        gl_grid = CSetOfObjects::Create();

    gl_grid->clear();
    gridmap.getAs3DObject(gl_grid);
    gl_grid->setName("gridmap");

    opengl::CRenderizablePtr obj = QtGL::theScene.getByName("gridmap");

    if(obj != NULL){

        QtGL::theScene.removeObject(obj);
    }


    QtGL::theScene.insert(gl_grid);
    ui->widget->setRender(true);
    ui->statusBar->showMessage(filename);

}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

bool MainWindow::eventFilter(QObject *target, QEvent *event) {
    if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Escape){
            normalScreen();
        }

        return QObject::eventFilter(target, event);
    }
}

void MainWindow::on_actionFull_Screen_triggered()
{
    std::system("notify-send 'MRPT - Gridmap visualizer' 'Please use escape to exit fullscreen'");
    this->showFullScreen();
    ui->toolBar->hide();
    ui->statusBar->hide();

}

void MainWindow::normalScreen(){

    this->showNormal();
    ui->toolBar->show();
    ui->statusBar->show();
    this->showMaximized();

}

void MainWindow::on_actionHelp_triggered()
{
    HelpDialog dialog(this);
    dialog.setWindowTitle("Help");
    dialog.exec();
}

void MainWindow::on_actionProperty_Editor_triggered()
{
    PropertyEditor dialog(this);
    dialog.setWindowTitle("Property Editor");
    dialog.exec();
}
