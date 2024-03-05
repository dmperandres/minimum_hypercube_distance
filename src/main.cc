/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under Apache 2 license: https://www.apache.org/licenses/LICENSE-2.0

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include <opencv.hpp>

#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include <EGL/egl.h>

#include "common.h"
#include "image_IO.h"
#include "file_csv.h"
#include "layer_map_distance.h"
#include "palette_data.h"
#include "qcolor.h"

using namespace std;

class _atomic_data{
public:
  std::string Short_name;
  std::string Name;
  float Atomic_number=0;
  float Atomic_weight=0;
  _qcolor Color;

  _atomic_data(){}
  _atomic_data(std::string Short_name1,std::string Name1,float Atomic_number1,float Atomic_weight1,_qcolor Color1):Short_name(Short_name1), Name(Name1), Atomic_number(Atomic_number1),Atomic_weight(Atomic_weight1),Color(Color1)
  {};
  _atomic_data(const _atomic_data &Data1)
  {
    Short_name=Data1.Short_name;
    Name=Data1.Name;
    Atomic_number=Data1.Atomic_number;
    Atomic_weight=Data1.Atomic_weight;
    Color=Data1.Color;
  };
};

const std::vector<_atomic_data> Vec_atomic_data={
  {"Ag","silver",47,107.87f,_qcolor(255,0,0)},
  {"Al","aluminium",13,26.982f,_qcolor(255,149,0)},
  {"Ar","argon",18,39.95f,_qcolor(213,255,0)},
  {"As","arsenic",33,74.922f,_qcolor(240,50,230)},
  {"Au","gold",79,196.97f,_qcolor(0,255,85)},
  {"B","boron",5,10.81f,_qcolor(0,255,234)},
  {"Ba","barium",56,137.33f,_qcolor(60,180,75)},
  {"Be","beryllium",4,9.0122f,_qcolor(21,0,255)},
  {"Bi","bismuth",83,208.98f,_qcolor(170,0,255)},
  {"Br","bromine",35,79.904f,_qcolor(255,0,191)},
  {"C","carbon",6,12.011f,_qcolor(255,0,42)},
  {"Ca","calcium",20,40.078f,_qcolor(255,255,25)},
  {"Cd","cadmium",48,112.41f,_qcolor(0,130,200)},
  {"Ce","cerium",58,140.12f,_qcolor(106,255,0)},
  {"Cl","chlorine",17,35.45f,_qcolor(0,255,42)},
  {"Co","cobalt",27,58.933f,_qcolor(245,130,48)},
  {"Cr","chromium",24,51.996f,_qcolor(145,30,180)},
  {"Cs","caesium",55,132.91f,_qcolor(0,21,255)},
  {"Cu","copper",29,63.546f,_qcolor(70,240,240)},
  {"Dy","dysprosium",66,162.50f,_qcolor(255,0,234)},
  {"Er","erbium",68,167.26f,_qcolor(255,0,85)},
  {"Eu","europium",63,151.96f,_qcolor(255,64,0)},
  {"F","fluorine",9,18.998f,_qcolor(255,213,0)},
  {"Fe","iron",26,55.845f,_qcolor(230,25,75)},
  {"Ga","gallium",31,69.723f,_qcolor(0,255,0)},
  {"Gd","gadolinium",64,157.25f,_qcolor(0,255,149)},
  {"Ge","germanium",32,72.630f,_qcolor(0,213,255)},
  {"H","hydrogen",1,1.008f,_qcolor(0,64,255)},
  {"He","helium",2,4.0026f,_qcolor(85,0,255)},
  {"Hf","hafnium",72,178.49f,_qcolor(234,0,255)},
  {"Hg","mercury",80,200.59f,_qcolor(210,245,60)},
  {"Ho","holmium",67,164.93f,_qcolor(255,21,0)},
  {"I","iodine",53,126.90f, _qcolor(255,170,0)},
  {"In","indium",49,114.82f,_qcolor(191,255,0)},
  {"Ir","iridium",77,192.22f,_qcolor(42,255,0)},
  {"K","potassium",19,39.098f,_qcolor(0,128,128)},
  {"Kr","krypton",36,83.798f,_qcolor(0,255,255)},
  {"La","lanthanum",57,138.91f,_qcolor(0,106,255)},
  {"Li","lithium",3,6.94f,_qcolor(42,0,255)},
  {"Lu","lutetium",71,174.97f,_qcolor(191,0,255)},
  {"Mg","magnesium",12,24.305f,_qcolor(255,0,170)},
  {"Mn","manganese",25,54.938f,_qcolor(220,190,255)},
  {"Mo","molybdenum",42,95.95f,_qcolor(255,128,0)},
  {"N","nitrogen",7,14.007f,_qcolor(234,255,0)},
  {"Na","sodium",11,22.990f,_qcolor(85,255,0)},
  {"Nb","niobium",41,92.906f,_qcolor(0,255,64)},
  {"Nd","neodymium",60,144.24f,_qcolor(0,255,213)},
  {"Ne","neon",10,20.180f,_qcolor(0,149,255)},
  {"Ni","nickel",28,58.693f,_qcolor(170,110,40)},
  {"O","oxygen",8,15.999f,_qcolor(149,0,255)},
  {"Os","osmium",76,190.23f,_qcolor(255,0,213)},
  {"P","phosphorus",15,30.974f,_qcolor(0,178,255)},
  {"Pb","lead",82,207.2f,_qcolor(128,0,0)},
  {"Pd","palladium",46,106.42f,_qcolor(255,234,0)},
  {"Pm","promethium",61,0,_qcolor(128,255,0)},
  {"Pr","praseodymium",59,140.91f,_qcolor(0,255,21)},
  {"Pt","platinum",78,195.08f,_qcolor(0,255,170)},
  {"Rb","rubidium",37,85.468f,_qcolor(0,191,255)},
  {"Re","rhenium",75,186.21f,_qcolor(0,42,255)},
  {"Rh","rhodium",45,102.91f,_qcolor(106,0,255)},
  {"Ru","ruthenium",44,101.07f,_qcolor(255,0,255)},
  {"S","sulfur",16,32.06f,_qcolor(255,0,106)},
  {"Sb","antimony",51,121.76f,_qcolor(170,255,195)},
  {"Sc","scandium",21,44.956f,_qcolor(255,135,0)},
  {"Se","selenium",34,78.971f,_qcolor(128,128,0)},
  {"Si","silicon",14,28.085f,_qcolor(21,255,0)},
  {"Sm","samarium",62,150.36f,_qcolor(0,255,128)},
  {"Sn","tin",50,118.71f,_qcolor(0,0,128)},
  {"Sr","strontium",38,87.62f,_qcolor(0,85,255)},
  {"Ta","tantalum",73,180.95f,_qcolor(64,0,255)},
  {"Tb","terbium",65,158.93f,_qcolor(213,0,255)},
  {"Tc","technetium",43,0.0f,_qcolor(255,0,149)},
  {"Te","tellurium",52,127.60f,_qcolor(255,0,0)},
  {"Th","thorium",90,232.04f,_qcolor(255,110,0)},
  {"Ti","titanium",22,47.867f,_qcolor(255,215,180)},
  {"Tl","thallium",81,204.38f,_qcolor(130,0,255)},
  {"Tm","thulium",69,168.93f,_qcolor(64,255,0)},
  {"V","vanadium",23,50.942f,_qcolor(0,255,85)},
  {"W","tungsten",74,183.84f,_qcolor(0,255,234)},
  {"Xe","xenon",54,131.29f,_qcolor(0,128,255)},
  {"Y","yttrium",39,88.906f,_qcolor(21,0,255)},
  {"Yb","ytterbium",70,173.05f,_qcolor(170,0,255)},
  {"Zn","zinc",30,65.38f,_qcolor(60,180,75)},
  {"Zr","zirconium",40,91.224f,_qcolor(155,0,255)}
};

