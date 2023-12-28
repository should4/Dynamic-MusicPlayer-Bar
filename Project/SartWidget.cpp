#include "SartWidget.h"
#include "ui_SartWidget.h"

#include "test.h"


SartWidget::SartWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SartWidget)
{
    ui->setupUi(this);

    //主窗口 去边框 + 可设计
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    //创建音乐索引对象
    musicInfo = new MusicInfo(MyFile::readAll());

    //创建音乐播放对象
    music_player = new MusicPlayer;
//    qDebug() << "list_size" << ui->listWidget_music_list->count();
    //初始化音乐列表
    muiscListInit();



    //初始化主窗口大小
    ui->frame_music->setGeometry(QRect(10, 20, 371, 210));
    ui->frame_music->setStyleSheet("background-color: rgb(230, 230, 230);border-radius:12px;");
    ui->frame->setStyleSheet("background-color:transparent;");

    //设置列表样式
    ui->listWidget_music_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //设置搜索栏模糊查找模型
    m_model = new QStandardItemModel(0, 1, this);
    m_completer = new QCompleter(m_model);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_search->setCompleter(m_completer);

    connect(m_completer, SIGNAL(activated(const QString&)), this, SLOT(onEmailChoosed(const QString&)));
    connect(ui->lineEdit_search, SIGNAL(textChanged(const QString&)), this, SLOT(onTextChanged(const QString&)));

    //音乐进度条的信号和槽
    connect(music_player,&MusicPlayer::durationChanged,this,&SartWidget::durationChangedSlots);
    connect(music_player,&MusicPlayer::positionChanged,this,&SartWidget::positionChangedSlots);

    //音乐播放完成后 的信号和槽
    connect(music_player,&MusicPlayer::mediaEnd,this,&SartWidget::mediaEndSlots);




}

SartWidget::~SartWidget()
{
    delete ui;
}





