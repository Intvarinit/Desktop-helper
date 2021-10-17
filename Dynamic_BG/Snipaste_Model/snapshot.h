#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "image.h"

#include <QGuiApplication>
#include <QScreen>
#include <QPen>
#include <QLabel>

namespace Ui {
class Snapshot;
}

class Snapshot : public QWidget
{
    Q_OBJECT

public:
    explicit Snapshot(QWidget *parent = nullptr);
    ~Snapshot();
    void mousePressEvent(QMouseEvent* evt);
    void mouseMoveEvent(QMouseEvent* evt);
    void mouseReleaseEvent(QMouseEvent* evt);

    void Snap();
    void paintEvent(QPaintEvent* );
signals:
	void finish();
protected:
    virtual void keyPressEvent(QKeyEvent* evt);

private:
//    QRect* rect;
    QPixmap pix;
    Ui::Snapshot *ui;

    //参考线部分
//    QWidget* refer;
    QRect* refer_pos;
    bool show_refer;
    QPen pen;
};

#endif // SNAPSHOT_H

