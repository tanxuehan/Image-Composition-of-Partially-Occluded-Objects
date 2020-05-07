#include "QtPastePic.h"
#include <qbuffer.h>
using namespace cv;
using namespace std;

QtPastePic::QtPastePic(QWidget *parent)
	:
	/*
	Initialization parameters

	Attributes:
	Paint(Qrect): Painting area.
	Alloffset(Qpoint): Total offset.
	ratio(QPoint): Image scaling. Default:1.0.
	pixW(int):Source image width. Default:985.
	pixH(int):Source image height. Default:740.

	*/

	QMainWindow(parent),
	Paint(20, 62, 550, 380),	
	Alloffset(0, 0)

{
	ratio = 1.0;          
	action = QtPastePic::None;
	pixW = 985;        
	pixH = 740;

	ui.setupUi(this);
}



QtPastePic::~QtPastePic()
{

}


void QtPastePic::on_target_pic_load_button_clicked()
{
	/*
	Load target image, and display the target image on the interface.
    
	Attributes:
    targetW(int):Target image width.
    targetH(int):Target image height.
	target_pic(Mat): Target image.
    target_img(QImage): Target image to show in ui.
    labelTargetImg(QImage):Target image in 'target pic' rect.
    target_pic_label(QLabel):Show target image in 'target pic' rect.
    target_pix（QPixmap):Target image in Qt paint area.
	*/

	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		tr("选择图像"),
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty())
	{
		return;
	}
	else
	{

		target_alphas.clear();

		string str = filename.toStdString();  
		target_pic = imread(str);
		targetH = target_pic.rows;
		targetW = target_pic.cols;
		cvtColor(target_pic, target_pic, CV_BGR2RGB);
		target_img = QImage((const unsigned char*)(target_pic.data), target_pic.cols, target_pic.rows, QImage::Format_RGB888);

		target_pic_label = new QLabel();
		QImage labelTargetImg = target_img.scaled(ui.target_pic_show->width() * 0.9, ui.target_pic_show->height() * 0.9);
		target_pic_label->setPixmap(QPixmap::fromImage(labelTargetImg));
		ui.target_pic_show->setWidget(target_pic_label);
        
		QPixmap temp_pix = QPixmap::fromImage(target_img);
		target_pix = &temp_pix;

	}

}

void QtPastePic::on_source_pic_load_button_clicked()
{
    /*
    Load source image, and display the source image on the interface.

    Attributes:
    source_pic(Mat): Source image.
    source_img(QImage): Source image to show in ui.
    labelSourceImg(QImage):Source image in 'source pic' rect.
    source_pic_label(QLabel):Show source image in 'source pic' rect.
    */

	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		tr("选择图像"),
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty())
	{
		return;
	}
	else
	{

		QImage loadedImage;
		if (!loadedImage.load(filename))
			return;
		pixW = loadedImage.width();
		pixH = loadedImage.height();
      
		string str = filename.toStdString(); 
		source_pic = imread(str);
		cvtColor(source_pic, source_pic, CV_BGR2RGB);
		source_img = QImage((const unsigned char*)(source_pic.data), source_pic.cols, source_pic.rows, QImage::Format_RGB888);
        
		source_pic_label = new QLabel();      
		QImage labelSourceImg = source_img.scaled(ui.source_pic_show->width() * 0.9, ui.source_pic_show->height() * 0.9);
		source_pic_label->setPixmap(QPixmap::fromImage(labelSourceImg));

		ui.source_pic_show->setWidget(source_pic_label);
        
	}
}

void QtPastePic::on_source_mask_load_button_clicked()
{
    /*
    Load source image mask, and display the source mask on the interface.

    Attributes:
    source_alpha_pic(Mat): Source image mask.
    source_alpha_img(QImage): Source image mask to show in ui.
    labelSourceAlphaImg(QImage):Source image mask in 'source image mask' rect.
    source_alpha_label(QLabel):Show source mask in 'source image mask' rect.
    */

	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		tr("选择图像"),
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty())
	{
		return;
	}
	else
	{

		string str = filename.toStdString(); 
		source_alpha_pic = imread(str);
		cvtColor(source_alpha_pic, source_alpha_pic, CV_BGR2RGB);
		source_alpha_img = QImage((const unsigned char*)(source_alpha_pic.data), source_alpha_pic.cols, source_alpha_pic.rows, QImage::Format_RGB888);
        
		source_alpha_label = new QLabel();
		QImage labelSourceAlphaImg = source_alpha_img.scaled(ui.source_mask_show->width()*0.9, ui.source_mask_show->height()*0.9);
		source_alpha_label->setPixmap(QPixmap::fromImage(labelSourceAlphaImg));
        
		ui.source_mask_show->setWidget(source_alpha_label);
        
		update();

	}

}


void QtPastePic::on_target_mask_load_button_clicked()
{
    /*
    Load target image mask, and display the target image mask on the interface.

    Attributes:
    target_alpha_pic(Mat): Target image mask.
    target_alphas(vector<Mat>): Save all target image masks.
    target_alpha_img(QImage): Target image mask to show in ui.
    labelTargetAlphaImg(QImage):Target image mask in 'target image mask' rect.
    target_alpha_label(QLabel):Show target mask in 'target image mask' rect.
    */

	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		tr("选择图像"),
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty())
	{
		return;
	}
	else
	{

		string str = filename.toStdString();  // 将filename转变为string类型；
		target_alpha_pic = imread(str);
        
		cvtColor(target_alpha_pic, target_alpha_pic, CV_BGR2RGB);
		target_alpha_img = QImage((const unsigned char*)(target_alpha_pic.data), target_alpha_pic.cols, target_alpha_pic.rows, QImage::Format_RGB888);

		target_alphas.push_back(target_alpha_pic);
        
		target_alpha_label = new QLabel();
		QImage labelTargetAlphaImg = target_alpha_img.scaled(ui.target_mask_show->width()*0.9, ui.target_mask_show->height()*0.9);
		target_alpha_label->setPixmap(QPixmap::fromImage(labelTargetAlphaImg));

		ui.target_mask_show->setWidget(target_alpha_label);


	}

}

void QtPastePic::on_target_depth_load_button_clicked()
{
    /*
    Load depth map of target image, and display the depth map on the interface.

    Attributes:
    depth_pic(Mat):  Depth map of target image.
    depth_img(QImage): Depth map of target image to show in ui.
    labelDepthImg(QImage):Depth map of target image in 'depth map' rect.
    depth_label(QLabel):Show depth label in 'depth map' rect.
    */

	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		tr("Img"),
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty())
	{
		return;
	}
	else
	{

		string str = filename.toStdString();
		depth_pic = imread(str);
		cvtColor(depth_pic, depth_pic, CV_BGR2RGB);
		depth_img = QImage((const unsigned char*)(depth_pic.data), depth_pic.cols, depth_pic.rows, QImage::Format_RGB888);
        
		depth_label = new QLabel();
		QImage labelDepthImg = depth_img.scaled(ui.target_depth_show->width()*0.9, ui.target_depth_show->height()*0.9);
		depth_label->setPixmap(QPixmap::fromImage(labelDepthImg));

		ui.target_depth_show->setWidget(depth_label);

	}

}

