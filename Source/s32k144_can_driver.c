#include "../src/Driver/CAN/Include/s32k144_can_driver.h"
//#include "../scr/Driver/CAN/Include/s32k144_can_driver.h"

uint8_t msg_buff_size = 0;
uint8_t num_msg_buff = 0;

Std_CAN_Status CAN_BitRateConfig(CAN_Type* can_instance, CAN_Bit_Timing_type* bit_rate_config)
{
	Std_CAN_Status status = CAN_E_OK;

    if(can_instance->MCR & CAN_MCR_FDEN_SHIFT)
    {
        can_instance->CBT = 0x802FB9EF;
        can_instance->FDCBT = 0x00131CE3;
    }
    else
    {
        float cr_samp_point = bit_rate_config->samp_point/(float)100;
        uint8_t cr_time_quanta = (uint8_t)(((float)bit_rate_config->time_quanta) * cr_samp_point);
        uint8_t sync_seg = 1;
        uint8_t phase_seg2 = (bit_rate_config->time_quanta - cr_time_quanta);
        uint8_t phase_seg1 = phase_seg2;
        uint8_t prop_seg = bit_rate_config->time_quanta - phase_seg1 - phase_seg2 - sync_seg;
        uint32_t f_Sclock = bit_rate_config->time_quanta * bit_rate_config->nominal_bit_Rate;
        uint8_t prescaler_val = 1 - (fCANCLK / f_Sclock);
        uint8_t rjw = 3;
        if(phase_seg2 < 4)
        {
            rjw = phase_seg2 - 1;
        }
        else
        {
            /* DO NOTHING */
        }
        can_instance->CBT |= CAN_CBT_BTF_MASK;
        can_instance->CBT |= CAN_CBT_EPRESDIV(prescaler_val);
        can_instance->CBT |= CAN_CBT_ERJW(rjw);
        can_instance->CBT |= CAN_CBT_EPSEG1(phase_seg1 - 1);
        can_instance->CBT |= CAN_CBT_EPSEG2(phase_seg2 - 1);
        can_instance->CBT |= CAN_CBT_EPROPSEG(prop_seg - 1);
    }

    return status;
}

