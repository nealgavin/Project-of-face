// ;stitchimage.cpp : implementation file
//

#include "stdafx.h"
#include "imagestitch.h"
#include "stitchimage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// stitchimage dialog


stitchimage::stitchimage(CWnd* pParent /*=NULL*/)
	: CDialog(stitchimage::IDD, pParent)
{
	//{{AFX_DATA_INIT(stitchimage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void stitchimage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(stitchimage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(stitchimage, CDialog)
	//{{AFX_MSG_MAP(stitchimage)
	ON_BN_CLICKED(IDC_openone, Onopenone)
	ON_BN_CLICKED(IDC_opentwo, Onopentwo)
	ON_BN_CLICKED(IDC_palnetocy1, Onpalnetocy1)
	ON_BN_CLICKED(IDC_palnetocy2, Onpalnetocy2)
	ON_BN_CLICKED(IDC_step11, Onstep11)
	ON_BN_CLICKED(IDC_step12, Onstep12)
	ON_BN_CLICKED(IDC_step21, Onstep21)
	ON_BN_CLICKED(IDC_step22, Onstep22)
	ON_BN_CLICKED(IDC_step31, Onstep31)
	ON_BN_CLICKED(IDC_step32, Onstep32)
	ON_BN_CLICKED(IDC_step41, Onstep41)
	ON_BN_CLICKED(IDC_step42, Onstep42)
	ON_BN_CLICKED(IDC_step51, Onstep51)
	ON_BN_CLICKED(IDC_step52, Onstep52)
	ON_BN_CLICKED(IDC_siftstitch, Onsiftstitch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// stitchimage message handlers

void stitchimage::Onopenone() 
{
	// TODO: Add your control notification handler code here
	CString filename;
	char  szFilter[] = "Jpg Files (*.jpg)|*.jpg|All Files (*.*)|*.*||";
	CFileDialog fdlg(TRUE, "JPG", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	
	if(fdlg.DoModal()!=IDOK)//程序一直再进程中
	
		return;

		filename=fdlg.GetPathName();
		std::string tempname = (LPCSTR)CString(filename);
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
		dst_cvsize.width = imageone->width * wscale;		//目标图像的宽为源图象宽的scale倍
		dst_cvsize.height = imageone->height * hscale;	//目标图像的高为源图象高的scale倍
		
		dst = cvCreateImage( dst_cvsize, imageone->depth, imageone->nChannels);	//构造目标图象
		cvResize(imageone, dst, CV_INTER_LINEAR);	//缩放源图像到目标图像	
		cvNamedWindow( "图像1",   CV_WINDOW_AUTOSIZE );	//创建用于显示目标图像的窗口	
		cvShowImage( "图像1", dst );		//显示目标图像
		cvMoveWindow( "图像1",0,0);
		cvWaitKey(0);
		cvReleaseImage(&dst);	//释放目标图像占用的内存
		cvDestroyWindow( "图像1" );	//销毁窗口“dst”
	//cvReleaseImage(&image1);

	
	
	
	
	
}

void stitchimage::Onopentwo() 
{
	// TODO: Add your control notification handler code here
	CString filename;
	char  szFilter[] = "Jpg Files (*.jpg)|*.jpg|All Files (*.*)|*.*||";
	CFileDialog fdlg(TRUE, "JPG", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	
	if(fdlg.DoModal()!=IDOK)//程序一直再进程中
		return;
	filename=fdlg.GetPathName();
	std::string tempname = (LPCSTR)CString(filename);
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
	dst_cvsize.width = imagetwo->width * wscale;		//目标图像的宽为源图象宽的scale倍
    dst_cvsize.height = imagetwo->height * hscale;	//目标图像的高为源图象高的scale倍
	
    dst = cvCreateImage( dst_cvsize, imagetwo->depth, imagetwo->nChannels);	//构造目标图象
    cvResize(imagetwo, dst, CV_INTER_LINEAR);	//缩放源图像到目标图像	
	cvNamedWindow( "图像2",   CV_WINDOW_AUTOSIZE );	//创建用于显示目标图像的窗口	
    cvShowImage( "图像2", dst );		//显示目标图像
	cvMoveWindow( "图像2",360,0);
	cvWaitKey(0);
    cvReleaseImage(&dst);	//释放目标图像占用的内存
   	cvDestroyWindow( "图像2" );	//销毁窗口“dst”
	//cvReleaseImage(&image2);
}

void stitchimage::Onpalnetocy1() 
{
	// TODO: Add your control notification handler code here
	imageptocy11=aa.palnetocylinder1(imageone);
	imageptocy1=cutrightimage(imageptocy11);
//	cvSaveImage("D:/imageptocy11.jpg",imageptocy11);
	IplImage* dst3=NULL;
	dst3=cvCreateImage(cvGetSize(imageptocy1),imageptocy1->depth,imageptocy1->nChannels);
	cvCopy(imageptocy1,dst3,NULL);
	
	int widthnew,heightnew;
    widthnew=imageptocy1->width;
	heightnew=imageptocy1->height;
	float wscale ;		
    float hscale ;
	wscale=350.0/widthnew;
	hscale=240.0/heightnew;
    CvSize dst3_cvsize;	
	dst3_cvsize.width = imageptocy1->width * wscale;		//目标图像的宽为源图象宽的scale倍
    dst3_cvsize.height =imageptocy1->height * hscale;	//目标图像的高为源图象高的scale倍
	
    dst3 = cvCreateImage( dst3_cvsize, imageptocy1->depth, imageptocy1->nChannels);	//构造目标图象
    cvResize(imageptocy1, dst3, CV_INTER_LINEAR);	//缩放源图像到目标图像	
	cvNamedWindow( "柱面投影1",   CV_WINDOW_AUTOSIZE );	//创建用于显示目标图像的窗口	
    cvShowImage( "柱面投影1", dst3 );		//显示目标图像
	cvMoveWindow( "柱面投影1",0,250);

	cvWaitKey(-1);
    cvReleaseImage(&dst3);	//释放目标图像占用的内存
   	cvDestroyWindow( "柱面投影1" );	//销毁窗口“dst”

}

void stitchimage::Onpalnetocy2() 
{
	// TODO: Add your control notification handler code here
	imageptocy22=aa.palnetocylinder1(imagetwo);
	imageptocy2=cutleftimage(imageptocy22);
//	cvSaveImage("D:/imageptocy22.jpg",imageptocy22);
	
	IplImage* dst3=NULL;
	dst3=cvCreateImage(cvGetSize(imageptocy2),imageptocy2->depth,imageptocy2->nChannels);
	cvCopy(imageptocy2,dst3,NULL);
	
	int widthnew,heightnew;
    widthnew=imageptocy2->width;
	heightnew=imageptocy2->height;
	float wscale ;		
    float hscale ;
	wscale=350.0/widthnew;
	hscale=240.0/heightnew;
    CvSize dst3_cvsize;	
	dst3_cvsize.width = imageptocy2->width * wscale;		//目标图像的宽为源图象宽的scale倍
    dst3_cvsize.height =imageptocy2->height * hscale;	//目标图像的高为源图象高的scale倍
	
    dst3 = cvCreateImage( dst3_cvsize, imageptocy2->depth, imageptocy2->nChannels);	//构造目标图象
    cvResize(imageptocy2, dst3, CV_INTER_LINEAR);	//缩放源图像到目标图像	
	cvNamedWindow( "柱面投影2",   CV_WINDOW_AUTOSIZE );	//创建用于显示目标图像的窗口	
    cvShowImage( "柱面投影2", dst3 );		//显示目标图像
	cvMoveWindow( "柱面投影2",360,250);
	
	cvWaitKey(-1);
    cvReleaseImage(&dst3);	//释放目标图像占用的内存
   	cvDestroyWindow( "柱面投影2" );	//销毁窗口“dst”
}



void stitchimage::Onstep11() 
{
	// TODO: Add your control notification handler code here
	image1=NULL;
	IplImage *grey_im1=NULL;
	DoubleSizeImage1=NULL;

	CvMat *image1Mat=NULL;
	tempMat1=NULL;

	//为图像分配内存
	image1=cvCreateImage(cvSize(imageptocy1->width,imageptocy1->height),imageptocy1->depth,imageptocy1->nChannels);
	grey_im1=cvCreateImage(cvSize(imageptocy1->width,imageptocy1->height),IPL_DEPTH_8U,1);
	DoubleSizeImage1=cvCreateImage(cvSize(2*(imageptocy1->width),2*(imageptocy1->height)),IPL_DEPTH_8U,3);
	//为图像阵列分配内存，假设两幅图像的大小相同，tempMat跟随image1的大小
	image1Mat=cvCreateMat(imageptocy1->height,imageptocy1->width,CV_32FC1);
	//转化成单通道图像再处理
	cvCvtColor(imageptocy1,grey_im1,CV_BGR2GRAY);
	//转换到Mat数据结构，图像操作使用的是浮点型操作
	cvConvert(grey_im1,image1Mat);
	
	//double t=(double)cvGetTickCount();
	
	//图像归一化
	cvConvertScale(image1Mat,image1Mat,1.0/255,0);

	int dim;
	dim=min(image1Mat->rows,image1Mat->cols);
	//金字塔阶数
	aa.numoctaves=(int) (log((double)dim) / log(2.0))-2;
	aa.numoctaves=min(aa.numoctaves,MAXOCTAVES);
	
	//step1预滤波除噪声，建立金字塔底层，底层为原图像的两倍
	tempMat1=aa.ScaleInitImage(image1Mat);

//	cvReleaseImage(& image1);
	cvReleaseImage(& grey_im1);
	cvReleaseMat(& image1Mat);

	//*******平滑滤波后的图像保存主要为了调试试验
	/*IplImage *tempimage=NULL;
	tempimage=cvCreateImage(cvSize(tempMat1->width,tempMat1->height),IPL_DEPTH_8U,1);
	cvConvertScale(tempMat1,tempMat1,255.0,0);
	cvConvertScaleAbs(tempMat1,tempimage,1,0);
	
	cvSaveImage("D:/tempimage1.jpg",tempimage);*/
	//cvReleaseImage(& tempimage);
	//*******end


}

void stitchimage::Onstep12() 
{
	// TODO: Add your control notification handler code here
	image2=NULL;
	IplImage *grey_im1=NULL;
	DoubleSizeImage2=NULL;

	CvMat *image1Mat=NULL;
	tempMat2=NULL;

	//为图像分配内存
	image2=cvCreateImage(cvSize(imageptocy2->width,imageptocy2->height),imageptocy2->depth,imageptocy2->nChannels);
	grey_im1=cvCreateImage(cvSize(imageptocy2->width,imageptocy2->height),IPL_DEPTH_8U,1);
	DoubleSizeImage2=cvCreateImage(cvSize(2*(imageptocy2->width),2*(imageptocy2->height)),IPL_DEPTH_8U,3);
	//为图像阵列分配内存，假设两幅图像的大小相同，tempMat跟随image1的大小
	image1Mat=cvCreateMat(imageptocy2->height,imageptocy2->width,CV_32FC1);
	//转化成单通道图像再处理
	cvCvtColor(imageptocy2,grey_im1,CV_BGR2GRAY);
	//转换到Mat数据结构，图像操作使用的是浮点型操作
	cvConvert(grey_im1,image1Mat);
	
	//double t=(double)cvGetTickCount();
	
	//图像归一化
	cvConvertScale(image1Mat,image1Mat,1.0/255,0);

	int dim;
	dim=min(image1Mat->rows,image1Mat->cols);
	//金字塔阶数
	aa.numoctaves=(int) (log((double)dim) / log(2.0))-2;
	aa.numoctaves=min(aa.numoctaves,MAXOCTAVES);
	
	//step1预滤波除噪声，建立金字塔底层，底层为原图像的两倍
	tempMat2=aa.ScaleInitImage(image1Mat);

	//cvReleaseImage(& image2);
	cvReleaseImage(& grey_im1);
	cvReleaseMat(& image1Mat);

	//*******平滑滤波后的图像保存主要为了调试试验
	/*IplImage *tempimage=NULL;
	tempimage=cvCreateImage(cvSize(tempMat2->width,tempMat2->height),IPL_DEPTH_8U,1);
	cvConvertScale(tempMat2,tempMat2,255.0,0);
	cvConvertScaleAbs(tempMat2,tempimage,1,0);
	
	cvSaveImage("D:/tempimage2.jpg",tempimage);*/
	//cvReleaseImage(& tempimage);
	//*******end
}

IplImage* stitchimage::cutrightimage(IplImage *image)
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
/*void stitchimage::cutrightimage(IplImage * image)
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
	

	
	imageptocy1=cvCreateImage(cvGetSize(temp),temp->depth,temp->nChannels);
	cvCopy(temp,imageptocy1,NULL);
	cvReleaseImage(&temp);

}*/

IplImage* stitchimage::cutleftimage(IplImage *image)
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

/*void stitchimage::cutleftimage(IplImage * image)
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
	

	
	imageptocy2=cvCreateImage(cvGetSize(temp),temp->depth,temp->nChannels);
	cvCopy(temp,imageptocy2,NULL);
	cvReleaseImage(&temp);
	
	//cvSaveImage("D:\cutimage.jpg",imageptocy2);
	
	


}*/

ImageOctaves * stitchimage::BuildGaussianOctaves1(CvMat * image)
{
	ImageOctaves *octaves;
	CvMat *tempMat11;
	CvMat *dst;

	CvMat *temp1;
	int i,j;
	double k=pow(2,1.0/((float)SCALESPEROCTAVE));//SCALESPEROCTAVE=2
	float preblur_sigma,initial_sigma,sigma1,sigma2,sigma,absolute_sigma,sigma_f;
	//计算金字塔的阶梯数目
	int dim=min(image->rows,image->cols);
	//金字塔阶数
	int numoctaves=(int)(log((double) dim) / log(2.0))-2;

	//限定金字塔的阶梯数
	numoctaves=min(numoctaves,MAXOCTAVES);//MAXOCTAVES=4
	//为高斯金字塔和DOG金字塔分配内存
	octaves=(ImageOctaves*) malloc( numoctaves * sizeof(ImageOctaves));
	DOGoctaves1=(ImageOctaves*) malloc( numoctaves * sizeof(ImageOctaves));
	//初始化原图像
	tempMat11=cvCloneMat(image);
	//preblur_sigma = 1.0;//sqrt(2 - 4*INITSIGMA*INITSIGMA),INITSIGMA=0.5;
    initial_sigma = sqrt(2);//sqrt( (4*INITSIGMA*INITSIGMA) + preblur_sigma * preblur_sigma );
    //initial_sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA * 4);
	

	

	//在每一阶金字塔图像中建立不同的尺度图像
	for (i=0;i<numoctaves;i++)
	{
		//首先建立金字塔每一阶梯的最底层，其中0阶梯的最底层已经建立好
		//为各个阶梯分配内存
		octaves[i].Octave=(ImageLevels*) malloc((SCALESPEROCTAVE+3) * sizeof(ImageLevels));
		DOGoctaves1[i].Octave=(ImageLevels*) malloc((SCALESPEROCTAVE+2) * sizeof(ImageLevels));
		//存储各个阶梯的最底层
		(octaves[i].Octave)[0].Level=tempMat11;
		octaves[i].col=tempMat11->cols;
		octaves[i].row=tempMat11->rows;
		DOGoctaves1[i].col=tempMat11->cols;
		DOGoctaves1[i].row=tempMat11->rows;
		
		

		if (DOUBLE_BASE_IMAGE_SIZE)//DOUBLE_BASE_IMAGE_SIZE=1
		{
			octaves[i].subsample=pow(2,i);
		}
		else
		{
			octaves[i].subsample=pow(2,i);
		}

		if (i==0)
		{
			(octaves[0].Octave)[0].levelsigma=initial_sigma;
			(octaves[0].Octave)[0].absolute_sigma = initial_sigma;
		}
		else
		{
			(octaves[i].Octave)[0].levelsigma=(octaves[i-1].Octave)[SCALESPEROCTAVE].levelsigma;
			(octaves[i].Octave)[0].absolute_sigma=(octaves[i-1].Octave)[SCALESPEROCTAVE].absolute_sigma;

		}
		sigma=initial_sigma;//sqrt(2)
		//建立本阶梯其他层图像
		for (j=1;j<SCALESPEROCTAVE+3;j++)
		{
			dst=cvCreateMat(tempMat11->rows,tempMat11->cols,CV_32FC1);//用于存储高斯层
			temp1=cvCreateMat(tempMat11->rows,tempMat11->cols,CV_32FC1);//用于存储DOG层
			//			if(i!=0)
			//			{
			//			    sigma1 = pow(k, j - 1) * ((octaves[i-1].Octave)[j-1].levelsigma);
			//		        sigma2 = pow(k, j) * ((octaves[i].Octave)[j-1].levelsigma);
			//			    sigma = sqrt(sigma2*sigma2 - sigma1*sigma1);
			sigma_f= sqrt(k*k-1)*sigma;//k=sqrt(2),sigma=sqrt(2),sigma_f=sqrt(2)
			//			}
			//			else
			//			{
			//			    sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA * 4)*pow(k,j);
			//			}		
            sigma = k*sigma;//sigma=2
			absolute_sigma=sigma*(octaves[i].subsample);//octaves[0].subsample=0.5
			(octaves[i].Octave)[j].levelsigma=sigma;
			(octaves[i].Octave)[j].absolute_sigma=absolute_sigma;

			
			
			
			
			
			//产生高斯层
			int length=aa.BlurImage((octaves[i].Octave)[j-1].Level,dst,sigma_f);//相应尺度
			(octaves[i].Octave)[j].levelsigmalength=length;//返回尺度大小
			(octaves[i].Octave)[j].Level=dst;//
			
	

			
			//产生DOG层
			cvSub(((octaves[i].Octave)[j]).Level,((octaves[i].Octave)[j-1]).Level,temp1,0);
			cvAbsDiff(((octaves[i].Octave)[j]).Level,((octaves[i].Octave)[j-1]).Level,temp1);
			((DOGoctaves1[i].Octave)[j-1]).Level=temp1;
		}

	

		
		tempMat11=aa.halfSizeImage(( (octaves[i].Octave)[SCALESPEROCTAVE].Level ));

	/*	IplImage *mosaic11=NULL;
		mosaic11=cvCreateImage(cvSize(dst->width,dst->height),IPL_DEPTH_8U,1);
		cvConvertScale(dst,dst,255.0,0);
		cvConvertScaleAbs(dst,mosaic11,1,0);
	        cvSaveImage("D:\GaussianPyramid of me.jpg",mosaic11);*/
		
		
		
	

	}
	cvReleaseMat(&tempMat11);
	cvReleaseMat(&dst);
//	cvReleaseMat(&temp1);

	return octaves;

}


ImageOctaves * stitchimage::BuildGaussianOctaves2(CvMat * image)
{
	ImageOctaves *octaves;
	CvMat *tempMat11;
	CvMat *dst;

	CvMat *temp1;
	int i,j;
	double k=pow(2,1.0/((float)SCALESPEROCTAVE));//SCALESPEROCTAVE=2
	float preblur_sigma,initial_sigma,sigma1,sigma2,sigma,absolute_sigma,sigma_f;
	//计算金字塔的阶梯数目
	int dim=min(image->rows,image->cols);
	//金字塔阶数
	int numoctaves=(int)(log((double) dim) / log(2.0))-2;

	//限定金字塔的阶梯数
	numoctaves=min(numoctaves,MAXOCTAVES);//MAXOCTAVES=4
	//为高斯金字塔和DOG金字塔分配内存
	octaves=(ImageOctaves*) malloc( numoctaves * sizeof(ImageOctaves));
	DOGoctaves2=(ImageOctaves*) malloc( numoctaves * sizeof(ImageOctaves));
	//初始化原图像
	tempMat11=cvCloneMat(image);
	//preblur_sigma = 1.0;//sqrt(2 - 4*INITSIGMA*INITSIGMA),INITSIGMA=0.5;
    initial_sigma = sqrt(2);//sqrt( (4*INITSIGMA*INITSIGMA) + preblur_sigma * preblur_sigma );
    //initial_sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA * 4);
	

	

	//在每一阶金字塔图像中建立不同的尺度图像
	for (i=0;i<numoctaves;i++)
	{
		//首先建立金字塔每一阶梯的最底层，其中0阶梯的最底层已经建立好
		//为各个阶梯分配内存
		octaves[i].Octave=(ImageLevels*) malloc((SCALESPEROCTAVE+3) * sizeof(ImageLevels));
		DOGoctaves2[i].Octave=(ImageLevels*) malloc((SCALESPEROCTAVE+2) * sizeof(ImageLevels));
		//存储各个阶梯的最底层
		(octaves[i].Octave)[0].Level=tempMat11;
		octaves[i].col=tempMat11->cols;
		octaves[i].row=tempMat11->rows;
		DOGoctaves2[i].col=tempMat11->cols;
		DOGoctaves2[i].row=tempMat11->rows;
		
		

		if (DOUBLE_BASE_IMAGE_SIZE)//DOUBLE_BASE_IMAGE_SIZE=1
		{
			octaves[i].subsample=pow(2,i);
		}
		else
		{
			octaves[i].subsample=pow(2,i);
		}

		if (i==0)
		{
			(octaves[0].Octave)[0].levelsigma=initial_sigma;
			(octaves[0].Octave)[0].absolute_sigma = initial_sigma;
		}
		else
		{
			(octaves[i].Octave)[0].levelsigma=(octaves[i-1].Octave)[SCALESPEROCTAVE].levelsigma;
			(octaves[i].Octave)[0].absolute_sigma=(octaves[i-1].Octave)[SCALESPEROCTAVE].absolute_sigma;

		}
		sigma=initial_sigma;//sqrt(2)
		//建立本阶梯其他层图像
		for (j=1;j<SCALESPEROCTAVE+3;j++)
		{
			dst=cvCreateMat(tempMat11->rows,tempMat11->cols,CV_32FC1);//用于存储高斯层
			temp1=cvCreateMat(tempMat11->rows,tempMat11->cols,CV_32FC1);//用于存储DOG层
			//			if(i!=0)
			//			{
			//			    sigma1 = pow(k, j - 1) * ((octaves[i-1].Octave)[j-1].levelsigma);
			//		        sigma2 = pow(k, j) * ((octaves[i].Octave)[j-1].levelsigma);
			//			    sigma = sqrt(sigma2*sigma2 - sigma1*sigma1);
			sigma_f= sqrt(k*k-1)*sigma;//k=sqrt(2),sigma=sqrt(2),sigma_f=sqrt(2)
			//			}
			//			else
			//			{
			//			    sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA * 4)*pow(k,j);
			//			}		
            sigma = k*sigma;//sigma=2
			absolute_sigma=sigma*(octaves[i].subsample);//octaves[0].subsample=0.5
			(octaves[i].Octave)[j].levelsigma=sigma;
			(octaves[i].Octave)[j].absolute_sigma=absolute_sigma;

			
			
			
			
			
			//产生高斯层
			int length=aa.BlurImage((octaves[i].Octave)[j-1].Level,dst,sigma_f);//相应尺度
			(octaves[i].Octave)[j].levelsigmalength=length;//返回尺度大小
			(octaves[i].Octave)[j].Level=dst;//
			
	

			
			//产生DOG层
			cvSub(((octaves[i].Octave)[j]).Level,((octaves[i].Octave)[j-1]).Level,temp1,0);
			cvAbsDiff(((octaves[i].Octave)[j]).Level,((octaves[i].Octave)[j-1]).Level,temp1);
			((DOGoctaves2[i].Octave)[j-1]).Level=temp1;
		}

	

		
		tempMat11=aa.halfSizeImage(( (octaves[i].Octave)[SCALESPEROCTAVE].Level ));

/*		IplImage *mosaic11=NULL;
		mosaic11=cvCreateImage(cvSize(dst->width,dst->height),IPL_DEPTH_8U,1);
		cvConvertScale(dst,dst,255.0,0);
		cvConvertScaleAbs(dst,mosaic11,1,0);
	        cvSaveImage("D:\GaussianPyramid of me.jpg",mosaic11);*/
		
		
		
	

	}
	cvReleaseMat(&tempMat11);
	cvReleaseMat(&dst);
//	cvReleaseMat(&temp1);//释放就出错
	return octaves;

}
void stitchimage::Onstep21() 
{
	// TODO: Add your control notification handler code here
	//step2建立Guassian金字塔和DOG金字塔
	Gaussianpyr1=BuildGaussianOctaves1(tempMat1);

	//显示高斯图像
/*	CvMat *mosaicHorizen1=NULL;
	CvMat *mosaicHorizen2=NULL;
	CvMat *mosaicVertical1=NULL;
#define ImLevels(OCTAVE,LEVEL,ROW,COL) ((float *)(Gaussianpyr1[(OCTAVE)].Octave[(LEVEL)].Level->data.fl +Gaussianpyr1[(OCTAVE)].Octave[(LEVEL)].Level->step/sizeof(float) *(ROW)))[(COL)]
	
	for (int i=0;i<aa.numoctaves;i++)
	{
		if (i==0)
		{
			mosaicHorizen1=aa.MosaicHorizen((Gaussianpyr1[0].Octave)[0].Level,(Gaussianpyr1[0].Octave)[1].Level);
			for(int j=2;j<SCALESPEROCTAVE+3;j++)
				mosaicHorizen1=aa.MosaicHorizen( mosaicHorizen1, (Gaussianpyr1[0].Octave)[j].Level);
			for(j=0;j<NUMSIZE;j++)
				mosaicHorizen1=aa.halfSizeImage(mosaicHorizen1);
			
		}
		else if (i==1)
		{
			mosaicHorizen2=aa.MosaicHorizen((Gaussianpyr1[1].Octave)[0].Level, (Gaussianpyr1[1].Octave)[1].Level);
			for(int j=2;j<SCALESPEROCTAVE+3;j++)
				mosaicHorizen2=aa.MosaicHorizen(mosaicHorizen2, (Gaussianpyr1[1].Octave)[j].Level );
			for(j=0;j<NUMSIZE;j++)
				mosaicHorizen2=aa.halfSizeImage(mosaicHorizen2);
			mosaicVertical1=aa.MosaicVertical( mosaicHorizen1, mosaicHorizen2 );
			
		}
		else
		{
			mosaicHorizen1=aa.MosaicHorizen( (Gaussianpyr1[i].Octave)[0].Level, (Gaussianpyr1[i].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+3;j++)
				mosaicHorizen1=aa.MosaicHorizen( mosaicHorizen1, (Gaussianpyr1[i].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen1=aa.halfSizeImage(mosaicHorizen1);
			mosaicVertical1=aa.MosaicVertical( mosaicVertical1, mosaicHorizen1 );
		}
	}
	IplImage *mosaic1=NULL;
	mosaic1=cvCreateImage(cvSize(mosaicVertical1->width,mosaicVertical1->height),IPL_DEPTH_8U,1);
	cvConvertScale(mosaicVertical1,mosaicVertical1,255.0,0);
	cvConvertScaleAbs(mosaicVertical1,mosaic1,1,0);
	cvSaveImage("D:\GaussianPyramid of me.jpg",mosaic1);
	
	cvNamedWindow("高斯金字塔",1);
	cvShowImage("高斯金字塔", mosaic1);
	cvWaitKey(0);
    cvDestroyWindow("mosaic1");
	cvReleaseImage(& mosaic1);
	
	
	//显示DOG金字塔
	for ( i=0; i<aa.numoctaves;i++)
	{
		if (i==0)
		{
			mosaicHorizen1=aa.MosaicHorizen( (DOGoctaves1[0].Octave)[0].Level, (DOGoctaves1[0].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+2;j++)
				mosaicHorizen1=aa.MosaicHorizen( mosaicHorizen1, (DOGoctaves1[0].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen1=aa.halfSizeImage(mosaicHorizen1);
		}
		else if (i==1)
		{
			mosaicHorizen2=aa.MosaicHorizen( (DOGoctaves1[1].Octave)[0].Level, (DOGoctaves1[1].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+2;j++)
				mosaicHorizen2=aa.MosaicHorizen( mosaicHorizen2, (DOGoctaves1[1].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen2=aa.halfSizeImage(mosaicHorizen2);
			mosaicVertical1=aa.MosaicVertical( mosaicHorizen1, mosaicHorizen2 );
		}
		else
		{
			mosaicHorizen1=aa.MosaicHorizen( (DOGoctaves1[i].Octave)[0].Level, (DOGoctaves1[i].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+2;j++)
				mosaicHorizen1=aa.MosaicHorizen( mosaicHorizen1, (DOGoctaves1[i].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen1=aa.halfSizeImage(mosaicHorizen1);
			mosaicVertical1=aa.MosaicVertical( mosaicVertical1, mosaicHorizen1 );
		}
	}
	//考虑到DOG金字塔各层图像都会有正负，所以，必须寻找最负的，以将所有图像抬高一个台阶去显示
	double min_val=0;
	double max_val=0;
	cvMinMaxLoc(mosaicVertical1,&min_val,&max_val,NULL,NULL,NULL);
	if (min_val<0.0)
	{
		cvAddS(mosaicVertical1,cvScalarAll((-1)*min_val),mosaicVertical1,NULL);
		
	}
	IplImage *mosaic2=NULL;
	mosaic2 = cvCreateImage(cvSize(mosaicVertical1->width, mosaicVertical1->height),  IPL_DEPTH_8U,1);
	cvConvertScale( mosaicVertical1, mosaicVertical1, 255.0/(max_val-min_val), 0 );
	cvConvertScaleAbs( mosaicVertical1, mosaic2, 1, 0 );
	
	cvSaveImage("DOGPyramid of me.jpg",mosaic2);
	cvNamedWindow("mosaic1",1);
	cvShowImage("mosaic1", mosaic2);
    cvWaitKey(0);*/


}

void stitchimage::Onstep22() 
{
	// TODO: Add your control notification handler code here
	Gaussianpyr2=BuildGaussianOctaves2(tempMat2);

		//显示高斯图像
/*	CvMat *mosaicHorizen1=NULL;
	CvMat *mosaicHorizen2=NULL;
	CvMat *mosaicVertical1=NULL;
#define ImLevels(OCTAVE,LEVEL,ROW,COL) ((float *)(Gaussianpyr2[(OCTAVE)].Octave[(LEVEL)].Level->data.fl +Gaussianpyr2[(OCTAVE)].Octave[(LEVEL)].Level->step/sizeof(float) *(ROW)))[(COL)]
	
	for (int i=0;i<aa.numoctaves;i++)
	{
		if (i==0)
		{
			mosaicHorizen1=aa.MosaicHorizen((Gaussianpyr2[0].Octave)[0].Level,(Gaussianpyr2[0].Octave)[1].Level);
			for(int j=2;j<SCALESPEROCTAVE+3;j++)
				mosaicHorizen1=aa.MosaicHorizen( mosaicHorizen1, (Gaussianpyr2[0].Octave)[j].Level);
			for(j=0;j<NUMSIZE;j++)
				mosaicHorizen1=aa.halfSizeImage(mosaicHorizen1);
			
		}
		else if (i==1)
		{
			mosaicHorizen2=aa.MosaicHorizen((Gaussianpyr2[1].Octave)[0].Level, (Gaussianpyr2[1].Octave)[1].Level);
			for(int j=2;j<SCALESPEROCTAVE+3;j++)
				mosaicHorizen2=aa.MosaicHorizen(mosaicHorizen2, (Gaussianpyr2[1].Octave)[j].Level );
			for(j=0;j<NUMSIZE;j++)
				mosaicHorizen2=aa.halfSizeImage(mosaicHorizen2);
			mosaicVertical1=aa.MosaicVertical( mosaicHorizen1, mosaicHorizen2 );
			
		}
		else
		{
			mosaicHorizen1=aa.MosaicHorizen( (Gaussianpyr2[i].Octave)[0].Level, (Gaussianpyr2[i].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+3;j++)
				mosaicHorizen1=aa.MosaicHorizen( mosaicHorizen1, (Gaussianpyr2[i].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen1=aa.halfSizeImage(mosaicHorizen1);
			mosaicVertical1=aa.MosaicVertical( mosaicVertical1, mosaicHorizen1 );
		}
	}
	IplImage *mosaic1=NULL;
	mosaic1=cvCreateImage(cvSize(mosaicVertical1->width,mosaicVertical1->height),IPL_DEPTH_8U,1);
	cvConvertScale(mosaicVertical1,mosaicVertical1,255.0,0);
	cvConvertScaleAbs(mosaicVertical1,mosaic1,1,0);
	cvSaveImage("D:\GaussianPyramid of me.jpg",mosaic1);
	
	cvNamedWindow("高斯金字塔",1);
	cvShowImage("高斯金字塔", mosaic1);
	cvWaitKey(0);
    cvDestroyWindow("mosaic1");
	cvReleaseImage(& mosaic1);
	
	
	//显示DOG金字塔
	for ( i=0; i<aa.numoctaves;i++)
	{
		if (i==0)
		{
			mosaicHorizen1=aa.MosaicHorizen( (DOGoctaves2[0].Octave)[0].Level, (DOGoctaves2[0].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+2;j++)
				mosaicHorizen1=aa.MosaicHorizen( mosaicHorizen1, (DOGoctaves2[0].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen1=aa.halfSizeImage(mosaicHorizen1);
		}
		else if (i==1)
		{
			mosaicHorizen2=aa.MosaicHorizen( (DOGoctaves2[1].Octave)[0].Level, (DOGoctaves2[1].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+2;j++)
				mosaicHorizen2=aa.MosaicHorizen( mosaicHorizen2, (DOGoctaves2[1].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen2=aa.halfSizeImage(mosaicHorizen2);
			mosaicVertical1=aa.MosaicVertical( mosaicHorizen1, mosaicHorizen2 );
		}
		else
		{
			mosaicHorizen1=aa.MosaicHorizen( (DOGoctaves2[i].Octave)[0].Level, (DOGoctaves2[i].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+2;j++)
				mosaicHorizen1=aa.MosaicHorizen( mosaicHorizen1, (DOGoctaves2[i].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen1=aa.halfSizeImage(mosaicHorizen1);
			mosaicVertical1=aa.MosaicVertical( mosaicVertical1, mosaicHorizen1 );
		}
	}
	//考虑到DOG金字塔各层图像都会有正负，所以，必须寻找最负的，以将所有图像抬高一个台阶去显示
	double min_val=0;
	double max_val=0;
	cvMinMaxLoc(mosaicVertical1,&min_val,&max_val,NULL,NULL,NULL);
	if (min_val<0.0)
	{
		cvAddS(mosaicVertical1,cvScalarAll((-1)*min_val),mosaicVertical1,NULL);
		
	}
	IplImage *mosaic2=NULL;
	mosaic2 = cvCreateImage(cvSize(mosaicVertical1->width, mosaicVertical1->height),  IPL_DEPTH_8U,1);
	cvConvertScale( mosaicVertical1, mosaicVertical1, 255.0/(max_val-min_val), 0 );
	cvConvertScaleAbs( mosaicVertical1, mosaic2, 1, 0 );
	
	cvSaveImage("DOGPyramid of me.jpg",mosaic2);
	cvNamedWindow("mosaic1",1);
	cvShowImage("mosaic1", mosaic2);
    cvWaitKey(0);*/

}


int stitchimage::DetectKeypoint1(int numoctaves,ImageOctaves *Gaussianpyr1)
{
	aa.keypoints1=NULL;
	//计算用于DOG极值点检测的主曲率比的阈值
	double curvature_threshold=((CURVATURE_THRESHOLD+1)*(CURVATURE_THRESHOLD+1))/CURVATURE_THRESHOLD;
	#define ImLevels(OCTAVE,LEVEL,ROW,COL) ((float *)(DOGoctaves1[(OCTAVE)].Octave[(LEVEL)].Level->data.fl + DOGoctaves1[(OCTAVE)].Octave[(LEVEL)].Level->step/sizeof(float) *(ROW)))[(COL)]

	int keypoint_count=0;
	for (int i=0;i<numoctaves;i++)
	{
		for (int j=1;j<SCALESPEROCTAVE+1;j++)//取中间的scaleperoctave个层
		{
			//在图像的有效区域内寻找具有显著性特征的局部最大值
			int dim=(int)(0.5+((Gaussianpyr1[i].Octave)[j].levelsigmalength)+0.5);
			for (int m=dim;m<((DOGoctaves1[i].row)-dim);m++)
			{
				for (int n=dim;n<((DOGoctaves1[i].col)-dim);n++)
				{
					if (ImLevels(i,j,m,n)!=0.0)//first 非零
					{
						
						float inf_val=ImLevels(i,j,m,n);
					
					/*	if(( (inf_val <= 50+ImLevels(i,j-1,m-1,n-1))&&
							(inf_val <= 50+ImLevels(i,j-1,m  ,n-1))&&
							(inf_val <= 50+ImLevels(i,j-1,m+1,n-1))&&
							(inf_val <= 50+ImLevels(i,j-1,m-1,n  ))&&
							(inf_val <= 50+ImLevels(i,j-1,m  ,n  ))&&
							(inf_val <= 50+ImLevels(i,j-1,m+1,n  ))&&
							(inf_val <= 50+ImLevels(i,j-1,m-1,n+1))&&
							(inf_val <= 50+ImLevels(i,j-1,m  ,n+1))&&
							(inf_val <= 50+ImLevels(i,j-1,m+1,n+1))&&    //底层的小尺度9
							
							(inf_val <= 50+ImLevels(i,j,m-1,n-1))&&
							(inf_val <= 50+ImLevels(i,j,m  ,n-1))&&
							(inf_val <= 50+ImLevels(i,j,m+1,n-1))&&
							(inf_val <= 50+ImLevels(i,j,m-1,n  ))&&
							(inf_val <= 50+ImLevels(i,j,m+1,n  ))&&
							(inf_val <= 50+ImLevels(i,j,m-1,n+1))&&
							(inf_val <= 50+ImLevels(i,j,m  ,n+1))&&
							(inf_val <= 50+ImLevels(i,j,m+1,n+1))&&     //当前层8
							
							(inf_val <= 50+ImLevels(i,j+1,m-1,n-1))&&
							(inf_val <= 50+ImLevels(i,j+1,m  ,n-1))&&
							(inf_val <= 50+ImLevels(i,j+1,m+1,n-1))&&
							(inf_val <= 50+ImLevels(i,j+1,m-1,n  ))&&
							(inf_val <= 50+ImLevels(i,j+1,m  ,n  ))&&
							(inf_val <= 50+ImLevels(i,j+1,m+1,n  ))&&
							(inf_val <= 50+ImLevels(i,j+1,m-1,n+1))&&
							(inf_val <= 50+ImLevels(i,j+1,m  ,n+1))&&
							(inf_val <= 50+ImLevels(i,j+1,m+1,n+1))     //下一层大尺度9							 
							) || 
							( (inf_val >= ImLevels(i,j-1,m-1,n-1)-5)&&
							(inf_val >= ImLevels(i,j-1,m  ,n-1)-5)&&
							(inf_val >= ImLevels(i,j-1,m+1,n-1)-5)&&
							(inf_val >= ImLevels(i,j-1,m-1,n  )-5)&&
							(inf_val >= ImLevels(i,j-1,m  ,n  )-5)&&
							(inf_val >= ImLevels(i,j-1,m+1,n  )-5)&&
							(inf_val >= ImLevels(i,j-1,m-1,n+1)-5)&&
							(inf_val >= ImLevels(i,j-1,m  ,n+1)-5)&&
							(inf_val >= ImLevels(i,j-1,m+1,n+1)-5)&&
							
							(inf_val >= ImLevels(i,j,m-1,n-1)-5)&&
							(inf_val >= ImLevels(i,j,m  ,n-1)-5)&&
							(inf_val >= ImLevels(i,j,m+1,n-1)-5)&&
							(inf_val >= ImLevels(i,j,m-1,n  )-5)&&
							(inf_val >= ImLevels(i,j,m+1,n  )-5)&&
							(inf_val >= ImLevels(i,j,m-1,n+1)-5)&&
							(inf_val >= ImLevels(i,j,m  ,n+1)-5)&&
							(inf_val >= ImLevels(i,j,m+1,n+1)-5)&& 
							
							(inf_val >= ImLevels(i,j+1,m-1,n-1)-5)&&
							(inf_val >= ImLevels(i,j+1,m  ,n-1)-5)&&
							(inf_val >= ImLevels(i,j+1,m+1,n-1)-5)&&
							(inf_val >= ImLevels(i,j+1,m  ,n  )-5)&&
							(inf_val >= ImLevels(i,j+1,m+1,n  )-5)&&
							(inf_val >= ImLevels(i,j+1,m-1,n+1)-5)&&
							(inf_val >= ImLevels(i,j+1,m  ,n+1)-5)&&
							(inf_val >= ImLevels(i,j+1,m+1,n+1)-5) 
						   ) )      //2、满足26个中极值点*/

						   if(( (inf_val <= ImLevels(i,j-1,m-1,n-1))&&
							   (inf_val <= ImLevels(i,j-1,m  ,n-1))&&
							   (inf_val <= ImLevels(i,j-1,m+1,n-1))&&
							   (inf_val <= ImLevels(i,j-1,m-1,n  ))&&
							   (inf_val <= ImLevels(i,j-1,m  ,n  ))&&
							   (inf_val <= ImLevels(i,j-1,m+1,n  ))&&
							   (inf_val <= ImLevels(i,j-1,m-1,n+1))&&
							   (inf_val <= ImLevels(i,j-1,m  ,n+1))&&
							   (inf_val <= ImLevels(i,j-1,m+1,n+1))&&    //底层的小尺度9
							   
							   (inf_val <= ImLevels(i,j,m-1,n-1))&&
							   (inf_val <= ImLevels(i,j,m  ,n-1))&&
							   (inf_val <= ImLevels(i,j,m+1,n-1))&&
							   (inf_val <= ImLevels(i,j,m-1,n  ))&&
							   (inf_val <= ImLevels(i,j,m+1,n  ))&&
							   (inf_val <= ImLevels(i,j,m-1,n+1))&&
							   (inf_val <= ImLevels(i,j,m  ,n+1))&&
							   (inf_val <= ImLevels(i,j,m+1,n+1))&&     //当前层8
							   
							   (inf_val <= ImLevels(i,j+1,m-1,n-1))&&
							   (inf_val <= ImLevels(i,j+1,m  ,n-1))&&
							   (inf_val <= ImLevels(i,j+1,m+1,n-1))&&
							   (inf_val <= ImLevels(i,j+1,m-1,n  ))&&
							   (inf_val <= ImLevels(i,j+1,m  ,n  ))&&
							   (inf_val <= ImLevels(i,j+1,m+1,n  ))&&
							   (inf_val <= ImLevels(i,j+1,m-1,n+1))&&
							   (inf_val <= ImLevels(i,j+1,m  ,n+1))&&
							   (inf_val <= ImLevels(i,j+1,m+1,n+1))     //下一层大尺度9							 
							   ) || 
							   ( (inf_val >= ImLevels(i,j-1,m-1,n-1))&&
							   (inf_val >= ImLevels(i,j-1,m  ,n-1))&&
							   (inf_val >= ImLevels(i,j-1,m+1,n-1))&&
							   (inf_val >= ImLevels(i,j-1,m-1,n  ))&&
							   (inf_val >= ImLevels(i,j-1,m  ,n  ))&&
							   (inf_val >= ImLevels(i,j-1,m+1,n  ))&&
							   (inf_val >= ImLevels(i,j-1,m-1,n+1))&&
							   (inf_val >= ImLevels(i,j-1,m  ,n+1))&&
							   (inf_val >= ImLevels(i,j-1,m+1,n+1))&&
							   
							   (inf_val >= ImLevels(i,j,m-1,n-1))&&
							   (inf_val >= ImLevels(i,j,m  ,n-1))&&
							   (inf_val >= ImLevels(i,j,m+1,n-1))&&
							   (inf_val >= ImLevels(i,j,m-1,n  ))&&
							   (inf_val >= ImLevels(i,j,m+1,n  ))&&
							   (inf_val >= ImLevels(i,j,m-1,n+1))&&
							   (inf_val >= ImLevels(i,j,m  ,n+1))&&
							   (inf_val >= ImLevels(i,j,m+1,n+1))&& 
							   
							   (inf_val >= ImLevels(i,j+1,m-1,n-1))&&
							   (inf_val >= ImLevels(i,j+1,m  ,n-1))&&
							   (inf_val >= ImLevels(i,j+1,m+1,n-1))&&
							   (inf_val >= ImLevels(i,j+1,m-1,n  ))&&
							   (inf_val >= ImLevels(i,j+1,m  ,n  ))&&
							   (inf_val >= ImLevels(i,j+1,m+1,n  ))&&
							   (inf_val >= ImLevels(i,j+1,m-1,n+1))&&
							   (inf_val >= ImLevels(i,j+1,m  ,n+1))&&
							   (inf_val >= ImLevels(i,j+1,m+1,n+1)) 
						   ) )      //2、满足26个中极值点
						
						{
							//存储特征点
							//必须具有明显的显著性，即必须大于CONTRAST_THRESHOLD=0.02
							if (fabs(ImLevels(i,j,m,n))>= CONTRAST_THRESHOLD+0.05)
							{
								//最后显著处的特征点必须有足够的曲率比，先计算Hessian矩阵
								//Tr_H = Dxx + Dyy;
                                //Det_H = Dxx*Dyy - Dxy^2;
								float Dxx,Dyy,Dxy,Tr_H,Det_H,curvature_ratio;
                                Dxx = ImLevels(i,j,m,n-1) + ImLevels(i,j,m,n+1)-2.0*ImLevels(i,j,m,n);
								Dyy = ImLevels(i,j,m-1,n) + ImLevels(i,j,m+1,n)-2.0*ImLevels(i,j,m,n);
								Dxy = ImLevels(i,j,m-1,n-1) + ImLevels(i,j,m+1,n+1) - ImLevels(i,j,m+1,n-1) - ImLevels(i,j,m-1,n+1);
                                Tr_H = Dxx + Dyy;
                                Det_H = Dxx*Dyy - Dxy*Dxy;
								//计算主曲率
								curvature_ratio=(1.0*Tr_H*Tr_H)/Det_H;
								if ((Det_H>=0.0) && (curvature_ratio <= curvature_threshold))//最后得到最具有显著性特征的特征点
								{
									//将其存储起来，以计算后面的特征描述
									keypoint_count++;
									Keypoint k;
									//为特征点分配内存
									k=(Keypoint) malloc(sizeof(struct KeypointSt));
									k->next=aa.keypoints1;
									aa.keypoints1=k;
									k->row=m*(Gaussianpyr1[i].subsample);
									k->col=n*(Gaussianpyr1[i].subsample);
									k->sy=m;//行
									k->sx=n;//列
									k->octave=i;
									k->level=j;
									k->scale=(Gaussianpyr1[i].Octave)[j].absolute_sigma; 

								}

							}


						}
						
					
						

					}
				}
			}
			
		}
	}
	return keypoint_count;

}


int stitchimage::DetectKeypoint2(int numoctaves,ImageOctaves *Gaussianpyr2)
{
	aa.keypoints2=NULL;
	//计算用于DOG极值点检测的主曲率比的阈值
	double curvature_threshold=((CURVATURE_THRESHOLD+1)*(CURVATURE_THRESHOLD+1))/CURVATURE_THRESHOLD;
	#define ImLevels(OCTAVE,LEVEL,ROW,COL) ((float *)(DOGoctaves2[(OCTAVE)].Octave[(LEVEL)].Level->data.fl + DOGoctaves2[(OCTAVE)].Octave[(LEVEL)].Level->step/sizeof(float) *(ROW)))[(COL)]

	int keypoint_count=0;
	for (int i=0;i<numoctaves;i++)
	{
		for (int j=1;j<SCALESPEROCTAVE+1;j++)//取中间的scaleperoctave个层
		{
			//在图像的有效区域内寻找具有显著性特征的局部最大值
			int dim=(int)(0.5+((Gaussianpyr2[i].Octave)[j].levelsigmalength)+0.5);
			for (int m=dim;m<((DOGoctaves2[i].row)-dim);m++)
			{
				for (int n=dim;n<((DOGoctaves2[i].col)-dim);n++)
				{
					if (ImLevels(i,j,m,n)!=0.0)//first 非零
					{
						
						float inf_val=ImLevels(i,j,m,n);
					
						if(( (inf_val <= ImLevels(i,j-1,m-1,n-1))&&
							(inf_val <= ImLevels(i,j-1,m  ,n-1))&&
							(inf_val <= ImLevels(i,j-1,m+1,n-1))&&
							(inf_val <= ImLevels(i,j-1,m-1,n  ))&&
							(inf_val <= ImLevels(i,j-1,m  ,n  ))&&
							(inf_val <= ImLevels(i,j-1,m+1,n  ))&&
							(inf_val <= ImLevels(i,j-1,m-1,n+1))&&
							(inf_val <= ImLevels(i,j-1,m  ,n+1))&&
							(inf_val <= ImLevels(i,j-1,m+1,n+1))&&    //底层的小尺度9
							
							(inf_val <= ImLevels(i,j,m-1,n-1))&&
							(inf_val <= ImLevels(i,j,m  ,n-1))&&
							(inf_val <= ImLevels(i,j,m+1,n-1))&&
							(inf_val <= ImLevels(i,j,m-1,n  ))&&
							(inf_val <= ImLevels(i,j,m+1,n  ))&&
							(inf_val <= ImLevels(i,j,m-1,n+1))&&
							(inf_val <= ImLevels(i,j,m  ,n+1))&&
							(inf_val <= ImLevels(i,j,m+1,n+1))&&     //当前层8
							
							(inf_val <= ImLevels(i,j+1,m-1,n-1))&&
							(inf_val <= ImLevels(i,j+1,m  ,n-1))&&
							(inf_val <= ImLevels(i,j+1,m+1,n-1))&&
							(inf_val <= ImLevels(i,j+1,m-1,n  ))&&
							(inf_val <= ImLevels(i,j+1,m  ,n  ))&&
							(inf_val <= ImLevels(i,j+1,m+1,n  ))&&
							(inf_val <= ImLevels(i,j+1,m-1,n+1))&&
							(inf_val <= ImLevels(i,j+1,m  ,n+1))&&
							(inf_val <= ImLevels(i,j+1,m+1,n+1))     //下一层大尺度9							 
							) || 
							( (inf_val >= ImLevels(i,j-1,m-1,n-1))&&
							(inf_val >= ImLevels(i,j-1,m  ,n-1))&&
							(inf_val >= ImLevels(i,j-1,m+1,n-1))&&
							(inf_val >= ImLevels(i,j-1,m-1,n  ))&&
							(inf_val >= ImLevels(i,j-1,m  ,n  ))&&
							(inf_val >= ImLevels(i,j-1,m+1,n  ))&&
							(inf_val >= ImLevels(i,j-1,m-1,n+1))&&
							(inf_val >= ImLevels(i,j-1,m  ,n+1))&&
							(inf_val >= ImLevels(i,j-1,m+1,n+1))&&
							
							(inf_val >= ImLevels(i,j,m-1,n-1))&&
							(inf_val >= ImLevels(i,j,m  ,n-1))&&
							(inf_val >= ImLevels(i,j,m+1,n-1))&&
							(inf_val >= ImLevels(i,j,m-1,n  ))&&
							(inf_val >= ImLevels(i,j,m+1,n  ))&&
							(inf_val >= ImLevels(i,j,m-1,n+1))&&
							(inf_val >= ImLevels(i,j,m  ,n+1))&&
							(inf_val >= ImLevels(i,j,m+1,n+1))&& 
							
							(inf_val >= ImLevels(i,j+1,m-1,n-1))&&
							(inf_val >= ImLevels(i,j+1,m  ,n-1))&&
							(inf_val >= ImLevels(i,j+1,m+1,n-1))&&
							(inf_val >= ImLevels(i,j+1,m-1,n  ))&&
							(inf_val >= ImLevels(i,j+1,m  ,n  ))&&
							(inf_val >= ImLevels(i,j+1,m+1,n  ))&&
							(inf_val >= ImLevels(i,j+1,m-1,n+1))&&
							(inf_val >= ImLevels(i,j+1,m  ,n+1))&&
							(inf_val >= ImLevels(i,j+1,m+1,n+1)) 
						   ) )      //2、满足26个中极值点
						
						{
							//存储特征点
							//必须具有明显的显著性，即必须大于CONTRAST_THRESHOLD=0.02
							if (fabs(ImLevels(i,j,m,n))>= CONTRAST_THRESHOLD+0.05)
							{
								//最后显著处的特征点必须有足够的曲率比，先计算Hessian矩阵
								//Tr_H = Dxx + Dyy;
                                //Det_H = Dxx*Dyy - Dxy^2;
								float Dxx,Dyy,Dxy,Tr_H,Det_H,curvature_ratio;
                                Dxx = ImLevels(i,j,m,n-1) + ImLevels(i,j,m,n+1)-2.0*ImLevels(i,j,m,n);
								Dyy = ImLevels(i,j,m-1,n) + ImLevels(i,j,m+1,n)-2.0*ImLevels(i,j,m,n);
								Dxy = ImLevels(i,j,m-1,n-1) + ImLevels(i,j,m+1,n+1) - ImLevels(i,j,m+1,n-1) - ImLevels(i,j,m-1,n+1);
                                Tr_H = Dxx + Dyy;
                                Det_H = Dxx*Dyy - Dxy*Dxy;
								//计算主曲率
								curvature_ratio=(1.0*Tr_H*Tr_H)/Det_H;
								if ((Det_H>=0.0) && (curvature_ratio <= curvature_threshold))//最后得到最具有显著性特征的特征点
								{
									//将其存储起来，以计算后面的特征描述
									keypoint_count++;
									Keypoint k;
									//为特征点分配内存
									k=(Keypoint) malloc(sizeof(struct KeypointSt));
									k->next=aa.keypoints2;
									aa.keypoints2=k;
									k->row=m*(Gaussianpyr2[i].subsample);
									k->col=n*(Gaussianpyr2[i].subsample);
									k->sy=m;//行
									k->sx=n;//列
									k->octave=i;
									k->level=j;
									k->scale=(Gaussianpyr2[i].Octave)[j].absolute_sigma; 

								}

							}


						}
						
					
						

					}
				}
			}
			
		}
	}
	return keypoint_count;

}


void stitchimage::DisplayKeypointLocation1(IplImage* image, ImageOctaves *Gaussianpyr1)
{
	Keypoint p = aa.keypoints1; // p指向第一个结点
	while(p) // 没到表尾
	{   
		cvLine( image, cvPoint((int)((p->col)-3),(int)(p->row)), 
			cvPoint((int)((p->col)+3),(int)(p->row)), CV_RGB(255,255,0),
			1, 8, 0 );
        cvLine( image, cvPoint((int)(p->col),(int)((p->row)-3)), 
			cvPoint((int)(p->col),(int)((p->row)+3)), CV_RGB(255,255,0),
			1, 8, 0 );
		//		cvCircle(image,cvPoint((uchar)(p->col),(uchar)(p->row)),
		//			(int)((GaussianPyr[p->octave].Octave)[p->level].absolute_sigma),
		//			CV_RGB(255,0,0),1,8,0);
		p=p->next;
	}
}

void stitchimage::DisplayKeypointLocation2(IplImage* image, ImageOctaves *Gaussianpyr2)
{
	Keypoint p = aa.keypoints2; // p指向第一个结点
	while(p) // 没到表尾
	{   
		cvLine( image, cvPoint((int)((p->col)-3),(int)(p->row)), 
			cvPoint((int)((p->col)+3),(int)(p->row)), CV_RGB(255,255,0),
			1, 8, 0 );
        cvLine( image, cvPoint((int)(p->col),(int)((p->row)-3)), 
			cvPoint((int)(p->col),(int)((p->row)+3)), CV_RGB(255,255,0),
			1, 8, 0 );
		//		cvCircle(image,cvPoint((uchar)(p->col),(uchar)(p->row)),
		//			(int)((GaussianPyr[p->octave].Octave)[p->level].absolute_sigma),
		//			CV_RGB(255,0,0),1,8,0);
		p=p->next;
	}
}
void stitchimage::Onstep31() 
{
	// TODO: Add your control notification handler code here

	int keycount=DetectKeypoint1(aa.numoctaves,Gaussianpyr1);
	cvCopy(imageptocy1,image1,NULL);
	DisplayKeypointLocation1(image1,Gaussianpyr1);
	cvPyrUp(image1,DoubleSizeImage1,CV_GAUSSIAN_5x5);
	//cvReleaseImage(&image1);
//	cvSaveImage("D:\DoubleSizeImage1.jpg",DoubleSizeImage1);
	cvNamedWindow("image1",2);
	cvShowImage("image1", DoubleSizeImage1);
	cvReleaseImage(&DoubleSizeImage1);
	cvWaitKey(0);  
    cvDestroyWindow("image1");

	
}

void stitchimage::Onstep32() 
{
	// TODO: Add your control notification handler code here
	int keycount=DetectKeypoint2(aa.numoctaves,Gaussianpyr2);
	cvCopy(imageptocy2,image2,NULL);
	DisplayKeypointLocation2(image2,Gaussianpyr2);
	cvPyrUp(image2,DoubleSizeImage2,CV_GAUSSIAN_5x5);
	//cvReleaseImage(&image2);
//	cvSaveImage("D:\DoubleSizeImage2.jpg",DoubleSizeImage2);
	cvNamedWindow("image2",2);
	cvShowImage("image2", DoubleSizeImage2);
	cvReleaseImage(&DoubleSizeImage2);
	cvWaitKey(0);  
    cvDestroyWindow("image2");
}

void stitchimage::ComputeGrad_DirecandMag1(int numoctaves,ImageOctaves *Gaussianpyr1)
{
	mag_pyr1=(ImageOctaves *) malloc(numoctaves * sizeof(ImageOctaves));
	grad_pyr1=(ImageOctaves *) malloc(numoctaves * sizeof(ImageOctaves));
	#define ImLevels(OCTAVE,LEVEL,ROW,COL) ((float *)(Gaussianpyr1[(OCTAVE)].Octave[(LEVEL)].Level->data.fl +Gaussianpyr1[(OCTAVE)].Octave[(LEVEL)].Level->step/sizeof(float) *(ROW)))[(COL)]
	for (int i=0;i<numoctaves;i++)
	{
		mag_pyr1[i].Octave=(ImageLevels *) malloc((SCALESPEROCTAVE) * sizeof(ImageLevels));
		grad_pyr1[i].Octave=(ImageLevels *) malloc((SCALESPEROCTAVE) * sizeof(ImageLevels));
		
		for (int j=1;j<SCALESPEROCTAVE+1;j++)//取中间的SCALESPEROCTAVE个层
		{
			CvMat *Mag=cvCreateMat(Gaussianpyr1[i].row,Gaussianpyr1[i].col,CV_32FC1);
			CvMat *Ori=cvCreateMat(Gaussianpyr1[i].row,Gaussianpyr1[i].col,CV_32FC1);
			CvMat *tempMat11=cvCreateMat(Gaussianpyr1[i].row,Gaussianpyr1[i].col,CV_32FC1);
			CvMat *tempMat22=cvCreateMat(Gaussianpyr1[i].row,Gaussianpyr1[i].col,CV_32FC1);
			cvZero(Mag);
			cvZero(Ori);
			cvZero(tempMat11);
			cvZero(tempMat22);
			#define MAG(ROW,COL) ((float *)(Mag->data.fl + Mag->step/sizeof(float) *(ROW)))[(COL)]   
			#define ORI(ROW,COL) ((float *)(Ori->data.fl + Ori->step/sizeof(float) *(ROW)))[(COL)]  
			#define TEMPMAT1(ROW,COL) ((float *)(tempMat11->data.fl + tempMat11->step/sizeof(float) *(ROW)))[(COL)]
			#define TEMPMAT2(ROW,COL) ((float *)(tempMat22->data.fl + tempMat22->step/sizeof(float) *(ROW)))[(COL)]
			for (int m=1;m<(Gaussianpyr1[i].row-1);m++)
			{
				for (int n=1;n<(Gaussianpyr1[i].col-1);n++)
				{
					//计算幅值
					TEMPMAT1(m,n)=0.5*(ImLevels(i,j,m,n+1)-ImLevels(i,j,m,n-1));//dx
					TEMPMAT2(m,n)=0.5*(ImLevels(i,j,m+1,n)-ImLevels(i,j,m-1,n));//dy
					MAG(m,n)=sqrt(TEMPMAT1(m,n)*TEMPMAT1(m,n)+TEMPMAT2(m,n)*TEMPMAT2(m,n));//幅值
					//计算方向
					ORI(m,n)=atan(TEMPMAT2(m,n)/TEMPMAT1(m,n));
					if (ORI(m,n)==CV_PI)
					{
						ORI(m,n)=-CV_PI;
						
					}
					
				}
				
			}
			((mag_pyr1[i].Octave)[j-1]).Level=Mag;
			((grad_pyr1[i].Octave)[j-1]).Level=Ori;
			cvReleaseMat(&tempMat11);
			cvReleaseMat(&tempMat22);
			cvReleaseMat(&Mag);
			cvReleaseMat(&Ori);
		}
		
		free(mag_pyr1[i].Octave);
		free(grad_pyr1[i].Octave);	
	}
	free(mag_pyr1);
	free(grad_pyr1);
	
	
}


void stitchimage::ComputeGrad_DirecandMag2(int numoctaves,ImageOctaves *Gaussianpyr2)
{
	mag_pyr2=(ImageOctaves *) malloc(numoctaves * sizeof(ImageOctaves));
	grad_pyr2=(ImageOctaves *) malloc(numoctaves * sizeof(ImageOctaves));
	#define ImLevels(OCTAVE,LEVEL,ROW,COL) ((float *)(Gaussianpyr2[(OCTAVE)].Octave[(LEVEL)].Level->data.fl +Gaussianpyr2[(OCTAVE)].Octave[(LEVEL)].Level->step/sizeof(float) *(ROW)))[(COL)]
	for (int i=0;i<numoctaves;i++)
	{
		mag_pyr2[i].Octave=(ImageLevels *) malloc((SCALESPEROCTAVE) * sizeof(ImageLevels));
		grad_pyr2[i].Octave=(ImageLevels *) malloc((SCALESPEROCTAVE) * sizeof(ImageLevels));
		
		for (int j=1;j<SCALESPEROCTAVE+1;j++)//取中间的SCALESPEROCTAVE个层
		{
			CvMat *Mag=cvCreateMat(Gaussianpyr2[i].row,Gaussianpyr2[i].col,CV_32FC1);
			CvMat *Ori=cvCreateMat(Gaussianpyr2[i].row,Gaussianpyr2[i].col,CV_32FC1);
			CvMat *tempMat11=cvCreateMat(Gaussianpyr2[i].row,Gaussianpyr2[i].col,CV_32FC1);
			CvMat *tempMat22=cvCreateMat(Gaussianpyr2[i].row,Gaussianpyr2[i].col,CV_32FC1);
			cvZero(Mag);
			cvZero(Ori);
			cvZero(tempMat11);
			cvZero(tempMat22);
			#define MAG(ROW,COL) ((float *)(Mag->data.fl + Mag->step/sizeof(float) *(ROW)))[(COL)]   
			#define ORI(ROW,COL) ((float *)(Ori->data.fl + Ori->step/sizeof(float) *(ROW)))[(COL)]  
			#define TEMPMAT1(ROW,COL) ((float *)(tempMat11->data.fl + tempMat11->step/sizeof(float) *(ROW)))[(COL)]
			#define TEMPMAT2(ROW,COL) ((float *)(tempMat22->data.fl + tempMat22->step/sizeof(float) *(ROW)))[(COL)]
			for (int m=1;m<(Gaussianpyr2[i].row-1);m++)
			{
				for (int n=1;n<(Gaussianpyr2[i].col-1);n++)
				{
					//计算幅值
					TEMPMAT1(m,n)=0.5*(ImLevels(i,j,m,n+1)-ImLevels(i,j,m,n-1));//dx
					TEMPMAT2(m,n)=0.5*(ImLevels(i,j,m+1,n)-ImLevels(i,j,m-1,n));//dy
					MAG(m,n)=sqrt(TEMPMAT1(m,n)*TEMPMAT1(m,n)+TEMPMAT2(m,n)*TEMPMAT2(m,n));//幅值
					//计算方向
					ORI(m,n)=atan(TEMPMAT2(m,n)/TEMPMAT1(m,n));
					if (ORI(m,n)==CV_PI)
					{
						ORI(m,n)=-CV_PI;
						
					}
					
				}
				
			}
			((mag_pyr2[i].Octave)[j-1]).Level=Mag;
			((grad_pyr2[i].Octave)[j-1]).Level=Ori;
			cvReleaseMat(&tempMat11);
			cvReleaseMat(&tempMat22);
			cvReleaseMat(&Mag);
			cvReleaseMat(&Ori);
		}
		free(mag_pyr2[i].Octave);
		free(grad_pyr2[i].Octave);
		
	}
	free(mag_pyr2);
	free(grad_pyr2);
	
}


void stitchimage::AssignTheMainOrientation1(int numoctaves, ImageOctaves *Gaussianpyr,ImageOctaves *mag_pyr,ImageOctaves *grad_pyr)
{
	aa.keyDescriptors1=NULL;
	int num_bins=36;
	float hist_step=2.0*pi/num_bins;
	float hist_orient[36];
	for (int i=0;i<36;i++)
	{
		hist_orient[i]=-pi+i*hist_step;
	}
	float sigma1=(((Gaussianpyr[0].Octave)[SCALESPEROCTAVE].absolute_sigma))/(Gaussianpyr[0].subsample);//SCALESPEROCTAVE+2
	int zero_pad=(int)(max(3.0f, 2 * GAUSSKERN *sigma1 + 1.0f)*0.5+0.5);
	#define ImLevels(OCTAVES,LEVELS,ROW,COL) ((float *)((Gaussianpyr[(OCTAVES)].Octave[(LEVELS)].Level)->data.fl + (Gaussianpyr[(OCTAVES)].Octave[(LEVELS)].Level)->step/sizeof(float) *(ROW)))[(COL)]
	
	int keypoint_count=0;
	Keypoint p=aa.keypoints1;//p指向第一个结点
	while(p)//没到表尾
	{
		int i=p->octave;
		int j=p->level;
		int m=p->sy;
		int n=p->sx;
		if ((m>=zero_pad)&&(m<Gaussianpyr[i].row-zero_pad)&&
			(n>=zero_pad)&&(n<Gaussianpyr[i].col-zero_pad))
		{
			float sigma=( ((Gaussianpyr[i].Octave)[j].absolute_sigma) ) / (Gaussianpyr[i].subsample);
			//产生二维高斯模板
			CvMat * mat=aa.GaussianKernel2D(sigma);
			int dim=(int)(0.5*(mat->rows));
			//分配用于存储patch幅值和方向的空间
			#define MAT(ROW,COL) ((float *)(mat->data.fl + mat->step/sizeof(float) *(ROW)))[(COL)]
			//声明方向直方图变量
			double * orienthist=(double *) malloc(36*sizeof(double));
			for (int sw=0;sw<36;++sw)
			{
				orienthist[sw]=0.0;
			}
			//在特征点的周围统计梯度方向
			for (int x=m-dim,mm=0;x<=(m+dim);x++,mm++)
			{
				for (int y=n-dim,nn=0;y<=(n+dim);y++,nn++)
				{
					//计算特征点处的幅值
					double dx=0.5*(ImLevels(i,j,x,y+1)-ImLevels(i,j,x,y-1));//dx
					double dy=0.5*(ImLevels(i,j,x+1,y)-ImLevels(i,j,x-1,y));//dy
					double mag=sqrt(dx*dx+dy*dy);//幅值
					//计算方向
					double Ori=atan(1.0*dy/dx);//注意dx!=0
					int binIdx=aa.FindClosestRotationBin(36,Ori);
					//利用高斯加权累加进直方图相应的块
					orienthist[binIdx]=orienthist[binIdx]+1.0*mag*MAT(mm,nn);
					
				}
			}
			//找出方向直方图中的峰值
			aa.AverageWeakBins(orienthist,36);
			//找出最大值
			double maxGrad=0.0;
			int maxBin=0;
			for (int b=0;b<36;++b)
			{
				if (orienthist[b] > maxGrad)
				{
					maxGrad=orienthist[b];
					maxBin=b;
				}
			}
			double maxPeakValue=0.0;
			double maxDegreeOriention=0.0;
			/*if((InterpolateOrientation(orienthist[maxBin==0 ? (36-1) : (maxBin-1)],orienthist[maxBin],
				orienthist[(maxBin+1) % 36],&maxDegreeOriention,&maxPeakValue))==false)
				printf("BUG: Parabola fitting broken");*/

			bool binIsKeypoint[36];
			for (b=0;b<36;++b)
			{
				binIsKeypoint[b]=false;
				if (b==maxBin)
				{
					binIsKeypoint[b]=true;
					continue;
				}
			
				if(orienthist[b] < (peakRelThresh * maxPeakValue))
					continue;
				int leftI=(b==0) ? (36-1) :(b-1);
				int rightI=(b+1) % 36;
				if(orienthist[b]<=orienthist[leftI] || orienthist[b] <= orienthist[rightI])
					continue;
				binIsKeypoint[b]=true;

			}
			//寻找另一个可能的点
			double oneBinRad=(2.0 * pi) / 36;
			for (b=0;b<36;++b)
			{
				if (binIsKeypoint[b]==false)
					continue;
				int bLeft=(b==0) ? (36-1) : (b-1);
				int bRight=(b+1) % 36;
				double peakValue;
				double degreeCorrection;

				double maxPeakValue,maxDegreeOriention;
				if (aa.InterpolateOrientation ( orienthist[maxBin == 0 ? (36 - 1) : (maxBin - 1)],
                    orienthist[maxBin], orienthist[(maxBin + 1) % 36],
                    &degreeCorrection, &peakValue) == false)
				{
					printf("BUG: Parabola fitting broken");
				}

				double degree=(b+degreeCorrection) * oneBinRad-pi;
				if(degree < -pi)
					degree+=2.0*pi;
				else if(degree > pi)
					degree-=2.0*pi;
				//存储方向，可以直接利用检测到的链表进行该步主方向的指定；
				//分配内存重新存储特征点
				Keypoint k;
				//allocate memory for the keypoint descriptor
			
				k=(Keypoint) malloc(sizeof(struct KeypointSt));
				k->next=aa.keyDescriptors1;
				aa.keyDescriptors1=k;
				k->descrip=(float*)malloc(LEN * sizeof(float));
				k->row=p->row;
				k->col=p->col;
				k->sy = p->sy;    //行
				k->sx = p->sx;    //列
				k->octave = p->octave;
				k->level = p->level;
				k->scale = p->scale;      
                k->ori = degree;
                k->mag = peakValue;

			}
			free(orienthist);
				

			



			
		}
		p=p->next;

	}

}


void stitchimage::DisplayOrientation1(IplImage *image,ImageOctaves *Gaussianpyr)
{
	p1=aa.keyDescriptors1;//p指向第一个节点,keyDescriptors一定要初始化为零
	while (p1)//没到表尾
	{
		float scale=(Gaussianpyr[p1->octave].Octave)[p1->level].absolute_sigma;
		float autoscale=3.0;
		float uu=autoscale*scale*cos(p1->ori);
		float vv=autoscale*scale*sin(p1->ori);
		float x=(p1->col)+uu;
		float y=(p1->row)+vv;
		
		cvLine(image, cvPoint((int)(p1->col),(int)(p1->row)), 
			cvPoint((int)x,(int)y), CV_RGB(255,255,0),
			1, 8, 0 );
		float alpha=0.33;
		float beta=0.33;
		
		float xx0=(p1->col)+uu-alpha*(uu+beta*vv);
		float yy0=(p1->row)+vv-alpha*(vv-beta*uu);
		float xx1=(p1->col)+uu-alpha*(uu-beta*vv);
		float yy1=(p1->row)+vv-alpha*(vv+beta*uu);
		cvLine(image,cvPoint((int)xx0,(int)yy0),cvPoint((int)x,(int)y),CV_RGB(255,255,0),1,8,0);
		cvLine(image,cvPoint((int)xx1,(int)yy1),cvPoint((int)x,(int)y),CV_RGB(255,255,0),1,8,0);
		p1=p1->next;
	}
	
}
void stitchimage::Onstep41() 
{
	// TODO: Add your control notification handler code here
	ComputeGrad_DirecandMag1(aa.numoctaves,Gaussianpyr1);
	AssignTheMainOrientation1(aa.numoctaves,Gaussianpyr1,mag_pyr1,grad_pyr1);
	cvCopy(imageptocy1,image1,NULL);
	DisplayOrientation1(image1,Gaussianpyr1);
	
//	cvSaveImage("D:\mag1.jpg",image1);
	cvNamedWindow("image11",2);
	cvShowImage("image11",image1);
	//cvReleaseImage(& image1);
	cvWaitKey(0);  
    cvDestroyWindow("image11");
}


void stitchimage::AssignTheMainOrientation2(int numoctaves, ImageOctaves *Gaussianpyr,ImageOctaves *mag_pyr,ImageOctaves *grad_pyr)
{
	aa.keyDescriptors2=NULL;
	int num_bins=36;
	float hist_step=2.0*pi/num_bins;
	float hist_orient[36];
	for (int i=0;i<36;i++)
	{
		hist_orient[i]=-pi+i*hist_step;
	}
	float sigma1=(((Gaussianpyr[0].Octave)[SCALESPEROCTAVE].absolute_sigma))/(Gaussianpyr[0].subsample);//SCALESPEROCTAVE+2
	int zero_pad=(int)(max(3.0f, 2 * GAUSSKERN *sigma1 + 1.0f)*0.5+0.5);
	#define ImLevels(OCTAVES,LEVELS,ROW,COL) ((float *)((Gaussianpyr[(OCTAVES)].Octave[(LEVELS)].Level)->data.fl + (Gaussianpyr[(OCTAVES)].Octave[(LEVELS)].Level)->step/sizeof(float) *(ROW)))[(COL)]
	
	int keypoint_count=0;
	Keypoint p=aa.keypoints2;//p指向第一个结点
	while(p)//没到表尾
	{
		int i=p->octave;
		int j=p->level;
		int m=p->sy;
		int n=p->sx;
		if ((m>=zero_pad)&&(m<Gaussianpyr[i].row-zero_pad)&&
			(n>=zero_pad)&&(n<Gaussianpyr[i].col-zero_pad))
		{
			float sigma=( ((Gaussianpyr[i].Octave)[j].absolute_sigma) ) / (Gaussianpyr[i].subsample);
			//产生二维高斯模板
			CvMat * mat=aa.GaussianKernel2D(sigma);
			int dim=(int)(0.5*(mat->rows));
			//分配用于存储patch幅值和方向的空间
			#define MAT(ROW,COL) ((float *)(mat->data.fl + mat->step/sizeof(float) *(ROW)))[(COL)]
			//声明方向直方图变量
			double * orienthist=(double *) malloc(36*sizeof(double));
			for (int sw=0;sw<36;++sw)
			{
				orienthist[sw]=0.0;
			}
			//在特征点的周围统计梯度方向
			for (int x=m-dim,mm=0;x<=(m+dim);x++,mm++)
			{
				for (int y=n-dim,nn=0;y<=(n+dim);y++,nn++)
				{
					//计算特征点处的幅值
					double dx=0.5*(ImLevels(i,j,x,y+1)-ImLevels(i,j,x,y-1));//dx
					double dy=0.5*(ImLevels(i,j,x+1,y)-ImLevels(i,j,x-1,y));//dy
					double mag=sqrt(dx*dx+dy*dy);//幅值
					//计算方向
					double Ori=atan(1.0*dy/dx);//注意dx!=0
					int binIdx=aa.FindClosestRotationBin(36,Ori);
					//利用高斯加权累加进直方图相应的块
					orienthist[binIdx]=orienthist[binIdx]+1.0*mag*MAT(mm,nn);
					
				}
			}
			//找出方向直方图中的峰值
			aa.AverageWeakBins(orienthist,36);
			//找出最大值
			double maxGrad=0.0;
			int maxBin=0;
			for (int b=0;b<36;++b)
			{
				if (orienthist[b] > maxGrad)
				{
					maxGrad=orienthist[b];
					maxBin=b;
				}
			}
			double maxPeakValue=0.0;
			double maxDegreeOriention=0.0;
			/*if((InterpolateOrientation(orienthist[maxBin==0 ? (36-1) : (maxBin-1)],orienthist[maxBin],
				orienthist[(maxBin+1) % 36],&maxDegreeOriention,&maxPeakValue))==false)
				printf("BUG: Parabola fitting broken");*/

			bool binIsKeypoint[36];
			for (b=0;b<36;++b)
			{
				binIsKeypoint[b]=false;
				if (b==maxBin)
				{
					binIsKeypoint[b]=true;
					continue;
				}
			
				if(orienthist[b] < (peakRelThresh * maxPeakValue))
					continue;
				int leftI=(b==0) ? (36-1) :(b-1);
				int rightI=(b+1) % 36;
				if(orienthist[b]<=orienthist[leftI] || orienthist[b] <= orienthist[rightI])
					continue;
				binIsKeypoint[b]=true;

			}
			//寻找另一个可能的点
			double oneBinRad=(2.0 * pi) / 36;
			for (b=0;b<36;++b)
			{
				if (binIsKeypoint[b]==false)
					continue;
				int bLeft=(b==0) ? (36-1) : (b-1);
				int bRight=(b+1) % 36;
				double peakValue;
				double degreeCorrection;

				double maxPeakValue,maxDegreeOriention;
				if (aa.InterpolateOrientation ( orienthist[maxBin == 0 ? (36 - 1) : (maxBin - 1)],
                    orienthist[maxBin], orienthist[(maxBin + 1) % 36],
                    &degreeCorrection, &peakValue) == false)
				{
					printf("BUG: Parabola fitting broken");
				}

				double degree=(b+degreeCorrection) * oneBinRad-pi;
				if(degree < -pi)
					degree+=2.0*pi;
				else if(degree > pi)
					degree-=2.0*pi;
				//存储方向，可以直接利用检测到的链表进行该步主方向的指定；
				//分配内存重新存储特征点
				Keypoint k;
				//allocate memory for the keypoint descriptor
			
				k=(Keypoint) malloc(sizeof(struct KeypointSt));
				k->next=aa.keyDescriptors2;
				aa.keyDescriptors2=k;
				k->descrip=(float*)malloc(LEN * sizeof(float));
				k->row=p->row;
				k->col=p->col;
				k->sy = p->sy;    //行
				k->sx = p->sx;    //列
				k->octave = p->octave;
				k->level = p->level;
				k->scale = p->scale;      
                k->ori = degree;
                k->mag = peakValue;

			}
			free(orienthist);
				

			



			
		}
		p=p->next;

	}

}


void stitchimage::DisplayOrientation2(IplImage *image,ImageOctaves *Gaussianpyr)
{
	p2=aa.keyDescriptors2;//p指向第一个节点,keyDescriptors一定要初始化为零
	while (p2)//没到表尾
	{
		float scale=(Gaussianpyr[p2->octave].Octave)[p2->level].absolute_sigma;
		float autoscale=3.0;
		float uu=autoscale*scale*cos(p2->ori);
		float vv=autoscale*scale*sin(p2->ori);
		float x=(p2->col)+uu;
		float y=(p2->row)+vv;
		
		cvLine(image, cvPoint((int)(p2->col),(int)(p2->row)), 
			cvPoint((int)x,(int)y), CV_RGB(255,255,0),
			1, 8, 0 );
		float alpha=0.33;
		float beta=0.33;
		
		float xx0=(p2->col)+uu-alpha*(uu+beta*vv);
		float yy0=(p2->row)+vv-alpha*(vv-beta*uu);
		float xx1=(p2->col)+uu-alpha*(uu-beta*vv);
		float yy1=(p2->row)+vv-alpha*(vv+beta*uu);
		cvLine(image,cvPoint((int)xx0,(int)yy0),cvPoint((int)x,(int)y),CV_RGB(255,255,0),1,8,0);
		cvLine(image,cvPoint((int)xx1,(int)yy1),cvPoint((int)x,(int)y),CV_RGB(255,255,0),1,8,0);
		p2=p2->next;
	}
	
}

void stitchimage::Onstep42() 
{
	// TODO: Add your control notification handler code here
	ComputeGrad_DirecandMag2(aa.numoctaves,Gaussianpyr2);
	AssignTheMainOrientation2(aa.numoctaves,Gaussianpyr2,mag_pyr2,grad_pyr2);
	//cvCopy(imageptocy2,image2,NULL);
	DisplayOrientation2(image2,Gaussianpyr2);
	
//	cvSaveImage("D:\mag2.jpg",image2);
	cvNamedWindow("image22",2);//cvNamedWindow("image22",1)1是代表窗口的大小
	cvShowImage("image22",image2);
	//cvReleaseImage(& image2);
	cvWaitKey(0);  
    cvDestroyWindow("image22");
}


void stitchimage::ExtractFeatureDescriptors1(int numoctaves,ImageOctaves *Gaussianpyr)
{
	//主要有八个方向
	float orient_bin_spacing=pi/4;
	float orient_angles[8]={-pi,-pi+orient_bin_spacing,-pi*0.5,-orient_bin_spacing,
	0.0,orient_bin_spacing,pi*0.5,pi+orient_bin_spacing};
	//产生描述子中心各点坐标
	float *feat_grid=(float *) malloc(2*16*sizeof(float));
	for (int i=0;i<GridSpacing;i++)//GridSpacing=4
	{
		for (int j=0;j<2*GridSpacing;++j,++j)
		{
			feat_grid[i*2*GridSpacing+j]=-6.0+i*GridSpacing;
			feat_grid[i*2*GridSpacing+j+1]=-6.0+0.5*j*GridSpacing;
		}
	}
	//产生网格
	float *feat_samples=(float *) malloc(2*256*sizeof(float));
	for (i=0;i<4*GridSpacing;i++)
	{
		for (int j=0;j<8*GridSpacing;j+=2)
		{
			feat_samples[i*8*GridSpacing+j]=-(2*GridSpacing-0.5)+i;
			feat_samples[i*8*GridSpacing+j+1]=-(2*GridSpacing-0.5)+0.5*j;
		}
	}
	float feat_window=2*GridSpacing;
	p1=aa.keyDescriptors1;//p1指向第一个节点
	while(p1)//没到表尾
	{
		float scale=(Gaussianpyr[p1->octave].Octave)[p1->level].absolute_sigma;
		float sine=sin(p1->ori);
		float cosine=cos(p1->ori);
		//计算中心点坐标旋转后的位置
		float *featcenter=(float *) malloc(2*16*sizeof(float));
		for (int i=0;i<GridSpacing;i++)
		{
			for (int j=0;j<2*GridSpacing;j+=2)
			{
				float x=feat_grid[i*2*GridSpacing+j];
				float y=feat_grid[i*2*GridSpacing+j+1];
				featcenter[i*2*GridSpacing+j]=((cosine * x + sine * y)+p1->sx);
				featcenter[i*2*GridSpacing+j+1]=((-sine * x + cosine * y)+p1->sy);

			}
		}
		
		float *feat=(float *) malloc(2*256*sizeof(float));

	//原程序有误
		for (i=0;i<2*64*GridSpacing;i++,i++)
		{
			float x=feat_samples[i];
			float y=feat_samples[i+1];
			feat[i]=((cosine * x + sine * y )+p1->sx);
			feat[i+1]=((-sine * x + cosine * y)+p1->sy);
		}

		//初始化特征点描述
		float *feat_desc=(float *) malloc(128 * sizeof(float));
		for (i=0;i<128;i++)
		{
			feat_desc[i]=0.0;
		}
		for (i=0;i<512;++i,++i)
		{
			float x_sample=feat[i];
			float y_sample=feat[i+1];
			float sample12=aa.getPixelBI(((Gaussianpyr[p1->octave].Octave)[p1->level]).Level, x_sample, y_sample-1);
			float sample21=aa.getPixelBI(((Gaussianpyr[p1->octave].Octave)[p1->level]).Level, x_sample-1, y_sample); 
			float sample22=aa.getPixelBI(((Gaussianpyr[p1->octave].Octave)[p1->level]).Level, x_sample, y_sample); 
			float sample23=aa.getPixelBI(((Gaussianpyr[p1->octave].Octave)[p1->level]).Level, x_sample+1, y_sample); 
			float sample32=aa.getPixelBI(((Gaussianpyr[p1->octave].Octave)[p1->level]).Level, x_sample, y_sample+1); 
			float diff_x=sample23-sample21;
			float diff_y=sample32-sample12;
			float mag_sample=sqrt(diff_x*diff_x+diff_y*diff_y);
			float grad_sample=atan(diff_y / diff_x);
			if(grad_sample==CV_PI)
				grad_sample=-CV_PI;
			//计算x，y方向的权重
			float *x_wght=(float *) malloc(GridSpacing * GridSpacing * sizeof(float));
			float *y_wght=(float *) malloc(GridSpacing * GridSpacing * sizeof(float));
			float *pos_wght=(float *) malloc(8*GridSpacing*GridSpacing*sizeof(float));
			for (int m=0;m<32;++m,++m)
			{
				float x=featcenter[m];
				float y=featcenter[m+1];
				x_wght[m/2]=max(1-(fabs(x-x_sample)*1.0/GridSpacing),0);
				y_wght[m/2]=max(1-(fabs(y-y_sample)*1.0/GridSpacing),0);

			}
			for ( m=0;m<16;++m)
				for(int n=0;n<8;++n)
					pos_wght[m*8+n]=x_wght[m]*y_wght[m];
			free(x_wght);
			free(y_wght);
			//计算方向的加权，首先旋转梯度场到主方向，然后计算差异
			float diff[8],orient_wght[128];
			for (m=0;m<8;++m)
			{
				float angle=grad_sample-(p1->ori)-orient_angles[m]+CV_PI;
				float temp=angle / (2.0 * CV_PI);
				angle-=(int)(temp) * (2.0*CV_PI);
				diff[m]=angle-CV_PI;
			}
			//计算高斯权重
			float x=p1->sx;
			float y=p1->sy;
			float g=exp(-((x_sample-x)*(x_sample-x)+(y-y_sample)*(y-y_sample))/(2*feat_window*feat_window)
				)/(2*CV_PI*feat_window*feat_window);
			for (m=0;m<128;++m)
			{
				orient_wght[m]=max((1.0 - 1.0*fabs(diff[m%8])/orient_bin_spacing),0);
				feat_desc[m]=feat_desc[m] + orient_wght[m]*pos_wght[m]*g*mag_sample;

			}
			free(pos_wght);
				


		}
		free(feat);
		free(featcenter);
		float norm=aa.GetVecNorm(feat_desc,128);
		for (int m=0;m<128;m++)
		{
			feat_desc[m]/=norm;
			if (feat_desc[m]>0.2)
			{
				feat_desc[m]=0.2;
			}
		}
		norm=aa.GetVecNorm(feat_desc,128);
		for (m=0;m<128;m++)
		{
			feat_desc[m]/=norm;
		}
		p1->descrip=feat_desc;
		p1=p1->next;
		//free(feat_desc);//不能使用，否则内存会在同一个地址使用
	}
	free(feat_grid);
	free(feat_samples);


}
void stitchimage::Onstep51() 
{
	// TODO: Add your control notification handler code here
	ExtractFeatureDescriptors1(aa.numoctaves,Gaussianpyr1);
}

void stitchimage::ExtractFeatureDescriptors2(int numoctaves,ImageOctaves *Gaussianpyr)
{
	//主要有八个方向
	float orient_bin_spacing=pi/4;
	float orient_angles[8]={-pi,-pi+orient_bin_spacing,-pi*0.5,-orient_bin_spacing,
	0.0,orient_bin_spacing,pi*0.5,pi+orient_bin_spacing};
	//产生描述子中心各点坐标
	float *feat_grid=(float *) malloc(2*16*sizeof(float));
	for (int i=0;i<GridSpacing;i++)//GridSpacing=4
	{
		for (int j=0;j<2*GridSpacing;++j,++j)
		{
			feat_grid[i*2*GridSpacing+j]=-6.0+i*GridSpacing;
			feat_grid[i*2*GridSpacing+j+1]=-6.0+0.5*j*GridSpacing;
		}
	}
	//产生网格
	float *feat_samples=(float *) malloc(2*256*sizeof(float));
	for (i=0;i<4*GridSpacing;i++)
	{
		for (int j=0;j<8*GridSpacing;j+=2)
		{
			feat_samples[i*8*GridSpacing+j]=-(2*GridSpacing-0.5)+i;
			feat_samples[i*8*GridSpacing+j+1]=-(2*GridSpacing-0.5)+0.5*j;
		}
	}
	float feat_window=2*GridSpacing;
	p2=aa.keyDescriptors2;//p指向第一个节点
	while(p2)//没到表尾
	{
		float scale=(Gaussianpyr[p2->octave].Octave)[p2->level].absolute_sigma;
		float sine=sin(p2->ori);
		float cosine=cos(p2->ori);
		//计算中心点坐标旋转后的位置
		float *featcenter=(float *) malloc(2*16*sizeof(float));
		for (int i=0;i<GridSpacing;i++)
		{
			for (int j=0;j<2*GridSpacing;j+=2)
			{
				float x=feat_grid[i*2*GridSpacing+j];
				float y=feat_grid[i*2*GridSpacing+j+1];
				featcenter[i*2*GridSpacing+j]=((cosine * x + sine * y)+p2->sx);
				featcenter[i*2*GridSpacing+j+1]=((-sine * x + cosine * y)+p2->sy);

			}
		}
		
		float *feat=(float *) malloc(2*256*sizeof(float));

		//原程序有误
		for (i=0;i<2*64*GridSpacing;i++,i++)
		{
			float x=feat_samples[i];
			float y=feat_samples[i+1];
			feat[i]=((cosine * x + sine * y )+p2->sx);
			feat[i+1]=((-sine * x + cosine * y)+p2->sy);
		}

		//初始化特征点描述
		
		//float *feat_desc=(float *) malloc(128 * sizeof(float));

		float *feat_desc=(float *) malloc(128 * sizeof(float));
		
		for (i=0;i<128;i++)
		{
			feat_desc[i]=0.0;
		}
		for (i=0;i<512;++i,++i)
		{
			float x_sample=feat[i];
			float y_sample=feat[i+1];
			float sample12=aa.getPixelBI(((Gaussianpyr[p2->octave].Octave)[p2->level]).Level, x_sample, y_sample-1);
			float sample21=aa.getPixelBI(((Gaussianpyr[p2->octave].Octave)[p2->level]).Level, x_sample-1, y_sample); 
			float sample22=aa.getPixelBI(((Gaussianpyr[p2->octave].Octave)[p2->level]).Level, x_sample, y_sample); 
			float sample23=aa.getPixelBI(((Gaussianpyr[p2->octave].Octave)[p2->level]).Level, x_sample+1, y_sample); 
			float sample32=aa.getPixelBI(((Gaussianpyr[p2->octave].Octave)[p2->level]).Level, x_sample, y_sample+1); 
			float diff_x=sample23-sample21;
			float diff_y=sample32-sample12;
			float mag_sample=sqrt(diff_x*diff_x+diff_y*diff_y);
			float grad_sample=atan(diff_y / diff_x);
			if(grad_sample==CV_PI)
				grad_sample=-CV_PI;
			//计算x，y方向的权重
			float *x_wght=(float *) malloc(GridSpacing * GridSpacing * sizeof(float));
			float *y_wght=(float *) malloc(GridSpacing * GridSpacing * sizeof(float));
			float *pos_wght=(float *) malloc(8*GridSpacing*GridSpacing*sizeof(float));
			for (int m=0;m<32;++m,++m)
			{
				float x=featcenter[m];
				float y=featcenter[m+1];
				x_wght[m/2]=max(1-(fabs(x-x_sample)*1.0/GridSpacing),0);
				y_wght[m/2]=max(1-(fabs(y-y_sample)*1.0/GridSpacing),0);

			}
			for ( m=0;m<16;++m)
				for(int n=0;n<8;++n)
					pos_wght[m*8+n]=x_wght[m]*y_wght[m];
			free(x_wght);
			free(y_wght);
			//计算方向的加权，首先旋转梯度场到主方向，然后计算差异
			float diff[8],orient_wght[128];
			for (m=0;m<8;++m)
			{
				float angle=grad_sample-(p2->ori)-orient_angles[m]+CV_PI;
				float temp=angle / (2.0 * CV_PI);
				angle-=(int)(temp) * (2.0*CV_PI);
				diff[m]=angle-CV_PI;
			}
			//计算高斯权重
			float x=p2->sx;
			float y=p2->sy;
			float g=exp(-((x_sample-x)*(x_sample-x)+(y-y_sample)*(y-y_sample))/(2*feat_window*feat_window)
				)/(2*CV_PI*feat_window*feat_window);
			for (m=0;m<128;++m)
			{
				orient_wght[m]=max((1.0 - 1.0*fabs(diff[m%8])/orient_bin_spacing),0);
				feat_desc[m]=feat_desc[m] + orient_wght[m]*pos_wght[m]*g*mag_sample;

			}
			free(pos_wght);
				


		}
		free(feat);
		free(featcenter);
		float norm=aa.GetVecNorm(feat_desc,128);
		for (int m=0;m<128;m++)
		{
			feat_desc[m]/=norm;
			if (feat_desc[m]>0.2)
			{
				feat_desc[m]=0.2;
			}
		}
		norm=aa.GetVecNorm(feat_desc,128);
		for (m=0;m<128;m++)
		{
			feat_desc[m]/=norm;
		}
		p2->descrip=feat_desc;
		p2=p2->next;
		//free(feat_desc);

		
	}
	free(feat_grid);
	free(feat_samples);
	

}

void stitchimage::Onstep52() 
{
	// TODO: Add your control notification handler code here
	ExtractFeatureDescriptors2(aa.numoctaves,Gaussianpyr2);
}


void stitchimage::stitch()
{
	p1=aa.keyDescriptors1;
	p2=aa.keyDescriptors2;
	Keyaxis xy[200];
	float dis;
	
	float distance1,distance2;
	int k=0;
	int x1,y1,x2,y2;
	int nn;
	int count=0;
	int m=0;
	float min,min1;
	while(p2)
	{
		k=k+1;
		p2=p2->next;
	}


	while(p1)
	{
		
		min=100,min1=100;
		float *fest_desc1=(float *) malloc(128 * sizeof(float));
		//float *fest_desc1;
		//fest_desc1=new float[128];
		//memcpy(fest_desc1,p1->descrip,128 * sizeof(float));
	/*	for (int i=0;i<128;i++)
		{
			fest_desc1[i]=*(p1->descrip);
			(p1->descrip)++;

		}*/
		fest_desc1=p1->descrip;
		
		float sum[200];
		for (int j=0;j<200;j++)
			sum[j]=0.0;
		int n=0;
		
		p2=aa.keyDescriptors2;
		while(p2)
		{
			
			float *fest_desc2=(float *) malloc(128*sizeof(float));
			//memcpy(fest_desc2,p2->descrip,128 * sizeof(float));
			fest_desc2=p2->descrip;
			
			for (int i=0;i<128;i++)
			{
				dis=fabs(fest_desc1[i]-fest_desc2[i]);
				sum[n]=sum[n]+dis;
			


			}
			if (sum[n]<min)
			{
				min=sum[n];
				distance1=min;
				nn=n;
			}
			n=n+1;
			//free(fest_desc2);
			p2=p2->next;
		}
		for (int i=0;i<k;i++)
		{
			if (i!=nn)
			{
				if (sum[i]<min1)
				{
					min1=sum[i];
					distance2=min1;

				}

			}
		}
		if (distance1*1.0/distance2<0.6)
		{
			n=0;
			p2=aa.keyDescriptors2;
			while(p2)
			{
				if (n==nn)
				{
					xy[m].width1=p1->col;
					xy[m].height1=p1->row;
					xy[m].width2=p2->col;
					xy[m].height2=p2->row;
					m++;
					count++;

				}
				n++;
				p2=p2->next;

			}
			
		}


		/*int k1,k2;//冒泡排序
		float temp=0;
		for (k1=1;k1<k;k1++)
		{
			for (k2=k-1;k2>=k1;k2--)
			{
				if (sum[k2]<sum[k2-1])
				{
					temp=sum[k2-1];
					sum[k2-1]=sum[k2];
					sum[k2]=temp;
				}
			}
		}*/
		

		
		
		//delete fest_desc1;
		//free(fest_desc1);
		//fest_desc1=NULL;
		p1=p1->next;

	}
//	free(fest_desc1);

	int mm=0;
	for (int i=0;i<count-1;i++)
	{
		
		if ((xy[i].width1-xy[i].width2)<100 || (xy[i].width1==xy[i+1].width1))
		continue;
		xy1[mm].width1=xy[i].width1;
		xy1[mm].height1=xy[i].height1;
		xy1[mm].width2=xy[i].width2;
		xy1[mm].height2=xy[i].height2;
		
		mm++;

	}
	ncount=mm;
//	opencvsolve();
//	gauss();
	Keyaxis xx;
	xx.width1=xy1[0].width1;
	xx.height1=xy1[0].height1;
	xx.width2=xy1[0].width2;
	xx.height2=xy1[0].height2;
	stitchok(xx);


}




void stitchimage::stitch1(IplImage *imag1,IplImage* imag2)
{
	p1=aa.keyDescriptors1;
	p2=aa.keyDescriptors2;
	Keyaxis xy[200];
	Keypoint p3=NULL;
	float dis;
	
	float distance1,distance11,distance2,distance22;
	int k,kk;
	k=0;
	kk=0;
	int x1,y1,x2,y2;
	int n,nn,nnn,n1;
	int count=0;
	int m=0;
	float min,min1;
	while(p2)
	{
		k=k+1;
		p2=p2->next;
	}
	while(p1)
	{
		kk=kk+1;
		p1=p1->next;
	}
	p1=aa.keyDescriptors1;
	while(p1)
	{
		p3=p1;
		min=100,min1=100;
		float *fest_desc1=(float *) malloc(128 * sizeof(float));	
		fest_desc1=p1->descrip;		
		float sum[200];
		for (int j=0;j<200;j++)
			sum[j]=0.0;
		n=0;		
		p2=aa.keyDescriptors2;
		while(p2)
		{
			float *fest_desc2=(float *) malloc(128*sizeof(float));
			fest_desc2=p2->descrip;
			for (int i=0;i<128;i++)
			{
				dis=fabs(fest_desc1[i]-fest_desc2[i]);
				sum[n]=sum[n]+dis;
			}
			if (sum[n]<min)
			{
				min=sum[n];
				distance1=min;
				nn=n;
			}
			n=n+1;
			p2=p2->next;
		}
		for (int i=0;i<k;i++)
		{
			if (i!=nn)
			{
				if (sum[i]<min1)
				{
					min1=sum[i];
					distance2=min1;
				}
			}
		}

		n1=0;
		p2=aa.keyDescriptors2;
		while(p2)
		{
			
			if (n1==nn)
			{
				
				min=100,min1=100;
				float *fest_desc2=(float *) malloc(128 * sizeof(float));	
				fest_desc2=p2->descrip;		
			//	float sum[200];
				for (int j=0;j<200;j++)
				sum[j]=0.0;
				p1=aa.keyDescriptors1;

				n=0;
				while(p1)
				{
					float *fest_desc1=(float *) malloc(128*sizeof(float));
					fest_desc1=p1->descrip;
					
					for (int i=0;i<128;i++)
					{
						dis=fabs(fest_desc2[i]-fest_desc1[i]);
						sum[n]=sum[n]+dis;
					}
				
					if (sum[n]<min)
					{
						min=sum[n];
						distance11=min;
						nnn=n;
					}
					n=n+1;
					p1=p1->next;
				}
				for (int i=0;i<kk;i++)
				{
					if (i!=nnn)
					{
						if (sum[i]<min1)
						{
							min1=sum[i];
							distance22=min1;
						}
					}
				}

			}
			
			n1++;
			p2=p2->next;
		}

		p1=p3;

		//if ((distance1*1.0/distance2<0.4)  && (distance11*1.0/distance22<0.4) && fabs(distance1-distance11)<0.000001)
		if ((distance1*1.0/distance2<0.5)  && (distance11*1.0/distance22<0.5) && (distance1==distance11))
		 
		{
			n=0;
			p2=aa.keyDescriptors2;
			while(p2)
			{
				if (n==nn)
				{
					xy[m].width1=p1->col;
					xy[m].height1=p1->row;
					xy[m].width2=p2->col;
					xy[m].height2=p2->row;
					m++;
					count++;
				}
				n++;
				p2=p2->next;

			}
			
		}
		

		p1=p1->next;

	}

	if (m==0)
	{
		MessageBox("找不到特征点对");
	}
	else
	{
		int wd,hd;
		wd=imag1->width-1550;
		hd=(imag1->height)/2-600;
		Keyaxis xx;
		xx.width1=xy[0].width1+wd;
		xx.height1=xy[0].height1+hd;
		xx.width2=xy[0].width2;
		xx.height2=xy[0].height2+hd;
		stitchok(xx,imag1,imag2);

	}



}

void stitchimage:: stitchok(Keyaxis xx,IplImage* imag1,IplImage* imag2)
{

	int width1;
	width1=imag1->width;

	int x,x1,y,y1,x3,x4,x5,disy;
	x=xx.width1;
	x1=xx.width2;
	x3=width1-x+x1;
	x4=width1-x3;
	x5=width1-x4;
	y=xx.height1;
	y1=xx.height2;
	int dis;
	dis=y-y1;
	disy=abs(y1-y);
	//	disy=27;
	
    
	uchar* data3;
	data3=(uchar*)imag1->imageData;
	uchar* data4;
	data4=(uchar*)imag2->imageData;

	

	int width33,height33;
	image33=NULL;

    CvSize image33_cvsize;
    height33=imag1->height-disy;
	width33=imag1->width+imag2->width-x3;
	image33_cvsize.height=height33;
	image33_cvsize.width=width33;
	uchar *dataout;
	image33 = cvCreateImage(image33_cvsize, imag1->depth,imag1->nChannels);
	dataout=(uchar*)image33->imageData;	
	float d,g;
	

	if (dis<0)
	{
		for(int i=0;i<height33;i++)
			
		{
			d=1.0;
			for(int j=0;j<x4;j++)
			{	
				for(int n=0;n<3;n++)
					dataout[i*image33->widthStep+j*image33->nChannels+n]=
					data3[i*imag1->widthStep+j*imag1->nChannels+n];
			}
			for (j=x4;j<width1;j++)
			{
				g=d-1.0/x3*(j-x4);
				for(int n=0;n<3;n++)
					
				{
					dataout[i*image33->widthStep+j*image33->nChannels+n]=(int)
						(g*data3[i*imag1->widthStep+j*imag1->nChannels+n]+
						(1.0-g)*data4[(i+disy)*imag2->widthStep+(j-x4)*imag2->nChannels+n]);
					
					
					
				}
			}
			for (j=width1;j<width33;j++)
			{
				for(int n=0;n<3;n++)
					dataout[i*image33->widthStep+j*image33->nChannels+n]=
					data4[(i+disy)*imag2->widthStep+(j-x4)*imag2->nChannels+n];
				
			}
			
		}
	}
	else
	{
		for(int i=disy;i<height33+disy;i++)
			
		{
			d=1.0;
			for(int j=0;j<x4;j++)
			{	
				for(int n=0;n<3;n++)
					dataout[(i-disy)*image33->widthStep+j*image33->nChannels+n]=
					data3[i*imag1->widthStep+j*imag1->nChannels+n];
			}
			for (j=x4;j<width1;j++)
			{
				g=d-1.0/x3*(j-x4);
				for(int n=0;n<3;n++)
					
				{
					dataout[(i-disy)*image33->widthStep+j*image33->nChannels+n]=(int)
						(g*data3[i*imag1->widthStep+j*imag1->nChannels+n]+
						(1.0-g)*data4[(i-disy)*imag2->widthStep+(j-x4)*imag2->nChannels+n]);
					
					
					
				}
			}
			for (j=width1;j<width33;j++)
			{
				for(int n=0;n<3;n++)
					dataout[(i-disy)*image33->widthStep+j*image33->nChannels+n]=
					data4[(i-disy)*imag2->widthStep+(j-x4)*imag2->nChannels+n];
				
			}
			
		}

	}

	
	
/*	IplImage* dst1=NULL;
	dst1=cvCreateImage(cvGetSize(image33),image33->depth,image33->nChannels);
	cvCopy(image33,dst1,NULL);
	
	cvSaveImage("D:/fullimag.jpg",image33);
	float wscale = 0.25;		
    float hscale = 0.22;
    CvSize dst1_cvsize;	
	dst1_cvsize.width = image33->width * wscale;		//目标图像的宽为源图象宽的scale倍
    dst1_cvsize.height = image33->height * hscale;	//目标图像的高为源图象高的scale倍
	
    dst1 = cvCreateImage( dst1_cvsize, image33->depth, image33->nChannels);	//构造目标图象
    cvResize(image33, dst1, CV_INTER_LINEAR);	//缩放源图像到目标图像	
	cvNamedWindow( "全景图",   CV_WINDOW_AUTOSIZE );	//创建用于显示目标图像的窗口	
    cvShowImage( "全景图", dst1 );		//显示目标图像
	cvMoveWindow( "全景图",0,500);
	cvWaitKey(-1);
    cvReleaseImage(&dst1);	//释放目标图像占用的内存
   	cvDestroyWindow( "全景图" );	//销毁窗口“dst”*/

}


void stitchimage::stitch1()
{
	p1=aa.keyDescriptors1;
	p2=aa.keyDescriptors2;
	Keyaxis xy[200];
	Keypoint p3=NULL;
	float dis;
	
	float distance1,distance11,distance2,distance22;
	int k,kk;
	k=0;
	kk=0;
	int x1,y1,x2,y2;
	int n,nn,nnn,n1;
	int count=0;
	int m=0;
	float min,min1;
	while(p2)
	{
		k=k+1;
		p2=p2->next;
	}
	while(p1)
	{
		kk=kk+1;
		p1=p1->next;
	}
	p1=aa.keyDescriptors1;
	while(p1)
	{
		p3=p1;
		min=100,min1=100;
		float *fest_desc1=(float *) malloc(128 * sizeof(float));	
		fest_desc1=p1->descrip;		
		float sum[200];
		for (int j=0;j<200;j++)
			sum[j]=0.0;
		n=0;		
		p2=aa.keyDescriptors2;
		while(p2)
		{
			float *fest_desc2=(float *) malloc(128*sizeof(float));
			fest_desc2=p2->descrip;
			for (int i=0;i<128;i++)
			{
				dis=fabs(fest_desc1[i]-fest_desc2[i]);
				sum[n]=sum[n]+dis;
			}
			if (sum[n]<min)
			{
				min=sum[n];
				distance1=min;
				nn=n;
			}
			n=n+1;
			p2=p2->next;
		}
		for (int i=0;i<k;i++)
		{
			if (i!=nn)
			{
				if (sum[i]<min1)
				{
					min1=sum[i];
					distance2=min1;
				}
			}
		}

		n1=0;
		p2=aa.keyDescriptors2;
		while(p2)
		{
			
			if (n1==nn)
			{
				
				min=100,min1=100;
				float *fest_desc2=(float *) malloc(128 * sizeof(float));	
				fest_desc2=p2->descrip;		
			//	float sum[200];
				for (int j=0;j<200;j++)
				sum[j]=0.0;
				p1=aa.keyDescriptors1;

				n=0;
				while(p1)
				{
					float *fest_desc1=(float *) malloc(128*sizeof(float));
					fest_desc1=p1->descrip;
					
					for (int i=0;i<128;i++)
					{
						dis=fabs(fest_desc2[i]-fest_desc1[i]);
						sum[n]=sum[n]+dis;
					}
				
					if (sum[n]<min)
					{
						min=sum[n];
						distance11=min;
						nnn=n;
					}
					n=n+1;
					p1=p1->next;
				}
				for (int i=0;i<kk;i++)
				{
					if (i!=nnn)
					{
						if (sum[i]<min1)
						{
							min1=sum[i];
							distance22=min1;
						}
					}
				}

			}
			
			n1++;
			p2=p2->next;
		}

		p1=p3;

		//if ((distance1*1.0/distance2<0.4)  && (distance11*1.0/distance22<0.4) && fabs(distance1-distance11)<0.000001)
		if ((distance1*1.0/distance2<0.4)  && (distance11*1.0/distance22<0.4) && (distance1==distance11))
		 
		{
			n=0;
			p2=aa.keyDescriptors2;
			while(p2)
			{
				if (n==nn)
				{
					xy[m].width1=p1->col;
					xy[m].height1=p1->row;
					xy[m].width2=p2->col;
					xy[m].height2=p2->row;
					m++;
					count++;
				}
				n++;
				p2=p2->next;

			}
			
		}
		

		p1=p1->next;

	}

	if (m==0)
	{
		MessageBox("找不到特征点对");
	}
	else
	{
		int wd,hd;
		wd=imageptocy11->width-1550;
		hd=(imageptocy11->height)/2-600;
		Keyaxis xx;
		xx.width1=xy[0].width1+wd;
		xx.height1=xy[0].height1+hd;
		xx.width2=xy[0].width2;
		xx.height2=xy[0].height2+hd;
		stitchok(xx);

	}



}

void stitchimage::stitch2()
{
	p1=aa.keyDescriptors1;
	p2=aa.keyDescriptors2;
	Keyaxis xy[200];
	Keypoint p3=NULL;
	float dis;
	
	float distance1,distance11,distance2,distance22;
	int k,kk;
	k=0;
	kk=0;
	int x1,y1,x2,y2;
	int n,nn,nnn,n1;
	int count=0;
	int m=0;
	float min,min1;
	while(p2)
	{
		k=k+1;
		p2=p2->next;
	}
	while(p1)
	{
		kk=kk+1;
		p1=p1->next;
	}
	p1=aa.keyDescriptors1;
	while(p1)
	{
		p3=p1;
		min=100,min1=100;
		float *fest_desc1=(float *) malloc(128 * sizeof(float));	
		fest_desc1=p1->descrip;		
		float sum[200];
		for (int j=0;j<200;j++)
			sum[j]=0.0;
		n=0;		
		p2=aa.keyDescriptors2;
		while(p2)
		{
			float *fest_desc2=(float *) malloc(128*sizeof(float));
			fest_desc2=p2->descrip;
			for (int i=0;i<128;i++)
			{
				dis=fabs(fest_desc1[i]-fest_desc2[i]);
				sum[n]=sum[n]+dis;
			}
			if (sum[n]<min)
			{
				min=sum[n];
				distance1=min;
				nn=n;
			}
			n=n+1;
			p2=p2->next;
		}
		for (int i=0;i<k;i++)
		{
			if (i!=nn)
			{
				if (sum[i]<min1)
				{
					min1=sum[i];
					distance2=min1;
				}
			}
		}

		n1=0;
		p2=aa.keyDescriptors2;
		while(p2)
		{
			
			if (n1==nn)
			{
				
				min=100,min1=100;
				float *fest_desc2=(float *) malloc(128 * sizeof(float));	
				fest_desc2=p2->descrip;		
			//	float sum[200];
				for (int j=0;j<200;j++)
				sum[j]=0.0;
				p1=aa.keyDescriptors1;

				n=0;
				while(p1)
				{
					float *fest_desc1=(float *) malloc(128*sizeof(float));
					fest_desc1=p1->descrip;
					
					for (int i=0;i<128;i++)
					{
						dis=fabs(fest_desc2[i]-fest_desc1[i]);
						sum[n]=sum[n]+dis;
					}
				
					if (sum[n]<min)
					{
						min=sum[n];
						distance11=min;
						nnn=n;
					}
					n=n+1;
					p1=p1->next;
				}
				for (int i=0;i<kk;i++)
				{
					if (i!=nnn)
					{
						if (sum[i]<min1)
						{
							min1=sum[i];
							distance22=min1;
						}
					}
				}

			}
			
			n1++;
			p2=p2->next;
		}

		p1=p3;

		//if ((distance1*1.0/distance2<0.4)  && (distance11*1.0/distance22<0.4) && fabs(distance1-distance11)<0.000001)
		if ((distance1*1.0/distance2<0.4)  && (distance11*1.0/distance22<0.4) && (distance1==distance11))
		 
		{
			n=0;
			p2=aa.keyDescriptors2;
			while(p2)
			{
				if (n==nn)
				{
					xy[m].width1=p1->col;
					xy[m].height1=p1->row;
					xy[m].width2=p2->col;
					xy[m].height2=p2->row;
					m++;
					count++;
				}
				n++;
				p2=p2->next;

			}
			
		}
		

		p1=p1->next;

	}

	if (m==0)
	{
		MessageBox("找不到特征点对");
	}
	else
	{
		
		Keyaxis xx;
		xx.width1=xy[0].width1;
		xx.height1=xy[0].height1;
		xx.width2=xy[0].width2;
		xx.height2=xy[0].height2;
		stitchok(xx);

	}

}

void stitchimage::stitch2(IplImage* imag1,IplImage* imag2)
{
	p1=aa.keyDescriptors1;
	p2=aa.keyDescriptors2;
	Keyaxis xy[200];
	Keypoint p3=NULL;
	float dis;
	
	float distance1,distance11,distance2,distance22;
	int k,kk;
	k=0;
	kk=0;
	int x1,y1,x2,y2;
	int n,nn,nnn,n1;
	int count=0;
	int m=0;
	float min,min1;
	while(p2)
	{
		k=k+1;
		p2=p2->next;
	}
	while(p1)
	{
		kk=kk+1;
		p1=p1->next;
	}
	p1=aa.keyDescriptors1;
	while(p1)
	{
		p3=p1;
		min=100,min1=100;
		float *fest_desc1=(float *) malloc(128 * sizeof(float));	
		fest_desc1=p1->descrip;		
		float sum[200];
		for (int j=0;j<200;j++)
			sum[j]=0.0;
		n=0;		
		p2=aa.keyDescriptors2;
		while(p2)
		{
			float *fest_desc2=(float *) malloc(128*sizeof(float));
			fest_desc2=p2->descrip;
			for (int i=0;i<128;i++)
			{
				dis=fabs(fest_desc1[i]-fest_desc2[i]);
				sum[n]=sum[n]+dis;
			}
			if (sum[n]<min)
			{
				min=sum[n];
				distance1=min;
				nn=n;
			}
			n=n+1;
			p2=p2->next;
		}
		for (int i=0;i<k;i++)
		{
			if (i!=nn)
			{
				if (sum[i]<min1)
				{
					min1=sum[i];
					distance2=min1;
				}
			}
		}

		n1=0;
		p2=aa.keyDescriptors2;
		while(p2)
		{
			
			if (n1==nn)
			{
				
				min=100,min1=100;
				float *fest_desc2=(float *) malloc(128 * sizeof(float));	
				fest_desc2=p2->descrip;		
			//	float sum[200];
				for (int j=0;j<200;j++)
				sum[j]=0.0;
				p1=aa.keyDescriptors1;

				n=0;
				while(p1)
				{
					float *fest_desc1=(float *) malloc(128*sizeof(float));
					fest_desc1=p1->descrip;
					
					for (int i=0;i<128;i++)
					{
						dis=fabs(fest_desc2[i]-fest_desc1[i]);
						sum[n]=sum[n]+dis;
					}
				
					if (sum[n]<min)
					{
						min=sum[n];
						distance11=min;
						nnn=n;
					}
					n=n+1;
					p1=p1->next;
				}
				for (int i=0;i<kk;i++)
				{
					if (i!=nnn)
					{
						if (sum[i]<min1)
						{
							min1=sum[i];
							distance22=min1;
						}
					}
				}

			}
			
			n1++;
			p2=p2->next;
		}

		p1=p3;

		//if ((distance1*1.0/distance2<0.4)  && (distance11*1.0/distance22<0.4) && fabs(distance1-distance11)<0.000001)
		if ((distance1*1.0/distance2<0.5)  && (distance11*1.0/distance22<0.5) && (distance1==distance11))
		 
		{
			n=0;
			p2=aa.keyDescriptors2;
			while(p2)
			{
				if (n==nn)
				{
					xy[m].width1=p1->col;
					xy[m].height1=p1->row;
					xy[m].width2=p2->col;
					xy[m].height2=p2->row;
					m++;
					count++;
				}
				n++;
				p2=p2->next;

			}
			
		}
		

		p1=p1->next;

	}

	if (m==0)
	{
		MessageBox("找不到特征点对");
	}
	else
	{
		
		Keyaxis xx;
		xx.width1=xy[0].width1;
		xx.height1=xy[0].height1;
		xx.width2=xy[0].width2;
		xx.height2=xy[0].height2;
		stitchok(xx,imag1,imag2);

	}

}
void stitchimage::opencvsolve()
{
	int i,j;
	float a[3][3],b[3],mm[3][3];
	for (i=0;i<3;i++)
	{
		a[i][0]=xy1[i+1].width1,a[i][1]=xy1[i+1].height1,a[i][2]=1;
		b[i]=xy1[i+1].width2;
	}

	//赋值给矩阵
	CvMat * A=cvCreateMat(3,3,CV_32FC1);
	int nn=A->cols;
	float *data=A->data.fl;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			data[i*nn+j]=a[i][j];
			
		}
	}

	CvMat * B=cvCreateMat(3,1,CV_32FC1);
	int nn1=B->cols;
	float *data1=B->data.fl;
	for (i=0;i<3;i++)
	{
		
		data1[i*nn1]=b[i];
		
	}

	CvMat * X=cvCreateMat(3,1,CV_32FC1);

	cvSolve(A,B,X,CV_LU);

	for (i=0;i<3;i++)
	{
		mm[0][i]=cvGet2D(X,i,0).val[0];
		
	}

	for (i=0;i<3;i++)
	{
	
		b[i]=xy1[i+1].height2;
	}
	
	//赋值给矩阵
	

	
	for (i=0;i<3;i++)
	{
		
		data1[i*nn1]=b[i];
		
	}
	
	
	
	cvSolve(A,B,X,CV_LU);
	
	for (i=0;i<3;i++)
	{
		mm[1][i]=cvGet2D(X,i,0).val[0];
		
	}
	//求出m6,m7
	
	
	mm[2][0]=-a[0][1]/(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
	mm[2][1]=a[0][0]/(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
	mm[2][2]=1;

	for (i=0;i<ncount;i++)
	{
		
		xy1[i].width2=mm[0][0]*(xy1[i].width1)+mm[0][1]*(xy1[i].height1)+mm[0][2];
		xy1[i].height2=mm[1][0]*xy1[i].width1+mm[1][1]*xy1[i].height1+mm[1][2];
	}


}

void stitchimage::rotateneighbor(IplImage *image,float angle)
{
	int imwidth,imheight;
	imwidth=image->width;
	imheight=image->height;
	//旋转角度，从度转化到弧度
	float frotateangle=2*pi*angle/360;
	//输入图像四个角坐标，以图像中心为坐标原点
	float fsrcx1,fsrcy1,fsrcx2,fsrcy2,fsrcx3,fsrcy3,fsrcx4,fsrcy4;
	//旋转后四个角的坐标，以图像中心为坐标原点
	float fdstx1,fdsty1,fdstx2,fdsty2,fdstx3,fdsty3,fdstx4,fdsty4;
	//计算旋转角度的正弦
	float fsina=(float) sin((double) frotateangle);
	//计算旋转角度的余弦
	float fcosa=(float) cos((double) frotateangle);

	//计算原图四个角的坐标
	fsrcx1=(float) (-(imwidth-1)/2);
	fsrcy1=(float) (imwidth-1)/2;



	

}

int stitchimage::gauss()
{
	int u,p,n=3;
	int i,j,k,d=0;
	float s=0,t,m,f=0;
	float a[3][3],b[3],mm[3][3];
	//求出m0，m1，m2
	for (i=0;i<3;i++)
	{
		a[i][0]=xy1[i].width1,a[i][1]=xy1[i].height1,a[i][2]=1;
		b[i]=xy1[i].width2;
	}
	for (k=0;k<2;k++)
	{
		for (i=k+1;i<3;i++)
		{
			for (u=k;u<3;u++)
			{
				if (fabs(a[u][k]>s))
				{
					s=fabs(a[u][k]);
					p=u;
				}
			}
			if (p!=k)
			{
				d=0;
				for (j=k;j<3;j++)
				{
					t=a[k][j],a[k][j]=a[p][j],a[p][j]=t;
				}
				t=b[k];b[k]=b[p];b[p]=t;
			}
			m=a[i][k]/a[k][k],b[i]=b[i]-m*b[k];
			for (j=k+1;j<3;j++)
			{
				a[i][j]=a[i][j]-m*a[k][j];
			}
			
		}
	}
	b[n-1]=b[n-1]/a[n-1][n-1];
	for (i=n-2;i>=0;i--)
	{
		for (j=i+1;j<n;j++)
		{
			f=a[i][j]*b[j];
		}
		b[i]=(b[i]-f)/a[i][j];
	}
	
	for (i=0;i<n;i++)
	{
		mm[0][i]=b[i];
	}

	//求出m3,m4,m5
	n=3;
	d=0;
	s=0,f=0;
	for (i=0;i<3;i++)
	{
		b[i]=xy1[i].height2;
	}
	for (k=0;k<2;k++)
	{
		for (i=k+1;i<3;i++)
		{
			for (u=k;u<3;u++)
			{
				if (fabs(a[u][k]>s))
				{
					s=fabs(a[u][k]);
					p=u;
				}
			}
			if (p!=k)
			{
				d=0;
				for (j=k;j<3;j++)
				{
					t=a[k][j],a[k][j]=a[p][j],a[p][j]=t;
				}
				t=b[k];b[k]=b[p];b[p]=t;
			}
			m=a[i][k]/a[k][k],b[i]=b[i]-m*b[k];
			for (j=k+1;j<3;j++)
			{
				a[i][j]=a[i][j]-m*a[k][j];
			}
			
		}
	}
	b[n-1]=b[n-1]/a[n-1][n-1];
	for (i=n-2;i>=0;i--)
	{
		for (j=i+1;j<n;j++)
		{
			f=a[i][j]*b[j];
		}
		b[i]=(b[i]-f)/a[i][j];
	}
	
	for (i=0;i<n;i++)
	{
		mm[1][i]=b[i];
	}

	//求出m6,m7


	mm[2][0]=-a[0][1]/(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
	mm[2][1]=a[0][0]/(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
	mm[2][2]=1;

	//赋值给矩阵
	CvMat * M=cvCreateMat(3,3,CV_32FC1);
	int nn=M->cols;
	float *data=M->data.fl;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			data[i*nn+j]=mm[i][j];

		}
	}

	for (i=0;i<ncount;i++)
	{

	xy1[i].width2=mm[0][0]*(xy1[i].width1)+mm[0][1]*(xy1[i].height1)+mm[0][2];
	xy1[i].height2=mm[1][0]*xy1[i].width1+mm[1][1]*xy1[i].height1+mm[1][2];
	}
	

	return 1;
	
	
	
}


void stitchimage:: stitchok(Keyaxis xx)
{

	int width1;
	width1=imageptocy11->width;

	int x,x1,y,y1,x3,x4,x5,disy;
	x=xx.width1;
	x1=xx.width2;
	x3=width1-x+x1;
	x4=width1-x3;
	x5=width1-x4;
	y=xx.height1;
	y1=xx.height2;
	int dis;
	dis=y-y1;
	disy=abs(y1-y);
	//	disy=27;
	
    
	uchar* data3;
	data3=(uchar*)imageptocy11->imageData;
	uchar* data4;
	data4=(uchar*)imageptocy22->imageData;

	

	int width33,height33;
	IplImage *image33=NULL;

    CvSize image33_cvsize;
    height33=imageptocy11->height-disy;
	width33=imageptocy11->width+imageptocy22->width-x3;
	image33_cvsize.height=height33;
	image33_cvsize.width=width33;
	uchar *dataout;
	image33 = cvCreateImage(image33_cvsize, imageptocy11->depth,imageptocy11->nChannels);
	dataout=(uchar*)image33->imageData;	
	float d,g;
	

	if (dis<0)
	{
		for(int i=0;i<height33;i++)
			
		{
			d=1.0;
			for(int j=0;j<x4;j++)
			{	
				for(int n=0;n<3;n++)
					dataout[i*image33->widthStep+j*image33->nChannels+n]=
					data3[i*imageptocy11->widthStep+j*imageptocy11->nChannels+n];
			}
			for (j=x4;j<width1;j++)
			{
				g=d-1.0/x3*(j-x4);
				for(int n=0;n<3;n++)
					
				{
					dataout[i*image33->widthStep+j*image33->nChannels+n]=(int)
						(g*data3[i*imageptocy11->widthStep+j*imageptocy11->nChannels+n]+
						(1.0-g)*data4[(i+disy)*imageptocy22->widthStep+(j-x4)*imageptocy22->nChannels+n]);
					
					
					
				}
			}
			for (j=width1;j<width33;j++)
			{
				for(int n=0;n<3;n++)
					dataout[i*image33->widthStep+j*image33->nChannels+n]=
					data4[(i+disy)*imageptocy22->widthStep+(j-x4)*imageptocy22->nChannels+n];
				
			}
			
		}
	}
	else
	{
		for(int i=disy;i<height33+disy;i++)
			
		{
			d=1.0;
			for(int j=0;j<x4;j++)
			{	
				for(int n=0;n<3;n++)
					dataout[(i-disy)*image33->widthStep+j*image33->nChannels+n]=
					data3[i*imageptocy11->widthStep+j*imageptocy11->nChannels+n];
			}
			for (j=x4;j<width1;j++)
			{
				g=d-1.0/x3*(j-x4);
				for(int n=0;n<3;n++)
					
				{
					dataout[(i-disy)*image33->widthStep+j*image33->nChannels+n]=(int)
						(g*data3[i*imageptocy11->widthStep+j*imageptocy11->nChannels+n]+
						(1.0-g)*data4[(i-disy)*imageptocy22->widthStep+(j-x4)*imageptocy22->nChannels+n]);
					
					
					
				}
			}
			for (j=width1;j<width33;j++)
			{
				for(int n=0;n<3;n++)
					dataout[(i-disy)*image33->widthStep+j*image33->nChannels+n]=
					data4[(i-disy)*imageptocy22->widthStep+(j-x4)*imageptocy22->nChannels+n];
				
			}
			
		}

	}

	
	
	IplImage* dst1=NULL;
	dst1=cvCreateImage(cvGetSize(image33),image33->depth,image33->nChannels);
	cvCopy(image33,dst1,NULL);
	
//	cvSaveImage("D:/fullimag.jpg",image33);
	float wscale = 0.22;		
    float hscale = 0.19;
    CvSize dst1_cvsize;	
	dst1_cvsize.width = image33->width * wscale;		//目标图像的宽为源图象宽的scale倍
    dst1_cvsize.height = image33->height * hscale;	//目标图像的高为源图象高的scale倍
	
    dst1 = cvCreateImage( dst1_cvsize, image33->depth, image33->nChannels);	//构造目标图象
    cvResize(image33, dst1, CV_INTER_LINEAR);	//缩放源图像到目标图像	
	cvNamedWindow( "全景图",   CV_WINDOW_AUTOSIZE );	//创建用于显示目标图像的窗口	
    cvShowImage( "全景图", dst1 );		//显示目标图像
	cvMoveWindow( "全景图",0,500);
	cvWaitKey(-1);
    cvReleaseImage(&dst1);	//释放目标图像占用的内存
   	cvDestroyWindow( "全景图" );	//销毁窗口“dst”

}
void stitchimage::Onsiftstitch() 
{
	// TODO: Add your control notification handler code here
	if (DOGoctaves1!=NULL)
	{
		DOGoctaves1=NULL;
	}
	if (DOGoctaves2!=NULL)
	{
		DOGoctaves2=NULL;
	}
	if (Gaussianpyr1!=NULL)
	{
		Gaussianpyr1=NULL;
	}
	if (Gaussianpyr2!=NULL)
	{
		Gaussianpyr2=NULL;
	}

	int wd,hd;
	wd=imageptocy11->width;
	hd=imageptocy11->height;
	if (wd >= 1600 && hd >= 1200)
	{
		stitch1();
	}
	else
	{
		stitch2();
	}
	
}
