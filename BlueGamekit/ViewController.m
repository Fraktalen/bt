//
//  ViewController.m
//  BlueGamekit
//
//  Created by user on 5/5/13.
//  Copyright (c) 2013 user. All rights reserved.
//

#import "ViewController.h"
#import "BluetoothManager.h"
#import "BluetoothDevice.h"

@interface ViewController ()
@end

@implementation ViewController

BluetoothManager *btManager = nil;

static void MyCallBack(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo){
    NSLog(@"CFN Name :%@ Data : %@", name, userInfo);
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // setup bluetooth interface
    btManager = [BluetoothManager sharedInstance];
    
    // setup bluetooth notifications
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(deviceDiscovered:) name:@"BluetoothDeviceDiscoveredNotification" object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(bluetoothAvailabilityChanged:) name:@"BluetoothAvailabilityChangedNotification" object:nil];
    
    // global notification explorer
    CFNotificationCenterRef c = CFNotificationCenterGetLocalCenter();
    CFNotificationCenterAddObserver
    (
        c,
        NULL,
        &MyCallBack,
        NULL,
        NULL,
        CFNotificationSuspensionBehaviorDeliverImmediately
     );
} // end viewDidLoad

// Bluetooth notifications
- (void)bluetoothAvailabilityChanged:(NSNotification *)notification {
    NSLog(@"NOTIFICATION:bluetoothAvailabilityChanged called. BT State: %d", [btManager enabled]);
}

- (void)deviceDiscovered:(NSNotification *) notification{
    BluetoothDevice *bt = [notification object];
    
    NSLog(@"NOTIFICATION :deviceDiscovered: %@ %@", bt.name, bt.address);
    

    /*
    // create a new list item
    BTListDevItem *item = [[[BTListDevItem alloc] init];
    initWithName:bt.name description:bt.address type:0 btdev:bt];
    
    NSArray *btDevItems = [[NSArray alloc] init];
    // add it to the list
    NSMutableArray *tempArray = [[NSMutableArray alloc] initWithArray:btDevItems];
    [tempArray addObject:(item)];
    btDevItems = tempArray;
    [UITableView reloadData];
     */
}

// Interface action bt on
- (IBAction)bluetoothON{
    NSLog(@"bluetoothON called");
    [btManager setPowered:YES];
    [btManager setEnabled:YES];
}
// Interface action bt off
- (IBAction)bluetoothOFF{
    NSLog(@"bluetooth OFF called");
    [btManager setPowered:NO];
    [btManager setEnabled:NO];
}

- (IBAction)scanDevices
{
    if ([btManager enabled])
    {
        // clear listview
        [self clearList];
        // start scan
        [btManager setDeviceScanningEnabled:YES];
    } else {
        NSLog(@"Error, turn on bluetooth first");
    }
}

- (IBAction)clearList {
    // TODO
}

- (IBAction)A {
    NSLog(@"A");
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
