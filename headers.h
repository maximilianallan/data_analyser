#pragma once

// stl headers

#include<unordered_map>
#include<vector>
#include<utility>
#include<string>
#include<exception>

//opencv headers

#include<cv.h>
#include<cxcore.h>
#include<highgui.h>

//c++ headers

#include<fstream>
#include<cstdlib>

#include<iostream>

//linux headers

#ifdef __linux__

#include<dirent.h>

#elif defined _WIN32 || _WIN64

#include<Windows.h>

#endif
