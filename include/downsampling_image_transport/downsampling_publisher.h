/* -*-c++-*--------------------------------------------------------------------
 * 2018 Bernd Pfrommer bernd.pfrommer@gmail.com
 */

#pragma once

#include "downsampling_image_transport/DownsamplingDynConfig.h"
#include <image_transport/simple_publisher_plugin.h>
#include <dynamic_reconfigure/server.h>

#include <mutex>
#include <memory>

namespace downsampling_image_transport {
  typedef image_transport::SimplePublisherPlugin<
    sensor_msgs::Image>  DownsamplingPublisherPlugin;
  class DownsamplingPublisher : public DownsamplingPublisherPlugin {
    typedef std::unique_lock<std::recursive_mutex> Lock;
  public:
    virtual std::string getTransportName() const override {
      return "downsampling";
    }
    void configure(DownsamplingDynConfig& config, int level);

  protected:
    // override to set up reconfigure server
    virtual void advertiseImpl(ros::NodeHandle &nh,
                               const std::string &base_topic,
                               uint32_t queue_size,
                               const image_transport::SubscriberStatusCallback
                               &user_connect_cb,
                               const image_transport::SubscriberStatusCallback
                               &user_disconnect_cb,
                               const ros::VoidPtr &tracked_object,
                               bool latch) override;
    void publish(const sensor_msgs::Image& message,
                 const PublishFn& publish_fn) const override;

  private:
    void initConfigServer();
    // variables ---------
    typedef dynamic_reconfigure::Server<DownsamplingDynConfig> ConfigServer;
    std::shared_ptr<ros::NodeHandle>   nh_;
    std::shared_ptr<ConfigServer> configServer_;
    DownsamplingDynConfig         config_;
    mutable std::recursive_mutex  configMutex_;
    mutable unsigned int          imageCounter_{0};
  };
}
