#include <stdlib.h>
#include <graphx.h>
#include <keypadc.h>
#include <string.h>

#define DETAILS_SCREEN 0x0
#define TABLE_SCREEN 0x1

typedef struct
{
    char name[14];
    char symbol[3];
    char mass[7];
    char density[6];
    char electronegativity[5];
    char melt[7];
    char boil[7];
    uint16_t year;
    uint8_t radius;
    uint16_t firstIon;
    uint8_t group;
    uint8_t neutrons;
}Element;

int main(void)
{

    static const Element elements[118] = {
        {"Hydrogen     ", "H ", "1.0079", "0.09 ", "2.20", "13.99 ", "20.271", 1766, 32, 1312, 2, 0},
        {"Helium       ", "He", "4.0026", "0.179", "N/A ", "0.95  ", "4.222 ", 1868, 37, 2372, 7, 2},
        {"Lithium      ", "Li", "6.941 ", "0.535", "0.98", "453.65", "1603  ", 1817, 130, 520, 0, 4},
        {"Beryllium    ", "Be", "9.0122", "1.848", "1.57", "1560  ", "3243  ", 1828, 99, 899, 1, 5},
        {"Boron        ", "B ", "10.81 ", "2.46 ", "2.04", "2349  ", "4200  ", 1808, 84, 801, 4, 6},
        {"Carbon       ", "C ", "12.011", "2.26 ", "2.55", "N/A   ", "3915  ", 0, 75, 1086, 2, 6},
        {"Nitrogen     ", "N ", "14.007", "1.251", "3.04", "63.15 ", "77.355", 1772, 71, 1402, 2, 7},
        {"Oxygen       ", "O ", "15.999", "1.429", "3.44", "54.36 ", "90.188", 1774, 64, 1314, 2, 8},
        {"Fluorine     ", "F ", "18.998", "1.696", "3.98", "53.48 ", "85.03 ", 1886, 60, 1681, 6, 10},
        {"Neon         ", "Ne", "20.18 ", "0.9  ", "N/A ", "24.56 ", "27.104", 1898, 62, 2081, 7, 10},
        {"Sodium       ", "Na", "22.99 ", "0.968", "0.93", "370.94", "1156.1", 1807, 160, 496, 0, 12},
        {"Magnesium    ", "Mg", "24.305", "1.738", "1.31", "923   ", "1363  ", 1755, 140, 738, 1, 12},
        {"Aluminium    ", "Al", "26.982", "2.7  ", "1.61", "933.47", "2743  ", 1827, 124, 578, 5, 14},
        {"Silicon      ", "Si", "28.086", "2.33 ", "1.9 ", "1687  ", "3538  ", 1824, 114, 786, 4, 14},
        {"Phosphorus   ", "P ", "30.974", "1.823", "2.19", "N/A   ", "N/A   ", 1669, 109, 1012, 2, 16},
        {"Sulfur       ", "S ", "32.066", "1.96 ", "2.58", "388.36", "717.8 ", 0, 104, 1000, 2, 16},
        {"Chlorine     ", "Cl", "35.453", "3.214", "3.16", "171.6 ", "239.11", 1774, 100, 1251, 6, 18},
        {"Argon        ", "Ar", "39.948", "1.784", "N/A ", "83.81 ", "87.302", 1894, 101, 1521, 7, 22},
        {"Potassium    ", "K ", "39.098", "0.856", "0.82", "336.7 ", "1032  ", 1807, 200, 419, 0, 20},
        {"Calcium      ", "Ca", "40.078", "1.55 ", "1.00", "1115  ", "1757  ", 1808, 174, 590, 1, 20},
        {"Scandium     ", "Sc", "44.956", "2.985", "1.36", "1814  ", "3109  ", 1878, 159, 631, 3, 24},
        {"Titanium     ", "Ti", "47.867", "4.507", "1.54", "1941  ", "3560  ", 1791, 148, 658, 3, 26},
        {"Vanadium     ", "V ", "50.942", "6.11 ", "1.63", "2183  ", "3680  ", 1801, 144, 650, 3, 28},
        {"Chromium     ", "Cr", "51.996", "7.14 ", "1.66", "2180  ", "2944  ", 1797, 130, 653, 3, 28},
        {"Manganese    ", "Mn", "54.938", "7.47 ", "1.55", "1519  ", "2334  ", 1774, 129, 717, 3, 30},
        {"Iron         ", "Fe", "55.845", "7.874", "1.83", "1811  ", "3134  ", 0, 124, 759, 3, 30},
        {"Cobalt       ", "Co", "58.933", "8.9  ", "1.88", "1768  ", "3200  ", 1735, 118, 758, 3, 32},
        {"Nickel       ", "Ni", "58.693", "8.908", "1.91", "1728  ", "3003  ", 1751, 117, 737, 3, 31},
        {"Copper       ", "Cu", "36.546", "8.92 ", "1.9 ", "1357.8", "2835  ", 0, 122, 745, 3, 35},
        {"Zinc         ", "Zn", "65.39 ", "7.14 ", "1.65", "692.68", "1180  ", 1746, 120, 906, 3, 35},
        {"Gallium      ", "Ga", "69.723", "5.904", "1.81", "302.91", "2673  ", 1875, 123, 579, 5, 39},
        {"Germanium    ", "Ge", "72.61 ", "5.323", "2.01", "1211.4", "3106  ", 1886, 120, 762, 4, 41},
        {"Arsenic      ", "As", "74.922", "5.727", "2.18", "N/A   ", "887   ", 1250, 120, 947, 4, 42},
        {"Selenium     ", "Se", "78.96 ", "4.819", "2.55", "494   ", "958   ", 1817, 118, 941, 2, 45},
        {"Bromine      ", "Br", "79.904", "3.12 ", "2.96", "265.8 ", "332.0 ", 1826, 117, 1140, 6, 45},
        {"Krypton      ", "Kr", "83.8  ", "3.75 ", "3.00", "115.78", "119.93", 1898, 116, 1351, 7, 48},
        {"Rubidium     ", "Rb", "85.468", "1.532", "0.82", "312.45", "961   ", 1861, 215, 403, 0, 48},
        {"Strontium    ", "Sr", "87.62 ", "2.63 ", "0.95", "1050  ", "1650  ", 1790, 190, 549, 1, 50},
        {"Yttrium      ", "Y ", "88.906", "4.472", "1.22", "1799  ", "3203  ", 1794, 176, 616, 3, 50},
        {"Zirconium    ", "Zr", "91.224", "6.511", "1.33", "2128  ", "4650  ", 1789, 164, 660, 3, 51},
        {"Niobium      ", "Nb", "92.906", "8.57 ", "1.6 ", "2750  ", "5017  ", 1801, 156, 664, 3, 52},
        {"Molybdenum   ", "Mo", "95.94 ", "10.28", "2.16", "2896  ", "4912  ", 1778, 146, 685, 3, 54},
        {"Technetium   ", "Tc", "[98]  ", "11.5 ", "1.9 ", "2430  ", "4538  ", 1937, 138, 702, 3, 55},
        {"Ruthenium    ", "Ru", "101.07", "12.37", "2.2 ", "2607  ", "4423  ", 1844, 136, 711, 3, 57},
        {"Rhodium      ", "Rh", "102.91", "12.45", "2.28", "2237  ", "3968  ", 1803, 134, 720, 3, 58},
        {"Palladium    ", "Pd", "106.42", "12.02", "2.2 ", "1828.1", "3236  ", 1803, 130, 805, 3, 60},
        {"Silver       ", "Ag", "107.87", "10.49", "1.93", "1234.9", "2435  ", 0, 136, 731, 3, 61},
        {"Cadmium      ", "Cd", "112.41", "8.65 ", "1.69", "594.22", "1040  ", 1817, 140, 868, 3, 64},
        {"Indium       ", "In", "114.82", "7.31 ", "1.78", "429.75", "2345  ", 1863, 142, 558, 5, 66},
        {"Tin          ", "Sn", "118.71", "7.31 ", "1.96", "505.08", "2875  ", 0, 140, 709, 5, 69},
        {"Antimony     ", "Sb", "121.76", "6.697", "2.05", "903.78", "1908  ", 0, 140, 834, 4, 71},
        {"Tellurium    ", "Te", "127.6 ", "6.24 ", "2.1 ", "722.66", "1261  ", 1782, 137, 869, 4, 76},
        {"Iodine       ", "I ", "126.91", "4.94 ", "2.66", "386.85", "457.4 ", 1811, 136, 1008, 6, 74},
        {"Xenon        ", "Xe", "131.29", "5.9  ", "2.6 ", "161.40", "165.05", 1898, 136, 1170, 7, 77},
        {"Cesium       ", "Cs", "132.91", "1.879", "0.79", "301.7 ", "944   ", 1860, 238, 376, 0, 78},
        {"Barium       ", "Ba", "137.33", "3.51 ", "0.89", "1000  ", "2118  ", 1808, 206, 503, 1, 81},
        {"Lanthanum    ", "La", "138.91", "6.146", "1.1 ", "1193  ", "3737  ", 1839, 194, 538, 8, 82},
        {"Cerium       ", "Ce", "140.12", "6.689", "1.12", "1068  ", "3716  ", 1803, 184, 528, 8, 82},
        {"Praseodymium ", "Pr", "140.91", "6.64 ", "1.13", "1208  ", "3403  ", 1841, 190, 523, 8, 82},
        {"Neodymium    ", "Nd", "144.24", "7.01 ", "1.14", "1297  ", "3347  ", 1885, 188, 530, 8, 84},
        {"Promethium   ", "Pm", "[145] ", "7.264", "N/A ", "1315  ", "3273  ", 1914, 186, 535, 8, 84},
        {"Samarium     ", "Sm", "150.36", "7.353", "1.17", "1345  ", "2173  ", 1879, 185, 543, 8, 88},
        {"Europium     ", "Eu", "151.97", "5.244", "N/A ", "1099  ", "1802  ", 1901, 183, 547, 8, 89},
        {"Gadolinium   ", "Gd", "157.25", "7.901", "1.2 ", "1585  ", "3273  ", 1880, 182, 592, 8, 93},
        {"Terbium      ", "Tb", "158.93", "8.219", "N/A ", "1629  ", "3396  ", 1843, 181, 564, 8, 94},
        {"Dysprosium   ", "Dy", "162.5 ", "8.551", "1.22", "1680  ", "2840  ", 1886, 180, 572, 8, 97},
        {"Holmium      ", "Ho", "164.93", "8.795", "1.23", "1734  ", "2873  ", 1878, 179, 581, 8, 98},
        {"Erbium       ", "Er", "167.26", "9.066", "1.24", "1802  ", "3141  ", 1842, 177, 589, 8, 99},
        {"Thulium      ", "Tm", "168.93", "9.321", "1.25", "1818  ", "2003  ", 1879, 177, 596, 8, 100},
        {"Ytterbium    ", "Yb", "173.04", "6.57 ", "N/A ", "1097  ", "1469  ", 1878, 178, 603, 8, 103},
        {"Lutetium     ", "Lu", "174.97", "9.841", "1.27", "1925  ", "3675  ", 1907, 174, 524, 8, 104},
        {"Hafnium      ", "Hf", "178.49", "13.31", "1.3 ", "2506  ", "4876  ", 1923, 164, 680, 3, 106},
        {"Tantalum     ", "Ta", "180.95", "16.65", "1.5 ", "3290  ", "5731  ", 1802, 158, 761, 3, 108},
        {"Tungsten     ", "W ", "183.84", "19.25", "2.36", "3695  ", "6203  ", 1783, 150, 770, 3, 110},
        {"Rhenium      ", "Re", "186.21", "21.02", "1.9 ", "3459  ", "5869  ", 1925, 141, 760, 3, 111},
        {"Osmium       ", "Os", "190.23", "22.61", "2.2 ", "3306  ", "5285  ", 1803, 136, 840, 3, 114},
        {"Iridium      ", "Ir", "192.22", "22.65", "2.2 ", "2719  ", "4403  ", 1803, 132, 880, 3, 115},
        {"Platinium    ", "Pt", "195.08", "21.09", "2.28", "2041.4", "4098  ", 1735, 130, 870, 3, 117},
        {"Gold         ", "Au", "196.97", "19.3 ", "2.54", "1337.3", "3243  ", 0, 130, 890, 3, 118},
        {"Mercury      ", "Hg", "200.59", "13.53", "2.00", "234.32", "629.88", 0, 132, 1007, 3, 121},
        {"Thallium     ", "Tl", "204.38", "11.85", "1.62", "577   ", "1746  ", 1861, 144, 589, 5, 123},
        {"Lead         ", "Pb", "207.2 ", "11.34", "2.33", "600.61", "2022  ", 0, 145, 716, 5, 125},
        {"Bismuth      ", "Bi", "208.98", "9.78 ", "2.02", "544.7 ", "1837  ", 0, 150, 703, 5, 126},
        {"Polonium     ", "Po", "[209] ", "9.196", "2.00", "527   ", "1235  ", 1898, 142, 812, 4, 125},
        {"Astatine     ", "At", "[210] ", "N/A  ", "2.2 ", "575   ", "610   ", 1940, 148, 899, 6, 125},
        {"Radon        ", "Rn", "[222] ", "9.73 ", "N/A ", "202   ", "211.5 ", 1900, 146, 1037, 7, 136},
        {"Francium     ", "Fr", "[223] ", "N/A  ", "0.7 ", "300   ", "950   ", 1939, 242, 380, 0, 136},
        {"Radium       ", "Ra", "[226] ", "5    ", "0.9 ", "1233  ", "2010  ", 1898, 211, 509, 1, 138},
        {"Actinium     ", "Ac", "[227] ", "10.07", "1.1 ", "1500  ", "3500  ", 1899, 201, 670, 9, 138},
        {"Thorium      ", "Th", "232.04", "11.72", "1.3 ", "2023  ", "5061  ", 1828, 190, 587, 9, 142},
        {"Protactinium ", "Pa", "231.04", "15.37", "1.5 ", "1841  ", "4300  ", 1913, 184, 568, 9, 140},
        {"Uranium      ", "U ", "238.03", "19.05", "1.38", "1405.3", "4404  ", 1841, 183, 598, 9, 146},
        {"Neptunium    ", "Np", "[237] ", "20.45", "1.36", "912   ", "4447  ", 1940, 180, 605, 9, 144},
        {"Plutonium    ", "Pu", "[244] ", "19.82", "1.28", "912.5 ", "3505  ", 1940, 180, 585, 9, 150},
        {"Americium    ", "Am", "[243] ", "N/A  ", "1.3 ", "1449  ", "2880  ", 1944, 173, 578, 9, 148},
        {"Curium       ", "Cm", "[247] ", "13.51", "1.3 ", "1613  ", "3383  ", 1944, 168, 581, 9, 151},
        {"Berkelium    ", "Bk", "[247] ", "14.78", "1.3 ", "1259  ", "2900  ", 1949, 168, 601, 9, 150},
        {"Californium  ", "Cf", "[251] ", "15.1 ", "1.3 ", "1173  ", "1743  ", 1950, 168, 608, 9, 153},
        {"Einsteinium  ", "Es", "[252] ", "8.84 ", "1.3 ", "1133  ", "1269  ", 1952, 165, 619, 9, 153},
        {"Fermium      ", "Fm", "[257] ", "N/A  ", "1.3 ", "1800  ", "N/A   ", 1952, 167, 627, 9, 157},
        {"Mendelevium  ", "Md", "[258] ", "N/A  ", "1.3 ", "1100  ", "N/A   ", 1955, 173, 635, 9, 157},
        {"Nobelium     ", "No", "[259] ", "N/A  ", "1.3 ", "1100  ", "N/A   ", 1958, 176, 642, 9, 157},
        {"Lawrencium   ", "Lr", "262.11", "N/A  ", "1.3 ", "1900  ", "N/A   ", 1961, 161, 470, 9, 159},
        {"Rutherfordium", "Rf", "265.12", "23.2 ", "N/A ", "2400  ", "5800  ", 1964, 157, 580, 3, 157},
        {"Dubnium      ", "Db", "268.13", "29.3 ", "N/A ", "N/A   ", "N/A   ", 1967, 149, 665, 3, 157},
        {"Seaborgium   ", "Sg", "271.13", "35   ", "N/A ", "N/A   ", "N/A   ", 1974, 143, 757, 3, 157},
        {"Bohrium      ", "Bh", "[270] ", "37.1 ", "N/A ", "N/A   ", "N/A   ", 1981, 141, 740, 3, 157},
        {"Hassium      ", "Hs", "277.15", "40.7 ", "N/A ", "N/A   ", "N/A   ", 1964, 134, 730, 3, 157},
        {"Meitnerium   ", "Mt", "276.15", "37.4 ", "N/A ", "N/A   ", "N/A   ", 1982, 129, 800, 3, 159},
        {"Darmstadtium ", "Ds", "281.16", "34.8 ", "N/A ", "N/A   ", "N/A   ", 1987, 128, 960, 3, 171},
        {"Roentgenium  ", "Rg", "280.16", "28.7 ", "N/A ", "N/A   ", "N/A   ", 1994, 121, 1020, 3, 162},
        {"Copernicium  ", "Cn", "285.17", "23.7 ", "N/A ", "N/A   ", "357   ", 1996, 122, 1155, 3, 165},
        {"Nihonium     ", "Nh", "284.18", "16   ", "N/A ", "700   ", "1430  ", 2004, 136, 707, 10, 170},
        {"Flerovium    ", "Fl", "289.19", "14   ", "N/A ", "340   ", "420   ", 1998, 143, 832, 10, 171},
        {"Moscovium    ", "Mc", "288.19", "13.5 ", "N/A ", "670   ", "1400  ", 2004, 162, 538, 10, 172},
        {"Livermorium  ", "Lv", "[293] ", "12.9 ", "N/A ", "708.5 ", "1085  ", 2000, 175, 664, 10, 173},
        {"Tennessine   ", "Ts", "[294] ", "7.2  ", "N/A ", "673   ", "823   ", 2009, 165, 737, 10, 177},
        {"Oganesson    ", "Og", "[294] ", "5    ", "N/A ", "N/A   ", "350   ", 2002, 157, 860, 10, 175}
    };
    
    static const uint8_t colors[11] = {228,230,7,234,29,241,23,157,47,217,149};
    uint8_t tempAtom;
    int tempPosX;
    uint8_t tempPosY;
    kb_key_t key, enterKey;
    
    static const uint8_t nonNobleGases[5] = {1, 7, 8, 9, 17};
    
    static const char *groups[11] = {"alkali metal", "alkaline metal", "non-metal", "transition metal", "metaloid", "other metal", "halogen", "noble gas", "lanthanoid", "actinoid", "unknown"};
    
    static const uint8_t mainArr[10][18] = {
        {1  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,2  },
        {3  ,4  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,5  ,6  ,7  ,8  ,9  ,10 },
        {11 ,12 ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,13 ,14 ,15 ,16 ,17 ,18 },
        {19 ,20 ,21 ,22 ,23 ,24 ,25 ,26 ,27 ,28 ,29 ,30 ,31 ,32 ,33 ,34 ,35 ,36 },
        {37 ,38 ,39 ,40 ,41 ,42 ,43 ,44 ,45 ,46 ,47 ,48 ,49 ,50 ,51 ,52 ,53 ,54 },
        {55 ,56 ,0  ,72 ,73 ,74 ,75 ,76 ,77 ,78 ,79 ,80 ,81 ,82 ,83 ,84 ,85 ,86 },
        {87 ,88 ,0  ,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118},
        {0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  },
        {0  ,0  ,0  ,57 ,58 ,59 ,60 ,61 ,62 ,63 ,64 ,65 ,66 ,67 ,68 ,69 ,70 ,71 },
        {0  ,0  ,0  ,89 ,90 ,91 ,92 ,93 ,94 ,95 ,96 ,97 ,98 ,99 ,100,101,102,103}
    };
    gfx_Begin();
    //setup
    gfx_SetTextFGColor(255);
    gfx_SetTextBGColor(5);
    gfx_SetTextTransparentColor(5);
    gfx_SetDrawScreen();
    gfx_ZeroScreen();
    gfx_SetColor(224);
    gfx_FillRectangle_NoClip(295, 212, 20, 20);
    gfx_SetTextScale(2,2);
    gfx_PrintStringXY("Periodic Table CE", 50, 3);
    gfx_PrintStringXY("X", 298, 215);
    gfx_SetTextScale(1,1);
    //Initialize starting position 
    int i = 1, j = 0, currAtom = 1, initialPosI = 1, initialPosJ = 0;
    bool first = true, redrawTable = true, prevArrowKey = false, prevEnterKey = false, arrowOnDetails = false, isAGas, screen;
    const Element* el;
    
    do
    {
        kb_Scan();
        key = kb_Data[7];
        enterKey = kb_Data[6];
        gfx_SetColor(0);
        if (redrawTable){
            gfx_FillRectangle_NoClip(0,25,320,180);
            //Draw the table
            for(int i=0; i<10; i++) {
                tempPosY = 32+17*i;
                for(int j=0;j<18;j++) {
                    tempAtom = mainArr[i][j];
                    if (tempAtom){
                        gfx_SetColor(colors[elements[tempAtom-1].group]);
                        tempPosX = 8+17*j;
                        gfx_FillRectangle_NoClip(tempPosX, tempPosY, 16, 16);
                        tempPosX += (4*(elements[tempAtom-1].symbol[1]==' ') + 2*(elements[tempAtom-1].symbol[1]=='i') + 2*(elements[tempAtom-1].symbol[1]=='l'));
                        gfx_PrintStringXY(elements[tempAtom-1].symbol,tempPosX, tempPosY+4);
                        if (tempAtom == currAtom && !first){
                            //in case the cursor position changed when we were on the details screen
                            initialPosI = i;
                            initialPosJ = j;
                        }
                    }
                }
            }
            i = initialPosI;
            j = initialPosJ;
            
            gfx_SetColor(255);

            gfx_HorizLine_NoClip(50,175,5);
            gfx_HorizLine_NoClip(50,191,5);
            gfx_VertLine_NoClip(50,122,69);
            gfx_Rectangle_NoClip(7+17*j,31+17*i,18,18);
            redrawTable = false;
            screen = TABLE_SCREEN;
        }
        
        if (first){
            key = kb_Up;
            first = false;
        }
        if (key && !prevArrowKey && screen == TABLE_SCREEN) {
            gfx_SetColor(0);
            gfx_Rectangle_NoClip(7+17*j,31+17*i,18,18);
            gfx_FillRectangle_NoClip(40, 205, 250, 32);
            do {
                switch (key)
                {
                    case kb_Down:
                           i += 1-10*(i==9);
                        break;
                    case kb_Right:
                           j += 1-18*(j==17);
                        break;
                    case kb_Up:
                           i -= 1-10*(!i);
                        break;
                    case kb_Left:
                           j -= 1-18*(!j);
                        break;
                }
                currAtom = mainArr[i][j];
            } while (!currAtom);
            
            el = &elements[currAtom-1];
            gfx_SetColor(255);
            gfx_Rectangle_NoClip(7+17*j,31+17*i,18,18);
        }
        
        if ((key && !prevArrowKey) || arrowOnDetails) {
            //redraw the element name and box at the bottom of the screen
            gfx_SetTextScale(2,2);
            gfx_PrintStringXY(el->name, 90, 215);
            gfx_SetColor(colors[el->group]);
            gfx_FillRectangle_NoClip(40, 205, 32, 32);
            gfx_PrintStringXY(el->symbol,41 + (8*(el->symbol[1]==' ') + 3*(el->symbol[1]=='i') + 3*(el->symbol[1]=='l')), 214);
            gfx_SetColor(0);
            arrowOnDetails = false;
        }

        if (key && !prevArrowKey && screen == DETAILS_SCREEN && (key == kb_Left || key == kb_Right)) {
            currAtom += (key == kb_Right) - (key == kb_Left);
            currAtom += 118*(!currAtom) - 118*(currAtom == 119);
            enterKey = kb_Enter;
            el = &elements[currAtom-1];
            arrowOnDetails = true;
            gfx_FillRectangle_NoClip(40, 205, 250, 32);
        }
        
        if (enterKey == kb_Enter && !prevEnterKey){
            if (!arrowOnDetails){
                //only redraw the table if we aren't changing elements on the details screen
                redrawTable = !screen;
            }
            gfx_FillRectangle_NoClip(0,25,320,180);
            gfx_SetTextScale(2,2);
            gfx_PrintStringXY(">   <", 300, 35);
            //gfx_PrintStringXY("<", 10, 35);
            gfx_SetTextScale(1,1);
            
            gfx_PrintStringXY("Mass: ", 50, 35);
            gfx_PrintString(el->mass);
            
            gfx_PrintStringXY("Atomic #: ", 50, 25);
            gfx_PrintUInt(currAtom,1+(currAtom>9)+(currAtom>99));
            
            gfx_PrintStringXY("Protons: ", 50, 55);
            gfx_PrintUInt(currAtom,1+(currAtom>9)+(currAtom>99));
            
            gfx_PrintStringXY("State: ", 50, 45);
            isAGas = false;
            if (el->group == 7 || memchr(nonNobleGases, currAtom, 5)){
                gfx_PrintString("Gas");
                isAGas = true;
            } else {
                if (currAtom == 35 || currAtom == 80)
                {
                    gfx_PrintString("Liquid");
                } else {
                    if (currAtom > 103){
                        gfx_PrintString("Unknown");
                    } else {
                        gfx_PrintString("Solid");
                    }
                }
            }
            
            gfx_PrintStringXY("Neutrons: ", 50, 65);
            gfx_PrintUInt(el->neutrons, 1+(el->neutrons>9)+(el->neutrons>99));
            
            gfx_PrintStringXY("Density: ", 50, 75);
            gfx_PrintString(el->density);
            if (isAGas){
                gfx_PrintString(" g/l");
            } else {
                gfx_PrintString(" g/cm3");
            }
            
            gfx_PrintStringXY("Electronegativity: ", 50, 85);
            gfx_PrintString(el->electronegativity);
            
            gfx_PrintStringXY("Group: ", 50, 95);
            gfx_PrintString(groups[el->group]);
            
            gfx_PrintStringXY("Melt: ", 50, 105);
            gfx_PrintString(el->boil);
            gfx_PrintString(" K.");
            
            gfx_PrintStringXY("Boil: ", 50, 115);
            gfx_PrintString(el->melt);
            gfx_PrintString(" K.");
            
            gfx_PrintStringXY("Year Discovered: ", 50, 125);
            if (el->year){
                gfx_PrintUInt(el->year, 4);
            } else {
                gfx_PrintString("ANCIENT");
            }
            
            gfx_PrintStringXY("Radius: ", 50, 135);
            gfx_PrintUInt(el->radius, 2+(el->radius > 99));
            gfx_PrintString(" pm");
            
            gfx_PrintStringXY("1st Ion: ", 50, 145);
            gfx_PrintUInt(el->firstIon, 3+(el->firstIon > 999));
            gfx_PrintString(" kJ/mol");
            
            screen = DETAILS_SCREEN;
        }
        
        prevArrowKey = key;
        prevEnterKey = enterKey;
            
    } while (kb_Data[1] != kb_Graph && kb_Data[6] != kb_Clear);
    
    gfx_End();
    return 0;
}
