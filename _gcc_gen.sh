
export SOLUTION_NAME=stsc
export SYSTEM_UTILITIES_ROOT=~/_dev/cpp_objc/system_utilities

export BUILD_TYPE=Debug
if [ "$1" == 'Release' ];
then
	export BUILD_TYPE=Release
fi

export BUILD_FOLDER=_build_"$BUILD_TYPE"_32

if [ ! -d $BUILD_FOLDER ];
then
	mkdir $BUILD_FOLDER
fi

cd $BUILD_FOLDER
cmake -DVERBOSE=ON -DSOLUTION_NAME=$SOLUTION_NAME -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G "Unix Makefiles" ../ 
cd ../

#echo "%BUILD_FOLDER%/%SOLUTION_NAME%.sln" > _start_msvc.bat