std::vector<std::string> Vec_element_name={"As","Ba","Ca","Cd","Co","Cr","Cu","Fe","Hg","K","Mn","Ni","Pb","Sb","Se","Sn","Ti","Zn"};

static const EGLint configAttribs[] = {
  EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
  EGL_BLUE_SIZE, 8,
  EGL_GREEN_SIZE, 8,
  EGL_RED_SIZE, 8,
  EGL_DEPTH_SIZE, 8,
  EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
  EGL_NONE
};

static const int pbufferWidth = 9;
static const int pbufferHeight = 9;

static const EGLint pbufferAttribs[] = {
  EGL_WIDTH, pbufferWidth,
  EGL_HEIGHT, pbufferHeight,
  EGL_NONE,
};

/*************************************************************************/

void adjust_image_sizes(int &Width1, int &Height1)
{
  float Rest;

  if (Width1%4!=0){
    Rest=int(roundf(float(Width1)/4.0f));
    Width1=int(Rest*4);

  }
  if (Height1%4!=0){
    Rest=int(roundf(float(Height1)/4.0f));
    Height1=int(Rest*4);
  }
}

/*************************************************************************/

void process_xrf_data(float& Max_value,float& Max_value_adjusted,float Atomic_number, vector<float>& Vec_value)
{
  float Max_aux=-1;
  for (unsigned int i=0;i<Vec_value.size();i++){
    if (Vec_value[i]>=0 && Vec_value[i]>Max_aux){
      Max_aux=Vec_value[i];
    }
  }

  Max_value=Max_aux;

  float Divisor=Max_aux;
  if (Max_aux==0) Divisor=1;

  Max_value_adjusted=Max_value/Atomic_number;

  for (unsigned int i=0;i<Vec_value.size();i++){
    if (Vec_value[i]>=0){
      Vec_value[i]=Vec_value[i]/Divisor;
    }
    else{
      Vec_value[i]=-1;
    }
  }
}

