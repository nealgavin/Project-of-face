#if !defined(AFX_FEATUREMATCH_H__03E01FAB_E843_4863_AE53_574DDC512A11__INCLUDED_)
#define AFX_FEATUREMATCH_H__03E01FAB_E843_4863_AE53_574DDC512A11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// featurematch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// featurematch dialog
#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "cxcore.h"
#include <string>
using namespace std;
#include "afxtempl.h"

typedef CArray<CPoint,CPoint> ptarry;


#define GAUSSKERN 3.5
#define  pi 3.1415926
#define  NUMSIZE 2
//sigma of base image--see D.L's paper
#define INITSIGMA 0.5

//number of scales per octvae. see  D.L's paper.
#define SCALESPEROCTAVE 2
#define MAXOCTAVES 4



#define CONTRAST_THRESHOLD   0.02
#define CURVATURE_THRESHOLD  10.0
#define DOUBLE_BASE_IMAGE_SIZE 1 
#define peakRelThresh 0.8
#define LEN 128
#define GridSpacing 4


// Data structure for a float image.
//金字塔的每一层
typedef struct ImageSt
{
	float levelsigma;
	int levelsigmalength;
	float absolute_sigma;
	CvMat *Level;

}ImageLevels;

//金字塔的每一阶梯
typedef struct ImageSt1
{
	int row,col;
	float subsample;
	ImageLevels *Octave;

}ImageOctaves;




//特征点的数据结构
typedef struct KeypointSt
{
	float row,col;//反馈回原图像大小，特征点的位置
	float sx,sy;//金字塔中特征点的位置
	int octave,level;//金字塔中，特征点所在的阶梯、层次

	float scale,ori,mag;//所在层的尺度sigma，主方向orientation（range [-PI,PI]）,幅值
	float *descrip;//特征描述字指针：128维或32维
	struct KeypointSt *next;//指向下一个关键点指针

} *Keypoint;





class featurematch : public CDialog
{
// Construction
public:
	featurematch(CWnd* pParent = NULL);   // standard constructor
public:
	IplImage *imageone;
	IplImage *imageptocy;

	IplImage *image1;
	IplImage *grey_im1;
	IplImage *DoubleSizeImage;

	CvMat *mosaicHorizen1;
	CvMat *mosaicHorizen2;
	CvMat *mosaicVertical1;
	
	IplImage *mosaic1;
	IplImage *mosaic2;

	CvMat *image1Mat;
	CvMat *tempMat;


int numoctaves;
	//存放高斯金字塔
	ImageOctaves *Gaussianpyr;
	ImageOctaves *DOGoctaves; 

	ImageOctaves *mag_thresh;
	ImageOctaves *mag_pyr;
	ImageOctaves *grad_pyr;
	

	//存放特征点
	Keypoint keypoints,keypoints1,keypoints2;//用于临时存储特征点的位置等
	Keypoint keyDescriptors,keyDescriptors1,keyDescriptors2;//用于最后的确定特征点以及特征描述字

public:
	//平面图像投影到柱面
	void palnetocylinder(IplImage *image);
	IplImage *palnetocylinder1(IplImage *image);
	//图像太大，运算速度太慢，裁剪第一张图像的最右边
	void cutrightimage(IplImage * image);
	//裁剪第二张图片的左边
	void cutleftimage(IplImage * image);

	//SIFT算法第一步：扩大图像，预滤波剔除噪声，得到金字塔的最底层-第一阶的第一层
	CvMat *ScaleInitImage(CvMat * im);
	//卷积模糊图像
	int BlurImage(CvMat * src, CvMat * dst1, float sigma);
	//产生1D高斯核
	float* GaussianKernel1D(float sigma, int dim);
	//x方向作卷积
	void Convolve1DWidth(float* kern, int dim, CvMat * src, CvMat * dst);
	//x方向像素作卷积
	float ConvolveLocWidth(float* kernel, int dim, CvMat * src, int x, int y);
	//y方向作卷积
	void Convolve1DHeight(float* kern, int dim, CvMat * src, CvMat * dst);
	//y方向像素处作卷积
	float ConvolveLocHeight(float* kernel, int dim, CvMat * src, int x, int y);
	//采样原来的图像，返回放大2倍尺寸的线性插值图像
	CvMat * doubleSizeImage2(CvMat * im);

	//第二步，建立Guassian和DOG金字塔
	ImageOctaves * BuildGaussianOctaves(CvMat * image);
	
	//缩小图像：下采样
	CvMat * halfSizeImage(CvMat * im);
	//为了显示图像金字塔，而做的图像水平垂直拼接
	CvMat* MosaicHorizen(CvMat* im1,CvMat* im2);
	CvMat* MosaicVertical(CvMat* im1,CvMat* im2);

	//第三步，特征点位置检测，最后确定特征点的位置
	int DetectKeypoint(int numoctaves,ImageOctaves *Gaussianpyr);
	void DisplayKeypointLocation(IplImage* image, ImageOctaves *Gaussianpyr);


	//第四步，计算高斯图像的梯度和幅值，计算各个特征点的主方向
	void ComputeGrad_DirecandMag(int numoctaves,ImageOctaves *Gaussianpyr);
	//确定各个特征点处的主方向函数
	void AssignTheMainOrientation(int numoctaves, ImageOctaves *Gaussianpyr,ImageOctaves *mag_pyr,ImageOctaves *grad_pyr);
	//得到二维高斯模板
	CvMat * GaussianKernel2D(float sigma); 
	//进行方向直方图统计
	int FindClosestRotationBin(int binCount,float angle);
	//对方向直方图滤波
	void AverageWeakBins(double * bins,int binCount);
	//确定真正的主方向
	bool InterpolateOrientation(double left,double middle,double right,double *degreeCorrection,double *peakValue);
	
	//第五步：抽取各个特征点处的特征描述字
	void ExtractFeatureDescriptors(int numoctaves,ImageOctaves *Gaussianpyr);
	//双线性插值，返回像素间的灰度值
	float getPixelBI(CvMat * im,float col,float row);
	//得到向量的欧式长度
	float GetVecNorm(float * vec,int dim);
	//显示特征点
	void DisplayOrientation(IplImage *image,ImageOctaves *Gaussianpyr);
// Dialog Data
	//{{AFX_DATA(featurematch)
	enum { IDD = IDD_featurematch };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(featurematch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(featurematch)
	afx_msg void Onopenimage();
	afx_msg void OnDestory();
	afx_msg void Onplanetocy();
	afx_msg void Onstep1();
	afx_msg void Onstep2();
	afx_msg void Ondetectfeature();
	afx_msg void Onstep4();
	afx_msg void Onstep5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEATUREMATCH_H__03E01FAB_E843_4863_AE53_574DDC512A11__INCLUDED_)