void SartWidget::executeAnimination_Unfold()
{
    QRect rect = this->geometry();
    int ax,ay,aw,ah;

    rect.getRect(&ax,&ay,&aw,&ah);
    /*  声明动画类，并将控制对象 this (this一定是继承自QObject的窗口部件)  以及属性名 "geometry" 传入构造函数  */
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
    /*  设置动画持续时长为 2 秒钟  */
    animation1->setDuration(220);
    /*  设置动画的起始状态 起始点 (1,2)  起始大小 (3,4)  */
    animation1->setStartValue(QRect(ax, ay, 584, 216));
    /*  设置动画的结束状态 结束点 (100,200)  结束大小 (300,400)  */
    animation1->setEndValue(QRect(ax, ay, 584, 320));
    /*  设置动画效果  */
    animation1->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo
    /*  开始执行动画 QAbstractAnimation::DeleteWhenStopped 动画结束后进行自清理(效果就好像智能指针里的自动delete animation) */
    //animation1->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation* animation2 = new QPropertyAnimation(this, "geometry");
    /*  设置动画持续时长为 2 秒钟  */
    animation2->setDuration(120);
    /*  设置动画的起始状态 起始点 (1,2)  起始大小 (3,4)  */
    animation2->setStartValue(QRect(ax, ay, 584, 320));
    /*  设置动画的结束状态 结束点 (100,200)  结束大小 (300,400)  */
    animation2->setEndValue(QRect(ax, ay, 584, 300));
    /*  设置动画效果  */
    animation2->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo
    /*  开始执行动画 QAbstractAnimation::DeleteWhenStopped 动画结束后进行自清理(效果就好像智能指针里的自动delete animation) */
    //animation2->start(QAbstractAnimation::DeleteWhenStopped);

    QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup(this);
    //pPosGroup->addPause(500);
    pPosGroup->addAnimation(animation1);
    pPosGroup->addAnimation(animation2);

    pPosGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void SartWidget::executeAnimination_Fold()
{
    QRect rect = this->geometry();
    int ax,ay,aw,ah;

    rect.getRect(&ax,&ay,&aw,&ah);
    qDebug() << ax << " "<< ay;

    /*  声明动画类，并将控制对象 this (this一定是继承自QObject的窗口部件)  以及属性名 "geometry" 传入构造函数  */
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
    connect(animation1,&QPropertyAnimation::finished,[=]
            {
                QPropertyAnimation* animation2 = new QPropertyAnimation(this, "geometry");
                /*  设置动画持续时长为 2 秒钟  */
                animation2->setDuration(120);
                /*  设置动画的起始状态 起始点 (1,2)  起始大小 (3,4)  */
                animation2->setStartValue(QRect(ax, ay, 584, 210));
                /*  设置动画的结束状态 结束点 (100,200)  结束大小 (300,400)  */
                animation2->setEndValue(QRect(ax, ay, 584, 216));
                /*  设置动画效果  */
                animation2->setEasingCurve(QEasingCurve::OutQuad);//InOutQuad  OutInExpo
                /*  开始执行动画 QAbstractAnimation::DeleteWhenStopped 动画结束后进行自清理(效果就好像智能指针里的自动delete animation) */
                animation2->start(QAbstractAnimation::DeleteWhenStopped);
            });
    /*  设置动画持续时长为 2 秒钟  */
    animation1->setDuration(220);
    /*  设置动画的起始状态 起始点 (1,2)  起始大小 (3,4)  */
    animation1->setStartValue(QRect(ax, ay, 584, 300));
    /*  设置动画的结束状态 结束点 (100,200)  结束大小 (300,400)  */
    animation1->setEndValue(QRect(ax, ay, 584, 210));
    /*  设置动画效果  */
    animation1->setEasingCurve(QEasingCurve::OutQuad);//InOutQuad  OutInExpo QEasingCurve::OutCubic QEasingCurve::OutQuad
    /*  开始执行动画 QAbstractAnimation::DeleteWhenStopped 动画结束后进行自清理(效果就好像智能指针里的自动delete animation) */
    animation1->start(QAbstractAnimation::DeleteWhenStopped);
}

void SartWidget::executeAnimination_Close()
{
    QRect rect = this->geometry();
    int ax,ay,aw,ah;

    rect.getRect(&ax,&ay,&aw,&ah);
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(600);
    animation1->setStartValue(QRect(ax, ay, aw, ah));
    animation1->setEndValue(QRect(ax, ay, aw, 0));
    animation1->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo

    QPropertyAnimation* animation2 = new QPropertyAnimation(this, "geometry");
    animation2->setDuration(120);
    animation2->setStartValue(QRect(ax, ay, 584, 320));
    animation2->setEndValue(QRect(ax, ay, 584, 300));
    animation2->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo

    QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup(this);
    //pPosGroup->addPause(500);
    pPosGroup->addAnimation(animation1);
    //pPosGroup->addAnimation(animation2);

    pPosGroup->start(QAbstractAnimation::DeleteWhenStopped);

    connect(pPosGroup,&QSequentialAnimationGroup::finished,this,[=]()
    {
        this->close();
    });
}

void SartWidget::executeAnimination_Gather()
{
    QRect rect = this->geometry();
    int ax,ay,aw,ah;

    rect.getRect(&ax,&ay,&aw,&ah);
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(600);
    animation1->setStartValue(QRect(ax, ay, aw, ah));
    animation1->setEndValue(QRect(ax, ay, aw/2, ah/2));
    animation1->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo

    QPropertyAnimation* animation2 = new QPropertyAnimation(this, "geometry");
    animation2->setDuration(120);
    animation2->setStartValue(QRect(ax, ay, 584, 320));
    animation2->setEndValue(QRect(ax, ay, 584, 300));
    animation2->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo

    QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup(this);
    //pPosGroup->addPause(500);
    pPosGroup->addAnimation(animation1);
    //pPosGroup->addAnimation(animation2);

    pPosGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void SartWidget::executeAnimination_Bounce(QPushButton* btn)
{
    QRect rect = btn->geometry();
    int ax,ay,aw,ah;
    int bounce_coef = 15;

    rect.getRect(&ax,&ay,&aw,&ah);
    QPropertyAnimation* animation1 = new QPropertyAnimation(btn, "geometry");
    animation1->setDuration(60);
    animation1->setStartValue(QRect(ax, ay, aw, ah));
    animation1->setEndValue(QRect(ax+aw/10, ay+ah/10, aw*9/10, ah*9/10));//(ax+aw/bounce_coef, ay+ah/bounce_coef, aw*(bounce_coef-1)/bounce_coef, ah*(bounce_coef-1)/bounce_coef)
    animation1->setEasingCurve(QEasingCurve::InOutCubic);//InOutQuad  OutInExpo QEasingCurve::InOutCubic QEasingCurve::OutCubic QEasingCurve::OutQuart

    QPropertyAnimation* animation2 = new QPropertyAnimation(btn, "geometry");
    animation2->setDuration(60);
    animation2->setStartValue(QRect(ax+aw/10, ay+ah/10, aw*9/10, ah*9/10));
    animation2->setEndValue(QRect(ax, ay, aw, ah));
    animation2->setEasingCurve(QEasingCurve::InOutCubic);//InOutQuad  OutInExpo

    QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup(this);

    pPosGroup->addAnimation(animation1);
    pPosGroup->addPause(2);
    pPosGroup->addAnimation(animation2);

    pPosGroup->start(QAbstractAnimation::DeleteWhenStopped);

}

void SartWidget::executeAnimination_Move(QFrame *frame)
{

}



void SartWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press)
    {
        move(event->globalPos() - mousePoint);
    }

}

