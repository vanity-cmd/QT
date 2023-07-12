#include "bianyuanjiance.h"

BianYuanjiance::BianYuanjiance()
{

}

//高斯平滑滤波器
void generic_guess(double kernel[10][10],int size,double thelt){
    double pi=acos(-1);
    double sum=0;
    int mk=size/2;
    for(int i=0;i<size;++i){
        for(int j=0;j<size;++j){
            kernel[i][j]=exp(-sqrt(pow(i-mk,2)+pow(j-mk,2))/(2*thelt*thelt));
            kernel[i][j]/=2*pi*thelt*thelt;
            sum+=kernel[i][j];
        }
    }
    for(int i=0;i<size;++i){
        for(int j=0;j<size;++j){
            kernel[i][j]/=sum;
        }
    }
}


//高斯滤波
QImage BianYuanjiance::guass(QImage grayimg){
    QImage guassimg;
    int k=5;//高斯滤波器规模
    double kernel[10][10];
    generic_guess(kernel,k,1.4);//设置好高斯滤波器
    //t_img用于将灰度图填充到长款都加上高斯滤波器的尺寸大小
    QImage * t_img=new QImage(grayimg.width()+k-1,grayimg.height()+k-1,QImage::Format_ARGB32);
    guassimg=QImage(grayimg.width(),grayimg.height(),QImage::Format_ARGB32);

    //lefttop
    for(int i=0;i<k/2;++i){
        for(int j=0;j<k/2;++j){
            t_img->setPixel(i,j,grayimg.pixel(0,0));

        }
    }

    //righttop
    for(int i=0;i<k/2;++i){
        for(int j=0;j<k/2;++j){
            t_img->setPixel(i,j,grayimg.pixel(grayimg.width()-1,0));

        }
    }

    //rightbottom
    for(int i=grayimg.width()+k/2;i<t_img->width();++i){
        for(int j=0;j<k/2;++j){
            t_img->setPixel(i,j,grayimg.pixel(grayimg.width()-1,grayimg.height()-1));
        }
    }

    //leftbottom
    for(int i=0;i<k/2;++i){
        for(int j=grayimg.height()+k/2;j<t_img->height();++j){
            t_img->setPixel(i,j,grayimg.pixel(0,grayimg.height()-1));

        }
    }

    //top
    for(int i=0;i<grayimg.width();++i){
        for(int j=0;j<k/2;++j){
            t_img->setPixel(i+k/2,j,grayimg.pixel(i,0));

        }
    }

    //right
    for(int i=t_img->width()-k/2;i<t_img->width();++i){
        for(int j=0;j<grayimg.height();++j){
            t_img->setPixel(i,j+k/2,grayimg.pixel(i,grayimg.height()-1));

        }
    }

    //left
    for(int i=0;i<k/2;++i){
           for(int j=0;j<grayimg.height();++j){
               t_img->setPixel(i,j+k/2,grayimg.pixel(0,j));
           }
       }

    for(int i=0;i<grayimg.width();++i){
        for(int j=0;j<grayimg.height();++j){
            t_img->setPixel(i+k/2,j+k/2,grayimg.pixel(i,j));

        }
    }

    for(int i=k/2;i<t_img->width()-k/2;++i){
        for(int j=k/2;j<t_img->height()-k/2;++j){
            double temp=0;
            for(int ti=0;ti<k;++ti){
                for(int tj=0;tj<k;++tj){
                    temp+=kernel[ti][tj]*qRed(t_img->pixel(i-k/2+ti,j-k/2+tj));
                }
            }
            guassimg.setPixel(i-k/2,j-k/2,qRgb(temp,temp,temp));
        }

    }
    return guassimg;
}



