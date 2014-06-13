//
//  PSPDFInkAnnotation.h
//  PSPDFKit
//
//  Copyright (c) 2012-2014 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import "PSPDFAnnotation.h"

/// PDF Ink Annotation. (Free Drawing)
/// Lines are automatically transformed when the `boundingBox` is changed.
@interface PSPDFInkAnnotation : PSPDFAnnotation

/// Designated initializer.
- (id)init;

/// Array of arrays of boxed `CGPoints`.
/// Example: `annotation.lines = @[@[BOXED(CGPointMake(100,100)), BOXED(CGPointMake(100,200)), BOXED(CGPointMake(150,300))]]`;
/// @warning: After setting lines, the boundingBox will be automatically recalculated.
@property (nonatomic, copy) NSArray *lines;

/// The `UIBezierPath` will be dynamically crated from the lines array.
@property (nonatomic, copy, readonly) UIBezierPath *bezierPath;

/// Will return YES if this ink annotation is a PSPDFKit signature.
/// This is a proprietary extension - other viewer will not be able to detect this.
@property (nonatomic, assign) BOOL isSignature;

/// By default, setting the `boundingBox` will transform all points in the lines array.
/// Use this setter to manually change the `boundingBox` without changing lines.
- (void)setBoundingBox:(CGRect)boundingBox transformLines:(BOOL)transformLines;

/// Generate new line array by applying transform.
/// This is used internally when `boundingBox` is changed.
- (NSArray *)copyLinesByApplyingTransform:(CGAffineTransform)transform;

@end

// Helper to convert `UIBezierPath` into an array of points (of `CGPoints` inside `NSValues`).
NSArray *PSPDFBezierPathGetPoints(UIBezierPath *path);

// Calculates the bounding box from lines.
CGRect PSPDFBoundingBoxFromLines(NSArray *lines, CGFloat lineWidth);

// Returns a new set of lines, with transform applied.
NSArray *PSPDFCopyLinesByApplyingTransform(NSArray *lines, CGAffineTransform transform);

/// Convert point array to a bezier path.
UIBezierPath *PSPDFSplineWithPointArray(NSArray *pointArray);

// Will convert view lines to PDF lines (operates on every point)
// Get the `cropBox` and rotation from `PSPDFPageInfo`.
// bounds should be the size of the view.
NSArray *PSPDFConvertViewLinesToPDFLines(NSArray *lines, CGRect cropBox, NSUInteger rotation, CGRect bounds);

// Converts a single line of boxed `CGPoints`.
NSArray *PSPDFConvertViewLineToPDFLines(NSArray *line, CGRect cropBox, NSUInteger rotation, CGRect bounds);

// Will convert PDF lines to view lines (operates on every point)
NSArray *PSPDFConvertPDFLinesToViewLines(NSArray *lines, CGRect cropBox, NSUInteger rotation, CGRect bounds);
