/** @defgroup G_BORICA Borica SDK
 Provides universal access to all supported devices' functions.
 In order to use one of the supported accessories in your program, several steps have to be performed:
 - Include BoricaSDK.h and libBorica.a in your project.
 - Go to Frameworks and add ExternalAccessory framework
 - Edit your program plist file, add new element and select "Supported external accessory protocols" from the list, then add the protocol names of the accessories you want to connect to:
 <br>For Pinpad: com.datecs.ppad
 <br>For Fiscal printers connected directly via bluetooth: com.datecs.printer.fiscal
 @{
 */
#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <ExternalAccessory/ExternalAccessory.h>
/**
 * Transaction type
 */
typedef NS_ENUM(int, TRANSACTION_TYPE)
{
    /**
     Purchase
     */
    PURCHASE=1,
    /**
     Purchase with cashback
     */
    PURCHASE_CASHBACK,
    /**
     Purchase with reference
     */
    PURCHASE_REFERENCE,
    /**
     Cash advance
     */
    CASH_ADVANCE,
    /**
     Authorization
     */
    AUTHORIZATION,
    /**
     Authorization  confirm
     */
    AUTORIZATION_CONFIRM
    ,
    /**
     Purchase void
     */
    VOID_PURCHASE,
    /**
     Cash advance void
     */
    VOID_CASH_ADVANCE,
    /**
     Authorization void
     */
    VOID_AUTHORIZATION,
    /**
     End of day
     */
    END_OF_DAY,
    /*
     Balance inquiry
     */
    BALANCE_INQUIRY,
    /**
     Loyalty spend
     */
    LOYALTY_SPEND,
    /**
     Void loyalty spend
     */
    VOID_LOYALTY_SPEND,
    /**
     Test connection
     */
    TEST_CONNECTION,
    /**
     Update
     */
    TERMINAL_UPDATE,
    
    /*
     PurchaseReturn
     */
    PURCHASE_RETURN = 22,
    /*
     Universal Reversal Advice
     */
    UNIVERSAL_REVERSAL_ADVICE = 21,
    /*
     Universal reversal
     */
    UNIVERSAL_REVERSAL = 18,
    /*
     KeyChange
     */
    KEY_CHANGE = 20,
    GET_PINPAD_STATUS = 26,
};

/**
 Pinpad Type
 */
typedef NS_ENUM(int, MENU_TYPE)
{
    MENU_TYPE_TRADING=0,
    MENU_TYPE_TRADING_REF,
    MENU_TYPE_TRADING_CASHBACK,
    MENU_TYPE_HOTEL_RENT_A_CAR,
    MENU_TYPE_BAR_RESTAURANT,
    MENU_TYPE_BANK_CHANGE,
    MENU_TYPE_TEST,
};

#define DTDeviceInfo DeviceInfo

/**
 Device information
 */
@interface DeviceInfo : NSObject
/**
 Battery voltage
 */
@property (copy) NSString *model;
/**
 Battery capacity in percents
 */
@property (copy) NSString *serialNumber;
/**
 Battery health in percents or 0 if unsupported
 */
@property (copy) NSString *version;
/**
 Battery maximum capacity in MA/H or 0 if unsupported
 */
@property (copy) NSString *terminalID;
/**
 Charging state
 */
@property (assign) MENU_TYPE menuType;

@end

#ifndef STRUCTURES_DEFINED
#define STRUCTURES_DEFINED

/**
 Battery information
 */
typedef NS_ENUM(int, BATTERY_CHIPS)
{
    BATTERY_CHIP_NONE=0,
    BATTERY_CHIP_BQ27421,
};

/**
 Battery information
 */
@interface DTBatteryInfo : NSObject
/**
 Battery voltage
 */
@property (assign) float voltage;
/**
 Battery capacity in percents
 */
@property (assign) int capacity;
/**
 Battery health in percents or 0 if unsupported
 */
@property (assign) int health;
/**
 Battery maximum capacity in MA/H or 0 if unsupported
 */
