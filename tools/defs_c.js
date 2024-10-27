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
  Key: 'u32',
  GamepadButton: 'u32',
  MouseButton: 'u32',
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
  Color: 'Color',
  Dimension: 'Dimension',
  Sound: 'unsigned int',
  bool: 'bool',
  'SfxParams*': 'SfxParams*',
  SfxPresetType: 'SfxPresetType',
  SfxWaveType: 'SfxWaveType',
  f32: 'float',
  u32: 'unsigned int',
  Key: 'Key',
  GamepadButton: 'GamepadButton',
  MouseButton: 'MouseButton',
  Image: 'unsigned int',
  'Vector[]': 'Vector*',
  ImageFilter: 'ImageFilter',
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
  Color: 'Color',
  Dimension: 'Dimension',
  Sound: 'unsigned int',
  Vector: 'Vector',
  Image: 'unsigned int',
  Font: 'unsigned int',
  Dimensions: 'Dimensions',
  Rectangle: 'Rectangle',
  bytes: 'unsigned char*',
  FileInfo: 'FileInfo',
  string: 'string'
}
