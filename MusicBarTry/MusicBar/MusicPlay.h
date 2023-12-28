#ifndef MUSICPLAY_H
#define MUSICPLAY_H

#include <QWidget>

namespace Ui {
class MusicPlay;
}

class MusicPlay : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlay(QWidget *parent = nullptr);
    ~MusicPlay();

private:
    Ui::MusicPlay *ui;
};

#endif // MUSICPLAY_H
