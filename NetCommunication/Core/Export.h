#pragma once

# define Proper_Export_Flag __declspec (dllexport)
# define Proper_Import_Flag __declspec (dllimport)


#ifdef NETCOMMUNICATION_DLL
#define NETCOMMUNICATION_EXPORT Proper_Export_Flag
#else
#define NETCOMMUNICATION_EXPORT Proper_Import_Flag
#endif