void SartWidget::mousePressEvent(QMouseEvent *event)
{
    if( (event->button() == Qt::LeftButton) )
    {
        mouse_press = true;
        mousePoint = event->globalPos() - this->pos();
    }
}

void SartWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press = false;
}

void SartWidget::executeAnimination_Expand()
{
    QRect rect = this->geometry();
    int ax,ay,aw,ah;

    rect.getRect(&ax,&ay,&aw,&ah);
    QPropertyAnimation* animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(600);
    animation1->setStartValue(QRect(ax, ay, aw, ah));
    animation1->setEndValue(QRect(ax, ay, aw*2, ah*2));
    animation1->setEasingCurve(QEasingCurve::InOutCubic);//InOutQuad  OutInExpo QEasingCurve::InOutCubic QEasingCurve::OutCubic QEasingCurve::OutQuart

    QPropertyAnimation* animation2 = new QPropertyAnimation(this, "geometry");
    animation2->setDuration(120);
    animation2->setStartValue(QRect(ax, ay, 584, 320));
    animation2->setEndValue(QRect(ax, ay, 584, 300));
    animation2->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo

    QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup;
    //pPosGroup->addPause(500);
    pPosGroup->addAnimation(animation1);
    //pPosGroup->addAnimation(animation2);

    pPosGroup->start(QAbstractAnimation::DeleteWhenStopped);

}


void SartWidget::on_btn_fold_clicked()
{
    executeAnimination_Fold();
}


void SartWidget::on_btn_unfold_clicked()
{
    executeAnimination_Unfold();
}


void SartWidget::on_lineEdit_search_returnPressed()
{
    qDebug() << "here";
    QString search_text = ui->lineEdit_search->text();

    search_text = search_text.split(" - ")[0];

//    QVector<QString> singer_list = musicInfo->searchSinger(search_text);
//    QVector<Music> music_list = musicInfo->searchMusic(search_text);

    //选中第一个查找到的音乐 播放
    int index = musicInfo->searchMusic_index(search_text);

    //判断是否找到符合条件的音乐
    if(index == -1)
    {
        qDebug() << "没找到";
    }
    else
    {
        //播放对应的歌曲
        QListWidgetItem* item = ui->listWidget_music_list->item(index);
        QModelIndex mode = ui->listWidget_music_list->indexFromItem(item);
        emit on_listWidget_music_list_doubleClicked(mode);
    }
    qDebug() << index;

//    qDebug() << "______________________________";
//    if(singer_list.empty())
//    {
//        qDebug() << "singer_list empty";
//    }
//    qDebug() << singer_list;

//    if(music_list.empty())
//    {
//        qDebug() << "music_list empty";
//    }
//    for(auto music:music_list)
//    {
//        qDebug() << music.name << " " << music.singer_list;
//    }
//    qDebug() << "______________________________";
}


void SartWidget::on_btn_close_clicked()
{
    executeAnimination_Bounce(ui->btn_close);

    executeAnimination_Close();
}


void SartWidget::on_btn_expanding_clicked()
{
    executeAnimination_Expand();
}


void SartWidget::on_btn_gather_clicked()
{
    executeAnimination_Gather();
}


void SartWidget::on_btn_play_clicked()
{
    executeAnimination_Bounce(ui->btn_play);
    //判断当前歌曲播放状态
    if(btn_play == false)
    {
        music_player->play(0);
        QFile styleFile(":\\qss\\btn_pause_style.qss");
        if(styleFile.open(QIODevice::ReadOnly))
        {
            qDebug("open success");
            QString setStyleSheet(styleFile.readAll());
            //切换图片
            ui->btn_play->setStyleSheet(setStyleSheet);
            styleFile.close();
        }
    }
    else
    {
        music_player->play(0);
        //切换图片
        QFile styleFile(":\\qss\\btn_play_style.qss");
        if(styleFile.open(QIODevice::ReadOnly))
        {
            qDebug("open success");
            QString setStyleSheet(styleFile.readAll());
            //切换图片
            ui->btn_play->setStyleSheet(setStyleSheet);
            styleFile.close();
        }


    }

    btn_play = !btn_play;


}




