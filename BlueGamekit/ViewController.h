//
//  ViewController.h
//  BlueGamekit
//
//  Created by user on 5/5/13.
//  Copyright (c) 2013 user. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
@property (weak, nonatomic) IBOutlet UITableView *btList;
- (IBAction)bluetoothON;
- (IBAction)bluetoothOFF;
- (IBAction)scanDevices;
- (IBAction)clearList;
- (IBAction)A;

@end
