
#include "PastePic.h"


bool boundaryJudge(Mat pic, int x, int y, int d) {

    /*
    Ablation Study: Find object boundaries in semantic segmentation results.
    When the kernel(size: d*d) has foreground (blue) and background (red) pixels, the pixel point is a point on the boundary.

    Args:
    d(int): the radius determines if the pixel is on the boundary.
    pic(Mat):the result image of AccurateSelectionEG2013. Background: blue. Foreground: red.
    x(int): row coordinates of pixels.
    y(int): column coordinates of pixels.

    Returns:
    (bool): Whether the pixel is a boundary.
    */

	bool blue = false;
	bool red = false;
	if (x < d || y < d || x >= pic.rows - d || y >= pic.cols - d)
	{
		return false;
	}
	for (int i = -d; i<d + 1; i++)
	{
		for (int j = -d; j<d + 1; j++)
		{
			if (int(pic.at<Vec3b>(x + i, y + j)[0]) == 0 && int(pic.at<Vec3b>(x + i, y + j)[1]) == 0 && int(pic.at<Vec3b>(x + i, y + j)[2]) == 255)
			{
				red = true;
			}
			if (int(pic.at<Vec3b>(x + i, y + j)[0]) == 255 && int(pic.at<Vec3b>(x + i, y + j)[1]) == 0 && int(pic.at<Vec3b>(x + i, y + j)[2]) == 0)
			{
				blue = true;
			}
		}
	}

	return (red == true && blue == true);	//accurate
}


double BiFilter(Mat source_pic, Mat alpha_pic, int x, int y, int d, float sigma_color, float sigma_space) {
    /*
    Ablation Study: Bilateral filtering for source_pic in pixel(x,y).

    Args:
    source_pic(Mat): Source image.
    alpha_pic(Mat):Alpha matte for target image.
    x(int): row coordinates of pixels.
    y(int): column coordinates of pixels.
    d(int): Kernel size of bilateral filtering. kernel size is regained from radius.
    sigma_color(float): range weight parameters.
    sigma_spacefloat): space weight parameters.

    Returns:
    final_alpha(float):alpha value in pixel(x,y) for input image after bilateral filtering.
    */

    int radius;
    float gauss_color_coeff = -0.5 / (sigma_color*sigma_color);
    float gauss_space_coeff = -0.5 / (sigma_space*sigma_space);
    alpha_pic.convertTo(alpha_pic, CV_32FC1);

    if (d <= 0) 
        radius = cvRound(sigma_space*1.5); 
    else 
        radius = d / 2;
    radius = MAX(radius, 1); 
    d = radius * 2 + 1; 
    vector<float> color_weight(d*d);
    vector<float> space_weight(d*d);
    vector<float> bi_weight(d*d);
    vector<float> alpha(d*d);
    vector<float> molecule(d*d);
    float all_weight = 0, all_molecule = 0;
    int i = -radius; int maxk = 0;
    for (; i <= radius; i++)
    {
        for (int j = -radius; j <= radius; j++)
        {
            float color_diff = 0;
            float r = std::sqrt((float)i*i + (float)j*j);       
            if (r > radius || i + x<0 || i + x >= alpha_pic.rows || j + y<0 || j + y >= alpha_pic.cols) 
                continue;
            space_weight[maxk] = (float)std::exp(r*r*gauss_space_coeff);

            for (int c = 0; c<3; c++)
            {
                color_diff += float(source_pic.at<Vec3f>(x + i, y + j)[c] - source_pic.Mat::at<Vec3f>(x, y)[c]);
            }
            color_weight[maxk] = (float)std::exp(color_diff*color_diff*gauss_color_coeff);
            bi_weight[maxk] = space_weight[maxk] * color_weight[maxk];
            alpha[maxk] = float(alpha_pic.at<float>(x + i, y + j));
            molecule[maxk] = alpha[maxk] * bi_weight[maxk];
            all_molecule += molecule[maxk];
            all_weight += bi_weight[maxk];
            maxk++;
        }
    }
    float final_alpha = all_molecule / all_weight;
    return final_alpha;
}


