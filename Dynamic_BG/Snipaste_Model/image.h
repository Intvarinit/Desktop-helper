#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QKeyEvent>
#include <QRect>
#include <QMouseEvent>
#include <QAction>
#include <QFileDialog>
#include <QClipboard>
#include <QDateTime>

namespace Ui {
class Image;
}

class Image : public QWidget
{
    Q_OBJECT

public:
    explicit Image(QWidget *parent = nullptr);
    ~Image();

    void setPix(QPixmap pix);
    void mousePressEvent(QMouseEvent* evt);
    void mouseMoveEvent(QMouseEvent* evt);

    void contextMenuEvent(QContextMenuEvent* evt);

protected:
    virtual void keyPressEvent(QKeyEvent* evt);
    virtual void keyReleaseEvent(QKeyEvent* evt);
private:
    Ui::Image *ui;
    QPoint topLeft;
    QPixmap pix,display;
    QAction *Save,*Exit;
    QSize size;
};

#endif // IMAGE_H
