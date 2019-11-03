#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include "cvui.h"
#define CVUI_IMPLEMENTATION
#define R 2
#define G 1
#define B 0
#define SIN(g) sin(g * 3.141592653589/180) 
#define COS(g) cos(g * 3.141592653589/180)

#define WINDOW1_NAME "Window 1"
#define WINDOW2_NAME "Windows 2"
#define WINDOW3_NAME "Windows 3"
#define WINDOW4_NAME "Windows 4"



extern int horizontal;
extern int vertical;
extern int level_green;
extern int level_blue;
extern int level_red;
extern double grades;
extern bool RGB[3];




// Update and show a window in a single call using cvui::imshow().
void compact(const cv::String& name, cv::Mat image, cv::Mat temp);


void traslation(cv::Mat source, cv::Mat &destination, int tx, int ty);

void rotation(cv::Mat source, cv::Mat &destination, double grades);
void colors( cv::Mat source, cv::Mat &destination);


