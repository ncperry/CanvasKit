//
//  CKIAssignment.h
//  CanvasKit
//
//  Created by Jason Larsen on 8/22/13.
//  Copyright (c) 2013 Instructure. All rights reserved.
//

#import "CKILockableModel.h"

@class CKICourse;
@class CKISubmission;
@class CKIRubric;

typedef NS_ENUM(NSUInteger, CKIAssignmentScoringType) {
    CKIAssignmentScoringTypePoints,
    CKIAssignmentScoringTypePercentage,
    CKIAssignmentScoringTypePassFail,
    CKIAssignmentScoringTypeLetter,
    CKIAssignmentScoringTypeGPAScale,
    CKIAssignmentScoringTypeNotGraded
};


@interface CKIAssignment : CKILockableModel


#pragma mark - Assignment Info

/**
 The name of the assignment.
 */
@property (nonatomic, copy) NSString *name;

/**
* The index of the assignment in it's group.
*/
@property (nonatomic) NSInteger position;

/**
 The assignment description, in an HTML fragment.
 */
@property (nonatomic, copy) NSString *descriptionHTML;

/**
 The due date for the assignment. nil if no due date.
 
 @warning If this assignment has assignment overrides, use the date from
 the override instead.
 */
@property (nonatomic, strong) NSDate *dueAt;

/**
 The date after which the assignment is locked. nil if this assignment is
 never locked.

 @warning If this assignment has assignment overrides, use the date from
 the override instead.
 */
@property (nonatomic, strong) NSDate *lockAt;

/**
 The date the assignment is unlocked. nil if this assignment is
 never locked.
 
 @warning If this assignment has assignment overrides, use the date from
 the override instead.
 */
@property (nonatomic, strong) NSDate *unlockAt;

/**
 The ID of the course to which the assignment belongs.
 */
@property (nonatomic, copy) NSString *courseID;

/**
 The URL to the assignment's web page.
 */
@property (nonatomic, strong) NSURL *htmlURL;

/**
 List of the allowed extensions for file uploads.
 
 @note Only valid if submissionTypes includes "online_upload"
 */
@property (nonatomic, copy) NSArray *allowedExtensions;

/**
 The ID of the assignment's group.
 */
@property (nonatomic, copy) NSString *assignmentGroupID;

/**
 The ID of the assignment's group set.
 
 @note Only applies if this is a group assignment.
 */
@property (nonatomic, copy) NSString *groupCategoryID;

/**
 The assignment is muted.
 */
@property (nonatomic) BOOL muted;

/**
 Boolean indicating peer reviews are assigned automatically. If false, the teacher is expected to manually assign peer reviews.
 */
@property (nonatomic) BOOL automaticPeerReviews;

/**
 The assignment is published
 
 @note Only visible if 'enable draft' account setting is on
 */
@property (nonatomic) BOOL published;


#pragma mark - Grading


/**
 The maximum points possible for the assignment.
 */
@property (nonatomic) double pointsPossible;

/**
 If this is a group assignment, boolean flag indicating whether or
 not students will be graded individually.
 */
@property (nonatomic) BOOL gradeGroupStudentsIndividually;

/**
 The type of grading the assignment receives; one of "pass_fail",
 "percent", "letter_grade", "points"
 */
@property (nonatomic, copy) NSString *gradingType;

/**
 The type of score the assignment submissions receive
 */
@property (nonatomic, assign) CKIAssignmentScoringType scoringType;

#pragma mark - Submissions



/**
 The types of submissions allowed for this assignment list
 containing one or more of the following: "discussion_topic",
 "online_quiz", "on_paper", "none", "external_tool",
 "online_text_entry", "online_url", "online_upload"
 "media_recording"
 */
@property (nonatomic, copy) NSArray *submissionTypes;


//Whether or not the assignment is locked for the user
@property (nonatomic) BOOL lockedForUser;

/**
 Submission for the assignment.
 */
@property (nonatomic, copy) CKISubmission *submission;

/**
 If the requesting user has grading rights, the number of
 submissions that need grading.
 */
@property (nonatomic) NSUInteger needsGradingCount;


#pragma mark - Rubric

/**
 Array of CKIRubricCriterion
 */
@property (nonatomic, strong) CKIRubric *rubric;


#pragma mark - Peer Review

/**
 Boolean indicating if peer reviews are required for this assignment
 */
@property (nonatomic) BOOL peerReviewRequired;

/**
 Boolean indicating peer reviews are assigned automatically.
 If false, the teacher is expected to manually assign peer reviews.
 */
@property (nonatomic) BOOL peerReviewsAutomaticallyAssigned;

/**
 Integer representing the amount of reviews each user is assigned.
 
 @note This is NOT valid unless you have peerReviewsAutomaticallyAssigned.
 */
@property (nonatomic) NSInteger peerReviewsAutomaticallyAssignedCount;

/**
 Date the reviews are due by. Must be a date that occurs after the default
 due date. If blank, or date is not after the assignment's due date, the
 assignment's due date will be used.
 
 @note This is NOT valid unless you have automatic_peer_reviews set to true.
 */
@property (nonatomic, strong) NSDate *peerReviewDueDate;

@end
