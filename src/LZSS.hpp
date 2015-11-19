#ifndef LZSS_HPP_
#define LZSS_HPP_

#include <iostream>
#include <cstdint>
#include <iomanip> //setw
#include <map>

using namespace std;

const unsigned int BUFFER_SIZE = 0x10000;
const uint32_t DATA_SIZE = 65536;
const uint32_t WINDOW_SIZE = 4096;
const uint16_t MAX_MATCH_LENGTH = 18;
const uint16_t MIN_MATCH_LENGTH = 3;
const uint8_t TEST_BIT = 0x80;

struct dist_t {
	int mask;
	int shift;
	int bank;
	uint8_t bits;
	uint16_t value;

};

struct len_t {
	uint16_t index = 0;
	uint16_t value = 0;
	uint8_t length = 0;
	uint8_t bank = 0;
	uint8_t distance = 0;
	uint8_t shift_c7 = 0;
	uint8_t shift_c9 = 0;
};

//uint16_t read_length(uint16_t &);
len_t read_length(uint16_t &);

uint16_t read_bank(uint16_t &);
//donald_t read_bank(uint16_t &);

//uint16_t read_distance(uint16_t &);
//donald_t read_distance(uint16_t &);

//uint16_t read_bank(uint16_t &);

//uint16_t calculate_bank(uint16_t &);
dist_t calculate_bank(uint16_t &, uint16_t &);

uint16_t check_bank(uint16_t &);

uint32_t check_pos(uint32_t cur_pos);

//void print_reg(void);
void print_reg(uint16_t &, uint16_t &, uint16_t &);
void print_title(void);
void load_reg_a(uint8_t* stream, uint16_t &index);
void load_reg_a(uint16_t &reg_a, uint8_t* stream, uint16_t &index);
void load_reg_a(uint16_t &reg_a, char* stream, int &index);
uint16_t read_bits(uint16_t &, uint8_t);

#endif /* LZSS_HPP_ */