void BoundaryBiFilter(Mat ac_pic, Mat alpha_pic, Mat source_pic, int r_boundary, int d_filter, char * target_path)
{
    /*
    Ablation Study: Bilateral filtering for the boundary of source_pic.

    Args:
    ac_pic(Mat):the Result image of AccurateSelectionEG2013. Background: blue. Foreground: red.
    alpha_pic(Mat): Alpha matte for input image.
    source_pic(Mat): Input image.
    r_boundary(int): The radius determines if the pixel is on the boundary.
    d_filter(int): Kernel size of bilateral filtering. kernel size is regained from radius.
    target_path(char*): The storage path of the result image.

    Returns:
    None.
    */

    Mat target_alpha_pic;
    source_pic.copyTo(target_alpha_pic);
    for (int x = r_boundary; x<ac_pic.rows - r_boundary; x++)
    {
        for (int y = r_boundary; y<ac_pic.cols - r_boundary; y++)
        {
            if (boundaryJudge(ac_pic, x, y, r_boundary))
            {
                if (x - (d_filter + 1) / 2>0 && x - (d_filter + 1) / 2<alpha_pic.rows && y - (d_filter + 1) / 2>0 && y - (d_filter + 1) / 2<alpha_pic.cols)
                {
                    target_alpha_pic.at<float>(x, y) = BiFilter(source_pic, alpha_pic, x, y, d_filter, 70, 70);
                }
            }
        }
    }
    imshow("target_alpha_pic", target_alpha_pic / 255.0);
    imwrite(target_path, target_alpha_pic);
}


Mat PastePic::PasteImage(Mat&source_pic, Mat&target_pic, Mat&source_alpha_pic, Mat&target_alpha_pic, int ox, int oy) {
    /*
    Composite the image according to the matte of the target image and the source image

    Args:
    source_pic(Mat&): Source image.
    target_pic(Mat&): Target image.
    target_alpha_pic(Mat):Alpha matte for target image.
    source_alpha_pic(Mat): Alpha matte for input image.
    source_pic(Mat): Input image.
    ox(int): row coordinates of pixels.
    oy(int): column coordinates of pixels.

    Returns:
    composit(Mat):composition result.
    */
	source_pic.convertTo(source_pic, CV_32F, 1.0 / 255.0);
	target_pic.convertTo(target_pic, CV_32F, 1.0 / 255.0);
	source_alpha_pic.convertTo(source_alpha_pic, CV_32FC1, 1.0 / 255.0);
	target_alpha_pic.convertTo(target_alpha_pic, CV_32FC1, 1.0 / 255.0);
	Mat composite, source_temp;
	target_pic.copyTo(composite);
	source_pic.copyTo(source_temp);
	for (int j = 0; j<source_alpha_pic.rows; j++)
	{
		for (int i = 0; i<source_alpha_pic.cols; i++)
		{
			if (j + ox<0 || j + ox >= target_pic.rows || i + oy<0 || i + oy >= target_pic.cols)
			{
				continue;
			}

			float target_alpha = target_alpha_pic.at<float>(j + ox, i + oy);
			float source_alpha = source_alpha_pic.at<float>(j, i);
			source_temp.at<Vec3f>(j, i) = source_alpha * source_pic.at<Vec3f>(j, i) + (1 - source_alpha)*target_pic.at<Vec3f>(ox + j, oy + i);
			composite.at<Vec3f>(ox + j, oy + i) = target_alpha * target_pic.at<Vec3f>(ox + j, oy + i) + (1 - target_alpha)*source_temp.at<Vec3f>(j, i);

		}
	}
	return composite;
}



void acAlphaPic(Mat ac_pic, char *path) {
    /*
    Ablation Study: Modify the color of the result image of AccurateSelectionEG2013

    Args:
    ac_pi(Mat):the result image of AccurateSelectionEG2013. Background: blue. Foreground: red.
    ac_alpha_pic(Mat):Color modified result image. Background: black. Foreground: white.

    Returns:
    None.
    */

	ac_pic.convertTo(ac_pic, CV_8UC3);
	Mat ac_alpha_pic(ac_pic.rows, ac_pic.cols, CV_8UC1, Scalar(0, 0, 0));
	for (int i = 0; i<ac_pic.rows; i++)
	{
		for (int j = 0; j<ac_pic.cols; j++)
		{
			//blue
			if (int(ac_pic.at<Vec3b>(i, j)[0]) == 255 && int(ac_pic.at<Vec3b>(i, j)[1]) == 0 && int(ac_pic.at<Vec3b>(i, j)[2]) == 0)
			{
				ac_alpha_pic.at<uchar>(i, j) = 255;
			}
			//red
			else
			{
				ac_alpha_pic.at<uchar>(i, j) = 0;
			}
		}
	}
	imshow("ac_alpha_pic", ac_alpha_pic);
	imwrite(path, ac_alpha_pic);
}


