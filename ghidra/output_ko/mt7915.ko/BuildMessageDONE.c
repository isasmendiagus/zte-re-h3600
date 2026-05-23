// module: mt7915.ko
// function: BuildMessageDONE @ 0x1f6c08
// size: 412 bytes
//

int BuildMessageDONE(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined1 local_21;
  int local_20;
  int local_1c [2];
  
  local_20 = 0;
  local_1c[0] = param_3;
  iVar1 = AppendWSCTLV(0x104a,param_3,param_2 + 0x70,0);
  local_1c[0] = local_1c[0] + iVar1;
  local_21 = 0xf;
  local_20 = local_20 + iVar1;
  iVar1 = AppendWSCTLV(0x1022,local_1c[0],&local_21,0);
  local_1c[0] = local_1c[0] + iVar1;
  local_20 = local_20 + iVar1;
  iVar1 = AppendWSCTLV(0x101a,local_1c[0],param_2 + 0x1b40,0);
  local_1c[0] = local_1c[0] + iVar1;
  local_20 = local_20 + iVar1;
  iVar1 = AppendWSCTLV(0x1039,local_1c[0],param_2 + 0x1b50,0);
  local_1c[0] = local_1c[0] + iVar1;
  local_20 = local_20 + iVar1;
  if (*(char *)(param_2 + 0x2b31) != '\0') {
    WscGenV2Msg(param_2,0,0,0,local_1c,&local_20);
    if (*(int *)(param_2 + 0x2b28) != 0) {
      if (*(short *)(param_2 + 0x2b26) != 0) {
        iVar1 = AppendWSCTLV(*(undefined2 *)(param_2 + 0x2b24),local_1c[0]);
        local_1c[0] = local_1c[0] + iVar1;
        local_20 = local_20 + iVar1;
      }
    }
  }
  iVar1 = DebugLevel;
  *(undefined1 *)(param_2 + 0x1c53) = 0;
  if (2 < iVar1) {
    printk("BuildMessageDONE :\n");
  }
  return local_20;
}