@property (assign) int maximumCapacity;
/**
 Charging state
 */
@property (assign) bool charging;

/**
 Battery chip type
 */
@property (assign) BATTERY_CHIPS batteryChipType;

/**
 Extended battery information specific to the chip used
 */
@property (copy) NSDictionary *extendedInfo;

@end

/**
 * Tags used in the transaction
 */
typedef NS_ENUM(UInt64, TAG)
{
    /**
     * Amount, Authorised (Binary)
     * <p>
     * Authorised amount of the transaction (excluding adjustments).
     * </p>
     */
    TAG_81_AMOUNT_AUTHORISED = 0x81,
    /**
     * Amount, Other (Binary)
     * <p>
     * Secondary amount associated with the transaction representing a cashback amount.
     * </p>
     */
    TAG_9F04_AMOUNT_OTHER = 0x9F04,
    /**
     * Transaction Date
     * <p>
     * Local date that the transaction was authorised.
     * </p>
     */
    TAG_9A_TRANSACTION_DATE = 0x9A,
    /**
     * Transaction Time
     * <p>
     * Local time that the transaction was authorised.
     * </p>
     */
    TAG_9F21_TRANSACTION_TIME = 0x9F21,
    /**
     * Application Identifier (AID) – terminal
     * <p>
     * Identifies the application as described in ISO/IEC 7816-5.
     * </p>
     */
    TAG_9F06_APPLICATION_IDENTIFIER = 0x9F06,
    /**
     * Terminal Identification
     * <p>
     * Designates the unique location of a terminal at a merchant.
     * </p>
     */
    TAG_9F1C_TERMINAL_ID = 0x9F1C,
    /**
     * Merchant Identifier
     * <p>
     * When concatenated with the Acquirer Identifier, uniquely identifies a given merchant.
     * </p>
     */
    TAG_9F16_TERMINAL_MERCHANT_ID = 0x9F16,
    /**
     * Application Cryptogram
     * <p>
     * Cryptogram returned by the ICC in response of the GENERATE AC command.
     * </p>
     */
    TAG_9F26_APPLICATION_CRYPTOGRAM = 0x9F26,
    /**
     * Transaction Currency Code
     * <p>
     * Indicates the currency code of the transaction according to ISO 4217.
     * </p>
     */
    TAG_5F2A_TERMINAL_CURRENCY_CODE = 0x5F2A,
    /**
     * Transaction Sequence Counter
     * <p>
     * Counter maintained by the terminal that is incremented by one for each transaction.
     * </p>
     */
    TAG_9F41_TRANSACTION_SEQUENCE_COUNTER = 0x9F41,
    /**
     * Cardholder Name
     * <p>
     * Indicates cardholder name according to ISO 7813.
     * </p>
     */
    TAG_5F20_CARDHOLDER_NAME = 0x5F20,
    
    /**
     * Card Scheme
     * <p>
     * String representation of the card scheme.
     * </p>
     */
    TAG_DF00_CARD_SCHEME = 0xDF00,
    /**
     * Transaction Reference Number (RRN)
     * <p>
     * The reference number is returned from Borica authorization server.
     * </p>
     */
    TAG_DF01_TRANSACTION_REFERENCE_NUMBER = 0xDF01,
    /**
     * Transaction Authorization Code (AC)
     * <p>
     * The authorization number is returned from Borica authorization server.
     * </p>
     */
    TAG_DF02_TRANSACTION_AUTHORIZATION_CODE = 0xDF02,
    /**
     * Transaction Reference Code.
     * <p>
     * Contains reference code on purchase with reference transaction.
     * </p>
     */
    TAG_DF03_TRANSACTION_REFERENCE = 0xDF03,
    /**
     * Secondary Amount, Authorised (Binary)
     * <p>
     * Authorised amount of the transaction (excluding adjustments) in different currency.
     * </p>
     */
    TAG_DF04_SECONDARY_AMOUNT = 0xDF04,
    /**
     * Transaction Result Code
     * <p>
     * Transaction result codes are defined in Borica application documentation.
     * </p>
     */
    TAG_DF05_TRANSACTION_RESULT = 0xDF05,
    /**
     * Transaction Error Code
     * <p>
     * Transaction error codes are defined in Borica application documentation.
     * </p>
     */
    TAG_DF06_TRANSACTION_ERROR_CODE = 0xDF06,
    /**
     * Host Reference Number
     * <p>
     * Reference number as returned from authorization server.
     * </p>
     */
    TAG_DF07_HOST_REFERENCE_NUMBER = 0xDF07,
    /** Host Authorization Code
     * <p>
     * Authorization code as returned from authorization server.
     * </p>
     */
    TAG_DF08_HOST_AUTHORIZATION_CODE = 0xDF08,
    /**
     * Host Error Code
     * <p>
     * Host error codes are defined in Borica documentation.
     * </p>
     */
    TAG_DF09_HOST_ERROR_CODE = 0xDF09,
    /**
     * Masked Application Primary Account Number (PAN)
     * <p>
     * Masked valid cardholder account number.
     * </p>
     */
    TAG_DF0A_MASKED_PAN = 0xDF0A,
    /**
     * Loyalty Points
     * <p>
     * Available loyalty points.
     * </p>
     */
    TAG_DF0B_LOYALTY_POINTS = 0xDF0B,
    /**
     * Transaction Type (Borica)
     * <p>
     * Transaction type codes are defined in Borica application documentation.
     * </p>
     */
    TAG_DF10_TRANSACTION_TYPE = 0xDF10,
    /**
     * Transaction Timeout Type
     * <p>
     * This tag contains info if transaction was unsuccessful and then later sent to server
     * </p>
     */
    TAG_DF12_TRANSACTION_TO_TYPE = 0xDF12,
    /**
     * Terminal Secondary Currency Name
     * <p>
     * The name of the secondary currency.
     * </p>
     */
    TAG_DF19_TERMINAL_SECONDARY_CURRENCY_NAME = 0xDF19,
    /**
     * CVM Signature
     * <p>
     * A numeric value that indicates whether signature is required or not.
     * </p>
     */
    TAG_DF23_CVM_SIGNATURE = 0xDF23,
    /**
     * Secondary Cashback Amount, (Binary)
     * <p>
     * Secondary amount associated with the transaction representing a cashback amount in
     * different currency.
     * </p>
     */
    TAG_DF24_CASHBACK = 0xDF24,
    /**
     * Payment interface.
     * <p>
     * The type of interface used to accomplished the transaction.
     * </p>
     */
    TAG_DF25_PAYMENT_INTERFACE = 0xDF25,
    /**
     * Terminal Currency Format
     * <p>
     * Two bytes that represent number of digits before and after digits separator.
     * </p>
     */
    TAG_DF26_TERMINAL_CURRENCY_FORMAT = 0xDF26,
    /**
     * Terminal Currency Name
     * <p>
     * The name of the primary currency.
     * </p>
     */
    TAG_DF27_TERMINAL_CURRENCY_NAME = 0xDF27,
    /**
     * Terminal Merchant Phone
     * <p>
     * Merchant phone number as provided from TMS system.
     * </p>
     */
    TAG_DF28_TERMINAL_MERCHANT_PHONE = 0xDF28,
    /**
     * Terminal Merchant Post Code
     * <p>
     * Merchant post code (ZIP) as provided from TMS system.
     * </p>
     */
    TAG_DF29_TERMINAL_MERCHANT_POST_CODE = 0xDF29,
    /**
     * Terminal Merchant Title (EN)
     * <p>
     * Merchant title in English language as provided from TMS system.
     * </p>
     */
    TAG_DF2A_TERMINAL_MERCHANT_TITLE_EN = 0xDF2A,
    /**
     * Terminal Merchant Address (EN)
     * <p>
     * Merchant address in English language as provided from TMS system.
     * </p>
     */
    TAG_DF2B_TERMINAL_MERCHANT_ADDRESS_EN = 0xDF2B,
    /**
     * Terminal Merchant City (EN)
     * <p>
     * Merchant city in English language as provided from TMS system.
     * </p>
     */
    TAG_DF2C_TERMINAL_MERCHANT_CITY_EN = 0xDF2C,
    /**
     * Terminal Merchant Name (EN)
     * <p>
     * Merchant name in English language as provided from TMS system.
     * </p>
     */
    TAG_DF2D_TERMINAL_MERCHANT_NAME_EN = 0xDF2D,
    /**
     * Terminal Merchant Title (BG)
     * <p>
     * Merchant title in Bulgarian language as provided from TMS system.
     * </p>
     */
    TAG_DF2E_TERMINAL_MERCHANT_TITLE_BG = 0xDF2E,
    /**
     * Terminal Merchant Address (BG)
     * <p>
     * Merchant address in Bulgarian language as provided from TMS system.
     * </p>
     */
    TAG_DF2F_TERMINAL_MERCHANT_ADDRESS_BG = 0xDF2F,
    /**
     * Terminal Merchant City (BG)
     * <p>
     * Merchant city in Bulgarian language as provided from TMS system.
     * </p>
     */
    TAG_DF30_TERMINAL_MERCHANT_CITY_BG = 0xDF30,
    /**
     * Terminal Merchant Name (BG)
     * <p>
     * Merchant name in Bulgarian language as provided from TMS system.
     * </p>
     */
    TAG_DF31_TERMINAL_MERCHANT_NAME_BG = 0xDF31,
    /**
     * Card scheme (Contactless).
     * <p>
     * The type of card scheme used to accomplished the transaction.
     * <p/>
     */
    TAG_DF60_CL_CARD_SCHEME = 0xDF60,
    /**
     * Transaction batch number.
     * <p>
     * The number of batch in which this transaction is created.
     * </p>
     */
    TAG_DF61_TRANSACTION_BATCH_NUMBER = 0xDF61,
    /**
     * Interface Identifier
     * <p>
     * The type of interface and operation used to accomplished the transaction.
     * </p>
     */
    TAG_DF62_INTERFACE_IDENTIFIER = 0xDF62,
    /**
     * Purchase service (tip)
     * <p>
     * The service adjustment to the purchase.
     * </p>
     */
    TAG_DF63_SERVICE = 0xDF63,
    /**
     * Secondary purchase service (tip)
     * <p>
     * The secondary service adjustment to the purchase.
     * </p>
     */
    TAG_DF64_SECONDARY_SERVICE = 0xDF64,
    /*
     payment system
     */
    TAG_DF79_ISSUER_ID = 0xDF79,
    /*
     RN
     */
    TAG_DF13_RN = 0xDF13,
    TAG_1A_PINPAD_STATUS = 0x001A,
};

