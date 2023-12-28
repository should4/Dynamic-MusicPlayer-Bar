#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QDebug>
#include <QFileDialog>
#include <QDir>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>
#include <QUrl>

#include <QObject>


class MusicPlayer : public QObject
{

    Q_OBJECT
public:
    MusicPlayer();

    QList<QUrl> play_list;

    QAudioOutput* audioOutPut;

    QMediaPlayer* mediaPlayer;

    QList<QAudioDevice> outPut_device_list;//音乐输出设备
    int device_id=0;//记录当前输出设备在列表中的位置


    int current_row=0;//记录当前播放歌曲所对应的行数

    //设置音量
    void setVolume(float vol);
    //播放歌曲
    void play(int row);
    void choose_play(int row);//选择指定歌曲播放
    //播放下一首 上一首
    void play_last();
    void play_next();
    //设置当前歌曲的进度
    void setPosition(qint64 duration);

    //设置输出设备
    void setOutPutDevice(int index);
    void toNextOutPutDevice();
    void outPutDeviceRefresh();
    QString getOutPutDeviceDescription();



signals:
    void durationChanged(qint64 duration);
    void positionChanged(qint64 duration);

    //单曲播放结束
    void mediaEnd();

private slots:
    void durationChangedSlots(qint64 duration);
    void positionChangedSlots(qint64 duration);

    void mediaStatusChangedSlots(QMediaPlayer::MediaStatus status);
};

#endif // MUSICPLAYER_H
