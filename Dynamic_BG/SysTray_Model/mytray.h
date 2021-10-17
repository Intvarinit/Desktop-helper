#ifndef MYTRAY_H
#define MYTRAY_H

#include <QSystemTrayIcon>
#include <QMenu>

class MyTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit MyTray(QObject* parent = nullptr);
    ~MyTray();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);       //接收对托盘的点击事件
    void createActions();       //创建托盘菜单
signals:
    void showMain();
    void quit();
    void ScrCut();
    void setBg();
public slots:
private:
    QMenu* menu;

    QAction* action_show;
    QAction* action_quit;
    QAction* action_help;
    QAction* action_about;
    QAction* action_bg;
    QAction* action_scrn;
};

#endif // MYTRAY_H
