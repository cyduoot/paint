#ifndef PAINT_H
#define PAINT_H

#include <QMainWindow>
#include <QImage>
#include <QFileDialog>
#include <QTimer>
#include <QPoint>
#include <QMouseEvent>
#include <QCursor>
#include <QPixmap>
#include <QMessageBox>
#include <QInputDialog>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "dialog.h"

using namespace cv;

namespace Ui {
class Paint;
}

class Paint : public QMainWindow
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = 0);
    ~Paint();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_Pen_triggered();


    void on_actionSave_triggered();

    void on_Rec_triggered();

    void on_Ellipse_triggered();

    void on_Eraser_triggered();

    void on_actionLine_Size_triggered();

    void on_Line_triggered();

    void on_actionColor_triggered();

    void on_Select_triggered();

    void on_actionBackgroud_color_triggered();

    void on_Bucket_triggered();

private:
    Ui::Paint *ui;
    cv::Mat image;
    bool pen, rec, elp, ers, lin, slt, slp, slm, bkt, lp;
    bool leftbtn;
    bool haveimg;
    QCursor pencur;
    void displayMat(Mat image);
    void refresh_all();
    void changecolorl(info);
    void changecolorr(info);
    cv::Point lastp;
    int line_size;
    Vec3b pixel, rpixel, lpixel;

};

#endif // PAINT_H
