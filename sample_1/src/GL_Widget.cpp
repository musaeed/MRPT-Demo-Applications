#include <QGLWidget>
#include <QApplication>
#include <QDebug>
#include <cmath>
#include <mrpt/gui/CDisplayWindow3D.h>
#include <mrpt/system/threads.h>
#include <mrpt/system/os.h>
#include <mrpt/utils/CTicTac.h>
#include <mrpt/utils/CObserver.h>
#include <mrpt/opengl/gl_utils.h>
#include <mrpt/opengl/stock_objects.h>
#include <mrpt/opengl/CText.h>
#include <mrpt/opengl/CGridPlaneXY.h>
#include <mrpt/opengl/CAxis.h>
#include <mrpt/opengl/CBox.h>
#include <mrpt/opengl/CCylinder.h>
#include <mrpt/opengl/CSphere.h>
#include <mrpt/poses/CPose3D.h>
#include <GL/glut.h>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QTimer>

using namespace std;
using namespace mrpt;
using namespace mrpt::gui;
using namespace mrpt::opengl;
using namespace mrpt::utils;
using namespace mrpt::poses;

class GLWidget : public QGLWidget{

    COpenGLScene theScene;
    CTicTac  timer;
    QPoint mousePosition;
    COpenGLViewportPtr view;
    float azimuth;
    float elevation;
    float distance;
    QTimer qtimer;
    const double R = 8;
    const double W = 5.0, Q = 3.3;

    void initializeGL(){

        fillScene();
        view = theScene.getViewport();
        glClearColor(0.5, 0.5, 0.5, 1.0);
        azimuth = 25.f;
        elevation = 15.f;
        distance = 35.f;
        //qtimer = new QTimer(this);
        connect(&qtimer, SIGNAL(timeout()), this, SLOT(update()));
        qtimer.start(10);

    }

    /// @note camera decides renderer size
    void resizeGL(int w, int h){
        glViewport(0,0,w,h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, (float)w/h, 0.01, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0,0.0,2.5, 0.0,0.0,0.0, 0,1,0);
    }

    void paintGL(){

        theScene.render();
        opengl::CRenderizablePtr obj1 = theScene.getByName("ball");
        opengl::CRenderizablePtr obj2 = theScene.getByName("cylinder");

        const double t = timer.Tac();

        obj1->setLocation(R* cos(W*t)*sin(Q*t),R* sin(W*t),R* cos(W*t)*cos(Q*t));
        obj2->setLocation(-R* cos(W*t)*sin(Q*t),-R* sin(W*t),R* -cos(W*t)*cos(Q*t));


        view->getCamera().setAzimuthDegrees(azimuth);
        view->getCamera().setElevationDegrees(elevation);
        view->getCamera().setZoomDistance(distance);
    }

    void mouseMoveEvent(QMouseEvent *event){

        QPoint currentPos = event->pos();

        float x = -mousePosition.x() + currentPos.x();
        float y = -mousePosition.y() + currentPos.y();

        if(event->buttons() == Qt::LeftButton){


            if(x > 0){

                azimuth -= 5.f;

            }
            else{

                azimuth += 5.f;
            }

        }
        if(event->buttons() == Qt::RightButton){
            if(y > 0){

                elevation += 2.f;

            }
            else{

                elevation -= 2.f;
            }
        }
        mousePosition = currentPos;
    }

    void wheelEvent(QWheelEvent *event) {

        if(event->delta() > 0){
            if(distance > 2.f)
                distance -= 2.f;
        }else{


            distance += 2.f;


        }

    }

    void keyPressEvent(QKeyEvent *event){

        if(event->key() == Qt::Key_Right){

            azimuth -= 5.f;

        }

        if(event->key() == Qt::Key_Left){

            azimuth += 5.f;

        }

        if(event->key() == Qt::Key_Up){

            elevation -= 2.f;

        }

        if(event->key() == Qt::Key_Down){

            elevation += 2.f;

        }
    }

    void fillScene(){

        {
            opengl::CGridPlaneXYPtr obj = opengl::CGridPlaneXY::Create(-20,20,-20,20,0,1);
            obj->setColor(0.8,0.8,0.8);
            theScene.insert( obj );
        }

        theScene.insert( mrpt::opengl::stock_objects::CornerXYZ() );

        {
            opengl::CAxisPtr obj = opengl::CAxis::Create();
            obj->setFrequency(5);
            obj->enableTickMarks();
            obj->setAxisLimits(-10,-10,-10, 10,10,10);
            theScene.insert( obj );
        }


        {
            opengl::CSpherePtr obj = opengl::CSphere::Create();
            obj->setColor(0,0,1);
            obj->setRadius(0.3);
            obj->setLocation(0,0,1);
            obj->setName( "ball" );
            theScene.insert( obj );
        }

        {
            opengl::CCylinderPtr obj = CCylinder::Create();
            obj->setColor(1,0,0);
            obj->setRadii(1.f,0.01);
            obj->setLocation(1,0,0);
            obj->setName("cylinder");
            theScene.insert(obj);
        }

        timer.Tic();

    }

    void update(){

        updateGL();
    }

};
