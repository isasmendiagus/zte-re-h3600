// module: mt7915.ko
// function: DfsDedicatedOutBandRDDRunning @ 0x235e58
// size: 700 bytes
//

void DfsDedicatedOutBandRDDRunning(int param_1)

{
  undefined1 uVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  
  mtRddControl(param_1,0,2,0,0);
  if (*(char *)(param_1 + 0x795404) == '\0') {
    if (2 < DebugLevel) {
      printk("%s() DedicatedZeroWaitDefault is not enabled\n","DfsDedicatedOutBandRDDRunning");
      return;
    }
  }
  else {
    iVar9 = 0;
    uVar7 = 0;
    puVar5 = (undefined1 *)(param_1 + 0x795133);
    while( true ) {
      puVar6 = puVar5 + 1;
      uVar1 = *puVar6;
      pbVar2 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar9);
      if (*pbVar2 < 0x24) {
        if (2 < DebugLevel) {
          printk("%s() not A-band, channel %d\n","DfsDedicatedOutBandRDDRunning");
        }
      }
      else {
        if (2 < DebugLevel) {
          printk("%s(): In-band channel %d, outband ch %d\n","DfsDedicatedOutBandRDDRunning",
                 puVar5[-3],*(undefined1 *)(param_1 + 0x7953fb));
        }
        uVar7 = (uint)pbVar2[0x49c];
        if (uVar7 != 0) {
          uVar8 = 0;
          do {
            if (((*(byte *)(param_1 + 0x7953fb) == pbVar2[uVar8 * 0x14]) &&
                (*(short *)(pbVar2 + uVar8 * 0x14 + 0xc) == 0)) &&
               (*(short *)(pbVar2 + uVar8 * 0x14 + 10) == 0)) {
              iVar3 = DfsPrimToCent(*(byte *)(param_1 + 0x7953fb),
                                    *(undefined1 *)(param_1 + 0x7953fc));
              iVar4 = DfsPrimToCent(puVar5[-3],*puVar6);
              if (iVar3 != iVar4) {
                if (DebugLevel < 3) {
                  return;
                }
                printk("%s(): NOP of Ch%d is clear, keep using this ch\n",
                       "DfsDedicatedOutBandRDDRunning",*(undefined1 *)(param_1 + 0x7953fb));
                return;
              }
              if (2 < DebugLevel) {
                printk("%s(): In-band %d is using this channel %d\n","DfsDedicatedOutBandRDDRunning"
                       ,iVar9,puVar5[-3]);
              }
              uVar7 = (uint)pbVar2[0x49c];
            }
            uVar8 = uVar8 + 1 & 0xff;
          } while (uVar8 < uVar7);
        }
        uVar7 = DfsBwChQueryByDefault(param_1,uVar1,param_1 + 0x795130,1,1,1,iVar9);
        if ((2 < DebugLevel) &&
           (printk("%s() bw_ch_band[%d] 0x%x\n","DfsDedicatedOutBandRDDRunning",iVar9,uVar7),
           2 < DebugLevel)) {
          printk("%s() bw_band[%d] 0x%x\n","DfsDedicatedOutBandRDDRunning",iVar9,
                 (uVar7 << 0x10) >> 0x18);
        }
      }
      iVar3 = DebugLevel;
      if (iVar9 == 1) break;
      iVar9 = 1;
      puVar5 = puVar6;
    }
    *(char *)(param_1 + 0x7953fb) = (char)uVar7;
    *(char *)(param_1 + 0x7953fc) = (char)(uVar7 >> 8);
    if (0 < iVar3) {
      printk(&_LC142,"DfsDedicatedOutBandRDDRunning",uVar7 & 0xff,(uVar7 << 0x10) >> 0x18);
      return;
    }
  }
  return;
}

