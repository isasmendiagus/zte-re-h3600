// module: mt7915.ko
// function: HQA_GetTXInfo @ 0x270a3c
// size: 168 bytes
//

undefined4 HQA_GetTXInfo(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_GetTXInfo",DebugLevel,0,0,0);
  }
  iVar1 = net_ad_wrap_service(param_1);
  uVar3 = *(uint *)(iVar1 + 0x111c);
  iVar1 = net_ad_wrap_service(param_1);
  uVar2 = *(uint *)(iVar1 + 0x1e34);
  *(uint *)(param_3 + 0xe) =
       uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 | uVar3 >> 0x18;
  *(uint *)(param_3 + 0x12) =
       uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 | uVar2 >> 0x18;
  FUN_0026cdd0(param_3,param_2,10,0);
  return 0;
}

