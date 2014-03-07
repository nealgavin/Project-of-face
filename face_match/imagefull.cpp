// imagefull.cpp : implementation file
//

#include "stdafx.h"
#include "imagestitch.h"
#include "imagefull.h"


//////////////////////////////////////////////
#include "cv.h"
#include "highgui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <io.h>
#include <time.h>
#include <ctype.h>

#include <winsock.h>
#include <iostream>
#include <vector>
#include <string>
#include <mysql.h>
#include <windows.h>

#include "AddDlg.h"
#include "StuDlg.h"
#include "CourseDlg.h"
#include "GradeDlg.h"
#include "MysqlDlg.h"

#ifdef _EiC
#define WIN32
#endif
using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libmysql.lib")

//////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// imagefull dialog


imagefull::imagefull(CWnd* pParent /*=NULL*/)
	: CDialog(imagefull::IDD, pParent)
{
	//{{AFX_DATA_INIT(imagefull)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void imagefull::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(imagefull)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(imagefull, CDialog)
	//{{AFX_MSG_MAP(imagefull)
	ON_BN_CLICKED(IDC_openimage1, Onopenimage1)
	ON_BN_CLICKED(IDC_openimage2, Onopenimage2)
	ON_BN_CLICKED(IDC_openimage6, Onopenimage6)
	ON_BN_CLICKED(IDC_stitchfullimage, Onstitchfullimage)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)

	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// imagefull message handlers

static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;
const int path_len = 555;
const int con_in_width = 1000;
const int con_in_height = 1000;
const int con_width = 100;
const int con_height = 100;
//char path_name[55],ID_Student[55]="F:\\project\\code\\training\\Rsize_Pic\\data\\Computer";
char con_check[65]="G:\\project\\code\\training\\face_match\\data\\";		//Ĭ�ϵ�ƥ����ʱĿ¼
char con_save[555] = "G:\\project\\code\\training\\face_match\\sam\\";	//��Ϣ¼��ʱĬ�ϵĴ�ͼƬ·��
vector<string> pic_name;	//������ͼƬ������
const char* cascade_name ="haarcascade_frontalface_alt.xml";
int Sample_NUM = 20;
CvMat* Sample;   ///����
CvMat* Unkonw;  ///��ʶ����������
CvMat* avg;
CvMat* eigenvectors;
CvMat* result;

MYSQL mydata;



CString filename;
std::string tempname;
string path_save;
IplImage *con_dst;


/*
void detect_and_draw( IplImage* img ,int in_or_check);
IplImage* RESIZE_PIC(IplImage*img);
void Draw(string path_name,int fun_choose);
void data_in_mysql(string stu_id,string index,string path_save);
bool SQL_query(string data_query);
*/

