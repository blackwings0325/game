/*class view, THAT IS OUR GAMEWINDOW*/
#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <memory>
#include "Common/square.h"
#include "Common/etlbase.h"
#include "View/ViewSinks/viewprosinks.h"
#include "View/ViewSinks/directionsink.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMovie>

class ViewProSinks;
class DirectionSink;

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT
    QPoint mousePos;

public:
    explicit View(QWidget *parent = 0);
    ~View();

    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void setMatrix(std::shared_ptr<SquareMatrix> spMatrix);  //connect to data
    void set_ptrCommand(std::shared_ptr<ICommandBase> ptrCommand); //connect to command ?
    void set_ptrDirection(std::shared_ptr<ICommandBase> ptrDirection);

    std::shared_ptr<IPropertyNotification> getPtrViewProSink(void); //return two command pointer ?
    std::shared_ptr<ICommandNotification> getDirectionSink(void);

    void paintEvent(QPaintEvent*);
    void Animation();
    void sleep(unsigned int msec);
    void paint_square();
private slots:
    void restart_btn_press();
    void emoji_btn_press();
private:
    Ui::View *ui;
    std::shared_ptr<SquareMatrix> _spMatrix;
    std::shared_ptr<ViewProSinks> _ptrViewProSink;
    std::shared_ptr<DirectionSink> _ptrDirectionSink;
    std::shared_ptr<ICommandBase> _ptrDirectionCommand;
    std::shared_ptr<ICommandBase> _ptrCommand;

    QLabel *score_label;
    QLabel *best_label;
    QLabel *now_score;
    QLabel *best_score;
    QPushButton *restart_btn;
    int get_color(int n);
    QLabel *square[16];
    QPropertyAnimation *anim[16];
    QParallelAnimationGroup group;
    QPropertyAnimation *comeup[16];
    QParallelAnimationGroup GroupComeUp;
    
    
    QPushButton *emoji_btn;
    QMovie *pic[11];
    static int emoji;
};

#endif // VIEW_H
