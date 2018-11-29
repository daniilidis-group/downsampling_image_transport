#include <pluginlib/class_list_macros.h>
#include "downsampling_image_transport/downsampling_publisher.h"
#include "downsampling_image_transport/downsampling_subscriber.h"

PLUGINLIB_EXPORT_CLASS(downsampling_image_transport::DownsamplingPublisher,  image_transport::PublisherPlugin)
PLUGINLIB_EXPORT_CLASS(downsampling_image_transport::DownsamplingSubscriber, image_transport::SubscriberPlugin)
