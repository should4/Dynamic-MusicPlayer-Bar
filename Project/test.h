#ifndef TEST_H
#define TEST_H

#include <QObject>

class Test : public QObject
{
    Q_OBJECT
public:
    Test();

    void emitHello();

signals:
    void hello();
    void hello2();

private slots:
    void helloSlots();
};

#endif // TEST_H