void SartWidget::on_volumeSlider_sliderPressed()
{
    qDebug() << "pressed";
    QFile styleFile(":\\qss\\slider_pressed_style.qss");
    if(styleFile.open(QIODevice::ReadOnly))
    {
        qDebug("open success");
        QString setStyleSheet(styleFile.readAll());
        ui->volumeSlider->setStyleSheet(setStyleSheet);
        styleFile.close();
    }

    //ui->slider->setStyleSheet();
}

void SartWidget::on_volumeSlider_sliderReleased()
{
    qDebug() << "released";
    QFile styleFile(":\\qss\\slider_released_style.qss");
    if(styleFile.open(QIODevice::ReadOnly))
    {
        qDebug("open success");
        QString setStyleSheet(styleFile.readAll());
        ui->volumeSlider->setStyleSheet(setStyleSheet);
        styleFile.close();
    }

}

void SartWidget::on_volumeSlider_valueChanged(int value)
{
    //滑动音量条 调节音量
    qDebug() << value;

    music_player->setVolume(value*1.0/100);

}

void SartWidget::onEmailChoosed(const QString & email)
{
    ui->lineEdit_search->clear();    // 清除已存在的文本更新内容
    ui->lineEdit_search->setText(email);
}

void SartWidget::onTextChanged(const QString &str)
{
    QStringList strlist;
//    strlist << "@163.com" << "@qq.com" << "@gmail.com" << "@hotmail.com" << "@126.com";
    QString search_text = ui->lineEdit_search->text();

    QVector<Music> music_list = musicInfo->searchMusic(search_text);

    for(auto itr=music_list.begin();itr!=music_list.end();++itr)
    {
        QString name = itr->root_text.replace('&','/');
        strlist.append(name);
    }

    m_model->removeRows(0, m_model->rowCount());   // 先清除已经存在的数据，不然的话每次文本变更都会插入数据，最后出现重复数据

    qDebug() <<"here syrlist_size="<< strlist.size();
    for (int i = 0; i < strlist.size(); ++i)
    {
        qDebug() <<"here";
        m_model->insertRow(0);
        QString temp = str;
        m_model->setData(m_model->index(0, 0),strlist.at(i));
    }
}



void SartWidget::on_btn_minimize_clicked()
{
    QPushButton* btn = ui->btn_minimize;

    QRect rect = btn->geometry();
    int ax,ay,aw,ah;
    int bounce_coef = 15;

    rect.getRect(&ax,&ay,&aw,&ah);
    QPropertyAnimation* animation1 = new QPropertyAnimation(btn, "geometry");
    animation1->setDuration(60);
    animation1->setStartValue(QRect(ax, ay, aw, ah));
    animation1->setEndValue(QRect(ax+aw/10, ay+ah/10, aw*9/10, ah*9/10));//(ax+aw/bounce_coef, ay+ah/bounce_coef, aw*(bounce_coef-1)/bounce_coef, ah*(bounce_coef-1)/bounce_coef)
    animation1->setEasingCurve(QEasingCurve::InOutCubic);//InOutQuad  OutInExpo QEasingCurve::InOutCubic QEasingCurve::OutCubic QEasingCurve::OutQuart

    QPropertyAnimation* animation2 = new QPropertyAnimation(btn, "geometry");
    animation2->setDuration(60);
    animation2->setStartValue(QRect(ax+aw/10, ay+ah/10, aw*9/10, ah*9/10));
    animation2->setEndValue(QRect(ax, ay, aw, ah));
    animation2->setEasingCurve(QEasingCurve::InOutCubic);//InOutQuad  OutInExpo

    QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup(this);

    pPosGroup->addAnimation(animation1);
    pPosGroup->addPause(2);
    pPosGroup->addAnimation(animation2);

    pPosGroup->start(QAbstractAnimation::DeleteWhenStopped);

    connect(pPosGroup,&QPropertyAnimation::finished,this,[=]()
    {
        this->setWindowState(Qt::WindowMinimized);
    });


}


