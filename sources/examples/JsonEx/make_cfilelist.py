import glob
import os
import re
# source directory
read_files =  glob.glob("OutC\\*.c") 
read_filesH =  glob.glob("OutC\\*.h")

with open("SrcList.cmake", "wb") as outfile:
    outfile.write(bytes("set(APP_SRCS",'UTF-8'));
    outfile.write(bytes("\r\n",'UTF-8'));
    for f in read_files:
            fpath, fname = os.path.split(f)
            outfile.write(bytes("./OutC/",'UTF-8'));
            outfile.write(bytes(fname,'UTF-8'));
            outfile.write(bytes("\r\n",'UTF-8'));
#    outfile.write(bytes(")",'UTF-8'));
#    outfile.write(bytes("\r\n",'UTF-8'));
    for f in read_filesH:
            fpath, fname = os.path.split(f)
            outfile.write(bytes("./OutC/",'UTF-8'));
            outfile.write(bytes(fname,'UTF-8'));
            outfile.write(bytes("\r\n",'UTF-8'));
    outfile.write(bytes(")",'UTF-8'));
    outfile.write(bytes("\r\n",'UTF-8'));


