# argument 1: path to include dir
# argument 2: path to output dir

# copy include files to output dir but for each file:
# - dont copy if the file is named "lib_def.h"
# - remove #include directives that include a file named "lib_def.h at any level (e.g. #include "lib_def.h", #include "./lib_def.h", #include "../lib_def.h")
# - if a line starts with PUBLIC, remove the PUBLIC keyword
# - if a line starts with PRIVATE, remove the whole line

INCLUDE_DIR=$1
OUTPUT_DIR=$2

# clean output dir if it exists
if [ -d $OUTPUT_DIR/include ]; then
    rm -rf $OUTPUT_DIR/include
fi

mkdir -p $OUTPUT_DIR/include

# copy include dir to output dir
cp -r $INCLUDE_DIR $OUTPUT_DIR

# remove lib_def.h
rm $OUTPUT_DIR/include/lib_def.h

for file in $(find $OUTPUT_DIR/include -type f -name "*.h"); do
    # remove #include directives that include a file named "lib_def.h at any level
    sed -i '/#include.*lib_def.h/d' $file
    # remove PUBLIC keyword
    sed -i 's/^PUBLIC //' $file
    # remove lines starting with PRIVATE
    sed -i '/^PRIVATE/d' $file
done
