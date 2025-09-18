#include <iostream>
#include <unordered_map>
using namespace std;

class Hierarchical
{
public:
    unordered_map<uint32_t, uint32_t> PD;
    unordered_map<uint32_t, uint32_t> PT;
    uint32_t BaseAddress = 0x0;

    Hierarchical()
    {
        uint32_t pgadd = 0x400;
        uint32_t fadd = 0x100000;
        for(int i=0;i<1024;i++)
        {
            PD.emplace(BaseAddress+(4*i), pgadd);
            for(int j=0;j<1024;j++)
            {
                PT.emplace(pgadd, fadd);
                pgadd = pgadd+(4*j);
                fadd = fadd+(4*j);
            }
        }
    }

    uint32_t logicalToPhysical(uint32_t logical)
    {
        uint32_t dirIndex = (logical >> 22) & 0x3FF;   //logical shift by 12 bits and then take and with 1111111111
        uint32_t tableIndex = (logical >> 12) & 0x3FF;     //logical shift by 12 bits and then take and with 1111111111
        uint32_t offset = logical & 0xFFF;

        printf("Directory Table Index: 0x%x\nPage Table Index: 0x%x\noffset: 0x%x\n", dirIndex, tableIndex, offset);

        uint32_t tableBaseAddress = PD[BaseAddress + (4*dirIndex)];

        printf("Table Base Address: 0x%x\n", tableBaseAddress);

        uint32_t frameAddress = PT[tableBaseAddress + (tableIndex*4)];

        return frameAddress;
    }
};

int main()
{
    Hierarchical h;

    uint32_t logical = 0;
    while(logical != -1)
    {
        cout << "\nEnter logical address(-1 for exit): 0x";
        
        cin >> logical;

        uint32_t physical = h.logicalToPhysical(logical);
        if(physical != -1)
        {
            printf("Physical address: 0x%x\n", physical);
        }
    }
    return 0;
}