QImage BianYuanjiance::calculate(QImage img,QImage img_gray,QImage img_guass){
    //计算梯度强度和方向
    double * gradx[img.width()];
    for(int i=0;i<img.width();++i)
        gradx[i]=new double[img.height()];
    double * grady[img.width()];
    for(int i=0;i<img.width();++i)
        grady[i]=new double[img.height()];
    double * grad[img.width()];
    for(int i=0;i<img.width();++i)
        grad[i]=new double[img.height()];
    double * dir[img.width()];
    for(int i=0;i<img.width();++i)
        dir[i]=new double[img.height()];
    int k=3;//sobel算子规模
    double kernelx[3][3]={-1,0,1,-2,0,2,-1,0,1};
    double kernely[3][3]={1,2,1,0,0,0,-1,-2,-1};

    QImage * t_img=new QImage(img_gray.width()+k-1,img_gray.height()+k-1,QImage::Format_ARGB32);
    //lefttop
    for(int i=0;i<k/2;++i){
        for(int j=0;j<k/2;++j){
            t_img->setPixel(i,j,img_gray.pixel(0,0));
        }
    }
    //righttop
    for(int i=0;i<k/2;++i){
        for(int j=0;j<k/2;++j){
            t_img->setPixel(i,j,img_gray.pixel(img_gray.width()-1,0));
        }
    }
    //rightbottom
    for(int i=img_gray.width()+k/2;i<t_img->width();++i){
        for(int j=0;j<k/2;++j){
            t_img->setPixel(i,j,img_gray.pixel(img_gray.width()-1,img_gray.height()-1));
        }
    }
    //leftbottom
    for(int i=0;i<k/2;++i){
        for(int j=img_gray.height()+k/2;j<t_img->height();++j){
            t_img->setPixel(i,j,img_gray.pixel(0,img_gray.height()-1));
        }
    }
    //top
    for(int i=0;i<img_gray.width();++i){
        for(int j=0;j<k/2;++j){
            t_img->setPixel(i+k/2,j,img_gray.pixel(i,0));
        }
    }
    //right
    for(int i=t_img->width()-k/2;i<t_img->width();++i){
        for(int j=0;j<img_gray.height();++j){
            t_img->setPixel(i,j+k/2,img_gray.pixel(img_gray.width()-1,j));
        }
    }
    //bottom
    for(int i=0;i<img_gray.width();++i){
        for(int j=t_img->height()-k/2;j<t_img->height();++j){
            t_img->setPixel(i+k/2,j,img_gray.pixel(i,img_gray.height()-1));
        }
    }
    //left
    for(int i=0;i<k/2;++i){
        for(int j=0;j<img_gray.height();++j){
            t_img->setPixel(i,j+k/2,img_gray.pixel(0,j));
        }
    }
    for(int i=0;i<img_gray.width();++i){
        for(int j=0;j<img_gray.height();++j){
            t_img->setPixel(i+k/2,j+k/2,img_gray.pixel(i,j));
        }
    }
    for(int i=k/2;i<t_img->width()-k/2;++i){
        for(int j=k/2;j<t_img->height()-k/2;++j){
            double tempx=0;
            double tempy=0;
            for(int ti=0;ti<k;++ti){
                for(int tj=0;tj<k;++tj){
                    tempx+=kernelx[ti][tj]*qRed(t_img->pixel(i-k/2+ti,j-k/2+tj));
                    tempy+=kernely[ti][tj]*qRed(t_img->pixel(i-k/2+ti,j-k/2+tj));
                }
            }
            gradx[i-k/2][j-k/2]=tempx;
            grady[i-k/2][j-k/2]=tempy;
            grad[i-k/2][j-k/2]=sqrt(pow(tempx,2)+pow(tempy,2));
            double theta=atan(tempy/tempx)+90;
            if (theta >= 0 && theta < 45)
                dir[i-k/2][j-k/2] = 2;
            else if (theta >= 45 && theta < 90)
                dir[i-k/2][j-k/2] = 3;
            else if (theta >= 90 && theta < 135)
                dir[i-k/2][j-k/2] = 0;
            else
                dir[i-k/2][j-k/2] = 1;
        }
    }


    //非极大值抑制图像制作

    QImage img_nms=QImage(img_guass.width(),img_guass.height(),QImage::Format_ARGB32);
    double temp=0;
    for(int i=0;i<img_nms.width();++i){
        for(int j=0;j<img_nms.height();++j){
            temp+=grad[i][j];
        }
    }
    temp/=img_nms.width()*img_nms.height();

    double highthresh=temp;
    double lowthresh=highthresh;

    double N,NE,E,SW,W,SE,S,NW;
    double grad1=0,grad2=0,tantheta=0;



    for(int i=1;i<img_nms.width()-1;++i){
        for(int j=1;j<img_nms.height();++j){
            N=grad[i][j-1];
            NE=grad[i+1][j-1];
            E=grad[i+1][j];
            SW=grad[i-1][j+1];
            W=grad[i-1][j];
            SE=grad[i+1][j+1];
            S=grad[i][j+1];
            NW=grad[i-1][j-1];
            if(dir[i][j]==0){
                tantheta=abs(grady[i][j]/gradx[i][j]);
                grad1=E*(1-tantheta)+NE*tantheta;
                grad2=W*(1-tantheta)+SW*tantheta;
            }
            else if(dir[i][j]==1){
                tantheta=abs(gradx[i][j]/grady[i][j]);
                grad1=N*(1-tantheta)+NE*tantheta;
                grad2=S*(1-tantheta)+SW*tantheta;
            }
            else if(dir[i][j]==2){
                tantheta=abs(gradx[i][j]/grady[i][j]);
                grad1=N*(1-tantheta)+NW*tantheta;
                grad2=S*(1-tantheta)+SE*tantheta;
            }
            else if(dir[i][j]==3){
                tantheta=abs(grady[i][j]/gradx[i][j]);
                grad1=W*(1-tantheta)+NW*tantheta;
                grad2=E*(1-tantheta)+SE*tantheta;
            }
            else{
                grad1=highthresh;
                grad2=highthresh;
            }
            if(grad[i][j]>grad1&&grad[i][j]>grad2){
                img_nms.setPixel(i,j,qRgb(255,255,255));//black边缘
                //                gradcp[i][j]=highthresh;
            }
            else{
                img_nms.setPixel(i,j,qRgb(0,0,0));//white
                grad[i][j]=0;
            }
        }
    }

    //双阈值检测
    QImage img_dt= QImage(img_nms.width(),img_nms.height(),QImage::Format_ARGB32);
    double * gradcp[img.width()];
    for(int i=0;i<img.width();++i)
        gradcp[i]=new double[img.height()];


    for(int i=0;i<img_dt.width();++i){
        for(int j=0;j<img_dt.height();++j){
            if(grad[i][j]>highthresh){//强边缘
                gradcp[i][j]=highthresh;
                img_dt.setPixel(i,j,qRgb(255,255,255));
            }
            else if(grad[i][j]>lowthresh){//弱边缘
                gradcp[i][j]=lowthresh;
                img_dt.setPixel(i,j,qRgb(255,255,255));
            }
            else{//非边缘
                gradcp[i][j]=0;
                img_dt.setPixel(i,j,qRgb(0,0,0));//抑制
            }
        }
    }


    QImage img_st=QImage(img_dt.width(),img_dt.height(),QImage::Format_ARGB32);
    int frac[8][2]={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
    for(int i=1;i<img_st.width()-1;++i){
        for(int j=1;j<img_st.height()-1;++j){
            if(gradcp[i][j]==highthresh){//强边缘
                img_st.setPixel(i,j,qRgb(255,255,255));
            }
            else if(gradcp[i][j]==lowthresh){//弱边缘
                for(int p=0;p<8;++p){
                    if(gradcp[i+frac[p][0]][j+frac[p][1]]==highthresh){
                        img_st.setPixel(i,j,qRgb(255,255,255));//边缘
                        break;
                    }
                    img_st.setPixel(i,j,qRgb(0,0,0));//非边缘
                }
            }
            else//非边缘
                img_st.setPixel(i,j,qRgb(0,0,0));
        }
    }


    return img_st;

}

