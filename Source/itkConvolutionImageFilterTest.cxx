
#include <string>

#include "itkConvolutionImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

template <unsigned int ImageDimension>
int itkConvolutionImageFilterTest( unsigned int argc, char *argv[] )
{
  typedef float                                  PixelType;
  typedef itk::Image<PixelType, ImageDimension>  ImageType;
  typedef itk::ImageFileReader<ImageType>        ReaderType;

  typename ReaderType::Pointer reader1 = ReaderType::New();
  reader1->SetFileName( argv[2] );
  reader1->Update();

  typename ReaderType::Pointer reader2 = ReaderType::New();
  reader2->SetFileName( argv[3] );
  reader2->Update();

  typedef itk::ConvolutionImageFilter<ImageType> ConvolutionFilterType;
  typename ConvolutionFilterType::Pointer convoluter
    = ConvolutionFilterType::New();
  convoluter->SetInput( reader1->GetOutput() );
  convoluter->SetImageKernelInput( reader2->GetOutput() );

  if( argc > 5 && static_cast<bool>( atoi( argv[5] ) ) )
    {
    convoluter->NormalizeOn();
    }

  try
    {
    convoluter->Update();
    }
  catch( ... )
    {
    return EXIT_FAILURE;
    }

  typedef itk::ImageFileWriter<ImageType> WriterType;
  typename WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[4] );
  writer->SetInput( convoluter->GetOutput() );
  writer->Update();

  return EXIT_SUCCESS;
}

int main( int argc, char *argv[] )
{
  if ( argc < 5 )
    {
    std::cout << "Usage: " << argv[0] << " imageDimension"
      << " inputImage kernelImage outputImage [normalizeImage]" << std::endl;
    return EXIT_FAILURE;
    }

  switch( atoi( argv[1] ) )
    {
    case 2:
      return itkConvolutionImageFilterTest<2>(
        argc, argv );
      break;
    case 3:
      return itkConvolutionImageFilterTest<3>(
       argc, argv );
      break;
    default:
      std::cerr << "Unsupported dimension" << std::endl;
      return EXIT_FAILURE;
    }
}
