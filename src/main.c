#include <stdlib.h>
#include <graphx.h>
#include <keypadc.h>
#include <string.h>
#include <tice.h>

#define DETAILS_SCREEN 0x0
#define TABLE_SCREEN 0x1
#define FR_LOCAL 0x10C
#define DE_LOCAL 0x113
#define ES_LOCAL 0x10A

typedef struct
{
    char symbol[3];
    char mass[9];
    char density[6];
    char electronegativity[5];
    char melt[7];
    char boil[7];
    char eleConf[23];
    char oxState[13];
    uint16_t year;
    uint8_t radius;
    uint16_t firstIon;
    uint8_t group;
    uint8_t neutrons;
}Element;

int main(void)
{

    static const Element elements[118] = {
        {"H ", "1.00784",  "0.09 ", "2.20", "13.99 ", "20.271", "1S",                     "1",            1766, 32, 1312, 2, 0},
        {"He", "4.002602", "0.179", "N/A ", "0.95  ", "4.222 ", "1S2",                    "N/A",          1868, 37, 2372, 7, 2},
        {"Li", "6.938",    "0.535", "0.98", "453.65", "1603  ", "1s2 2s",                 "1",            1817, 130, 520, 0, 4},
        {"Be", "9.012182", "1.848", "1.57", "1560  ", "3243  ", "1s2 2s2",                "2" ,            1828, 99, 899, 1, 5},
        {"B ", "10.806",   "2.46 ", "2.04", "2349  ", "4200  ", "1s2 2s2 2p",             "3",            1808, 84, 801, 4, 6},
        {"C ", "12.0096",  "2.26 ", "2.55", "N/A   ", "3915  ", "1s2 2s2 2p2",            "-4,4 (2)",     0, 75, 1086, 2, 6},
        {"N ", "14.00643", "1.251", "3.04", "63.15 ", "77.355", "1s2 2s2 2p3",            "-3,3 (5,4,2)", 1772, 71, 1402, 2, 7},
        {"O ", "15.99903", "1.429", "3.44", "54.36 ", "90.188", "1s2 2s2 2p4",            "-2",           1774, 64, 1314, 2, 8},
        {"F ", "18.99840", "1.696", "3.98", "53.48 ", "85.03 ", "1s2 2s2 2p5",            "-1",           1886, 60, 1681, 6, 10},
        {"Ne", "20.1797",  "0.9  ", "N/A ", "24.56 ", "27.104", "1s2 2s2 2p6",            "N/A",          1898, 62, 2081, 7, 10},
        {"Na", "22.98977", "0.968", "0.93", "370.94", "1156.1", "[Ne] 3s",                "1",            1807, 160, 496, 0, 12},
        {"Mg", "24.3050",  "1.738", "1.31", "923   ", "1363  ", "[Ne] 3s2",               "2",            1755, 140, 738, 1, 12},
        {"Al", "26.98154", "2.7  ", "1.61", "933.47", "2743  ", "[Ne] 3s2 3P",            "3",            1827, 124, 578, 5, 14},
        {"Si", "28.084",   "2.33 ", "1.9 ", "1687  ", "3538  ", "[Ne] 3s2 3p2",           "4 (2)",        1824, 114, 786, 4, 14},
        {"P ", "30.97376", "1.823", "2.19", "N/A   ", "N/A   ", "[Ne] 3s2 3p3",           "-3,3 (5,4)",   1669, 109, 1012, 2, 16},
        {"S ", "32.059",   "1.96 ", "2.58", "388.36", "717.8 ", "[Ne] 3s2 3p4",           "6 (-2,2,4)",   0, 104, 1000, 2, 16},
        {"Cl", "35.446",   "3.214", "3.16", "171.6 ", "239.11", "[Ne] 3s2 3p5",           "-1,1 (3,5,7)", 1774, 100, 1251, 6, 18},
        {"Ar", "39.948",   "1.784", "N/A ", "83.81 ", "87.302", "[Ne] 3s2 3p6",           "N/A",          1894, 101, 1521, 7, 22},
        {"K ", "39.0983",  "0.856", "0.82", "336.7 ", "1032  ", "[Ar] 4s",                "1",            1807, 200, 419, 0, 20},
        {"Ca", "40.078",   "1.55 ", "1.00", "1115  ", "1757  ", "[Ar] 4s2",               "2",            1808, 174, 590, 1, 20},
        {"Sc", "44.95591", "2.985", "1.36", "1814  ", "3109  ", "[Ar] 3d 4s2",            "3",            1878, 159, 631, 3, 24},
        {"Ti", "47.867",   "4.507", "1.54", "1941  ", "3560  ", "[Ar] 3d2 4s2",           "4 (3)",        1791, 148, 658, 3, 26},
        {"V ", "50.9415",  "6.11 ", "1.63", "2183  ", "3680  ", "[Ar] 3d3 4s2",           "5 (4,3,2)",    1801, 144, 650, 3, 28},
        {"Cr", "51.9961",  "7.14 ", "1.66", "2180  ", "2944  ", "[Ar] 3d5 4s",            "3 (6,2)",      1797, 130, 653, 3, 28},
        {"Mn", "54.93805", "7.47 ", "1.55", "1519  ", "2334  ", "[Ar] 3d5 4s2",           "2 (7,6,4,3)",  1774, 129, 717, 3, 30},
        {"Fe", "55.845",   "7.874", "1.83", "1811  ", "3134  ", "[Ar] 3d6 4s2",           "3 (2)",        0, 124, 759, 3, 30},
        {"Co", "58.93319", "8.9  ", "1.88", "1768  ", "3200  ", "[Ar] 3d7 4s2",           "2 (3)",        1735, 118, 758, 3, 32},
        {"Ni", "58.6934",  "8.908", "1.91", "1728  ", "3003  ", "[Ar] 3d8 4s2",           "2 (3)",        1751, 117, 737, 3, 31},
        {"Cu", "36.546",   "8.92 ", "1.9 ", "1357.8", "2835  ", "[Ar] 3d10 4s",           "2 (1)",        0, 122, 745, 3, 35},
        {"Zn", "65.38",    "7.14 ", "1.65", "692.68", "1180  ", "[Ar] 3d10 4s2",          "2",            1746, 120, 906, 3, 35},
        {"Ga", "69.723",   "5.904", "1.81", "302.91", "2673  ", "[Ar] 3d10 4s2 4p",       "3",            1875, 123, 579, 5, 39},
        {"Ge", "72.63",    "5.323", "2.01", "1211.4", "3106  ", "[Ar] 3d10 4s2 4p2",      "4",            1886, 120, 762, 4, 41},
        {"As", "74.92160", "5.727", "2.18", "N/A   ", "887   ", "[Ar] 3d10 4s2 4p3",      "-3,3 (5)",     1250, 120, 947, 4, 42},
        {"Se", "78.97",    "4.819", "2.55", "494   ", "958   ", "[Ar] 3d10 4s2 4p4",      "4 (-2,2,6)",   1817, 118, 941, 2, 45},
        {"Br", "79.904",   "3.12 ", "2.96", "265.8 ", "332.0 ", "[Ar] 3d10 4s2 4p5",      "-1,1 (5,7)",   1826, 117, 1140, 6, 45},
        {"Kr", "83.798",   "3.75 ", "3.00", "115.78", "119.93", "[Ar] 3d10 4s2 4p6",      "0 (2)",        1898, 116, 1351, 7, 48},
        {"Rb", "85.4678",  "1.532", "0.82", "312.45", "961   ", "[Kr] 5s",                "1",            1861, 215, 403, 0, 48},
        {"Sr", "87.62",    "2.63 ", "0.95", "1050  ", "1650  ", "[Kr] 5s2",               "2",            1790, 190, 549, 1, 50},
        {"Y ", "88.90585", "4.472", "1.22", "1799  ", "3203  ", "[Kr] 4d 5s2",            "3",            1794, 176, 616, 3, 50},
        {"Zr", "91.224",   "6.511", "1.33", "2128  ", "4650  ", "[Kr] 4d2 5s2",           "4",            1789, 164, 660, 3, 51},
        {"Nb", "92.90638", "8.57 ", "1.6 ", "2750  ", "5017  ", "[Kr] 4d4 5s",            "5 (3)",        1801, 156, 664, 3, 52},
        {"Mo", "95.95",    "10.28", "2.16", "2896  ", "4912  ", "[Kr] 4d5 5s",            "6 (5,4,3,2)",  1778, 146, 685, 3, 54},
        {"Tc", "96.90636", "11.5 ", "1.9 ", "2430  ", "4538  ", "[Kr] 4d5 5s2",           "7",            1937, 138, 702, 3, 55},
        {"Ru", "101.07",   "12.37", "2.2 ", "2607  ", "4423  ", "[Kr] 4d7 5s",            "3,4 (2,6,8)",  1844, 136, 711, 3, 57},
        {"Rh", "102.9055", "12.45", "2.28", "2237  ", "3968  ", "[Kr] 4d8 5s",            "3 (2,4)",      1803, 134, 720, 3, 58},
        {"Pd", "106.42",   "12.02", "2.2 ", "1828.1", "3236  ", "[Kr] 4d10",              "2 (4)",        1803, 130, 805, 3, 60},
        {"Ag", "107.8682", "10.49", "1.93", "1234.9", "2435  ", "[Kr] 4d10 5s",           "1",            0, 136, 731, 3, 61},
        {"Cd", "112.411",  "8.65 ", "1.69", "594.22", "1040  ", "[Kr] 4d10 5s2",          "2",            1817, 140, 868, 3, 64},
        {"In", "114.818",  "7.31 ", "1.78", "429.75", "2345  ", "[Kr] 4d10 5s2 5p",       "3",            1863, 142, 558, 5, 66},
        {"Sn", "118.710",  "7.31 ", "1.96", "505.08", "2875  ", "[Kr] 4d10 5s2 5p2",      "4 (2)",        0, 140, 709, 5, 69},
        {"Sb", "121.760",  "6.697", "2.05", "903.78", "1908  ", "[Kr] 4d10 5s2 5p3",      "-3,3 (5)",     0, 140, 834, 4, 71},
        {"Te", "127.60",   "6.24 ", "2.1 ", "722.66", "1261  ", "[Kr] 4d10 5s2 5p4",      "4 (-2,2,6)",   1782, 137, 869, 4, 76},
        {"I ", "126.9045", "4.94 ", "2.66", "386.85", "457.4 ", "[Kr] 4d10 5s2 5p5",      "-1,1 (5,7)",   1811, 136, 1008, 6, 74},
        {"Xe", "131.293",  "5.9  ", "2.6 ", "161.40", "165.05", "[Kr] 4d10 5s2 5p6",      "0 (2,4,6)",    1898, 136, 1170, 7, 77},
        {"Cs", "132.9055", "1.879", "0.79", "301.7 ", "944   ", "[Xe] 6s",                "1",            1860, 238, 376, 0, 78},
        {"Ba", "137.327",  "3.51 ", "0.89", "1000  ", "2118  ", "[Xe] 6s2",               "2",            1808, 206, 503, 1, 81},
        {"La", "138.9055", "6.146", "1.1 ", "1193  ", "3737  ", "[Xe] 5d 6s2",            "3",            1839, 194, 538, 8, 82},
        {"Ce", "140.116",  "6.689", "1.12", "1068  ", "3716  ", "[Xe] 4f 5d 6s2",         "3 (4)",        1803, 184, 528, 8, 82},
        {"Pr", "140.9077", "6.64 ", "1.13", "1208  ", "3403  ", "[Xe] 4f3 6s2",           "3 (4)",        1841, 190, 523, 8, 82},
        {"Nd", "144.242",  "7.01 ", "1.14", "1297  ", "3347  ", "[Xe] 4f4 6s2",           "3",            1885, 188, 530, 8, 84},
        {"Pm", "144.9128", "7.264", "N/A ", "1315  ", "3273  ", "[Xe] 4f5 6s2",           "3",            1914, 186, 535, 8, 84},
        {"Sm", "150.4",    "7.353", "1.17", "1345  ", "2173  ", "[Xe] 4f6 6s2",           "3 (2)",        1879, 185, 543, 8, 88},
        {"Eu", "151.964",  "5.244", "N/A ", "1099  ", "1802  ", "[Xe] 4f7 6s2",           "3 (2)",        1901, 183, 547, 8, 89},
        {"Gd", "157.2",    "7.901", "1.2 ", "1585  ", "3273  ", "[Xe] 4f7 5d 6s2",        "3",            1880, 182, 592, 8, 93},
        {"Tb", "158.9254", "8.219", "N/A ", "1629  ", "3396  ", "[Xe] 4f9 6s2",           "3 (4)",        1843, 181, 564, 8, 94},
        {"Dy", "162.500",  "8.551", "1.22", "1680  ", "2840  ", "[Xe] 4f10 6s2",          "3",            1886, 180, 572, 8, 97},
        {"Ho", "164.9303", "8.795", "1.23", "1734  ", "2873  ", "[Xe] 4f11 6s2",          "3",            1878, 179, 581, 8, 98},
        {"Er", "167.259",  "9.066", "1.24", "1802  ", "3141  ", "[Xe] 4f12 6s2",          "3",            1842, 177, 589, 8, 99},
        {"Tm", "168.9342", "9.321", "1.25", "1818  ", "2003  ", "[Xe] 4f13 6s2",          "3 (2)",        1879, 177, 596, 8, 100},
        {"Yb", "173.054",  "6.57 ", "N/A ", "1097  ", "1469  ", "[Xe] 4f14 6s2",          "3 (2)",        1878, 178, 603, 8, 103},
        {"Lu", "174.9668", "9.841", "1.27", "1925  ", "3675  ", "[Xe] 4f14 5d 6s2",       "3",            1907, 174, 524, 8, 104},
        {"Hf", "178.49",   "13.31", "1.3 ", "2506  ", "4876  ", "[Xe] 4f14 5d2 6s2",      "4",            1923, 164, 680, 3, 106},
        {"Ta", "180.9479", "16.65", "1.5 ", "3290  ", "5731  ", "[Xe] 4f14 5d3 6s2",      "5",            1802, 158, 761, 3, 108},
        {"W ", "183.84",   "19.25", "2.36", "3695  ", "6203  ", "[Xe] 4f14 5d4 6s2",      "6 (5,4,3,2)",  1783, 150, 770, 3, 110},
        {"Re", "186.207",  "21.02", "1.9 ", "3459  ", "5869  ", "[Xe] 4f14 5d5 6s2",      "7 (6,4,2)",    1925, 141, 760, 3, 111},
        {"Os", "190.23",   "22.61", "2.2 ", "3306  ", "5285  ", "[Xe] 4f14 5d6 6s2",      "4 (2,3,6,8)",  1803, 136, 840, 3, 114},
        {"Ir", "192.217",  "22.65", "2.2 ", "2719  ", "4403  ", "[Xe] 4f14 5d7 6s2",      "4 (2,3,6)",    1803, 132, 880, 3, 115},
        {"Pt", "195.084",  "21.09", "2.28", "2041.4", "4098  ", "[Xe] 4f14 5d9 6s",       "4 (2)",        1735, 130, 870, 3, 117},
        {"Au", "196.9666", "19.3 ", "2.54", "1337.3", "3243  ", "[Xe] 4f14 5d10 6s",      "3 (1)",        0, 130, 890, 3, 118},
        {"Hg", "200.59",   "13.53", "2.00", "234.32", "629.88", "[Xe] 4f14 5d10 6s2",     "2 (1)",        0, 132, 1007, 3, 121},
        {"Tl", "204.382",  "11.85", "1.62", "577   ", "1746  ", "[Xe] 4f14 5d10 6s2 6p",  "1 (3)",        1861, 144, 589, 5, 123},
        {"Pb", "207.2 ",   "11.34", "2.33", "600.61", "2022  ", "[Xe] 4f14 5d10 6s2 6p2", "2 (4)",        0, 145, 716, 5, 125},
        {"Bi", "208.9804", "9.78 ", "2.02", "544.7 ", "1837  ", "[Xe] 4f14 5d10 6s2 6p3", "3 (5)",        0, 150, 703, 5, 126},
        {"Po", "208.9824", "9.196", "2.00", "527   ", "1235  ", "[Xe] 4f14 5d10 6s2 6p4", "4 (2,6)",      1898, 142, 812, 4, 125},
        {"At", "209.9872", "N/A  ", "2.2 ", "575   ", "610   ", "[Xe] 4f14 5d10 6s2 6p5", "-1,1 (3,5,7)", 1940, 148, 899, 6, 125},
        {"Rn", "222.0176", "9.73 ", "N/A ", "202   ", "211.5 ", "[Xe] 4f14 5d10 6s2 6p6", "0 (2)",        1900, 146, 1037, 7, 136},
        {"Fr", "223.0197", "N/A  ", "0.7 ", "300   ", "950   ", "[Rn] 7s",                "1",            1939, 242, 380, 0, 136},
        {"Ra", "226.0254", "5    ", "0.9 ", "1233  ", "2010  ", "[Rn] 7s2",               "2",            1898, 211, 509, 1, 138},
        {"Ac", "227.0278", "10.07", "1.1 ", "1500  ", "3500  ", "[Rn] 6d 7s2",            "3",            1899, 201, 670, 9, 138},
        {"Th", "232.0381", "11.72", "1.3 ", "2023  ", "5061  ", "[Rn] 6d2 7s2",           "4",            1828, 190, 587, 9, 142},
        {"Pa", "231.0358", "15.37", "1.5 ", "1841  ", "4300  ", "[Rn] 5f2 6d 7s2",        "5 (4)",        1913, 184, 568, 9, 140},
        {"U ", "238.0289", "19.05", "1.38", "1405.3", "4404  ", "[Rn] 5f3 6d 7s2",        "6 (5,4,3)",    1841, 183, 598, 9, 146},
        {"Np", "237.0482", "20.45", "1.36", "912   ", "4447  ", "[Rn] 5f4 6d 7s2",        "5 (6,4,3)",    1940, 180, 605, 9, 144},
        {"Pu", "244.0642", "19.82", "1.28", "912.5 ", "3505  ", "[Rn] 5f6 7s2",           "4 (6,5,3)",    1940, 180, 585, 9, 150},
        {"Am", "243.0614", "N/A  ", "1.3 ", "1449  ", "2880  ", "[Rn] 5f7 7s2",           "3 (6,5,4)",    1944, 173, 578, 9, 148},
        {"Cm", "247.0704", "13.51", "1.3 ", "1613  ", "3383  ", "[Rn] 5f7 6d 7s2",        "3",            1944, 168, 581, 9, 151},
        {"Bk", "247.0703", "14.78", "1.3 ", "1259  ", "2900  ", "[Rn] 5f9 7s2",           "3 (4)",        1949, 168, 601, 9, 150},
        {"Cf", "251.0796", "15.1 ", "1.3 ", "1173  ", "1743  ", "[Rn] 5f10 7s2",          "3",            1950, 168, 608, 9, 153},
        {"Es", "252.0830", "8.84 ", "1.3 ", "1133  ", "1269  ", "[Rn] 5f11 7s2",          "3",            1952, 165, 619, 9, 153},
        {"Fm", "257.0951", "N/A  ", "1.3 ", "1800  ", "N/A   ", "[Rn] 5f12 7s2",          "3",            1952, 167, 627, 9, 157},
        {"Md", "258.0984", "N/A  ", "1.3 ", "1100  ", "N/A   ", "[Rn] 5f13 7s2",          "3",            1955, 173, 635, 9, 157},
        {"No", "259.101",  "N/A  ", "1.3 ", "1100  ", "N/A   ", "[Rn] 5f14 7s2",          "2,3",          1958, 176, 642, 9, 157},
        {"Lr", "266.120",  "N/A  ", "1.3 ", "1900  ", "N/A   ", "[Rn] 5f14 7s2 7p",       "3",            1961, 161, 470, 9, 159},
        {"Rf", "267.122",  "23.2 ", "N/A ", "2400  ", "5800  ", "[Rn] 5f14 6d2 7s2",      "N/A",          1964, 157, 580, 3, 157},
        {"Db", "268.126",  "29.3 ", "N/A ", "N/A   ", "N/A   ", "[Rn] 5f14 6d3 7s2",      "N/A",          1967, 149, 665, 3, 157},
        {"Sg", "269.128",  "35   ", "N/A ", "N/A   ", "N/A   ", "[Rn] 5f14 6d4 7s2",      "N/A",          1974, 143, 757, 3, 157},
        {"Bh", "270.133",  "37.1 ", "N/A ", "N/A   ", "N/A   ", "[Rn] 5f14 6d5 7s2",      "N/A",          1981, 141, 740, 3, 157},
        {"Hs", "269.1336", "40.7 ", "N/A ", "N/A   ", "N/A   ", "[Rn] 5f14 6d6 7s2",      "N/A",          1964, 134, 730, 3, 157},
        {"Mt", "277.154",  "37.4 ", "N/A ", "N/A   ", "N/A   ", "[Rn] 5f14 6d7 7s2",      "N/A",          1982, 129, 800, 3, 159},
        {"Ds", "282.166",  "34.8 ", "N/A ", "N/A   ", "N/A   ", "[Rn] 5f14 6d8 7s2",      "N/A",          1987, 128, 960, 3, 171},
        {"Rg", "282.169",  "28.7 ", "N/A ", "N/A   ", "N/A   ", "[Rn] 5f14 6d9 7s2",      "N/A",          1994, 121, 1020, 3, 162},
        {"Cn", "286.179",  "23.7 ", "N/A ", "N/A   ", "357   ", "[Rn] 5f14 6d10 7s2",     "N/A",          1996, 122, 1155, 3, 165},
        {"Nh", "286.182",  "16   ", "N/A ", "700   ", "1430  ", "[Rn] 5f14 6d10 7s2 7p1", "N/A",          2004, 136, 707, 10, 170},
        {"Fl", "290.192",  "14   ", "N/A ", "340   ", "420   ", "[Rn] 5f14 6d10 7s2 7p2", "N/A",          1998, 143, 832, 10, 171},
        {"Mc", "290.196",  "13.5 ", "N/A ", "670   ", "1400  ", "[Rn] 5f14 6d10 7s2 7p3", "N/A",          2004, 162, 538, 10, 172},
        {"Lv", "293.205",  "12.9 ", "N/A ", "708.5 ", "1085  ", "[Rn] 5f14 6d10 7s2 7p4", "N/A",          2000, 175, 664, 10, 173},
        {"Ts", "294.211",  "7.2  ", "N/A ", "673   ", "823   ", "[Rn] 5f14 6d10 7s2 7p5", "N/A",          2009, 165, 737, 10, 177},
        {"Og", "295.216",  "5    ", "N/A ", "N/A   ", "350   ", "[Rn] 5f14 6d10 7s2 7p6", "N/A",          2002, 157, 860, 10, 175}
    };
    
    static const uint8_t colors[11] = {228,230,7,234,29,241,23,157,47,217,149};
    const system_info_t *system_info = os_GetSystemInfo();
    
    static const char *strings_en[20] = {"Periodic Table CE", "Atomic #: ", "ANCIENT", "Mass: ", "Neutrons: ", "Protons: ", "Radius: ", "1st ion: ", "Electronegativity: ", "Density: ", "Melting Pt.: ", "Boiling Pt.: ", "State: ", "Year discovered: ", "Gas", "Solid", "Liquid", "Unknown", "Group: ", "Oxidation States: "};
    static const char *strings_fr[20] = {"Tableau Periodique CE", "# Atomique: ", "ANCIEN", "Masse: ", "Neutrons: ", "Protons: ", "Rayon: ", "1ere Ionis: ", "Electronegativite: ", "Densite: ", "Pt. Fusion: ", "Pt. Ebullition: ", "Etat: ", "Decouvert: ", "Gaz", "Solide", "Liquide", "Inconnue", "Groupe: ", "Etats d'oxydation: "};
    static const char *strings_de[20] = {"Periodiek Systeem CE", "Atoomnr: ", "ANTIEK", "Massa: ", "Neutronen: ", "Protonen: ", "Straal: ", "1ste ion: ", "Elektronegativiteit: ", "Dichtheid: ", "Smeltpunt: ", "Kookpunt: ", "Aggregatietoestand: ", "Jaar ontdekking: ", "Gas", "Vast", "Vloeibaar", "Onbekend", "Groep: ", "Oxidatietoestand: "};
    static const char *strings_es[20] = {"Tabla Periodica CE", "# Atomico: ", "DESCONOCIDO", "Peso: ", "Neutrones: ", "Protones: ", "Radio: ", "1er ion: ", "Electronegatividad: ", "Densidad: ", "Pt. Fusion: ", "Pt. Ebullicion: ", "Estado: ", "Descubier: ", "Gas", "Solido", "Liquido", "Desconocida", "Grupo: ", "Estados de oxidacion: "};
    static const char *elementNames_en[118] = {"Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", "Carbon", "Nitrogen", "Oxygen", "Fluorine", "Neon", "Sodium", "Magnesium", "Aluminium", "Silicon", "Phosphorus", "Sulfur", "Chlorine", "Argon", "Potassium", "Calcium", "Scandium", "Titanium", "Vanadium", "Chromium", "Manganese", "Iron", "Cobalt", "Nickel", "Copper", "Zinc", "Gallium", "Germanium", "Arsenic", "Selenium", "Bromine", "Krypton", "Rubidium", "Strontium", "Yttrium", "Zirconium", "Niobium", "Molybdenum", "Technetium", "Ruthenium", "Rhodium", "Palladium", "Silver", "Cadmium", "Indium", "Tin", "Antimony", "Tellurium", "Iodine", "Xenon", "Cesium", "Barium", "Lanthanum", "Cerium", "Praseodymium", "Neodymium", "Promethium", "Samarium", "Europium", "Gadolinium", "Terbium", "Dysprosium", "Holmium", "Erbium", "Thulium", "Ytterbium", "Lutetium", "Hafnium", "Tantalum", "Tungsten", "Rhenium", "Osmium", "Iridium", "Platinium", "Gold", "Mercury", "Thallium", "Lead", "Bismuth", "Polonium", "Astatine", "Radon", "Francium", "Radium", "Actinium", "Thorium", "Protactinium", "Uranium", "Neptunium", "Plutonium", "Americium", "Curium", "Berkelium", "Californium", "Einsteinium", "Fermium", "Mendelevium", "Nobelium", "Lawrencium", "Rutherfordium", "Dubnium", "Seaborgium", "Bohrium", "Hassium", "Meitnerium", "Darmstadtium", "Roentgenium", "Copernicium", "Nihonium", "Flerovium", "Moscovium", "Livermorium", "Tennessine", "Oganesson"};
    static const char *elementNames_fr[118] = {"Hydrogene", "Helium", "Lithium", "Beryllium", "Bore", "Carbone", "Azote", "Oxygene", "Fluor", "Neon", "Sodium", "Magnesium", "Aluminium", "Sillicium", "Phosphore", "Soufre", "Chlore", "Argon", "Potassium", "Calcium", "Scandium", "Titane", "Vanadium", "Chrome", "Manganese", "Fer", "Cobalt", "Nickel", "Cuivre", "Zinc", "Gallium", "Germanium", "Arsenic", "Selenium", "Brome", "Krypton", "Rubidium", "Strontium", "Yttrium", "Zirconium", "Niobium", "Molybdene", "Technetium", "Ruthenium", "Rhodium", "Palladium", "Argent", "Cadmium", "Indium", "Etain", "Antimoine", "Tellure", "Iode", "Xenon", "Cesium", "Baryum", "Lanthane", "Cerium", "Praseodyme", "Neodyme", "Promethium", "Samarium", "Europium", "Gadolinium", "Terbium", "Dysprosium", "Holmium", "Erbium", "Thulium", "Ytterbium", "Lutecium", "Hafnium", "Tantale", "Tungstene", "Rhenium", "Osmium", "Iridium", "Platine", "Or", "Mercure", "Thallium", "Plomb", "Bismuth", "Polonium", "Astate", "Radon", "Francium", "Radium", "Actinium", "Thorium", "Protactinium", "Uranium", "Neptunium", "Plutonium", "Americium", "Curium", "Berkelium", "Californium", "Einsteinium", "Fermium", "Mendelevium", "Nobelium", "Lawrencium", "Rutherfordium", "Dubnium", "Seaborgium", "Bohrium", "Hassium", "Meitnerium", "Darmstadtium", "Roentgenium", "Copernicium", "Nihonium", "Flerovium", "Moscovium", "Livermorium", "Tennesse", "Oganesson"};
    static const char *elementNames_de[118] = {"Waterstof", "Helium", "Lithium", "Beryllium", "Boor", "Koolstof", "Stikstof", "Zuurstof", "Fluor", "Neon", "Natrium", "Magnesium", "Aluminium", "Silicium", "Fosfor", "Zwavel", "Chloor", "Argon", "Kalium", "Calcium", "Scandium", "Titanium", "Vanadium", "Chroom", "Mangaan", "Ijzer", "Kobalt", "Nikkel", "Koper", "Zink", "Gallium", "Germanium", "Arseen", "Seleen", "Broom", "Krypton", "Rubidium", "Strontium", "Yttrium", "Zirkonium", "Niobium", "Molybdeen", "Technetium", "Ruthenium", "Rodium", "Palladium", "Zilver", "Cadmium", "Indium", "Tin", "Antimoon", "Telluur", "Jood", "Xenon", "Cesium", "Barium", "Lanthaan", "Cerium", "Praseodymium", "Neodymium", "Promethium", "Samarium", "Europium", "Gadolinium", "Terbium", "Dysprosium", "Holmium", "Erbium", "Thulium", "Ytterbium", "Lutetium", "Hafnium", "Tantaal", "Wolfraam", "Renium", "Osmium", "Iridium", "Platina", "Goud", "Kwik", "Thallium", "Lood", "Bismut", "Polonium", "Astaat", "Radon", "Francium", "Radium", "Actinium", "Thorium", "Protactinium", "Uranium", "Neptunium", "Plutonium", "Americium", "Curium", "Berkelium", "Californium", "Einsteinium", "Fermium", "Mendelevium", "Nobelium", "Lawrencium", "Rutherfordium", "Dubnium", "Seaborgium", "Bohrium", "Hassium", "Meitnerium", "Darmstadtium", "Rontgenium", "Copernicium", "Nihonium", "Flerovium", "Moscovium", "Livermorium", "Tennessine", "Oganesson"};
    static const char *elementNames_es[118] = {"Hidrogeno", "Helio", "Litio", "Berilio", "Boro", "Carbono", "Nitrogeno", "Oxigeno", "Fluor", "Neon", "Sodio", "Magnesio", "Aluminio", "Silicio", "Fosforo", "Azufre", "Cloro", "Argon", "Potasio", "Calcio", "Escandio", "Titanio", "Vanadio", "Cromo", "Manganeso", "Hierro", "Cobalto", "Niquel", "Cobre", "Zinc", "Galio", "Germanio", "Arsenico", "Selenio", "Bromo", "Kripton", "Rubidio", "Estroncio", "Itrio", "Zirconio", "Niobio", "Molibdeno", "Tecnecio", "Rutenio", "Rodio", "Paladio", "Plata", "Cadmio", "Indio", "Estano", "Antimonio", "Telurio", "Yodo", "Xenon", "Cesio", "Bario", "Lantano", "Cerio", "Praseodimio", "Neodimio", "Prometio", "Samario", "Europio", "Gadolinio", "Terbio", "Disprosio", "Holmio", "Erbio", "Tulio", "Iterbio", "Lutecio", "Hafnio", "Tantalio", "Wolframio", "Renio", "Osmio", "Iridio", "Platino", "Oro", "Mercurio", "Talio", "Plomo", "Bismuto", "Polonio", "Astato", "Radon", "Francio", "Radio", "Actinio", "Torio", "Protactinio", "Uranio", "Neptunio", "Plutonio", "Americio", "Curio", "Berkelio", "Californio", "Einstenio", "Fermio", "Mendelevio", "Nobelio", "Laurencio", "Rutherfordio", "Dubnio", "Seaborgio", "Bohrio", "Hassio", "Meitnerio", "Darmstadtio", "Roentgenio", "Copernicio", "Nihonio", "Flerovio", "Moscovio", "Livermorio", "Teneso", "Oganeson"};
    
    static const char *groups_en[11] = {"alkali metal", "alkaline metal", "non-metal", "transition metal", "metalloid", "other metal", "halogen", "noble gas", "lanthanoid", "actinoid", "unknown"};
    static const char *groups_fr[11] = {"metal alcalin", "base alcalino-terre.", "non-metallique", "metal de transition", "metalloide", "autre metal", "halogene", "gaz rare", "lanthanide", "actinide", "inconnu"};
    static const char *groups_de[11] = {"alkalimetalen", "aardalkalimetalen", "niet-metalen", "overgangsmetaal", "metaloiden", "other metal", "halogenen", "edelgassen", "lanthaniden", "actiniden", "onbekend"};
    static const char *groups_es[11] = {"alcalino", "alcalinoterreos", "no metal", "metal de transicion", "semimetal", "otro metal", "halogenos", "gas noble", "lantanido", "actinido", "desconocida"};

    const char** localizedStrings = strings_en;
    const char** localizedGroups = groups_en;
    const char** localizedElementNames = elementNames_en;

    switch ((int)system_info->language) {
            case FR_LOCAL:
                localizedStrings = strings_fr;
                localizedGroups = groups_fr;
                localizedElementNames = elementNames_fr;
                break;
            case DE_LOCAL:
                localizedStrings = strings_de;
                localizedGroups = groups_de;
                localizedElementNames = elementNames_de;
                break;
            case ES_LOCAL:
                localizedStrings = strings_es;
                localizedGroups = groups_es;
                localizedElementNames = elementNames_es;
                break;
    }
    
    uint8_t tempAtom;
    int tempPosX;
    uint8_t tempPosY;
    kb_key_t key, enterKey;
    
    static const uint8_t nonNobleGases[5] = {1, 7, 8, 9, 17};
    
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
    gfx_PrintStringXY(localizedStrings[0],(LCD_WIDTH - gfx_GetStringWidth(localizedStrings[0])) / 2, 3);
    
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
            gfx_PrintStringXY(localizedElementNames[currAtom-1], 90, 215);
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
            gfx_PrintStringXY(el->eleConf,(LCD_WIDTH - gfx_GetStringWidth(el->eleConf)) / 2, 170);
            gfx_SetTextScale(1,1);
            
            gfx_PrintStringXY(localizedStrings[3], 50, 35);
            gfx_PrintString(el->mass);
            gfx_PrintString(" u");
            
            gfx_PrintStringXY(localizedStrings[1], 50, 25);
            gfx_PrintUInt(currAtom,1+(currAtom>9)+(currAtom>99));
            
            gfx_PrintStringXY(localizedStrings[5], 50, 55);
            gfx_PrintUInt(currAtom,1+(currAtom>9)+(currAtom>99));
            
            gfx_PrintStringXY(localizedStrings[12], 50, 45);
            isAGas = false;
            if (el->group == 7 || memchr(nonNobleGases, currAtom, 5)){
                gfx_PrintString(localizedStrings[14]);
                isAGas = true;
            } else {
                if (currAtom == 35 || currAtom == 80)
                {
                    gfx_PrintString(localizedStrings[16]);
                } else {
                    if (currAtom > 103){
                        gfx_PrintString(localizedStrings[17]);
                    } else {
                        gfx_PrintString(localizedStrings[15]);
                    }
                }
            }
            
            gfx_PrintStringXY(localizedStrings[4], 50, 65);
            gfx_PrintUInt(el->neutrons, 1+(el->neutrons>9)+(el->neutrons>99));
            
            gfx_PrintStringXY(localizedStrings[9], 50, 75);
            gfx_PrintString(el->density);
            if (isAGas){
                gfx_PrintString(" g/l");
            } else {
                gfx_PrintString(" g/cm3");
            }
            
            gfx_PrintStringXY(localizedStrings[8], 50, 85);
            gfx_PrintString(el->electronegativity);
            
            gfx_PrintStringXY(localizedStrings[18], 50, 95);
            gfx_PrintString(localizedGroups[el->group]);
            
            gfx_PrintStringXY(localizedStrings[10], 50, 105);
            gfx_PrintString(el->boil);
            gfx_PrintString(" K.");
            
            gfx_PrintStringXY(localizedStrings[11], 50, 115);
            gfx_PrintString(el->melt);
            gfx_PrintString(" K.");
            
            gfx_PrintStringXY(localizedStrings[13], 50, 125);
            if (el->year){
                gfx_PrintUInt(el->year, 4);
            } else {
                gfx_PrintString(localizedStrings[2]);
            }
            
            gfx_PrintStringXY(localizedStrings[6], 50, 135);
            gfx_PrintUInt(el->radius, 2+(el->radius > 99));
            gfx_PrintString(" pm");
            
            gfx_PrintStringXY(localizedStrings[7], 50, 145);
            gfx_PrintUInt(el->firstIon, 3+(el->firstIon > 999));
            gfx_PrintString(" kJ/mol");
            
            gfx_PrintStringXY(localizedStrings[19], 50, 155);
            gfx_PrintString(el->oxState);
            
            screen = DETAILS_SCREEN;
        }
        
        prevArrowKey = key;
        prevEnterKey = enterKey;
            
    } while (kb_Data[1] != kb_Graph && kb_Data[6] != kb_Clear);
    
    gfx_End();
    return 0;
}
