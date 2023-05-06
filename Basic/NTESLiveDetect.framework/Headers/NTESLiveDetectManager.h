//
//  NTESLiveDetectManager.h
//  NTESLiveDetect
//
//  Created by Ke Xu on 2019/2/27.
//  Copyright © 2019 Ke Xu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  @abstract    枚举
 *
 *  @说明         NTESLDCompletionHandler    对象的参数，用于表示获取token的状态
 *
 *               NTESLDCheckPass            活体检测通过
 *               NTESLDCheckNotPass         活体检测不通过
 *               NTESLDOperationTimeout     操作超时，用户未在规定时间内完成动作
 *               NTESLDGetConfTimeout       活体检测获取配置信息超时
 *               NTESLDOnlineCheckTimeout   云端检测结果请求超时
 *               NTESLDOnlineUploadFailure  云端检测上传图片失败
 *               NTESLDNonGateway           网络未连接
 *               NTESLDSDKError             SDK内部发生错误
 *               NTESLDCameraNotAvailable   App未获取相机权限
 *
 *
 */
typedef NS_ENUM(NSUInteger, NTESLDStatus) {
    NTESLDCheckPass = 1,
    NTESLDCheckNotPass,
    NTESLDOperationTimeout,
    NTESLDGetConfTimeout,
    NTESLDOnlineCheckTimeout,
    NTESLDOnlineUploadFailure,
    NTESLDNonGateway,
    NTESLDSDKError,
    NTESLDCameraNotAvailable,
};

/**
*  @abstract    动作检测灵敏度枚举
*
*               NTESSensitEasy            动作检测容易通过
*               NTESSensitNormal         动作检测默认状态
*               NTESSensitHard             动作检测不容易通过
*/
typedef NS_ENUM(NSUInteger, NTESSensit) {
    NTESSensitEasy = 0,
    NTESSensitNormal,
    NTESSensitHard,
};



NS_ASSUME_NONNULL_BEGIN

/**
 @说明        获取活体检测结果的回调
 */
typedef void(^NTESLDCompletionHandler)(NTESLDStatus status, NSDictionary * _Nullable params);

/**
 @说明        返回所有动作的序列码
             动作状态表示：0——正面，1——右转，2——左转，3——张嘴，4——眨眼
 */
typedef void(^NTESLDAcitionsHandler)(NSDictionary *params);

/**
 @说明        正在进行云端检测
 */
typedef void(^ __nullable NTESLDCheckingHandler)(void);


/**
 @说明        动作检测监听，可在App内做相应提示
             动作检测的数据结构：@{@"action" : @{1 : YES}}  或者 @{@"exception" : @"1"}  二者只可能出现其中之一。
             使用[notification.userInfo objectForKey:@"action"]获取当前动作状态，NSDictionary类型
             key:当前执行的动作状态 0——正面，1——右转，2——左转，3——张嘴，4——眨眼, -1——未检测到完整人脸
             value:对应动作的完成状态 NO——未完成 YES——已完成
             使用NSString *exception =  [notification.userInfo objectForKey:@"exception"]获取异常，NSString类型
             exception:当前的异常状态 1——保持面部在框内，2——环境光线过暗，3——环境光线过亮，4——请勿抖动手机
 */
extern NSString * _Nonnull const NTESLDNotificationStatusChange;

@interface NTESLiveDetectManager : NSObject

/**
 初始化检测对象
 
 @param imageView               传入放置检测活体的imageView对象，imageView宽高比需设定为3:4
 @param sensit                      请传入活体检灵敏度类型。
 */
- (instancetype)initWithImageView:(UIImageView *)imageView
                 withDetectSensit:(NTESSensit)sensit;

/**
 设置活体检测的超时时间
 
 @param timeout                 请传入10-120范围内的时间值，默认30，单位s
 */
- (void)setTimeoutInterval:(NSTimeInterval)timeout;

/**
 开始活体检测
 
 @param businessID              产品编号
 @param actionsHandler          活体检测动作序列号的回调
 @param checkingHandler          活体检测正在进行云端检测的回调
 @param completionHandler       活体检测结果的回调，结果状态见NTESLDStatus枚举类型
 */
- (void)startLiveDetectWithBusinessID:(NSString *)businessID
                       actionsHandler:(NTESLDAcitionsHandler)actionsHandler
                      checkingHandler:(NTESLDCheckingHandler)checkingHandler
                    completionHandler:(NTESLDCompletionHandler)completionHandler;

/**
 开始活体检测
 
 @param businessID              产品编号
 @param configURL                   URL 域名集合，可传多个域名，实现域名的重试机制(例如：先使用第一个域名，如果第一个域名失败，就取第二个域名以此类推)，若传nil，使用默认值
 @param actionsHandler          活体检测动作序列号的回调
 @param checkingHandler          活体检测正在进行云端检测的回调
 @param completionHandler       活体检测结果的回调，结果状态见NTESLDStatus枚举类型
 */
- (void)startLiveDetectWithBusinessID:(NSString *)businessID
                            configURL:(NSArray<NSString *> * _Nullable)configURL
                       actionsHandler:(NTESLDAcitionsHandler)actionsHandler
                      checkingHandler:(NTESLDCheckingHandler)checkingHandler
                    completionHandler:(NTESLDCompletionHandler)completionHandler;

/**
 停止活体检测                     ⚠️ 请在主线程中调用
 
 @abstract                      调用时机：
                                1、在活体检测结果的回调里（NTESLDCompletionHandler）调用
                                2、未完成活体检测，需要中止时调用
 */
- (void)stopLiveDetect;

/**
 SDK版本号获取
 */
- (NSString *)getSDKVersion;

@end

NS_ASSUME_NONNULL_END
