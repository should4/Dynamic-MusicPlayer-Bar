#include "test.h"

Test::Test()
{
    QObject::connect(this,&Test::hello,this,&Test::helloSlots);

}

void Test::emitHello()
{
    emit hello();
}

void Test::helloSlots()
{
    emit hello2();
}
