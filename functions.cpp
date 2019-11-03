#include "functions.h"
#include "cvui.h"
 int horizontal = 1;
 int vertical = 1;
 int level_green = 100;
 int level_blue = 100;
 int level_red = 100;
 double grades =0;
 bool RGB[3] ={true, true, true};


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
		rotation(image, temp, grades);
        cvui::imshow(WINDOW1_NAME, temp);
	}

    cvui::checkbox(frame, 20, 240, "Red colors", &RGB[2]);
    cvui::checkbox(frame, 20, 260, "Green colors", &RGB[1]);
    cvui::checkbox(frame, 20, 280, "Blue colors", &RGB[0]);
	cvui::update(name);
	
	// Tell cvui to update its internal structures regarding a particular window
	// then show it. Below we are using cvui::imshow(), which is cvui's version of
	// the existing cv::imshow(). They behave exactly the same, the only difference
	// is that cvui::imshow() will automatically call cvui::update(name) for you.
	cvui::imshow(WINDOW2_NAME, frame);
}



void traslation(cv::Mat source, cv::Mat &destination, int tx, int ty){

    int height_image =  source.rows;
    int width_image = source.cols * source.channels();
    int number_channels = source.channels();
    int x,y;
    destination.setTo(cv::Scalar(0));
    

    for (int height_index = 0; height_index < height_image; ++height_index)
    {
        uchar *base_image_array = source.ptr<uchar>(height_index);
        
        
        for (int width_index = 0; width_index < width_image; width_index += number_channels)
        {   
            x = width_index + tx*number_channels;
            y = height_index + ty;
            
            if (x < 0 or x > width_image or y < 0 or y > height_image)
                break;

            uchar *destination_array = destination.ptr<uchar>(y);

            for (int ch = 0; ch < number_channels; ch++)
            {
                *(destination_array + x + ch) = *(base_image_array + width_index + ch);
            }
            
            
        }
    }

    
}



void rotation(cv::Mat source, cv::Mat &destination, double grades){

    //Informacion de la imagen
    int number_channels = source.channels();
    int height_image = source.rows;
    int width_image = source.cols*number_channels;
    //Variables para la rotacion
    int xReference,yReference;
    int newX,newY,x,y;
    
    int new_height =  ( height_image*abs(COS(grades)) + width_image*abs(SIN(grades))); 
    int new_width =  ( height_image*abs(SIN(grades)) + width_image*abs(COS(grades)));
    
    destination = cv::Mat::zeros(new_height,new_width,source.type());
    
	xReference = new_height/2;
    yReference = new_width/2;

    int xoffset = xReference - height_image/2;
    int yoffset = yReference - width_image/2;
    
    
    for(int height_index=0; height_index < height_image; height_index++){
        
        uchar *ren = source.ptr< uchar > (height_index);

        for(int width_index = 0; width_index < width_image; width_index += number_channels){
            for(int ch = 0; ch < number_channels; ++ch ) {

                newX = height_index - xReference + xoffset;
                newY = width_index - yReference + yoffset;
                x =  xReference + ( newX*COS(grades) - newY*SIN(grades)); 
                y =  yReference + ( newX*SIN(grades) + newY*COS(grades));

                if(x>=0 && x < new_height && y>=0 && y < new_width){
                    uchar *renc = destination.ptr< uchar > (x);
                    *(renc + y + ch )  = *(ren + width_index + ch)*RGB[ch];
                }
            }
        }
    }

}


void colors( cv::Mat source, cv::Mat &destination)
{   
    int number_rows =  source.rows;
    int number_Columnes = source.cols * source.channels();
    int number_channels = source.channels();
   for (int height_index = 0; height_index < number_rows; ++height_index)
    {
        uchar *row_pixels_source = source.ptr<uchar>(height_index);
        uchar *row_pixels_destiny = destination.ptr<uchar>(height_index);
        for (int width_index = 0; width_index < number_Columnes; width_index += number_channels)
        {
            
            *(row_pixels_destiny + width_index + R) = *(row_pixels_source + width_index + R)*(level_red/100.0)*RGB[R];
            *(row_pixels_destiny + width_index + G) = *(row_pixels_source + width_index + G)*(level_green/100.0)*RGB[G];
            *(row_pixels_destiny + width_index + B) = *(row_pixels_source + width_index + B)*(level_blue/100.0)*RGB[B];
            
        }
    }
    
    
    
 
}
