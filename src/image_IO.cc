/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under Apache 2 license: https://www.apache.org/licenses/LICENSE-2.0

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "image_IO.h"

using namespace std;

/*************************************************************************/
// BGR format

void _image_IO::read_image(string Name,cv::Mat &Image_in)
{
  #ifdef WINDOWS
  string Aux_string;
  for (int i=0;i<Name.size();i++){
    if (Name[i]=='/'){
      Aux_string.push_back('\\');
    }
    else Aux_string.push_back(Name[i]);
  }
  Name=Aux_string;
  #endif

  Image_in=cv::imread(Name,cv::IMREAD_UNCHANGED);
  if( !Image_in.data ){ // check if the image has been loaded properly
    cout << "Error reading the image: " << Name << endl;
    exit(-1);
  }
}

/*************************************************************************/

void _image_IO::write_image(string Name,cv::Mat &Image_out)
{
	imwrite(Name, Image_out);
}