/**
 * Transaction result
 */
typedef NS_ENUM(int, TRANSACTION_RESULT)
{
    /**
     Transaction was approved
     */
    APPROVED = 0,
    /**
     Transaction was denied
     */
    DECLINED = 1,
    /**
     Transaction error
     */
    ERROR = 2,
};


/**
 * Defines payment interface types.
 */
typedef NS_ENUM(int, PAYMENT_INTERFACE)
{
    /**
     * Unknown
     */
    PAYMENT_INTERFACE_UNKNOWN = -1,

    /**
     * Chip interface is used.
     */
    PAYMENT_INTERFACE_CHIP = 0,

    /**
     * Contactless interface is used.
     */
    PAYMENT_INTERFACE_CONTACTLESS = 1,

    /**
     * Magnetic stripe interface is used.
     */
    PAYMENT_INTERFACE_MAGNETIC_STRIPE = 2,

    /**
     * Manual card entry is used.
     */
    PAYMENT_INTERFACE_MANUAL_ENTRY = 3,
};

/**
 * Defines contactless card scheme identifiers.
 */
typedef NS_ENUM(int, CONTACTLESS_CARD_SCHEME)
{
    /**
     * Unknown
     */
    CONTACTLESS_CARD_SCHEME_UNKNOWN = -1,

    /**
     * Visa Asia Pacific contactless card.
     */
    CONTACTLESS_CARD_SCHEME_VISA_ASIA_PACIFIC = 0x01,
    /**
     * Mastercard PayPass contactless card.
     */
    CONTACTLESS_CARD_SCHEME_MASTERCARD_PAYPASS = 0x02,
    /**
     * Visa contactless card.
     */
    CONTACTLESS_CARD_SCHEME_VISA = 0x03,
    /**
     * American Express contactless card.
     */
    CONTACTLESS_CARD_SCHEME_AMEX = 0x04,
    /**
     * JCB contactless card.
     */
    CONTACTLESS_CARD_SCHEME_JCB = 0x05,
    /**
     * Discover contactless card.
     */
    CONTACTLESS_CARD_SCHEME_DISCOVER = 0x06,
};