//��ͼ��1
void imagefull::Onopenimage1() 
{
	// TODO: Add your control notification handler code here
	
//	CString filename;
	char  szFilter[] = "Jpg Files (*.jpg)|*.jpg|All Files (*.*)|*.*||";
	CFileDialog fdlg(TRUE, "JPG", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	
	if(fdlg.DoModal()!=IDOK)//����һֱ�ٽ�����
		
		return;
	
	filename=fdlg.GetPathName();
//	std::string tempname = (LPCSTR)CString(filename);
	tempname = (LPCSTR)CString(filename);
	const char* tmp=tempname.c_str();
	imageone=NULL;
	imageone=cvLoadImage(tmp,CV_LOAD_IMAGE_ANYCOLOR);
	
	IplImage* dst=NULL;
	dst=cvCreateImage(cvGetSize(imageone),imageone->depth,imageone->nChannels);
	cvCopy(imageone,dst,NULL);
	
	
	float wscale, hscale;		
	int tempw,temph;
	tempw=imageone->width;
	temph=imageone->height;
	wscale=350.1/tempw;
	hscale=240.0/temph;
	CvSize dst_cvsize;	
	dst_cvsize.width = imageone->width * wscale;		//Ŀ��ͼ��Ŀ�ΪԴͼ����scale��
	dst_cvsize.height = imageone->height * hscale;	//Ŀ��ͼ��ĸ�ΪԴͼ��ߵ�scale��
	
	dst = cvCreateImage( dst_cvsize, imageone->depth, imageone->nChannels);	//����Ŀ��ͼ��
	cvResize(imageone, dst, CV_INTER_LINEAR);	//����Դͼ��Ŀ��ͼ��	
	cvNamedWindow( "ͼ��1",   CV_WINDOW_AUTOSIZE );	//����������ʾĿ��ͼ��Ĵ���	
	cvShowImage( "ͼ��1", dst );		//��ʾĿ��ͼ��
	cvMoveWindow( "ͼ��1",0,0);
	cvWaitKey(0);
	cvReleaseImage(&dst);	//�ͷ�Ŀ��ͼ��ռ�õ��ڴ�
	cvDestroyWindow( "ͼ��1" );	//���ٴ��ڡ�dst��
}
//��ͼ��2
void imagefull::Onopenimage2() 
{
	// TODO: Add your control notification handler code here
//CString filename;
	char  szFilter[] = "Jpg Files (*.jpg)|*.jpg|All Files (*.*)|*.*||";
	CFileDialog fdlg(TRUE, "JPG", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	
	if(fdlg.DoModal()!=IDOK)//����һֱ�ٽ�����
		
		return;
	
	filename=fdlg.GetPathName();
//	std::string tempname = (LPCSTR)CString(filename);
	tempname = (LPCSTR)CString(filename);
	const char* tmp=tempname.c_str();
	imagetwo=NULL;
	imagetwo=cvLoadImage(tmp,CV_LOAD_IMAGE_ANYCOLOR);
	
	IplImage* dst=NULL;
	dst=cvCreateImage(cvGetSize(imagetwo),imagetwo->depth,imagetwo->nChannels);
	cvCopy(imagetwo,dst,NULL);
	
	
	float wscale, hscale;		
	int tempw,temph;
	tempw=imagetwo->width;
	temph=imagetwo->height;
	wscale=350.1/tempw;
	hscale=240.0/temph;
	CvSize dst_cvsize;	
	dst_cvsize.width = imagetwo->width * wscale;		//Ŀ��ͼ��Ŀ�ΪԴͼ����scale��
	dst_cvsize.height = imagetwo->height * hscale;	//Ŀ��ͼ��ĸ�ΪԴͼ��ߵ�scale��
	
	dst = cvCreateImage( dst_cvsize, imagetwo->depth, imagetwo->nChannels);	//����Ŀ��ͼ��
	cvResize(imagetwo, dst, CV_INTER_LINEAR);	//����Դͼ��Ŀ��ͼ��	
	cvNamedWindow( "ͼ��2",   CV_WINDOW_AUTOSIZE );	//����������ʾĿ��ͼ��Ĵ���	
	cvShowImage( "ͼ��2", dst );		//��ʾĿ��ͼ��
	cvMoveWindow( "ͼ��2",365,0);
	cvWaitKey(0);
	cvReleaseImage(&dst);	//�ͷ�Ŀ��ͼ��ռ�õ��ڴ�
	cvDestroyWindow( "ͼ��2" );	//���ٴ��ڡ�dst��
}

//����
void imagefull::Onopenimage6() 
{
	// TODO: Add your control notification handler code here
	cvDestroyWindow( "ͼ��1" );	//���ٴ��ڡ�dst��
	cvDestroyWindow( "ͼ��2" );	//���ٴ��ڡ�dst��
	cvDestroyWindow("ȫ��ͼ");
	cvSaveImage("F:/project/code/training/RELEASEimagestitch0/joint/fullimag.jpg",bb.image33);
}

IplImage* imagefull::cutleftimage(IplImage *image)
{
	int wd,hd;
	wd=image->width;
	hd=image->height;
	if (wd >= 1600 && hd >= 1200)
	{
		
		uchar * datain;
		uchar * tempdata;
		IplImage *temp=NULL;
		CvSize temp_cvsize;
		temp_cvsize.width=1550;
		temp_cvsize.height=1200;
		temp=cvCreateImage(temp_cvsize,image->depth,image->nChannels);
		tempdata=(uchar *)temp->imageData;
		datain=(uchar *)image->imageData;
		int wd,hg;
		wd=image->width;
		hg=image->height;
		for (int i=0;i<1200;i++)
		{
			for (int j=0;j<1550;j++)
			{
				for (int n=0;n<3;n++)
				{
					tempdata[i*temp->widthStep+j*temp->nChannels+n]=datain[(hg/2-600+i)*image->widthStep+j*image->nChannels+n];
				}
			}
		}
		
		//	cvSaveImage("D:\imageptocy1.jpg",temp);
		return temp;
	}
	else
	{
		return image;
		
		
	}

}
IplImage* imagefull::cutrightimage(IplImage *image)
{
	int wd,hd;
	wd=image->width;
	hd=image->height;
	if (wd >= 1600 && hd >= 1200)
	{
		
		uchar * datain;
		uchar * tempdata;
		IplImage *temp=NULL;
		CvSize temp_cvsize;
		temp_cvsize.width=1550;
		temp_cvsize.height=1200;
		temp=cvCreateImage(temp_cvsize,image->depth,image->nChannels);
		tempdata=(uchar *)temp->imageData;
		datain=(uchar *)image->imageData;
		int wd,hg;
		wd=image->width;
		hg=image->height;
		for (int i=0;i<1200;i++)
		{
			for (int j=0;j<1550;j++)
			{
				for (int n=0;n<3;n++)
				{
					tempdata[i*temp->widthStep+j*temp->nChannels+n]=datain[(hg/2-600+i)*image->widthStep+(wd-1550+j)*image->nChannels+n];
				}
			}
		}
		
		//	cvSaveImage("D:\imageptocy1.jpg",temp);
		return temp;
	}
	else
	{
		return image;
		

	}

}

void imagefull::step1(IplImage *image)
{
	image1=NULL;
	IplImage *grey_im1=NULL;
	DoubleSizeImage1=NULL;
	
	CvMat *image1Mat=NULL;
	tempMat1=NULL;
	
	//Ϊͼ������ڴ�
	image1=cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
	grey_im1=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);
	DoubleSizeImage1=cvCreateImage(cvSize(2*(image->width),2*(image->height)),IPL_DEPTH_8U,3);
	//Ϊͼ�����з����ڴ棬��������ͼ��Ĵ�С��ͬ��tempMat����image1�Ĵ�С
	image1Mat=cvCreateMat(image->height,image->width,CV_32FC1);
	//ת���ɵ�ͨ��ͼ���ٴ���
	cvCvtColor(image,grey_im1,CV_BGR2GRAY);
	//ת����Mat���ݽṹ��ͼ�����ʹ�õ��Ǹ����Ͳ���
	cvConvert(grey_im1,image1Mat);
	
	//double t=(double)cvGetTickCount();
	
	//ͼ���һ��
	cvConvertScale(image1Mat,image1Mat,1.0/255,0);
	
	int dim;
	dim=min(image1Mat->rows,image1Mat->cols);
	//����������
	aa.numoctaves=(int) (log((double)dim) / log(2.0))-2;
	aa.numoctaves=min(aa.numoctaves,MAXOCTAVES);
	
	//step1Ԥ�˲��������������������ײ㣬�ײ�Ϊԭͼ�������
	tempMat1=aa.ScaleInitImage(image1Mat);
	
	//	cvReleaseImage(& image1);

	cvReleaseImage(& grey_im1);
	cvReleaseMat(& image1Mat);

}
void imagefull::step2()
{
	int keycount=bb.DetectKeypoint1(aa.numoctaves,Gaussianpyr1);
	
/*	cvCopy(imageptocy1,image1,NULL);
	bb.DisplayKeypointLocation1(image1,Gaussianpyr1);
	cvPyrUp(image1,DoubleSizeImage1,CV_GAUSSIAN_5x5);
	//cvReleaseImage(&image1);
	cvSaveImage("D:\DoubleSizeImage1.jpg",DoubleSizeImage1);
	cvNamedWindow("image1",2);
	cvShowImage("image1", DoubleSizeImage1);
	cvReleaseImage(&DoubleSizeImage1);
	cvWaitKey(0);  
    cvDestroyWindow("image1");*/

}


void imagefull::step3()
{
	bb.ComputeGrad_DirecandMag1(aa.numoctaves,Gaussianpyr1);
	bb.AssignTheMainOrientation1(aa.numoctaves,Gaussianpyr1,aa.mag_pyr,aa.grad_pyr);
/*	cvCopy(imageptocy1,image1,NULL);
	aa.DisplayOrientation(image1,Gaussianpyr1);
	
	cvSaveImage("D:\mag1.jpg",image1);
	cvNamedWindow("image11",2);
	cvShowImage("image11",image1);
	//cvReleaseImage(& image1);
	cvWaitKey(0);  
    cvDestroyWindow("image11");*/

}
void imagefull::clearmemory()
{
	if(imageone!=NULL)
		cvReleaseImage(&imageone);


}

void imagefull::stitch1(IplImage* imag1,IplImage* imag2)
{
	int wd,hd;
	wd=imag1->width;
	hd=imag1->height;
	if (wd >= 1600 && hd>= 1200)
	{
		bb.stitch1(imag1,imag2);
	}
	else
	{
		bb.stitch2(imag1,imag2);
	}
}
//ȫ��ƴ��
void imagefull::Onstitchfullimage() 
{
	// TODO: Add your control notification handler code here

	//��һ��ƴ��

	//��һ��ͼƬ
	imageptocy11=aa.palnetocylinder1(imageone);
	imageptocy1=cutrightimage(imageptocy11);
	step1(imageptocy1);//�����ײ������
	Gaussianpyr1=bb.BuildGaussianOctaves1(tempMat1);//����˫������
	int keycount0=bb.DetectKeypoint1(aa.numoctaves,Gaussianpyr1);
	//cvCopy(imageptocy2,image1,NULL);
	//bb.DisplayKeypointLocation2(image1,Gaussianpyr2);
	
	bb.ComputeGrad_DirecandMag1(aa.numoctaves,Gaussianpyr1);
	bb.AssignTheMainOrientation1(aa.numoctaves,Gaussianpyr1,bb.mag_pyr1,bb.grad_pyr1);//�����ֵ����
	bb.ExtractFeatureDescriptors1(aa.numoctaves,Gaussianpyr1);//����������

	//�ڶ���ͼƬ
	imageptocy22=aa.palnetocylinder1(imagetwo);
	imageptocy2=cutleftimage(imageptocy22);
	step1(imageptocy2);//�����ײ������
	Gaussianpyr2=bb.BuildGaussianOctaves2(tempMat1);//����˫������
	int keycount=bb.DetectKeypoint2(aa.numoctaves,Gaussianpyr2);
	//cvCopy(imageptocy2,image1,NULL);
	//bb.DisplayKeypointLocation2(image1,Gaussianpyr2);

	bb.ComputeGrad_DirecandMag2(aa.numoctaves,Gaussianpyr2);
	bb.AssignTheMainOrientation2(aa.numoctaves,Gaussianpyr2,bb.mag_pyr2,bb.grad_pyr2);//�����ֵ����

	bb.ExtractFeatureDescriptors2(aa.numoctaves,Gaussianpyr2);//����������

/*	cvCopy(imageptocy2,image1,NULL);
	bb.DisplayOrientation2(image1,Gaussianpyr2);
	
	cvSaveImage("D:\mag1.jpg",image1);
	cvNamedWindow("image11",2);
	cvShowImage("image11",image1);
	//cvReleaseImage(& image1);
	cvWaitKey(0);  
    cvDestroyWindow("image11");*/

	
	
	stitch1(imageptocy11,imageptocy22);

	if (imageptocy11!=NULL)
	{
		cvReleaseImage(&imageptocy11);
	}
	if (imageptocy22!=NULL)
	{
		cvReleaseImage(&imageptocy22);
	}
	if (imageone!=NULL)
	{
		cvReleaseImage(&imageone);
	}
	if (imagetwo!=NULL)
	{
		cvReleaseImage(&imagetwo);
	}
	if (Gaussianpyr1!=NULL)
	{
		Gaussianpyr1=NULL;
	}
	if (Gaussianpyr2!=NULL)
	{
		Gaussianpyr2=NULL;
	}






	/*//�ڶ���ƴ��
	//��һ��
	imageok1=NULL;
	imageok1=cvCreateImage(cvGetSize(bb.image33),bb.image33->depth,bb.image33->nChannels);
	cvCopy(bb.image33,imageok1,NULL);

	
	imageptocy1=cutrightimage(imageok1);
	step1(imageptocy1);//�����ײ������
	Gaussianpyr1=bb.BuildGaussianOctaves1(tempMat1);//����˫������
	int keycount1=bb.DetectKeypoint1(aa.numoctaves,Gaussianpyr1);
	//cvCopy(imageptocy2,image1,NULL);
	//bb.DisplayKeypointLocation2(image1,Gaussianpyr2);
	
	bb.ComputeGrad_DirecandMag1(aa.numoctaves,Gaussianpyr1);
	bb.AssignTheMainOrientation1(aa.numoctaves,Gaussianpyr1,bb.mag_pyr1,bb.grad_pyr1);//�����ֵ����
	bb.ExtractFeatureDescriptors1(aa.numoctaves,Gaussianpyr1);//����������

	//�ڶ���
	imageptocy33=aa.palnetocylinder1(imagethree);
	imageptocy3=cutleftimage(imageptocy33);
	step1(imageptocy3);//�����ײ������
	Gaussianpyr2=bb.BuildGaussianOctaves2(tempMat1);//����˫������
	int keycount2=bb.DetectKeypoint2(aa.numoctaves,Gaussianpyr2);
	//cvCopy(imageptocy2,image1,NULL);
	//bb.DisplayKeypointLocation2(image1,Gaussianpyr2);
	
	bb.ComputeGrad_DirecandMag2(aa.numoctaves,Gaussianpyr2);
	bb.AssignTheMainOrientation2(aa.numoctaves,Gaussianpyr2,bb.mag_pyr2,bb.grad_pyr2);//�����ֵ����
	
	bb.ExtractFeatureDescriptors2(aa.numoctaves,Gaussianpyr2);//����������

	stitch1(imageok1,imageptocy33);

	if (imageptocy33!=NULL)
	{
		cvReleaseImage(&imageptocy33);
	}

	if (imagethree!=NULL)
	{
		cvReleaseImage(&imagethree);
	}

	if (Gaussianpyr1!=NULL)
	{
		Gaussianpyr1=NULL;
	}
	if (Gaussianpyr2!=NULL)
	{
		Gaussianpyr2=NULL;
	}




	//������ƴ��
	//��һ��
	if (imageok1!=NULL)
	{
		cvReleaseImage(&imageok1);
	}
	
	imageok1=cvCreateImage(cvGetSize(bb.image33),bb.image33->depth,bb.image33->nChannels);
	cvCopy(bb.image33,imageok1,NULL);
	
	
	imageptocy1=cutrightimage(imageok1);
	step1(imageptocy1);//�����ײ������
	Gaussianpyr1=bb.BuildGaussianOctaves1(tempMat1);//����˫������
	int keycount3=bb.DetectKeypoint1(aa.numoctaves,Gaussianpyr1);
	//cvCopy(imageptocy2,image1,NULL);
	//bb.DisplayKeypointLocation2(image1,Gaussianpyr2);
	
	bb.ComputeGrad_DirecandMag1(aa.numoctaves,Gaussianpyr1);
	bb.AssignTheMainOrientation1(aa.numoctaves,Gaussianpyr1,bb.mag_pyr1,bb.grad_pyr1);//�����ֵ����
	bb.ExtractFeatureDescriptors1(aa.numoctaves,Gaussianpyr1);//����������

	//�ڶ���
	imageptocy44=aa.palnetocylinder1(imagefour);
	imageptocy4=cutleftimage(imageptocy44);
	step1(imageptocy4);//�����ײ������
	Gaussianpyr2=bb.BuildGaussianOctaves2(tempMat1);//����˫������
	int keycount5=bb.DetectKeypoint2(aa.numoctaves,Gaussianpyr2);
	//cvCopy(imageptocy2,image1,NULL);
	//bb.DisplayKeypointLocation2(image1,Gaussianpyr2);
	
	bb.ComputeGrad_DirecandMag2(aa.numoctaves,Gaussianpyr2);
	bb.AssignTheMainOrientation2(aa.numoctaves,Gaussianpyr2,bb.mag_pyr2,bb.grad_pyr2);//�����ֵ����
	
	bb.ExtractFeatureDescriptors2(aa.numoctaves,Gaussianpyr2);//����������
	
	stitch1(imageok1,imageptocy44);


	if (imageptocy44!=NULL)
	{
		cvReleaseImage(&imageptocy44);
	}

	if (imagefour!=NULL)
	{
		cvReleaseImage(&imagefour);
	}

	if (Gaussianpyr1!=NULL)
	{
		Gaussianpyr1=NULL;
	}
	if (Gaussianpyr2!=NULL)
	{
		Gaussianpyr2=NULL;
	}


	//���Ĵ�ƴ��
	//��һ��
	if (imageok1!=NULL)
	{
		cvReleaseImage(&imageok1);
	}
	
	imageok1=cvCreateImage(cvGetSize(bb.image33),bb.image33->depth,bb.image33->nChannels);
	cvCopy(bb.image33,imageok1,NULL);
	
	
	imageptocy1=cutrightimage(imageok1);
	step1(imageptocy1);//�����ײ������
	Gaussianpyr1=bb.BuildGaussianOctaves1(tempMat1);//����˫������
	int keycount6=bb.DetectKeypoint1(aa.numoctaves,Gaussianpyr1);
	//cvCopy(imageptocy2,image1,NULL);
	//bb.DisplayKeypointLocation2(image1,Gaussianpyr2);
	
	bb.ComputeGrad_DirecandMag1(aa.numoctaves,Gaussianpyr1);
	bb.AssignTheMainOrientation1(aa.numoctaves,Gaussianpyr1,bb.mag_pyr1,bb.grad_pyr1);//�����ֵ����
	bb.ExtractFeatureDescriptors1(aa.numoctaves,Gaussianpyr1);//����������
	
	//�ڶ���
	imageptocy55=aa.palnetocylinder1(imagefive);
	imageptocy5=cutleftimage(imageptocy55);
	step1(imageptocy5);//�����ײ������
	Gaussianpyr2=bb.BuildGaussianOctaves2(tempMat1);//����˫������
	int keycount7=bb.DetectKeypoint2(aa.numoctaves,Gaussianpyr2);
	//cvCopy(imageptocy2,image1,NULL);
	//bb.DisplayKeypointLocation2(image1,Gaussianpyr2);
	
	bb.ComputeGrad_DirecandMag2(aa.numoctaves,Gaussianpyr2);
	bb.AssignTheMainOrientation2(aa.numoctaves,Gaussianpyr2,bb.mag_pyr2,bb.grad_pyr2);//�����ֵ����
	
	bb.ExtractFeatureDescriptors2(aa.numoctaves,Gaussianpyr2);//����������
	
	stitch1(imageok1,imageptocy55);

	if (imageptocy55!=NULL)
	{
		cvReleaseImage(&imageptocy55);
	}

	if (imagefive!=NULL)
	{
		cvReleaseImage(&imagefive);
	}
	if (Gaussianpyr1!=NULL)
	{
		Gaussianpyr1=NULL;
	}
	if (Gaussianpyr2!=NULL)
	{
		Gaussianpyr2=NULL;
	}


	//�����ƴ��
	//��һ��
/*	if (imageok1!=NULL)
	{
		cvReleaseImage(&imageok1);
	}
	
	imageok1=cvCreateImage(cvGetSize(bb.image33),bb.image33->depth,bb.image33->nChannels);
	cvCopy(bb.image33,imageok1,NULL);
	
	
	imageptocy1=cutrightimage(imageok1);
	step1(imageptocy1);//�����ײ������
	Gaussianpyr1=bb.BuildGaussianOctaves1(tempMat1);//����˫������
	int keycount7=bb.DetectKeypoint1(aa.numoctaves,Gaussianpyr1);
	//cvCopy(imageptocy2,image1,NULL);
	//bb.DisplayKeypointLocation2(image1,Gaussianpyr2);
	
	bb.ComputeGrad_DirecandMag1(aa.numoctaves,Gaussianpyr1);
	bb.AssignTheMainOrientation1(aa.numoctaves,Gaussianpyr1,bb.mag_pyr1,bb.grad_pyr1);//�����ֵ����
	bb.ExtractFeatureDescriptors1(aa.numoctaves,Gaussianpyr1);//����������
	
	//�ڶ���
	imageptocy66=aa.palnetocylinder1(imagesix);
	imageptocy6=cutleftimage(imageptocy66);
	step1(imageptocy6);//�����ײ������
	Gaussianpyr2=bb.BuildGaussianOctaves2(tempMat1);//����˫������
	int keycount7=bb.DetectKeypoint2(aa.numoctaves,Gaussianpyr2);
	//cvCopy(imageptocy2,image1,NULL);
	//bb.DisplayKeypointLocation2(image1,Gaussianpyr2);
	
	bb.ComputeGrad_DirecandMag2(aa.numoctaves,Gaussianpyr2);
	bb.AssignTheMainOrientation2(aa.numoctaves,Gaussianpyr2,bb.mag_pyr2,bb.grad_pyr2);//�����ֵ����
	
	bb.ExtractFeatureDescriptors2(aa.numoctaves,Gaussianpyr2);//����������
	
	stitch1(imageok1,imageptocy66);
	
	if (imageptocy66!=NULL)
	{
		cvReleaseImage(&imageptocy66);
	}
	
	if (imagesix!=NULL)
	{
		cvReleaseImage(&imagesix);
	}
	if (Gaussianpyr1!=NULL)
	{
		Gaussianpyr1=NULL;
	}
	if (Gaussianpyr2!=NULL)
	{
		Gaussianpyr2=NULL;
	}*/


	
	IplImage* dst1=NULL;
	dst1=cvCreateImage(cvGetSize(bb.image33),bb.image33->depth,bb.image33->nChannels);
	cvCopy(bb.image33,dst1,NULL);
	
//	cvSaveImage("D:/fullimag.jpg",bb.image33);
	float wscale = 0.9;		
    float hscale = 0.9;
    CvSize dst1_cvsize;	
	dst1_cvsize.width = bb.image33->width * wscale;		//Ŀ��ͼ��Ŀ�ΪԴͼ����scale��
    dst1_cvsize.height = bb.image33->height * hscale;	//Ŀ��ͼ��ĸ�ΪԴͼ��ߵ�scale��
	
    dst1 = cvCreateImage( dst1_cvsize, bb.image33->depth, bb.image33->nChannels);	//����Ŀ��ͼ��
    cvResize(bb.image33, dst1, CV_INTER_LINEAR);	//����Դͼ��Ŀ��ͼ��	
	cvNamedWindow( "ȫ��ͼ",   CV_WINDOW_AUTOSIZE );	//����������ʾĿ��ͼ��Ĵ���	
    cvShowImage( "ȫ��ͼ", dst1 );		//��ʾĿ��ͼ��
	cvMoveWindow( "ȫ��ͼ",0,500);
	cvWaitKey(-1);
    cvReleaseImage(&dst1);	//�ͷ�Ŀ��ͼ��ռ�õ��ڴ�
   	cvDestroyWindow( "ȫ��ͼ" );	//���ٴ��ڡ�dst��

}

////////////////////////////////////////////////////////////////////////////////////////////
void imagefull::ShowImg(IplImage*img)
{
  
   cvNamedWindow("showpic",CV_WINDOW_AUTOSIZE);
   cvShowImage("showpic",img);
   //system("pause");
   while(cvWaitKey(1) != ' ')
	;
   //cvWaitKey(200);
   cvDestroyWindow("showpic");

}
void imagefull::detect_and_draw( IplImage* img ,int in_or_check)
{
    static CvScalar colors[] =
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
    };

//	IplImage* img1,*dst,*con_dst;
	IplImage* img1,*dst;
	CvSize size;//IplImage* detectFace;
	CvMat* map1,*map2;
	CvRect* r1;
	CvRect rect;
    double scale = 1.3;
    IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
    IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
                         cvRound (img->height/scale)),
                     8, 1 );
    int i;
    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvResize( gray, small_img, CV_INTER_LINEAR );
    cvEqualizeHist( small_img, small_img );
    cvClearMemStorage( storage );
   ///gavin add
    con_dst = cvCreateImage(cvSize(con_width,con_height),8,3);///very importance
