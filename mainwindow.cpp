#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "CTimeLineTrack.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    view = new CTimeLineView( this );
    //view->scene()->setSceneRect(-50,0, 1920, 1080);
    view->setChannelLabelWidth(200);
//    connect( view->scene(), &QGraphicsScene::focusItemChanged, [this](QGraphicsItem *newFocus, QGraphicsItem *oldFocus, Qt::FocusReason reason){
//        qDebug() << "newFocus:" << newFocus << "oldFocus:" << oldFocus;
//    } );

    view->setInteractive(true);
    view->setMouseTracking(true);
    view->setFocus();


    CTimeLineChannel* channel = new CTimeLineChannel("id", "Test channel2");

    channel->setTimeLinePtr( view );
    channel->setColor( Qt::cyan );
    view->addChannel( channel );

    channel = new CTimeLineChannel("id", "Test 2");
    channel->setTimeLinePtr( view );
    channel->setColor( Qt::red );
    view->addChannel( channel );

    channel = new CTimeLineChannel("id", "Blala 2");
    channel->setTimeLinePtr( view );
    channel->setColor( Qt::green );
    view->addChannel( channel );

    channel = new CTimeLineChannel("id", "trrr 2");
    channel->setTimeLinePtr( view );
    channel->setColor( Qt::yellow );
    view->addChannel( channel );

    channel = new CTimeLineChannel("id", "tr 2");
    channel->setTimeLinePtr( view );
    channel->setColor( Qt::red );
    view->addChannel( channel );

    channel = new CTimeLineChannel("id", "trrr 3");
    channel->setTimeLinePtr( view );
    channel->setColor( Qt::cyan );
    view->addChannel( channel );

    channel = new CTimeLineChannel("id", "trrr 4");
    channel->setTimeLinePtr( view );
    channel->setColor( Qt::green );
    view->addChannel( channel );



    setCentralWidget(view);

}

MainWindow::~MainWindow()
{
    delete ui;
}
