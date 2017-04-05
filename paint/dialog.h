#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class Dialog;
}

struct info{
    bool ok;
    int r, g, b;
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void showColor();
    void send()
    {
        emit rgb(d_color);
    }

signals:
    void rgb(const info &col);

private:
    Ui::Dialog *ui;
    info d_color;
};

#endif // DIALOG_H
