#include <stdlib.h>
#include <graphx.h>
#include <keypadc.h>
#include <string.h>

#define DETAILS_SCREEN 0x0
#define TABLE_SCREEN 0x1

int GetElementType(int atomicNumber) {
    uint8_t nonMetals[7] = {1,6,7,8,15,16,34};
    if (memchr(nonMetals,atomicNumber,7)) {
        return 0;
    }
    uint8_t nobleGases[6] = {2,10,18,36,54,86};
    if (memchr(nobleGases,atomicNumber,6)) {
        return 7;
    }
    uint8_t alkaliMetals[6] = {3,11,19,37,55,87};
    if (memchr(alkaliMetals,atomicNumber,6)) {
        return 1;
    }
    uint8_t alkalineMetals[6] = {4,12,20,38,56,88};
    if (memchr(alkalineMetals,atomicNumber,6)) {
        return 2;
    }
    uint8_t halogens[5] = {9,17,35,53,85};
    if (memchr(halogens,atomicNumber,5)) {
        return 6;
    }
    uint8_t metaloids[7] = {5,14,32,33,51,52,84};
    if (memchr(metaloids,atomicNumber,7)) {
        return 5;
    }
    uint8_t other[7] = {13,31,49,50,81,82,83};
    if (memchr(other,atomicNumber,7)) {
        return 4;
    }
    if (atomicNumber>56 && atomicNumber<72){
        return 9;
    }
    if (atomicNumber>88 && atomicNumber<104){
        return 10;
    }
    if (atomicNumber>112){
        return 8;
    }
    return 3;
}

typedef struct
{
    char name[14];
    char symbol[3];
    char mass[7];
    char density[6];
    char electronegativity[5];
    char melt[7];
    char boil[7];
    int year;
    int radius;
    int firstIon;
}Element;

