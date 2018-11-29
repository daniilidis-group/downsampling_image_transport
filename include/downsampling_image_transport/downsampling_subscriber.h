/* -*-c++-*--------------------------------------------------------------------
 * 2018 Bernd Pfrommer bernd.pfrommer@gmail.com
 */
#pragma once

#include <image_transport/simple_subscriber_plugin.h>
#include <sensor_msgs/Image.h>


namespace downsampling_image_transport {
  using Image         = sensor_msgs::Image;
  using ImageConstPtr = sensor_msgs::ImageConstPtr;
  
  typedef image_transport::SimpleSubscriberPlugin<Image>
  DownsamplingSubscriberPlugin;
  class DownsamplingSubscriber: public DownsamplingSubscriberPlugin  {
  public:
    virtual ~DownsamplingSubscriber() {}

    virtual std::string getTransportName() const {
      return "downsampling";
    }

  protected:
    virtual void
    internalCallback(const typename sensor_msgs::ImageConstPtr &message,
                     const Callback& user_cb) override;
  private:
  };
}
