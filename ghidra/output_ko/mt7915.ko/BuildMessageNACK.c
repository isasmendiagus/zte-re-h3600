// module: mt7915.ko
// function: BuildMessageNACK @ 0x1f6f40
// size: 468 bytes
//

int BuildMessageNACK(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  ushort local_1c;
  undefined1 local_1a [2];
  int local_18;
  int local_14;
  
  local_1c = *(ushort *)(param_2 + 0x178) << 8 | *(ushort *)(param_2 + 0x178) >> 8;
  local_18 = 0;
  local_14 = param_3;
  iVar1 = AppendWSCTLV(0x104a,param_3,param_2 + 0x70,0);
  local_14 = local_14 + iVar1;
  local_1a[0] = 0xe;
  local_18 = local_18 + iVar1;
  iVar1 = AppendWSCTLV(0x1022,local_14,local_1a,0);
  local_14 = local_14 + iVar1;
  local_18 = local_18 + iVar1;
  iVar1 = AppendWSCTLV(0x101a,local_14,param_2 + 0x1b40,0);
  local_14 = local_14 + iVar1;
  local_18 = local_18 + iVar1;
  iVar1 = AppendWSCTLV(0x1039,local_14,param_2 + 0x1b50,0);
  local_14 = local_14 + iVar1;
  local_18 = local_18 + iVar1;
  iVar1 = AppendWSCTLV(0x1009,local_14,&local_1c,0);
  local_14 = local_14 + iVar1;
  local_18 = local_18 + iVar1;
  if (*(char *)(param_2 + 0x2b31) != '\0') {
    WscGenV2Msg(param_2,0,0,0,&local_14,&local_18);
    if (*(int *)(param_2 + 0x2b28) != 0) {
      if (*(short *)(param_2 + 0x2b26) != 0) {
        iVar1 = AppendWSCTLV(*(undefined2 *)(param_2 + 0x2b24),local_14);
        local_14 = local_14 + iVar1;
        local_18 = local_18 + iVar1;
      }
    }
  }
  iVar1 = DebugLevel;
  *(undefined1 *)(param_2 + 0x1c53) = 0;
  if (2 < iVar1) {
    printk("BuildMessageNACK :\n");
  }
  return local_18;
}

