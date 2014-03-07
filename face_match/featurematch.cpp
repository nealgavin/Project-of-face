// featurematch.cpp : implementation file
//

#include "stdafx.h"
#include "imagestitch.h"
#include "featurematch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// featurematch dialog


featurematch::featurematch(CWnd* pParent /*=NULL*/)
	: CDialog(featurematch::IDD, pParent)
{
	//{{AFX_DATA_INIT(featurematch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void featurematch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(featurematch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(featurematch, CDialog)
	//{{AFX_MSG_MAP(featurematch)
	ON_BN_CLICKED(IDC_openimage, Onopenimage)
	ON_BN_CLICKED(IDC_Destory, OnDestory)
	ON_BN_CLICKED(IDC_planetocy, Onplanetocy)
	ON_BN_CLICKED(IDC_step1, Onstep1)
	ON_BN_CLICKED(IDC_step2, Onstep2)
	ON_BN_CLICKED(IDC_detectfeature, Ondetectfeature)
	ON_BN_CLICKED(IDC_step4, Onstep4)
	ON_BN_CLICKED(IDC_step5, Onstep5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// featurematch message handlers

/***************************************************************************
*��������
*   openimage()
*
*��������:
*   ��
*
*����ֵ��
*   ��
*
*˵�����ú�����һ��ͼƬ�����ͼ��ָ��imageone��Ȼ���imageoneͼ�����Ŵ�ŵ�
*dstͼ��ָ�룬��ҪĿ����Ϊ���Ժ��ʵĴ�С�ٴ�������ʾ��      
***************************************************************************/
void featurematch::Onopenimage() 
{
	
	// TODO: Add your control notification handler code here
	CString filename;
	char  szFilter[] = "Jpg Files (*.jpg)|*.jpg|All Files (*.*)|*.*||";
	CFileDialog fdlg(TRUE, "JPG", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);

	if(fdlg.DoModal()!=IDOK)//����һֱ�ٽ�����
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
	dst_cvsize.width = imageone->width * wscale;		//Ŀ��ͼ��Ŀ�ΪԴͼ����scale��
    dst_cvsize.height = imageone->height * hscale;	//Ŀ��ͼ��ĸ�ΪԴͼ��ߵ�scale��
	
    dst = cvCreateImage( dst_cvsize, imageone->depth, imageone->nChannels);	//����Ŀ��ͼ��
    cvResize(imageone, dst, CV_INTER_LINEAR);	//����Դͼ��Ŀ��ͼ��	
	cvNamedWindow( "ͼ��",   CV_WINDOW_AUTOSIZE );	//����������ʾĿ��ͼ��Ĵ���	
    cvShowImage( "ͼ��", dst );		//��ʾĿ��ͼ��
	cvMoveWindow( "ͼ��",0,0);
	cvWaitKey(0);
    cvReleaseImage(&dst);	//�ͷ�Ŀ��ͼ��ռ�õ��ڴ�
   	cvDestroyWindow( "ͼ��1" );	//���ٴ��ڡ�dst��
	cvReleaseImage(&imageone);
	
}


IplImage * featurematch::palnetocylinder1(IplImage *image)
{
	imageptocy=NULL;
	int b=35;
	int width,height;
	int widthnew,heightnew;
	CvSize imageptocy_cvsize;
	width=image->width;
	height=image->height;
	float r=width/(2*tan(2*pi*b/720.1));
	float ff=r*r;
	float k;
	widthnew=(int)(r*b*2*pi/360);
	heightnew=height;
	imageptocy_cvsize.width=widthnew;
	imageptocy_cvsize.height=heightnew;
	uchar* data;
	uchar* dataout;
	data=(uchar*)image->imageData;
	float n1,n2;
	imageptocy=cvCreateImage(imageptocy_cvsize,image->depth, image->nChannels);
	dataout=(uchar *)imageptocy->imageData;
	int coordinatex,coordinatey;
	
	for ( int i=0;i<heightnew;i++)
	{
		
		for (int j=0;j<widthnew;j++)
		{
			
			n1=j-width/2;
			n2=n1*n1;
			k=sqrt(ff+n2);
			coordinatex=(int)(width/2+r*tan((j-r*b*2*pi/720)/r));
            coordinatey=(int)((height/2-k*(height/2-i)/r));
			if ((coordinatex>=0) && (coordinatex<width) && (coordinatey>=0) && (coordinatey<height))
			{
				
				
				for (int n=0;n<3;n++)
				{
					
					dataout[i*imageptocy->widthStep+j*imageptocy->nChannels+n]=
						data[coordinatey*image->widthStep+coordinatex*image->nChannels+n];
					
				}
				
			}
			else
			{
				for(int n=0;n<3;n++)
					dataout[i*imageptocy->widthStep+j*imageptocy->nChannels+n]=0;
				
			}
			
		}
		
	}
	
	
	

	
    //cvReleaseImage(&image);
   
	return imageptocy;
	


}

/***************************************************************************
*��������
*   palnetocylinder()
*
*��������:
*  IplImage *imag-�򿪵�ͼ��
*
*����ֵ��
*   ��
*
*˵�����ú������򿪵�ͼ��ͶӰ��ͼ��imageptocy��Ȼ���imageptocyͼ�����Ŵ�ŵ�
*ds3tͼ��ָ�룬��ҪĿ����Ϊ���Ժ��ʵĴ�С�ٴ�������ʾ��      
***************************************************************************/
void featurematch::palnetocylinder(IplImage *image)
{
	imageptocy=NULL;
	int b=35;
	int width,height;
	int widthnew,heightnew;
	CvSize imageptocy_cvsize;
	width=image->width;
	height=image->height;
	float r=width/(2*tan(2*pi*b/720.1));
	float ff=r*r;
	float k;
	widthnew=(int)(r*b*2*pi/360);
	heightnew=height;
	imageptocy_cvsize.width=widthnew;
	imageptocy_cvsize.height=heightnew;
	uchar* data;
	uchar* dataout;
	data=(uchar*)image->imageData;
	float n1,n2;
	imageptocy=cvCreateImage(imageptocy_cvsize,image->depth, image->nChannels);
	dataout=(uchar *)imageptocy->imageData;
	int coordinatex,coordinatey;
	
	for ( int i=0;i<heightnew;i++)
	{
		
		for (int j=0;j<widthnew;j++)
		{
			
			n1=j-width/2;
			n2=n1*n1;
			k=sqrt(ff+n2);
			coordinatex=(int)(width/2+r*tan((j-r*b*2*pi/720)/r));
            coordinatey=(int)((height/2-k*(height/2-i)/r));
			if ((coordinatex>=0) && (coordinatex<width) && (coordinatey>=0) && (coordinatey<height))
			{
				
				
				for (int n=0;n<3;n++)
				{
					
					dataout[i*imageptocy->widthStep+j*imageptocy->nChannels+n]=
						data[coordinatey*image->widthStep+coordinatex*image->nChannels+n];
					
				}
				
			}
			else
			{
				for(int n=0;n<3;n++)
					dataout[i*imageptocy->widthStep+j*imageptocy->nChannels+n]=255;
				
			}
			
		}
		
	}
	
	
	
	IplImage* dst3=NULL;
	dst3=cvCreateImage(cvGetSize(imageptocy),imageptocy->depth,imageptocy->nChannels);
	cvCopy(imageptocy,dst3,NULL);
	
	
	float wscale ;		
    float hscale ;
	wscale=350.0/widthnew;
	hscale=240.0/heightnew;
    CvSize dst3_cvsize;	
	dst3_cvsize.width = imageptocy->width * wscale;		//Ŀ��ͼ��Ŀ�ΪԴͼ����scale��
    dst3_cvsize.height =imageptocy->height * hscale;	//Ŀ��ͼ��ĸ�ΪԴͼ��ߵ�scale��
	
    dst3 = cvCreateImage( dst3_cvsize, imageptocy->depth, imageptocy->nChannels);	//����Ŀ��ͼ��
    cvResize(imageptocy, dst3, CV_INTER_LINEAR);	//����Դͼ��Ŀ��ͼ��	
	cvNamedWindow( "����ͶӰ1",   CV_WINDOW_AUTOSIZE );	//����������ʾĿ��ͼ��Ĵ���	
    cvShowImage( "����ͶӰ1", dst3 );		//��ʾĿ��ͼ��
	cvMoveWindow( "����ͶӰ1",0,250);
	

	//cutleftimage(imageptocy);


	cvWaitKey(-1);
    cvReleaseImage(&dst3);	//�ͷ�Ŀ��ͼ��ռ�õ��ڴ�
   	cvDestroyWindow( "����ͶӰ1" );	//���ٴ��ڡ�dst��
	if(image!=NULL)
		cvReleaseImage(&image);
/*	if(imageptocy!=NULL)
		cvReleaseImage(&imageptocy);*/
	

}



/***************************************************************************
*��������
*   cutleftimage()
*
*��������:
*IplImage * image
*
*����ֵ��
*  ��
*
*˵�����ú��������ͼ�񣬰Ѵ�ͼ���غϲ��ֲü���Сͼ�� ���ڶ��������  
***************************************************************************/
void featurematch::cutleftimage(IplImage * image)
{
	uchar * datain;
	uchar * tempdata;
	IplImage *temp=NULL;
	CvSize temp_cvsize;
	temp_cvsize.width=640;
	temp_cvsize.height=480;
	temp=cvCreateImage(temp_cvsize,image->depth,image->nChannels);
	tempdata=(uchar *)temp->imageData;
	datain=(uchar *)image->imageData;
	int wd,hg;
	wd=image->width;
	hg=image->height;
	for (int i=0;i<480;i++)
	{
		for (int j=0;j<640;j++)
		{
			for (int n=0;n<3;n++)
			{
				tempdata[i*temp->widthStep+j*temp->nChannels+n]=datain[(hg/2-240+i)*image->widthStep+(100+j)*image->nChannels+n];
			}
		}
	}
	
	cvReleaseImage(&imageptocy);
	
	imageptocy=cvCreateImage(cvGetSize(temp),temp->depth,temp->nChannels);
	cvCopy(temp,imageptocy,NULL);
	cvReleaseImage(&temp);
	
//	cvSaveImage("D:\cutimage.jpg",imageptocy);

}
/***************************************************************************
*��������
*   cutrightimage()
*
*��������:
*IplImage * image
*
*����ֵ��
*  ��
*
*˵�����ú��������ͼ�񣬰Ѵ�ͼ���غϲ��ֲü���Сͼ�� ,��һ�����ұ�  
***************************************************************************/
void featurematch::cutrightimage(IplImage * image)
{
	uchar * datain;
	uchar * tempdata;
	IplImage *temp=NULL;
	CvSize temp_cvsize;
	temp_cvsize.width=640;
	temp_cvsize.height=480;
	temp=cvCreateImage(temp_cvsize,image->depth,image->nChannels);
	tempdata=(uchar *)temp->imageData;
	datain=(uchar *)image->imageData;
	int wd,hg;
	wd=image->width;
	hg=image->height;
	for (int i=0;i<480;i++)
	{
		for (int j=0;j<640;j++)
		{
			for (int n=0;n<3;n++)
			{
				tempdata[i*temp->widthStep+j*temp->nChannels+n]=datain[(hg/2-240+i)*image->widthStep+(wd-700+j)*image->nChannels+n];
			}
		}
	}
	
	cvReleaseImage(&imageptocy);

	imageptocy=cvCreateImage(cvGetSize(temp),temp->depth,temp->nChannels);
	cvCopy(temp,imageptocy,NULL);
	cvReleaseImage(&temp);

//	cvSaveImage("D:\cutimage.jpg",imageptocy);




}


/***************************************************************************
*��������
*   doubleSizeImage2()
*
*��������:
*CvMat * im-ԭͼ���������
*
*����ֵ��
*  CvMat *
*
*˵�����ú�������ԭͼ��һ��    
***************************************************************************/

CvMat * featurematch::doubleSizeImage2(CvMat * im)
{
	unsigned int i,j;
	int w=im->cols*2;
	int h=im->rows*2;
	CvMat *imnew=cvCreateMat(h,w,CV_32FC1);

	#define Im(ROW,COL) ((float *)(im->data.fl + im->step/sizeof(float) *(ROW)))[(COL)]
	#define Imnew(ROW,COL) ((float *)(imnew->data.fl + imnew->step/sizeof(float) *(ROW)))[(COL)]
	for (j=0;j<h;j++)
	{
		for (i=0;i<w;i++)
		{
			Imnew(j,i)=Im(j/2,i/2);

		}
	}

	/*
	A B C
	E F G
	H I J
	����A C H J��ԭ��ͼ�������
	����B E G I F�ǲ�ֵ�������
	*/
	//��ֵ����B��I
	for (j=0;j<h;j+=2)
	{
		for (i=1;i<w-1;i+=2)
		{
			Imnew(j,i)=0.5*(Im(j/2,i/2)+Im(j/2,i/2+1));
		}
	}
	//��ֵ����E��G
	for ( j = 1; j < h - 1; j += 2)
	{
		for ( i = 0; i < w; i += 2)
		{
			Imnew(j,i)=0.5*(Im(j/2, i/2)+Im(j/2+1, i/2));
		}
	}

	for ( j = 1; j < h - 1; j += 2)
	{
		for ( i = 1; i < w - 1; i += 2)
		{
			Imnew(j,i)=0.25*(Im(j/2, i/2)+Im(j/2+1, i/2)+Im(j/2, i/2+1)+Im(j/2+1, i/2+1));
		}
	}
	return imnew;
}


/***************************************************************************
*��������
*   ConvolveLocWidth()
*
*��������:
*	float* kern-��˹��ϵ��
*	int dim
*	CvMat * src-ͼ�����ݾ���
*	int x-ͼ�������
*	int y-ͼ��������
*
*����ֵ��
*  ��
*
*˵�����ú�����Ҫ��x����ÿһ���������    
***************************************************************************/

float featurematch::ConvolveLocWidth(float* kernel, int dim, CvMat * src, int x, int y)
{
	#define Src(ROW,COL) ((float *)(src->data.fl + src->step/sizeof(float) *(ROW)))[(COL)]
	unsigned int i;
	float pixel=0;
	int col;
	int cen=dim/2;
	for (i=0;i<dim;i++)
	{
		col=x+(i-cen);
		if(col<0)
			col=0;
		if(col>=src->cols)
			col=src->cols-1;
		pixel +=kernel[i] * Src(y,col);
	}
	if(pixel > 1)
		pixel=1;
	return pixel;
}



/***************************************************************************
*��������
*   Convolve1DWidth()
*
*��������:
*	float* kern-��˹�˵�ϵ��
*	int dim
*	CvMat * src-ԭͼ�����ݾ���
*	CvMat * dst-��˹������ͼ��
*
*����ֵ��
*  ��
*
*˵�����ú�����Ҫ��x���������    
***************************************************************************/
void featurematch::Convolve1DWidth(float* kern, int dim, CvMat * src, CvMat * dst)
{
	#define  DST(ROW,COL) ((float *)(dst->data.fl + dst->step/sizeof(float) *(ROW)))[(COL)]//row���У�col����
	unsigned int i,j;

	for (j=0;j<src->rows;j++)//��
	{
		for (i=0;i<src->cols;i++)
		{
			DST(j,i)=ConvolveLocWidth(kern,dim,src,i,j);
		}
	}

}

/***************************************************************************
*��������
*   ConvolveLocHeight()
*
*��������:
*	float* kern-��˹��ϵ��
*	int dim
*	CvMat * src-ͼ�����ݾ���
*	int x-ͼ�������
*	int y-ͼ��������
*
*����ֵ��
*  ��
*
*˵�����ú�����Ҫ��y����ÿһ���������    
***************************************************************************/

float featurematch::ConvolveLocHeight(float* kernel, int dim, CvMat * src, int x, int y)
{
	#define Src(ROW,COL) ((float *)(src->data.fl + src->step/sizeof(float) *(ROW)))[(COL)]
    unsigned int j;
	float pixel = 0;
	int cen = dim / 2;
	//printf("ConvolveLoc(): Applying convoluation at location (%d, %d)\n", x, y);
	for ( j = 0; j < dim; j++) 
	{
		int row = y + (j - cen);
		if (row < 0)
			row = 0;
		if (row >= src->rows)
			row = src->rows - 1;
		pixel += kernel[j] * Src(row,x);
	}
	if (pixel > 1)
		pixel = 1;
	return pixel;

}

/***************************************************************************
*��������
*   Convolve1DHeight()
*
*��������:
*	float* kern-��˹�˵�ϵ��
*	int dim
*	CvMat * src-ԭͼ�����ݾ���
*	CvMat * dst-��˹������ͼ��
*
*����ֵ��
*  ��
*
*˵�����ú�����Ҫ��x���������    
***************************************************************************/
void featurematch::Convolve1DHeight(float* kern, int dim, CvMat * src, CvMat * dst)
{

	#define Dst(ROW,COL) ((float *)(dst->data.fl + dst->step/sizeof(float) *(ROW)))[(COL)]
    unsigned int i,j;
	for ( j = 0; j < src->rows; j++) 
	{
		for ( i = 0; i < src->cols; i++) 
		{
			//printf("%d, %d\n", i, j);
			Dst(j,i) = ConvolveLocHeight(kern, dim, src, i, j);
		}
	}

}



/***************************************************************************
*��������
*   GaussianKernel1D(float sigma, int dim)
*
*��������:
*	float sigma-0.5��˹�˵ľ�����
*	int dim-һ����������
*	
*����ֵ��
*  float-
*
*˵�����ú�����Ҫ����1D��˹��    
***************************************************************************/

float*  featurematch::GaussianKernel1D(float sigma, int dim)
{
	unsigned int i;
	float *kern=(float *)malloc( dim*sizeof(float));
	float s2=sigma*sigma;//sigma=0.5;
	int c=dim/2;//c=5/2=2
	float m=1.0/(sqrt(2.0 * CV_PI) * sigma);//m=0.797885
	double v;
	for (i=0;i < (dim +1) / 2;i++)
	{
		v=m*exp(-(1.0*i*i)/(2.0*s2));
		kern[c+i]=v;
		kern[c-i]=v;
	}
	return kern;
}




/***************************************************************************
*��������
*   BlurImage()
*
*��������:
*	CvMat * src-ԭͼ������ݾ���
*	CvMat * dst-ƽ�����ͼ�����ݾ���	
*	float sigma-0.5
*����ֵ��
*  int-
*
*˵�����ú�����Ҫ�Ե�ͼ��ƽ���˲�    
***************************************************************************/
int featurematch:: BlurImage(CvMat * src, CvMat * dst, float sigma)
{
	float *convkernel;
	int dim=(int) max(3.0f,2.0 * GAUSSKERN*sigma+1.0f);//int(4.5)=4Ϊʲô������
	CvMat *tempMat11;
	//��dim������
	if(dim % 2==0)
		dim++;//dim=5
	tempMat11=cvCreateMat(src->rows,src->cols,CV_32FC1);//�������ռ�
	convkernel=GaussianKernel1D(sigma,dim);

	Convolve1DWidth(convkernel,dim,src,tempMat11);
	Convolve1DHeight(convkernel,dim,tempMat11,dst);
	cvReleaseMat(&tempMat11);
	return dim;

}




/***************************************************************************
*��������
*   ScaleInitImage()
*
*��������:
*  CvMat * im-ͼ������ݾ���
*
*����ֵ��
*  CvMat-ͼ������ݾ���
*
*˵�����ú�����Ҫ�������ͼ���������ͼ��Ԥ�˲��޳�������
*�õ�����������ײ�-��һ�׵ĵ�һ��      
***************************************************************************/

CvMat * featurematch:: ScaleInitImage(CvMat * im)
{
	double sigma,preblur_sigma;
	CvMat *imMat=NULL;
	CvMat *dst=NULL;
	CvMat *tempMat=NULL;
	//���ȶ�ͼ�����ƽ���˲�����������
	imMat=cvCreateMat(im->rows,im->cols,CV_32FC1);//�������ռ�
	BlurImage(im,imMat,INITSIGMA);//INITSIGMA=0.5��


	
	//����������ֱ���
	//��ʼ���Ŵ�ԭʼͼ�����ԭͼ������Ͻ��к�������
	//��������������ײ�
/*	if (DOUBLE_BASE_IMAGE_SIZE)//DOUBLE_BASE_IMAGE_SIZE=1
	{
		//tempMat=imMat;
		tempMat=doubleSizeImage2(imMat);//������������ͼ����ж��β�����������0.5���������Բ�ֵ
		#define TEMPMAT(ROW,COL) ((float *)(tempMat->data.fl + tempMat->step/sizeof(float) * (ROW)))[(COL)]
		dst = cvCreateMat(tempMat->rows, tempMat->cols, CV_32FC1);
		preblur_sigma = 1.0;//sqrt(2 - 4*INITSIGMA*INITSIGMA);Ϊʲô���������
		BlurImage(tempMat,dst,preblur_sigma);//��߶ȴ����Ƶ�ɷݣ�С�߶ȴ����Ƶ�ɷ�

		// The initial blurring for the first image of the first octave of the pyramid.
		sigma=sqrt((4*INITSIGMA*INITSIGMA)+preblur_sigma*preblur_sigma);
		//		sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA * 4);
		BlurImage(dst,tempMat,sigma);



		cvReleaseMat(&dst);
		return tempMat;
	}
	else
	{*/
		
		dst=cvCreateMat(im->rows,im->cols,CV_32FC1);
		//sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA);
		preblur_sigma=1.0;//sqrt(2 - 4*INITSIGMA*INITSIGMA);
		sigma=sqrt((4*INITSIGMA*INITSIGMA)+preblur_sigma * preblur_sigma);
		BlurImage(imMat,dst,sigma);
		cvReleaseMat(&imMat);//�޸�
		return dst;

//	}


}

void featurematch::OnDestory() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnDestroy();
	cvReleaseImage(&imageone);
	
	cvDestroyWindow("ͼ��1");
}

void featurematch::Onplanetocy() 
{
	// TODO: Add your control notification handler code here
	palnetocylinder(imageone);
	
	//cutimage(imageptocy);
	cvReleaseImage(&imageone);

}

void featurematch::Onstep1() 
{
	// TODO: Add your control notification handler code here
	image1=NULL;
	grey_im1=NULL;
	DoubleSizeImage=NULL;

	image1Mat=NULL;
	tempMat=NULL;

	
	
	
	//Ϊͼ������ڴ�
	image1=cvCreateImage(cvSize(imageptocy->width,imageptocy->height),imageptocy->depth,imageptocy->nChannels);
	grey_im1=cvCreateImage(cvSize(imageptocy->width,imageptocy->height),IPL_DEPTH_8U,1);
	DoubleSizeImage=cvCreateImage(cvSize(2*(imageptocy->width),2*(imageptocy->height)),IPL_DEPTH_8U,3);
	//Ϊͼ�����з����ڴ棬��������ͼ��Ĵ�С��ͬ��tempMat����image1�Ĵ�С
	image1Mat=cvCreateMat(imageptocy->height,imageptocy->width,CV_32FC1);
	//ת���ɵ�ͨ��ͼ���ٴ���
	cvCvtColor(imageptocy,grey_im1,CV_BGR2GRAY);
	//ת����Mat���ݽṹ��ͼ�����ʹ�õ��Ǹ����Ͳ���
	cvConvert(grey_im1,image1Mat);

	double t=(double)cvGetTickCount();

	//ͼ���һ��
	cvConvertScale(image1Mat,image1Mat,1.0/255,0);

	int dim;
	dim=min(image1Mat->rows,image1Mat->cols);
	//����������
	numoctaves=(int) (log((double)dim) / log(2.0))-2;
	numoctaves=min(numoctaves,MAXOCTAVES);//����������С�ڵ����Ľ�

	//step1Ԥ�˲��������������������ײ㣬�ײ�Ϊԭͼ�������
	tempMat=ScaleInitImage(image1Mat);

	//cvReleaseImage(& image1);
	cvReleaseImage(& grey_im1);
	//cvReleaseImage(& imageptocy);
	//*******ƽ���˲����ͼ�񱣴���ҪΪ�˵�������
	/*IplImage *tempimage=NULL;
	tempimage=cvCreateImage(cvSize(tempMat->width,tempMat->height),IPL_DEPTH_8U,1);
	cvConvertScale(tempMat,tempMat,255.0,0);
	cvConvertScaleAbs(tempMat,tempimage,1,0);
	
	cvSaveImage("D:/tempimage.jpg",tempimage);*/
	//cvReleaseImage(& tempimage);
	//*******end

	
}


/***************************************************************************
*��������
*   halfSizeImage()
*
*��������:
*  CvMat * im-ͼ������ݾ���
*
*����ֵ��
*  CvMat *-ͼ������ݾ���
*
*˵����ͼ�񽵲�����������Сһ����ͼ��    
***************************************************************************/
CvMat * featurematch::halfSizeImage(CvMat * im)
{
	unsigned int i,j;
	int w=im->cols/2;
	int h=im->rows/2;
	CvMat *imnew=cvCreateMat(h,w,CV_32FC1);
	#define Im(ROW,COL) ((float *)(im->data.fl + im->step/sizeof(float) *(ROW)))[(COL)]
	#define Imnew(ROW,COL) ((float *)(imnew->data.fl + imnew->step/sizeof(float) *(ROW)))[(COL)]
	
	for (j=0;j<h;j++)
	{
		for (i=0;i<w;i++)
		{
			Imnew(j,i)=Im(j*2,i*2);

		}
	}
	return imnew;

}
/***************************************************************************
*��������
*   BuildGaussianOctaves()
*
*��������:
*  CvMat * image-ͼ������ݾ���
*
*����ֵ��
*  ImageOctave-ÿһ���ݵ�����
*
*˵����������������һ�׵�һ��ͼ���
*�����˹�����������߶�ͼ��
*ÿ�׵���Ŀ�ɱ���SCALESPEROCTAVE����
*�ú�����Ҫ��ͼ�����ݽ���Gaussian������ 
*����һ������ͼ�񣬼������ĸ�˹������ͼ��
*�����ⲿ�����ǽ���ָ�룬
*�ڲ�������ÿһ�������ڲ��Ĳ�ͬ�߶�ͼ��    
***************************************************************************/
ImageOctaves * featurematch::BuildGaussianOctaves(CvMat * image)
{

	
	ImageOctaves *octaves;
	CvMat *tempMat1;
	CvMat *dst;

	CvMat *temp1;
	int i,j;
	double k=pow(2,1.0/((float)SCALESPEROCTAVE));//SCALESPEROCTAVE=2
	float preblur_sigma,initial_sigma,sigma1,sigma2,sigma,absolute_sigma,sigma_f;
	//����������Ľ�����Ŀ
	int dim=min(image->rows,image->cols);
	//����������
	int numoctaves=(int)(log((double) dim) / log(2.0))-2;

	//�޶��������Ľ�����
	numoctaves=min(numoctaves,MAXOCTAVES);//MAXOCTAVES=4
	//Ϊ��˹��������DOG�����������ڴ�
	octaves=(ImageOctaves*) malloc( numoctaves * sizeof(ImageOctaves));
	DOGoctaves=(ImageOctaves*) malloc( numoctaves * sizeof(ImageOctaves));
	//��ʼ��ԭͼ��
	tempMat1=cvCloneMat(image);
	//preblur_sigma = 1.0;//sqrt(2 - 4*INITSIGMA*INITSIGMA),INITSIGMA=0.5;
    initial_sigma = sqrt(2);//sqrt( (4*INITSIGMA*INITSIGMA) + preblur_sigma * preblur_sigma );
    //initial_sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA * 4);
	
	
	//��ÿһ�׽�����ͼ���н�����ͬ�ĳ߶�ͼ��
	for (i=0;i<numoctaves;i++)
	{
		//���Ƚ���������ÿһ���ݵ���ײ㣬����0���ݵ���ײ��Ѿ�������
		//Ϊ�������ݷ����ڴ�
		octaves[i].Octave=(ImageLevels*) malloc((SCALESPEROCTAVE+3) * sizeof(ImageLevels));//SCALESPEROCTAVE=2
		DOGoctaves[i].Octave=(ImageLevels*) malloc((SCALESPEROCTAVE+2) * sizeof(ImageLevels));
		//�洢�������ݵ���ײ�
		(octaves[i].Octave)[0].Level=tempMat1;
		octaves[i].col=tempMat1->cols;
		octaves[i].row=tempMat1->rows;
		DOGoctaves[i].col=tempMat1->cols;
		DOGoctaves[i].row=tempMat1->rows;
		
		

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
		//����������������ͼ��
		for (j=1;j<SCALESPEROCTAVE+3;j++)
		{
			dst=cvCreateMat(tempMat1->rows,tempMat1->cols,CV_32FC1);//���ڴ洢��˹��
			temp1=cvCreateMat(tempMat1->rows,tempMat1->cols,CV_32FC1);//���ڴ洢DOG��
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

			
			
			
			
			
			//������˹��
			int length=BlurImage((octaves[i].Octave)[j-1].Level,dst,sigma_f);//��Ӧ�߶�
			(octaves[i].Octave)[j].levelsigmalength=length;//���س߶ȴ�С
			(octaves[i].Octave)[j].Level=dst;//
			
	

			
			//����DOG��
			cvSub(((octaves[i].Octave)[j]).Level,((octaves[i].Octave)[j-1]).Level,temp1,0);
			cvAbsDiff(((octaves[i].Octave)[j]).Level,((octaves[i].Octave)[j-1]).Level,temp1);
			((DOGoctaves[i].Octave)[j-1]).Level=temp1;
		}

		
		tempMat1=halfSizeImage(( (octaves[i].Octave)[SCALESPEROCTAVE+2].Level ));
		/*IplImage *mosaic11=NULL;
		mosaic11=cvCreateImage(cvSize(dst->width,dst->height),IPL_DEPTH_8U,1);
		cvConvertScale(dst,dst,255.0,0);
		cvConvertScaleAbs(dst,mosaic11,1,0);
	        cvSaveImage("D:\GaussianPyramid of me.jpg",mosaic11);*/
		
	

	}
	return octaves;

}




/***************************************************************************
*��������
*   MosaicVertical()
*
*��������:
*  CvMat * im1-ͼ������ݾ���1
*  CvMat * im2-ͼ������ݾ���2
*
*����ֵ��
*  CvMat *-ͼ������ݾ���
*
*˵����ͼ��ֱƴ����ʾ    
***************************************************************************/
CvMat* featurematch::MosaicVertical(CvMat* im1,CvMat* im2)
{
	int row,col;
	CvMat *mosaic = cvCreateMat(im1->rows+im2->rows,max(im1->cols,im2->cols), CV_32FC1);
	#define Mosaic(ROW,COL) ((float*)(mosaic->data.fl + mosaic->step/sizeof(float)*(ROW)))[(COL)]
	#define Im11Mat(ROW,COL) ((float *)(im1->data.fl + im1->step/sizeof(float) *(ROW)))[(COL)]
	#define Im22Mat(ROW,COL) ((float *)(im2->data.fl + im2->step/sizeof(float) *(ROW)))[(COL)]
	cvZero(mosaic);
	
	/* Copy images into mosaic1. */
	for ( row = 0; row < im1->rows; row++)
		for ( col = 0; col < im1->cols; col++)
			Mosaic(row,col)= Im11Mat(row,col) ;
		for ( row = 0; row < im2->rows; row++)
			for ( col = 0; col < im2->cols; col++)
				Mosaic((row+im1->rows),col)=Im22Mat(row,col) ;
			
  return mosaic;

}


/***************************************************************************
*��������
*   MosaicHorizen()
*
*��������:
*  CvMat * im1-ͼ������ݾ���1
*  CvMat * im2-ͼ������ݾ���2
*
*����ֵ��
*  CvMat *-ͼ������ݾ���
*
*˵����ͼ��ˮƽƴ����ʾ    
***************************************************************************/
CvMat* featurematch::MosaicHorizen(CvMat* im1,CvMat* im2)
{
	int row,col;
	CvMat *mosaic=cvCreateMat(max(im1->rows,im2->rows),(im1->cols+im2->cols),CV_32FC1);
	#define Mosaic(ROW,COL) ((float*)(mosaic->data.fl + mosaic->step/sizeof(float)*(ROW)))[(COL)]
	#define Im11Mat(ROW,COL) ((float *)(im1->data.fl + im1->step/sizeof(float) *(ROW)))[(COL)]
    #define Im22Mat(ROW,COL) ((float *)(im2->data.fl + im2->step/sizeof(float) *(ROW)))[(COL)]
	cvZero(mosaic);
	//������ͼƬ���ݺϳ�һ��
	for (row=0;row<im1->rows;row++)
	{
		for (col=0;col<im1->cols;col++)
		{
			Mosaic(row,col)=Im11Mat(row,col);
		}
	}
	for (row=0;row<im2->rows;row++)
	{
		for (col=0;col<im2->cols;col++)
		{
			Mosaic(row,(col+im1->cols))=Im22Mat(row,col);
		}
	}
	return mosaic;
}

void featurematch::Onstep2() 
{
	// TODO: Add your control notification handler code here
	//step2����Guassian��������DOG������
	Gaussianpyr=BuildGaussianOctaves(tempMat);
	
	//��ʾ��˹ͼ��
	mosaicHorizen1=NULL;
	mosaicHorizen2=NULL;
	mosaicVertical1=NULL;
	#define ImLevels(OCTAVE,LEVEL,ROW,COL) ((float *)(Gaussianpyr[(OCTAVE)].Octave[(LEVEL)].Level->data.fl +Gaussianpyr[(OCTAVE)].Octave[(LEVEL)].Level->step/sizeof(float) *(ROW)))[(COL)]
	
	for (int i=0;i<numoctaves;i++)
	{
		if (i==0)
		{
			mosaicHorizen1=MosaicHorizen((Gaussianpyr[0].Octave)[0].Level,(Gaussianpyr[0].Octave)[1].Level);
			for(int j=2;j<SCALESPEROCTAVE+3;j++)
				mosaicHorizen1=MosaicHorizen( mosaicHorizen1, (Gaussianpyr[0].Octave)[j].Level);
			for(j=0;j<NUMSIZE;j++)
				mosaicHorizen1=halfSizeImage(mosaicHorizen1);

		}
		else if (i==1)
		{
			mosaicHorizen2=MosaicHorizen((Gaussianpyr[1].Octave)[0].Level, (Gaussianpyr[1].Octave)[1].Level);
			for(int j=2;j<SCALESPEROCTAVE+3;j++)
				mosaicHorizen2=MosaicHorizen(mosaicHorizen2, (Gaussianpyr[1].Octave)[j].Level );
			for(j=0;j<NUMSIZE;j++)
				mosaicHorizen2=halfSizeImage(mosaicHorizen2);
			mosaicVertical1=MosaicVertical( mosaicHorizen1, mosaicHorizen2 );

		}
		else
		{
			mosaicHorizen1=MosaicHorizen( (Gaussianpyr[i].Octave)[0].Level, (Gaussianpyr[i].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+3;j++)
				mosaicHorizen1=MosaicHorizen( mosaicHorizen1, (Gaussianpyr[i].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen1=halfSizeImage(mosaicHorizen1);
			mosaicVertical1=MosaicVertical( mosaicVertical1, mosaicHorizen1 );
		}
	}
	mosaic1=NULL;
	mosaic1=cvCreateImage(cvSize(mosaicVertical1->width,mosaicVertical1->height),IPL_DEPTH_8U,1);
	cvConvertScale(mosaicVertical1,mosaicVertical1,255.0,0);
	cvConvertScaleAbs(mosaicVertical1,mosaic1,1,0);
//	cvSaveImage("D:\GaussianPyramid of me.jpg",mosaic1);

	cvNamedWindow("��˹������",1);
	cvShowImage("��˹������", mosaic1);
	cvWaitKey(0);
    cvDestroyWindow("mosaic1");
	cvReleaseImage(& mosaic1);


	//��ʾDOG������
	for ( i=0; i<numoctaves;i++)
	{
		if (i==0)
		{
			mosaicHorizen1=MosaicHorizen( (DOGoctaves[0].Octave)[0].Level, (DOGoctaves[0].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+2;j++)
				mosaicHorizen1=MosaicHorizen( mosaicHorizen1, (DOGoctaves[0].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen1=halfSizeImage(mosaicHorizen1);
		}
		else if (i==1)
		{
			mosaicHorizen2=MosaicHorizen( (DOGoctaves[1].Octave)[0].Level, (DOGoctaves[1].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+2;j++)
				mosaicHorizen2=MosaicHorizen( mosaicHorizen2, (DOGoctaves[1].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen2=halfSizeImage(mosaicHorizen2);
			mosaicVertical1=MosaicVertical( mosaicHorizen1, mosaicHorizen2 );
		}
		else
		{
			mosaicHorizen1=MosaicHorizen( (DOGoctaves[i].Octave)[0].Level, (DOGoctaves[i].Octave)[1].Level );
			for (int j=2;j<SCALESPEROCTAVE+2;j++)
				mosaicHorizen1=MosaicHorizen( mosaicHorizen1, (DOGoctaves[i].Octave)[j].Level );
			for ( j=0;j<NUMSIZE;j++)
				mosaicHorizen1=halfSizeImage(mosaicHorizen1);
			mosaicVertical1=MosaicVertical( mosaicVertical1, mosaicHorizen1 );
		}
  }
	//���ǵ�DOG����������ͼ�񶼻������������ԣ�����Ѱ����ģ��Խ�����ͼ��̧��һ��̨��ȥ��ʾ
	double min_val=0;
	double max_val=0;
	cvMinMaxLoc(mosaicVertical1,&min_val,&max_val,NULL,NULL,NULL);
	if (min_val<0.0)
	{
		cvAddS(mosaicVertical1,cvScalarAll((-1)*min_val),mosaicVertical1,NULL);
		
	}
	mosaic2 = cvCreateImage(cvSize(mosaicVertical1->width, mosaicVertical1->height),  IPL_DEPTH_8U,1);
	cvConvertScale( mosaicVertical1, mosaicVertical1, 255.0/(max_val-min_val), 0 );
	cvConvertScaleAbs( mosaicVertical1, mosaic2, 1, 0 );
	
//	cvSaveImage("DOGPyramid of me.jpg",mosaic2);
	cvNamedWindow("mosaic1",1);
	cvShowImage("mosaic1", mosaic2);
    cvWaitKey(0);


}



/***************************************************************************
*��������
*   DetectKeypoint()
*
*��������:
*  int numoctaves-
*  ImageOctaves *Gaussianpyr-ͼ��ĸ�˹������
*
*����ֵ��
*  int -ͼ������ݾ���
*
*˵�������DOG�������еľֲ����ֵ���ҵ�֮�󣬻�Ҫ���������������ȷ��Ϊ������
*һ�������������ԵĲ��죬��������Ӧ���Ǳ�Ե�㣬
*��Ҳ����˵���ڼ�ֵ�㴦�������ʱ�Ӧ��С��ĳһ����ֵ��    
***************************************************************************/
int featurematch::DetectKeypoint(int numoctaves,ImageOctaves *Gaussianpyr)
{
	keypoints=NULL;
	//��������DOG��ֵ����������ʱȵ���ֵCURVATURE_THRESHOLD=10,curvature_threshold=12.1
	double curvature_threshold=((CURVATURE_THRESHOLD+1)*(CURVATURE_THRESHOLD+1))/CURVATURE_THRESHOLD;
	#define ImLevels(OCTAVE,LEVEL,ROW,COL) ((float *)(DOGoctaves[(OCTAVE)].Octave[(LEVEL)].Level->data.fl + DOGoctaves[(OCTAVE)].Octave[(LEVEL)].Level->step/sizeof(float) *(ROW)))[(COL)]

	int keypoint_count=0;
	for (int i=0;i<numoctaves;i++)
	{
		for (int j=1;j<SCALESPEROCTAVE+1;j++)//ȡ�м��scaleperoctave����
		{
			//��ͼ�����Ч������Ѱ�Ҿ��������������ľֲ����ֵ
			int dim=(int)(0.5+((Gaussianpyr[i].Octave)[j].levelsigmalength)+0.5);
			for (int m=dim;m<((DOGoctaves[i].row)-dim);m++)
			{
				for (int n=dim;n<((DOGoctaves[i].col)-dim);n++)
				{
					if (ImLevels(i,j,m,n)!=0.0)//first ����
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
							(inf_val <= ImLevels(i,j-1,m+1,n+1))&&    //�ײ��С�߶�9
							
							(inf_val <= ImLevels(i,j,m-1,n-1))&&
							(inf_val <= ImLevels(i,j,m  ,n-1))&&
							(inf_val <= ImLevels(i,j,m+1,n-1))&&
							(inf_val <= ImLevels(i,j,m-1,n  ))&&
							(inf_val <= ImLevels(i,j,m+1,n  ))&&
							(inf_val <= ImLevels(i,j,m-1,n+1))&&
							(inf_val <= ImLevels(i,j,m  ,n+1))&&
							(inf_val <= ImLevels(i,j,m+1,n+1))&&     //��ǰ��8
							
							(inf_val <= ImLevels(i,j+1,m-1,n-1))&&
							(inf_val <= ImLevels(i,j+1,m  ,n-1))&&
							(inf_val <= ImLevels(i,j+1,m+1,n-1))&&
							(inf_val <= ImLevels(i,j+1,m-1,n  ))&&
							(inf_val <= ImLevels(i,j+1,m  ,n  ))&&
							(inf_val <= ImLevels(i,j+1,m+1,n  ))&&
							(inf_val <= ImLevels(i,j+1,m-1,n+1))&&
							(inf_val <= ImLevels(i,j+1,m  ,n+1))&&
							(inf_val <= ImLevels(i,j+1,m+1,n+1))     //��һ���߶�9							 
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
						   ) )      //2������26���м�ֵ��
						
						{
							//�洢������
							//����������Ե������ԣ����������CONTRAST_THRESHOLD=0.02
							if (fabs(ImLevels(i,j,m,n))>= CONTRAST_THRESHOLD)
							{
								//�����������������������㹻�����ʱȣ��ȼ���Hessian����
								//Tr_H = Dxx + Dyy;
                                //Det_H = Dxx*Dyy - Dxy^2;
								float Dxx,Dyy,Dxy,Tr_H,Det_H,curvature_ratio;
                                Dxx = ImLevels(i,j,m,n-1) + ImLevels(i,j,m,n+1)-2.0*ImLevels(i,j,m,n);
								Dyy = ImLevels(i,j,m-1,n) + ImLevels(i,j,m+1,n)-2.0*ImLevels(i,j,m,n);
								Dxy = ImLevels(i,j,m-1,n-1) + ImLevels(i,j,m+1,n+1) - ImLevels(i,j,m+1,n-1) - ImLevels(i,j,m-1,n+1);
                                Tr_H = Dxx + Dyy;
                                Det_H = Dxx*Dyy - Dxy*Dxy;
								//����������
								curvature_ratio=(1.0*Tr_H*Tr_H)/Det_H;
								if ((Det_H>=0.0) && (curvature_ratio <= curvature_threshold))//���õ������������������������ curvature_threshold=12.1
								{
									//����洢�������Լ���������������
									keypoint_count++;
									Keypoint k;
									//Ϊ����������ڴ�
									k=(Keypoint) malloc(sizeof(struct KeypointSt));
									k->next=keypoints;
									keypoints=k;
									k->row=m*(Gaussianpyr[i].subsample);
									k->col=n*(Gaussianpyr[i].subsample);
									k->sy=m;//��
									k->sx=n;//��
									k->octave=i;
									k->level=j;
									k->scale=(Gaussianpyr[i].Octave)[j].absolute_sigma; 

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







/***************************************************************************
*��������
*   DisplayKeypointLocation()
*
*��������:
*  IplImage *image-ԭʼͼ��
*  ImageOctaves *Gaussianpyr-������ͼ��
*
*����ֵ��
*  void
*
*˵�����ú�����Ҫ��sift��������ʾ��ԭͼ����    
***************************************************************************/
void featurematch::DisplayKeypointLocation(IplImage* image, ImageOctaves *Gaussianpyr)
{
	Keypoint p = keypoints; // pָ���һ�����
	while(p) // û����β
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
void featurematch::Ondetectfeature() 
{
	// TODO: Add your control notification handler code here
	int keycount=DetectKeypoint(numoctaves,Gaussianpyr);
	cvCopy(imageptocy,image1,NULL);
	DisplayKeypointLocation(image1,Gaussianpyr);
	//ͼ����ϲ��������ͼ��Ϊ�����2�㣬CV_GAUSSIAN_5x5����˲��������ͣ�Ŀǰֻ֧�����
	//cvPyrUp(image1,DoubleSizeImage,CV_GAUSSIAN_5x5);
	//cvSaveImage("D:\DoubleSizeImage.jpg",DoubleSizeImage);
	cvNamedWindow("image1",1);
	cvShowImage("image1", image1);
	cvWaitKey(0);  
    cvDestroyWindow("image1");

}


/***************************************************************************
*��������
*   ComputeGrad_DirecandMag()
*
*��������:
*  int numoctaves-
*  ImageOctaves *Gaussianpyr-������ͼ��
*
*����ֵ��
*  void
*
*˵�����ú�����Ҫ���������ͼ���������������ͷ�ֵ   
***************************************************************************/
void featurematch::ComputeGrad_DirecandMag(int numoctaves,ImageOctaves *Gaussianpyr)
{
	mag_pyr=(ImageOctaves *) malloc(numoctaves * sizeof(ImageOctaves));
	grad_pyr=(ImageOctaves *) malloc(numoctaves * sizeof(ImageOctaves));
	#define ImLevels(OCTAVE,LEVEL,ROW,COL) ((float *)(Gaussianpyr[(OCTAVE)].Octave[(LEVEL)].Level->data.fl +Gaussianpyr[(OCTAVE)].Octave[(LEVEL)].Level->step/sizeof(float) *(ROW)))[(COL)]
	for (int i=0;i<numoctaves;i++)
{
		mag_pyr[i].Octave=(ImageLevels *) malloc((SCALESPEROCTAVE) * sizeof(ImageLevels));
		grad_pyr[i].Octave=(ImageLevels *) malloc((SCALESPEROCTAVE) * sizeof(ImageLevels));

	for (int j=1;j<SCALESPEROCTAVE+1;j++)//ȡ�м��SCALESPEROCTAVE����
	{
		CvMat *Mag=cvCreateMat(Gaussianpyr[i].row,Gaussianpyr[i].col,CV_32FC1);
		CvMat *Ori=cvCreateMat(Gaussianpyr[i].row,Gaussianpyr[i].col,CV_32FC1);
		CvMat *tempMat1=cvCreateMat(Gaussianpyr[i].row,Gaussianpyr[i].col,CV_32FC1);
		CvMat *tempMat2=cvCreateMat(Gaussianpyr[i].row,Gaussianpyr[i].col,CV_32FC1);
		cvZero(Mag);
		cvZero(Ori);
		cvZero(tempMat1);
		cvZero(tempMat2);
		#define MAG(ROW,COL) ((float *)(Mag->data.fl + Mag->step/sizeof(float) *(ROW)))[(COL)]   
		#define ORI(ROW,COL) ((float *)(Ori->data.fl + Ori->step/sizeof(float) *(ROW)))[(COL)]  
		#define TEMPMAT1(ROW,COL) ((float *)(tempMat1->data.fl + tempMat1->step/sizeof(float) *(ROW)))[(COL)]
		#define TEMPMAT2(ROW,COL) ((float *)(tempMat2->data.fl + tempMat2->step/sizeof(float) *(ROW)))[(COL)]
		for (int m=1;m<(Gaussianpyr[i].row-1);m++)
		{
			for (int n=1;n<(Gaussianpyr[i].col-1);n++)
			{
				//�����ֵ
				TEMPMAT1(m,n)=0.5*(ImLevels(i,j,m,n+1)-ImLevels(i,j,m,n-1));//dx
				TEMPMAT2(m,n)=0.5*(ImLevels(i,j,m+1,n)-ImLevels(i,j,m-1,n));//dy
				MAG(m,n)=sqrt(TEMPMAT1(m,n)*TEMPMAT1(m,n)+TEMPMAT2(m,n)*TEMPMAT2(m,n));//��ֵ
				//���㷽��
				ORI(m,n)=atan(TEMPMAT2(m,n)/TEMPMAT1(m,n));
				if (ORI(m,n)==CV_PI)
				{
					ORI(m,n)=-CV_PI;

				}

			}
			
		}
		((mag_pyr[i].Octave)[j-1]).Level=Mag;
		((grad_pyr[i].Octave)[j-1]).Level=Ori;
		cvReleaseMat(&tempMat1);
		cvReleaseMat(&tempMat2);
	}

}
	free(mag_pyr);
	free(grad_pyr);

}


/***************************************************************************
*��������
*   AssignTheMainOrientation()
*
*��������:
*  int numoctaves-
*  ImageOctaves *Gaussianpyr-������ͼ��
*  ImageOctaves *mag_pyr-��ֵ
*  ImageOctaves *grad_pyr-����
*
*����ֵ��
*  void
*
*˵�����ú�����Ҫ���������ͼ���������������ȷ��������  
***************************************************************************/
void featurematch::AssignTheMainOrientation(int numoctaves, ImageOctaves *Gaussianpyr,ImageOctaves *mag_pyr,ImageOctaves *grad_pyr)
{
	keyDescriptors=NULL;
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
	Keypoint p=keypoints;//pָ���һ�����
	while(p)//û����β
	{
		int i=p->octave;
		int j=p->level;
		int m=p->sy;
		int n=p->sx;
		if ((m>=zero_pad)&&(m<Gaussianpyr[i].row-zero_pad)&&
			(n>=zero_pad)&&(n<Gaussianpyr[i].col-zero_pad))
		{
			float sigma=( ((Gaussianpyr[i].Octave)[j].absolute_sigma) ) / (Gaussianpyr[i].subsample);
			//������ά��˹ģ��
			CvMat * mat=GaussianKernel2D(sigma);
			int dim=(int)(0.5*(mat->rows));
			//�������ڴ洢patch��ֵ�ͷ���Ŀռ�
			#define MAT(ROW,COL) ((float *)(mat->data.fl + mat->step/sizeof(float) *(ROW)))[(COL)]
			//��������ֱ��ͼ����
			double * orienthist=(double *) malloc(36*sizeof(double));
			for (int sw=0;sw<36;++sw)
			{
				orienthist[sw]=0.0;
			}
			//�����������Χͳ���ݶȷ���
			for (int x=m-dim,mm=0;x<=(m+dim);x++,mm++)
			{
				for (int y=n-dim,nn=0;y<=(n+dim);y++,nn++)
				{
					//���������㴦�ķ�ֵ
					double dx=0.5*(ImLevels(i,j,x,y+1)-ImLevels(i,j,x,y-1));//dx
					double dy=0.5*(ImLevels(i,j,x+1,y)-ImLevels(i,j,x-1,y));//dy
					double mag=sqrt(dx*dx+dy*dy);//��ֵ
					//���㷽��
					double Ori=atan(1.0*dy/dx);//ע��dx!=0
					int binIdx=FindClosestRotationBin(36,Ori);
					//���ø�˹��Ȩ�ۼӽ�ֱ��ͼ��Ӧ�Ŀ�
					orienthist[binIdx]=orienthist[binIdx]+1.0*mag*MAT(mm,nn);
					
				}
			}
			//�ҳ�����ֱ��ͼ�еķ�ֵ
			AverageWeakBins(orienthist,36);
			//�ҳ����ֵ
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
			//Ѱ����һ�����ܵĵ�
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
				if (InterpolateOrientation ( orienthist[maxBin == 0 ? (36 - 1) : (maxBin - 1)],
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
				//�洢���򣬿���ֱ�����ü�⵽��������иò��������ָ����
				//�����ڴ����´洢������
				Keypoint k;
				//allocate memory for the keypoint descriptor
			
				k=(Keypoint) malloc(sizeof(struct KeypointSt));
				k->next=keyDescriptors;
				keyDescriptors=k;
				k->descrip=(float*) malloc(LEN * sizeof(float));
				k->row=p->row;
				k->col=p->col;
				k->sy = p->sy;    //��
				k->sx = p->sx;    //��
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

/***************************************************************************
*��������
*   GaussianKernel2D()
*
*��������:
*float sigma-�˲�����
*
*����ֵ��
*  CvMat
*
*˵�����ú�����Ҫ���������ͼ���������������ȷ��������  
***************************************************************************/
CvMat * featurematch:: GaussianKernel2D(float sigma)
{
	int dim=(int) max(3.0f, 2.0 * GAUSSKERN *sigma + 1.0f);
	if (dim % 2==0)
	{
		dim++;
	}
	CvMat * mat=cvCreateMat(dim,dim,CV_32FC1);
	#define Mat(ROW,COL) ((float *)(mat->data.fl + mat->step/sizeof(float) *(ROW)))[(COL)]
	float s2=sigma*sigma;
	int c=dim/2;
	float m=1.0/(sqrt(2.0*CV_PI)*sigma);
	for (int i=0;i<(dim +1) / 2;i++)
	{
		for (int j=0;j<(dim +1) / 2;j++)
		{
			float v=m*exp(-(1.0*i*i+1.0*j*j) / (2.0*s2));
			Mat(c+i,c+j) =v;
			Mat(c-i,c+j) =v;
			Mat(c+i,c-j) =v;
			Mat(c-i,c-j) =v;
		}
	}
	return mat;

}




/***************************************************************************
*��������
*   FindClosestRotationBin()
*
*��������:
*int binCount-36ά
*float angle-�Ƕ�
*
*����ֵ��
*  CvMat
*
*˵�����ú�����ҪѰ�����������������  
***************************************************************************/
int featurematch::FindClosestRotationBin(int binCount,float angle)
{
	angle+=CV_PI;
	angle/=2.0*CV_PI;
	angle*=binCount;
	int idx=(int)angle;
	if (idx==binCount)
	{
		idx=0;
	}
	return (idx);

}


/***************************************************************************
*��������
*   AverageWeakBins()
*
*��������:
*  double * bins
*  int binCount-36ά
*
*����ֵ��
*  void
*
*˵�����ú�����Ҫ�������˲�  
***************************************************************************/
void featurematch::AverageWeakBins(double * bins,int binCount)
{
	for (int sn=0;sn<2;++sn)
	{
		double firstE=bins[0];
		double last=bins[binCount-1];
		for (int sw=0;sw<binCount;++sw)
		{
			double cur=bins[sw];
			double next=(sw==(binCount-1)) ? firstE:bins[(sw+1) % binCount];
			bins[sw]=(last+cur+next) /3.0;
			last=cur;

		}
	}

}


/***************************************************************************
*��������
*   AverageWeakBins()
*
*��������:
*  double * bins
*  int binCount-36ά
*
*����ֵ��
*  CvMat
*
*˵�����ú�����Ҫ�������˲�  
***************************************************************************/
bool featurematch::InterpolateOrientation(double left,double middle,double right,double *degreeCorrection,double *peakValue)
{
	double a=((left+right) - 2.0 * middle) / 2.0;//���������ϵ��a
	if (a==0.0)
		return false;
	double c=(((left-middle)/a)-1.0) / 2.0;
	double b=middle-c*c*a;
	if (c<-0.5 || c>0.5)
		return false;
	*degreeCorrection=c;
	*peakValue=b;
	return true;
	
	

}
void featurematch::Onstep4() 
{
	// TODO: Add your control notification handler code here
	ComputeGrad_DirecandMag(numoctaves,Gaussianpyr);
	AssignTheMainOrientation(numoctaves,Gaussianpyr,mag_pyr,grad_pyr);
	cvCopy(imageptocy,image1,NULL);
	DisplayOrientation(image1,Gaussianpyr);

//	cvSaveImage("D:\mag.jpg",image1);
	cvNamedWindow("image1",1);
	cvShowImage("image1",image1);
	cvWaitKey(0);  
    cvDestroyWindow("image1");

}

/***************************************************************************
*��������
*   GetVecNorm()
*
*��������:
*  float * vec
*  int dim
*
*����ֵ��
*  float
*
*˵�����õ�������ŷʽ���룬2��ʽ  
***************************************************************************/
float featurematch:: GetVecNorm(float * vec,int dim)
{
	float sum=0.0;
	for(unsigned int i=0;i<dim;i++)
		sum+=vec[i]*vec[i];
	return sqrt(sum);

}
/***************************************************************************
*��������
*   getPixelBI()
*
*��������:
*  CvMat * im
*  float col
*  float row
*
*����ֵ��
*  float
*
*˵����˫���Բ�ֵ���������ؼ�ĻҶ�  
***************************************************************************/
float featurematch::getPixelBI(CvMat * im,float col,float row)
{
	int irow,icol;
	float rfrac,cfrac;
	float row1=0,row2=0;
	int width=im->cols;
	int height=im->rows;
	#define ImMat(ROW,COL) ((float *)(im->data.fl + im->step/sizeof(float) *(ROW)))[(COL)]
	
	irow=(int) row;
	icol=(int) col;

	if(irow < 0 || irow >=height || icol < 0 || icol >=width)
		return 0;
	if(row > height-1)
		row= height-1;
	if (col>width-1)
		col=width-1;
	rfrac=1.0-(row-(float) irow);
	cfrac=1.0-(col-(float) icol);
	if (cfrac<1)
	{
		row1=cfrac*ImMat(irow,icol)+(1.0-cfrac)*ImMat(irow,icol+1);
	}
	else
	{
		row1=ImMat(irow,icol);

	}
	if (rfrac<1)
	{
		if (cfrac<1)
		{
			row2=cfrac*ImMat(irow+1,icol)+(1.0-cfrac)*ImMat(irow+1,icol+1);

		}
		else
		{
			row2=ImMat(irow+1,icol);
		}
	}
	return rfrac*row1+(1.0-rfrac)*row2;

}
/***************************************************************************
*��������
*   ExtractFeatureDescriptors()
*
*��������:
*  int numoctaves
*  ImageOctaves *Gaussianpyr
*
*����ֵ��
*  CvMat
*
*˵�����ú�����Ҫ��ȷ��������������֡���������patch�������ݶȷ����
*��������ת���������򣬲�ֵ�õ������ݶ�ֵ��һ�������������2*2*8=32
*ά��������Ҳ������4*4*8=128ά����������ȷ�Ľ���������  
***************************************************************************/
void featurematch::ExtractFeatureDescriptors(int numoctaves,ImageOctaves *Gaussianpyr)
{
	//��Ҫ�а˸�����
	float orient_bin_spacing=pi/4;
	float orient_angles[8]={-pi,-pi+orient_bin_spacing,-pi*0.5,-orient_bin_spacing,
	0.0,orient_bin_spacing,pi*0.5,pi+orient_bin_spacing};
	//�������������ĸ�������
	float *feat_grid=(float *) malloc(2*16*sizeof(float));
	for (int i=0;i<GridSpacing;i++)//GridSpacing=4
	{
		for (int j=0;j<2*GridSpacing;++j,++j)
		{
			feat_grid[i*2*GridSpacing+j]=-6.0+i*GridSpacing;
			feat_grid[i*2*GridSpacing+j+1]=-6.0+0.5*j*GridSpacing;
		}
	}
	//��������
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
	Keypoint p=keyDescriptors;//pָ���һ���ڵ�
	while(p)//û����β
	{
		float scale=(Gaussianpyr[p->octave].Octave)[p->level].absolute_sigma;
		float sine=sin(p->ori);
		float cosine=cos(p->ori);
		//�������ĵ�������ת���λ��
		float *featcenter=(float *) malloc(2*16*sizeof(float));
		for (int i=0;i<GridSpacing;i++)
		{
			for (int j=0;j<2*GridSpacing;j+=2)
			{
				float x=feat_grid[i*2*GridSpacing+j];
				float y=feat_grid[i*2*GridSpacing+j+1];
				featcenter[i*2*GridSpacing+j]=((cosine * x + sine * y)+p->sx);
				featcenter[i*2*GridSpacing+j+1]=((-sine * x + cosine * y)+p->sy);

			}
		}
		
		float *feat=(float *) malloc(2*256*sizeof(float));

		//ԭ�����д�
		for (i=0;i<2*64*GridSpacing;i++,i++)
		{
			float x=feat_samples[i];
			float y=feat_samples[i+1];
			feat[i]=((cosine * x + sine * y )+p->sx);
			feat[i+1]=((-sine * x + cosine * y)+p->sy);
		}

		//��ʼ������������
		float *feat_desc=(float *) malloc(128 * sizeof(float));
		for (i=0;i<128;i++)
		{
			feat_desc[i]=0.0;
		}
		for (i=0;i<512;++i,++i)
		{
			float x_sample=feat[i];
			float y_sample=feat[i+1];
			float sample12=getPixelBI(((Gaussianpyr[p->octave].Octave)[p->level]).Level, x_sample, y_sample-1);
			float sample21=getPixelBI(((Gaussianpyr[p->octave].Octave)[p->level]).Level, x_sample-1, y_sample); 
			float sample22=getPixelBI(((Gaussianpyr[p->octave].Octave)[p->level]).Level, x_sample, y_sample); 
			float sample23=getPixelBI(((Gaussianpyr[p->octave].Octave)[p->level]).Level, x_sample+1, y_sample); 
			float sample32=getPixelBI(((Gaussianpyr[p->octave].Octave)[p->level]).Level, x_sample, y_sample+1); 
			float diff_x=sample23-sample21;
			float diff_y=sample32-sample12;
			float mag_sample=sqrt(diff_x*diff_x+diff_y*diff_y);
			float grad_sample=atan(diff_y / diff_x);
			if(grad_sample==CV_PI)
				grad_sample=-CV_PI;
			//����x��y�����Ȩ��
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
			//���㷽��ļ�Ȩ��������ת�ݶȳ���������Ȼ��������
			float diff[8],orient_wght[128];
			for (m=0;m<8;++m)
			{
				float angle=grad_sample-(p->ori)-orient_angles[m]+CV_PI;
				float temp=angle / (2.0 * CV_PI);
				angle-=(int)(temp) * (2.0*CV_PI);
				diff[m]=angle-CV_PI;
			}
			//�����˹Ȩ��
			float x=p->sx;
			float y=p->sy;
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
		float norm=GetVecNorm(feat_desc,128);
		for (int m=0;m<128;m++)
		{
			feat_desc[m]/=norm;
			if (feat_desc[m]>0.2)
			{
				feat_desc[m]=0.2;
			}
		}
		norm=GetVecNorm(feat_desc,128);
		for (m=0;m<128;m++)
		{
			feat_desc[m]/=norm;
		}
		p->descrip=feat_desc;
		p=p->next;
		
	}
	free(feat_grid);
	free(feat_samples);

}

/***************************************************************************
*��������
*   DisplayOrientation()
*
*��������:
*  IplImage *image-ԭʼͼ��
*  ImageOctaves *Gaussianpyr-������ͼ��
*
*����ֵ��
*  void
*
*˵�����ú�����Ҫ��sift��������ʾ��ԭͼ����    
***************************************************************************/
void featurematch:: DisplayOrientation(IplImage *image,ImageOctaves *Gaussianpyr)
{
	Keypoint p=keyDescriptors;//pָ���һ���ڵ�,keyDescriptorsһ��Ҫ��ʼ��Ϊ��
	while (p)//û����β
	{
		float scale=(Gaussianpyr[p->octave].Octave)[p->level].absolute_sigma;
		float autoscale=3.0;
		float uu=autoscale*scale*cos(p->ori);
		float vv=autoscale*scale*sin(p->ori);
		float x=(p->col)+uu;
		float y=(p->row)+vv;

		//����
		cvLine(image, cvPoint((int)(p->col),(int)(p->row)), 
			cvPoint((int)x,(int)y), CV_RGB(255,255,0),
               1, 8, 0 );
		
		//����ͷ
		float alpha=0.33;
		float beta=0.33;
		
		float xx0=(p->col)+uu-alpha*(uu+beta*vv);
		float yy0=(p->row)+vv-alpha*(vv-beta*uu);
		float xx1=(p->col)+uu-alpha*(uu-beta*vv);
		float yy1=(p->row)+vv-alpha*(vv+beta*uu);
		cvLine(image,cvPoint((int)xx0,(int)yy0),cvPoint((int)x,(int)y),CV_RGB(255,255,0),1,8,0);
		cvLine(image,cvPoint((int)xx1,(int)yy1),cvPoint((int)x,(int)y),CV_RGB(255,255,0),1,8,0);
		p=p->next;
	}

}

void featurematch::Onstep5() 
{
	// TODO: Add your control notification handler code here
	ExtractFeatureDescriptors(numoctaves,Gaussianpyr);
	//cvWaitKey(0);

}