void Denoising(Mat pic, int max_r, char *save_path)
{
    /*
    Ablation Study: Blur the boundary of the result image of AccurateSelectionEG2013.

    Args:
    pic(Mat):the result image of AccurateSelectionEG2013. Background: blue. Foreground: red.
    max_r(int):Maximum range of radius used to find the boundary.

    Returns:
    None.

    */
	Mat unnoise_pic;
	pic.copyTo(unnoise_pic);
	int pic_rows = pic.rows;
	int pic_cols = pic.cols;
	for (int i = max_r; i<pic_rows - max_r; i++)
	{
		for (int j = max_r; j<pic_cols - max_r; j++)
		{
			for (int r = max_r; r>0; r--)
			{
				bool all_red = true;

				for (int x = -r; x <= r; x++)
				{
					int y1 = sqrt(r*r - x * x);
					int y2 = -sqrt(r*r - x * x);
					if (pic.at<Vec3b>(i + x, j + y1)[0] == 255 || pic.at<Vec3b>(i + x, j + y2)[0] == 255)
					{
						all_red = false;
						break;
					}
				}

				if (all_red)
				{
					for (int x = -r; x <= r; x++)
					{
						for (int y = -r; y <= r; y++)
						{
							if (x*x + y * y<r*r)
							{
								unnoise_pic.at<Vec3b>(i + x, j + y)[0] = uchar(0);
								unnoise_pic.at<Vec3b>(i + x, j + y)[1] = uchar(0);
								unnoise_pic.at<Vec3b>(i + x, j + y)[2] = uchar(255);
							}
						}
					}
					break;
				}
			}
		}
	}
	imshow("pic", unnoise_pic);
	imwrite(save_path, unnoise_pic);
}

double PastePic::ObjDepth(Mat obj_mask, Mat depth_pic, int col, int row) {
    /*
    Ablation Study: Calculate the depth value of the content of interest in the source image 
        according to the size of the area where the object is located.
    */

	obj_mask.convertTo(obj_mask, CV_8UC1);
	depth_pic.convertTo(depth_pic, CV_8UC1);
	int rows_len = obj_mask.rows;
	int cols_len = obj_mask.cols;
	int depth_pic_rows_len = depth_pic.rows;
	int depth_pic_cols_len = depth_pic.cols;
	int N = 0;
	int depth = 0;
	for (int i = 0; i<rows_len; i++)
	{
		for (int j = 0; j<cols_len; j++)
		{
            //Since the input alpha matte does not only contain white (255) and black (0).
            //Therefore, select pixels above 200 to represent white.
			if (obj_mask.at<uchar>(i, j)>200 && i + row<depth_pic_rows_len && j + col<depth_pic_cols_len)
			{
				depth += depth_pic.at<uchar>(i + row, j + col);
				N++;
			}
		}
	}
	double obj_depth = double(depth) / N;
	return obj_depth;
}



double PastePic::ObjDepth(Mat obj_mask, Mat depth_pic) {

    /*
    Ablation Study: Calculate the depth value of the content in the target image 
        according to the size of the area where the object is located.
    */

	obj_mask.convertTo(obj_mask, CV_8UC1);
	depth_pic.convertTo(depth_pic, CV_8UC1);
	int rows_len = obj_mask.rows;
	int cols_len = obj_mask.cols;
	int N = 0;
	int depth = 0;

	for (int i = 0; i<rows_len; i++)
	{
		for (int j = 0; j<cols_len; j++)
		{
            //Since the input alpha matte does not only contain white (255) and black (0).
            //Therefore, select pixels above 200 to represent white.
			if (obj_mask.at<uchar>(i, j)>200)
			{
				depth += depth_pic.at<uchar>(i, j);
				N++;
			}
		}
	}
	double obj_depth = double(depth) / N;
	return obj_depth;
}


