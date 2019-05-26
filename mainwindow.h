#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QStandardItem>
#include <QJsonArray>
#include "images.h"
#include "field.h"


namespace Ui {
class MainWindow;
}

enum State{
    ST_PLACING_SHIPHS,
    ST_WAITING_STEP,
    ST_MAKING_STEP

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QByteArray Data;

    QJsonDocument doc;
    QJsonParseError docError;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *ev);


public slots:
    void sockReady();
    void sockDisc();

signals:
    void StartServerGame();
    void StartAlone();
private slots:
    void on_actionClose_triggered();
    void on_actionPlayer_VS_Computer_triggered();
    void on_actionPlayers_VS_Player_triggered();

private:
    Ui::MainWindow *ui;
    Images *pictures;
    Field *field1, *field2;
    State state;
    QTcpSocket* client;
};

#endif // MAINWINDOW_H
