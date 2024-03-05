/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under Apache 2 license: https://www.apache.org/licenses/LICENSE-2.0

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef QCOLOR_H
#define QCOLOR_H

#include <opencv.hpp>

#include "vertex.h"

class _qcolor
{
public:

  _qcolor(int Red=0,int Green=0,int Blue=255):Colorf(float(Red),float(Green),float(Blue)){}
  _qcolor(const _qcolor& Color1){Colorf=Color1.Colorf;}

  bool operator!=(const _qcolor& Color1);
  bool operator==(const _qcolor& Color1);
  _qcolor& operator=(const _qcolor& Color1);

  _qcolor& setHsv(float Hue,float Saturation, float Value);

  _qcolor& toRgb();
  _qcolor& toHsv();

  float red(){return Colorf.r;}
  float green(){return Colorf.g;}
  float blue(){return Colorf.b;}

  float hue(){return Colorf.r;}
  float saturation(){return Colorf.g;}
  float value(){return Colorf.b;}

protected:
  _vertex3f Colorf;
};

#endif

