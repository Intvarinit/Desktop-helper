#ifndef WIDGET_H
#define WIDGET_H

#include <QPoint>
#include <QMouseEvent>
#include <QWidget>
#include <QTimer>
#include <QSettings>
#include <QFileDialog>
#include <windows.h>

#include "Snipaste_Model/snapshot.h"
#include "SysTray_Model/mytray.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void mouseMoveEvent(QMouseEvent *evt);      //控制窗口移动
    void mousePressEvent(QMouseEvent* evt);     //点击事件
//    void keyPressEvent(QKeyEvent *evt);
    void roleCut();
private slots:
    void on_Set_clicked();
    void on_Close_clicked();
    void on_Minimum_clicked();

    void setBG(QString path);
    void on_BG_clicked();
    void on_Snap_clicked();

    void on_Save_BG_clicked();

signals:

private:
    Ui::Widget *ui;
    QPoint moveleftTop;
    QTimer timer;       //动画切换的定时器
    bool expend;
    Snapshot snap;
    MyTray* tray;
    bool hided;

    int backGroundNum;        //壁纸的张数
    QString curDir;
};

#endif // WIDGET_H
