#pragma once

//python include - must be before standard headers

#include<Python.h>

// stl headers

#include<unordered_map>
#include<vector>
#include<utility>
#include<string>
#include<exception>
#include<algorithm>

//opencv headers

#include<cv.h>
#include<cxcore.h>
#include<highgui.h>

//c++ headers

#include<fstream>
#include<cstdlib>
#include<iostream>
#include<assert.h>
#include<errno.h>
#include<stdio.h>


//linux headers

#ifdef __linux__

#include<dirent.h>

#elif defined _WIN32 || _WIN64

#include<Windows.h>

#endif
