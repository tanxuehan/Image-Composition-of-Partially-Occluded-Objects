#include "widget.h"
#include "PastePic.h"




bool QtPastePic::event(QEvent * event)
{
    /*
    Mouse click event.
    Move the picture with the mouse
    */
	static bool press = false;
	static QPoint PreDot;

	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);      
		if (mouse->button() == Qt::LeftButton &&Paint.contains(mouse->pos()))
		{
            //Determine whether the mouse is released with the left button, and it was in the painting area before.
			press = true;
			this->setCursor(Qt::OpenHandCursor);
			PreDot = mouse->pos();
		}

	}
	else if (event->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);
    
		if (mouse->button() == Qt::LeftButton && press)
		{
            //Determine whether the mouse is released with the left button, and it was in the painting area before.
			this->setCursor((Qt::ArrowCursor));
			press = false;
		}
	}

	if (event->type() == QEvent::MouseMove)              
	{
        //Move picture
		if (press)
		{
			QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

			offset.setX(mouse->x() - PreDot.x());
			offset.setY(mouse->y() - PreDot.y());
			PreDot = mouse->pos();
			action = QtPastePic::Move;
			this->update();
		}
	}
	return QWidget::event(event);
}

void QtPastePic::wheelEvent(QWheelEvent* event) 
{
    /*
    Mouse wheel event.
    Zoom the picture by scrolling the mouse wheel.
    */
	if (event->delta()>0) 
    {      
        //Slide the mouse wheel down to zoom out the picture
		action = QtPastePic::Shrink;
		this->update();
        
	}
	else 
    {     
        //Slide the mouse wheel up to zoom in the picture
        action = QtPastePic::Amplification;
		this->update();
	}

	event->accept();
}



void QtPastePic::paintEvent(QPaintEvent *event)
{

	QPainter painter(this);

	int NowW = ratio * pixW;
	int NowH = ratio * pixH;
    
	QPixmap target_pix_temp;
	target_pix_temp = QPixmap::fromImage(target_img);
	target_pix = &target_pix_temp;


	QPixmap pix_temp;
	pix_temp= QPixmap::fromImage(mask_img);
	pix= &pix_temp;
   
	if (action == QtPastePic::Amplification)  
	{
        //zoom out the picture
		ratio -= 0.1*ratio;
		if (ratio<0.018)
			ratio = 0.01;
	}
	else  if (action == QtPastePic::Shrink)  
	{
        //zoom in the picture
		ratio += 0.1*ratio;
		if (ratio>4.5)
			ratio = 5.000;
	}
	if (action == QtPastePic::Amplification || action == QtPastePic::Shrink)  
	{
        //Update image
		NowW = ratio * pixW;
		NowH = ratio * pixH;
        
		QMatrix matrix;
		matrix.scale(ratio, ratio);

		source_img = source_img.scaled(NowW, NowH);

		QMatrix mask_matrix;
		mask_matrix.scale(ratio, ratio);
		mask_img = mask_img.scaled(NowW, NowH);

		QPixmap temp_pix = QPixmap::fromImage(mask_img);
		pix = &temp_pix;
		*pix = pix->scaled(NowW, NowH, Qt::KeepAspectRatio);
      
		action = QtPastePic::None;

	}

	if (action == QtPastePic::Move) 
	{
        //move image
		QPixmap pix_temp;
		pix_temp = QPixmap::fromImage(source_img);
		pix = &pix_temp;


		int offsetx = Alloffset.x() + offset.x();
		Alloffset.setX(offsetx);

		int offsety = Alloffset.y() + offset.y();
		Alloffset.setY(offsety);
		action = QtPastePic::None;
	}

	if (abs(Alloffset.x()) >= (Paint.width() / 2 + NowW / 2 - 20))  
	{
        //Limit X offset value
		if (Alloffset.x()>0)
			Alloffset.setX(Paint.width() / 2 + NowW / 2 - 20);
		else
			Alloffset.setX(-Paint.width() / 2 + -NowW / 2 + 20);
	}
	if (abs(Alloffset.y()) >= (Paint.height() / 2 + NowH / 2 - 62))   
	{
        //Limit Y offset value
		if (Alloffset.y()>0)
			Alloffset.setY(Paint.height() / 2 + NowH / 2 - 62);
		else
			Alloffset.setY(-Paint.height() / 2 + -NowH / 2 + 62);

	}

	int x = Paint.width() / 2 + Alloffset.x() - NowW / 2;
	if (x<0)
		x = 0;

	int y = Paint.height() / 2 + Alloffset.y() - NowH / 2;
	if (y<0)
		y = 0;

	int  sx = NowW / 2 - Paint.width() / 2 - Alloffset.x();
	if (sx<0)
		sx = 0;

	int  sy = NowH / 2 - Paint.height() / 2 - Alloffset.y();
	if (sy<0)
		sy = 0;

	int w = (NowW - sx)>Paint.width() ? Paint.width() : (NowW - sx);
	if (w>(Paint.width() - x))
		w = Paint.width() - x;

	int h = (NowH - sy)>Paint.height() ? Paint.height() : (NowH - sy);
	if (h>(Paint.height() - y))
		h = Paint.height() - y;

	painter.drawRect(Paint.x() - 1, Paint.y() - 1, Paint.width() + 1, Paint.height() + 1); //»­¿ò
	painter.drawPixmap(-targetW / 2 + Paint.width() / 2 +Paint.x(), Paint.height() / 2 - targetH / 2+Paint.y(), *target_pix, 0, 0,-1,-1);  //»æ»­Í¼ÐÎ
	painter.drawPixmap(x + Paint.x(), y + Paint.y(), *pix, sx, sy,-1,-1);

	
}