#endif //STRUCTURES_DEFINED


/**
 Provides universal access to all supported devices' functions.
 In order to use one of the supported accessories in your program, several steps have to be performed:
 - Include BoricaSDK.h and libBorica.a in your project.
 - Go to Frameworks and add ExternalAccessory framework
 - Edit your program plist file, add new element and select "Supported external accessory protocols" from the list, then add the protocol names of the accessories you want to connect to:
 <br>For Pinpad: com.datecs.ppad
 <br>For Fiscal printers connected directly via bluetooth: com.datecs.printer.fiscal
 */
@interface Borica : NSObject


/**
 Creates and initializes new class instance or returns already initalized one. Use this function, if you want to access the class from different places
 @return shared class instance
 **/
+(id)instance;

/**
 Allows unlimited delegates to be added to a single class instance. This is useful in the case of global
 class and every view can use addDelegate when the view is shown and removeDelegate when no longer needs to monitor events
 @param newDelegate the delegate that will be notified of events
 **/
-(void)addDelegate:(id)newDelegate;

/**
 Removes delegate, previously added with addDelegate
 @param newDelegate the delegate that will be no longer be notified of events
 **/
-(void)removeDelegate:(id)newDelegate;

/**
 Tries to connect to supported devices in the background, connection status notifications will be passed through the delegate.
 Once connect is called, it will automatically try to reconnect until disconnect is called. Note that "connect" call works in background and will notify the caller of connection success via connectionState delegate. Do not assume the library has fully connected to the device after this call, but wait for the notification.
 **/
