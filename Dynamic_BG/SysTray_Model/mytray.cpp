#include "mytray.h"

//#include <QDebug>
#include <QMessageBox>

MyTray::MyTray(QObject* parent)
{
    setIcon(QIcon(":/res/menu/check_box_normal.png"));

    this->setToolTip(QString("I am Tray,Click me to Cut Screen!"));

    menu = new QMenu();         //创建菜单

//    menu->addAction(say);

    connect(this,&QSystemTrayIcon::activated,this,&MyTray::iconActivated);      //鼠标点击事件绑定
//    connect(this,&QSystemTrayIcon::messageClicked,this,[=](){           //点击了showMessage窗口的事件绑定
//        qDebug() << "You Click the Message";
//    });

    createActions();        //创建Action并绑定事件

    this->setContextMenu(menu);     //设置托盘菜单
}

MyTray::~MyTray()
{
    delete menu;
}

void MyTray::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
        switch (reason) {
        case QSystemTrayIcon::Trigger:
        {
            emit ScrCut();
//            qDebug() << "ScrCut Ending!";
            //showMessage("click","you click systemTray");
            break;
        }
//        case QSystemTrayIcon::DoubleClick:
//        {
//            qDebug() << "double click";
//            break;
//        }
        default:
            break;
        }
}

void MyTray::createActions()
{
    //创建托盘项
    action_show = new QAction(this);
    connect(action_show,&QAction::triggered,[=](){
        emit showMain();
    });
    action_quit = new QAction(this);
    connect(action_quit,&QAction::triggered,[=](){
        emit quit();
    });
    action_bg = new QAction(this);
    connect(action_bg,&QAction::triggered,[=](){
        emit setBg();
    });
    action_help = new QAction(this);
    connect(action_help,&QAction::triggered,[=](){
        QMessageBox::information(nullptr,QString("Teach you to use it"),QString("you can Cut Screen after click tray"));
    });
    action_about = new QAction(this);
    connect(action_about,&QAction::triggered,[=](){
        QMessageBox::about(nullptr,QString("About the demo"),QString("Nothing"));
    });
    action_scrn = new QAction(this);
    connect(action_scrn,&QAction::triggered,[=](){
        emit ScrCut();
    });

    action_show->setText("Show");
    action_quit->setText("Quit");
    action_bg->setText("SetBackground");
    action_help->setText("Help");
    action_about->setText("About");
    action_scrn->setText("ScreenCut");

    menu->addAction(action_show);
    menu->addAction(action_bg);
    menu->addAction(action_scrn);
    menu->addSeparator();
    menu->addAction(action_help);
    menu->addAction(action_about);
    menu->addSeparator();
    menu->addAction(action_quit);
}

