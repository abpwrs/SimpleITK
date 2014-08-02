/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
#ifndef __sitkBSplineTransform_h
#define __sitkBSplineTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{

class SITKCommon_EXPORT BSplineTransform
  : public Transform
{
public:
  typedef BSplineTransform Self;
  typedef Transform Superclass;
  explicit BSplineTransform(unsigned int dimensions);

  BSplineTransform( const BSplineTransform & );

  BSplineTransform &operator=( const BSplineTransform & );

  /** parameters */

  /** fixed parameter */
  Self &SetTransformDomainDirection(const std::vector<double> &);
  std::vector<double>  GetTransformDomainDirection() const;
  Self &SetTransformDomainMeshSize(const std::vector<unsigned int>&);
  std::vector<unsigned int> GetTransformDomainMeshSize() const;
  Self &SetTransformDomainOrigin(const std::vector<double>&);
  std::vector<double> GetTransformDomainOrigin() const;
  Self &SetTransformDomainPhysicalDimensions(const std::vector<double> &);
  std::vector<double> GetTransformDomainPhysicalDimensions() const;

  /* additional methods */

  /** \brief Get a vector of the coefficient images representing the BSpline
   *
   * A lazy shallow copy of the images from ITK are performed. If they
   * are modified in SimpleITK a deep copy will occur. However, if
   * the coefficients are modified in ITK, then no copy will occur and
   * the images help by SimpleITK may change.
   */
  std::vector<Image> GetCoefficientImages () const;

protected:

  virtual void SetPimpleTransform( PimpleTransformBase *pimpleTransform );

private:

  using Superclass::AddTransform;

  struct MyVisitor
  {
    itk::TransformBase *transform;
    BSplineTransform *that;
    template< typename TransformType >
    void operator() ( void ) const
      {
        TransformType *t = dynamic_cast<TransformType*>(transform);
        if (t)
          {
          that->InternalInitialization<TransformType>(t);
          }
      }
  };

  void InternalInitialization(itk::TransformBase *transform);

  template <typename TransformType>
    void InternalInitialization(TransformType *transform);

  static PimpleTransformBase *CreateBSplinePimpleTransform(unsigned int dimension);

  nsstd::function<std::vector<double> ()> m_pfGetTransformDomainDirection;
  nsstd::function<void (const std::vector<double> &)> m_pfSetTransformDomainDirection;
  nsstd::function<std::vector<unsigned int> ()> m_pfGetTransformDomainMeshSize;
  nsstd::function<void (const std::vector<unsigned int>&)> m_pfSetTransformDomainMeshSize;
  nsstd::function<std::vector<double> ()> m_pfGetTransformDomainOrigin;
  nsstd::function<void (const std::vector<double>&)> m_pfSetTransformDomainOrigin;
  nsstd::function<std::vector<double> ()> m_pfGetTransformDomainPhysicalDimensions;
  nsstd::function<void (const std::vector<double> &)> m_pfSetTransformDomainPhysicalDimensions;

  nsstd::function<std::vector<Image> ()> m_pfGetCoefficientImages;

};

}
}

#endif // __sitkBSplineTransform_h