-(void)connect;

/**
 Stops the sdk from trying to connect to supported devices and breaks existing connections.
 **/
-(void)disconnect;

/**
 Returns complete information about connected device
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return device information if function succeeded, nil otherwise
 */
-(DTDeviceInfo *)getDeviceInfo:(NSError **)error;

/**
 Returns complete information about device's battery. Currently this function is fully supported on Infinea-X and gives partial info when called for the rest of thee devices
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return battery information if function succeeded, nil otherwise
 */
-(DTBatteryInfo *)getBatteryInfo:(NSError **)error;

/**
 Simple test procedure to get a response from the pinpad
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)ping:(NSError **)error;

/**
 Starts transaction, the transaction result will be sent via transactionComplete delegate
 @param transactionType transaction type, one of the TRANSACTION_TYPE enum values
 @param data TLV array with required information like amount, reference code, etc. Needed values depend on transaction type
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)startTransaction:(TRANSACTION_TYPE)transactionType data:(NSData *)data error:(NSError **)error;

/**
 Ends transaction
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(NSData *)endTransaction:(NSError **)error;

/**
 Returns data associated with the last transaction
 @param tags the list of tags to read from the reports
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return the list of tags requested or nil if function failed
 */
-(NSData *)getReceiptTags:(NSData *)tags error:(NSError **)error;

/**
 Returns current pinpad Real Time Clock
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return device's current time if function succeeded, nil otherwise
 */
-(NSDate *)getRTC:(NSError **)error;

/**
 Set device's current Real Time Clock
 @param date date/time
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return TRUE if function succeeded, FALSE otherwise
 */
