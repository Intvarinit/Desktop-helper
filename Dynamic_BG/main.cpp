#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);         //防止系统托盘化时被关闭
    Widget w;
    w.show();

    return a.exec();
}


/*setBg轮播还没开始做，QSetting设置无法写回
*/
