#define COLUMNS 7
#define SUSPENDER 1
#define MATAR 2
#define CONTINUAR 3

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>
#include <QFile>
#include <QDebug>

#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include  <time.h>
#include <sched.h>
#include <stdlib.h>

#include <sys/time.h>
#include <qresource.h>

#define _GNU_SOURCE
#include <sched.h>


using namespace std;

QString pid;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    populandoTabela();
    startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populandoTabela()
{
    ui->tabela->clearContents();

    QString path = "C:\\Users\\Usuário\\Documents\\GerenciadorDeProcessos\\processos.txt";
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    QTextStream in(&file);

    int rows = 0;

    while(!in.atEnd()) {
        QString line = in.readLine();
        ui->tabela->setRowCount(line.size());

        QStringList fields = line.split(",");

        for (auto c=0; c<COLUMNS; c++){
             ui->tabela->setItem( rows, c, new QTableWidgetItem(fields.at(c)));
             ui->tabela->update();
        }
        rows++;
    }
    ui->tabela->update();

    file.close();

// ------------ Inserindo Linhas na Tabela
//    tableWidget->insertRow ( tableWidget->rowCount() );
//    tableWidget->setItem   ( tableWidget->rowCount()-1,
//                             yourColumn,
//                             new QTableWidgetItem(string));

//    ui->tableWidget->clear();
//    ui->tableWidget->setRowCount(numRows);
//    ui->tableWidget->setColumnCount(numColumns);
//    for (auto r=0; r<numRows; r++)
//         for (auto c=0; c<numColumns; c++)
//              tableWidget->setItem( r, c, new QTableWidgetItem(stringData(r,c)));

//    QFile file("/home/hamad/lesson11.txt");
//    if(!file.open(QIODevice::ReadOnly)) {
//        QMessageBox::information(0, "error", file.errorString());
//    }


//-------------------Leitura de Arquivo
//    QTextStream in(&file);

//    while(!in.atEnd()) {
//        QString line = in.readLine();
//        QStringList fields = line.split(",");
//        model->appendRow(fields);
//    }

    //    file.close();
}

void MainWindow::pegarPID()
{
   pid = ui->textEditPID->toPlainText();

}

void MainWindow::executarComando(int idComando)
{
    pegarPID();
    QString comando;

    switch (idComando) {
    case MATAR:
        comando = "kill -STOP "+pid;
        break;
    case SUSPENDER:
        comando = "kill -TSTP "+pid;
       // kill(pid,SIGKILL);
        //(void) signal(SIGINT, ouch);
        break;
    case CONTINUAR:
        comando = "kill -CONT "+pid;
        break;
    default:
        break;
    }

    QByteArray comandoConvertido = comando.toLocal8Bit();
    const char *comandoFinal = comandoConvertido.data();

    system(comandoFinal);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
//    if(ui->textEditFiltro->toPlainText().isEmpty()){
//        system("pstree grep > processos.txt");
//        populandoTabela();
//    }
}

void MainWindow::suspender()
{
    executarComando(SUSPENDER);
}

void MainWindow::continuar()
{
    executarComando(CONTINUAR);
}

void MainWindow::matar()
{
    executarComando(MATAR);
}

void MainWindow::alterarCPU()
{
    int novaCPU;
    novaCPU = ui->comboBoxCPU->currentText().toInt();

   // cpu_set_t mask;
    //CPU_ZERO(&mask);


    //CPU_SET(pid, &mask);    // alocar na CPU 0
    //int result = sched_setaffinity(0, sizeof(mask), &mask);

    qDebug() << novaCPU;
}

void MainWindow::mudarPrioridade()
{
    QString novaPrioridade;
    QString comando;

    novaPrioridade = ui->comboBoxPrioridade->currentText();
    pegarPID();

    comando = " renice " + novaPrioridade + " -p " + pid;

    QByteArray comandoConvertido = comando.toLocal8Bit();
    const char *comandoFinal = comandoConvertido.data();

    system(comandoFinal);

    //setpriority(PRIO_PROCESS, pid , novaPrioridade);

    qDebug() << novaPrioridade;
}

void MainWindow::pegarPIDTabela(QModelIndex *i)
{

    qDebug() << i->row();
    qDebug() << "clicou";
}

void MainWindow::filtro()
{
     QString textoFiltro = ui->textEditFiltro->toPlainText();

     QString comando;
     comando = " ps -auf | grep " + textoFiltro + " > processos.txt";

     QByteArray comandoConvertido = comando.toLocal8Bit();
     const char *comandoFinal = comandoConvertido.data();

 //    system(comandoFinal);

     populandoTabela();
}

