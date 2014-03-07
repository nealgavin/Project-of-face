#if !defined(AFX_IMAGEFULL_H__58D58994_09A1_488A_A945_83E63D8531B9__INCLUDED_)
#define AFX_IMAGEFULL_H__58D58994_09A1_488A_A945_83E63D8531B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// imagefull.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// imagefull dialog
#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "cxcore.h"
#include <string>
#include "featurematch.h"
#include "stitchimage.h"
using namespace std;
#include "afxtempl.h"

class imagefull : public CDialog
{
// Construction
public:
	imagefull(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(imagefull)
	enum { IDD = IDD_fullimage };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

public:
	IplImage *imageone,*imagetwo,*imagethree,*imagefour,*imagefive,*imagesix;
	IplImage *imageptocy11,*imageptocy22,*imageptocy33,*imageptocy44,*imageptocy55,*imageptocy66;
	IplImage *imageptocy1,*imageptocy2,*imageptocy3,*imageptocy4,*imageptocy5,*imageptocy6;
	featurematch aa;
	stitchimage bb;

	//step1
	IplImage *image1,*DoubleSizeImage1;
	CvMat *tempMat1;

	
	//step2
	ImageOctaves *Gaussianpyr1,*Gaussianpyr2;
	ImageOctaves *DOGoctaves1,*DOGoctaves2;

	//ƴ�Ӻ�����
	IplImage *imageok1;

	//////////////////////////���ӵ�


public:
	IplImage* cutrightimage(IplImage *image);
	IplImage* cutleftimage(IplImage *image);
	//step1�����������ײ�
	void step1(IplImage *image);

	//���������
	void step2();

	//�����������ֵ
	void step3();

	//�����ڴ�
	void clearmemory();

	//��һ��ƴ��
	void stitch1(IplImage *imag1,IplImage *imag2);

	///////////////////////////���Ӳ���
//1 �������
void detect_and_draw( IplImage* img ,int in_or_check);
IplImage* RESIZE_PIC(IplImage*img);
void Draw(string path_name,int fun_choose);
void data_in_mysql(string stu_id,string index,string path_save);
bool SQL_query(string data_query);
void ShowImg(IplImage*img);
//2 ƥ��
void Match();
void get_detect_and_check();
void getSample_NUM(int&num,char*ss);
void PickPCA(int Sample_Num,char*Path_of_Img);
CvMat* Load_Image_And_Training(int Training_Num,const char*Img_Path,bool sam);
void MatchWhoPCA(const char*path_who);
void UPDATE_SQL_CEHCK(string name/*,string course_id,string class_id*/);

//�������ݿ�
void Mysql_link();

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(imagefull)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(imagefull)
	afx_msg void Onopenimage1();
	afx_msg void Onopenimage2();
	afx_msg void Onopenimage6();
	afx_msg void Onstitchfullimage();
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	afx_msg void OnButton5();
	afx_msg void OnButton4();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEFULL_H__58D58994_09A1_488A_A945_83E63D8531B9__INCLUDED_)