//    ShowImg(img);
 //  printf("Please enter the path of save img!\n");
        //char Img_Save[path_len];
        //scanf("%s",Img_Save);
        string path_copy;
        //cin>>path_copy;
		if(in_or_check == 1)//����γɵ�ģ���
		{
			path_copy = con_save;
		}
		else if(in_or_check == 2)//ƥ���õ���ʱĿ¼
		{
			path_copy = con_check;
		}
    if( cascade )
    {
        double t = (double)cvGetTickCount();
        CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,
                                            1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
                                            cvSize(30, 30) );
        t = (double)cvGetTickCount() - t;
        printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
//        ShowImg(img);
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
			
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
            CvPoint pt1,pt2;
            int radius;
            pt1.x = cvRound((r->x)*scale);
            pt1.y = cvRound((r->y)*scale);
            pt2.x = cvRound((r->x + r->width)*scale);
            pt2.y = cvRound((r->y + r->height)*scale);
//            printf("pt1 %d %d  pt2 %d %d\n",pt1.x,pt1.y,pt2.x,pt2.y);
            rect.x = min(pt1.x,pt2.x);
            rect.y = min(pt1.y,pt2.y);
            rect.width = abs(pt1.x-pt2.x);
            rect.height = abs(pt1.y-pt2.y);
