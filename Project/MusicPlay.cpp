#include "MusicPlay.h"
#include "ui_MusicPlay.h"

MusicPlay::MusicPlay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlay)
{
    ui->setupUi(this);
}

MusicPlay::~MusicPlay()
{
    delete ui;
}
