/* -*-c++-*--------------------------------------------------------------------
 * 2018 Bernd Pfrommer bernd.pfrommer@gmail.com
 */

#include "downsampling_image_transport/downsampling_subscriber.h"

namespace downsampling_image_transport {

  void DownsamplingSubscriber::internalCallback(
    const ImageConstPtr& msg, const Callback& user_cb) {
    (user_cb)(msg);
  }
}
