#include "gamewidget.h"


QVector2D GameWidget::getTranslation() const
{
    return translation;
}

void GameWidget::setTranslation(const QVector2D &value)
{
    translation = value;
}

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),m_lastRect(0,0,0,0)
{


    this->player = new Player(QVector2D(30,30),25);
    this->level = new Level(this->player);
    startTimer(1000/60);  // 60 fps
}

GameWidget::~GameWidget()
{
    delete player;
    delete level;
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    if(m_lastRect.height() < 10)
    {
        m_lastRect = event->rect();
    }
    //this->move(this->width()/2-player->getCentr().x(), this->height()/2-player->getCentr().y());
    //this->raise();
   // this->resize(this->width(), this->height());
    level->draw(this);
    player->draw(this);
    #ifndef QT_NO_DEBUG   // если Отладка, то рисуеются линии отвечающие за определение столкновения объектов. (а NDEBUG не объявлен, я думал это стандартная костанта для всех IDE, а вон оно как)
        this->level->checkCollision(this);
    #endif
}

void GameWidget::timerEvent(QTimerEvent *event)
{
    this->action();
    this->setTranslation(QVector2D(this->width()/2-player->getCentr().x(), this->height()/2-player->getCentr().y()));
    this->repaint();
}

void GameWidget::mouseMoveEvent(QMouseEvent *ev)
{
//    this->x = ev->x();
   // this->y = ev->y();
    player->moveTo(QVector2D(ev->x()- this->getTranslation().x(), ev->y()- this->getTranslation().y()));
    emit mousePos();
}

void GameWidget::mousePressEvent(QMouseEvent *ev)
{
    emit mousePressed();
}

void GameWidget::leaveEvent(QEvent *ev)
{
    emit mouseLeft();
}

void GameWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    player->stop();
}


void GameWidget::action()
{

    player->action();
    #ifdef QT_NO_DEBUG   // если не Отладка
        this->level->checkCollision(nullptr);
    #endif*/
   // this->level->checkCollision(nullptr);
}


