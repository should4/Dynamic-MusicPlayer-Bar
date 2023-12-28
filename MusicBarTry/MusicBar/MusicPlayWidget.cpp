#include "MusicPlayWidget.h"
#include "ui_MusicPlayWidget.h"

MusicPlayWidget::MusicPlayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayWidget)
{
    ui->setupUi(this);
}

MusicPlayWidget::~MusicPlayWidget()
{
    delete ui;
}
