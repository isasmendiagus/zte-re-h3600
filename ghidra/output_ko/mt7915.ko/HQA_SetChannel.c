// module: mt7915.ko
// function: HQA_SetChannel @ 0x26f948
// size: 188 bytes
//

undefined4 HQA_SetChannel(int param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  code *pcVar5;
  
  uVar2 = *(uint *)(param_3 + 0xc);
  bVar1 = (byte)(uVar2 >> 0x18);
  iVar4 = *(int *)(param_1 + 0xa39fd4);
  if (2 < DebugLevel) {
    printk("%s: Channel = %d, BW = %d\n","HQA_SetChannel",*(undefined1 *)(param_1 + 0xa3ad5c),
           *(undefined1 *)(param_1 + 0xa3ad65));
  }
  *(byte *)(param_1 + 0xa3ad5c) = bVar1;
  pcVar5 = *(code **)(iVar4 + 0x54);
  if (pcVar5 == (code *)0x0) {
    uVar3 = 1;
  }
  else {
    uVar3 = (*pcVar5)(param_1,(int)(short)((ushort)((uVar2 >> 0x10 & 0xff) << 8) | (ushort)bVar1),0,
                      0,0);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar3);
  return uVar3;
}

