#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

using namespace cv;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->red, &QLineEdit::textChanged, this, &Dialog::showColor);
    connect(ui->green, &QLineEdit::textChanged, this, &Dialog::showColor);
    connect(ui->blue, &QLineEdit::textChanged, this, &Dialog::showColor);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Dialog::send);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showColor()
{
    int r, g, b;
    bool ok, t;
    ok = true;
    r = ui->red->text().toInt(&t);
    ok = ok && t;
    g = ui->green->text().toInt(&t);
    ok = ok && t;
    b = ui->blue->text().toInt(&t);
    ok = ok && t;
    if (!ui->red->text().isEmpty() && ! ui->green->text().isEmpty() && !ui->blue->text().isEmpty())
        if (!ok || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255){
            QMessageBox::warning(NULL, "ERROR", "Illegal input!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }
    Mat rgb(50, 50, CV_8UC3, Scalar(r, g, b));
    QImage img;

        img =QImage((const unsigned char*)(rgb.data),
                    rgb.cols,rgb.rows,
                    rgb.cols*rgb.channels(),
                    QImage::Format_RGB888);

    ui->color->setPixmap(QPixmap::fromImage(img));
    ui->color->resize(ui->color->pixmap()->size());
    d_color.ok = ok;
    d_color.r = r;
    d_color.g = g;
    d_color.b = b;
}
