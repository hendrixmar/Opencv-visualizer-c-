#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include "functions.h"

#define WINDOW1_NAME "Window 1"
#define WINDOW2_NAME "Windows 2"
#define WINDOW3_NAME "Windows 3"
#define WINDOW4_NAME "Windows 4"
int horizontal = 1;
int vertical = 1;
double grades =0;



// Update and show a window in a single call using cvui::imshow().
void compact(const cv::String& name, cv::Mat image, cv::Mat temp) {
	// Create a frame for this window and fill it with a nice color
	cv::Mat frame = cv::Mat(400, 600, CV_8UC3);
	
	frame = cv::Scalar(49, 52, 49);
	bool vert_,horz_, rota_;

	// Inform cvui that the components to be rendered from now one belong to
	// a window in particular.
	//
	// If you don't inform that, cvui will assume the components belong to
	// the default window (informed in cvui::init()). In that case, the
	// interactions with all other windows being used will not work.
	cvui::context(name);

	cvui::printf(frame, 20, 5, "Move image horizontally");
	cvui::printf(frame, 20, 75, "Move image vertically");
	vert_ = cvui::trackbar(frame, 20, 20, 220, &horizontal, 0, 100);
	horz_ = cvui::trackbar(frame, 20, 90, 220, &vertical, 0, 100);

	if (vert_ || horz_) {
		traslation(image,temp, horizontal, vertical);

		cvui::imshow(WINDOW1_NAME, temp);
		
	}

	cvui::printf(frame, 20, 140, "Rotate image");
	
	rota_ = cvui::trackbar(frame, 20, 150, 220, &grades, 0.0, 360.0);

	if(rota_){
		std::cout<<"Bruh"<<std::endl;
	}

	cvui::update(name);
	
	// Tell cvui to update its internal structures regarding a particular window
	// then show it. Below we are using cvui::imshow(), which is cvui's version of
	// the existing cv::imshow(). They behave exactly the same, the only difference
	// is that cvui::imshow() will automatically call cvui::update(name) for you.
	cvui::imshow(WINDOW2_NAME, frame);
}



int main(int argc, const char *argv[])
{
	// Init cvui. If you don't tell otherwise, cvui will create the required OpenCV
	// windows based on the list of names you provided.
	const cv::String windows[] = { WINDOW1_NAME, WINDOW2_NAME};
	cvui::init(windows, 2);
	cv::Mat image = cv::imread("test.jpg",1);
	
	cvui::imshow(WINDOW1_NAME, image);
	cv::Mat temp = cv::Mat::zeros(image.rows,image.cols,image.type()); 
	//image  = traslation(image, value, value);
	
	while (1) {
		// The functions below will update a window and show them using cv::imshow().
		// In that case, you must call the pair cvui::context(NAME)/cvui::update(NAME)
		// to render components and update the window.
		compact(WINDOW2_NAME, image, temp);
		//window(WINDOW1_NAME, image);
		
		
		// The function below will do the same as the funcitons above, however it will
		// use cvui::imshow() (cvui's version of cv::imshow()), which will automatically
		// call cvui::update() for us.


		// Check if ESC key was pressed
		if (cv::waitKey(20) == 27) {
			break;
		}
	}

	return 0;
}