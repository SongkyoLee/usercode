#!/bin/csh
cd _in_dir_
#cms
eval `scramv1 runtime -csh`
cd -
cmsRun _in_dir_/_input_py_
##rfcp _output_file_ _out_dir_/_output_file_
mv _output_file_ _in_dir_/
