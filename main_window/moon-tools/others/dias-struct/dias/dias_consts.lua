SIZE_OF_UINT8 = 1;
SIZE_OF_UINT16 = 2;
SIZE_OF_UINT32 = 4;
SIZE_OF_UINT64 = 8;
SIZE_OF_INT8 = 1;
SIZE_OF_INT16 = 2;
SIZE_OF_INT32 = 4;
SIZE_OF_INT64 = 8;

LTE_OPT_USE_DIAS_API = 0x00000001;

DIAS_V2X_AID_LIST_MAX_NUM = 20;

DIAS_V2X_MSG_TYPE_RAW = 1 << 0;  --透传消息
DIAS_V2X_MSG_TYPE_BSM = 1 << 1;  --BSM消息
DIAS_V2X_MSG_TYPE_SPAT = 1 << 2; --SPAT消息
DIAS_V2X_MSG_TYPE_MAP = 1 << 3;  --MAP消息
DIAS_V2X_MSG_TYPE_RSM = 1 << 4;  --RSM消息
DIAS_V2X_MSG_TYPE_RSI = 1 << 5;  --RSI消息
DIAS_V2X_MSG_TYPE_ALL = 1 << 31;

MAX_RSA_COUNT           =  16;
MAX_PATH_COUNT          =  32;
MAX_RTE_COUNT           =  8;
MAX_RTS_COUNT           =  16;
MAX_REFERENCEPATH_COUNT =  8;
MAX_REFERENCELINK_COUNT =  16;
MAX_PATHPOINT_NUMBER    =  32;
MAX_DESCRIPTION_LENGTH  =  512;

MAX_PARTICIPANT_NUMBER = 16;


AID_BSM_TYPE1 = 111;
AID_BSM_TYPE2 = 112;
AID_BSM_TYPE3 = 113;
AID_BSM_TYPE4 = 114;
AID_RSM = 3623;
AID_RSI_TYPE1 = 3620;
AID_RSI_TYPE2 = 3621;
AID_RSI_TYPE3 = 3622;
AID_MAP  = 3618;
AID_SPAT = 3619;

DIAS_INIT_MSG_TYPE_STRUCT = 0
DIAS_INIT_MSG_TYPE_ASN1_STRUCT = 1
DIAS_INIT_MSG_TYPE_ASN1_ENCODED = 2

MaxMapCount                  = 5
MaxIntersectionGeometryNum   = 8
MaxLinkNum                   = 8
MaxLinkPointNum              = 31
MaxSpeedLimitNum             = 4
MaxInLaneNum                 = 16
MaxConnectionsNum            = 8
MaxPointNum                  = 31 
MaxPointAttributesNum        = 8
MaxMovementNum               = 8
MapSavePeriod                = 5

MAX_INTERSECTION_NUMBER = 32; --最大十字路口数量
MAX_SIGNAL_GROUPS_NUMBER = 255; --最大信号灯数量
MAX_NAME_LEN = 1;
SIGNAL_GROUPS_NUMBER = 20 --相位数量(每个路口有多少组信号灯)
INTERSECTION_NUMBER = 32 --十字路口数量(每组数据包含多少个十字路口信息)

VEHICLE_ID_LEN = 8
PATH_HISTORY_POINTS_MAX	= 23