Std_CAN_Status CAN_Init(CAN_Config_type* can_config)
{
    Std_CAN_Status status = CAN_E_OK;
    /* CANx is CAN0 or CAN1 or CAN2 */
    CAN_Type* CANx = can_config->can_instance;
    /* Disable module before selecting clock*/
    CANx->MCR |= CAN_MCR_MDIS_MASK;
    while(!((CANx->MCR & CAN_MCR_LPMACK_MASK) >> CAN_MCR_LPMACK_SHIFT))
    {
        /* DO NOTHING */
    }

    /* setting clock*/
    if(BUS_CLOCK == can_config->clock_source)
    {
        CANx->CTRL1 |= CAN_CTRL1_CLKSRC_MASK;
    }
    else
    {
        CANx->CTRL1 &= ~CAN_CTRL1_CLKSRC_MASK;
    }

    /* Enable module after selecting clock and enter freeze mode(MCR[FRZ], MCR[HALT] is auto set)*/
    CANx->MCR &= ~CAN_MCR_MDIS_MASK;
    while(((CANx->MCR & CAN_MCR_LPMACK_MASK) >> CAN_MCR_LPMACK_SHIFT))
    {
        /* DO NOTHING */
    }
    while (!((CANx->MCR & CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT))
    {
        /* DO NOTHING */
    }

    /* Set CAN mode(CAN 2.0 or FlexCAN) */
    if(CANFD == can_config->can_mode)
    {
        CANx->MCR |= CAN_MCR_FDEN_MASK;
        /* Switching BRS */
        if(ENABLE_BRS == can_config->bit_rate_sw)
        {
            CANx->FDCTRL |= CAN_FDCTRL_FDRATE_MASK;
        }
        else
        {
            /* DO NOTHING */
        }

        /* payload configure */

        switch (can_config->payload)
        {
        case PAYLOAD_8_BYTES:
            can_config->can_instance->FDCTRL |= CAN_FDCTRL_MBDSR0(0);
            can_config->can_instance->MCR &= ~CAN_MCR_MAXMB_MASK;
            can_config->can_instance->MCR |= CAN_MCR_MAXMB(31);
            msg_buff_size = 4;
            num_msg_buff = 32;
            break;
        case PAYLOAD_16_BYTES:
            can_config->can_instance->FDCTRL |= CAN_FDCTRL_MBDSR0(1);
            can_config->can_instance->MCR &= ~CAN_MCR_MAXMB_MASK;
            can_config->can_instance->MCR |= CAN_MCR_MAXMB(20);
            msg_buff_size = 6;
            num_msg_buff = 21;
            break;
        case PAYLOAD_32_BYTES:
            can_config->can_instance->FDCTRL |= CAN_FDCTRL_MBDSR0(2);
            can_config->can_instance->MCR &= ~CAN_MCR_MAXMB_MASK;
            can_config->can_instance->MCR |= CAN_MCR_MAXMB(11);
            msg_buff_size = 10;
            num_msg_buff = 12;
            break;
        case PAYLOAD_64_BYTES:
            can_config->can_instance->FDCTRL |= CAN_FDCTRL_MBDSR0(3);
            can_config->can_instance->MCR &= ~CAN_MCR_MAXMB_MASK;
            can_config->can_instance->MCR |= CAN_MCR_MAXMB(6);
            msg_buff_size = 18;
            num_msg_buff = 7;
            break;
        default:
            break;
        }
    }
    else
    {
        CANx->MCR |= CAN_MCR_MAXMB(31);
        msg_buff_size = 4;
        num_msg_buff = 32;
    }
    /* configue bit timing */
    CAN_BitRateConfig(CANx, can_config->bit_rate_config);

    for(volatile uint8_t idx = 0; idx < 128U; idx++)
    {
        CANx->RAMn[idx] = 0;
    }

    /* init 32 msg buff filter */
    for(uint8_t idx = 0; idx < num_msg_buff; idx++)
    {
        CANx->RXIMR[idx] = 0xFFFFFFFF;
    }

    /* Enable for reception */
    for(uint8_t idx = 0; idx < (uint8_t)(num_msg_buff / 2); idx++)
    {
        CANx->RAMn[idx*msg_buff_size] = 0x04000000;
        CANx->RAMn[idx*msg_buff_size] |= (uint32_t)(1 << 31);
    }

    for(uint8_t idx = (uint8_t)(num_msg_buff / 2); idx < num_msg_buff; idx++)
    {
        CANx->RAMn[idx*msg_buff_size] = 0x08000000;
        CANx->RAMn[idx*msg_buff_size] |= (uint32_t)(1 << 31);
    }

    volatile uint8_t idx = 0;
    while((idx < num_msg_buff) && (0x84000000 != CANx->RAMn[idx*msg_buff_size]))
    {
    	idx++;
    }

    /* write Rx ID into msg buf */
    if(STARDADARD_ID == can_config->id_type)
    {
        CANx->RAMn[idx*msg_buff_size + 1] = ((can_config->rx_identifier) << CAN_WMBn_CS_STD_ID_SHIFT);
    }
    else
    {
        CANx->RAMn[idx*msg_buff_size + 1] = ((can_config->rx_identifier));
    }
    /* operation configure */
    if(LOOP_BACK_MODE == can_config->operate_mode)
    {
        CANx->CTRL1 |= CAN_CTRL1_LPB_MASK;
    }
    else
    {
        /* DO NOTHING */
    }

    /* Out freeze mode */
    CANx->MCR &= ~CAN_MCR_FRZ_MASK;
    CANx->MCR &= ~CAN_MCR_HALT_MASK;
    while (((CANx->MCR & CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT))
    {
        /* DO NOTHING */
    }

    while ((CAN0->MCR && CAN_MCR_NOTRDY_MASK) >> CAN_MCR_NOTRDY_SHIFT)
    {
    	/* DO NOTHING */
    }

    return status;
}

void CAN_transmit_msg(CAN_Type* CAN_instance,uint32_t id, uint8_t* data_buff)
{
    uint8_t idx = 0;
    while((idx < num_msg_buff) && (0x88000000 != CAN_instance->RAMn[idx*msg_buff_size]))
    {
    	idx++;
    }
    CAN_instance->IFLAG1 = (uint32_t)(1 << idx);
    CAN_instance->RAMn[idx*msg_buff_size + 1] = (id << 18);

    uint8_t num_words = msg_buff_size - 2;
    for (uint8_t w_idx = 0; w_idx < num_words; w_idx++)
    {
        uint32_t data_word = 0;
        for (uint8_t idx = 0; idx < 4; idx++)
        {
            uint8_t data_idx = (w_idx * 4) + idx;
            data_word |= (uint32_t)(data_buff[data_idx]) << (8 * (3 - idx));
        }
        CAN_instance->RAMn[idx * msg_buff_size + 2 + w_idx] = data_word;
    }

    CAN_instance->RAMn[idx*msg_buff_size] |= 0 << CAN_WMBn_CS_DLC_SHIFT;
    CAN_instance->RAMn[idx*msg_buff_size] |= 13 << CAN_WMBn_CS_DLC_SHIFT;
    CAN_instance->RAMn[idx*msg_buff_size] |= 1 << CAN_WMBn_CS_SRR_SHIFT;
    CAN_instance->RAMn[idx*msg_buff_size] |= 0xC << 24;
    CAN_instance->IFLAG1 = (1 << idx);
    while((CAN_instance->IFLAG1 & (1 << idx)))
    {
    	/* DO NOTHING */
    }
}

void CAN_receive_msg(CAN_Type* CAN_instance, uint8_t *rx_buff, uint16_t length_buff)
{
    uint8_t idx_mb = 0;
	while(!(CAN_instance->IFLAG1 & (1 << idx_mb)))
    {
        idx_mb++;
    }

    uint8_t num_words = msg_buff_size - 2;
    uint8_t rx_idx = 0;
    for(uint8_t w_idx = 0; w_idx < num_words; w_idx++)
    {
        for(uint8_t idx = 0; idx < 4; idx++)
        {
//            uint8_t b_idx = (w_idx * 4) + idx;
            if(rx_idx < length_buff)
            {
                rx_buff[rx_idx] = (uint8_t)(CAN_instance->RAMn[idx_mb * msg_buff_size + 2 + w_idx] >> (8 * (3 - idx)));
                rx_idx++;
            }
        }
    }

    CAN_instance->IFLAG1 = (1 << idx_mb);
}
