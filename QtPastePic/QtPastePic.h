
#include <QtWidgets/QMainWindow>
#include "ui_QtPastePic.h"
#include<QGraphicsScene>  
#include<QGraphicsView>                 
#include<opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>  
#include <qfiledialog.h>             
#include <qlabel.h>            
#include <cstdio>
#include <opencv2\opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;




class QtPastePic : public QMainWindow
{
	Q_OBJECT

public:
	QtPastePic(QWidget *parent = Q_NULLPTR);
    //Initialization parameters

	~QtPastePic();
    
private slots:
	void on_source_pic_load_button_clicked();
    //Load source image, and display the source image on the interface.
	void on_target_pic_load_button_clicked();
    //Load target image, and display the target image on the interface.
	void on_source_mask_load_button_clicked();
    //Load source image mask, and display the source mask on the interface.
	void on_target_mask_load_button_clicked();
    //Load target image mask, and display the target image mask on the interface.
	void on_target_depth_load_button_clicked();
    //Load depth map of target image, and display the depth map on the interface.

public:
	Mat target_pic;
	Mat source_pic;
	vector<Mat> target_alphas;
	Mat depth_pic;
	Mat source_alpha_pic;
	Mat target_alpha_pic;
	Mat source_mask_pic;
	Mat output_pic;


private:
	Ui::QtPastePicClass ui;

	
	QLabel *source_pic_label;
	QLabel *target_pic_label;
	QLabel *source_alpha_label;
	QLabel *target_alpha_label;
	QLabel *depth_label;
	QLabel *output_label;


	//void makeBgTransparent();

private:

	QImage target_img;
	QImage source_img;
	QImage source_alpha_img;
	QImage target_alpha_img;
	QImage depth_img;
	QImage output_img;
	QImage mask_img;

	QLabel *source_imageLabel;
	QScrollArea *source_scrollArea;

	QPixmap  *pix;
	QPixmap  *target_pix;

	int action;          //Action (zoom in, zoom out, move ...)
	int pixW;            //Source image width.
	int pixH;            //Source image height.
	int targetW;            //Target image width.
	int targetH;            //Target image height.

	QRect Paint;         //Painting area.

	float ratio;                //Image scaling.
	QPoint offset;              //Image offset value moved once
	QPoint Alloffset;           //Total offset.
	QLabel label;




	QPushButton  BigButton;
	QPushButton  LittleButton;
	QPushButton  LiftButton;
	QPushButton  RightButton;
	QPushButton  UpButton;
	QPushButton  DownButton;
	QPushButton  maskButton;
	QPushButton  outputButton;


	void AddComboItem(QComboBox* cmbo);
	bool event(QEvent * event);             //Mouse click event.
	void wheelEvent(QWheelEvent* e);     //Mouse wheel event.

private slots:
	void    on_little_clicked();
	void    on_big_clicked();
	void    on_up_clicked();
	void    on_down_clicked();
	void    on_left_clicked();
	void    on_right_clicked();
	void    on_mask_clicked();
	void    on_output_clicked();



	void paintEvent(QPaintEvent *event);
public:

	enum  Type {
		None = 0,
		Amplification,
		Shrink,
		Lift,
		Right,
		Up,
		Down,
		Move
	};


};
