#include "rgbd_transport/RGBDImage.h"

namespace rgbd {

// ----------------------------------------------------------------------------------------

RGBDImage::RGBDImage(const cv::Mat& rgb_image,
                     const cv::Mat& depth_image,
                     const image_geometry::PinholeCameraModel& cam_model,
                     const std::string& frame_id,
                     double timestamp) :
    cam_model_(cam_model),
    frame_id_(frame_id),
    timestamp_(timestamp),
    rgb_image_(rgb_image),
    depth_image_(depth_image)
{
    // Set the rasterizer
    rasterizer_.setFocalLengths(cam_model_.fx(), cam_model_.fy());
    rasterizer_.setOpticalCenter(cam_model_.cx(), cam_model_.cy());
    rasterizer_.setOpticalTranslation(cam_model_.Tx(), cam_model_.Ty());

    // Determine scaling between rgb and depth
    ratio_ = depth_image_.cols / depth_image_.rows; // 640 / 480
    factor_ = rgb_image_.cols / depth_image_.cols; // 640 / 640 or 1280 / 640
    width_ = rgb_image_.cols;
    height_ = width_ / ratio_;
}

}