void SartWidget::on_btn_last_clicked()
{
    executeAnimination_Bounce(ui->btn_last);

    //播放上一首
    music_player->play_last();

    //更新播放栏
    musicCoverUpdate(music_player->current_row);

    QFile styleFile(":\\qss\\btn_pause_style.qss");
    if(styleFile.open(QIODevice::ReadOnly))
    {
        qDebug("open success");
        QString setStyleSheet(styleFile.readAll());
        //切换图片
        ui->btn_play->setStyleSheet(setStyleSheet);
        styleFile.close();
    }
    btn_play = true;
}


void SartWidget::on_btn_next_clicked()
{
    executeAnimination_Bounce(ui->btn_next);

    //播放下一首
    music_player->play_next();

    //更新播放栏
    musicCoverUpdate(music_player->current_row);

    QFile styleFile(":\\qss\\btn_pause_style.qss");
    if(styleFile.open(QIODevice::ReadOnly))
    {
        qDebug("open success");
        QString setStyleSheet(styleFile.readAll());
        //切换图片
        ui->btn_play->setStyleSheet(setStyleSheet);
        styleFile.close();
    }
    btn_play = true;
}


void SartWidget::on_btn_add_clicked()
{
    executeAnimination_Bounce(ui->btn_add);

    //如果 点击前为收起的状态 则展开搜索栏 且更换图像
    if(btn_add_flag == false)
    {
        QRect rect = ui->frame_music->geometry();
        QRect rect1 = ui->listWidget_music_list->geometry();
        int ax,ay,aw,ah;
        int ax1,ay1,aw1,ah1;//设计播放列表动画 高度 150->220 增加 70

        rect1.getRect(&ax1,&ay1,&aw1,&ah1);
        rect.getRect(&ax,&ay,&aw,&ah);

        QPropertyAnimation* animation1 = new QPropertyAnimation(ui->frame_music, "geometry");
        animation1->setDuration(250);
        animation1->setStartValue(QRect(ax, ay, aw, ah));
        animation1->setEndValue(QRect(ax, ay, aw, ah + 55));
        animation1->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo QEasingCurve::InOutCubic QEasingCurve::OutCubic QEasingCurve::OutQuart

        QPropertyAnimation* animation1_1 = new QPropertyAnimation(ui->listWidget_music_list, "geometry");
        animation1_1->setDuration(250);
        animation1_1->setStartValue(QRect(ax1, ay1, aw1, ah1));
        animation1_1->setEndValue(QRect(ax1, ay1, aw1, ah1 + 60));
        animation1_1->setEasingCurve(QEasingCurve::OutCubic);

        QPropertyAnimation* animation2 = new QPropertyAnimation(ui->frame_music, "geometry");
        animation2->setDuration(120);
        animation2->setStartValue(QRect(ax, ay, aw, ah + 55));
        animation2->setEndValue(QRect(ax, ay, aw, ah + 50));
        animation2->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo

        QPropertyAnimation* animation2_1 = new QPropertyAnimation(ui->listWidget_music_list, "geometry");
        animation2_1->setDuration(0);
        animation2_1->setStartValue(QRect(ax1, ay1, aw1, ah1));
        animation2_1->setEndValue(QRect(ax1, ay1, aw1, ah1 + 60));
        animation2_1->setEasingCurve(QEasingCurve::OutCubic);

        QParallelAnimationGroup *parallelGroup = new QParallelAnimationGroup;
        QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup;
        QSequentialAnimationGroup *pPosGroup1 = new QSequentialAnimationGroup;
        //pPosGroup->addPause(500);
        pPosGroup->addAnimation(animation1);
        pPosGroup->addAnimation(animation2);

        pPosGroup1->addAnimation(animation1_1);
        pPosGroup1->addAnimation(animation2_1);

        parallelGroup->addAnimation(pPosGroup);
        parallelGroup->addAnimation(pPosGroup1);

        parallelGroup->start(QAbstractAnimation::DeleteWhenStopped);
        //将 btn_add 当前图标改为 “-”
        ui->btn_add->setStyleSheet("border: none;image:url(':/image/fold.svg');");

        connect(pPosGroup,&QPropertyAnimation::finished,this,[=]()
        {

            btn_add_flag = !btn_add_flag;
        });
    }
    else
    {
        QRect rect = ui->frame_music->geometry();
        QRect rect1 = ui->listWidget_music_list->geometry();
        int ax,ay,aw,ah;
        int ax1,ay1,aw1,ah1;//设计播放列表动画 高度 150->220 增加 70

        rect1.getRect(&ax1,&ay1,&aw1,&ah1);
        rect.getRect(&ax,&ay,&aw,&ah);

        QPropertyAnimation* animation1 = new QPropertyAnimation(ui->frame_music, "geometry");
        animation1->setDuration(250);
        animation1->setStartValue(QRect(ax, ay, aw, ah));
        animation1->setEndValue(QRect(ax, ay, aw, ah - 55));
        animation1->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo QEasingCurve::InOutCubic QEasingCurve::OutCubic QEasingCurve::OutQuart

        QPropertyAnimation* animation1_1 = new QPropertyAnimation(ui->listWidget_music_list, "geometry");
        animation1_1->setDuration(250);
        animation1_1->setStartValue(QRect(ax1, ay1, aw1, ah1));
        animation1_1->setEndValue(QRect(ax1, ay1, aw1, ah1 - 60));
        animation1_1->setEasingCurve(QEasingCurve::OutCubic);


        QPropertyAnimation* animation2 = new QPropertyAnimation(ui->frame_music, "geometry");
        animation2->setDuration(120);
        animation2->setStartValue(QRect(ax, ay, aw, ah - 55));
        animation2->setEndValue(QRect(ax, ay, aw, ah - 50));
        animation2->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo

        QPropertyAnimation* animation2_1 = new QPropertyAnimation(ui->listWidget_music_list, "geometry");
        animation2_1->setDuration(0);
        animation2_1->setStartValue(QRect(ax1, ay1, aw1, ah1));
        animation2_1->setEndValue(QRect(ax1, ay1, aw1, ah1 - 60));
        animation2_1->setEasingCurve(QEasingCurve::OutCubic);


        QParallelAnimationGroup *parallelGroup = new QParallelAnimationGroup;
        QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup;
        QSequentialAnimationGroup *pPosGroup1 = new QSequentialAnimationGroup;
        //pPosGroup->addPause(500);
        pPosGroup->addAnimation(animation1);
        pPosGroup->addAnimation(animation2);

        pPosGroup1->addAnimation(animation1_1);
        pPosGroup1->addAnimation(animation2_1);

        parallelGroup->addAnimation(pPosGroup);
        parallelGroup->addAnimation(pPosGroup1);

        parallelGroup->start(QAbstractAnimation::DeleteWhenStopped);
        //将 btn_add 当前图标改为 “-”
        ui->btn_add->setStyleSheet("border: none;image:url(':/image/unfold.svg');");

        connect(pPosGroup,&QPropertyAnimation::finished,this,[=]()
        {

            btn_add_flag = !btn_add_flag;
        });
    }
}


