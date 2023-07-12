#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QList>
#include <QString>
#include <QMessageBox>
#include <QScreen>
#include <QTranslator>
#include <QEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int imagenum;
    QStringList srcDirPathList;

    QImage ImageSetSize(QImage  qimage,QLabel *qLabel);
    void ImageShow(int imagenum);

    void retranslateUi();

    void changeEvent(QEvent *event);








private slots:


    void on_OpenBtn_clicked();

    void on_OpenAct_triggered();

    //void on_BeforeBtn_clicked();

    //void on_AfterBtn_clicked();

    void on_HuiDuBtn_clicked();

    void on_YuanTuBtn_clicked();

    void on_ErZhiSlider_valueChanged(int value);

    void on_ErZhilineEdit_textEdited(const QString &arg1);

    void on_LvBoBtn_clicked();

    void on_GaMaSlider_valueChanged(int value);

    void on_GaMalineEdit_textEdited(const QString &arg1);

    void on_BianYuanBtn_clicked();

    void on_SaveAsBtn_clicked();

    void on_comboBox_activated(int index);

    void on_AfterBtn_clicked();

private:
    Ui::MainWindow *ui;
    QTranslator *m_PTranslator;
    bool m_IsCN;
};
#endif // MAINWINDOW_H
