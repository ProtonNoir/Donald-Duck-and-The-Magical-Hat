#include <iostream>
#include <fstream>
//#include <cstdlib> //malloc
#include <iomanip> //setw
#include "LZSS.hpp"

using namespace std;

int main(int argc, char **argv)
{
    uint16_t reg_c7 = 0;
    uint16_t reg_c9 = 0;
    uint16_t shift_c9 = 16;

    len_t d;
    dist_t b;

    char _inputData[BUFFER_SIZE] = { 0 };
    char _outputData[BUFFER_SIZE] = { 0 };

    int _inputPosition = 0;
    int _outputPosition = 0;

    //int offset = 0x1078dd;//Title screen
    int offset = 0x117819;//Password screen

    ifstream in_file("Donald Duck Mahou no Boushi (J).smc",
                     ios::in | ios::binary);

    if (!in_file.is_open()) // если файл не открыт
        cout << "Файл не может быть открыт!\n"; // сообщить об этом
    else
    {

        in_file.seekg(offset, ios::beg);
        const unsigned short _decompressionSize = 0x6000;
        uint32_t offsetData = offset;
        in_file.seekg(offsetData, ios::beg);
        in_file.read(_inputData, BUFFER_SIZE);
        in_file.close();

        load_reg_a(reg_c9, _inputData, _inputPosition);
        reg_c7 = reg_c9;
        _inputPosition += 2;

        while (_outputPosition < _decompressionSize)
        {
            cout << hex << "Input position = [" << setw(4)
                 << (int) _inputPosition << "]";
            cout << hex << "\tOutput position = [" << setw(4)
                 << (int) _outputPosition << "]" << endl;

            uint8_t code;

            code = _inputData[_inputPosition++];
            cout << hex << "code = [" << int(code) << "]" << endl;
            if (_outputPosition >= _decompressionSize)
                break;

            for (int i = 0; i < 0x08; i++)
            {

                if ((code & TEST_BIT) == TEST_BIT)
                {
                    cout << hex << "LITERAL = ["
                         << int(_inputData[_inputPosition] & 0xff) << "]"
                         << endl;
                    uint8_t lit;
                    lit = _inputData[_inputPosition++] & 0xff;
                    _outputData[_outputPosition++] = lit;

                    if ((_outputPosition == _decompressionSize)
                            || (_outputPosition > _decompressionSize))
                        break;
                }

                else

                {
                 cout << hex << "___LZ___ " << endl;

                    uint16_t lz_len;
                    uint16_t lz_off;
                    uint16_t lz_dist;

                    print_reg(reg_c7, reg_c9, shift_c9);

                    cout << "...SEARCHING LENGTH" << endl;

                    d = read_length(reg_c7);
                    cout << hex << " D.LENGTH = " << int(d.length)
                         << " D.SHIFT_C7 = " << int(d.shift_c7)
                         << " D.SHIFT_C9 = " << int(d.shift_c9)
                         << " D.VALUE = " << int(d.value) << endl;
                    shift_c9 += d.shift_c7;
                    cout << hex << "shift_c9=" << setfill('0') << setw(4)
                         << int(shift_c9) << endl;

                    if (shift_c9 > 16)
                    {
                        reg_c7 = ((reg_c7 << d.shift_c7) & 0xffff);
                        cout << hex << "!!!" << setfill('0') << setw(4)
                          << "REG_C7=[" << int(reg_c7) << "]" << endl;

                       // int shift = shift_c9;
                        shift_c9 = shift_c9 - 16;

                        int mask = 0;
                        if (shift_c9 == 1)
                            mask = 0x10000;
                        if (shift_c9 == 2)
                            mask = 0x30000;
                        if (shift_c9 == 3)
                            mask = 0x70000;
                        if (shift_c9 == 4)
                            mask = 0xf0000;
                        if (shift_c9 == 5)
                            mask = 0x1f0000;
                        if (shift_c9 == 6)
                            mask = 0x3f0000;
                        if (shift_c9 == 7)
                            mask = 0x7f0000;
                        if (shift_c9 == 8)
                            mask = 0xff0000;
                        if (shift_c9 == 9)
                            mask = 0x1ff0000;
                        if (shift_c9 == 10)
                            mask = 0x3ff0000;
                        if (shift_c9 == 11)
                            mask = 0x7ff0000;
                        if (shift_c9 == 12)
                            mask = 0xfff0000;
                        if (shift_c9 == 13)
                            mask = 0x1fff0000;
                        if (shift_c9 == 14)
                            mask = 0x3fff0000;
                        if (shift_c9 == 15)
                            mask = 0x7fff0000;
                        if (shift_c9 == 16)
                            mask = 0xffff0000;
                        if (shift_c9 == 0)
                            mask = 0x0000;


                        int x;
                        x = (reg_c9 << 16) & mask;
                        x = x >> 16;

                        x = (reg_c9 << (shift_c9 - 16));
                        x = (x >> 16) & 0xffff;

                        cout << hex << "x=" << setfill('0') << setw(4) << int(x)
                             << endl;

                        reg_c7 = x;

                        load_reg_a(reg_c9, _inputData, _inputPosition);
                        _inputPosition += 2;

                        reg_c7 = reg_c7
                                 | ((reg_c9 >> (16 - shift_c9) & 0xffff));

                    }

                    else
                    {
                        if (shift_c9 == 16)
                        {
                            reg_c7 = reg_c9;

                        }

                        else
                        {

                            reg_c7 = ((reg_c7 << d.shift_c7) & 0xffff);
                            reg_c7 = reg_c7
                                     | ((reg_c9 >> (16 - shift_c9) & 0xffff));

                        }

                    }

                    cout << hex << "!!!" << setfill('0') << setw(4)
                         << int((reg_c9 >> (16 - shift_c9) & 0xffff))
                         << endl;
                    cout << hex << "!!!" << setfill('0') << setw(4)
                         << int(reg_c9 << shift_c9) << endl;

                    cout << "AFTER LENGTH:" << endl;
                    print_reg(reg_c7, reg_c9, shift_c9);

                    cout << "...SEARCHING DISTANCE" << endl;

                    b = calculate_bank(reg_c7, reg_c9);


                    cout << hex << "b.shift=" << setfill('0') << setw(4)
                         << int(b.shift) << endl;
                    cout << hex << "b.bits=" << setfill('0') << setw(4)
                         << int(b.bits) << endl;


                    shift_c9 += b.shift;

                    if (shift_c9 > 16)

                    {

                        shift_c9 = shift_c9 - 16;
                        int mask = 0;
                        if (shift_c9 == 1)
                            mask = 0x10000;
                        if (shift_c9 == 2)
                            mask = 0x30000;
                        if (shift_c9 == 3)
                            mask = 0x70000;
                        if (shift_c9 == 4)
                            mask = 0xf0000;
                        if (shift_c9 == 5)
                            mask = 0x1f0000;
                        if (shift_c9 == 6)
                            mask = 0x3f0000;
                        if (shift_c9 == 7)
                            mask = 0x7f0000;
                        if (shift_c9 == 8)
                            mask = 0xff0000;
                        if (shift_c9 == 9)
                            mask = 0x1ff0000;
                        if (shift_c9 == 10)
                            mask = 0x3ff0000;
                        if (shift_c9 == 11)
                            mask = 0x7ff0000;
                        if (shift_c9 == 12)
                            mask = 0xfff0000;
                        if (shift_c9 == 13)
                            mask = 0x1fff0000;
                        if (shift_c9 == 14)
                            mask = 0x3fff0000;
                        if (shift_c9 == 15)
                            mask = 0x7fff0000;
                        if (shift_c9 == 16)
                            mask = 0xffff0000;
                        if (shift_c9 == 0)
                            mask = 0x0000;

                        int y;
                        y = (reg_c9 << 16) & mask;
                        y = y >> 16;
                        cout << hex << "y=" << setfill('0') << setw(4) << int(y)
                             << endl;

                        y = (reg_c9 << (shift_c9 - 16));
                        y = (y >> 16) & 0xffff;

                        cout << hex << "y=" << setfill('0') << setw(4) << int(y)
                             << endl;

                        reg_c7 = y;

                        load_reg_a(reg_c9, _inputData, _inputPosition);
                        _inputPosition += 2;

                        reg_c7 = reg_c7
                                 | ((reg_c9 >> (16 - shift_c9) & 0xffff));

                    }

                    else
                    {
                        if (shift_c9 == 16)
                        {
                            reg_c7 = reg_c9;
                        }

                        else
                        {
                            reg_c7 = ((reg_c7 << b.shift) & 0xffff);
                            reg_c7 = reg_c7 | ((reg_c9 >> (16 - shift_c9) & 0xffff));
                        }

                    }

                    cout << "AFTER BANK:" << endl;
                    print_reg(reg_c7, reg_c9, shift_c9);

                    shift_c9 += b.bits;

                    if (b.bits==0)

                    {
                        cout << hex << "b.value=" << setfill('0') << setw(4)
                             << int(b.value) << endl;
                        //--reg_c7 = ((reg_c7 << b.shift) & 0xffff);
                        //--reg_c7 = reg_c7
                        //--         | ((reg_c9 >> (16 - shift_c9) & 0xffff));
                        lz_dist = b.value;
                    }

                    else

                    {
                        lz_dist = b.value;
                        lz_dist = lz_dist | (read_bits(reg_c7, b.bits));
                        //--cout << "...NOT ZERO" << endl;
                        //-- cout << hex << "b.bits=" << setfill('0') << setw(4)
                        //--     << int(b.bits) << endl;
                    }

                    cout << "AFTER DISTANCE:" << endl;
                    print_reg(reg_c7, reg_c9, shift_c9);

                    if (shift_c9 > 16)

                    {

                        shift_c9 = shift_c9 - 16;
                        int mask = 0;
                        if (shift_c9 == 1)
                            mask = 0x10000;
                        if (shift_c9 == 2)
                            mask = 0x30000;
                        if (shift_c9 == 3)
                            mask = 0x70000;
                        if (shift_c9 == 4)
                            mask = 0xf0000;
                        if (shift_c9 == 5)
                            mask = 0x1f0000;
                        if (shift_c9 == 6)
                            mask = 0x3f0000;
                        if (shift_c9 == 7)
                            mask = 0x7f0000;
                        if (shift_c9 == 8)
                            mask = 0xff0000;
                        if (shift_c9 == 9)
                            mask = 0x1ff0000;
                        if (shift_c9 == 10)
                            mask = 0x3ff0000;
                        if (shift_c9 == 11)
                            mask = 0x7ff0000;
                        if (shift_c9 == 12)
                            mask = 0xfff0000;
                        if (shift_c9 == 13)
                            mask = 0x1fff0000;
                        if (shift_c9 == 14)
                            mask = 0x3fff0000;
                        if (shift_c9 == 15)
                            mask = 0x7fff0000;
                        if (shift_c9 == 16)
                            mask = 0xffff0000;
                        if (shift_c9 == 0)
                            mask = 0x0000;

                        int v;
                        v = (reg_c9 << 16) & mask;
                        v = v >> 16;
                       cout << hex << "v=" << setfill('0') << setw(4) << int(v)
                        << endl;

                        v = (reg_c9 << (shift_c9 - 16));
                        v = (v >> 16) & 0xffff;

                        cout << hex << "v=" << setfill('0') << setw(4) << int(v)
                         << endl;

                        reg_c7 = v;

                        load_reg_a(reg_c9, _inputData, _inputPosition);
                        _inputPosition += 2;

                        reg_c7 = reg_c7
                                 | ((reg_c9 >> (16 - shift_c9) & 0xffff));

                    }

                    else
                    {
                        if (shift_c9 == 16)
                        {
                            reg_c7 = reg_c9;
                        }

                        else
                        {
                            reg_c7 = ((reg_c7 << b.bits) & 0xffff);
                            reg_c7 = reg_c7 | ((reg_c9 >> (16 - shift_c9) & 0xffff));
                        }

                    }


                   print_reg(reg_c7, reg_c9, shift_c9);

                    cout << hex << "\nInput position = [" << setw(4)
                         << (int) _inputPosition << "]" << endl;
                    cout << hex << "\tOutput position = [" << setw(4)
                         << (int) _outputPosition << "]" << endl;
                    lz_len = d.length + 1;
                    cout << hex << " LENGTH = " << lz_len << endl;
                    lz_dist = lz_dist + 1;
                    cout << hex << " DISTANCE = " << lz_dist << endl;
                    lz_off = _outputPosition - lz_dist;
                    cout << hex << " OFFSET = " << lz_off << endl;

                    for (int j = 0; j < lz_len; j++)
                    {
                        _outputData[_outputPosition++] = _outputData[lz_off++];
                        if ((_outputPosition == _decompressionSize)
                                || (_outputPosition > _decompressionSize))
                            break;
                    }

                }
                code <<= 1;
            }


    }
    ofstream out_file("Donald Duck Mahou no Boushi (J)_decomp_password.bin",
                      ios::out | ios::binary);
    if (!out_file.is_open()) // если файл не открыт
        cout << "Файл не может быть открыт!\n"; // сообщить об этом
    else
    {
        out_file.write(_outputData, _outputPosition);
        out_file.close();
    }

    return 0;

}

return -1;
}