void SartWidget::on_btn_list_clicked()
{
    executeAnimination_Bounce(ui->btn_list);

    //如果 点击前为收起的状态 则展开列表
    if(btn_list_flag == false)
    {
        QRect rect = ui->frame_music->geometry();
        QRect rect1 = ui->frame_functionGroup->geometry();
        int ax,ay,aw,ah;
        int ax1,ay1,aw1,ah1;


        rect.getRect(&ax,&ay,&aw,&ah);
        rect1.getRect(&ax1,&ay1,&aw1,&ah1);
        qDebug() << rect1;

        QPropertyAnimation* animation1 = new QPropertyAnimation(ui->frame_music, "geometry");
        animation1->setDuration(250);
        animation1->setStartValue(QRect(ax, ay, aw, ah));
        animation1->setEndValue(QRect(ax, ay, aw + 185, ah));
        animation1->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo QEasingCurve::InOutCubic QEasingCurve::OutCubic QEasingCurve::OutQuart

        QPropertyAnimation* animation1_1 = new QPropertyAnimation(ui->frame_functionGroup, "geometry");
        animation1_1->setDuration(250);
        animation1_1->setStartValue(QRect(ax1, ay1, aw1, ah1));
        animation1_1->setEndValue(QRect(ax1 + 185, ay1, aw1, ah1));
        animation1_1->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo QEasingCurve::InOutCubic QEasingCurve::OutCubic QEasingCurve::OutQuart

        QPropertyAnimation* animation2 = new QPropertyAnimation(ui->frame_music, "geometry");
        animation2->setDuration(120);
        animation2->setStartValue(QRect(ax, ay, aw + 185, ah));
        animation2->setEndValue(QRect(ax, ay, aw + 180, ah));
        animation2->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo

        QPropertyAnimation* animation2_1 = new QPropertyAnimation(ui->frame_functionGroup, "geometry");
        animation2_1->setDuration(120);
        animation2_1->setStartValue(QRect(ax1 + 185, ay1, aw1, ah1));
        animation2_1->setEndValue(QRect(ax1 + 180, ay1, aw1, ah1));
        animation2_1->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo

        QParallelAnimationGroup* parallelGroup = new QParallelAnimationGroup;
        QSequentialAnimationGroup *pPosGroup1 = new QSequentialAnimationGroup;
        QSequentialAnimationGroup *pPosGroup1_1 = new QSequentialAnimationGroup;
        //pPosGroup->addPause(500);
        pPosGroup1->addAnimation(animation1);
        pPosGroup1->addAnimation(animation2);

        pPosGroup1_1->addAnimation(animation1_1);
        pPosGroup1_1->addAnimation(animation2_1);

        parallelGroup->addAnimation(pPosGroup1);
        parallelGroup->addAnimation(pPosGroup1_1);

        parallelGroup->start(QAbstractAnimation::DeleteWhenStopped);

        btn_list_flag = !btn_list_flag;
    }
    else
    {
        QRect rect = ui->frame_music->geometry();
        QRect rect1 = ui->frame_functionGroup->geometry();
        int ax,ay,aw,ah;
        int ax1,ay1,aw1,ah1;

        rect.getRect(&ax,&ay,&aw,&ah);
        rect1.getRect(&ax1,&ay1,&aw1,&ah1);

        QPropertyAnimation* animation1 = new QPropertyAnimation(ui->frame_music, "geometry");
        animation1->setDuration(250);
        animation1->setStartValue(QRect(ax, ay, aw, ah));
        animation1->setEndValue(QRect(ax, ay, aw - 185, ah));
        animation1->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo QEasingCurve::InOutCubic QEasingCurve::OutCubic QEasingCurve::OutQuart

        QPropertyAnimation* animation1_1 = new QPropertyAnimation(ui->frame_functionGroup, "geometry");
        animation1_1->setDuration(250);
        animation1_1->setStartValue(QRect(ax1, ay1, aw1, ah1));
        animation1_1->setEndValue(QRect(ax1 - 185, ay1, aw1, ah1));
        animation1_1->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo QEasingCurve::InOutCubic QEasingCurve::OutCubic QEasingCurve::OutQuart

        QPropertyAnimation* animation2 = new QPropertyAnimation(ui->frame_music, "geometry");
        animation2->setDuration(120);
        animation2->setStartValue(QRect(ax, ay, aw - 185, ah));
        animation2->setEndValue(QRect(ax, ay, aw - 180, ah));
        animation2->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo

        QPropertyAnimation* animation2_1 = new QPropertyAnimation(ui->frame_functionGroup, "geometry");
        animation2_1->setDuration(120);
        animation2_1->setStartValue(QRect(ax1 - 185, ay1, aw1, ah1));
        animation2_1->setEndValue(QRect(ax1 - 180, ay1, aw1, ah1));
        animation2_1->setEasingCurve(QEasingCurve::OutCubic);//InOutQuad  OutInExpo

        //一个并行动画 连个串行动画
        QParallelAnimationGroup* parallelGroup = new QParallelAnimationGroup;
        QSequentialAnimationGroup *pPosGroup1 = new QSequentialAnimationGroup;
        QSequentialAnimationGroup *pPosGroup1_1 = new QSequentialAnimationGroup;
        //pPosGroup->addPause(500);
        pPosGroup1->addAnimation(animation1);
        pPosGroup1->addAnimation(animation2);

        pPosGroup1_1->addAnimation(animation1_1);
        pPosGroup1_1->addAnimation(animation2_1);

        parallelGroup->addAnimation(pPosGroup1);
        parallelGroup->addAnimation(pPosGroup1_1);

        parallelGroup->start(QAbstractAnimation::DeleteWhenStopped);

        btn_list_flag = !btn_list_flag;

    }
}