int main(void)
{

    static const Element elements[118] = {
        {"Hydrogen     ", "H ", "1.0079", "0.09 ", "2.20", "13.99 ", "20.271", 1766, 32, 1312},
        {"Helium       ", "He", "4.0026", "0.179", "N/A ", "0.95  ", "4.222 ", 1868, 37, 2372},
        {"Lithium      ", "Li", "6.941 ", "0.535", "0.98", "453.65", "1603  ", 1817, 130, 520},
        {"Beryllium    ", "Be", "9.0122", "1.848", "1.57", "1560  ", "3243  ", 1828, 99, 899},
        {"Boron        ", "B ", "10.81 ", "2.46 ", "2.04", "2349  ", "4200  ", 1808, 84, 801},
        {"Carbon       ", "C ", "12.011", "2.26 ", "2.55", "N/A   ", "3915  ", 0, 75, 1086},
        {"Nitrogen     ", "N ", "14.007", "1.251", "3.04", "63.15 ", "77.355", 1772, 71, 1402},
        {"Oxygen       ", "O ", "15.999", "1.429", "3.44", "54.36 ", "90.188", 1774, 64, 1314},
        {"Fluorine     ", "F ", "18.998", "1.696", "3.98", "53.48 ", "85.03 ", 1886, 60, 1681},
        {"Neon         ", "Ne", "20.18 ", "0.9  ", "N/A ", "24.56 ", "27.104", 1898, 62, 2081},
        {"Sodium       ", "Na", "22.99 ", "0.968", "0.93", "370.94", "1156.1", 1807, 160, 496},
        {"Magnesium    ", "Mg", "24.305", "1.738", "1.31", "923   ", "1363  ", 1755, 140, 738},
        {"Aluminium    ", "Al", "26.982", "2.7  ", "1.61", "933.47", "2743  ", 1827, 124, 578},
        {"Silicon      ", "Si", "28.086", "2.33 ", "1.9 ", "1687  ", "3538  ", 1824, 114, 786},
        {"Phosphorus   ", "P ", "30.974", "1.823", "2.19", "N/A   ", "N/A   ", 1669, 109, 1012},
        {"Sulfur       ", "S ", "32.066", "1.96 ", "2.58", "388.36", "717.8 ", 0, 104, 1000},
        {"Chlorine     ", "Cl", "35.453", "3.214", "3.16", "171.6 ", "239.11", 1774, 100, 1251},
        {"Argon        ", "Ar", "39.948", "1.784", "N/A ", "83.81 ", "87.302", 1894, 101, 1521},
        {"Potassium    ", "K ", "39.098", "0.856", "0.82", "336.7 ", "1032  ", 1807, 200, 419},
        {"Calcium      ", "Ca", "40.078", "1.55 ", "1.00", "1115  ", "1757  ", 1808, 174, 590},
        {"Scandium     ", "Sc", "44.956", "2.985", "1.36", "1814  ", "3109  ", 1878, 159, 631},
        {"Titanium     ", "Ti", "47.867", "4.507", "1.54", "1941  ", "3560  ", 1791, 148, 658},
        {"Vanadium     ", "V ", "50.942", "6.11 ", "1.63", "2183  ", "3680  ", 1801, 144, 650},
        {"Chromium     ", "Cr", "51.996", "7.14 ", "1.66", "2180  ", "2944  ", 1797, 130, 653},
        {"Manganese    ", "Mn", "54.938", "7.47 ", "1.55", "1519  ", "2334  ", 1774, 129, 717},
        {"Iron         ", "Fe", "55.845", "7.874", "1.83", "1811  ", "3134  ", 0, 124, 759},
        {"Cobalt       ", "Co", "58.933", "8.9  ", "1.88", "1768  ", "3200  ", 1735, 118, 758},
        {"Nickel       ", "Ni", "58.693", "8.908", "1.91", "1728  ", "3003  ", 1751, 117, 737},
        {"Copper       ", "Cu", "36.546", "8.92 ", "1.9 ", "1357.8", "2835  ", 0, 122, 745},
        {"Zinc         ", "Zn", "65.39 ", "7.14 ", "1.65", "692.68", "1180  ", 1746, 120, 906},
        {"Gallium      ", "Ga", "69.723", "5.904", "1.81", "302.91", "2673  ", 1875, 123, 579},
        {"Germanium    ", "Ge", "72.61 ", "5.323", "2.01", "1211.4", "3106  ", 1886, 120, 762},
        {"Arsenic      ", "As", "74.922", "5.727", "2.18", "N/A   ", "887   ", 1250, 120, 947},
        {"Selenium     ", "Se", "78.96 ", "4.819", "2.55", "494   ", "958   ", 1817, 118, 941},
        {"Bromine      ", "Br", "79.904", "3.12 ", "2.96", "265.8 ", "332.0 ", 1826, 117, 1140},
        {"Krypton      ", "Kr", "83.8  ", "3.75 ", "3.00", "115.78", "119.93", 1898, 116, 1351},
        {"Rubidium     ", "Rb", "85.468", "1.532", "0.82", "312.45", "961   ", 1861, 215, 403},
        {"Strontium    ", "Sr", "87.62 ", "2.63 ", "0.95", "1050  ", "1650  ", 1790, 190, 549},
        {"Yttrium      ", "Y ", "88.906", "4.472", "1.22", "1799  ", "3203  ", 1794, 176, 616},
        {"Zirconium    ", "Zr", "91.224", "6.511", "1.33", "2128  ", "4650  ", 1789, 164, 660},
        {"Niobium      ", "Nb", "92.906", "8.57 ", "1.6 ", "2750  ", "5017  ", 1801, 156, 664},
        {"Molybdenum   ", "Mo", "95.94 ", "10.28", "2.16", "2896  ", "4912  ", 1778, 146, 685},
        {"Technetium   ", "Tc", "[98]  ", "11.5 ", "1.9 ", "2430  ", "4538  ", 1937, 138, 702},
        {"Ruthenium    ", "Ru", "101.07", "12.37", "2.2 ", "2607  ", "4423  ", 1844, 136, 711},
        {"Rhodium      ", "Rh", "102.91", "12.45", "2.28", "2237  ", "3968  ", 1803, 134, 720},
        {"Palladium    ", "Pd", "106.42", "12.02", "2.2 ", "1828.1", "3236  ", 1803, 130, 805},
        {"Silver       ", "Ag", "107.87", "10.49", "1.93", "1234.9", "2435  ", 0, 136, 731},
        {"Cadmium      ", "Cd", "112.41", "8.65 ", "1.69", "594.22", "1040  ", 1817, 140, 868},
        {"Indium       ", "In", "114.82", "7.31 ", "1.78", "429.75", "2345  ", 1863, 142, 558},
        {"Tin          ", "Sn", "118.71", "7.31 ", "1.96", "505.08", "2875  ", 0, 140, 709},
        {"Antimony     ", "Sb", "121.76", "6.697", "2.05", "903.78", "1908  ", 0, 140, 834},
        {"Tellurium    ", "Te", "127.6 ", "6.24 ", "2.1 ", "722.66", "1261  ", 1782, 137, 869},
        {"Iodine       ", "I ", "126.91", "4.94 ", "2.66", "386.85", "457.4 ", 1811, 136, 1008},
        {"Xenon        ", "Xe", "131.29", "5.9  ", "2.6 ", "161.40", "165.05", 1898, 136, 1170},
        {"Cesium       ", "Cs", "132.91", "1.879", "0.79", "301.7 ", "944   ", 1860, 238, 376},
        {"Barium       ", "Ba", "137.33", "3.51 ", "0.89", "1000  ", "2118  ", 1808, 206, 503},
        {"Lanthanum    ", "La", "138.91", "6.146", "1.1 ", "1193  ", "3737  ", 1839, 194, 538},
        {"Cerium       ", "Ce", "140.12", "6.689", "1.12", "1068  ", "3716  ", 1803, 184, 528},
        {"Praseodymium ", "Pr", "140.91", "6.64 ", "1.13", "1208  ", "3403  ", 1841, 190, 523},
        {"Neodymium    ", "Nd", "144.24", "7.01 ", "1.14", "1297  ", "3347  ", 1885, 188, 530},
        {"Promethium   ", "Pm", "[145] ", "7.264", "N/A ", "1315  ", "3273  ", 1914, 186, 535},
        {"Samarium     ", "Sm", "150.36", "7.353", "1.17", "1345  ", "2173  ", 1879, 185, 543},
        {"Europium     ", "Eu", "151.97", "5.244", "N/A ", "1099  ", "1802  ", 1901, 183, 547},
        {"Gadolinium   ", "Gd", "157.25", "7.901", "1.2 ", "1585  ", "3273  ", 1880, 182, 592},
        {"Terbium      ", "Tb", "158.93", "8.219", "N/A ", "1629  ", "3396  ", 1843, 181, 564},
        {"Dysprosium   ", "Dy", "162.5 ", "8.551", "1.22", "1680  ", "2840  ", 1886, 180, 572},
        {"Holmium      ", "Ho", "164.93", "8.795", "1.23", "1734  ", "2873  ", 1878, 179, 581},
        {"Erbium       ", "Er", "167.26", "9.066", "1.24", "1802  ", "3141  ", 1842, 177, 589},
        {"Thulium      ", "Tm", "168.93", "9.321", "1.25", "1818  ", "2003  ", 1879, 177, 596},
        {"Ytterbium    ", "Yb", "173.04", "6.57 ", "N/A ", "1097  ", "1469  ", 1878, 178, 603},
        {"Lutetium     ", "Lu", "174.97", "9.841", "1.27", "1925  ", "3675  ", 1907, 174, 524},
        {"Hafnium      ", "Hf", "178.49", "13.31", "1.3 ", "2506  ", "4876  ", 1923, 164, 680},
        {"Tantalum     ", "Ta", "180.95", "16.65", "1.5 ", "3290  ", "5731  ", 1802, 158, 761},
        {"Tungsten     ", "W ", "183.84", "19.25", "2.36", "3695  ", "6203  ", 1783, 150, 770},
        {"Rhenium      ", "Re", "186.21", "21.02", "1.9 ", "3459  ", "5869  ", 1925, 141, 760},
        {"Osmium       ", "Os", "190.23", "22.61", "2.2 ", "3306  ", "5285  ", 1803, 136, 840},
        {"Iridium      ", "Ir", "192.22", "22.65", "2.2 ", "2719  ", "4403  ", 1803, 132, 880},
        {"Platinium    ", "Pt", "195.08", "21.09", "2.28", "2041.4", "4098  ", 1735, 130, 870},
        {"Gold         ", "Au", "196.97", "19.3 ", "2.54", "1337.3", "3243  ", 0, 130, 890},
        {"Mercury      ", "Hg", "200.59", "13.53", "2.00", "234.32", "629.88", 0, 132, 1007},
        {"Thallium     ", "Tl", "204.38", "11.85", "1.62", "577   ", "1746  ", 1861, 144, 589},
        {"Lead         ", "Pb", "207.2 ", "11.34", "2.33", "600.61", "2022  ", 0, 145, 716},
        {"Bismuth      ", "Bi", "208.98", "9.78 ", "2.02", "544.7 ", "1837  ", 0, 150, 703},
        {"Polonium     ", "Po", "[209] ", "9.196", "2.00", "527   ", "1235  ", 1898, 142, 812},
        {"Astatine     ", "At", "[210] ", "N/A  ", "2.2 ", "575   ", "610   ", 1940, 148, 899},
        {"Radon        ", "Rn", "[222] ", "9.73 ", "N/A ", "202   ", "211.5 ", 1900, 146, 1037},
        {"Francium     ", "Fr", "[223] ", "N/A  ", "0.7 ", "300   ", "950   ", 1939, 242, 380},
        {"Radium       ", "Ra", "[226] ", "5    ", "0.9 ", "1233  ", "2010  ", 1898, 211, 509},
        {"Actinium     ", "Ac", "[227] ", "10.07", "1.1 ", "1500  ", "3500  ", 1899, 201, 670},
        {"Thorium      ", "Th", "232.04", "11.72", "1.3 ", "2023  ", "5061  ", 1828, 190, 587},
        {"Protactinium ", "Pa", "231.04", "15.37", "1.5 ", "1841  ", "4300  ", 1913, 184, 568},
        {"Uranium      ", "U ", "238.03", "19.05", "1.38", "1405.3", "4404  ", 1841, 183, 598},
        {"Neptunium    ", "Np", "[237] ", "20.45", "1.36", "912   ", "4447  ", 1940, 180, 605},
        {"Plutonium    ", "Pu", "[244] ", "19.82", "1.28", "912.5 ", "3505  ", 1940, 180, 585},
        {"Americium    ", "Am", "[243] ", "N/A  ", "1.3 ", "1449  ", "2880  ", 1944, 173, 578},
        {"Curium       ", "Cm", "[247] ", "13.51", "1.3 ", "1613  ", "3383  ", 1944, 168, 581},
        {"Berkelium    ", "Bk", "[247] ", "14.78", "1.3 ", "1259  ", "2900  ", 1949, 168, 601},
        {"Californium  ", "Cf", "[251] ", "15.1 ", "1.3 ", "1173  ", "1743  ", 1950, 168, 608},
        {"Einsteinium  ", "Es", "[252] ", "8.84 ", "1.3 ", "1133  ", "1269  ", 1952, 165, 619},
        {"Fermium      ", "Fm", "[257] ", "N/A  ", "1.3 ", "1800  ", "N/A   ", 1952, 167, 627},
        {"Mendelevium  ", "Md", "[258] ", "N/A  ", "1.3 ", "1100  ", "N/A   ", 1955, 173, 635},
        {"Nobelium     ", "No", "[259] ", "N/A  ", "1.3 ", "1100  ", "N/A   ", 1958, 176, 642},
        {"Lawrencium   ", "Lr", "262.11", "N/A  ", "1.3 ", "1900  ", "N/A   ", 1961, 161, 470},
        {"Rutherfordium", "Rf", "265.12", "23.2 ", "N/A ", "2400  ", "5800  ", 1964, 157, 580},
        {"Dubnium      ", "Db", "268.13", "29.3 ", "N/A ", "N/A   ", "N/A   ", 1967, 149, 665},
        {"Seaborgium   ", "Sg", "271.13", "35   ", "N/A ", "N/A   ", "N/A   ", 1974, 143, 757},
        {"Bohrium      ", "Bh", "[270] ", "37.1 ", "N/A ", "N/A   ", "N/A   ", 1981, 141, 740},
        {"Hassium      ", "Hs", "277.15", "40.7 ", "N/A ", "N/A   ", "N/A   ", 1964, 134, 730},
        {"Meitnerium   ", "Mt", "276.15", "37.4 ", "N/A ", "N/A   ", "N/A   ", 1982, 129, 800},
        {"Darmstadtium ", "Ds", "281.16", "34.8 ", "N/A ", "N/A   ", "N/A   ", 1987, 128, 960},
        {"Roentgenium  ", "Rg", "280.16", "28.7 ", "N/A ", "N/A   ", "N/A   ", 1994, 121, 1020},
        {"Copernicium  ", "Cn", "285.17", "23.7 ", "N/A ", "N/A   ", "357   ", 1996, 122, 1155},
        {"Nihonium     ", "Nh", "284.18", "16   ", "N/A ", "700   ", "1430  ", 2004, 136, 707},
        {"Flerovium    ", "Fl", "289.19", "14   ", "N/A ", "340   ", "420   ", 1998, 143, 832},
        {"Moscovium    ", "Mc", "288.19", "13.5 ", "N/A ", "670   ", "1400  ", 2004, 162, 538},
        {"Livermorium  ", "Lv", "[293] ", "12.9 ", "N/A ", "708.5 ", "1085  ", 2000, 175, 664},
        {"Tennessine   ", "Ts", "[294] ", "7.2  ", "N/A ", "673   ", "823   ", 2009, 165, 737},
        {"Oganesson    ", "Og", "[294] ", "5    ", "N/A ", "N/A   ", "350   ", 2002, 157, 860}
    };
    
    static const uint8_t colors[11] = {7,228,230,234,241,29,23,157,149,47,217};
    int tempAtom;
    int tempPosX;
    int tempPosY;
    kb_key_t key;
    kb_key_t enterKey;
    
    static const char *groups[11] = {"non-metal", "alkali metal", "alkaline metal", "transition metal", "other metal", "metaloid", "halogen", "noble gas", "unknown", "lanthanoid", "actinoid"};
    
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
    int i = 1;
    int j = 0;
    int first = true;
    int currAtom;
    bool prevArrowKey = false;
    bool prevEnterKey = false;
    bool redrawTable = true;
    bool screen;
    Element currElement;
    
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
                for(int j=0;j<18;j++) {
                    tempAtom = mainArr[i][j];
                    if (tempAtom){
                        gfx_SetColor(colors[GetElementType(tempAtom)]);
                        tempPosX = 8+17*j;
                        tempPosY = 32+17*i;
                        gfx_FillRectangle_NoClip(tempPosX, tempPosY, 16, 16);
                        tempPosX += (4*(elements[tempAtom-1].symbol[1]==' '));
                        gfx_PrintStringXY(elements[tempAtom-1].symbol,tempPosX, tempPosY+4);
                    }
                }
            }
            gfx_SetColor(255);
            gfx_Line_NoClip(50,175,55,175);
            gfx_Line_NoClip(50,191,55,191);
            gfx_Line_NoClip(50,122,50,191);
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
            } while (!mainArr[i][j]);
            currAtom = mainArr[i][j];
            currElement = elements[currAtom-1];
            gfx_SetColor(255);
            gfx_Rectangle_NoClip(7+17*j,31+17*i,18,18);

            gfx_SetTextScale(2,2);
            gfx_PrintStringXY(currElement.name, 90, 215);
            
            gfx_SetColor(colors[GetElementType(currAtom)]);
            gfx_FillRectangle_NoClip(40, 205, 32, 32);
            gfx_PrintStringXY(currElement.symbol,41+(8*(currElement.symbol[1]==' ')), 214);
        }
        if (enterKey && !prevEnterKey){
            redrawTable = !screen;
            gfx_FillRectangle_NoClip(0,25,320,180);
            gfx_SetTextScale(1,1);

            gfx_PrintStringXY("Mass: ", 50, 35);
            gfx_PrintString(currElement.mass);

            gfx_PrintStringXY("Density: ", 50, 45);
            gfx_PrintString(currElement.density);
            gfx_PrintString(" g/l");
            
            gfx_PrintStringXY("Electronegativity: ", 50, 55);
            gfx_PrintString(currElement.electronegativity);
            
            gfx_PrintStringXY("Group: ", 50, 65);
            gfx_PrintString(groups[GetElementType(currAtom)]);
            
            gfx_PrintStringXY("Atomic #: ", 50, 25);
            gfx_PrintInt(currAtom,1+(currAtom>9)+(currAtom>99));
            
            gfx_PrintStringXY("Melt: ", 50, 75);
            gfx_PrintString(currElement.boil);
            
            gfx_PrintStringXY("Boil: ", 50, 85);
            gfx_PrintString(currElement.melt);
            
            gfx_PrintStringXY("Year Discovered: ", 50, 95);
            if (currElement.year){
                gfx_PrintInt(currElement.year,4);
            } else {
                gfx_PrintString("ANCIENT");
            }
            
            gfx_PrintStringXY("Radius: ", 50, 105);
            gfx_PrintInt(currElement.radius, 2+(currElement.radius > 99));
            
            gfx_PrintStringXY("1st Ion: ", 50, 115);
            gfx_PrintInt(currElement.firstIon, 3+(currElement.firstIon > 999));
            
            screen = DETAILS_SCREEN;
        }
        prevArrowKey = key;
        prevEnterKey = enterKey;
            
    } while (kb_Data[1] != kb_Graph && kb_Data[6] != kb_Clear);
    
    gfx_End();
    return 0;
}
