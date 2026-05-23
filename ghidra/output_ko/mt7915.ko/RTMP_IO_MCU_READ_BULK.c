// module: mt7915.ko
// function: RTMP_IO_MCU_READ_BULK @ 0x27b1f0
// size: 276 bytes
//

void RTMP_IO_MCU_READ_BULK(undefined4 param_1,int param_2,int param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  param_4 = param_4 >> 2;
  if (param_4 != 0) {
    uVar4 = 0;
    uVar6 = 0;
    iVar5 = 0;
    do {
      *(int *)(RegPair + uVar4 * 8) = param_3;
      iVar2 = iVar5;
      if ((uVar4 == 0x7f) || (param_4 - 1 == uVar6)) {
        puVar3 = (uint *)(RegPair + 4);
        MtCmdMultipleMacRegAccessRead(param_1,RegPair,uVar4 + 1);
        do {
          uVar1 = *puVar3;
          if (3 < DebugLevel) {
            printk("%s: Offset = %x, Value = %x\n","RTMP_IO_MCU_READ_BULK",puVar3[-1],uVar1);
          }
          puVar3 = puVar3 + 2;
          *(uint *)(param_2 + iVar2 * 4) =
               uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
               uVar1 >> 0x18;
          iVar2 = iVar2 + 1;
        } while ((uint)(iVar2 - iVar5) <= uVar4);
        uVar4 = 0;
      }
      else {
        uVar4 = uVar4 + 1;
      }
      uVar6 = uVar6 + 1;
      param_3 = param_3 + 4;
      iVar5 = iVar2;
    } while (uVar6 != param_4);
  }
  return;
}

