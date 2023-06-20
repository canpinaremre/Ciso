//Auto-generated header file
//XML source: ICD_File_Name


#ifndef __ICD_FILE_NAME_H__
#define __ICD_FILE_NAME_H__
#include <stdint.h> 
#define PACKED __attribute__((packed)) 


class PACKED HELP_t
{
public:
 uint8_t bit8_deneme;
 float my_fl;
 double double_array[10];
 uint8_t tekrar_sayisi;
 class PACKED struct_ornek_t
 {
 public:
  uint8_t __rezerve_at_86;
  uint8_t __rezerve_at_87;
  uint8_t __rezerve_at_88;
  uint8_t ornek_byte;
  double ornek2_double;
 };
};


#endif // __ICD_FILE_NAME_H__
