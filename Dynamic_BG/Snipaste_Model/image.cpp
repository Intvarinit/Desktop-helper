#include "image.h"
#include "ui_image.h"

#include <QMenu>

Image::Image(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Image)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

    Save = new QAction("保存截图");
    connect(Save, &QAction::triggered,this,[=](){
        QString data = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString("Snipaste_%1.png").arg(data), tr("images(*.png,*.jpg,*.bmp)"));
        this -> pix.save(fileName);
    });
	Exit = new QAction("Exit");
	connect(Exit, &QAction::triggered,this,[=](){
		this -> close();
	});

    this -> grabKeyboard();       //不灵敏的时候使用
    setMouseTracking(true);
}

Image::~Image()
{
    delete ui;
}

void Image::setPix(QPixmap pix)
{
    this -> pix = pix;
    size = pix.size();
    ui -> label -> setPixmap(pix);
}

void Image::mousePressEvent(QMouseEvent *evt)
{
    topLeft = evt-> pos();
}

void Image::mouseMoveEvent(QMouseEvent *evt)
{
    this -> move(evt->globalPos() - topLeft);
}

//创建菜单
void Image::contextMenuEvent(QContextMenuEvent *evt)
{
    QMenu *menu = new QMenu(this);
    menu->addAction(Save);
    menu->addAction(Exit);
    menu->move(evt->globalPos());
    menu->show();
}

void Image::keyPressEvent(QKeyEvent *evt)
{
    if(evt -> key() == Qt::Key_Escape){     //退出截图
        this -> close();
//    }else if(evt -> modifiers() == Qt::ControlModifier && evt -> key() == Qt::Key_Plus){    //Ctrl + '+'
    }else if(evt -> key() == Qt::Key_Plus){    //放大图像
        size *= 1.1;
        display = pix.scaled(size,Qt::KeepAspectRatio);
        ui -> label -> setPixmap(display);
    }else if(evt -> key() == Qt::Key_Minus){   //缩小图像
        size *= 0.9;
        display = pix.scaled(size,Qt::KeepAspectRatio);
        ui -> label -> setPixmap(display);
    }else if(evt -> modifiers() == Qt::ControlModifier && evt -> key() == Qt::Key_C){
        QClipboard* board = QApplication::clipboard();
        board->setPixmap(pix);
    }
}

void Image::keyReleaseEvent(QKeyEvent *evt)
{

}
