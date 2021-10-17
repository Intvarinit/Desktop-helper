#include "widget.h"
#include "ui_widget.h"

//#include <QDebug>
//#include <QProcess>
//#include <QMap>
#include <QSettings>
#include <QDir>
#include <QFileInfo>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);        //去掉窗口标题
    setAttribute(Qt::WA_TranslucentBackground);     //设置窗口透明
    setWindowIcon(QIcon(":/DyBg.ico"));

//    QDir dir("C:/Qt/DEMO/Projects/Dynamic_BG/background");
    curDir = QDir().currentPath();
    QDir dir("./background");
//    if(dir.exists()){
//    }
    int img_num = dir.count() - 2;  //减去当前目录和上级目录
//    qDebug() << img_num;
    //设置写入
    QSettings BG_set("ProgramSet.ini", QSettings::IniFormat);
    BG_set.beginGroup("background");
    BG_set.setValue("backgroundNum",img_num);
//    qDebug() << BG_set.status();
    BG_set.endGroup();
//        qDebug() << "WriteBack!";
    backGroundNum = BG_set.value("background/backgroundNum").toInt();
//    qDebug() << BG_set.status() << backGroundNum;

    //截图模块初始化
//    snap.hide();
    hided = false;
    connect(&snap,&Snapshot::finish,[=](){
        if(!hided){
            this->show();
            hided = false;
        }
    });

    //人物初始化
    ui -> widget -> setStyleSheet(QString("background-image:url(:/res/Role/Role1.png);"
                                          "background-repeat:no-repeat;"));

    this -> timer.start(3000);
    connect(&timer, &QTimer::timeout,this, &Widget::roleCut);

    //设置按键格式
    ui -> Set -> setIcon(QIcon(":/res/menu/setting.png"));
    ui -> Minimum -> setIcon(QIcon(":/res/menu/sub.png"));
    ui -> Close -> setIcon(QIcon(":/res/menu/quit.png"));
    ui->BG->setIcon(QIcon(":/res/menu/BG.png"));
    ui->Snap->setIcon(QIcon(":/res/menu/Snipaste.png"));
    ui->Save_BG->setIcon(QIcon(":/res/menu/add.png"));
    setStyleSheet("QPushButton{border:none; background-color:black; width:32px; height:32px}"
                  "QPushButton::hover{background-color:red;}");

    tray = new MyTray(this);
    //托盘功能绑定
    connect(tray,&MyTray::showMain,[=](){           //接收托盘的显示信号
        this->show();
        hided = false;
    });
    connect(tray,&MyTray::quit,[=](){               //接收托盘的退出信号
//        qDebug() << "Exit";
        on_Close_clicked();
    });
    connect(tray,&MyTray::ScrCut,[=](){             //接收托盘请求截图的信号
        on_Snap_clicked();
//        qDebug() << "CutScrn Ending!";
    });
    connect(tray,&MyTray::setBg,[=](){              //接收托盘请求设置背景的信号
        on_BG_clicked();
    });
    tray -> show();

    ui->BG->hide();
    ui->Snap->hide();
    ui->Save_BG->hide();
    expend = false;

}

Widget::~Widget()
{
//    qDebug() << "Terminate!";
    QSettings BG_set("ProgramSet.ini", QSettings::IniFormat);
    BG_set.beginGroup("background");
    BG_set.setValue("backgroundNum",backGroundNum);
    BG_set.endGroup();
    delete ui;
}

void Widget::mouseMoveEvent(QMouseEvent *evt)
{
    this -> move(evt -> globalPos() - this -> moveleftTop);
}

void Widget::mousePressEvent(QMouseEvent *evt)
{
    this -> moveleftTop = evt -> pos();
}

void Widget::roleCut()
{
    static int flag = 1;
    flag = flag%4 + 1;
    ui -> widget -> setStyleSheet(QString("background-image:url(:/res/Role/Role%1.png);"
                                          "background-repeat:no-repeat;").arg(char(flag + '0')));
}

void Widget::on_Set_clicked()       //设置的选择
{
    if(!expend){
        ui->BG->show();
        ui->Snap->show();
        ui->Save_BG->show();
        expend = true;
    }else{
        ui->BG->hide();
        ui->Snap->hide();
        ui->Save_BG->hide();
        expend = false;
    }
}

void Widget::on_Close_clicked()
{
    QApplication* app;
    app->quit();
}

void Widget::on_Minimum_clicked()
{
    this -> hide();
    hided = true;
//方式一：获取整个屏幕
//    QScreen* scrn = QGuiApplication::primaryScreen();
//    scrn->grabWindow(0).save("123.png");
//    scrn->grabWindow(0,0,0,200,400).save("123.png");

//方式二：获取部分屏幕
//    QRect rect = this->geometry();
//    QPixmap pix = this -> grab(QRect(0,0,200,200));
//    pix.save("123.png");

    //    this -> show();
}

void Widget::setBG(QString path)
{
    if(path == "")
        return;
    QSettings wallPaper("HKEY_CURRENT_USER\\Control Panel\\Desktop", QSettings::NativeFormat);
//    QString path("C:/Qt/DEMO/Dynamic_BG/res/back/1.jpg");
    //把注册表的桌面图片路径改为指定路径.
    wallPaper.setValue("Wallpaper", path);

    QByteArray byte = path.toLocal8Bit();
    //调用windows api.
    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, byte.data(), SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
}

void Widget::on_BG_clicked()
{
//    QString BgPath = QFileDialog::getOpenFileName(this, "选择壁纸","./","Image(*.jpg *.png *.gif)");
    int rand = qrand()%backGroundNum + 1;
    QString BgPath = QString("%1/background/back%2.png").arg(curDir).arg(rand);
    if(QFileInfo(BgPath).isFile()){
        setBG(BgPath);
    }
}

//void Widget::keyPressEvent(QKeyEvent *evt)
//{
//    if(evt -> key() == Qt::Key_X){     //Ctrl + 1截图
//        qDebug() << "Paste";
//        snap -> show();
//    }
//    return QWidget::keyPressEvent(evt);
//}

void Widget::on_Snap_clicked()
{
//    QScreen* sc = QGuiApplication::primaryScreen();

//    QPixmap pix = sc -> grabWindow(0,0,0,1920,1080);
//    this->show();
//    QString Save_path = QFileDialog::getSaveFileName(this,"保存截图","./","Image(*.png *.jpg)");
//    pix.save(Save_path);
    this->hide();
    snap.show();
}

void Widget::on_Save_BG_clicked()
{
    QString BgName = QFileDialog::getOpenFileName(this, "选择壁纸","./"
                                                  ,"Image(*.jpg *.png *.gif)");
    if(BgName.isNull())
        return;

    QFile::copy(BgName,QString("%1/background/back%2.png").arg(curDir).arg(++backGroundNum));
}
