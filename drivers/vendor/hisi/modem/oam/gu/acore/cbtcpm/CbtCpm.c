

/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CbtCpm.c
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ����޸�   :
  ��������   : CBT�������˿ں��߼�ͨ��ӳ�����ģ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��5��31��
    ��    ��   : L00256032
    �޸�����   : V8R1 OM_Optimize��Ŀ����

***************************************************************************** */

/*****************************************************************************
  1 ͷ�ļ�����
**************************************************************************** */
#include "CbtCpm.h"
#include "cpm.h"
#include "SCMSoftDecode.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_CBT_CPM_C
/*lint +e767 */

/* ****************************************************************************
  2 ȫ�ֱ�������
**************************************************************************** */
CBTCPM_RCV_FUNC                g_pCbtRcvFunc = VOS_NULL_PTR;
CBTCPM_SEND_FUNC               g_pCbtSndFunc = VOS_NULL_PTR;

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/

extern VOS_UINT32 CBTSCM_SoftDecodeDataRcv(VOS_UINT8 *pucBuffer, VOS_UINT32 ulLen);

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : CBTCPM_PortRcvReg
 ��������  : ��CBTͨ��ע����պ���
 �������  : pRecvFunc��   ���ݽ��պ�����ַ
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID CBTCPM_PortRcvReg(CBTCPM_RCV_FUNC pRcvFunc)
{
    g_pCbtRcvFunc = pRcvFunc;

    return;
}

/*****************************************************************************
 �� �� ��  : CBTCPM_PortSndReg
 ��������  : ��CBTͨ��ע�ᷢ�ͺ���
 �������  : pSndFunc��   ���ݷ��ͺ�����ַ
 �������  : ��
 �� �� ֵ  : ��
 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_VOID CBTCPM_PortSndReg(CBTCPM_SEND_FUNC pSndFunc)
{
    g_pCbtSndFunc = pSndFunc;

    return;
}

/*****************************************************************************
 �� �� ��  : CBTCPM_GetRcvFunc
 ��������  : ��ȡCBTͨ�����պ�����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ݽ��պ�����ַ
 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
CBTCPM_RCV_FUNC CBTCPM_GetRcvFunc(VOS_VOID)
{
    return g_pCbtRcvFunc;
}

/*****************************************************************************
 �� �� ��  : CBTCPM_GetSndFunc
 ��������  : ��ȡCBTͨ�����ͺ�����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ݷ��ͺ�����ַ
 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
CBTCPM_SEND_FUNC CBTCPM_GetSndFunc(VOS_VOID)
{
    return g_pCbtSndFunc;
}

/*****************************************************************************
 �� �� ��  : CBTCPM_NotifyChangePort
 ��������  : AT���CBT�����ݽ��պͷ��ͺ���
 �������  : enPhyPort:AT�������˿ں�
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
VOS_UINT32 CBTCPM_NotifyChangePort(AT_PHY_PORT_ENUM_UINT32 enPhyPort)
{
    /* NAS��UART����У׼ */
    if (CPM_IND_PORT > enPhyPort)
    {
        /* ��AT��÷������ݵĺ���ָ�� */
        CBTCPM_PortSndReg(AT_QuerySndFunc(enPhyPort));

        /* ��AT�Ķ˿���У׼������USB��VCOM�������� */
        CBTCPM_PortRcvReg(VOS_NULL_PTR);

        /* ��У׼ͨ���Ľ��պ�����ATģ�� */
        AT_RcvFuncReg(enPhyPort, CBTSCM_SoftDecodeDataRcv);

        return VOS_OK;
    }

    return VOS_ERR;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif



