#include "paint.h"
#include "ui_paint.h"
#include<QDebug>


Paint::Paint(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Paint)
{
    ui->setupUi(this);
    refresh_all();
    haveimg = false;
    line_size = 1;
    lpixel[0] = 0;
    lpixel[1] = 0;
    lpixel[2] = 0;
    rpixel[0] = 255;
    rpixel[1] = 255;
    rpixel[2] = 255;
}

Paint::~Paint()
{
    delete ui;
}

void Paint::refresh_all()
{
    pen = false;
    rec = false;
    elp = false;
    ers = false;
    lin = false;
    bkt = false;
    //slt = false;
    //slm = false;
}

void Paint::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),
                                    ".",tr("Image Files (*.png *.jpg *.bmp)"));
        image = cv::imread(fileName.toLatin1().data());

        refresh_all();
        displayMat(image);
}

void Paint::displayMat(Mat image)
{
    Mat rgb;
    QImage img;
    if(image.channels()==3)
    {
        //cvt Mat BGR 2 QImage RGB
        cvtColor(image,rgb,CV_BGR2RGB);
        img =QImage((const unsigned char*)(rgb.data),
                    rgb.cols,rgb.rows,
                    rgb.cols*rgb.channels(),
                    QImage::Format_RGB888);
    }
    else
    {
        img =QImage((const unsigned char*)(image.data),
                    image.cols,image.rows,
                    image.cols*image.channels(),
                    QImage::Format_RGB888);
    }

    ui->imagelabel->setPixmap(QPixmap::fromImage(img));
    ui->imagelabel->resize(ui->imagelabel->pixmap()->size());
    haveimg = true;
}

void Paint::on_actionNew_triggered()
{
    cv::Mat M(500, 500, CV_8UC3, Scalar(255, 255, 255));
    image = M;
    refresh_all();
    displayMat(image);
}

void Paint::mousePressEvent(QMouseEvent *event)
{
    if (event -> button() == Qt::LeftButton)
    {
        pixel = lpixel;
        leftbtn = true;
    }
    else
    {
        pixel = rpixel;
        leftbtn = false;
    }
    if (haveimg)
    {
        if (pen)
        {
                lastp.x = event->x();
                lastp.y = event->y() - 57;
                circle(image, lastp, line_size/2, pixel, -1);
                displayMat(image);
        }
        if (rec)
        {

                lastp.x = event->x();
                lastp.y = event->y() - 57;
        }
        if (elp)
        {
                lastp.x = event->x();
                lastp.y = event->y() - 57;
        }
        if (ers)
        {
            if(event->button() == Qt::LeftButton){
                lastp.x = event->x();
                lastp.y = event->y() - 57;
                circle(image, lastp, line_size/2, rpixel, -1);
                displayMat(image);
            }

        }
        if (lin)
        {

                lastp.x = event->x();
                lastp.y = event->y() - 57;
        }
       /* if (slt)
        {
            if(event->button() == Qt::LeftButton){

                lastp.x = event->x();
                lastp.y = event->y() - 57;
            }
        }*/
        if (bkt)
        {
            lastp.x = event->x();
            lastp.y = event->y();
            if (event->button() == Qt::LeftButton)
                floodFill(image, lastp, lpixel);
            else
                floodFill(image, lastp, rpixel);
            displayMat(image);
        }
    }
}

