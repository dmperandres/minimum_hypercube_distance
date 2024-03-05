/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under Apache 2 license: https://www.apache.org/licenses/LICENSE-2.0

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "qcolor.h"

using namespace std;

/*************************************************************************/

bool _qcolor::operator!=(const _qcolor& Color1)
{
  if (Colorf!=Color1.Colorf) return true;
  else return false;
}

/*************************************************************************/

bool _qcolor::operator==(const _qcolor& Color1)
{
  if (Colorf==Color1.Colorf) return true;
  else return false;
}

/*************************************************************************/

_qcolor& _qcolor::operator=(const _qcolor& Color1)
{
  Colorf=Color1.Colorf;
  return *this;
}

/*************************************************************************/

_qcolor& _qcolor::setHsv(float Hue,float Saturation, float Value)
{
  Colorf.r=Hue;
  Colorf.g=Saturation;
  Colorf.b=Value;

  return *this;
}

/*************************************************************************/

_qcolor& _qcolor::toRgb()
{
  cv::Mat Input(1,1,CV_32FC3);
  cv::Mat Output(1,1,CV_32FC3);

//  cout << "original " << Colorf.r << " " << Colorf.g << " " << Colorf.b << endl;

  Input.at<cv::Vec3f>(0)[0]=Colorf.r; // H
  Input.at<cv::Vec3f>(0)[1]=Colorf.g/255.0f; // S
  Input.at<cv::Vec3f>(0)[2]=Colorf.b/255.0f; // V
  cvtColor(Input, Output, cv::COLOR_HSV2RGB);
  Colorf.r=Output.at<cv::Vec3f>(0)[0]*255.0f;
  Colorf.g=Output.at<cv::Vec3f>(0)[1]*255.0f;
  Colorf.b=Output.at<cv::Vec3f>(0)[2]*255.0f;

//  cout << "toRGB " << Colorf.r << " " << Colorf.g << " " << Colorf.b << endl;

  return *this;
}

/*************************************************************************/

_qcolor& _qcolor::toHsv()
{
  cv::Mat Input(1,1,CV_32FC3);
  cv::Mat Output(1,1,CV_32FC3);

//  cout << "original " << Colorf.r << " " << Colorf.g << " " << Colorf.b << endl;

  Input.at<cv::Vec3f>(0)[0]=Colorf.r/255.0f;
  Input.at<cv::Vec3f>(0)[1]=Colorf.g/255.0f;
  Input.at<cv::Vec3f>(0)[2]=Colorf.b/255.0f;
  cvtColor(Input, Output, cv::COLOR_RGB2HSV);
  Colorf.r=Output.at<cv::Vec3f>(0)[0];
  Colorf.g=Output.at<cv::Vec3f>(0)[1];
  Colorf.b=Output.at<cv::Vec3f>(0)[2];

//  cout << "toHsv " << Colorf.r << " " << Colorf.g << " " << Colorf.b << endl;

  return *this;
}
