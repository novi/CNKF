//#include "./nkf_bridge.c"

#include <CoreFoundation/CoreFoundation.h>

CF_EXPORT CF_RETURNS_RETAINED __nonnull CFDataRef cf_nkf_convert(__nonnull CFDataRef src, __nonnull CFStringRef opts,  CFIndex* _Nonnull  outLength);
CF_EXPORT CF_RETURNS_RETAINED __nullable CFStringRef cf_nkf_convert_to_utf8(__nonnull CFDataRef src,  __nonnull CFStringRef opts);
CF_EXPORT CF_RETURNS_RETAINED __nullable CFStringRef cf_nkf_guess(__nonnull CFDataRef src);