void Paint::mouseMoveEvent(QMouseEvent *event)
{
    if (haveimg)
    {
        if (pen)
        {
            cv::Point p;
            p.x = event->x();
            p.y = event->y() - 57;
            line(image, lastp, p, pixel, line_size);
            lastp = p;
            displayMat(image);
        }
        if (rec)
        {
            cv::Mat preimage;
            image.copyTo(preimage);
            cv::Point p;
            p.x = event->x();
            p.y = event->y() - 57;
            rectangle(preimage, lastp, p, pixel, line_size);
            displayMat(preimage);
            preimage.release();
        }
        if (elp)
        {
            cv::Mat preimage;
            image.copyTo(preimage);
            cv::Point p;
            p.x = event->x();
            p.y = event->y() - 57;
            if (!(abs(p.x - lastp.x) == 0 || abs(p.y - lastp.y) == 0)){
                ellipse(preimage, RotatedRect(Point2f(lastp.x, lastp.y), Point2f(lastp.x, p.y), Point2f(p.x, p.y)), pixel, line_size);
            }
            displayMat(preimage);
            preimage.release();
        }
        if (ers)
        {
            if(leftbtn){
                cv::Point p;
                p.x = event->x();
                p.y = event->y() - 57;
                line(image, lastp, p, rpixel, line_size);
                lastp = p;
                displayMat(image);
            }
        }
        if (lin)
        {
            cv::Mat preimage;
            image.copyTo(preimage);
            cv::Point p;
            p.x = event->x();
            p.y = event->y() - 57;
            line(preimage, lastp, p, pixel, line_size);
            displayMat(preimage);
            preimage.release();
        }
        /*if (slt)
        {
            cv::Mat preimage;
            image.copyTo(preimage);
            cv::Point p;
            p.x = event->x();
            p.y = event->y() - 57;
            vrectangle(preimage, lastp, p, pixel, line_size);
            displayMat(preimage);
            preimage.release();
        }*/

     }
}

void Paint::mouseReleaseEvent(QMouseEvent *event)
{
   if (haveimg)
   {
       if (rec)
       {
           cv::Point p;
           p.x = event->x();
           p.y = event->y() - 57;
           rectangle(image, lastp, p, pixel, line_size);
           displayMat(image);
       }
       if (elp)
       {
           cv::Point p;
           p.x = event->x();
           p.y = event->y() - 57;
           ellipse(image, RotatedRect(Point2f(lastp.x, lastp.y), Point2f(lastp.x, p.y), Point2f(p.x, p.y)), pixel, line_size);
           displayMat(image);
       }
       if (lin)
       {
           cv::Point p;
           p.x = event->x();
           p.y = event->y() - 57;
           line(image, lastp, p, pixel, line_size);
           displayMat(image);
       }
      /* if (slt)
       {
           cv::Point p;
           p.x = event->x();
           p.y = event->y() - 57;
           vrectangle(image, lastp, p, pixel, line_size);
           displayMat(image);
           slt = false;
           slm = true;
       }*/

   }
}
void Paint::on_actionSave_triggered()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,
        tr("Save Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!fileName.isNull())
    {
          imwrite( fileName.toLatin1().data(), image );
    }
}