/*************************************************************************/

// int load_control_data(string Element,vector<bool> &Vec_control)
// {
//   int Num_valid=0;
//   Vec_control.resize(165);

//   std::fstream File;
//   File.open("./input_data/"+Element+"_control.txt",ios::in);

//   string Line;
//   getline(File,Line);
//   File.close();
//   for (unsigned int i=0;i<165;i++){
//     if (Line[i]=='Y'){
//       Vec_control[i]=true;
//       Num_valid++;
//     }
//     else Vec_control[i]=false;
//   }
//   return Num_valid;
// }

/*************************************************************************/

void load_data_csv_format(string File_name,_project_data_ns::_project_data &Project_data,std::vector<std::string> &Vec_element_name)
{
  string Error;
  string Line;
  int Error_position;

  _file_csv File_csv;
  File_csv.open(File_name,_file_csv_ns::_mode::MODE_READ);
  if (File_csv.read(Project_data,Vec_element_name,Error,Line,Error_position)==true){
    File_csv.close();
  }
  else{
    File_csv.close();
    cout << "There is an error in the 'csv'  file" << endl;
    exit(-1);
  }

//  cout << "Num samples " << Project_data.Num_samples << endl;
//  cout << "widht " << Project_data.Width << endl;
//  cout << "Height " << Project_data.Height << endl;
//  cout << "X " << Project_data.Vec_coordinate_x.size() << endl;
//  cout << "Num elements " << Project_data.Vec_interpreted_data_xrf.size() << endl;

  // adjust the y coordinates to be right oriented (OpenGL
  for (unsigned int i=0;i<Project_data.Vec_coordinate_y.size();i++){
    Project_data.Vec_coordinate_y[i]=Project_data.Height-1.0f-Project_data.Vec_coordinate_y[i];
  }

  // addjust the values of the meausres depending on the atomic number

  for (unsigned int i=0;i<Project_data.Vec_interpreted_data_xrf.size();i++){
    float Atomic_number=-1;

    string Element_name=Project_data.Vec_interpreted_data_xrf[i].Name;

    for (auto &Data: Vec_atomic_data){
      if (Data.Short_name==Element_name){
        Atomic_number=Data.Atomic_number;
        break;
      }
    }

    if (Atomic_number==-1){
      cout << "The element " << Element_name << " does not exist" << endl;
      exit(-1);
    }

    process_xrf_data(Project_data.Vec_interpreted_data_xrf[i].Max_value,Project_data.Vec_interpreted_data_xrf[i].Max_value_adjusted, Atomic_number, Project_data.Vec_interpreted_data_xrf[i].Vec_value);
  }
}

