/* -*-c++-*--------------------------------------------------------------------
 * 2018 Bernd Pfrommer bernd.pfrommer@gmail.com
 */
#include "downsampling_image_transport/downsampling_publisher.h"

namespace downsampling_image_transport {
  void
  DownsamplingPublisher::configure(DownsamplingDynConfig& config, int level) {
    Lock lock(configMutex_);
    config_ = config;
  }

  void DownsamplingPublisher::advertiseImpl(
    ros::NodeHandle &nh, const std::string &base_topic,
    uint32_t queue_size,
    const image_transport::SubscriberStatusCallback  &conn_cb,
    const image_transport::SubscriberStatusCallback  &disconn_cb,
    const ros::VoidPtr &tracked_object, bool latch) {
    
    const std::string transportTopic = getTopicToAdvertise(base_topic);
    nh_.reset(new ros::NodeHandle(transportTopic));
    initConfigServer();
    DownsamplingPublisherPlugin::advertiseImpl(
      nh, base_topic, queue_size, conn_cb, disconn_cb, tracked_object, latch);
  }

  void
  DownsamplingPublisher::publish(const sensor_msgs::Image& message,
                                 const PublishFn &publish_fn) const {
    Lock lock(configMutex_);
    imageCounter_++;
    if ((int)imageCounter_ > config_.sampling_rate) {
      (publish_fn)(message);
      imageCounter_ = 0;
    }
  }

  void DownsamplingPublisher::initConfigServer() {
    Lock lock(configMutex_);
    if (!configServer_) {
      configServer_.reset(new ConfigServer(*nh_));
      // this will trigger an immediate callback!
      configServer_->setCallback(
        boost::bind(&DownsamplingPublisher::configure, this, _1, _2));
    }
  }
}
