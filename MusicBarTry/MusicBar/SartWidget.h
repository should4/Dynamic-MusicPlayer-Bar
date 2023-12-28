#ifndef SARTWIDGET_H
#define SARTWIDGET_H

#include <QWidget>

#include <QCompleter>//自动补全

#include <QPropertyAnimation>//单个动画设计类
#include <QSequentialAnimationGroup>//串行动画设计类
#include <QParallelAnimationGroup>//并行动画设计类

#include <QPushButton>
#include <QFrame>
#include <QListWidgetItem>

//重写鼠标事件
#include <QMouseEvent>

//SVG 格式图片加载
#include "qpainter.h"



#include "MyFile.h"
#include "MusicInfo.h"
#include "MusicPlayer.h"

//模糊查找
#include <QStandardItemModel>
#include <QCompleter>

QT_BEGIN_NAMESPACE
namespace Ui { class SartWidget; }
QT_END_NAMESPACE

class SartWidget : public QWidget
{
    Q_OBJECT

public:
    SartWidget(QWidget *parent = nullptr);
    ~SartWidget();

private slots:


    void on_btn_fold_clicked();

    void on_btn_unfold_clicked();

    void on_lineEdit_search_returnPressed();

    void on_btn_close_clicked();

    void on_btn_expanding_clicked();

    void on_btn_gather_clicked();

    //按钮
    void on_btn_play_clicked();
    void on_btn_last_clicked();
    void on_btn_next_clicked();
    void on_btn_add_clicked();



    void on_volumeSlider_sliderPressed();

    void on_volumeSlider_sliderReleased();

    void on_volumeSlider_valueChanged(int value);

    //模糊查找
    void onEmailChoosed(const QString&);
    void onTextChanged(const QString&);



    void on_btn_minimize_clicked();



    void on_btn_list_clicked();

    void on_btn_search_clicked();

    //双击音乐列表中的元素 播放音乐列表
    void on_listWidget_music_list_doubleClicked(const QModelIndex &index);

    //音乐进度调节的信号和槽
    void durationChangedSlots(qint64 duration);
    void positionChangedSlots(qint64 duration);
//    //播放状态改变
//    void statusChangedSlots(QMediaPlayer::PlaybackState status);

    //单曲播放完成的槽函数
    void mediaEndSlots();

    void on_prograssSlider_sliderPressed();

    void on_prograssSlider_sliderReleased();



    void on_btn_switch_audio_clicked();

private:
    Ui::SartWidget *ui;

    //更新音乐栏
    void musicCoverUpdate(int row);

    //初始化音乐列表
    void muiscListInit();


     QCompleter *completer1;
     QCompleter *completer2;

     //动画
     void executeAnimination_Unfold();
     void executeAnimination_Fold();
     void executeAnimination_Close();
     void executeAnimination_Expand();
     void executeAnimination_Gather();
     void executeAnimination_Bounce(QPushButton* btn);
     void executeAnimination_Move(QFrame* frame);


     //音乐索引
     MusicInfo* musicInfo;

     //音乐播放
    MusicPlayer* music_player;

     QStandardItemModel* m_model;
     QCompleter* m_completer;

     //重写鼠标事件
     bool mouse_press;
     QPoint mousePoint;

     //记录 btn_add 和 btn_list 的状态 来设置对应属性及动画
     bool btn_add_flag=false; // true 表示搜索栏已展开   false 表示搜索栏收起
     bool btn_list_flag=false;// true 表示播放列表已展开 false 表示播放列表收起
     //记录 btn_play 的状态 来设置对应图片
     bool btn_play=false;

     //记录进度条是否被拖动
     bool is_pressed=false;

     //圆角转换
     QPixmap round(const QPixmap &src, int radius);


protected:
   void mouseMoveEvent(QMouseEvent *event);
   void mousePressEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);



};
#endif // SARTWIDGET_H
