#include "functions.h"
#include "cvui.h"
#include <math.h>
 int horizontal = 0;
 int vertical = 0;


double grades =0;
bool RGB[3] ={true, true, true};
double level[3] ={1,1,1};
bool not_ =false;
bool verbord_ = false;
bool horbord_ = false;
bool bin_operations[5] = {false, false, false, false, false};
double normal_value = 255.0;


void size_reducing(cv::Mat source, cv::Mat &destination, int size_reduction){
    
    int temp=2;
    for (int i = 0; i < size_reduction; i++)
        temp *= 2;

    int k,i2;
    int new_height = floor(source.rows / temp);
    int new_width = floor(source.cols / temp)*3;
    int auxiliar = floor(source.cols / temp);
    destination = cv::Mat::zeros(new_height,auxiliar,CV_8UC3);
    
    for(int height_index = 0, k = 0; height_index < new_height ; height_index++, k += temp){
      
      if(size_reducing == 0) 
        k=height_index;

      uchar * row_pixels_source = source.ptr <uchar>(k);
      uchar * row_pixels_destiny = destination.ptr <uchar>(height_index);
      for( int j = 0, i2 = 0; j < destination.cols*3; j += 3, i2 += temp*3){ 
        if (size_reducing == 0 ) i2 = j; 

        for(int ch = 0; ch < 3; ++ch ) {               
            *( row_pixels_destiny + j + ch ) = *(row_pixels_source + i2 + ch);
        
        }
      }
    }
   
}

void sub_operation(cv::Mat source_a, cv::Mat source_b, cv::Mat &destination)
{   
    int number_rows =  source_a.rows;
    int number_Columnes = source_a.cols * source_a.channels();
    int number_channels = source_a.channels();
    
    //cv::cvtColor(source, temp, CV_BGR2GRAY);
    for (int height_index = 0; height_index < number_rows; ++height_index)
    {
        
        uchar *row_pixels_destiny = destination.ptr<uchar>(height_index);
        uchar *row_pixels_a = source_a.ptr<uchar>(height_index);
        uchar *row_pixels_b = source_b.ptr<uchar>(height_index);

        for (int width_index = 0; width_index < number_Columnes; width_index += number_channels)
        {
            for(int ch = 0; ch < number_channels; ++ch ) {
            *(row_pixels_destiny + width_index + ch) = 
                *(row_pixels_a + width_index + ch) -
                *(row_pixels_b + width_index + ch);
            }
           
        }
    }
    
 
}

void sum_operation(cv::Mat source_a, cv::Mat source_b, cv::Mat &destination)
{   
    int number_rows =  source_a.rows;
    int number_Columnes = source_a.cols * source_a.channels();
    int number_channels = source_a.channels();
    
    //cv::cvtColor(source, temp, CV_BGR2GRAY);
    for (int height_index = 0; height_index < number_rows; ++height_index)
    {
        
        uchar *row_pixels_destiny = destination.ptr<uchar>(height_index);
        uchar *row_pixels_a = source_a.ptr<uchar>(height_index);
        uchar *row_pixels_b = source_b.ptr<uchar>(height_index);

        for (int width_index = 0; width_index < number_Columnes; width_index += number_channels)
        {
            for(int ch = 0; ch < number_channels; ++ch ) {
                *(row_pixels_destiny + width_index + ch) = 
                    (*(row_pixels_a + width_index + ch) +
                    *(row_pixels_b + width_index + ch) )*255/(normal_value);
            }
           
        }
    }
    
 
}



