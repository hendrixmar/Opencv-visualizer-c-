#include "functions.h"


int main(int argc, const char *argv[])
{   

    if ( argc < 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    cv::Mat image= cv::imread( argv[1], 0);

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    

	// Init cvui. If you don't tell otherwise, cvui will create the required OpenCV
	// windows based on the list of names you provided.
	const cv::String windows[] = { WINDOW1_NAME, WINDOW2_NAME};
	cvui::init(windows, 2);
    
	
	
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