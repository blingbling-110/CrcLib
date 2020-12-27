#include"CrcTest.h"
#include"CrcCalculator.h"

using namespace std;

void testCalculateCrc()
{
	unsigned char input[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	cout << "0x" << setw((size_t)ceil(WIDTH / 4)) << setfill('0') << hex <<
		calculateCrc<crcType>(input, sizeof(input), WIDTH, POLY, INIT, REFIN, REFOUT, XOROUT) << endl;
}

void testCalculateCrcTable()
{
	crcType table[256];
	calculateCrcTable<crcType>(table, WIDTH,  POLY, REFIN, REFOUT);
	cout << "{" << endl;
	for (size_t i = 0; i < 256; i++)
	{
		cout << "0x" << setw((size_t)ceil(WIDTH / 4)) << setfill('0') << hex << table[i];
		if (i < 255)
		{
			cout << ", ";
		}
		if (i % 8 == 7)
		{
			cout << endl;
		}
	}
	cout << "}";
}

int main()
{
	//testCalculateCrc();
	testCalculateCrcTable();
	cin.get();
	return 0;
}