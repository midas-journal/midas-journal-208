cmake_minimum_required(VERSION 2.4)

#include some macros from another file...
INCLUDE(${CMAKE_SOURCE_DIR}/IJMacros.txt)

#Change PROJECT_NAME to the name of your project
PROJECT(ConvolutionImageFilterTest)

#The following lines are required to use Dart
ENABLE_TESTING()
INCLUDE(Dart)
FIND_PROGRAM(IMAGE_COMPARE ImageCompare)

#Declare any external dependencies that your project may have here.
#examples include: ITK, VTK, JPEG, PNG, OpenGL, ZLIB, Perl, Java
#If you're not sure what name to use, look in the Modules directory of your
#cmake install and check that a file named Find(Package).cmake exists
SET(Required_Packages
ITK
)

#this foreach loads all of the packages that you specified as required.
#It shouldn't need to be modified.
FOREACH(Package ${Required_Packages})
  LOADPACKAGE(${Package})
ENDFOREACH(Package)

#Set any libraries that your project depends on.
#examples: ITKCommon, VTKRendering, etc
SET(Libraries
    ITKCommon
    ITKBasicFilters
    ITKStatistics
    ITKAlgorithms
    ITKIO
    itkgdcm
   )

#the following block of code is an example of how to build an executable in
#cmake.  Unmodified, it will add an executabale called "MyExe" to the project.
#MyExe will be built using the files MyClass.h and MyClass.cxx, and it will
#be linked to all the libraries you specified above. 
#You can build more than one executable per project

IF(BUILD_TESTING)

SET(CurrentExe
    "itkConvolutionImageFilterTest"
    )
ADD_EXECUTABLE(${CurrentExe} 
               ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe}
                      ${Libraries})

ENDIF(BUILD_TESTING)

#the following line is an example of how to add a test to your project.
#Testname is the title for this particular test.  ExecutableToRun is the
#program which will be running this test.  It can either be a part of this
#project or an external executable.  After that list any args that are needed
#for this test.  Include as many tests as you like.  If your project doesn't have
#any tests you can comment out or delete the following line.
# ADD_TEST(Testname ExecutableToRun arg1 arg2 arg3)

ADD_TEST( Conv_Avg ${CurrentExe} 2 ${CMAKE_SOURCE_DIR}/Images/BrainT1SliceBorder20.nii.gz ${CMAKE_SOURCE_DIR}/Images/constant.nii.gz 
${CMAKE_BINARY_DIR}/output_avg.nii.gz ) 
ADD_TEST( Compare_Avg ${IMAGE_COMPARE}  
${CMAKE_BINARY_DIR}/output_avg.nii.gz ${CMAKE_SOURCE_DIR}/Images/output_avg.nii.gz ) 

ADD_TEST( Conv_SobelX ${CurrentExe} 2 ${CMAKE_SOURCE_DIR}/Images/BrainT1SliceBorder20.nii.gz ${CMAKE_SOURCE_DIR}/Images/sobel_x.nii.gz 
${CMAKE_BINARY_DIR}/output_sobel_x.nii.gz ) 
ADD_TEST( Compare_SobelX ${IMAGE_COMPARE} ${CMAKE_BINARY_DIR}/output_sobel_x.nii.gz ${CMAKE_SOURCE_DIR}/Images/output_sobel_x.nii.gz 
 ) 

ADD_TEST( Conv_SobelY ${CurrentExe} 2 ${CMAKE_SOURCE_DIR}/Images/BrainT1SliceBorder20.nii.gz ${CMAKE_SOURCE_DIR}/Images/sobel_y.nii.gz 
${CMAKE_BINARY_DIR}/output_sobel_y.nii.gz ) 
ADD_TEST( Compare_SobelY ${IMAGE_COMPARE} ${CMAKE_BINARY_DIR}/output_sobel_y.nii.gz 
${CMAKE_SOURCE_DIR}/Images/output_sobel_y.nii.gz )