/*************************************************************************/
_qcolor compute_color(string Name_element)
{
  _qcolor Color;

  for (auto &Data: Vec_atomic_data){
    if (Name_element==Data.Short_name){
      Color=Data.Color;
      break;
    }
  }

  return Color;
}

/*************************************************************************/

void create_colors(int Pos_palette1, string Element_name1,vector<float> &Vec_proportion, vector<_qcolor> &Vec_color1,_color_map_ns::_zero_value_color Zero_value_color1)
{
  _color_map Color_map;
  _qcolor Color;

  Color_map.compute_regular_values(_palette_data_ns::Vec_palette_data_aux[Pos_palette1].Num_steps);

  Vec_proportion=Color_map.Vec_values;

  Color_map.zero_value_color(Zero_value_color1);

  Color=compute_color(Element_name1);

  // it is necessary to compute the new colors depending on the element
  if (_palette_data_ns::Vec_palette_data_aux[Pos_palette1].Data_type==_palette_data_ns::_data_type::DATA_TYPE_DISCRETE){
    if (_palette_data_ns::Vec_palette_data_aux[Pos_palette1].Color_type==_palette_data_ns::_color_type::COLOR_TYPE_TONE){
      Color_map.compute_tones_sections(_palette_data_ns::Vec_palette_data_aux[Pos_palette1].Num_steps,Vec_color1,Color);
    }
    else{
      Color_map.compute_colors_sections(_palette_data_ns::Vec_palette_data_aux[Pos_palette1].Num_steps,Vec_color1,Color);
    }
  }
  else{
    if (_palette_data_ns::Vec_palette_data_aux[Pos_palette1].Color_type==_palette_data_ns::_color_type::COLOR_TYPE_TONE){
      Color_map.compute_tones_interpolations(_palette_data_ns::Vec_palette_data_aux[Pos_palette1].Num_steps,Vec_color1,Color);
    }
    else{
      Color_map.compute_colors_interpolations(_palette_data_ns::Vec_palette_data_aux[Pos_palette1].Num_steps,Vec_color1,Color);
    }
  }
}

/*************************************************************************/

