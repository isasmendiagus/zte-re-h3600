// module: mt7915.ko
// function: sta_tx_pkt_handle @ 0x5327c
// size: 280 bytes
//

undefined4 sta_tx_pkt_handle(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  code *UNRECOVERED_JUMPTABLE;
  int *piVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_2 + 0x904);
  iVar1 = GetStaCfgByWdev();
  iVar3 = *(int *)(param_3 + 0xc);
  if (iVar3 == 0) {
    return 1;
  }
  if (iVar1 != 0) {
    switch(*(char *)(param_3 + 5)) {
    case '\x01':
    case '\x02':
      UNRECOVERED_JUMPTABLE = *(code **)(iVar5 + 0x18);
      break;
    case '\x03':
      UNRECOVERED_JUMPTABLE = *(code **)(iVar5 + 0x1c);
      break;
    case '\x04':
      UNRECOVERED_JUMPTABLE = *(code **)(iVar5 + 0x20);
      break;
    case '\x05':
      UNRECOVERED_JUMPTABLE = *(code **)(iVar5 + 0x24);
      break;
    case '\x06':
      UNRECOVERED_JUMPTABLE = *(code **)(iVar5 + 0x28);
      break;
    case '\a':
      UNRECOVERED_JUMPTABLE = *(code **)(iVar5 + 0x2c);
      break;
    case '\b':
      UNRECOVERED_JUMPTABLE = *(code **)(iVar5 + 0x30);
      break;
    case '\t':
      UNRECOVERED_JUMPTABLE = *(code **)(iVar5 + 0x34);
      break;
    default:
      if (-1 < DebugLevel) {
        printk("Send a pacekt was not classified!!\n");
        iVar3 = *(int *)(param_3 + 0xc);
      }
      goto LAB_00053304;
    }
                    /* WARNING: Could not recover jumptable at 0x00053328. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (*UNRECOVERED_JUMPTABLE)(param_1,param_2,param_3);
    return uVar2;
  }
  if (*(char *)(param_3 + 5) == '\x04') {
    piVar4 = *(int **)(param_3 + 0x40);
    while (piVar4 != (int *)0x0) {
      iVar1 = *piVar4;
      *piVar4 = 0;
      *(int *)(param_3 + 0x40) = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)(param_3 + 0x44) = 0;
      }
      *(int *)(param_3 + 0x48) = *(int *)(param_3 + 0x48) + -1;
      RTMPFreeNdisPacket(param_1,piVar4);
      piVar4 = *(int **)(param_3 + 0x40);
    }
    return 1;
  }
LAB_00053304:
  RTMPFreeNdisPacket(param_1,iVar3);
  return 1;
}