void binary_operations(const cv::String& name, cv::Mat image_a, cv::Mat image_b, bool grayscale) {
	// Create a frame for this window and fill it with a nice color
	cv::Mat frame = cv::Mat(400, 600, CV_8UC3);

    static cv::Mat temp_a;
    static cv::Mat temp_b;
    
    
    temp_a = image_a.clone();
    temp_b = image_a.clone();
    
    
    temp_a;
    temp_b.setTo(cv::Scalar(0));
    
	frame = cv::Scalar(49, 52, 49);
	bool vert_,horz_, rota_, or_, and_, xor_, flag = false, sub_, sum_, nor_;
    
	// Inform cvui that the components to be rendered from now one belong to
	// a window in particular.
	//
	// If you don't inform that, cvui will assume the components belong to
	// the default window (informed in cvui::init()). In that case, the
	// interactions with all other windows being used will not work.
	cvui::context(name);

	cvui::printf(frame, 20, 5, "Reduce size of image");
	cvui::printf(frame, 20, 75, "Move image vertically");
	vert_ = cvui::trackbar(frame, 20, 20, 220, &horizontal, 0, 5);
	horz_ = cvui::trackbar(frame, 20, 90, 220, &vertical, 0, 64);
    rota_ = cvui::trackbar(frame, 20, 150, 220, &grades, 0.0, 360.0);
    cvui::printf(frame, 300, 5, "Level of red");    cvui::trackbar(frame, 300, 20, 220, &level[2], 0.0, 1.0);
	cvui::printf(frame, 300, 75, "Level of green"); cvui::trackbar(frame, 300, 90, 220, &level[1], 0.0, 1.0);
    cvui::printf(frame, 300, 145, "Level of blue"); cvui::trackbar(frame, 300, 160, 220, &level[0], 0.0, 1.0);
    cvui::printf(frame, 20, 140, "Rotate image");

    cvui::checkbox(frame, 400, 240, "Red colors", &RGB[2]) ;
    cvui::checkbox(frame, 400, 260, "Green colors", &RGB[1]);
    cvui::checkbox(frame, 400, 280, "Blue colors", &RGB[0]);

    or_ = cvui::checkbox(frame, 250, 240, "Or operation", &bin_operations[0]);
    and_ = cvui::checkbox(frame, 250, 260, "And operation", &bin_operations[1]);
    xor_ = cvui::checkbox(frame, 250, 280, "Xor operation", &bin_operations[2]);
    sum_ = cvui::checkbox(frame, 250, 300, "Sum operation", &bin_operations[3]);
    sub_ = cvui::checkbox(frame, 250, 320, "Sub operation", &bin_operations[4]);
    
    cvui::printf(frame, 10, 300, "Normalization value"); 
    nor_ = cvui::trackbar(frame, 10, 340, 220, &normal_value, 0.0, 250.0);

    cvui::checkbox(frame, 400, 300, "Not operation", &not_);
    
    cvui::checkbox(frame, 400, 320, "Vertical border", &verbord_);
    cvui::checkbox(frame, 400, 340, "Horizontal border", &horbord_);
    
    

    colors(temp_a, temp_b);
    swap_mat(temp_a, temp_b);
    

    if(rota_){
        cv::cvtColor(image_a, temp_a, CV_BGR2GRAY);
		rotation(temp_a, temp_b, grades);
        cvui::imshow(WINDOW3_NAME, temp_b);
       
	}
    if(horz_ || vert_){

        //traslation(image_a, temp_b, horizontal, vertical);
        if(horizontal != 0)
            size_reducing(image_a,temp_b, horizontal);
        else{
            temp_b = image_a.clone();
        }
        cvui::imshow(WINDOW4_NAME, temp_b);
    }
		
		
	if(not_){
        not_operation(temp_a);
    }
    
    if(and_){
        and_operation(temp_a,image_b, temp_b);
        swap_mat(temp_a, temp_b);
        
        
    }
    if(or_){
        or_operation(temp_a,image_b, temp_b);
        swap_mat(temp_a, temp_b);
        
    }
    if(xor_){
        xor_operation(temp_a,image_b, temp_b);
        swap_mat(temp_a, temp_b);
    }


    if(horbord_ || verbord_ ){

        cv::cvtColor(image_a, temp_a, CV_BGR2GRAY);
        temp_b.setTo(cv::Scalar(0));
        if(horbord_)
        {
            horizontal_borders(temp_a,temp_b);
        }
        else{
            vertical_borders(temp_a,temp_b);
        }
        cvui::imshow(WINDOW5_NAME, temp_b);
        
    }

	
    if(sum_  || nor_){
        sum_operation(temp_a,image_b, temp_b);
        swap_mat(temp_a, temp_b);
    }

    if(sub_ || nor_){
        sub_operation(temp_a,image_b, temp_b);
        swap_mat(temp_a, temp_b);
    }

	//cv::hconcat(image_a,image_b,temp_b);
    //cv::hconcat(temp_a,temp_b, temp_a);

    cvui::update(name);
	// Tell cvui to update its internal structures regarding a particular window
	// then show it. Below we are using cvui::imshow(), which is cvui's version of
	// the existing cv::imshow(). They behave exactly the same, the only difference
	// is that cvui::imshow() will automatically call cvui::update(name) for you.
	cvui::imshow(WINDOW2_NAME, frame);
    cvui::imshow(WINDOW1_NAME, temp_a);
    
}