void SartWidget::on_btn_search_clicked()
{
    executeAnimination_Bounce(ui->btn_search);

    on_lineEdit_search_returnPressed();
}




void SartWidget::on_listWidget_music_list_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    qDebug() << index;

    //更新播放蓝页面
    musicCoverUpdate(row);


//    QString name = item->text();
//    QString photo_path = QDir::currentPath() + "/cover/" + name + ".jpg";
//    QString style_sheet = QString("QLabel{border-radius: 14px;border-image: url(%1);}").arg(photo_path);//"D:\Qt_practice\build-MusicBar-Desktop_Qt_6_3_2_MinGW_64_bit-Debug\cover\Myself - Post Malone.jpg"
//    ui->label_image->setStyleSheet(style_sheet);
//    qDebug() << style_sheet;

    //设置播放状态
    //判断当前是否处于播放状态
    //判断在列表中点击的是否为当前播放音乐
    if(row == music_player->current_row)
    {
        on_btn_play_clicked();
    }
    else
    {
        //如果点击的不为当前播放音乐，且当前状态为停止时
        if(btn_play == false)
        {
            QFile styleFile(":\\qss\\btn_pause_style.qss");
            if(styleFile.open(QIODevice::ReadOnly))
            {
                qDebug("open success");
                QString setStyleSheet(styleFile.readAll());
                //切换图片
                ui->btn_play->setStyleSheet(setStyleSheet);
                styleFile.close();
            }
            btn_play = true;
        }
        //qDebug() << "here";
        music_player->choose_play(row);
    }
}

