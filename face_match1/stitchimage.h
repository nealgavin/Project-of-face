#if !defined(AFX_STITCHIMAGE_H__BA0ACBC8_1280_44AB_B5C3_102F825ED05E__INCLUDED_)
#define AFX_STITCHIMAGE_H__BA0ACBC8_1280_44AB_B5C3_102F825ED05E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// stitchimage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// stitchimage dialog


#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "cxcore.h"
#include <string>
#include "featurematch.h"

using namespace std;
#include "afxtempl.h"



typedef struct Keypointaxis
{
	int width1,height1;
	int width2,height2;
	
} Keyaxis;


class stitchimage : public CDialog
{
// Construction
public:
	stitchimage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(stitchimage)
	enum { IDD = IDD_stitch };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(stitchimage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	//���ݳ�Ա
	IplImage *imageone,*imagetwo;
	//ԭͼ
	IplImage *imageptocy11,*imageptocy22;
	//��ͼ�ü����Сͼ
	IplImage *imageptocy1,*imageptocy2;

	IplImage *image1,*image2,*DoubleSizeImage1,*DoubleSizeImage2;
	CvMat *tempMat1,*tempMat2;
	ImageOctaves *Gaussianpyr1,*Gaussianpyr2;
	ImageOctaves *DOGoctaves1,*DOGoctaves2;

	ImageOctaves *mag_thresh;
	ImageOctaves *mag_pyr1,*mag_pyr2;
	ImageOctaves *grad_pyr1,*grad_pyr2;

	Keypoint p1,p2;

	featurematch aa;
	Keyaxis xy1[100];
	//��ȷ��ƥ�����
	int ncount;

	
	//�ɹ�ƥ��
	IplImage *image33;

	//��Ա����
	//����ͶӰ����
	//void palnetocylinder(IplImage *image);

	//ͼ��̫�������ٶ�̫�����ü���һ��ͼ������ұ�
//	void cutrightimage(IplImage * image);
	IplImage* cutrightimage(IplImage *image);
	//�ü��ڶ���ͼƬ�����
	//void cutleftimage(IplImage * image);
	IplImage* cutleftimage(IplImage *image);


	//�ڶ�������gaussian��dog������
	ImageOctaves * BuildGaussianOctaves1(CvMat * image);
	ImageOctaves * BuildGaussianOctaves2(CvMat * image);

	//step3���������
	int DetectKeypoint1(int numoctaves,ImageOctaves *Gaussianpyr1);
	int DetectKeypoint2(int numoctaves,ImageOctaves *Gaussianpyr2);
	void DisplayKeypointLocation1(IplImage* image, ImageOctaves *Gaussianpyr1);
	void DisplayKeypointLocation2(IplImage* image, ImageOctaves *Gaussianpyr2);

	//step4�����ֵ����
	void ComputeGrad_DirecandMag1(int numoctaves,ImageOctaves *Gaussianpyr1);
	void ComputeGrad_DirecandMag2(int numoctaves,ImageOctaves *Gaussianpyr2);

	void AssignTheMainOrientation1(int numoctaves, ImageOctaves *Gaussianpyr,ImageOctaves *mag_pyr,ImageOctaves *grad_pyr);
	void AssignTheMainOrientation2(int numoctaves, ImageOctaves *Gaussianpyr,ImageOctaves *mag_pyr,ImageOctaves *grad_pyr);
	void DisplayOrientation1(IplImage *image,ImageOctaves *Gaussianpyr);
	void DisplayOrientation2(IplImage *image,ImageOctaves *Gaussianpyr);

	//step5��ȡ������
	void ExtractFeatureDescriptors1(int numoctaves,ImageOctaves *Gaussianpyr);
	void ExtractFeatureDescriptors2(int numoctaves,ImageOctaves *Gaussianpyr);

	//ͼ��ƴ��
	void stitch();
	void stitch1();
	void stitch2();
	void stitchok(Keyaxis xx);

	//��ͼ��ƴ��
	void stitch1(IplImage* imag1,IplImage* imag2);
	void stitchok(Keyaxis xx,IplImage* imag1,IplImage* imag2);

	//ԭͼƴ��
	void stitch2(IplImage* imag1,IplImage* imag2);

	//������Է�����
	//���ø�˹��ѡ��Ԫ�������
	int gauss();
	//����opencv�к������
	void opencvsolve();
	//ͼ�����ת,���ڲ�ֵ�㷨
	void rotateneighbor(IplImage *image,float angle);



protected:

	// Generated message map functions
	//{{AFX_MSG(stitchimage)
	afx_msg void Onopenone();
	afx_msg void Onopentwo();
	afx_msg void Onpalnetocy1();
	afx_msg void Onpalnetocy2();
	afx_msg void Onstep11();
	afx_msg void Onstep12();
	afx_msg void Onstep21();
	afx_msg void Onstep22();
	afx_msg void Onstep31();
	afx_msg void Onstep32();
	afx_msg void Onstep41();
	afx_msg void Onstep42();
	afx_msg void Onstep51();
	afx_msg void Onstep52();
	afx_msg void Onsiftstitch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STITCHIMAGE_H__BA0ACBC8_1280_44AB_B5C3_102F825ED05E__INCLUDED_)
