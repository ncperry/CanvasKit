//
//  CKIActivityStreamItemTests.swift
//  CanvasKit
//
//  Created by Nathan Lambson on 7/10/14.
//  Copyright (c) 2014 Instructure. All rights reserved.
//

import UIKit
import XCTest

class CKIActivityStreamItemTests: XCTestCase {

    override func setUp() {
        super.setUp()
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }

    func testJSONModelConversion() {
        var activityStreamItemDictionary = Helpers.loadJSONFixture("activity_stream_item") as NSDictionary
        var streamItem = CKIActivityStreamMessageItem(fromJSONDictionary: activityStreamItemDictionary)
        
        var formatter = ISO8601DateFormatter()
        formatter.includeTime = true
    
        XCTAssertEqualObjects(streamItem.id, "1234", "Activity Stream Item id was not parsed correctly")
        
        XCTAssertEqualObjects(streamItem.title, "Stream Item Subject", "Activity Stream Item title was not parsed correctly")
        
        XCTAssertEqualObjects(streamItem.message, "This is the body text of the activity stream item. It is plain-text, and can be multiple paragraphs.", "Activity Stream Item message was not parsed correctly")

        XCTAssertEqualObjects(streamItem.courseID, "1", "Activity Stream Item courseID was not parsed correctly")
        
        XCTAssertEqualObjects(streamItem.groupID, "1", "Activity Stream Item groupID was not parsed correctly")
        
        var date = formatter.dateFromString("2011-07-13T09:12:00Z")
        XCTAssertEqualObjects(streamItem.createdAt, date, "Activity Stream Item createdAt date was not parsed correctly")
        
        date = formatter.dateFromString("2011-07-25T08:52:41Z")
        XCTAssertEqualObjects(streamItem.updatedAt, date, "Activity Stream Item updatedAt date was not parsed correctly")
        
        var url = NSURL.URLWithString("http://canvas.instructure.com/api/v1/foo")
        XCTAssertEqualObjects(streamItem.url, url, "Activity Stream Item url was not parsed correctly")

        url = NSURL.URLWithString("http://canvas.instructure.com/api/v1/foo")
        XCTAssertEqualObjects(streamItem.htmlURL, url, "Activity Stream Item htmlURL was not parsed correctly")
        
        XCTAssert(streamItem.isRead, "Activity Stream Item isRead was not parsed correctly")
        
       //Consider testing custom transformers at some point in time, which is probably never since we aren't doing it right now.
    }

    func testPerformanceExample() {
        // This is an example of a performance test case.
        self.measureBlock() {
            // Put the code you want to measure the time of here.
        }
    }

}
