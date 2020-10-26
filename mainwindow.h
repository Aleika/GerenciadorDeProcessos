#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void populandoTabela();
    void pegarPID();
    void executarComando(int idComando);

public slots:
     void suspender();
     void continuar();
     void matar();
     void alterarCPU();
     void mudarPrioridade();
     void pegarPIDTabela(int column, int row);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
