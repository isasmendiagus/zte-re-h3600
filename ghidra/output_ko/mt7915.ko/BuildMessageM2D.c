// module: mt7915.ko
// function: BuildMessageM2D @ 0x1f49e0
// size: 1152 bytes
//

int BuildMessageM2D(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  undefined1 local_31;
  int local_30;
  int local_2c [2];
  
  local_30 = 0;
  local_2c[0] = param_3;
  iVar1 = AppendWSCTLV(0x104a,param_3,param_2 + 0x70,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_31 = 6;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x1022,local_2c[0],&local_31,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x101a,local_2c[0],param_2 + 0x1b40,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x1039,local_2c[0],param_2 + 0x1b60,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x1048,local_2c[0],param_2 + 0x72,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x1004,local_2c[0],param_2 + 0xc2,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x1010,local_2c[0],param_2 + 0xc4,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x100d,local_2c[0],param_2 + 0xc6,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x1008,local_2c[0],param_2 + 200,0);
  iVar3 = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  local_2c[0] = iVar3;
  sVar2 = strlen((char *)(param_2 + 0xcb));
  iVar1 = AppendWSCTLV(0x1021,iVar3,(char *)(param_2 + 0xcb),sVar2 & 0xffff);
  iVar3 = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  local_2c[0] = iVar3;
  sVar2 = strlen((char *)(param_2 + 0x10b));
  iVar1 = AppendWSCTLV(0x1023,iVar3,(char *)(param_2 + 0x10b),sVar2 & 0xffff);
  iVar3 = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  local_2c[0] = iVar3;
  sVar2 = strlen((char *)(param_2 + 299));
  iVar1 = AppendWSCTLV(0x1024,iVar3,(char *)(param_2 + 299),sVar2 & 0xffff);
  iVar3 = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  local_2c[0] = iVar3;
  sVar2 = strlen((char *)(param_2 + 0x14b));
  iVar1 = AppendWSCTLV(0x1042,iVar3,(char *)(param_2 + 0x14b),sVar2 & 0xffff);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x1054,local_2c[0],param_2 + 0xa8,0);
  iVar3 = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  local_2c[0] = iVar3;
  sVar2 = strlen((char *)(param_2 + 0x88));
  iVar1 = AppendWSCTLV(0x1011,iVar3,(char *)(param_2 + 0x88),sVar2 & 0xffff);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x103c,local_2c[0],param_2 + 0x16b,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x1002,local_2c[0],param_2 + 0x174,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x1009,local_2c[0],param_2 + 0x178,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  iVar1 = AppendWSCTLV(0x102d,local_2c[0],param_2 + 0x16c,0);
  local_2c[0] = local_2c[0] + iVar1;
  local_30 = local_30 + iVar1;
  if (*(char *)(param_2 + 0x2b31) != '\0') {
    WscGenV2Msg(param_2,0,0,0,local_2c,&local_30);
    if (*(int *)(param_2 + 0x2b28) != 0) {
      if (*(short *)(param_2 + 0x2b26) != 0) {
        iVar1 = AppendWSCTLV(*(undefined2 *)(param_2 + 0x2b24),local_2c[0]);
        local_2c[0] = local_2c[0] + iVar1;
        local_30 = local_30 + iVar1;
      }
    }
  }
  iVar1 = DebugLevel;
  *(undefined1 *)(param_2 + 0x1c53) = 0;
  if (2 < iVar1) {
    printk("BuildMessageM2D.\n");
  }
  return local_30;
}

