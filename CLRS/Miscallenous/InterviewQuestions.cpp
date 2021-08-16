#include <iostream> 
using namespace std;

/*
uint8_t BitsSet( uint32_t val )
{
    uint8_t res = 0, pos = 0;
    while ( pos < 32 )
    {
        if ( val & (1 << pos) )
        {
            res++;
        }
        pos++;
    }

    return res;
}

uint8_t BitsSet2( uint32_t val )
{
    int res = 0;
    while ( val )
    {
        res++;
        val = val & (val - 1);
    }
    return res;
}
*/



constexpr uint8_t FIELD_A = 26;
constexpr uint8_t FIELD_B = 6;



struct s_t {
    uint32_t a : FIELD_A;
    uint32_t b : FIELD_B;
;
};









int main()
{
    int x = 0, y = 1;
    if ( x++ && y++ )
    {
        // do something; won't change x or y 
    }
    cout << "x = " << x << " y = " << y << endl;

    int m = 1, n = 1;
    if ( m++ || n-- )
    {
        // do something; won't change m or n
    }
    cout << "m = " << m << " n = " << n << endl;
    s_t val; 
    val.a = 0x20;
    val.b = 0xf;
}

// uint8_t BitsSet( uint32_t n )