-(BOOL)setRTC:(NSDate *)date error:(NSError **)error;

/**
 Returns reports stored in the device
 @param tags the list of tags to read from the reports
 @param error pointer to NSError object, where error information is stored in case function fails. You can pass nil if you don't want that information
 @return an array of NSData objects, containign TLV structure with the tags of each report or nil if function failed
 */
-(NSArray *)getReports:(NSData *)tags error:(NSError **)error;


-(NSArray<CBPeripheral *> *)btleDiscoverSupportedDevicesAndStopOnFound:(BOOL)stopOnFound error:(NSError **)error;
-(BOOL)btleDiscoverStop;
-(BOOL)btleConnectToDevice:(CBPeripheral *)aPeripheral error:(NSError **)error;
-(BOOL)btleConnectToDeviceAndGetStreams:(CBPeripheral *)aPeripheral error:(NSError **)error;
-(BOOL)btleDisconnect:(CBPeripheral *)aPeripheral error:(NSError **)error;

/**
 Adds delegate to the class
 **/
@property(assign) id delegate;

/**
 Provides a list of currently registered delegates
 */
@property(readonly) NSMutableArray *delegates;

/**
 Returns current connection state
 **/
@property(readonly) BOOL connected;
/**
 Returns connected device name
 **/
@property(readonly) NSString *deviceName;
/**
 Returns connected device model
 **/
@property(readonly) NSString *deviceModel;
/**
 Returns connected device firmware version
 **/
@property(readonly) NSString *firmwareRevision;
/**
 Returns connected device firmware version in format MAJOR*100+MINOR, i.e. version 1.15 will be returned as 115
 **/
@property(readonly) int firmwareRevisionNumber;
/**
 Returns connected device hardware version
 **/
@property(readonly) NSString *hardwareRevision;
/**
 Returns connected device serial number
 **/
@property(readonly) NSString *serialNumber;

/**
 SDK version number in format MAJOR*100+MINOR, i.e. version 1.15 will be returned as 115
 */
@property(readonly) int sdkVersion;

/**
 SDK build date
 */
@property(readonly) NSDate *sdkBuildDate;

/**
 Contains currently connected bluetooth LE devices or empty array if no connected devices are found
 **/
@property(readonly) NSArray<CBPeripheral *> *btleConnectedDevices;

@end

/**
 Protocol describing various notifications that BoricaSDK can send.
 @ingroup G_BORICA
 */
@protocol BoricaDelegates <NSObject>
@optional

/**
 Called when borica compatible pinpad is connected
 @param device borica sdk instance
 */
-(void)deviceConnected:(Borica *)device;
/**
 Called when borica compatible pinpad is disconnected
 @param device borica sdk instance
 */
-(void)deviceDisconnected:(Borica *)device;
/**
 Called when a transaction is successful
 @param device borica sdk instance
 @param transactionType the transaction type that was initiated before
 @param resultData TLV list of tags returned with the transaction. This is very short list, basically containing the transaction result and reference number, for extended list use getReceiptTags
 */
-(void)transactionComplete:(Borica *)device transactionType:(TRANSACTION_TYPE)transactionType resultData:(NSData *)resultData;
/**
 Called when a transaction failed
 @param device borica sdk instance
 @param errorCode borica error code returned
 */
-(void)transactionFailed:(Borica *)device errorCode:(int)errorCode;

/**
 Notification sent when bluetooth low energy device is connected
 @param device bluetooth low energy device
 **/
-(void)bluetoothLEDeviceConnected:(CBPeripheral *)device;

/**
 Notification sent when bluetooth low energy connection is lost
 @param device bluetooth low energy device
 */
-(void)bluetoothLEDeviceDisconnected:(CBPeripheral *)device;

-(bool)bluetoothLEDeviceDiscovered:(CBPeripheral *)device;
-(void)bluetoothLEDiscoverCompletedWithError:(NSError *)error;
/**@}*/
@end

/**@}*/