//            printf(" cvrect = %d %d wh %d %d\n",rect.x,rect.y,rect.width,rect.height);
            dst = cvCreateImage(cvSize(rect.width,rect.height),8,3);///very importance
//            cvNamedWindow("img",CV_WINDOW_AUTOSIZE);
//            cvNamedWindow("dst",CV_WINDOW_AUTOSIZE);
           
            cvSetImageROI(img,rect);
            cvCopy(img,dst);
            cvResetImageROI(img);///����ROI
            cvResize(dst,con_dst, CV_INTER_LINEAR);
			path_save = path_copy;

			if(in_or_check == 1)
            {
                ShowImg(con_dst);
			
            }
	
           /***
           �����Ĺ��� 2014��2��26
           �������ݿ⣬in_or_check = 1 ����������
           in_or_check = 2 ��ƥ�� 
           ***/
			if(in_or_check == 2)
			{
				char int_to_char[10];
				itoa(i+1,int_to_char,10);
				path_save += int_to_char;
				path_save += ".jpg";
				cvSaveImage(path_save.c_str(),con_dst);
			}
			
		/*		path_save += index;
                path_save += ".jpg";
				data_in_mysql(stu_id,index,path_save);///less a fucntion
				cvSaveImage(path_save.c_str(),con_dst); /// save the picture
		*/   
        
