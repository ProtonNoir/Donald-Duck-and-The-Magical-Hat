#include "LZSS.hpp"
#include <cstdint>

uint32_t check_pos(uint32_t cur_pos) {
	if (cur_pos >= WINDOW_SIZE) {
		cur_pos = cur_pos - WINDOW_SIZE;
	}
	return cur_pos;
}

uint16_t read_bank(uint16_t &value) {
	cout << "Donald Duck Mahou no Boushi" << endl;
	cout << "Donald Duck in the Magic Cap" << endl;
	cout << "Donald Duck and The Magical Hat" << endl;

	uint8_t bank[] = {
	//4bit
			0x10,//0001 - 0x00
			0x20, //0010 - 0x10
			//5bit
			0x30,//00110 - 0x20
			0x38,        //00111 - 0x30
			0x40,        //01000 - 0x40
			0x48,        //01001 - 0x50
			0x50,        //01010 - 0x60
			0x58,        //01011 - 0x70
			//6bit
			0x00,//000000 - 0x00 - BANK + DISTANCE
			0x60,        //011000 - 0x80
			0x64,        //011001 - 0x90
			0x68,        //011010 - 0xA0
			0x6C,        //011011 - 0xB0
			0x70,        //011100 - 0xC0
			0x74,        //011101 - 0xD0
			0x78,        //011110 - 0xE0
			0x7C //011111 - 0xF0
			};

	uint8_t mask[] = { 0xf0, 0xf8, 0xfc, 0xfe, 0xff };

	// map<int bb, int vv> bank_map;

	cout << hex << (int) (value & 0xf0) << endl;
	cout << hex << (int) (value & 0xf8) << endl;
	cout << hex << (int) (value & 0xfc) << endl;

	cout << hex << "value=" << (int) value << endl;

	uint16_t t1 = check_bank(value);

	cout << hex << "z.check=" << (int) t1 << endl;

	int x = 0;
	int y = 0;

	for (int j = 0; j < 3; j++) {
		int val = value & mask[j];

		for (int i = 0; i < 0x10; i++) {

			uint8_t temp = bank[i];

			if (temp == val) {
				cout << hex << "val=" << (int) val << endl;
				cout << hex << "i=" << i << " j=" << j << " TRUE" << " bank["
						<< i << "]=" << (int) bank[i] << " mask[" << j << "]="
						<< (int) mask[j] << " temp=" << (int) temp << endl;

				if (mask[j] > mask[j - 1]) {
					x = j;
					y = i;
				}

				if (val == value)
					cout << "EXACT!!!" << endl;
			}

		}

	}

	cout << hex << "x=" << (int) x << endl;
	cout << hex << "y=" << (int) y << endl;

	return value;
}

//uint16_t calculate_bank(uint16_t &value)
dist_t calculate_bank(uint16_t &value, uint16_t &value2)

