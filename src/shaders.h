/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under Apache 2 license: https://www.apache.org/licenses/LICENSE-2.0

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef SHADERS_H
#define SHADERS_H

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/*************************************************************************/

class _shaders
{
public:

  GLuint load_shaders(string File_vertex_shader, string File_fragment_shader);
  GLuint load_shaders(const GLchar **Vertex_shader_source,const GLchar **Fragment_shader_source);

protected:
  bool read_file(string File_name,string &Code);
  void show_error(GLint Shader);
};

#endif // SHADERS_H