//			cerr<<path_save<<endl;
            //get_File_Name(Save_File_Name,Img_Save,i+1);
            //printf("%s\n",Save_File_Name);
          //  cvSaveImage(path_save.c_str(),con_dst);
//            ShowImg(con_dst);
//            cvShowImage("img",img);
//            cvShowImage("dst",dst);
//            cvWaitKey(0);
//            cvDestroyWindow("img");
//            cvDestroyWindow("dst");
            radius = cvRound((r->width + r->height)*0.25*scale);
			if(in_or_check == 3)///just show the picture of detect and draw
			{
				 cvRectangle( img, pt1, pt2, colors[i%2], 2, 8, 0 );
			}
           
        }
    }
	if(in_or_check == 3)
	{
		ShowImg(img);
	}
	//ShowImg(img);
/*	string tt = con_save;
	++num;
	char ks[10];
	itoa(num,ks,10);
	tt += ks;
	tt += ".jpg";
	cvSaveImage(tt.c_str(),img);
	*/
   // cvShowImage( "result", img );
   // cvReleaseImage( &gray );
   // cvReleaseImage( &small_img );
}
bool imagefull::SQL_query(string data_query)
{
	//cout<<data_query<<endl;
	int x=1;
    if(mysql_query(&mydata,data_query.c_str()) == 0)
    {
   //     cerr<<"query success!"<<endl;
		x=3;
		return 1;
    }
    else 
    {
		x=4;
     //   cerr<<"query failed!"<<endl;
		return 0;
    }
	int y=x;
}
void imagefull::data_in_mysql(string stu_id,string index,string path_save)
{
   string data_query="";
   data_query = "insert into img_table(img_name,stu_id) values (";
  // data_query += index;
   data_query += "'";
   data_query += index;
   data_query += ".jpg',";
   data_query += stu_id;
   data_query += ")";
 //  cerr<<"query:"<<endl;
 //  cerr<<data_query<<endl;
   SQL_query(data_query);
}
IplImage* imagefull::RESIZE_PIC(IplImage*img)
{
	CvSize dstsize;
	if(img->width<1000)
		return img;
	float res = 1000.0/img->width;

	dstsize.width = img->width*res;
	dstsize.height = img->height*res;
	IplImage*dst = cvCreateImage( dstsize, img->depth, img->nChannels );
	cvResize(img,dst, CV_INTER_LINEAR);
	return dst;
}

