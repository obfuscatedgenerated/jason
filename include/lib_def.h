// #PRIVATEHEADER

#ifndef JASON_LIB_DEF_H
#define JASON_LIB_DEF_H

#ifdef WIN32

#define PUBLIC __declspec(dllexport)
#define PRIVATE

#else

#ifdef __GNUC__ >= 4

#define PUBLIC __attribute__((visibility("default")))
#define PRIVATE __attribute__((visibility("hidden")))

#else

#define PUBLIC
#define PRIVATE

#endif

#endif

#endif //JASON_LIB_DEF_H
