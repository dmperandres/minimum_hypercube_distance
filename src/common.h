/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under Apache 2 license: https://www.apache.org/licenses/LICENSE-2.0

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

namespace _common_ns
{
  struct _result_linear_regresion{
    float Slope=0;
    float Intercept=0;
    float Correlation_coefficient=0;
  };

  enum class _color_model:unsigned char {COLOR_MODEL_RGB,COLOR_MODEL_HLS,COLOR_MODEL_HSV,COLOR_MODEL_LAB,COLOR_MODEL_LUV,COLOR_MODEL_LAST};
  const std::vector<std::string> Vec_names_color_model={"RGB","HLS","HSV","LAB","LUB"};
  const _color_model COLOR_MODEL_DEFAULT=_color_model::COLOR_MODEL_RGB;
}

#endif