void SartWidget::durationChangedSlots(qint64 duration)
{
    //qDebug() << "duration=" << duration;
    int reaction_time = 500;
    ui->label_total->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60));
    ui->prograssSlider->setRange(0,duration-reaction_time);//设置间隔
}

void SartWidget::positionChangedSlots(qint64 duration)
{
    ui->label_current->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));
    //如果进度条未被拖动
    if(!is_pressed)
    {
        ui->prograssSlider->setValue(duration);
    }
}

void SartWidget::mediaEndSlots()
{
    music_player->play_next();

    musicCoverUpdate(music_player->current_row);
}

//void SartWidget::statusChangedSlots(QMediaPlayer::PlaybackState status)
//{
//    switch (status) {
//    case QMediaPlayer::PlaybackState::PausedState:

//        break;
//    default:
//        break;
//    }
//}


void SartWidget::on_prograssSlider_sliderPressed()
{
    //获取当前playCourseSlider是否被press
    is_pressed = true;
}


void SartWidget::on_prograssSlider_sliderReleased()
{
    qint64 duration = ui->prograssSlider->value();
    music_player->setPosition(duration);

    is_pressed = false;
}

void SartWidget::musicCoverUpdate(int row)
{
    QListWidgetItem* item = ui->listWidget_music_list->item(row);

    //将点击的音乐对应信息显示在左侧音乐栏上
    QSize size = ui->label_image->size();
    QPixmap pix = item->icon().pixmap(size);
    pix = round(pix,14);//圆角处理
    ui->label_image->setPixmap(pix);

    //将音乐 及歌手名显示在左侧音乐栏
    QStringList list = item->text().split(" - ");
    QString song = list[0];
    QString singers = list[1];
    singers.replace('&','/');

    ui->label_song->setText(song);
    ui->label_singers->setText(singers);
}

void SartWidget::muiscListInit()
{
    //首先 music_list 中的内容读取到 listWidget 中
    ui->listWidget_music_list->clear();
    QList<Music> music_list = musicInfo->music_list;
    for(auto itr=music_list.begin();itr!=music_list.end();++itr)
    {
        QString name = itr->root_text;
        QString photo_path = QDir::currentPath() + "/cover/" + name + ".jpg";
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(name);
        item->setIcon(QIcon(photo_path));

        ui->listWidget_music_list->addItem(item);
    }



    for(int row=0;row<ui->listWidget_music_list->count();++row)
    {
        QString path = QDir::currentPath();

        QString file = "/music/" + ui->listWidget_music_list->item(row)->text() + ".mp3";
        qDebug() << path + file;
        music_player->play_list.append(QUrl::fromLocalFile(path + file));
    }
}

QPixmap SartWidget::round(const QPixmap &src, int radius)
{
    if (src.isNull())
    {
        return QPixmap();
    }

    QBitmap mask(src.size());
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(mask.rect(), Qt::white);
    painter.setBrush(Qt::black);
    painter.drawRoundedRect(mask.rect(), radius, radius);
    QPixmap image = src.copy();
    image.setMask(mask);
    return image;
}






void SartWidget::on_btn_switch_audio_clicked()
{
    executeAnimination_Bounce(ui->btn_switch_audio);

    music_player->toNextOutPutDevice();

    QString description = music_player->getOutPutDeviceDescription();

    if(description.contains("耳机"))
    {
        ui->btn_switch_audio->setStyleSheet("border-radius:4px;image:url(:/image/switch_earphone3.svg);");
    }

    if(description.contains("扬声器"))
    {
        ui->btn_switch_audio->setStyleSheet("border-radius:4px;image:url(:/image/switch_audio_off.svg);");
    }
}

