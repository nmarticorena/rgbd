#ifndef RGBD_TRANSPORT_IMAGE_H_
#define RGBD_TRANSPORT_IMAGE_H_

#include "rgbd/types.h"

#include <opencv2/core/core.hpp>
#include <image_geometry/pinhole_camera_model.h>
#include <geolib/sensors/DepthCamera.h>

namespace tue
{
namespace serialization
{
    class InputArchive;
    class OutputArchive;
}
}

namespace rgbd {

class Image {

    friend class Server;
    friend class Client;
    friend class View;

public:

    Image();

    Image(const cv::Mat& rgb_image,
              const cv::Mat& depth_image,
              const image_geometry::PinholeCameraModel& cam_model,
              const std::string& frame_id,
              double timestamp);

    Image(const cv::Mat& rgb_image,
              const cv::Mat& depth_image,
              const geo::DepthCamera& cam_model,
              const std::string& frame_id,
              double timestamp);

    void setupRasterizer();

    inline const cv::Mat& getDepthImage() const { return depth_image_; }
    inline const cv::Mat& getRGBImage() const { return rgb_image_; }

    inline const std::string& getFrameId() const
    {
        return frame_id_;
    }

    inline const double& getTimestamp() const
    {
        return timestamp_;
    }

    inline void setDepthImage(const cv::Mat& depth_image) { depth_image_ = depth_image; }

    friend void serialize(const Image& image, tue::serialization::OutputArchive& a);

    friend void deserialize(tue::serialization::InputArchive& a, Image& image);

protected:

    cv::Mat rgb_image_;
    cv::Mat depth_image_;

    image_geometry::PinholeCameraModel cam_model_;
    geo::DepthCamera rasterizer_;

    std::string frame_id_;
    double timestamp_;

};

}

#endif