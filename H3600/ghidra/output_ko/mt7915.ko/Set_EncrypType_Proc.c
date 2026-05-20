// module: mt7915.ko
// function: Set_EncrypType_Proc @ 0x586e8
// size: 240 bytes
//

undefined4
Set_EncrypType_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined *puVar2;
  int iVar3;
  
  iVar3 = *(int *)(*param_1 + 0x3c);
  SetWdevEncrypMode(param_1 + iVar3 * 0x84dec + 0xdb6e1);
  if ((char)param_1[iVar3 * 0x84dec + 0xdc6ee] == '\0') {
    puVar2 = (undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar3 * 0x2137b0));
    uVar1 = HcGetBandByWdev(puVar2);
    uVar1 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar1);
    hc_set_ChCtrlChListStat(uVar1,0);
    BuildChannelList(param_1,puVar2);
    RTMPSetPhyMode(param_1,puVar2,(char)param_1[0x1e5312]);
  }
  if (2 < DebugLevel) {
    printk("%s:: CIPHER=0x%x\n","Set_EncrypType_Proc",param_1[iVar3 * 0x84dec + 0xdb6e1],
           param_1 + (int)(RTMPSetDesiredRates + iVar3 * 0x84dec),param_4);
  }
  return 1;
}

