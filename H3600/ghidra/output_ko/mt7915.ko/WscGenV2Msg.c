// module: mt7915.ko
// function: WscGenV2Msg @ 0x2015bc
// size: 324 bytes
//

undefined4
WscGenV2Msg(int param_1,int param_2,int param_3,undefined1 param_4,int *param_5,int *param_6)

{
  undefined4 uVar1;
  int iVar2;
  byte local_25;
  undefined1 *local_24;
  
  local_24 = (undefined1 *)0x0;
  os_alloc_mem(0,&local_24,0x80);
  if (local_24 == (undefined1 *)0x0) {
    uVar1 = 0;
  }
  else {
    local_25 = 0;
    *local_24 = 0;
    local_24[1] = 0x37;
    local_24[2] = 0x2a;
    WscAppendV2SubItem(0,param_1 + 0x71,1,local_24 + 3,&local_25);
    iVar2 = local_25 + 3;
    if (param_2 != 0) {
      if (param_3 == 0) {
        WscAppendV2SubItem(1,&BROADCAST_ADDR,6,local_24 + iVar2,&local_25);
        iVar2 = iVar2 + (uint)local_25;
      }
      else {
        WscAppendV2SubItem(1,param_3,param_4,local_24 + iVar2,&local_25);
        iVar2 = iVar2 + (uint)local_25;
      }
    }
    iVar2 = AppendWSCTLV(0x1049,*param_5,local_24,iVar2);
    *param_5 = *param_5 + iVar2;
    *param_6 = *param_6 + iVar2;
    os_free_mem(local_24);
    uVar1 = 1;
  }
  return uVar1;
}

