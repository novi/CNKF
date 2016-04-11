//
//  CNKFTests.m
//  CNKFTests
//
//  Created by ito on 12/27/15.
//  Copyright © 2015 Yusuke Ito. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "nkf_bridge.h"

@interface CNKFTests : XCTestCase

@end

@implementation CNKFTests

- (void)setUp {
    [super setUp];
}

- (void)tearDown {
    [super tearDown];
}

- (void)testConvert {
    NSString* input = @"あいうえお漢字123🍣\\¥¥¥";
    
    NSData* inputData = ([input dataUsingEncoding:NSUTF8StringEncoding]);
    
    CFIndex outLength = 0;
    CFDataRef outData = cf_nkf_convert((__bridge CFDataRef)(inputData), (__bridge CFStringRef)@"-w", &outLength);
    
    NSLog(@"\n%@->\n%@, %lu, %lu", inputData, outData, CFDataGetLength(outData), outLength);
    
    NSString* outString = [[NSString alloc] initWithData:(__bridge NSData * _Nonnull)(outData) encoding:NSUTF8StringEncoding];
    
    NSLog(@"%@->%@", input, outString);
    outString = [outString stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"\0"]];
    
    //XCTAssertTrue([inputData isEqualToData:(__bridge NSData * _Nonnull)(outData)]);
    XCTAssertTrue([input compare:outString] == NSOrderedSame);
    
    CFRelease(outData);
}

- (void)testConvertUTF8 {
    NSString* input = @"あいうえお漢字123🍣\\¥¥¥";
    
    NSData* inputData = ([input dataUsingEncoding:NSUTF8StringEncoding]);
    
    CFStringRef outString = cf_nkf_convert_to_utf8((__bridge CFDataRef)(inputData), (__bridge CFStringRef)@"-w");
    
    NSLog(@"%@->%@", input, outString);
    
    XCTAssertTrue([input compare:(__bridge NSString * _Nonnull)outString] == NSOrderedSame);
}

- (void)testGuessUTF8Input {
    NSString* input = @"あいうえお漢字123🍣\\¥¥¥";
    NSData* inputData = ([input dataUsingEncoding:NSUTF8StringEncoding]);
    CFStringRef code = cf_nkf_guess((__bridge CFDataRef _Nonnull)(inputData));
    
    NSLog(@"%@", code);
    
    XCTAssertTrue([(__bridge NSString* _Nullable)(code) isEqualToString:@"UTF-8"]);
    
}


@end
