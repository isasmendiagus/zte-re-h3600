// module: mt7915.ko
// function: get_operating_class_list @ 0x142008
// size: 124 bytes
//

undefined4 get_operating_class_list(void)

{
  undefined4 *in_stack_00000000;
  undefined4 *in_stack_00000004;
  
  in_stack_00000000[1] = 0x77767574;
  *in_stack_00000000 = 0x73545351;
  in_stack_00000000[2] = 0x7b7a7978;
  in_stack_00000000[3] = 0x7f7e7d7c;
  *(undefined2 *)(in_stack_00000000 + 4) = 0x8180;
  *in_stack_00000004 = 0x12;
  return 1;
}

