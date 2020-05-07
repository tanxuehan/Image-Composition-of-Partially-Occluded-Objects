
#include <cstdio>
#include <opencv2\opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class PastePic {
private:

	double ObjDepth(Mat obj_mask, Mat depth_pic, int col, int row);
    /*
    Ablation Study: Calculate the depth value of the content of interest in the source image 
        according to the size of the area where the object is located.

    Args:
    obj_mask(Mat): Alpha matte of source image.
    depth_pic(Mat): Depth map of source image.
    row(int): row displacement of pixels.
    col(int): column displacement of pixels.

    Returns:
    obj_depth(double): the depth value of the content of interest in the source image.
    */

	double ObjDepth(Mat obj_mask, Mat depth_pic);
    /*
    Ablation Study: Calculate the depth value of the content in the target image 
        according to the size of the area where the object is located.

    Args:
    obj_mask(Mat): Alpha matte of target image.
    depth_pic(Mat): Depth map of target image.

    Returns:
    obj_depth(double): the depth value of the content in the target image.
    */
	double ObjDepthFoot(Mat obj_mask, Mat depth_pic, vector<Mat> target_alphas, int col, int row, int area_row, int area_col);
    /*
    Calculate the depth value of the content of interest in the source image
        according to the set area size. The area is a rectangle with the lowest point at the bottom of the content.

    Args:
    obj_mask(Mat): Alpha matte of source image.
    depth_pic(Mat): Depth map of source image.
    target_alphas(vector<Mat>):Alpha matte of the content in target image.
    area_row(int):the row of the set area.
    area_col(int):the column of the set area.
    row(int): row displacement of pixels.
    col(int): column displacement of pixels.

    Returns:
    obj_depth(double): the depth value of the content of interest in the source image.
    */

	double ObjDepthFoot(Mat obj_mask, Mat depth_pic, int area_row, int area_col);
    /*
    Calculate the depth value of the content in the target image.
        according to the set area size. The area is a rectangle with the lowest point at the bottom of the content.

    Args:
    obj_mask(Mat): Alpha matte of source image.
    depth_pic(Mat): Depth map of source image.
    target_alphas(vector<Mat>):Alpha matte of the content in target image.
    area_row(int):the row of the set area.
    area_col(int):the column of the set area.

    Returns:
    obj_depth(double): the depth value of the content of interest in the source image.
    */

	void CompareDepth(double source_depth, double target_depth, Mat target_alpha, Mat& loc_alpha);
    /*
    Compare the depth value of the content of interest with the content in the target image.
    Calculate the alpha matte of the content before the content of interest.

    Args:
    source_depth(double): Depth value of source image.
    target_depth(double): Depth value of target image.
    target_alphas(vector<Mat>):Alpha matte of the content in target image.
    loc_alpha(Mat):the alpha matte of the content in the target image after compartion.

    Returns:
    None.
    */

	Mat SourceLocMask(float resize_ratio, Mat source_alpha, vector<Mat> target_alphas, Mat target_depth_pic, int col, int row);
    /*
    Calculate the depth value of the content in the target image and source image
    according to the set area size. The area is a rectangle with the lowest point at the bottom of the content.
    Calculate the alpha matte of the content before the content of interest.

    Args:
    resize_ratio(float): Image scaling.
    source_alpha(Mat): The alpha matte of the content of interest.
    target_depth(double): The alpha matte of  the content in the target image.
    target_alphas(vector<Mat>):Alpha matte of the content in target image.
    target_depth_pic(Mat):Depth map of target image.
    row(int): row displacement of pixels.
    col(int): column displacement of pixels.

    Returns:
    source_loc_alpha(Mat): the alpha matte of the content before the content of interest.
    */

	Mat PasteImage(Mat&source_pic, Mat&target_pic, Mat&source_alpha_pic, Mat&target_alpha_pic, int ox, int oy);
    /*
    Composite the image according to the matte of the target image and the source image

    Args:
    source_pic(Mat&): Source image.
    target_pic(Mat&): Target image.
    target_alpha_pic(Mat):Alpha matte for target image.
    source_alpha_pic(Mat): Alpha matte for source image.
    ox(int): row coordinates of pixels.
    oy(int): column coordinates of pixels.

    Returns:
    composit(Mat):composition result.
    */

public:
	Mat Cutout(Mat source_pic, Mat source_alpha);
    /*
    Ablation Study: Crop out content of interest.

    Args:
    source_pic(Mat&): Source image.
    source_alpha(Mat): Alpha matte for input image.

    Returns:
    cutout_pic(Mat):The content of interest.
    */

	Mat SourceLocMaskPasteImage(Mat source_pic, Mat target_pic, Mat source_alpha_pic, vector<Mat> target_alphas, Mat depth_pic, char* save_path, int ox, int oy, float ratio);
    /*
    Image composition according to the order of depth values(main entrance)

    Arg:
    source_pic(Mat): Source image.
    target_pic(Mat): Target image.
    source_alpha_pic(Mat): Alpha matte for input image.
    target_alphas(vector<Mat>):Alpha matte of the content in target image.
    depth_pic(Mat): Depth map of source image.
    ox(int): row coordinates of pixels.
    oy(int): column coordinates of pixels.
    ratio(float): Image scaling.

    Returns:
    composite(Mat): composition result.
    */

	Mat target_pic;     //Target image.
	Mat source_pic;     //Source image.
	vector<Mat> target_alphas;      //Alpha matte of the content in target image.
	Mat depth_pic;      //Depth map of source image.
	Mat source_alpha_pic;       //Alpha matte for source image.
	Mat target_alpha_pic;       //Alpha matte for target image.
	int loc_row;        //row coordinates of pixels.
	int loc_col;        //column coordinates of pixels.

};
