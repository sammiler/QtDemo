#include "myclass.h"

int main()
{
    MyClass * myinstance = new MyClass;
    const QMetaObject * metaObject = myinstance->metaObject();
    auto v = metaObject->classInfo(0).value();
    QObject * object = myinstance;
    myinstance->setPriority(MyClass::VeryHigh);
    object->setProperty("priority","Low");
    return 0;
}