void  QtPastePic::on_little_clicked()
{
	action = QtPastePic::Amplification;
	this->update();
}

void  QtPastePic::on_big_clicked()
{
	action = QtPastePic::Shrink;
	this->update();
}
void QtPastePic::on_up_clicked()
{
	action = QtPastePic::Move;
	offset.setX(0);
	offset.setY(-20);

	this->update();
}
void QtPastePic::on_down_clicked()
{
	action = QtPastePic::Move;
	offset.setX(0);
	offset.setY(20);
	this->update();
}
void QtPastePic::on_left_clicked()
{
	action = QtPastePic::Move;
	offset.setX(-20);
	offset.setY(0);

	this->update();
}
void QtPastePic::on_right_clicked()
{
	action = QtPastePic::Move;
	offset.setX(20);
	offset.setY(0);

	this->update();
}

void QtPastePic::on_mask_clicked()
{
	PastePic pastepic;
	Mat source;
	Mat target;

	cvtColor(source_pic, source, CV_RGB2BGR);
	cvtColor(source_alpha_pic, target, CV_RGB2BGR);
	source_mask_pic = pastepic.Cutout(source, target);
	cvtColor(source_mask_pic, source_mask_pic, CV_BGRA2RGBA);

	mask_img = QImage((const unsigned char*)(source_mask_pic.data), source_mask_pic.cols, source_mask_pic.rows, QImage::Format_RGBA8888);
}

void QtPastePic::on_output_clicked()
{
	PastePic pastepic;

	Mat source;
	Mat source_alpha;
	Mat target;
	vector<Mat> target_alphas_bgr;
	Mat depth;

	cvtColor(source_pic, source, CV_RGB2BGR);
	cvtColor(source_alpha_pic, source_alpha, CV_RGB2GRAY);
	cvtColor(target_pic, target, CV_RGB2BGR);
	cvtColor(depth_pic, depth, CV_RGB2GRAY);
	int i = 0;
	for (vector<Mat>::iterator target_alpha_iter = target_alphas.begin(); target_alpha_iter != target_alphas.end(); target_alpha_iter++)
	{
		Mat target_alpha_bgr;
		cvtColor(*target_alpha_iter, target_alpha_bgr, CV_RGB2GRAY);
		target_alphas_bgr.push_back(target_alpha_bgr);

	}

	Mat normal_alpha = Mat::zeros(target.rows, target.cols, CV_8UC1);
	Mat normal_output_pic = pastepic.SourceLocMaskPasteImage(source, target, source_alpha, target_alphas_bgr, normal_alpha, "C:/Users/txh/Desktop/test_t8.png",  Alloffset.y()+int((targetH-ratio*pixH)/2), Alloffset.x() + int((targetW - ratio * pixW) / 2), ratio);
	normal_output_pic=normal_output_pic*255.0;
	imwrite("C:/Users/txh/Desktop/test_normal.png", normal_output_pic);

	output_pic = pastepic.SourceLocMaskPasteImage(source, target, source_alpha, target_alphas_bgr, depth, "C:/Users/txh/Desktop/test_t8.png",  Alloffset.y()+int((targetH-ratio*pixH)/2), Alloffset.x() + int((targetW - ratio * pixW) / 2), ratio);

	output_pic = output_pic * 255.0;

	imwrite("C:/Users/txh/Desktop/test_f.png", output_pic);
	output_pic = imread("C:/Users/txh/Desktop/test_f.png");

	cvtColor(output_pic, output_pic, CV_BGR2RGB);
	output_img = QImage((const unsigned char*)(output_pic.data), output_pic.cols, output_pic.rows, QImage::Format_RGB888);
	

	//Show in the box below
	output_label = new QLabel();
	output_label->setPixmap(QPixmap::fromImage(output_img));
	output_label->resize(QSize(output_img.width(), output_img.height()));
	ui.output_show->setWidget(output_label);

}