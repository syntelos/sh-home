/*
 * syntelos host endian tool
 * Copyright (C) 2024, John Pritchard, Syntelos
 */
#ifndef _endian_kind_h
#define _endian_kind_h
/*
 * Employ endian statically by defining _ENDIAN_KIND to be
 * _ENDIAN_KIND_LE or _ENDIAN_KIND_BE.  Otherwise, only the
 * dynamic endianness resolution is available.
 */
typedef enum endian_kind {
  /*
   * The endianness is unknown.  The conversion functions will return
   * zero.  (Note that "middle endian" cases are believed to be
   * archaic and have not been handled).
   */
  endian_kind_un = 0,
  /*
   * The endianness is known to be "little".  
   */
  endian_kind_le = 1,
  /*
   * The endianness is known to be "big".  
   */
  endian_kind_be = 2

} endian_kind;

typedef union endian16_t {
  uint16_t value;
  uint8_t data[sizeof(uint16_t)];
} endian16_t;

typedef union endian32_t {
  uint32_t value;
  uint8_t data[sizeof(uint32_t)];
} endian32_t;

typedef union endian64_t {
  uint64_t value;
  uint8_t data[sizeof(uint64_t)];
} endian64_t;

/*
 * Determine host system endianness dynamically.
 */
endian_kind endian(){

  endian16_t test;
  {
    test.data[0] = 0x01;
    test.data[1] = 0x00;
  }

  switch (test.value){
  case 0x0100U:
    return endian_kind_be;

  case 0x0001U:
    return endian_kind_le;

  default:
    return endian_kind_un;
  }
}
/*
 * Employ host system endianness statically by defining
 * _ENDIAN_KIND.
 */
#define endian_swap_macro(n,s,a,b) \
  s = n.data[a];                 \
  n.data[a] = n.data[b];         \
  n.data[b] = s;

uint16_t endian_swap_be16(uint16_t he){
#if _ENDIAN_KIND == _ENDIAN_KIND_LE
  endian16_t n;
  {
    n.value = he;
  }
  {
    uint8_t s;

    endian_swap_macro(n,s,1,0);
  }
  return n.value;
#else
  return he;
#endif
}
uint32_t endian_swap_be32(uint32_t he){
#if _ENDIAN_KIND == _ENDIAN_KIND_LE
  endian32_t n;
  {
    n.value = he;
  }
  {
    uint8_t s;

    endian_swap_macro(n,s,3,0);
    endian_swap_macro(n,s,2,1);
  }
  return n.value;
#else
  return he;
#endif
}
uint64_t endian_swap_be64(uint64_t he){
#if _ENDIAN_KIND == _ENDIAN_KIND_LE
  endian64_t n;
  {
    n.value = he;
  }
  {
    uint8_t s;

    endian_swap_macro(n,s,7,0);
    endian_swap_macro(n,s,6,1);
    endian_swap_macro(n,s,5,2);
    endian_swap_macro(n,s,4,3);
  }
  return n.value;
#else
  return he;
#endif
}

#if _ENDIAN_KIND == _ENDIAN_KIND_LE
#define endian_he_to_be16(b) endian_swap_be16(b)
#define endian_be_to_he16(b) endian_swap_be16(b)
#else
#define endian_he_to_be16(b) (b)
#define endian_be_to_he16(b) (b)
#endif

#if _ENDIAN_KIND == _ENDIAN_KIND_LE
#define endian_he_to_be32(b) endian_swap_be32(b)
#define endian_be_to_he32(b) endian_swap_be32(b)
#else
#define endian_he_to_be32(b) (b)
#define endian_be_to_he32(b) (b)
#endif

#if _ENDIAN_KIND == _ENDIAN_KIND_LE
#define endian_he_to_be64(b) endian_swap_be64(b)
#define endian_be_to_he64(b) endian_swap_be64(b)
#else
#define endian_he_to_be64(b) (b)
#define endian_be_to_he64(b) (b)
#endif

#endif