{
	dist_t temp;
	uint8_t bits;

	uint8_t bank3[] = {
	//3bit
			0x80,//100 - 0x1XX = 0x100...0x1FF
			};

	uint8_t bank4[] = {
	//4bit
			0x20, //0010 - 0x1X - 0x10...0x1F
 			0xA0, //1010 - 0x2XX = 0x200...0x2FF
			0xB0, //1011 - 0x3XX = 0x300...0x3FF
			};

	uint8_t bank5[] = {
	//5bit
			0x30, //00110 - 0x20
			0x38, //00111 - 0x30
			0x40, //01000 - 0x40
			0x48, //01001 - 0x50
			0x50, //01010 - 0x60
			0x58, //01011 - 0x70

			0xC0, //11000 - 0x4XX = 0x400...0x4FF
			0xC8, //11001 - 0x5XX = 0x500...0x5FF
			0xD0, //11010 - 0x6XX = 0x600...0x6FF
			0xD8, //11011 - 0x7XX = 0x700...0x7FF

			};

	uint8_t bank6[] = {
	//6bit
			//0x00,//000000 - 0x00 (BANK + DISTANCE)
			0x04, //000001 - 0x01 (BANK + DISTANCE)
			0x08, //000010 - 0x02 (BANK + DISTANCE)
			0x0C, //000011 - 0x03 (BANK + DISTANCE)

			0x60, //011000 - 0x80
			0x64, //011001 - 0x90
			0x68, //011010 - 0xA0
			0x6C, //011011 - 0xB0
			0x70, //011100 - 0xC0
			0x74, //011101 - 0xD0
			0x78, //011110 - 0xE0
			0x7C, //011111 - 0xF0

			0xE0, //111000 - 0x8XX = 0x800...0x8FF
			0xE4, //111001 - 0x9XX = 0x900...0x9FF
			0xE8, //111010 - 0xAXX = 0xA00...0xAFF
			0xEC, //111011 - 0xBXX = 0xB00...0xBFF
			0xF0, //111100 - 0xCXX = 0xC00...0xCFF
			0xF4, //111101 - 0xDXX = 0xD00...0xDFF
			0xF8, //111110 - 0xEXX = 0xE00...0xEFF
			0xFC, //111111 - 0xFXX = 0xF00...0xFFF

			};

	uint8_t bank7[] = {
	//7bit
			0x10,//0001000 - 0x04 (BANK + DISTANCE)
			0x12, //0001001 - 0x05 (BANK + DISTANCE)
			0x14, //0001010 - 0x06 (BANK + DISTANCE)
			0x16, //0001011 - 0x07 (BANK + DISTANCE)
			};

	uint8_t bank8[] = {
	//8bit
			0x18,//00011000 - 0x08 (BANK + DISTANCE)
			0x19, //00011001 - 0x09 (BANK + DISTANCE)
			0x1A, //00011010 - 0x0A (BANK + DISTANCE)
			0x1B, //00011011 - 0x0B (BANK + DISTANCE)
			0x1C, //00011100 - 0x0C (BANK + DISTANCE)
			0x1D, //00011101 - 0x0D (BANK + DISTANCE)
			0x1E, //00011110 - 0x0E (BANK + DISTANCE)
			0x1F, //00011111 - 0x0F (BANK + DISTANCE)
			};

	uint16_t mask[] = { 0xc0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };

	cout << hex << "value=" << setfill('0') << setw(4) << int(value) << endl;

	int length_zero_count = 0;
	int bit_count = 0;
	const int max_length_zero_count = 6;
	const int max_bit_count = 8;
	int bit_shift = 0;

	uint16_t cc = value;

	while (!(cc & 0x8000)) {
		length_zero_count++;
		bit_count++;
		cc = cc << 1;
		if (length_zero_count == max_length_zero_count)
			break;
	}

	if (length_zero_count == 6) {
		temp.bank = 0;
		temp.shift = 6;
		temp.bits = 0;
		//temp.value=cc;
		temp.value = 0;
		return temp;
	}

	int c = 0;
	int b = 0;
	int val = 0;
	bool s = false;
	//uint16_t p=(value>>8)&mask[2];
	uint16_t p = (value >> 8) & mask[5];
	int bank;

	for (int i = 0; i < sizeof(bank8); i++) {
		if (bank8[i] == p) {
			cout << hex << "BANK8[" << i << "]=" << (int) bank8[i] << endl;
			c = 8;
			b = bank8[i];
			s = true;
			bits = 0;
			if (b == 0x18) {
				val = 0x8;
			}
			if (b == 0x19) {
				val = 0x9;
			}
			if (b == 0x1a) {
				val = 0xA;
			}
			if (b == 0x1b) {
				val = 0xB;
			}
			if (b == 0x1c) {
				val = 0xC;
			}
			if (b == 0x1d) {
				val = 0xD;
			}
			if (b == 0x1e) {
				val = 0xE;
			}
			if (b == 0x1f) {
				val = 0xF;
			}
		}

	}

	if (!s) {

		p = value >> 8;
		p = p & mask[4];

		for (int i = 0; i < sizeof(bank7); i++)

		{
			if (bank7[i] == p) {
				cout << hex << "BANK7[" << i << "]=" << (int) bank7[i] << endl;
				c = 7;
				b = bank7[i];
				s = true;
				bits = 0;

				if (b == 0x10) {
					val = 0x4;
				}
				if (b == 0x12) {
					val = 0x5;
				}
				if (b == 0x14) {
					val = 0x6;
				}
				if (b == 0x16) {
					val = 0x7;
				}

			}
		}

		if (!s) {
			p = value >> 8;
			p = p & mask[3];
			for (int i = 0; i < sizeof(bank6); i++) {
				if (bank6[i] == p) {
					cout << hex << "BANK6[" << i << "]=" << (int) bank6[i]
							<< endl;
					c = 6;
					b = bank6[i];
					s = true;

					if (b == 0x00) {
						val = 0x0;
						bits = 0;
					}
					if (b == 0x04) {
						val = 0x1;
						bits = 0;
					}
					if (b == 0x08) {
						val = 0x2;
						bits = 0;
					}
					if (b == 0x0c) {
						val = 0x3;
						bits = 0;
					}

					if (b == 0x60) {
						val = 0x80;
						bits = 4;
					}
					if (b == 0x64) {
						val = 0x90;
						bits = 4;
					}
					if (b == 0x68) {
						val = 0xA0;
						bits = 4;
					}
					if (b == 0x6C) {
						val = 0xB0;
						bits = 4;
					}
					if (b == 0x70) {
						val = 0xC0;
						bits = 4;
					}
					if (b == 0x74) {
						val = 0xD0;
						bits = 4;
					}
					if (b == 0x78) {
						val = 0xE0;
						bits = 4;
					}
					if (b == 0x7C) {
						val = 0xF0;
						bits = 4;
					}

					if (b == 0xE0) {
						val = 0x800;
						bits = 8;
					}
					if (b == 0xE4) {
						val = 0x900;
						bits = 8;
					}
					if (b == 0xE8) {
						val = 0xA00;
						bits = 8;
					}
					if (b == 0xEC) {
						val = 0xB00;
						bits = 8;
					}
					if (b == 0xF0) {
						val = 0xC00;
						bits = 8;
					}
					if (b == 0xF4) {
						val = 0xD00;
						bits = 8;
					}
					if (b == 0xF8) {
						val = 0xE00;
						bits = 8;
					}
					if (b == 0xFC) {
						val = 0xF00;
						bits = 8;
					}

				}

			}

			if (!s) {
				p = value >> 8;
				p = p & mask[2];

				for (int i = 0; i < sizeof(bank5); i++)

				{
					if (bank5[i] == p) {
						cout << hex << "BANK5[" << i << "]=" << (int) bank5[i]
								<< endl;
						c = 5;
						b = bank5[i];
						s = true;
						//bits=4;

						if (b == 0x30) {
							val = 0x20;
							bits = 4;
						}
						if (b == 0x38) {
							val = 0x30;
							bits = 4;
						}
						if (b == 0x40) {
							val = 0x40;
							bits = 4;
						}
						if (b == 0x48) {
							val = 0x50;
							bits = 4;
						}
						if (b == 0x50) {
							val = 0x60;
							bits = 4;
						}
						if (b == 0x58) {
							val = 0x70;
							bits = 4;
						}

						if (b == 0xc0) {
							val = 0x400;
							bits = 8;
						}
						if (b == 0xc8) {
							val = 0x500;
							bits = 8;
						}
						if (b == 0xd0) {
							val = 0x600;
							bits = 8;
						}
						if (b == 0xd8) {
							val = 0x700;
							bits = 8;
						}

					}
				}

			}

			if (!s) {
				p = value >> 8;
				p = p & mask[1];

				for (int i = 0; i < sizeof(bank4); i++)

				{
					if (bank4[i] == p) {
						cout << hex << "BANK4[" << i << "]=" << (int) bank4[i]
								<< endl;
						c = 4;
						b = bank4[i];
						s = true;

						if (b == 0x20) {
							val = 0x10;
							bits = 4;
						}

						if (b == 0xa0) {
							val = 0x200;
							bits = 8;
						}

						if (b == 0xb0) {
							val = 0x300;
							bits = 8;
						}

					}

				}

			}

						if (!s) {
				p = value >> 8;
				p = p & mask[0];

				for (int i = 0; i < sizeof(bank3); i++)

				{
					if (bank3[i] == p) {
						cout << hex << "BANK3[" << i << "]=" << (int) bank3[i]
								<< endl;
						c = 3;
						b = bank3[i];
						s = true;

						if (b == 0x80) {
							val = 0x100;
							bits = 8;
						}

					}

				}

			}

			}
	}

	//cout << hex << "BANK=" << (int) bank << endl;
	cout << hex << "SHIFT=" << (int) c << endl;
	cout << hex << "VALUE=" << (int) val << endl;

	temp.bank = bank;
	temp.shift = c;
	temp.bits = bits;
	temp.value = val;

	return temp;
}

