#include "snapshot.h"
#include "image.h"
#include "ui_snapshot.h"

#include <QPainter>
#include <QToolTip>

//#include <QGraphicsDropShadowEffect>
Snapshot::Snapshot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Snapshot)
{
    ui -> setupUi(this);
    setWindowTitle("Snipaste");
//    this -> rect = new QRect;
    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);
    setWindowOpacity(0.5);
    this -> setGeometry(0,0,1920,1080);
    this -> grabKeyboard();       //不灵敏的时候使用
    setMouseTracking(true);
    hide();
//	emit finish();

//    refer = new QDialog;
//    refer->setWindowOpacity(0);
//    refer->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
//    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(refer);
//    shadow->setOffset(0,0);
//    shadow->setColor(QColor(0,255,255,127));
//    shadow->setBlurRadius(10);
//    refer->setGraphicsEffect(shadow);


//    refer->setStyleSheet("border:1px solid rgb(0,255,255)");
//    refer->hide();
    refer_pos = new QRect;

    show_refer = false;

    pen.setColor(Qt::green);
    pen.setWidth(3);
}

Snapshot::~Snapshot()
{
    delete refer_pos;
}

//左上角开始截图
void Snapshot::mousePressEvent(QMouseEvent* evt){
//    this -> rect -> setTopLeft(evt->pos());
    refer_pos->setTopLeft(evt->pos());
//    refer->setGeometry(evt->x(),evt->y(),0,0);
//    refer->show();
    show_refer = true;
    update();
}

void Snapshot::mouseMoveEvent(QMouseEvent* evt){
    if(evt->pos().x() < refer_pos->topLeft().x()){			//左边
        if(evt->pos().y() < refer_pos->topLeft().y()){		//左上
            refer_pos -> setBottomRight(refer_pos->topLeft());
            refer_pos -> setTopLeft(evt->pos());
        }else{											//左下
            refer_pos -> setTopRight(refer_pos->topLeft());
            refer_pos -> setBottomLeft(evt->pos());
        }
    }else if(evt->pos().y() < refer_pos->topLeft().y()){		//右上
        refer_pos -> setBottomLeft(refer_pos->topLeft());
        refer_pos -> setTopRight(evt->pos());
    }else{												//右下，正常截图
        refer_pos -> setBottomRight(evt->pos());
    }
    update();       //重绘参考线
//    refer->setGeometry(refer_pos->topLeft().x(),refer_pos->topLeft().y(),refer_pos->width(),refer_pos->height());
//    if(refer->isHidden()){
//        refer->show();
//    }
    QString pos = QString("%1,%2").arg(refer_pos->width()).arg(refer_pos->height());
    QToolTip::showText(evt->pos(),pos,this);
}

//结束后隐藏窗口并截图
void Snapshot::mouseReleaseEvent(QMouseEvent* evt){
//    if(evt->pos().x() < rect->topLeft().x()){			//左边
//        if(evt->pos().y() < rect->topLeft().y()){		//左上
//            this -> rect->setBottomRight(rect->topLeft());
//            this -> rect->setTopLeft(evt->pos());
//        }else{											//左下
//            this -> rect->setTopRight(rect->topLeft());
//            this -> rect->setBottomLeft(evt->pos());
//        }
//    }else if(evt->pos().y() < rect->topLeft().y()){		//右上
//        this -> rect->setBottomLeft(rect->topLeft());
//        this -> rect->setTopRight(evt->pos());
//    }else{												//右下，正常截图
//        this -> rect -> setBottomRight(evt->pos());
//    }

    hide();
    Snap();
    show_refer = false;
    update();
}

void Snapshot::Snap()
{
    QScreen* scrn = QGuiApplication::primaryScreen();
    pix = scrn -> grabWindow(0,refer_pos->x(),refer_pos->y(),refer_pos->width(),refer_pos->height());
    Image* snap = new Image;
    snap -> setPix(pix);
    snap->setGeometry(refer_pos->x(),refer_pos->y(),refer_pos->width(),refer_pos->height());
    snap -> show();
    emit finish();
}

void Snapshot::paintEvent(QPaintEvent *)
{
    if(show_refer){
        QPainter paint(this);
        paint.setPen(pen);
        paint.drawRect(*refer_pos);
    }
}


//键盘事件
void Snapshot::keyPressEvent(QKeyEvent *evt)
{
    if(evt -> key() == Qt::Key_Escape){
        this -> hide();
    }/*else if(evt->key() == Qt::Key_1){

    }*/
}

