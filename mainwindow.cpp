#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "huidu.h"
#include "erzhihua.h"
#include "lvbo.h"
#include "gamabianhua.h"
#include "bianyuanjiance.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(1000,630);

    setWindowTitle("yhh_199050130");

    m_PTranslator = new QTranslator(this);
    m_IsCN = true;






}

MainWindow::~MainWindow()
{
    delete ui;
}

Huidu hui;
ErZhiHua ErZhi;
LvBo Lb;
GaMabianhua GaMa;
BianYuanjiance BianYuan;





void MainWindow::changeEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        if(m_IsCN = false && ui->comboBox->currentIndex()==0)
        {
            ui->comboBox->setCurrentIndex(1);
        }
        break;
    default :
        break;
    }
}






void MainWindow::on_comboBox_activated(int index)
{
    switch(index)
    {
    case 0:
        m_PTranslator->load("../yhhfinal_CN.qm");
        //m_PTranslator->load("yhhfinal_CN.qm");
        m_IsCN = true;
        break;

    case 1:
        m_PTranslator->load("../yhhfinal/yhhfinal_EN.qm");
        //m_PTranslator->load("yhhfinal_EN.qm");
        m_IsCN = false;
        break;

    default:
        break;
    }
    qApp->installTranslator(m_PTranslator);
    //ui->retranslateUi(this);
    //QApplication::installTranslator(m_PTranslator);
}






//图片居中显示,图片大小与label大小相适应
QImage MainWindow::ImageSetSize (QImage  qimage,QLabel *qLabel)
{
    QImage image;
    QSize imageSize = qimage.size();
    QSize labelSize = qLabel->size();

    double dWidthRatio = 1.0*imageSize.width() / labelSize.width();
    double dHeightRatio = 1.0*imageSize.height() / labelSize.height();
            if (dWidthRatio>dHeightRatio)
            {
                image = qimage.scaledToWidth(labelSize.width());
            }
            else
            {
                image = qimage.scaledToHeight(labelSize.height());
            }
            return image;

    }


void MainWindow::on_OpenBtn_clicked()
{
    //打开图片文件，选择图片
    QStringList srcDirPathListS = QFileDialog::getOpenFileNames(this, tr("选择图片"),QDir::homePath(), tr("图像文件(*.jpg *.png *.bmp)"));
    qDebug()<<"图片路径"<<srcDirPathListS; //在控制台输出路径观察
    srcDirPathList = srcDirPathListS;//持久化图片
    if(!srcDirPathList.isEmpty())
    {
        imagenum =0;
        QImage image=QImage(srcDirPathList.at(imagenum));//初始化选中第一张图片
        qDebug()<<"image:"<<image;
        ImageShow(imagenum);
    }
    else if(srcDirPathList.isEmpty())
    {

        return;
    }

}

void MainWindow::on_OpenAct_triggered()
{
    //打开图片文件，选择图片
    QStringList srcDirPathListS = QFileDialog::getOpenFileNames(this, tr("选择图片"),QDir::homePath(), tr("图像文件(*.jpg *.png *.bmp)"));
    qDebug()<<"图片路径"<<srcDirPathListS; //在控制台输出路径观察
    srcDirPathList = srcDirPathListS;//持久化图片
    if(!srcDirPathList.isEmpty())
    {
        imagenum =0;
        QImage image=QImage(srcDirPathList.at(imagenum));//初始化选中第一张图片
        qDebug()<<"image:"<<image;
        ImageShow(imagenum);
    }
    else if(srcDirPathList.isEmpty())
    {

        return;
    }
}


void MainWindow::ImageShow(int imagenum)
{

    ui->PicLabel->setPixmap(QPixmap::fromImage(ImageSetSize(QImage(srcDirPathList.at(imagenum)),ui->PicLabel)));

    if(imagenum-1<0)
    {
    ui->BeforeLabel->setPixmap(QPixmap::fromImage(ImageSetSize(QImage(srcDirPathList.at(srcDirPathList.count()-1)),ui->BeforeLabel)));
    }
    else
    {
     ui->BeforeLabel->setPixmap(QPixmap::fromImage(ImageSetSize(QImage(srcDirPathList.at(imagenum-1)),ui->BeforeLabel)));
    }

    if(imagenum+1 >= srcDirPathList.count())
    {
     ui->AfterLabel->setPixmap(QPixmap::fromImage(ImageSetSize(QImage(srcDirPathList.at(0)),ui->BeforeLabel)));
    }
    else {
      ui->AfterLabel->setPixmap(QPixmap::fromImage(ImageSetSize(QImage(srcDirPathList.at(imagenum+1)),ui->BeforeLabel)));
    }
}






void MainWindow::on_HuiDuBtn_clicked()
{
    if(srcDirPathList.isEmpty())
    {
        QMessageBox::information(this,tr("请先选择图片"),
                                 tr("请先选择图片！"));
        return;
    }
    else{
        QImage image=QImage(srcDirPathList.at(imagenum));
        QImage grayimage=hui.gray(image);
        ui->PicLabel->setPixmap(QPixmap::fromImage(ImageSetSize(grayimage,ui->PicLabel)));
    }
}


