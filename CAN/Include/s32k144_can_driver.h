#include "S32K144.h"

#define fCANCLK (8000000U)
#define CANCLK  (80000000U)

#define CAN_WMBn_CS_STD_ID_SHIFT (18U)

#define MSG_BUF_SIZE  (4U) /* Msg Buffer Size. (CAN 2.0AB: 2 hdr +  2 data= 4 words) */
typedef enum
{
    CAN_E_OK,    /* Successful */
    CAN_E_NOT_OK /* failure */
} Std_CAN_Status;

typedef enum
{
    CAN20,
    CANFD
} CAN_MODE_type;

typedef enum
{
    NORMAL_MODE,
    FREEZE_MODE,
    LOOP_BACK_MODE,
    LISTEN_ONLY_MODE,
    CANFD_ACTIVE_MODE,
    MODULE_DISABLE_MODE,
    STOP_MODE,
    PRETENDED_NETWORK_MODE
} CAN_OPERATION_MODE_type;

typedef enum
{
    BUS_CLOCK,
    SOSCDIV2_CLOCK
} CAN_CLOCK_SOURCE_type;

typedef enum
{
    ENABLE_BRS,
    DISBALE_BRS
} CAN_BIT_RATE_SW_type;

typedef struct
{
    uint32_t nominal_bit_Rate;
    uint32_t data_bit_rate;
    uint8_t time_quanta;
    uint8_t samp_point;
} CAN_Bit_Timing_type;

typedef enum
{
    PAYLOAD_8_BYTES,
    PAYLOAD_16_BYTES,
    PAYLOAD_32_BYTES,
    PAYLOAD_64_BYTES,
} CAN_PAYLOAD_type;

typedef enum
{
    EXTENDED_ID,
    STARDADARD_ID
} CAN_ID_TYPE_type;

typedef struct {
    CAN_Type *can_instance;
    uint8_t operate_mode;
    CAN_Bit_Timing_type *bit_rate_config;
    uint8_t can_mode;
    uint8_t clock_source;
    uint8_t bit_rate_sw;
    uint32_t tx_identifier;
    uint32_t rx_identifier;
    uint8_t payload;
    uint8_t id_type;
} CAN_Config_type;

Std_CAN_Status CAN_Init(CAN_Config_type* can_config);
void CAN_transmit_msg(CAN_Type* CAN_instance,uint32_t id, uint8_t* data_buff);
void CAN_receive_msg(CAN_Type* CAN_instance, uint8_t *rx_buff, uint16_t length_buff);
