#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#define R 2
#define G 1
#define B 0
#define SIN(g) sin(g * 3.141592653589/180) 
#define COS(g) cos(g * 3.141592653589/180)

extern int horizontal;
extern int vertical;
extern int level_green;
extern int level_blue;
extern int level_red;
extern double grades;
extern bool RGB[3];

void traslation(cv::Mat source, cv::Mat &destination, int tx, int ty);

void rotation(cv::Mat source, cv::Mat &destination, double grades);
void colors( cv::Mat source, cv::Mat &destination);