void imagefull::Draw(string path_name,int fun_choose)
{
//	cerr<<path_name<<endl;
      cascade_name = "haarcascade_frontalface_alt2.xml";
      cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
      storage = cvCreateMemStorage(0);
      IplImage* image = cvLoadImage( path_name.c_str(), 1 );
	  image = RESIZE_PIC(image);
	  //ShowImg(image);
      if( image )
        {
            detect_and_draw( image,fun_choose );
            cvReleaseImage( &image );
        }
		
}

/////////////////////ƥ��
CvMat* imagefull::Load_Image_And_Training(int Training_Num,const char*Img_Path,bool sam)
{
  IplImage* dst=0;
  //char name[55],ID[20];
  CvMat Row_Header,*Row,*Train_Mat;
  string name;
  Train_Mat = cvCreateMat(Training_Num,con_width*con_height,CV_32FC1);
  for(int i=0;i<Training_Num;++i)
  {
    //strcpy(name,Img_Path);
	  name = Img_Path;
    if(sam)
    {
	  name += pic_name[i];
	  //name += ".jpg";
      //itoa(i+1,ID,10); ///turn to 10 char
      //strcat(name,ID);
      //strcat(name,".jpg");
    }
    else
    {
//      itoa(5,ID,10); ///turn to 10 char
//      strcat(name,ID);
//      strcat(name,".jpg");
    }
    printf("ooo___%s\n",name.c_str());
    dst = cvLoadImage(name.c_str(),0);  ///��Ҫ��0��ͨ������
    CvMat* mat = cvCreateMat(dst->height,dst->width,CV_32FC1);
//    ShowImg(dst);
    cvConvert(dst,mat);///turn picture to Mat
    Row = cvReshape(mat,&Row_Header,0,1); ///ת��һ��

    float* ptr=(float*)(Train_Mat->data.fl+i*Train_Mat->step/4);
    float* _ptr=(float*)Row->data.fl;

    for(int j=0;j<Train_Mat->cols;++j) ///��ͼƬ����ѵ������
    {
      *ptr = *_ptr;
      ++ptr;
      ++_ptr;
    }
  }
  return Train_Mat;
}
void imagefull::getSample_NUM(int&num,char*ss)
{
	  long handle;
	  struct _finddata_t fileinfo;
	  string path = ss;
     path += "*.jpg";
	 num = 0;
	 pic_name.clear();
	  handle = _findfirst(path.c_str(),&fileinfo);
	  if(handle == -1)
		return ;
	  pic_name.push_back(fileinfo.name);
//	  cout<<fileinfo.name<<endl;
		  ++num;
	  while(!_findnext(handle,&fileinfo))
	  { 
		  ++num;
//		cout<<fileinfo.name<<endl;
		pic_name.push_back(fileinfo.name);
	  }
	  _findclose(handle);

}
void imagefull::UPDATE_SQL_CEHCK(string name/*,string course_id,string class_id*/)
{
	/**********************************************************************
	 �õ�stu_id
	**********************************************************************/
	string sql_s = "select stu_id from img_table where img_name = '";
		sql_s += name;
		sql_s += "'";
//		cerr<<sql_s<<endl;
		MYSQL_RES* result = NULL;
	string stu_id,class_id,course_id;

    if(!SQL_query(sql_s))
       return;

     result = mysql_store_result(&mydata);
     int row_num = mysql_num_rows(result);
//     cerr<<"row count"<<row_num<<endl;
     unsigned int field_num = mysql_num_fields(result);
     MYSQL_FIELD* field = NULL;
     for(unsigned int i=0;i<field_num;++i)
     {
         field = mysql_fetch_field_direct(result,i);
//         cerr<<field->name<<"\t\t";
     }
     //��ӡ����
     MYSQL_ROW row = NULL;
     row = mysql_fetch_row(result);
     while(row != NULL)
     {
         for(int i=0;i<field_num;++i)
         {
//             cout<<row[i]<<"\t\t";
			 stu_id = row[i];
         }
//         cout<<endl;
         row = mysql_fetch_row(result);
     }
	 /*********************************************************
	 ��stu_id �� course_id
	 2014/3/7
	 *********************************************************/
	sql_s = "select course_id from course_table where stu_id = '";
		sql_s += stu_id;
		sql_s += "'";
//		cerr<<sql_s<<endl;
		result = NULL;

    if(!SQL_query(sql_s))
       return;

     result = mysql_store_result(&mydata);
     row_num = mysql_num_rows(result);
//     cerr<<"row count"<<row_num<<endl;
      field_num = mysql_num_fields(result);
      field = NULL;
     for(unsigned int ii=0;ii<field_num;++ii)
     {
         field = mysql_fetch_field_direct(result,ii);
//         cerr<<field->name<<"\t\t";
     }
     //��ӡ����
     row = NULL;
     row = mysql_fetch_row(result);
     while(row != NULL)
     {
         for(int i=0;i<field_num;++i)
         {
//             cout<<row[i]<<"\t\t";
			 course_id = row[i];
         }
//         cout<<endl;
         row = mysql_fetch_row(result);
     }
	 /**************************************************
	 ��stu_id �õ� class_id 2014/3/7
	 **************************************************/
	sql_s = "select class_id from grade_table where stu_id = '";
		sql_s += stu_id;
		sql_s += "'";
//		cerr<<sql_s<<endl;
		 result = NULL;

    if(!SQL_query(sql_s))
       return;

     result = mysql_store_result(&mydata);
     row_num = mysql_num_rows(result);
//     cerr<<"row count"<<row_num<<endl;
      field_num = mysql_num_fields(result);
      field = NULL;
     for(unsigned int iii=0;iii<field_num;++iii)
     {
         field = mysql_fetch_field_direct(result,iii);
//         cerr<<field->name<<"\t\t";
     }
     //��ӡ����
     row = NULL;
     row = mysql_fetch_row(result);
     while(row != NULL)
     {
         for(int i=0;i<field_num;++i)
         {
//             cout<<row[i]<<"\t\t";
			 class_id = row[i];
         }
//         cout<<endl;
         row = mysql_fetch_row(result);
     }
	 /**************************************************************/
	sql_s = "insert into check_table(stu_id,course_id,date,class_id,arrive) values(";
	sql_s += stu_id;
	sql_s += ",";
	sql_s += course_id;
	sql_s += ",now(),";
	sql_s += class_id;
	sql_s += ",1)";
//	cerr<<sql_s<<endl;
	SQL_query(sql_s);
     mysql_free_result(result);
		
}
void imagefull::MatchWhoPCA(const char*path_who)///can add path or number
{
  //  printf("enter the path of Who match!\n");
 //   char path_who[path_len];
  //  scanf("%s",path_who);
	/*******show_pic_who_to_match*********/
	IplImage* pic_to_show = cvLoadImage(path_who,CV_LOAD_IMAGE_ANYCOLOR);
	ShowImg(pic_to_show);
    CvMat* Unkonw = Load_Image_And_Training(1,path_who/*ID_Student*/,0);
    CvMat* result2 = cvCreateMat(Unkonw->rows,min(Sample->rows,Sample->cols),CV_32FC1);
           cvProjectPCA( Unkonw,avg,eigenvectors,result2 );
    	float* dif = new float[result->rows];
      float* _dif = dif;
      float* t_free = dif;
      float* resptr1,*resptr2;
      float sum;
      for(int i=0;i<result->rows;++i)
      {
          sum = 0.0;
          resptr1=(float*)result->data.fl+i*result->step/4;
          resptr2=(float*)result2->data.fl;
          for(int j=0;j<result->cols;++j)
          {
            sum += (float)(*resptr1-*resptr2)*(*resptr1-*resptr2);
            resptr1++; resptr2++;
          }
        *dif = sum;
        printf("--%d %f\n",i+1,sum);
        dif++;
      }

      int dex=1;                           //���������Ǵ�1��ʼ��
      float temp=*_dif;
      printf("besgin: %f\n",temp);
      for(int k=1;k<result->rows;k++)
      {
          _dif++;
          if(temp>*_dif)
          {
            printf("temp= %f _dif= %f\n",temp,*_dif);
            dex=k+1;            //���������Ǵ�1��ʼ��
            temp=*_dif;
          }
      }
 //     printf("OK_OK_%d\n",dex);
//	  cerr<<pic_name[dex-1]<<endl;
	  ///course_id class_id

	  UPDATE_SQL_CEHCK(pic_name[dex-1]/*,"11","22"*/);//course_id,class_id
	  string show_pic = con_save + pic_name[dex-1];
	  IplImage* img = cvLoadImage(show_pic.c_str(),CV_LOAD_IMAGE_ANYCOLOR);
	  ShowImg(img);
      delete [] t_free;

}
void imagefull::PickPCA(int Sample_Num,char*Path_of_Img)//
{

         Sample = Load_Image_And_Training(Sample_Num,Path_of_Img/*ID_Student*/,1);
         avg = cvCreateMat(1,Sample->cols,CV_32FC1);
	CvMat* eigenvalues = cvCreateMat(1,min(Sample->rows,Sample->cols),CV_32FC1);
         eigenvectors = cvCreateMat(min(Sample->rows,Sample->cols),Sample->cols,CV_32FC1);
         result = cvCreateMat(Sample->rows,min(Sample->rows,Sample->cols),CV_32FC1);//���ɷ���Ŀ:min(Sample->rows,Sample->cols)

	cvCalcPCA( Sample,avg,eigenvalues,eigenvectors,CV_PCA_DATA_AS_ROW );
	cvProjectPCA( Sample,avg,eigenvectors,result );

}
void imagefull::get_detect_and_check()
{
	 long handle;
	  struct _finddata_t fileinfo;
	  string path = con_check;
	  path += "*.jpg";
	  handle = _findfirst(path.c_str(),&fileinfo);
	  if(handle == -1)
		return ;
	  path = con_check;
//	  cout<<fileinfo.name<<endl;
	  path += fileinfo.name;
	  MatchWhoPCA(path.c_str());
	  while(!_findnext(handle,&fileinfo))
	  { 
//		cout<<fileinfo.name<<endl;
		path = con_check;
		path += fileinfo.name;
		MatchWhoPCA(path.c_str());
	  }
	  _findclose(handle);
}
void imagefull::Match()
{

 //   cerr<<"enter the path of picture to check!"<<endl;

	Draw(tempname,2);
	getSample_NUM(Sample_NUM,con_save);
    PickPCA(Sample_NUM,con_save);
	get_detect_and_check();

}

