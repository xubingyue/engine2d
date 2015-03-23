//
//  ViewController.m
//  engine2d
//
//  Created by TTc on 14-6-16.
//  Copyright (c) 2014年 liutianshx. All rights reserved.
//

#import "ViewController.h"
#import "winfw.h"
static ViewController *_controller = nil;

@interface ViewController ()

@property(strong,nonatomic)EAGLContext *context;
@end

@implementation ViewController

-(id)init{
    _controller = [super init];
    return _controller;
}

+(ViewController*)getLastInstance{
    return _controller;
}


-(void)viewDidLoad{
    [super viewDidLoad];
    self.context = [[EAGLContext alloc]initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if(!self.context){
        NSLog(@"Failed to create ES context");
        exit(1);
    }
    GLKView *view = (GLKView*)self.view;
    view.context = self.context;
    [EAGLContext setCurrentContext:_context];
    
    
    CGFloat screenScale = [[UIScreen mainScreen] scale];
    CGRect bounds = [UIScreen mainScreen].bounds;
    printf("screenScale: %f\n", screenScale);
    printf("bounds: x:%f y:%f w:%f h:%f\n",
           bounds.origin.x, bounds.origin.y,
           bounds.size.width, bounds.size.height);
    
    NSString *appFolderPath = [[NSBundle mainBundle]resourcePath];
    const char* folder = [appFolderPath UTF8String];
    
    engine2d_win_init(bounds.origin.x, bounds.origin.y, bounds.size.width, bounds.size.height, screenScale, folder);

}

-(void)viewDidUnload
{
    [super viewDidUnload];
    
    NSLog(@"viewDidUnload");
    if ([self isViewLoaded] &&  ([[self view] window] == nil)) {
        self.view = nil;
        if([EAGLContext currentContext] == self.context){
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }
}

//MARK: 逻辑循序
- (void)update
{
    engine2d_win_update();
}

-(void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    engine2d_win_frame();
}

//MARK: TOUCH
-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    for(UITouch *touch in touches){
        CGPoint p = [touch locationInView:touch.view];
        engine2d_win_touch(p.x, p.y, TOUCH_BEGIN);
    }
}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    for(UITouch *touch in touches){
        CGPoint p = [touch locationInView:touch.view];
        engine2d_win_touch(p.x, p.y, TOUCH_MOVE);
    }

}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    for(UITouch *touch in touches) {
        CGPoint p = [touch locationInView:touch.view];
        engine2d_win_touch(p.x, p.y, TOUCH_END);
    }
}



-(BOOL)prefersStatusBarHidden
{
    return YES;
}


- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight;
    
}

- (void)dealloc
{
    //lejoy_exit();
    _controller = nil;
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}


@end
