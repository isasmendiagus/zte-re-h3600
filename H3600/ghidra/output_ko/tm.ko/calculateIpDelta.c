// module: tm.ko
// function: calculateIpDelta @ 0x5eb74
// size: 96 bytes
//

uint calculateIpDelta(undefined1 *param_1,undefined1 *param_2)

{
  uint uVar1;
  
  uVar1 = (uint)CONCAT11(param_1[2],param_1[3]) + (~(uint)CONCAT11(param_2[2],param_2[3]) & 0xffff)
          + (uint)CONCAT11(*param_1,param_1[1]) + (~(uint)CONCAT11(*param_2,param_2[1]) & 0xffff);
  uVar1 = (uVar1 & 0xffff) + (uVar1 >> 0x10);
  return (uVar1 & 0xffff) + (uVar1 >> 0x10) & 0xffff;
}

