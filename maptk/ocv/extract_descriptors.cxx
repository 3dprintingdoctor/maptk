/*ckwg +5
 * Copyright 2013 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#include <maptk/ocv/extract_descriptors.h>
#include <maptk/ocv/image_container.h>
#include <maptk/ocv/feature_set.h>
#include <maptk/ocv/descriptor_set.h>


namespace maptk
{

namespace ocv
{

/// Private implementation class
class extract_descriptors::priv
{
public:
  /// Constructor
  priv()
  : extractor(cv::DescriptorExtractor::create("SURF"))
  {
  }

  /// Copy constructor
  priv(const priv& other)
  : extractor(cv::DescriptorExtractor::create("SURF"))
  {
  }

  /// the descriptor extractor algorithm
  cv::Ptr<cv::DescriptorExtractor> extractor;
};


/// Constructor
extract_descriptors
::extract_descriptors()
: d_(new priv)
{
}


/// Copy Constructor
extract_descriptors
::extract_descriptors(const extract_descriptors& other)
: d_(new priv(*other.d_))
{
}


/// Destructor
extract_descriptors
::~extract_descriptors()
{
}


/// Extract from the image a descriptor corresoponding to each feature
descriptor_set_sptr
extract_descriptors
::extract(image_container_sptr image_data,
          feature_set_sptr features) const
{
  if( !image_data || !features )
  {
    return descriptor_set_sptr();
  }
  cv::Mat img = image_container_to_ocv_matrix(*image_data);
  std::vector<cv::KeyPoint> kpts = features_to_ocv_keypoints(*features);

  cv::Mat desc;
  d_->extractor->compute( img, kpts, desc );

  return descriptor_set_sptr(new ocv::descriptor_set(desc));
}


} // end namespace ocv

} // end namespace maptk