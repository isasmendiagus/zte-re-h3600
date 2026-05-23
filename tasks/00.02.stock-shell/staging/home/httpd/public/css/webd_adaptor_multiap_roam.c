/******************************************************************************
* Copyright (C) 2008, ZTE Corporation.
*
* File Name:    webd_adaptor_multiap_roam.c
* Author:       jiang.jinhua
* Date:         2018-09-08
* Descrption:   为模块cmapi提供get/set/query/del适配函数
* Changes:      
******************************************************************************/

#include "csp_webd.h"
#include "enum2str.h"
#include "haikui_enum2str.h"
#include "csp_multi_ap_cmapi.h"
#include "csp_module.h"


/******************************************************************************
* Function:     MultiAPGetRoamCfgComm
* Descrption:   该函数是PT_CM_MULTIAP_ROAM_CONFIG结构体转换函数
* Input:        dwOp:           运算符，目前有GET,SET,CHECK
                ptConf:         T_CM_ETH_PORT_CONF结构体指针
                ptList:         参数链表首指针
* Output:       N/A
* Return:       INT32
******************************************************************************/
static INT32 MultiAPGetRoamCfgComm(DWORD dwOp, T_CM_MULTIAP_ROAM_CONFIG *ptConf, PT_WEBD_PRM_L ptlist)
{
    INT32   iRet = WEB_SUCCESS;

    iRet = AdaptorPrmOp(dwOp, ptlist, CSP_INT32,      WEB_RW,  &iRet, ID_NOTNEEDCONV,       "RoamRssiLmt24G",         &ptConf->tRoamRssiLmt24G);
    iRet = AdaptorPrmOp(dwOp, ptlist, CSP_INT32,      WEB_RW,  &iRet, ID_NOTNEEDCONV,       "RoamRssiLmt5G",         &ptConf->tRoamRssiLmt5G);

    return iRet;
}

/* 注册适配接口 */
static INT32 InitWebdAdaptor(VOID)
{
    INT32 iRet = WEB_SUCCESS;

    AddCmapiFuncItem("OBJ_MULTIAP_ROAM_ID", (DWORD)sizeof(T_CM_MULTIAP_ROAM_CONFIG), (COVERTCOMM)MultiAPGetRoamCfgComm, (GETCMAPIFUNC)CmMultiAPGetRoamCfg, 
                                   CmMultiAPSetRoamCfg, NULL, NULL, &iRet);

    return iRet;
}

MODULE_INIT(InitWebdAdaptor);