void compute_normalized_image(_common_ns::_color_model Color_model, shared_ptr<cv::Mat> Original,shared_ptr<cv::Mat> Image_normalized)
{
  // convert first the RGBA image. It is used with the other conversions
  // BGRA -> RGBA  (interchange R and B channels)
  cv::cvtColor(*Original.get(),*Image_normalized.get(),cv::COLOR_BGRA2RGBA,4);
  // convert to 4 float
  Image_normalized->convertTo(*Image_normalized, CV_32FC4);

  cv::Vec4f Data;
  // RGBA
  // This is compulsory: the other color models convert from RGB to XXX. The values must be normalized
  for (size_t i=0;i<Image_normalized->total();i++){
    Data=Image_normalized->at<cv::Vec4f>(i);
    Data/=255.0f;
    Image_normalized->at<cv::Vec4f>(i)=Data;
  }

  if (Color_model!=_common_ns::_color_model::COLOR_MODEL_RGB){
    // copy the color image
//    shared_ptr<cv::Mat> Image_normalized1=make_shared<cv::Mat>();

//   *Image_normalized1=Image_normalized->clone();

    cv::Mat Color_channels(Original->rows,Original->cols, CV_32FC3);
    cv::Mat Alpha_channel(Original->rows,Original->cols, CV_32FC1);
    cv::Mat Out[]={Color_channels,Alpha_channel};
    int from_to[] = { 0,0, 1,1, 2,2, 3,3 };
    // split the channels in the color part and the transparency part
    // source, num_sources, destiny, num_destinies, from_to, num_pairs
    cv::mixChannels(Image_normalized.get(),1,Out,2,from_to,4);

    switch (int(Color_model)) {
      case int(_common_ns::_color_model::COLOR_MODEL_HLS):
        //  0<=H<=360, 0<=S<=1, 0<=V<=1
        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2HLS,3);
        break;
      case int(_common_ns::_color_model::COLOR_MODEL_HSV):
        //  0<=H<=360, 0<=S<=1, 0<=V<=1
        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2HSV,3);
        break;
      case int(_common_ns::_color_model::COLOR_MODEL_LAB):
        //  0<=L<=100, -127<=a<=127, -127<=b<=127
        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2Lab,3);
        break;
      case int(_common_ns::_color_model::COLOR_MODEL_LUV):
        //  0<=L<=100, -134<=u<=220, -140<=v<=122
        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2Luv,3);
        break;
      default:break;
    }

    // add the Alpha_channel channel
    cv::mixChannels(Out,2,Image_normalized.get(),1,from_to,4);
  }
}

/*************************************************************************/

string create_file_name(string Element_name, _common_ns::_color_model Color_model1, vector<bool> Use_colors1, vector<bool> Use_positions1, bool Distance_normalization1, _layer_map_distance_ns::_position_normalization_type Position_normalization_type1,int Probe_value,int Num_points_value)
{
  std::string File_name=Element_name+"_";

  // text to know the type of computation that was made: c -> color, p -> position
  File_name=File_name+_common_ns::Vec_names_color_model[int(Color_model1)]+"_";
  if (Use_colors1[0]==true || Use_colors1[1]==true || Use_colors1[2]==true) File_name=File_name+"c";
  if (Use_colors1[0]==true) File_name=File_name+"1";
  if (Use_colors1[1]==true) File_name=File_name+"2";
  if (Use_colors1[2]==true) File_name=File_name+"3";
  if (Use_positions1[0]==true || Use_positions1[1]==true) File_name=File_name+"p";
  if (Use_positions1[0]==true) File_name=File_name+"1";
  if (Use_positions1[1]==true) File_name=File_name+"2";

  if (Distance_normalization1==true) File_name=File_name+"_NY";
  else File_name=File_name+"_NN";

  if (Position_normalization_type1==_layer_map_distance_ns::_position_normalization_type::POSITION_NORMALIZATION_HOMOGENEOUS) File_name=File_name+"_HO";
  else File_name=File_name+"_HE";

  File_name=File_name+"_P"+to_string(Probe_value);

  return File_name;
}

/*************************************************************************/

bool check_true_false(string String,bool &Var,string Text)
{
  if (String=="TRUE" || String=="FALSE"){
    if (String=="FALSE") Var=false;
    return true;
  }
  else{
    cout << "Error with " << Text <<endl;
    return false;
  }
}

/*************************************************************************/

bool directory_exists(const std::string& path) {
  struct stat info;
  if(stat(path.c_str(), &info) != 0) {
    return false; // the path doesn't exist
  } else if(info.st_mode & S_IFDIR) {
    return true; // the path exists
  } else {
    return false; // It is not a folder
  }
}

/*************************************************************************/

void check_opengl()
{
  const GLubyte* strm;
  std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << "\n";
  if (!glewGetExtension("GL_ARB_texture_non_power_of_two")){
    std::cerr << "Warning: ARB_texture_non_power_of_two may not be supported" << "\n";
    exit (-1);
  }

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";
  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";
}

/*************************************************************************/

EGLDisplay initilize_EGL()
{
  // 1. Initialize EGL
  EGLDisplay eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  EGLint major, minor;

  eglInitialize(eglDpy, &major, &minor);

  // 2. Select an appropriate configuration
  EGLint numConfigs;
  EGLConfig eglCfg;

  eglChooseConfig(eglDpy, configAttribs, &eglCfg, 1, &numConfigs);

  // 3. Create a surface
  //    EGLSurface eglSurf = eglCreatePbufferSurface(eglDpy, eglCfg,pbufferAttribs);

  // 4. Bind the API
  eglBindAPI(EGL_OPENGL_API);

  // 5. Create a context and make it current
  EGLContext eglCtx = eglCreateContext(eglDpy, eglCfg, EGL_NO_CONTEXT,nullptr);

  //    eglMakeCurrent(eglDpy, eglSurf, eglSurf, eglCtx);
  eglMakeCurrent(eglDpy, EGL_NO_SURFACE, EGL_NO_SURFACE, eglCtx);

  if(EGL_SUCCESS != eglGetError()){
    cout << "Problem with EGL";
  }

  GLenum err;
  glewExperimental = GL_TRUE;
  err = glewInit();
  if (GLEW_OK != err){
    // Problem: glewInit failed, something is seriously wrong.
    std::cerr << "Error: " << glewGetErrorString(err) << "\n";
    exit (-1);
  }

  return eglDpy;
}

/*************************************************************************/

