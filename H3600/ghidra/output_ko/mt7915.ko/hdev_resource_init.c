// module: mt7915.ko
// function: hdev_resource_init @ 0xa89b8
// size: 44 bytes
//

void hdev_resource_init(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_1 + 0x4328);
  HdevHwResourceInit();
  uVar1 = *puVar2;
  *(undefined4 **)(param_1 + 0x4320) = puVar2 + 0x29e127;
  *(undefined4 *)(param_1 + 0x4324) = uVar1;
  return;
}

