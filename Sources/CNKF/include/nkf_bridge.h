//#include "./nkf_bridge.c"

#include <CoreFoundation/CoreFoundation.h>

CF_EXPORT CF_RETURNS_RETAINED __nonnull CFDataRef cf_nkf_convert(__nonnull CFDataRef src, __nonnull CFDataRef optsString,  CFIndex* _Nonnull  outLength);
CF_EXPORT CF_RETURNS_RETAINED const char* _Nullable  cf_nkf_guess(__nonnull CFDataRef src);