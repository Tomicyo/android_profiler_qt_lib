from tools.android import build_android_instance
from tools.windows import build_win64_instance
#from tools.download import download_and_extract
import os
curdir = os.path.dirname(os.path.abspath(__file__))
print curdir
build_android_instance(curdir, 'armeabi-v7a', 'gnustl_shared')
#build_win64_instance(True, True)