void traslation(cv::Mat source, cv::Mat &destination, int tx, int ty){

    int height_image =  source.rows;
    int width_image = source.cols * source.channels();
    int number_channels = source.channels();
    int x,y;
    
    destination = cv::Mat::zeros(height_image, width_image, source.type());
    

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

void swap_mat(cv::Mat &image_a, cv::Mat &image_b){
    cv::Mat temp;
    temp = image_a;
    image_a = image_b;
    image_b = temp;
}


void rotation(cv::Mat source, cv::Mat &destination, double grades){

    //Informacion de la imagen
    int number_channels = source.channels();
    int height_image = source.rows;
    int width_image = source.cols*number_channels;
    //Variables para la rotacion
    int xReference,yReference;
    int newX,newY,x,y;
    
    int new_height = ( height_image*abs(COS(grades)) + width_image*abs(SIN(grades))); 
    int new_width = ( height_image*abs(SIN(grades)) + width_image*abs(COS(grades)));
    
    destination = cv::Mat::zeros(new_height,new_width,source.type());
    
	xReference = new_height/2;
    yReference = new_width/2;

    int xoffset = xReference - height_image/2;
    int yoffset = yReference - width_image/2;
    
    
    for(int height_index=0; height_index < height_image; height_index++){
        
        uchar *ren = source.ptr< uchar > (height_index);

        for(int width_index = 0; width_index < width_image; width_index += number_channels){
            
            newX = height_index - xReference + xoffset;
            newY = width_index - yReference + yoffset;
            
            x =  xReference + ( newX*COS(grades) - newY*SIN(grades)); 
            y =  yReference + ( newX*SIN(grades) + newY*COS(grades));
            
            for(int ch = 0; ch < number_channels; ++ch ) {

                if(x >= 0 && x < new_height && y >= 0 && y < new_width){
                    uchar *renc = destination.ptr< uchar > (x);
                    *(renc + y + ch )  = *(ren + width_index + ch)*RGB[ch]*level[ch];

                    
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
            for(int ch = 0; ch < number_channels; ++ch ) {
                *(row_pixels_destiny + width_index + ch) = *(row_pixels_source + width_index + ch)*level[ch]*RGB[ch];
                
            }
                

        }
    }
    
 
}


void vertical_borders(cv::Mat source, cv::Mat &destination)
{   
    int number_rows =  source.rows;
    int number_Columnes = source.cols * source.channels();
    int number_channels = source.channels();
    
    //cv::cvtColor(source, temp, CV_BGR2GRAY);
    for (int height_index = 0; height_index < number_rows; ++height_index)
    {
        uchar *row_pixels_source = source.ptr<uchar>(height_index);
        uchar *row_pixels_destiny = destination.ptr<uchar>(height_index);
        for (int width_index = 1; width_index < number_Columnes; width_index += number_channels)
        {
            
            *(row_pixels_destiny + width_index ) = 
            abs(*(row_pixels_source + width_index - 1) -
                *(row_pixels_source + width_index ) );

            
        }
    }
    
 
}

void horizontal_borders(cv::Mat source, cv::Mat &destination)
{   
    int number_rows =  source.rows;
    int number_Columnes = source.cols * source.channels();
    int number_channels = source.channels();
    
    //cv::cvtColor(source, temp, CV_BGR2GRAY);
    for (int height_index = 1; height_index < number_rows; ++height_index)
    {
        
        uchar *row_pixels_destiny = destination.ptr<uchar>(height_index);
        uchar *row_pixels_a = source.ptr<uchar>(height_index);
        uchar *row_pixels_b = source.ptr<uchar>(height_index-1);
        for (int width_index = 0; width_index < number_Columnes; width_index += number_channels)
        {
            
            *(row_pixels_destiny + width_index ) = 
            abs(*(row_pixels_a + width_index ) -
                *(row_pixels_b + width_index ) );

            
        }
    }
    
 
}


void and_operation(cv::Mat source_a, cv::Mat source_b, cv::Mat &destination)
{   
    int number_rows =  source_a.rows;
    int number_Columnes = source_a.cols * source_a.channels();
    int number_channels = source_a.channels();
    
    //cv::cvtColor(source, temp, CV_BGR2GRAY);
    for (int height_index = 0; height_index < number_rows; ++height_index)
    {
        
        uchar *row_pixels_destiny = destination.ptr<uchar>(height_index);
        uchar *row_pixels_a = source_a.ptr<uchar>(height_index);
        uchar *row_pixels_b = source_b.ptr<uchar>(height_index);

        for (int width_index = 0; width_index < number_Columnes; width_index += number_channels)
        {
            for(int ch = 0; ch < number_channels; ++ch ) {
            *(row_pixels_destiny + width_index + ch) = 
                *(row_pixels_a + width_index + ch) &
                *(row_pixels_b + width_index + ch);
            }
           
        }
    }
    
 
}

void not_operation(cv::Mat &source_a)
{   
    int number_rows =  source_a.rows;
    int number_Columnes = source_a.cols * source_a.channels();
    int number_channels = source_a.channels();
    
    //cv::cvtColor(source, temp, CV_BGR2GRAY);
    for (int height_index = 0; height_index < number_rows; ++height_index)
    {
        
        
        uchar *row_pixels_a = source_a.ptr<uchar>(height_index);

        for (int width_index = 0; width_index < number_Columnes; width_index += number_channels)
        {
            
            for(int ch = 0; ch < number_channels; ++ch ) {
                *(row_pixels_a + width_index +ch) = ~*(row_pixels_a + width_index + ch);
            }

           
        }
    }
    
 
}

void or_operation(cv::Mat source_a, cv::Mat source_b, cv::Mat &destination)
{   
    int number_rows =  source_a.rows;
    int number_Columnes = source_a.cols * source_a.channels();
    int number_channels = source_a.channels();
    
    //cv::cvtColor(source, temp, CV_BGR2GRAY);
    for (int height_index = 0; height_index < number_rows; ++height_index)
    {
        
        uchar *row_pixels_destiny = destination.ptr<uchar>(height_index);
        uchar *row_pixels_a = source_a.ptr<uchar>(height_index);
        uchar *row_pixels_b = source_b.ptr<uchar>(height_index);

        for (int width_index = 0; width_index < number_Columnes; width_index += number_channels)
        {
             for(int ch = 0; ch < number_channels; ++ch ) {
                *(row_pixels_destiny + width_index + ch) = 
                *(row_pixels_a + width_index  + ch ) |
                *(row_pixels_b + width_index  + ch);
             }
            
        }
    }
    
 
}

void xor_operation(cv::Mat source_a, cv::Mat source_b, cv::Mat &destination)
{   
    int number_rows =  source_a.rows;
    int number_Columnes = source_a.cols * source_a.channels();
    int number_channels = source_a.channels();
    
    //cv::cvtColor(source, temp, CV_BGR2GRAY);
    for (int height_index = 0; height_index < number_rows; ++height_index)
    {
        
        uchar *row_pixels_destiny = destination.ptr<uchar>(height_index);
        uchar *row_pixels_a = source_a.ptr<uchar>(height_index);
        uchar *row_pixels_b = source_b.ptr<uchar>(height_index);

        for (int width_index = 0; width_index < number_Columnes; width_index += number_channels)
        {
             for(int ch = 0; ch < number_channels; ++ch ) {
            
                *(row_pixels_destiny + width_index + ch) = 
                *(row_pixels_a + width_index + ch) ^
                *(row_pixels_b + width_index  + ch);
             }
           
        }
    }
    
 
}