void Paint::on_Pen_triggered()
{
    refresh_all();
    pen = !pen;
    if (pen)
    {
        setCursor(Qt::CrossCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void Paint::on_Rec_triggered()
{
    refresh_all();
    rec = !rec;
    if (rec)
    {
        setCursor(Qt::CrossCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void Paint::on_Ellipse_triggered()
{
    refresh_all();
    elp = !elp;
    if (elp)
    {
        setCursor(Qt::CrossCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void Paint::on_Eraser_triggered()
{
    refresh_all();
    ers = !ers;
    if (ers)
    {
        setCursor(Qt::CrossCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void Paint::on_actionLine_Size_triggered()
{
    bool ok = false;
    QString text = QInputDialog::getText(NULL,
                        tr( "Line size" ),
                        tr( "Please enter the line size(1-99)" ),
                        QLineEdit::Normal, QString::null, &ok);
      if ( ok && !text.isEmpty() )
      {
        int temp;
        bool succ;
        temp = 0;
        temp = text.toInt(&succ);
        if (succ)
        {
            line_size = temp;
        }
        else
        {
            QMessageBox::warning(NULL, "ERROR", "Illegal input!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
      }
}

void Paint::on_Line_triggered()
{
    refresh_all();
    lin = !lin;
    if (lin)
    {
        setCursor(Qt::CrossCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void Paint::on_actionColor_triggered()
{
    /*bool ok = false;
    QString text = QInputDialog::getText(NULL,
                        tr( "Color" ),
                        tr( "Please enter the color you want(in the form of \"R(0-255) G(0-255) B(0-255) \")" ),
                        QLineEdit::Normal, QString::null, &ok);
      if ( ok && !text.isEmpty() )
      {
        QStringList Rgb;
        Rgb = text.split(" ");
        int tp[3];
        bool f0, f;
        f = true;
        tp[0] = tp[1] = tp[2] = -1;
        tp[2] = Rgb.at(0).toInt(&f0);
        f = f && f0;
        tp[1] = Rgb.at(1).toInt(&f0);
        f = f && f0;
        tp[0] = Rgb.at(2).toInt(&f0);
        f = f && f0;
        for (int i = 0; i < 3; i++)
            if (tp[i] < 0 || tp[i] > 255)
            {
                f = false;
                break;
            }
        if (f)
        {
            lpixel[0] = tp[0];
            lpixel[1] = tp[1];
            lpixel[2] = tp[2];
            Mat col(10, 10, CV_8UC3, lpixel);
            const char *pstrWindowsTitle = "Color preview";
            cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);

            imshow(pstrWindowsTitle, col);
            cvWaitKey();

            cvDestroyWindow(pstrWindowsTitle);
            col.release();
        }
        else
        {
            QMessageBox::warning(NULL, "ERROR", "Illegal input!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
      }
      */

    Dialog *d;
    d = new Dialog;
    connect(d, &Dialog::rgb, this, &Paint::changecolorl);
    d->exec();
    delete d;


}

void Paint::changecolorl(info col)
{
    if (col.ok){
        lpixel[0] = col.b;
        lpixel[1] = col.g;
        lpixel[2] = col.r;
    }
}

void Paint::on_Select_triggered()
{
    /*refresh_all();
    slt = !slt;
    if (slt)
    {
        setCursor(Qt::CrossCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }*/
}

void Paint::on_actionBackgroud_color_triggered()
{
    /*bool ok = false;
    QString text = QInputDialog::getText(NULL,
                        tr( "Color" ),
                        tr( "Please enter the color you want(in the form of \"R(0-255) G(0-255) B(0-255) \")" ),
                        QLineEdit::Normal, QString::null, &ok);
      if ( ok && !text.isEmpty() )
      {
        QStringList Rgb;
        Rgb = text.split(" ");
        int tp[3];
        bool f0, f;
        f = true;
        tp[0] = tp[1] = tp[2] = -1;
        tp[2] = Rgb.at(0).toInt(&f0);
        f = f && f0;
        tp[1] = Rgb.at(1).toInt(&f0);
        f = f && f0;
        tp[0] = Rgb.at(2).toInt(&f0);
        f = f && f0;
        for (int i = 0; i < 3; i++)
            if (tp[i] < 0 || tp[i] > 255)
            {
                f = false;
                break;
            }
        if (f)
        {
            rpixel[0] = tp[0];
            rpixel[1] = tp[1];
            rpixel[2] = tp[2];
            Mat col(10, 10, CV_8UC3, rpixel);
            const char *pstrWindowsTitle = "Color preview";
            cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);

            imshow(pstrWindowsTitle, col);
            cvWaitKey();

            cvDestroyWindow(pstrWindowsTitle);
            col.release();
        }
        else
        {
            QMessageBox::warning(NULL, "ERROR", "Illegal input!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
      }*/
    Dialog *d;
    d = new Dialog;
    connect(d, &Dialog::rgb, this, &Paint::changecolorr);
    d->exec();
    delete d;
}

void Paint::changecolorr(info col)
{
    if (col.ok){
        rpixel[0] = col.b;
        rpixel[1] = col.g;
        rpixel[2] = col.r;
    }
}

void Paint::on_Bucket_triggered()
{
    refresh_all();
    bkt = !bkt;
    if (bkt)
    {
        setCursor(Qt::CrossCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}
