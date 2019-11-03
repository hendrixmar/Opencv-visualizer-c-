#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define SIN(x) sin(x * 3.141592653589/180) 
#define COS(x) cos(x * 3.141592653589/180)

using namespace cv;
using namespace std;

Mat image;
Mat imR;
Mat imWB;

/*
* Funcion para rotar una imagen, esta imagen va en blanco y negro
*/

void rota(int v, void *Datos){
    //Informacion de la imagen
    int nc = imWB.channels();
    int rw = imWB.rows;
    int cl = imWB.cols*nc;
    //Variables para la rotacion
    int xReference,yReference,i,j,k;
    int newX,newY,x,y;
    
    int newR =  ( rw*abs(COS(v)) + cl*abs(SIN(v))); 
    int newC =  ( rw*abs(SIN(v)) + cl*abs(COS(v)));
    
    Mat res = Mat::zeros(newR,newC,imWB.type());
    
	xReference = newR/2;
    yReference = newC/2;

    int xoffset = xReference - rw/2;
    int yoffset = yReference - cl/2;
    
    //Calculo de la rotacion de la imagen
    for(j=0; j < rw ;j++){
        uchar *ren = imWB.ptr< uchar > (j);
        for (i = 0; i < cl; i+=nc){
            for(k=0; k < nc; ++k){
                newX = j - xReference + xoffset;
                newY = i - yReference + yoffset;
                x =  xReference + ( newX*COS(v) - newY*SIN(v)); 
                y =  yReference + ( newX*SIN(v) + newY*COS(v));
                if(x>=0 && x < newR && y>=0 && y < newC){
                    uchar *renc = res.ptr< uchar > (x);
                    *(renc + y + k) = *(ren + i + k);
                }
            }
        }
    }

    namedWindow("Rotacion", 1 );
    imshow("Rotacion", res);
}
//Funcion principal
int main(int argc,char** argv){
	if( argc != 2 ){printf("usage: DisplayImage.out <Image_Path>\n");return-1;}
	image = imread( argv[1], 1 );
	cvtColor(image, imWB, cv::COLOR_RGB2GRAY);
	if( !image.data ){printf("No image data\n");return-1;}
	//Rotacion
	int angulo=0;
	namedWindow("Rotacion", 1);
	imshow("Rotacion", imWB);
	createTrackbar("Angulo", "Rotacion", &angulo, 360 , rota, &angulo);
    
	//Sale del programa al presionar ESC
	while(1){
		char c = waitKey();
		if( c == 27)
			break;
	}
	return 0;
}