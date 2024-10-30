// these are definitions that are shared between C things

export const apiArgNamMap = {
  string: 'string',
  i32: 'i32',
  Color: 'Color',
  Dimension: 'Dimension',
  Sound: 'Sound',
  bool: 'bool',
  'SfxParams*': 'SfxParams_pointer',
  SfxPresetType: 'SfxPresetType',
  SfxWaveType: 'SfxWaveType',
  f32: 'f32',
  u32: 'u32',
  Key: 'Key',
  GamepadButton: 'GamepadButton',
  MouseButton: 'MouseButton',
  Image: 'Image',
  'Vector[]': 'Vector_array',
  ImageFilter: 'u32',
  Font: 'u32',
  'u32*': 'u32_pointer',
  bytes: 'bytes'
}

export const apiArgTypeMap = {
  string: 'char*',
  i32: 'int',
  Color: 'pntr_color',
  Dimension: 'Null0Dimension',
  Sound: 'unsigned int',
  bool: 'bool',
  'SfxParams*': 'SfxParams*',
  SfxPresetType: 'SfxPresetType',
  SfxWaveType: 'SfxWaveType',
  f32: 'float',
  u32: 'unsigned int',
  Key: 'pntr_app_key',
  GamepadButton: 'pntr_app_gamepad_button',
  MouseButton: 'pntr_app_mouse_button',
  Image: 'unsigned int',
  'Vector[]': 'pntr_vector*',
  ImageFilter: 'pntr_filter',
  Font: 'unsigned int',
  'u32*': 'unsigned int*',
  bytes: 'unsigned char*'
}

export const apiRetNameMap = {
  u64: 'u64',
  f32: 'f32',
  i32: 'i32',
  bool: 'bool',
  Color: 'Color',
  Dimension: 'Dimension',
  Sound: 'u32',
  Vector: 'Vector',
  Image: 'u32',
  Font: 'u32',
  Dimensions: 'Dimensions',
  Rectangle: 'Rectangle',
  bytes: 'bytes',
  FileInfo: 'FileInfo',
  string: 'string'
}

export const apiRetTypeMap = {
  u64: 'uint64_t',
  f32: 'float',
  i32: 'int',
  bool: 'bool',
  Color: 'pntr_color',
  Dimension: 'Null0Dimension',
  Sound: 'unsigned int',
  Vector: 'Vector',
  Image: 'unsigned int',
  Font: 'unsigned int',
  Rectangle: 'pntr_rectangle',
  bytes: 'unsigned char*',
  FileInfo: 'PHYSFS_stat',
  string: 'char*'
}
