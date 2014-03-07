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
//��������ÿһ��
typedef struct ImageSt
{
	float levelsigma;
	int levelsigmalength;
	float absolute_sigma;
	CvMat *Level;

}ImageLevels;

//��������ÿһ����
typedef struct ImageSt1
{
	int row,col;
	float subsample;
	ImageLevels *Octave;

}ImageOctaves;




//����������ݽṹ
typedef struct KeypointSt
{
	float row,col;//������ԭͼ���С���������λ��
	float sx,sy;//���������������λ��
	int octave,level;//�������У����������ڵĽ��ݡ����

	float scale,ori,mag;//���ڲ�ĳ߶�sigma��������orientation��range [-PI,PI]��,��ֵ
	float *descrip;//����������ָ�룺128ά��32ά
	struct KeypointSt *next;//ָ����һ���ؼ���ָ��

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
	//��Ÿ�˹������
	ImageOctaves *Gaussianpyr;
	ImageOctaves *DOGoctaves; 

	ImageOctaves *mag_thresh;
	ImageOctaves *mag_pyr;
	ImageOctaves *grad_pyr;
	

	//���������
	Keypoint keypoints,keypoints1,keypoints2;//������ʱ�洢�������λ�õ�
	Keypoint keyDescriptors,keyDescriptors1,keyDescriptors2;//��������ȷ���������Լ�����������

public:
	//ƽ��ͼ��ͶӰ������
	void palnetocylinder(IplImage *image);
	IplImage *palnetocylinder1(IplImage *image);
	//ͼ��̫�������ٶ�̫�����ü���һ��ͼ������ұ�
	void cutrightimage(IplImage * image);
	//�ü��ڶ���ͼƬ�����
	void cutleftimage(IplImage * image);

	//SIFT�㷨��һ��������ͼ��Ԥ�˲��޳��������õ�����������ײ�-��һ�׵ĵ�һ��
	CvMat *ScaleInitImage(CvMat * im);
	//���ģ��ͼ��
	int BlurImage(CvMat * src, CvMat * dst1, float sigma);
	//����1D��˹��
	float* GaussianKernel1D(float sigma, int dim);
	//x���������
	void Convolve1DWidth(float* kern, int dim, CvMat * src, CvMat * dst);
	//x�������������
	float ConvolveLocWidth(float* kernel, int dim, CvMat * src, int x, int y);
	//y���������
	void Convolve1DHeight(float* kern, int dim, CvMat * src, CvMat * dst);
	//y�������ش������
	float ConvolveLocHeight(float* kernel, int dim, CvMat * src, int x, int y);
	//����ԭ����ͼ�񣬷��طŴ�2���ߴ�����Բ�ֵͼ��
	CvMat * doubleSizeImage2(CvMat * im);

	//�ڶ���������Guassian��DOG������
	ImageOctaves * BuildGaussianOctaves(CvMat * image);
	
	//��Сͼ���²���
	CvMat * halfSizeImage(CvMat * im);
	//Ϊ����ʾͼ���������������ͼ��ˮƽ��ֱƴ��
	CvMat* MosaicHorizen(CvMat* im1,CvMat* im2);
	CvMat* MosaicVertical(CvMat* im1,CvMat* im2);

	//��������������λ�ü�⣬���ȷ���������λ��
	int DetectKeypoint(int numoctaves,ImageOctaves *Gaussianpyr);
	void DisplayKeypointLocation(IplImage* image, ImageOctaves *Gaussianpyr);


	//���Ĳ��������˹ͼ����ݶȺͷ�ֵ����������������������
	void ComputeGrad_DirecandMag(int numoctaves,ImageOctaves *Gaussianpyr);
	//ȷ�����������㴦����������
	void AssignTheMainOrientation(int numoctaves, ImageOctaves *Gaussianpyr,ImageOctaves *mag_pyr,ImageOctaves *grad_pyr);
	//�õ���ά��˹ģ��
	CvMat * GaussianKernel2D(float sigma); 
	//���з���ֱ��ͼͳ��
	int FindClosestRotationBin(int binCount,float angle);
	//�Է���ֱ��ͼ�˲�
	void AverageWeakBins(double * bins,int binCount);
	//ȷ��������������
	bool InterpolateOrientation(double left,double middle,double right,double *degreeCorrection,double *peakValue);
	
	//���岽����ȡ���������㴦������������
	void ExtractFeatureDescriptors(int numoctaves,ImageOctaves *Gaussianpyr);
	//˫���Բ�ֵ���������ؼ�ĻҶ�ֵ
	float getPixelBI(CvMat * im,float col,float row);
	//�õ�������ŷʽ����
	float GetVecNorm(float * vec,int dim);
	//��ʾ������
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