//uint16_t read_length(uint16_t &reg){
len_t read_length(uint16_t &reg) {

	uint16_t c = 0;
	uint8_t length = 0;
	len_t d;
	int length_zero_count = 0;
	int bit_count = 0;
	const int max_length_zero_count = 9;
	const int max_bit_count = 16;
	int bit_shift = 0;

	c = reg;

	while (!(c & 0x8000)) {
		length_zero_count++;
		bit_count++;
		c = c << 1;
		if (length_zero_count == max_length_zero_count)
			break;
	}

	if (length_zero_count == 0) {
		bit_shift = 1;
		length = 1;
		d.length = length;
		d.shift_c7 = bit_shift;
		d.shift_c9 = 0x10 - bit_shift;
		d.value = c;
		return d;
	}

	if (length_zero_count == 9) {
		bit_shift = 14;
		uint16_t var=((reg<<9)&0xff00);
		length = read_bits(var, 5);
		length = length+0x81;
		d.length = length;
		d.shift_c7 = bit_shift;
		d.shift_c9 = 0x10 - bit_shift;
		d.value = c;
		return d;
	}

	uint8_t len_bits = length_zero_count + 1;

	for (int i = 0; i < len_bits; i++) {
		length = length << 1;
		uint16_t bit;
		bit = (c & 0x8000);
		length = length | (bit >> 15);
		c = c << 1;
	}

	d.length = length;
	bit_shift = (length_zero_count * 2) + 1;
	d.shift_c7 = bit_shift;
	d.shift_c9 = 16 - bit_shift;
	d.value = c;

	return d;
}
;