//�������ݿ�
void imagefull::Mysql_link()
{
    //MYSQL mydata;
    //��ʼ�����ݿ�
    if(0==mysql_library_init(0,NULL,NULL))
         {
 //         cout<<"mysql_library_init() succeed"<<endl;
         }
         else
         {
//          cout<<"mysql_library_init() failed"<<endl;
         }

    #ifdef STEPBYSTEP
         system("pause");
        #endif

         //��ʼ�����ݽṹ
         if(NULL!=mysql_init(&mydata))
         {
    //      cout<<"mysql_init() succeed"<<endl;
         }
         else
         {
    //      cout<<"mysql_init() failed"<<endl;
         }

          //���������ݿ�֮ǰ�����ö��������ѡ��
         //�������õ�ѡ��ܶ࣬���������ַ����������޷���������
         if(0==mysql_options(&mydata,MYSQL_SET_CHARSET_NAME,"gbk"))
         {
   //       cout<<"mysql_options() succeed"<<endl;
         }
         else
         {
   //       cout<<"mysql_options() failed"<<endl;
         }

      #ifdef STEPBYSTEP
       system("pause");
      #endif

       if(!mysql_real_connect(&mydata,"localhost","root","dream","face_match",3306,NULL,0))///3307
	   {
	   
	   }
    //          printf("\nc++ link mysql fail\n");
   //    else
    //          printf("\nc++ link mysql success!\n");

      #ifdef STEPBYSTEP
       system("pause");
      #endif
}