//显示原图按钮
void MainWindow::on_YuanTuBtn_clicked()
{
    if(srcDirPathList.isEmpty())
    {
        QMessageBox::information(this,tr("请先选择图片"),
                                 tr("请先选择图片！"));
        return;
    }
    else{
        QImage image=QImage(srcDirPathList.at(imagenum));
        ui->PicLabel->setPixmap(QPixmap::fromImage(ImageSetSize(image,ui->PicLabel)));
    }
}


//二值化调节条
void MainWindow::on_ErZhiSlider_valueChanged(int value)
{
    if(srcDirPathList.isEmpty()){
        QMessageBox::information(this,tr("请先选择图片"),
                                 tr("请先选择图片！"));
        return;
    }
    else{
        QImage image=QImage(srcDirPathList.at(imagenum));//读取当前图片
        QImage grayimage=hui.gray(image);//灰度化
        QImage ErZhiImage=ErZhi.TwoSide(grayimage,value);//二值化
        ui->ErZhilineEdit->setText(QString::number(value));//改变文本框内值为二值化比对值
        ui->PicLabel->setPixmap(QPixmap::fromImage(ImageSetSize(ErZhiImage,ui->PicLabel)));//显示二值化图像
    }
}




//二值化文本框
void MainWindow::on_ErZhilineEdit_textEdited(const QString &arg1)
{
    if(srcDirPathList.isEmpty()){
        QMessageBox::information(this,tr("请先选择图片"),
                                 tr("请先选择图片！"));
        return;
    }
    else{
        int value=arg1.toInt();
        if (value>=0 && value<=255)
        {
        QImage image=QImage(srcDirPathList.at(imagenum));
        QImage grayimage=hui.gray(image);
        QImage TwoSideImage=ErZhi.TwoSide(grayimage,value);//都是和上面一样的
        ui->ErZhiSlider->setValue(value);//当文本框内数值改变时，动态变化调节条位置
        ui->PicLabel->setPixmap(QPixmap::fromImage(ImageSetSize(TwoSideImage,ui->PicLabel)));
        }
        else
        {
            QMessageBox::information(this,tr("请输入正确数值"),
                                     tr("请输入0-255！"));
            return;
        }
    }
}





//均值滤波按钮
void MainWindow::on_LvBoBtn_clicked()
{
    if(srcDirPathList.isEmpty())
        {
            QMessageBox::information(this,tr("请先选择图片"),
                                     tr("请先选择图片！"));
            return;
        }
        else{
            QImage image=QImage(srcDirPathList.at(imagenum));
            QImage avgimage=Lb.avg(image);
            ui->PicLabel->setPixmap(QPixmap::fromImage(ImageSetSize(avgimage,ui->PicLabel)));
        }
}





//调节条伽马变换
void MainWindow::on_GaMaSlider_valueChanged(int value)
{
    if(srcDirPathList.isEmpty()){
            QMessageBox::information(this,tr("请先选择图片"),
                                     tr("请先选择图片！"));
            return;
        }
        else{

            QImage image=QImage(srcDirPathList.at(imagenum));//读取当前图片
            double values=value;
            QImage GammaImage=GaMa.Gamma(image,values/10);//伽马变换
            ui->GaMalineEdit->setText(QString::number(values/10));//改变文本框内值为伽马因子
            ui->PicLabel->setPixmap(QPixmap::fromImage(ImageSetSize(GammaImage,ui->PicLabel)));//显示伽马变换图像
        }
}





//文本框伽马变换
void MainWindow::on_GaMalineEdit_textEdited(const QString &arg1)
{
    if(srcDirPathList.isEmpty()){
            QMessageBox::information(this,tr("请先选择图片"),
                                     tr("请先选择图片！"));
            return;
        }
        else{
            double value=arg1.toDouble();
            if (value>=0 && value<=25)
            {
            QImage image=QImage(srcDirPathList.at(imagenum));
            QImage GammaImage=GaMa.Gamma(image,value);//都是和上面一样的
            value=value*10;
            ui->GaMaSlider->setValue(value);//当文本框内数值改变时，动态变化调节条位置
            ui->PicLabel->setPixmap(QPixmap::fromImage(ImageSetSize(GammaImage,ui->PicLabel)));
            }
            else
            {
                QMessageBox::information(this,tr("请输入正确数值"),
                                         tr("请输入0-25！"));
                return;
            }
        }
}


//边缘检测
void MainWindow::on_BianYuanBtn_clicked()
{
    if(srcDirPathList.isEmpty())
        {
            QMessageBox::information(this,tr("请先选择图片"),
                                     tr("请先选择图片！"));
            return;
        }
        else{
            QImage image=QImage(srcDirPathList.at(imagenum));
            QImage grayimage=hui.gray(image);
            QImage guassimage=BianYuan.guass(image);
            QImage stimage=BianYuan.calculate(image,grayimage,guassimage);
            ui->PicLabel->setPixmap(QPixmap::fromImage(ImageSetSize(stimage,ui->PicLabel)));
        }

}




//另存为
void MainWindow::on_SaveAsBtn_clicked()
{
    QString fileName1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
    ui->PicLabel->pixmap()->toImage().save(fileName1);
    //if(1)
    //{
     //QMessageBox::information(this, tr("yhh_199050130"),tr("保存成功"),QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok);
    //}
    //else
    //{
     //QMessageBox::information(this, tr("yhh_199050130"),tr("保存失败"));
    //}
}






void MainWindow::on_AfterBtn_clicked()
{

}
