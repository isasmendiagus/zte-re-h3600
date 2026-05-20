// module: mt7915.ko
// function: WscCheckWpsIeFromWpsAP @ 0x1eb380
// size: 260 bytes
//

void WscCheckWpsIeFromWpsAP(undefined4 param_1,int param_2,undefined2 *param_3)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  ushort uVar7;
  ushort uStack_23;
  
  iVar3 = memcmp((void *)(param_2 + 2),&WPS_OUI,4);
  if (iVar3 == 0) {
    puVar6 = (uint *)(param_2 + 6);
    uVar5 = *(byte *)(param_2 + 1) - 4;
    sVar1 = (short)uVar5;
    while (0 < sVar1) {
      uVar4 = *puVar6;
      if ((param_3 != (undefined2 *)0x0) && (((uVar4 & 0xff) << 8 | uVar4 >> 8 & 0xff) == 0x1012)) {
        uVar2 = (ushort)puVar6[1];
        uVar7 = uVar2 << 8 | uVar2 >> 8;
        if (3 < DebugLevel) {
          printk("WscCheckWpsIeFromWpsAP : DevicePasswordID = 0x%04x\n",uVar7,uVar2,DebugLevel,uVar7
                );
        }
        if (uVar7 == 0) {
          *param_3 = 0;
        }
        else if (uVar7 == 4) {
          *param_3 = 4;
        }
      }
      uStack_23 = (ushort)(uVar4 >> 0x10);
      uVar4 = (uStack_23 & 0xff) << 8 | (uint)(uStack_23 >> 8);
      uVar5 = ((uVar5 & 0xffff) - 4) - uVar4;
      puVar6 = (uint *)((int)puVar6 + uVar4 + 4);
      sVar1 = (short)uVar5;
    }
  }
  return;
}