double PastePic::ObjDepthFoot(Mat obj_mask, Mat depth_pic, vector<Mat> target_alphas, int col, int row, int area_row, int area_col) {
    /*
    Calculate the depth value of the content of interest in the source image
        according to the set area size. The area is a rectangle with the lowest point at the bottom of the content.
    */

	obj_mask.convertTo(obj_mask, CV_8UC1);
	depth_pic.convertTo(depth_pic, CV_8UC1);
	int rows_len = obj_mask.rows;
	int cols_len = obj_mask.cols;
	int depth_pic_rows_len = depth_pic.rows;
	int depth_pic_cols_len = depth_pic.cols;
	int N = 0;
	int depth = 0;
	int bottom_row = 0;
	int bottom_col = 0;

	for (int i = 0; i<rows_len; i++)
	{
		for (int j = 0; j<cols_len; j++)
		{
            //Since the input alpha matte does not only contain white (255) and black (0).
            //Therefore, select pixels above 200 to represent white.
			if (obj_mask.at<uchar>(i, j)>200 && i + row<depth_pic_rows_len && j + col<depth_pic_cols_len&& i + row>0 && j + col>0)
			{
				bottom_col = bottom_col>j ? bottom_col : j;
				bottom_row = bottom_row>i ? bottom_row : i;
			}
		}
	}

	for (int i = bottom_row; i>0 && i>bottom_row - area_col; i--)
	{
		for (int j = bottom_col; j>0 && j>bottom_col - area_row; j--)
		{
            //Since the input alpha matte does not only contain white (255) and black (0).
            //Therefore, select pixels above 200 to represent white.
			if (obj_mask.at<uchar>(i, j)>200 && i + row<depth_pic_rows_len && j + col<depth_pic_cols_len && j + col<depth_pic_cols_len&& i + row>0 && j + col>0)
			{
				bool obj = false;
				for (vector<Mat>::iterator target_alpha_iter = target_alphas.begin(); target_alpha_iter != target_alphas.end(); target_alpha_iter++)
				{
					if ((*target_alpha_iter).at<uchar>(i + row, j + col)>250)
					{
						obj = true;
						break;
					}
				}
				if (obj == false)
				{
					depth += depth_pic.at<uchar>(i + row, j + col);
					N++;
				}
			}
		}
	}
	double obj_depth = double(depth) / N;
	return obj_depth;
}



double PastePic::ObjDepthFoot(Mat obj_mask, Mat depth_pic, int area_row, int area_col) {

    /*
    Calculate the depth value of the content in the target image.
        according to the set area size. The area is a rectangle with the lowest point at the bottom of the content.
    */

	obj_mask.convertTo(obj_mask, CV_8UC1);
	depth_pic.convertTo(depth_pic, CV_8UC1);
	int rows_len = obj_mask.rows;
	int cols_len = obj_mask.cols;
	int N = 0;
	int depth = 0;
	int bottom_row = 0;
	int bottom_col = 0;

	int depth_pic_rows_len = depth_pic.rows;
	int depth_pic_cols_len = depth_pic.cols;



	for (int i = 0; i<rows_len; i++)
	{
		for (int j = 0; j<cols_len; j++)
		{
            //Since the input alpha matte does not only contain white (255) and black (0).
            //Therefore, select pixels above 200 to represent white.
			if (obj_mask.at<uchar>(i, j)>200 && i <depth_pic_rows_len && j <depth_pic_cols_len)
			{
				bottom_col = bottom_col>j ? bottom_col : j;
				bottom_row = bottom_row>i ? bottom_row : i;
			}
		}
	}

	for (int i = bottom_row; i>0 && bottom_row - area_col; i--)
	{
		for (int j = bottom_col; j>0 && bottom_col - area_row; j--)
		{

			if (obj_mask.at<uchar>(i, j)<5)
			{
				depth += depth_pic.at<uchar>(i, j);
				N++;
			}
		}
	}
	double obj_depth = double(depth) / N;
	return obj_depth;
}

void PastePic::CompareDepth(double source_depth, double target_depth, Mat target_alpha, Mat& loc_alpha)
{
    /*
    Compare the depth value of the content of interest with the content in the target image.
    Calculate the alpha matte of the content before the content of interest.
    */

	target_alpha.convertTo(target_alpha, CV_8UC1);
	loc_alpha.convertTo(loc_alpha, CV_8UC1);
	int rows_len = target_alpha.rows;
	int cols_len = target_alpha.cols;
	if (target_depth<source_depth)
	{
		for (int i = 0; i<rows_len; i++)
		{
			for (int j = 0; j<cols_len; j++)
			{
                //Since the input alpha matte does not only contain white (255) and black (0).
                //Therefore, select pixels above 200 to represent white.
				if (target_alpha.at<uchar>(i, j)>200)
				{
					loc_alpha.at<uchar>(i, j) = 255;
				}
			}
		}
	}
}


