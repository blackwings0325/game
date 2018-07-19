#include "view.h"
#include "ui_view.h"
#include <QDebug>
#include <QFont>
#include <QThread>

QColor colors[11]{QColor(212,212,170),QColor(166,74,0),QColor(191,111,48),QColor(255,113,0),
            QColor(255,149,64),QColor(255,177,115),QColor(255,169,0),QColor(191,143,48),
            QColor(166,110,0),QColor(255,190,64),QColor(255,207,115)};

View::View(QWidget *parent) :  //ctor
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background,QColor(255,222,173));
    this->setPalette(palette);


    QFont font;
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPixelSize(30);

    score_label = new QLabel("SCORE",this);
    score_label->setGeometry(20,20,200,50);
    score_label->setAlignment(Qt::AlignCenter);
    score_label->setFont(font);

    best_label = new QLabel("BEST",this);
    best_label->setGeometry(240,20,200,50);
    best_label->setAlignment(Qt::AlignCenter);
    best_label->setFont(font);

    now_score = new QLabel("0",this);
    now_score->setGeometry(20,70,200,50);
    now_score->setAlignment(Qt::AlignCenter);
    now_score->setFont(font);

    best_score = new QLabel("0",this);
    best_score->setGeometry(240,70,200,50);
    best_score->setAlignment(Qt::AlignCenter);
    best_score->setFont(font);

    restart_btn = new QPushButton("RESTART",this);
    restart_btn->setGeometry(430,30,200,100);
    restart_btn->setFont(font);

    connect(restart_btn,SIGNAL(clicked(bool)),this,SLOT(restart_btn_press()));


    _ptrViewProSink = std::make_shared<ViewProSinks>(ViewProSinks(this));
    _ptrViewSetSink = std::make_shared<ViewSetSink>(ViewSetSink(this));
    _ptrDirectionSink = std::make_shared<DirectionSink>(DirectionSink(this));
    setMatrix(NULL);
}

View::~View()
{
    delete ui;
}

void View::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_S||e->key()==Qt::Key_Down)
    {
        _ptrDirectionCommand->SetParameter(1);
        _ptrDirectionCommand->Exec();
        View::update();
    }
    if(e->key()==Qt::Key_W||e->key()==Qt::Key::Key_Up)
    {
        _ptrDirectionCommand->SetParameter(2);
        _ptrDirectionCommand->Exec();
        View::update();
    }
    if(e->key()==Qt::Key_A||e->key()==Qt::Key::Key_Left)
    {
        _ptrDirectionCommand->SetParameter(3);
        _ptrDirectionCommand->Exec();
        View::update();
    }
    if(e->key()==Qt::Key_D||e->key()==Qt::Key::Key_Right)
    {
        _ptrDirectionCommand->SetParameter(4);
        _ptrDirectionCommand->Exec();
        View::update();
    }


}

void View::setMatrix(std::shared_ptr<SquareMatrix> spMatrix)  //connect data to this
{
    this->_spMatrix = spMatrix;
}

void View::set_ptrCommand(std::shared_ptr<ICommandBase> ptrCommand)  //connect command to this
{
    _ptrCommand = ptrCommand;
}

void View::set_ptrDirection(std::shared_ptr<ICommandBase> ptrDirection)
{
    _ptrDirectionCommand = ptrDirection;
}

std::shared_ptr<IPropertyNotification> View::getPtrViewProSink(void)  //return property notification
{
    return std::static_pointer_cast<IPropertyNotification>(_ptrViewProSink);
}

std::shared_ptr<ICommandNotification> View::getPtrViewSetSink(void)  //return command notifycation
{

    return std::static_pointer_cast<ICommandNotification>(_ptrViewSetSink);
}

std::shared_ptr<ICommandNotification> View::getDirectionSink(void)
{
    return std::static_pointer_cast<ICommandNotification>(_ptrDirectionSink);
}


void View::paintEvent(QPaintEvent *ev)
{
    int i,j;
    QPainter painter(this);
    QBrush brush(QColor(124,99,84));
    //brush.setColor();
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRect(90,190,370,370);

    QFont font;
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPixelSize(35);

    now_score->setText(QString::number(_spMatrix->getScore()));
    best_score->setText(QString::number(_spMatrix->getBest()));

    for(i=0;i<4;i++)
        for(j=0;j<4;j++){
            if(this->_spMatrix->getChildNumber(i,j) == 0){
                painter.setPen(Qt::NoPen);
                brush.setColor(QColor(193,160,117));
                painter.setBrush(brush);
                painter.drawRoundedRect((100+(90*j)),(200+(90*i)),80,80,4,4);

            }
            else {
                painter.setPen(Qt::NoPen);
                brush.setColor(colors[get_color(this->_spMatrix->getChildNumber(i,j))]);
                painter.setBrush(brush);
                painter.drawRoundedRect((100+(90*j)),(200+(90*i)),80,80,4,4);
                painter.setPen(QColor(0,0,0));
                painter.setFont(font);
                painter.drawText((100+(90*j)),(200+(90*i)),80,80,Qt::AlignCenter,QString::number(this->_spMatrix->getChildNumber(i,j),10));
            }
        }
}

int View::get_color(int n)
{
    int i=-1;
    n/=2;
    while(n!=0){
        i++;
        n/=2;
    }
    return i;
}

void View::restart_btn_press()
{

}