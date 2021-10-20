dir = "C:\\Users\\PC_901_ADMIN\\PycharmProjects\\pythonProject3\\tiles"
tar = "C:\\Users\\PC_901_ADMIN\\Desktop\\tiles"
import glob
import os

header = "osm_100-l-3-"

dir1 = os.path.join(dir, "*")
dir1_list = glob.glob(dir1)

for folder in dir1_list:
    dir2 = os.path.join(folder, "*")
    dir2_list = glob.glob(dir2)
    folder_basename = os.path.basename(folder)
    for fold in dir2_list:
        dir3 = os.path.join(fold, "*")
        dir3_list = glob.glob(dir3)
        fold_basename = os.path.basename(fold)
        for fo in dir3_list:
            fo_basename = os.path.basename(fo)
            src = os.path.split(fo)[0]
            re_name = tar + "\\" + header + folder_basename + "-" + fold_basename + "-" + fo_basename
            os.rename(fo, re_name)
            print(re_name)

files = os.listdir(tar)

file= open("filenames.txt","w+")
for f in files:
	file.write("<file>offline_tiles/"+f+"</file>\n")
file.close()