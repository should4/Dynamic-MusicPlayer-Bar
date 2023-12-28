#ifndef MUSICPLAYWIDGET_H
#define MUSICPLAYWIDGET_H

#include <QWidget>

namespace Ui {
class MusicPlayWidget;
}

class MusicPlayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayWidget(QWidget *parent = nullptr);
    ~MusicPlayWidget();

private:
    Ui::MusicPlayWidget *ui;
};

#endif // MUSICPLAYWIDGET_H