///////////////////////////////////////////////////////////////
//1 ������⣺todraw()
void imagefull::OnButton1() 
{
	// TODO: Add your control notification handler code here
	//tempname��filename�����·��.jpg��tempname��string���͵�
    Draw(tempname,3);
}
//������������1�������⵽��������Ϣ����ģ���
//void imagefull::OnButton2() 
//{
	// TODO: Add your control notification handler code here
	//������Ϣ�Ի��������CAddDlg
 
/*	CAddDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		
			string stu_id,index;	  
			stu_id = dlg.m_stuid;
			index = dlg.m_index;
			path_save += index;
			path_save += ".jpg";
			data_in_mysql(stu_id,index,path_save);///less a fucntion
			cvSaveImage(path_save.c_str(),con_dst); /// save the picture
	
              
     }
*/	 
	/*	   else if(in_or_check == 2)
		   {
			   char ts[22];
			    itoa(i,ts,10);
				path_save += ts;
				path_save += ".jpg";
				string to_save = "insert into path_pic values('";
					to_save += path_save;
					to_save += "')";
				cerr<<to_save<<endl;
				SQL_query(to_save);
				cvSaveImage(path_save.c_str(),con_dst);
		   }
		   */

//}
//����ƥ��
void imagefull::OnButton3() 
{
	// TODO: Add your control notification handler code here
	Match();

/*	ԭdetect_and_draw�������
	 char ts[22];
	 itoa(i,ts,10);
	 path_save += ts;
	 path_save += ".jpg";
	 string to_save = "insert into path_pic values('";
	 to_save += path_save;
	 to_save += "')";
	 //cerr<<to_save<<endl;
	 SQL_query(to_save);
	 cvSaveImage(path_save.c_str(),con_dst);
*/
}
//�������ݿ�
void imagefull::OnButton5() 
{
	// TODO: Add your control notification handler code here
	CMysqlDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		Mysql_link();
	}
}

CStuDlg dlg;
//ѧ����Ϣע�᣺��Ӧԭs_table����
void imagefull::OnButton4() 
{
	// TODO: Add your control notification handler code here
	//CStuDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		string stu_id, stu_name;
		stu_id=dlg.m_stuid;
		stu_name=dlg.m_stuname;
		string data="insert into s_table(stu_id,stu_name) values(";
		data += stu_id;
		data += ",'";
		data += stu_name;
		data += "')";
		SQL_query(data);
	}
}
//�γ���Ϣ���룺��Ӧԭcourse_table����
void imagefull::OnButton6() 
{
	// TODO: Add your control notification handler code here
	CCourseDlg dlg1;
	if(dlg1.DoModal()==IDOK)
	{
		string course_id, course_name, teacher_id;
		course_id=dlg1.m_courseid;
		course_name=dlg1.m_coursename;
		teacher_id=dlg1.m_teacherid;
	
			string data="insert into course_table(course_id,course_name,teacher_id,stu_id) values(";
			data += course_id;
			data += ",'";
			data += course_name;
			data += "',";
			data += teacher_id;
			data += ",";
			data += dlg.m_stuid;
			data += ")";
			SQL_query(data);
	}
}
//�༶��Ϣ���룺��Ӧԭgrade_table����
void imagefull::OnButton7() 
{
	// TODO: Add your control notification handler code here
	CGradeDlg dlg2;
	if(dlg2.DoModal()==IDOK)
	{
		string grade_id, class_id, grade_name, class_name;
		grade_id=dlg2.m_gradeid;
		class_id=dlg2.m_classid;
		grade_name=dlg2.m_gradename;
		class_name=dlg2.m_classname;

		string data="insert into grade_table(grade_id,class_id,class_name,grade_name) values(";
		data += grade_id;
		data += ",";
		data += class_id;
		data += ",'";
		data += class_name;
		data += "','";
		data += grade_name;
		data += "')";
		SQL_query(data);
	}
}
//ͼ��ɼ�
void imagefull::OnButton8() 
{
	// TODO: Add your control notification handler code here
/*	CCaptureDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
			string stu_id,index;	  
			stu_id = dlg.m_stuid;
			index = dlg.m_index;
			path_save += index;
			path_save += ".jpg";
			data_in_mysql(stu_id,index,path_save);///less a fucntion
			cvSaveImage(path_save.c_str(),con_dst); /// save the picture
	}
	*/
		CString filename;
	string tempname;
	IplImage*imageone;
		char  szFilter[] = "Jpg Files (*.jpg)|*.jpg|All Files (*.*)|*.*||";
	CFileDialog fdlg(TRUE, "JPG", NULL, OFN_HIDEREADONLY | 

OFN_OVERWRITEPROMPT,szFilter);
	
	if(fdlg.DoModal()!=IDOK)//����һֱ�ٽ�����
	{	//	filename=fdlg.GetPathName();
		//	SetDlgItemText(IDC_EDIT4,filename);
			//UpdataData(FALSE);
	}
	//	return;
	
	filename=fdlg.GetPathName();
//	std::string tempname = (LPCSTR)CString(filename);
	tempname = (LPCSTR)CString(filename);
	const char* tmp=tempname.c_str();
	imageone=NULL;
	imageone=cvLoadImage(tmp,CV_LOAD_IMAGE_ANYCOLOR);
	
	IplImage* dst=NULL;
	dst=cvCreateImage(cvGetSize(imageone),imageone->depth,imageone->nChannels);
	cvCopy(imageone,dst,NULL);
	
	
	float wscale, hscale;		
	int tempw,temph;
	tempw=imageone->width;
	temph=imageone->height;
	wscale=350.1/tempw;
	hscale=240.0/temph;
	CvSize dst_cvsize;	
	dst_cvsize.width = imageone->width * wscale;		//Ŀ��ͼ��Ŀ�ΪԴͼ����scale��
	dst_cvsize.height = imageone->height * hscale;	//Ŀ��ͼ��ĸ�ΪԴͼ��ߵ�scale��
	
	dst = cvCreateImage( dst_cvsize, imageone->depth, imageone->nChannels);	//����Ŀ��ͼ��
	cvResize(imageone, dst, CV_INTER_LINEAR);	//����Դͼ��Ŀ��ͼ��	
	Draw(tempname.c_str(),1);
	
}
//¼��ɼ�ͼ����Ϣ
void imagefull::OnButton9() 
{
	// TODO: Add your control notification handler code here
		CAddDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
			
			string stu_id,index,path=path_save;	  
			stu_id = dlg.m_stuid;
			index = dlg.m_index;
			path += index;
			path += ".jpg";
			data_in_mysql(stu_id,index,path);///less a fucntion
			cvSaveImage(path.c_str(),con_dst); /// save the picture
	
              
     }
}