int main(int argc, char *argv[])
{
  int Element_value=0;
  _common_ns::_color_model Color_model_value=_common_ns::_color_model::COLOR_MODEL_RGB;
  bool Use_color1=true;
  bool Use_color2=true;
  bool Use_color3=true;
  bool Use_position1=true;
  bool Use_position2=true;
  bool Distance_normalization=true;
  _layer_map_distance_ns::_position_normalization_type Position_normalization_type=_layer_map_distance_ns::_position_normalization_type::POSITION_NORMALIZATION_HOMOGENEOUS;
  int Probe_value=1;
  int Palette_value=3;
  _color_map_ns::_zero_value_color Zero_value_color=_color_map_ns::_zero_value_color::ZERO_VALUE_COLOR_BLACK;

  if (!(argc==2 || argc==16)){
    cout << "usage: mhd Input_data(path to CSV file with data) Input_image(path to PNG file) Output_folder(path to output folder) Element_name color_model[RGB|HLS|HSV|LAB|LUB] color1[TRUE|FALSE] color2[TRUE|FALSE] color3[TRUE|FALSE] position1[TRUE|FALSE] position2[TRUE|FALSE] normalization[TRUE|FALSE] position_normalization[HOM|HET] probe[1|2|...|49] palette_number[0|1|2|...|15] Color_for_zero[BLACK|WHITE]\n\nusage: mhd PROBES(shows the valid values)\n\nusage: mhd PALETTES(shows the valid values)\n\nusage: mhd OPENGL(shows the OpenGL driver)\n\nexample: mhd ./input/data.csv ./input/vis_image.png ./output As RGB TRUE TRUE TRUE TRUE TRUE TRUE HET 1 3 BLACK" << endl;

    exit(-1);
  }

  if (argc==2){
    if (string(argv[1])=="PROBES"){
      cout << "Probes" << endl;
      for (unsigned int i=0; i<_layer_map_distance_ns::Vec_name_probe.size();i++){
        cout << _layer_map_distance_ns::Vec_name_probe[i] << " -> " << i << endl;
      }
      cout << endl << "Default = " << Probe_value << endl;
    }
    if (string(argv[1])=="PALETTES"){
      cout << "Palettes" << endl;
      for (unsigned int i=0;i<_palette_data_ns::Vec_palette_data_aux.size();i++){
        cout << _palette_data_ns::Vec_palette_data_aux[i].Name << " -> " << i << endl;
      }
      cout << endl << "Default = " << Palette_value << endl;
    }
    if (string(argv[1])=="OPENGL"){
      EGLDisplay eglDpy=initilize_EGL();
      check_opengl();
      eglTerminate(eglDpy);
    }
    exit(0);
  }

  if (argc==16){
    int Pos=1;
    string Input_data_file=argv[Pos++];
    string Input_image_file=argv[Pos++];
    string Output_folder=argv[Pos++];
    string Element=argv[Pos++];
    string Color_model=argv[Pos++];
    string Color1=argv[Pos++];
    string Color2=argv[Pos++];
    string Color3=argv[Pos++];
    string Position1=argv[Pos++];
    string Position2=argv[Pos++];
    string Normalization=argv[Pos++];
    string Position_normalization=argv[Pos++];
    string Probe=argv[Pos++];
    string Palette=argv[Pos++];
    string Color_for_zero=argv[Pos++];

    {
    std::ifstream infile(Input_data_file);
    if (!infile.good()){
      cout << "Error with Input_data_file" << endl;
      exit(-1);
    }
    }

    {
    std::ifstream infile(Input_image_file);
    if (!infile.good()){
      cout << "Error with Input_image_file" << endl;
      exit(-1);
    }
    }

    {
    if(!directory_exists(Output_folder)) {
      cout << "Error with Output_folder" << endl;
      exit(-1);
    }
    }

    auto It=std::find(Vec_element_name.begin(),Vec_element_name.end(),Element);
    if (It==Vec_element_name.end()){
      cout << "The element " << Element << " is not valid" << endl;
      exit(-1);
    }
    Element_value=It - Vec_element_name.begin();

    if (Color_model=="RGB" || Color_model=="HLS" || Color_model=="HSV" || Color_model=="LAB" || Color_model=="LUV"){
      if (Color_model=="HLS") Color_model_value=_common_ns::_color_model::COLOR_MODEL_HLS;
      if (Color_model=="HSV") Color_model_value=_common_ns::_color_model::COLOR_MODEL_HSV;
      if (Color_model=="LAB") Color_model_value=_common_ns::_color_model::COLOR_MODEL_LAB;
      if (Color_model=="LUV") Color_model_value=_common_ns::_color_model::COLOR_MODEL_LUV;
    }
    else{
      cout << "Error with Color_model" << endl;
      exit(-1);
    }

    if (!check_true_false(Color1,Use_color1,"Color1")) exit(-1);
    if (!check_true_false(Color2,Use_color2,"Color2")) exit(-1);
    if (!check_true_false(Color3,Use_color3,"Color3")) exit(-1);
    if (!check_true_false(Position1,Use_position1,"Position1")) exit(-1);
    if (!check_true_false(Position2,Use_position2,"Position2")) exit(-1);
    if (!check_true_false(Normalization,Distance_normalization,"Normalization")) exit(-1);

    if (Position_normalization=="HOM" || Position_normalization=="HET"){
      if (Position_normalization=="HET") Position_normalization_type=_layer_map_distance_ns::_position_normalization_type::POSITION_NORMALIZATION_HETEROGENEOUS;
    }
    else{
      cout << "Error with Position_normalization" << endl;
      exit(-1);
    }

    Probe_value=stoi(Probe);
    if (Probe_value<0 || Probe_value>9){
      cout << "Error with Probe" << endl;
      exit(-1);
    }

    Palette_value=stoi(Palette);
    if (Palette_value<0 || Palette_value>16){
      cout << "Error with Palette" << endl;
      exit(-1);
    }

    if (Color_for_zero!="BLACK" && Color_for_zero!="WHITE"){
      cout << "Error with Color_for_zero" << endl;
      exit(-1);
    }

    vector<bool> Vec_use_colors={Use_color1,Use_color2,Use_color3};
    vector<bool> Vec_use_positions={Use_position1,Use_position2};

    EGLDisplay eglDpy=initilize_EGL();

    // load data
    _project_data_ns::_project_data Project_data;
    load_data_csv_format(Input_data_file,Project_data,Vec_element_name);

    if (Element_value>=int(Project_data.Vec_interpreted_data_xrf.size())){
      cout << "Error: Element > number of elements in CSV file" << endl;
      exit(-1);
    }

    int Num_of_positions=Project_data.Vec_interpreted_data_xrf[0].Vec_value.size();

    // load image
    _image_IO Image_io;
    shared_ptr<cv::Mat> Input_image=make_shared<cv::Mat>();

    // BGR
    Image_io.read_image(Input_image_file,*Input_image.get());

    int Width_aux=Input_image->cols;
    int Height_aux=Input_image->rows;

    adjust_image_sizes(Width_aux,Height_aux);
    if (Width_aux!=Input_image->cols || Height_aux!=Input_image->rows){
      cv::resize(*Input_image.get(),*Input_image.get(),cv::Size(Width_aux,Height_aux),0,0,cv::INTER_CUBIC);
    }

    // flip the original image to adapt it to OpenGL
    cv::flip(*Input_image.get(),*Input_image.get(),0);
    // convert to BGRA. Add the alpha channel in case the original image has not it
    cv::cvtColor(*Input_image.get(),*Input_image.get(),cv::COLOR_BGR2BGRA,4);

    // Now create the normalized image
    shared_ptr<cv::Mat> Image_normalized=make_shared<cv::Mat>();

    compute_normalized_image(Color_model_value,Input_image,Image_normalized);

    // Out image
    shared_ptr<cv::Mat> Image_out=make_shared<cv::Mat>();
    Image_out->create(Input_image->rows,Input_image->cols,CV_8UC4);

    // create the new layer
    shared_ptr<_layer_map_distance> Layer=make_shared<_layer_map_distance>();
    // the result image
    Layer->image(Image_out);
    // the data of the element
    Layer->add_input_data(Project_data.Vec_coordinate_x,Project_data.Vec_coordinate_y,Project_data.Vec_interpreted_data_xrf[Element_value].Vec_value);
    // the color image
    Layer->add_input_image(Image_normalized);
  //  Layer->add_image_alpha_channel(Image_alpha_channel);
    Layer->size(Image_normalized->cols,Image_normalized->rows);
    Layer->color_model(Color_model_value);
    Layer->probe(_layer_map_distance_ns::Vec_value_probe[Probe_value]);
    Layer->use_colors(Vec_use_colors);
    Layer->use_positions(Vec_use_positions);
    Layer->normalization(Distance_normalization);
    Layer->position_normalization_type(Position_normalization_type);
  //  Layer->data_type_print(Data_type_print1);

    // create color_bar
    if (Color_for_zero=="WHITE"){
      Zero_value_color=_color_map_ns::_zero_value_color::ZERO_VALUE_COLOR_WHITE;
    }

    vector<_qcolor> Vec_color;
    vector<float> Vec_proportion;
    _color_map Color_map;
    Color_map.compute_regular_values(_palette_data_ns::Vec_palette_data_aux[Palette_value].Num_steps);
    create_colors(Palette_value,Project_data.Vec_interpreted_data_xrf[Element_value].Name,Vec_proportion,Vec_color,Zero_value_color);
    Layer->set_colormap(Vec_proportion,Vec_color,int(_palette_data_ns::Vec_palette_data_aux[Palette_value].Data_type));

    Layer->update();

    //
    std::string File_name=create_file_name(Element,Color_model_value,Vec_use_colors,Vec_use_positions,Distance_normalization,Position_normalization_type,Probe_value,Num_of_positions);

    File_name=Output_folder+'/'+File_name;

    cout << File_name << endl;

    // image
    cv::flip(*Image_out.get(),*Image_out.get(),0);

    Image_io.write_image(File_name+".png",*Image_out.get());

    cout << "Process done" << endl;

    eglTerminate(eglDpy);
  }

  return(0);
}
