#include <SimpleITKTestHarness.h>
#include <itkHashImageFilter.h>
#include <itkImageFileReader.h>

class HashImageFilterTest
  : public ::testing::Test {
public:

  template <typename TPixelType, unsigned int IDimension>
  void CheckImageHashMD5( const std::string &fname, const std::string &expectedHash )
  {

    typedef itk::ImageFileReader<itk::Image<TPixelType, IDimension > > ReaderType;
    typename ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( dataFinder.GetFile ( fname ) );
    reader->Update();

    typedef itk::HashImageFilter< itk::Image<TPixelType, IDimension> > HasherType;
    typename HasherType::Pointer  hasher = HasherType::New();
    hasher->SetHashFunction( HasherType::MD5 );
    hasher->SetInput( reader->GetOutput() );
    hasher->Update();

    EXPECT_EQ ( expectedHash, hasher->GetHash() );

  }

  template <typename TPixelType, unsigned int IDimension>
  void CheckImageHashSHA1( const std::string &fname, const std::string &expectedHash )
  {

    typedef itk::ImageFileReader<itk::Image<TPixelType, IDimension > > ReaderType;
    typename ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( dataFinder.GetFile ( fname ) );
    reader->Update();

    typedef itk::HashImageFilter< itk::Image<TPixelType, IDimension> > HasherType;
    typename HasherType::Pointer  hasher = HasherType::New();
    hasher->SetHashFunction( HasherType::SHA1 );
    hasher->SetInput( reader->GetOutput() );
    hasher->Update();

    EXPECT_EQ ( expectedHash, hasher->GetHash() );

  }
};

TEST_F(HashImageFilterTest, InstantiateTest) {

  typedef itk::HashImageFilter< itk::Image< unsigned char, 1> > UCHAR1HasherType;
  EXPECT_TRUE( UCHAR1HasherType::New() );

  typedef itk::HashImageFilter< itk::Image< unsigned char, 2> > UCHAR2HasherType;
  EXPECT_TRUE( UCHAR2HasherType::New() );

  typedef itk::HashImageFilter< itk::Image< unsigned char, 3> > UCHAR3HasherType;
  EXPECT_TRUE( UCHAR3HasherType::New() );

  typedef itk::HashImageFilter< itk::Image< unsigned int, 3> > UINT23HasherType;
  EXPECT_TRUE( UINT23HasherType::New() );

  typedef itk::HashImageFilter< itk::Image<int, 3> > INT23HasherType;
  EXPECT_TRUE( INT23HasherType::New() );

  typedef itk::HashImageFilter< itk::Image<float, 3> > FLOATHasherType;
  EXPECT_TRUE( INT23HasherType::New() );

  typedef itk::HashImageFilter< itk::Image<double, 3> > DOUBLEHasherType;
  EXPECT_TRUE( INT23HasherType::New() );

};


TEST_F(HashImageFilterTest, MD5HashValues ) {

  this->CheckImageHashMD5<float,3>("Input/RA-Float.nrrd", "3ccccde44efaa3d688a86e94335c1f16");

  this->CheckImageHashMD5<float,2>("Input/RA-Float.nrrd", "16142594b185c50d64dd629750b94c90");

  this->CheckImageHashMD5<float,1>("Input/RA-Float.nrrd", "606f0ee67f5b181f90286e17e6f49926");

  this->CheckImageHashMD5<short, 3>("Input/Ramp-Down-Short.nrrd", "71f5c852a6251069fa1d60f796463343" );

  this->CheckImageHashMD5<int, 3>("Input/Ramp-Down-Short.nrrd", "f945b2b5384ba6f21a0fd50a970fb5ff");
}


TEST_F(HashImageFilterTest, SHA1HashValues ) {

  this->CheckImageHashSHA1<float,3>("Input/RA-Float.nrrd", "b187541bdcc89843d0a25a3761f344c358f3518a" );

  this->CheckImageHashSHA1<float,2>("Input/RA-Float.nrrd", "7bd2146732f1e6f38fe5ed387332d3ad3541b182" );

  this->CheckImageHashSHA1<float,1>("Input/RA-Float.nrrd",  "0eac9ac1f19b27743dfeabe76e69ae251c02b641" );

  this->CheckImageHashSHA1<short, 3>("Input/Ramp-Down-Short.nrrd", "4b0bd9dcf1f7d78101ce24da7f51de212f302ae9" );

  this->CheckImageHashSHA1<int, 3>("Input/Ramp-Down-Short.nrrd",  "3dc54908746f25fd42f17c5fe44935013e508b1b" );
}

TEST_F(HashImageFilterTest, VectorImages ) {

  // test image of vectors
  {
  typedef itk::Image<itk::Vector<float, 1>, 3 > VectorImageType;

  typedef itk::ImageFileReader<VectorImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) );
  reader->Update();

  typedef itk::HashImageFilter< VectorImageType > HasherType;
  HasherType::Pointer  hasher = HasherType::New();
  hasher->SetHashFunction( HasherType::MD5 );
  hasher->SetInput( reader->GetOutput() );
  hasher->Update();

  EXPECT_EQ( hasher->GetHash(), "3ccccde44efaa3d688a86e94335c1f16" );
  }

  // test vector image
  {
  typedef itk::VectorImage<float, 3> VectorImageType;

  typedef itk::ImageFileReader<VectorImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) );
  reader->Update();

  typedef itk::HashImageFilter< VectorImageType > HasherType;
  HasherType::Pointer  hasher = HasherType::New();
  hasher->SetHashFunction( HasherType::MD5 );
  hasher->SetInput( reader->GetOutput() );
  hasher->Update();


  EXPECT_EQ( hasher->GetHash(), "3ccccde44efaa3d688a86e94335c1f16" );
  }
}

TEST_F(HashImageFilterTest, Coverage ) {

 typedef itk::HashImageFilter< itk::Image< unsigned char, 2> > UCHAR2HasherType;
 UCHAR2HasherType::Pointer hasher = UCHAR2HasherType::New();

 // PrintSelf
 std::cout << hasher;

 // Set/Get Methods
 hasher->SetHashFunction( UCHAR2HasherType::MD5 );
 EXPECT_EQ(  hasher->GetHashFunction(), UCHAR2HasherType::MD5 );

 hasher->SetHashFunction( UCHAR2HasherType::SHA1 );
 EXPECT_EQ(  hasher->GetHashFunction(), UCHAR2HasherType::SHA1 );
}