uint16_t check_bank(uint16_t &value) {
	uint16_t c;
	int length_zero_count = 0;

	cout << "11111";
	c = value;
	cout << "c = " << c << endl;
	cout << "22222";

	cout << "c = " << setfill('0') << setw(4) << c << endl;

	//if (!(c&0x8000)) length_zero_count++;

	while (!(c & 0x8000)) {
		length_zero_count++;
		c = c << 1;
		//cout << "33333";
	}
	//cout << "44444";

	return length_zero_count;

}

void print_reg(uint16_t &reg_c7, uint16_t &reg_c9, uint16_t &shift_c9) {
	cout << hex << "reg_c7=" << setfill('0') << setw(4) << int(reg_c7) << endl;
	cout << hex << "reg_c9=" << setfill('0') << setw(4) << int(reg_c9) << endl;
	//cout << hex << "shift_c9=" << setfill('0') << setw(4) << int(shift_c9) << endl;
	cout << "shift_c9=" << setfill('0') << setw(4) << shift_c9 << endl;
}

void print_title(void) {
	cout << "Donald Duck Mahou no Boushi" << endl;
	cout << "Donald Duck in the Magic Cap" << endl;
	cout << "Donald Duck and The Magical Hat" << endl;
}

void load_reg_a(uint16_t &reg_a, uint8_t* stream, uint16_t &index) {
	reg_a = (stream[index + 1] << 8) | stream[index];

}

void load_reg_a(uint16_t &reg_a, char* stream, int &index) {
	short a, b;
	a = (stream[index + 1] << 8) & 0xff00;
	b = stream[index] & 0x00ff;
	reg_a = a | b;

	//reg_a=(stream[index+1]<<8)|stream[index];

}

uint16_t read_bits(uint16_t &value, uint8_t bits) {
	uint16_t t = 0;
	cout << hex << "val=" << setfill('0') << setw(4) << value << "\n";
	if (bits == 4) {
		t = value & 0xf000;
		cout << hex << "t&0xf000=" << setfill('0') << setw(4) << t << "\n";
		t = (t >> 12) & 0x000f;
		cout << "bits==4" << endl;
	}

	if (bits == 8) {
		t = value & 0xff00;
		cout << hex << "t&0xff00=" << setfill('0') << setw(4) << t << "\n";
		t = (t >> 8) & 0x00ff;
		cout << "bits==8" << endl;
	}

	if (bits == 5) {
		t = value & 0xf100;
		cout << hex << "t&0xf100=" << setfill('0') << setw(4) << t << "\n";
		t = (t >> (16-5)) & 0x00ff;
		cout << "bits==5" << endl;
	}

	if (bits == 0) {
		return t;
	}

	//t=value>>8;
	//t=(16-bits);
	//value=value<<bits;
	//value=value<<t;

	cout << hex << "t=" << t << endl;
	return t;
}

