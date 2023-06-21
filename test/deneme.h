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
	uint8_t byte_array[1];
	uint8_t tekrar_sayisi;
	class PACKED tekrarli_ornek_t
	{
	public:
		uint8_t tekrarli_ornek;
		double tekrarli_double;
	};
	tekrarli_ornek_t tekrarli_ornek[1]; // dumy array, src =tekrar_sayisi
		class PACKED struct_ornek_t
		{
		public:
			uint8_t __rezerve_at_87;
			uint8_t __rezerve_at_88;
			uint8_t __rezerve_at_89;
			uint8_t ornek_byte;
			double ornek2_double;
			class PACKED DurumBiti_t
			{
			public:
			 uint32_t ornek_durum:2;
			 uint32_t ornekbit_2:1;
			 uint32_t rezerve_0:1;
			 uint32_t rezerve_1:1;
			 uint32_t my_bit:1;
			 uint32_t __rezerve_at_99:26;
			};
		};
	struct_ornek_t struct_ornek;
	int8_t __rezerve_at_87;
	int8_t __rezerve_at_88;
	uint8_t all_properties_default;
	uint16_t crc;
};

int a = sizeof(HELP_t);


#endif // __ICD_FILE_NAME_H__