Mat PastePic::SourceLocMask(float resize_ratio, Mat source_alpha, vector<Mat> target_alphas, Mat target_depth_pic, int col, int row)
{
    /*
    Calculate the depth value of the content in the target image and source image
    according to the set area size. The area is a rectangle with the lowest point at the bottom of the content.
    Calculate the alpha matte of the content before the content of interest.
    */

	vector<Mat> target_alpha;
	Mat source_alpha_resize;
	int	resize_cols = source_alpha.cols*resize_ratio;
	int	resize_rows = source_alpha.rows*resize_ratio;
	resize(source_alpha, source_alpha_resize, Size(resize_cols, resize_rows), 0, 0, INTER_LINEAR);
	//double source_depth=ObjDepth(source_alpha_resize,target_depth_pic,col,row);
	double source_depth = ObjDepthFoot(source_alpha_resize, target_depth_pic, target_alphas, col, row, 50, 100);
	vector<double> depthes;
	Mat source_loc_alpha = Mat::zeros(target_depth_pic.rows, target_depth_pic.cols, CV_8UC1);
	for (vector<Mat>::iterator target_alpha_iter = target_alphas.begin(); target_alpha_iter != target_alphas.end(); target_alpha_iter++)
	{
		//double target_depth=ObjDepth(*target_alpha_iter,target_depth_pic);
		double target_depth = ObjDepthFoot(*target_alpha_iter, target_depth_pic, 50, 100);
		CompareDepth(source_depth, target_depth, *target_alpha_iter, source_loc_alpha);
	}
    
	return source_loc_alpha;
}

/*
Mat PastePic::sourceMaskInTarget(Mat source_alpha, vector<Mat> target_alphas, int row_loc, int col_loc)
{

	Mat target_alpha1 = target_alphas[0];
	Mat source_alpha_in_target = Mat::zeros(target_alpha1.rows, target_alpha1.cols, CV_32FC1);
	int source_rows_len = source_alpha.rows;
	int source_cols_len = source_alpha.cols;
	int target_rows_len = target_alpha1.rows;
	int target_cols_len = target_alpha1.cols;

	for (int i = 0; i<source_rows_len && i + row_loc<target_rows_len; i++)
	{
		for (int j = 0; j<source_cols_len && j + col_loc<target_cols_len; j++)
		{
			if (source_alpha.at<uchar>(i, j)>200)
			{
				for (vector<Mat>::iterator target_alpha_iter = target_alphas.begin(); target_alpha_iter != target_alphas.end(); target_alpha_iter++)
				{
					if ((*target_alpha_iter).at<uchar>(i + row_loc, j + col_loc)>250)
					{
						continue;
					}
				}
				source_alpha_in_target.at<uchar>(i + row_loc, j + col_loc) = 0;

			}
		}
	}
	return source_alpha_in_target;
}
*/

Mat PastePic::Cutout(Mat source_pic, Mat source_alpha)
{
    /*
    Ablation Study: Crop out content of interest.
    */

	source_pic.convertTo(source_pic, CV_8UC3);
	cvtColor(source_alpha, source_alpha, CV_BGR2GRAY);
	int c = source_alpha.channels();
	string s = to_string(c);

	int rows_len = source_pic.rows;
	int cols_len = source_pic.cols;

	Mat cutout_pic = Mat::zeros(rows_len, cols_len, CV_8UC4);

	for (int i = 0; i<rows_len; i++)
	{
		for (int j = 0; j<cols_len; j++)
		{
			if (source_alpha.at<uchar>(i, j)<5)
			{
				cutout_pic.at<Vec4b>(i, j)[3] = 0;
			}
			else
			{
				cutout_pic.at<Vec4b>(i, j)[3] = 255;
				for (int channel = 0; channel<3; channel++)
				{
					cutout_pic.at<Vec4b>(i, j)[channel] = source_pic.at<Vec3b>(i, j)[channel];
				}
			}
		}
	}
	imwrite("C:/Users/txh/Desktop/test.png", cutout_pic);
	return cutout_pic;

}


Mat PastePic::SourceLocMaskPasteImage(Mat source_pic, Mat target_pic, Mat source_alpha_pic, vector<Mat> target_alphas, Mat depth_pic, char* save_path,int ox, int oy, float ratio)
{
    /*
    Image composition according to the order of depth values (main entrance).
    */

	Mat target_alpha_pic = SourceLocMask(ratio, source_alpha_pic, target_alphas, depth_pic, ox, oy);
	int col_size = source_alpha_pic.cols*ratio;
	int row_size = source_alpha_pic.rows*ratio;
    

	Mat source_alpha_pic_resize, source_pic_resize;
	resize(source_alpha_pic, source_alpha_pic_resize, Size(col_size, row_size), 0, 0, INTER_LINEAR);
	resize(source_pic, source_pic_resize, Size(col_size, row_size), 0, 0, INTER_LINEAR);
	Mat composite = PasteImage(source_pic_resize, target_pic, source_alpha_pic_resize, target_alpha_pic, ox, oy);
	return composite;
}


