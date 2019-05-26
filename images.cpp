#include "images.h"

void Images::load(){
images.insert("background",QImage("C:\\Users\\Mic-PC\\Documents\\MGTU IM BAUMANA\\Algorithm_language\\Second_Sem\\HW\\QT\\Sea_Battle\\Resources\\background.png"));
images.insert("ship_part",QImage("C:\\Users\\Mic-PC\\Documents\\MGTU IM BAUMANA\\Algorithm_language\\Second_Sem\\HW\\QT\\Sea_Battle\\Resources\\ship_part.png"));
images.insert("past",QImage("C:\\Users\\Mic-PC\\Documents\\MGTU IM BAUMANA\\Algorithm_language\\Second_Sem\\HW\\QT\\Sea_Battle\\Resources\\past.png"));
images.insert("hit",QImage("C:\\Users\\Mic-PC\\Documents\\MGTU IM BAUMANA\\Algorithm_language\\Second_Sem\\HW\\QT\\Sea_Battle\\Resources\\hit.png"));
images.insert("killed",QImage("C:\\Users\\Mic-PC\\Documents\\MGTU IM BAUMANA\\Algorithm_language\\Second_Sem\\HW\\QT\\Sea_Battle\\Resources\\killed.png"));
}

QImage &Images::get(const QString &imgName){
    QMap<QString,QImage>::iterator i = images.find(imgName);
    if (i==images.end())
        throw 1;
    return i.value();

}
