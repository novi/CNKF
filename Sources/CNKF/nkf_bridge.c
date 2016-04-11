
#ifndef CF_NKF_H
#define CF_NKF_H

#include <CoreFoundation/CoreFoundation.h>

#undef getc
#undef ungetc
#define getc(f)         (input_ctr>=i_len?-1:input[input_ctr++])
#define ungetc(c,f)     input_ctr--

#define INCSIZE         32

#undef putchar
#undef TRUE
#undef FALSE
#define putchar(c)      cf_nkf_putchar(c)

static UInt8 *output;
static const UInt8 *input;

static CFIndex input_ctr;
static CFIndex i_len;

static CFIndex output_ctr;
static CFMutableDataRef outputData;

static CFIndex incsize = INCSIZE;

static int
cf_nkf_putchar(unsigned int c)
{
    if (outputData == NULL) return c;
    
    if (output_ctr >= CFDataGetLength(outputData)) {
        CFDataIncreaseLength(outputData, incsize);
        incsize *= 2;
    }
    output[output_ctr++] = c;
    
    return c;
}

#define PERL_XS 1

#include "nkf/config.h"
#include "nkf/utf8tbl.c"
#include "nkf/nkf.c"

 CF_RETURNS_RETAINED __nonnull CFDataRef cf_nkf_convert(__nonnull CFDataRef src, __nonnull CFStringRef opts,  CFIndex* _Nonnull  outLength)
{
    
    reinit();
    incsize = INCSIZE;
    
    CFDataRef optsData = CFStringCreateExternalRepresentation(NULL, opts, kCFStringEncodingUTF8, 0);
    CFMutableDataRef optsDataM = CFDataCreateMutableCopy(NULL, CFDataGetLength(optsData), optsData);
    options(CFDataGetMutableBytePtr(optsDataM));
    
    input_ctr = 0;
    input = CFDataGetBytePtr(src);
    i_len = CFDataGetLength(src);
    
    outputData = CFDataCreateMutable(NULL, i_len*3 + 10);
    output = CFDataGetMutableBytePtr(outputData);
    
    output_ctr = 0;
    *output    = '\0';
    
    kanji_convert(NULL);
    
    CFRelease(optsData);
    CFRelease(optsDataM);
    
    *outLength = output_ctr;
    
    return outputData;
}

CF_RETURNS_RETAINED __nullable CFStringRef cf_nkf_convert_to_utf8(__nonnull CFDataRef src,  __nonnull CFStringRef opts)
{
    CFIndex outLength = 0;
    CFDataRef data = cf_nkf_convert(src, opts, &outLength);
    CFStringRef str = CFStringCreateWithBytes(NULL, CFDataGetBytePtr(data), outLength, kCFStringEncodingUTF8, true);
    CFRelease(data);
    return str;
}

CF_RETURNS_RETAINED __nullable CFStringRef cf_nkf_guess(__nonnull CFDataRef src)
{
    reinit();
    incsize = INCSIZE;
    
    input_ctr = 0;
    input = CFDataGetBytePtr(src);
    i_len = CFDataGetLength(src);
    
    outputData = NULL; // no output data
    
    kanji_convert(NULL);
    
    const char* code = get_guessed_code();
    return CFStringCreateWithCString(NULL, code, kCFStringEncodingUTF8);
}


#endif

