#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pictures = new Images;
    pictures->load();

    field1 = new Field(pictures,43,39,382,382);
    field2 = new Field(pictures,588,39,382,382);

    client = new QTcpSocket(this);
        connect(client,SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(client,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    connect(client,SIGNAL(StartServerGame()),this,SLOT(GameByServer()));


    field1->redraw();
    field2->redraw();

    state = ST_PLACING_SHIPHS;
}

MainWindow::~MainWindow()
{
    delete pictures;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(0,this->menuBar()->geometry().height(),
                      pictures->get("background"));
    painter.drawImage(field1->getX(),this->menuBar()
                      ->geometry().height()+field1->getY(),
                      field1->getImage());
    painter.drawImage(field2->getX(),this->menuBar()
                      ->geometry().height()+field2->getY(),
                      field2->getImage());

}

void MainWindow::mousePressEvent(QMouseEvent *ev){
    QPoint pos = ev->pos();
    pos.setY(pos.y() - this->menuBar()->geometry().height());
    if(state==ST_PLACING_SHIPHS){
        QPoint point = field1->getCoord(pos.x(),pos.y());
        if(point.x()==-1) return;
        qDebug() << "Ship at" << point.x() << point.y();
        field1->setCell(point.x(),point.y(),CL_SHIP);
        field1->redraw();
        this->update();
    }
    else if(state==ST_MAKING_STEP){
        QPoint point = field2->getCoord(pos.x(),pos.y());
        if(point.x()==-1) return;
        qDebug() << "Going to" << point.x() << point.y();
        field2->setCell(point.x(),point.y(),CL_DOT);
        field1->redraw();
        this->update();
        //TODO: network code here
    }
}


void MainWindow::sockDisc()
{
  client->deleteLater();
}

void MainWindow::sockReady()
{
    if (client->waitForConnected(500))
    {
        client->waitForReadyRead(500);
        Data = client->readAll();

        doc = QJsonDocument::fromJson(Data,&docError);

        if(docError.errorString()=="no error occurred"){
            if((doc.object().value("type").toString() == "connect" ) && (doc.object().value("status").toString() == "yes")){
                QMessageBox::information(this, "Информация","Соединение установлено");
            }
            /*else if(doc.object().value("type").toString() == "resultSelect"){
                QStandardItemModel* model = new QStandardItemModel(nullptr);
                model->setHorizontalHeaderLabels(QStringList()<<"name");

                QJsonArray docAr = doc.object().value("result").toArray();
                for(int i=0;i<docAr.count();i++){
                    QStandardItem* col = new QStandardItem(docAr[i].toObject().value("name").toString());
                    model->appendRow(col);*/
            }

            else{
                QMessageBox::information(this,"Информация","Соединение не установлено");
            }
        }
        else{
            QMessageBox::information(this,"Информация","Ошибки передачи с форматом данных   "+docError.errorString());
        }
}

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionPlayer_VS_Computer_triggered()
{
    qDebug()<< "Pressed Start BY SERVER";
}

void MainWindow::on_actionPlayers_VS_Player_triggered()
{
    qDebug()<< "Pressed Start BY SERVER";
    client->connectToHost("127.0.0.1",1234);
    emit StartServerGame();
}
