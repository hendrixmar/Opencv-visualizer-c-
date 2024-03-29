#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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
#define WINDOW5_NAME "Windows 5"


extern bool not_;
extern int horizontal;
extern int vertical;
extern double level[3];
extern double grades;
extern bool RGB[3];
extern bool horbord_;


// Update and show a window in a single call using cvui::imshow().

void binary_operations(const cv::String& name, cv::Mat image, cv::Mat temp, bool);

void traslation(cv::Mat source, cv::Mat &destination, int tx, int ty);

void rotation(cv::Mat source, cv::Mat &destination, double grades);
void colors( cv::Mat source, cv::Mat &destination);

void vertical_borders(cv::Mat source, cv::Mat &destination);
void horizontal_borders(cv::Mat source, cv::Mat &destination);
void swap_mat(cv::Mat &image_a, cv::Mat &image_b);
void and_operation(cv::Mat source_a, cv::Mat source_b, cv::Mat &destination);
void or_operation(cv::Mat source_a, cv::Mat source_b, cv::Mat &destination);
void not_operation(cv::Mat &source_a);
void xor_operation(cv::Mat source_a, cv::Mat source_b, cv::Mat &destination);
void size_reducing(cv::Mat source, cv::Mat &destination, int size_reduction);