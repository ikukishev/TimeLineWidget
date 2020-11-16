#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "CTimeLineEffect.h"

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

    view->setCompositionDuration(50000);

    view->setInteractive(true);
    view->setMouseTracking(true);
    view->setFocus();

    auto effectAdded = []( ITimeLineChannel* tlChannel, IEffect* effect )
    {
       qDebug() <<  "effectAdded" << tlChannel->label() << "has new" << effect->getUuid();
    };

    auto effectDeleted = []( ITimeLineChannel* tlChannel, QUuid uuid )
    {
       qDebug() << "effectDeleted" <<  tlChannel->label() << uuid << "items";
    };

    auto effectChanged = [](  ITimeLineChannel* tlChannel, IEffect* effect )
    {
       qDebug() << tlChannel->label()
                << "effect changed. label:" << effect->effectNameLabel()
                << "position:" << effect->effectStartPosition()
                << "duration:" << effect->effectDuration();
    };

    auto effectSelected = [](  ITimeLineChannel* tlChannel, IEffect* effect )
    {
       qDebug() << tlChannel->label()
                << "effect selected. label:" << effect->effectNameLabel()
                << "position:" << effect->effectStartPosition()
                << "duration:" << effect->effectDuration();
    };

    CTimeLineChannel* channel = new CTimeLineChannel("id", "Test channel2", view);
    connect( channel, &CTimeLineChannel::effectAdded, effectAdded );
    connect( channel, &CTimeLineChannel::effectRemoved, effectDeleted );

    connect( channel, &CTimeLineChannel::effectChanged, effectChanged );
    connect( channel, &CTimeLineChannel::effectSelected, effectSelected );

    CTimeLineEffect::EffectFactory::factory.create( channel, 1000 );

    CTimeLineEffect::EffectFactory::factory.create( channel, 1 );

    CTimeLineEffect::EffectFactory::factory.create( channel, 25000 )->setEffectDuration(10000);

    CTimeLineEffect::EffectFactory::factory.create( channel, 49000 )->setEffectDuration(10000);


    channel->setColor( Qt::cyan );
    view->addChannel( channel );



    channel = new CTimeLineChannel("id", "Test 2", view);
    connect( channel, &CTimeLineChannel::effectAdded, effectAdded );
    connect( channel, &CTimeLineChannel::effectRemoved, effectDeleted );
    channel->setColor( Qt::red );
    view->addChannel( channel );

    CTimeLineEffect::EffectFactory::factory.create( channel, 1 );

    channel = new CTimeLineChannel("id", "Blala 2", view);
    connect( channel, &CTimeLineChannel::effectAdded, effectAdded );
    connect( channel, &CTimeLineChannel::effectRemoved, effectDeleted );
    channel->setColor( Qt::green );
    view->addChannel( channel );

    channel = new CTimeLineChannel("id", "trrr 2", view);
    connect( channel, &CTimeLineChannel::effectAdded, effectAdded );
    connect( channel, &CTimeLineChannel::effectRemoved, effectDeleted );
    channel->setColor( Qt::yellow );
    view->addChannel( channel );

    channel = new CTimeLineChannel("id", "tr 2", view);
    connect( channel, &CTimeLineChannel::effectAdded, effectAdded );
    connect( channel, &CTimeLineChannel::effectRemoved, effectDeleted );
    channel->setColor( Qt::red );
    view->addChannel( channel );

    channel = new CTimeLineChannel("id", "trrr 3", view);
    connect( channel, &CTimeLineChannel::effectAdded, effectAdded );
    connect( channel, &CTimeLineChannel::effectRemoved, effectDeleted );
    channel->setColor( Qt::cyan );
    view->addChannel( channel );

    channel = new CTimeLineChannel("id", "trrr 4", view);
    connect( channel, &CTimeLineChannel::effectAdded, effectAdded );
    connect( channel, &CTimeLineChannel::effectRemoved, effectDeleted );
    channel->setColor( Qt::green );
    view->addChannel( channel );


    connect( view, &CTimeLineView::playFromPosition, []( CTimeLineView* view, uint64_t position ){
       view->setCompositionPosition( position );
    });



    setCentralWidget(view);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRemove_triggered()
{
   if (view->channels().end() != view->channels().begin())
   {
      if ( *view->channels().begin() )
      {
         view->removeChannel( *view->channels().begin() );
      }

   }
}
