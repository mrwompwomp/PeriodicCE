#include <stdlib.h>
#include <graphx.h>
#include <keypadc.h>
#include <string.h>

int isElementPresent(uint8_t elementList[], int listLength, int atomicNumber) {
    bool isElementPresent = false;
    for (uint8_t i = 0; i < listLength; i++) {
        if (elementList[i] == atomicNumber) {
            isElementPresent = true;
            break;
        }
    }
    return isElementPresent;
}

int GetElementType(int atomicNumber) {
    uint8_t nonMetals[7] = {1,6,7,8,15,16,34};
    if (isElementPresent(nonMetals,7,atomicNumber)) {
        return 1;
    }
    uint8_t nobleGases[6] = {2,10,18,36,54,86};
    if (isElementPresent(nobleGases,6,atomicNumber)) {
        return 8;
    }
    uint8_t alkaliMetals[6] = {3,11,19,37,55,87};
    if (isElementPresent(alkaliMetals,6,atomicNumber)) {
        return 2;
    }
    uint8_t alkalineMetals[6] = {4,12,20,38,56,88};
    if (isElementPresent(alkalineMetals,6,atomicNumber)) {
        return 3;
    }
    uint8_t halogens[5] = {9,17,35,53,85};
    if (isElementPresent(halogens,5,atomicNumber)) {
        return 7;
    }
    uint8_t metaloids[7] = {5,14,32,33,51,52,84};
    if (isElementPresent(metaloids,7,atomicNumber)) {
        return 6;
    }
    uint8_t other[7] = {13,31,49,50,81,82,83};
    if (isElementPresent(other,7,atomicNumber)) {
        return 5;
    }
    if (atomicNumber>56 && atomicNumber<72){
        return 10;
    }
    if (atomicNumber>88 && atomicNumber<104){
        return 11;
    }
    if (atomicNumber>112){
        return 9;
    }
    return 4;
}

int main(void)
{
    char atomNameList[] = "Hydrogen    Helium      Lithium     Beryllium   Boron       Carbon      Nitrogen    Oxygen      Fluorine    Neon        Sodium      Magnesium   Aluminium   Silicon     Phosphorus  Sulfur      Chlorine    Argon       Potassium   Calcium     Scandium    Titanium    Vanadium    Chromium    Manganese   Iron        Cobalt      Nickel      Copper      Zinc        Gallium     Germanium   Arsenic     Selenium    Bromine     Krypton     Rubidium    Strontium   Yttrium     Zirconium   Niobium     Molybdenum  Technetium  Ruthenium   Rhodium     Palladium   Silver      Cadmium     Indium      Tin         Antimony    Tellurium   Iodine      Xenon       Cesium      Barium      Lanthanum   Cerium      PraseodymiumNeodymium   Promethium  Samarium    Europium    Gadolinium  Terbium     Dysprosium  Holmium     Erbium      Thulium     Ytterbium   Lutetium    Hafnium     Tantalum    Tungsten    Rhenium     Osmium      Iridium     Platinium   Gold        Mercury     Thallium    Lead        Bismuth     Polonium    Astatine    Radon       Francium    Radium      Actinium    Thorium     ProtactiniumUranium     Neptunium   Plutonium   Americium   Curium      Berkelium   Californium Einsteinium Fermium     Mendelevium Nobelium    Lawrencium              Dubnium     Seaborgium  Bohrium     Hassium     Meitnerium  DarmstadtiumRoentgenium Copernicium Nihonium    Flerovium   Moscovium   Livermorium Tennessine  Oganesson   ";
    char title[] = "Periodic Table CE";
    uint8_t colors[11] = {7,228,230,234,241,29,23,157,149,47,217};
    int tempAtom;
    int tempElementType;
    int tempPosX;
    int tempPosY;
    kb_key_t key;

    char symbols[236] = "H HeLiBeB C N O F NeNaMgAlSiP S ClArK CaScTiV CrMnFeCoNiCuZnGaGeAsSeBrKrRbSrY ZrNbMoTcRuRhPdAgCdInSnSbTeI XeCsBaLaCePrNdPmSmEuGdTbDyHoErTmYbLuHfTaW ReOsIrPtAuHgTlPbBiPoAtRnFrRaAcThPaU NpPuAmCmBkCfEsFmMdNoLrRfDbSgBhHsMtDsRgCnNhFlMcLvTsOg";
    
    char atomicMasses[708] = "1.00794.00266.941 9.012210.81 12.01114.00715.99918.99820.18 22.99 24.30526.98228.08630.97432.06635.45339.94839.09840.07844.95647.86750.94251.99654.93855.84558.93358.69336.54665.39 69.72372.61 74.92278.96 79.90483.8  85.46887.62 88.90691.22492.90695.94 98    101.07102.91106.42107.87112.41114.82118.71121.76127.6 126.91131.29132.91137.33138.91140.12140.91144.24145   150.36151.97157.25158.93162.5 164.93167.26168.93173.04174.97178.49180.95183.84186.21190.23192.22195.08196.97200.59204.38207.2 208.98209   210   222   223   226   227   232.04231.04238.03237   244   243   247   247   251   252   257   258   259   262.11265.12268.13271.13270   277.15276.15281.16280.16285.17284.18289.19288.19293   294   294   ";
    
    char desnityList[590] = "0.09 0.1790.5351.8482.46 2.26 1.2511.4291.6960.9  0.9681.7382.7  2.33 1.8231.96 3.2141.7840.8561.55 2.9854.5076.11 7.14 7.47 7.8748.9  8.9088.92 7.14 5.9045.3235.7274.8193.12 3.75 1.5322.63 4.4726.5118.57 10.2811.5 12.3712.4512.0210.498.65 7.31 7.31 6.6976.24 4.94 5.9  1.8793.51 6.1466.6896.64 7.01 7.2647.3535.2447.9018.2198.5518.7959.0669.3216.57 9.84113.3116.6519.2521.0222.6122.6521.0919.3 13.5311.8511.349.78 9.196N/A  9.73 N/A  5    10.0711.7215.3719.0520.4519.82N/A  13.5114.7815.1 8.84 N/A  N/A  N/A  N/A  23.2 29.3 35   37.1 40.7 37.4 34.8 28.7 23.7 16   14   13.5 12.9 7.2  5    ";
    
    char electronegList[472] = "2.20N/A 0.981.572.042.553.043.443.98N/A 0.931.311.611.9 2.192.583.16N/A 0.821   1.361.541.631.661.551.831.881.911.9 1.651.812.012.182.552.963   0.820.951.221.331.6 2.161.9 2.2 2.282.2 1.931.691.781.962.052.1 2.662.6 0.790.891.1 1.121.131.14N/A 1.17N/A 1.2 N/A 1.221.231.241.25N/A 1.271.3 1.5 2.361.9 2.2 2.2 2.282.542   1.622.332.022   2.2 N/A 0.7 0.9 1.1 1.3 1.5 1.381.361.281.3 1.3 1.3 1.3 1.3 1.3 1.3 1.3 1.3 N/A N/A N/A N/A N/A N/A N/A N/A N/A N/A N/A N/A N/A N/A N/A ";
    
    char groups[176] = "non-metal       alkali metal    alkaline metal  transition metalother metal     metaloid        halogen         noble gas       unknown         lanthanoid      actinoid        ";
    
    char* substr = malloc(2);
    char* atomName = malloc(12);
    char* currAtomMass = malloc(6);
    char* currDensity = malloc(5);
    char* currElectroneg = malloc(4);
    char* currElementType = malloc(16);
    
    
    uint8_t mainArr[10][18] = {
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
        {3,4,0,0,0,0,0,0,0,0,0,0,5,6,7,8,9,10},
        {11,12,0,0,0,0,0,0,0,0,0,0,13,14,15,16,17,18},
        {19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36},
        {37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54},
        {55,56,0,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86},
        {87,88,0,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71},
        {0,0,0,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103}
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
    gfx_PrintStringXY(title, 50, 3);
    gfx_PrintStringXY("X", 298, 215);
    gfx_SetTextScale(1,1);
    
    //Draw the table
    for(int i=0; i<10; i++) {
      for(int j=0;j<18;j++) {
          tempAtom = mainArr[i][j];
          if (tempAtom){
              tempElementType = GetElementType(tempAtom);
              strncpy(substr, symbols+2*(tempAtom-1), 2);
              gfx_SetColor(colors[tempElementType]);
              tempPosX = 8+17*j;
              tempPosY = 32+17*i;
              
              gfx_FillRectangle_NoClip(tempPosX, tempPosY, 16, 16);
              tempPosX += (4*(substr[1]==' '));
              gfx_PrintStringXY(substr,tempPosX, tempPosY+4);
          }
        }
    }
    gfx_SetColor(255);
    gfx_Line_NoClip(50,175,55,175);
    gfx_Line_NoClip(50,191,55,191);
    gfx_Line_NoClip(50,122,50,191);
    
    //Initialize starting position 
    int i = 1;
    int j = 0;
    int first = true;
    bool prevkey = false;
    int currAtom;
    
    do
    {
        kb_Scan();
        key = kb_Data[7];
        if (first){
            key = kb_Up;
            first = false;
        }
        if (key && !prevkey) {
            gfx_SetColor(0);
            gfx_Rectangle_NoClip(7+17*j,31+17*i,18,18);
            gfx_FillRectangle_NoClip(50,25,160,50);
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
            gfx_SetColor(255);
            gfx_Rectangle_NoClip(7+17*j,31+17*i,18,18);

            //the only atom whos name is 13 chars long
            gfx_SetTextScale(2,2);
            if (currAtom == 104){
                gfx_PrintStringXY("Rutherfordium",90, 215);
            } else {
                strncpy(atomName, atomNameList+12*(currAtom-1), 12);
                gfx_PrintStringXY(atomName, 90, 215);
            }
            gfx_SetColor(colors[GetElementType(currAtom)]);
            gfx_FillRectangle_NoClip(40, 205, 32, 32);
            strncpy(substr, symbols+2*(currAtom-1), 2);
            gfx_PrintStringXY(substr,41+(9*(substr[1]==' ')), 214);
            gfx_SetTextScale(1,1);

            strncpy(currAtomMass, atomicMasses+6*(currAtom-1), 6);
            gfx_PrintStringXY("Mass:", 50, 35);
            gfx_PrintStringXY(currAtomMass, 88, 35);

            gfx_PrintStringXY("Density:               g/l", 50, 45);
            strncpy(currDensity, desnityList+5*(currAtom-1), 5);
            gfx_PrintStringXY(currDensity, 109, 45);
            
            gfx_PrintStringXY("EN.:", 50, 55);
            strncpy(currElectroneg, electronegList+4*(currAtom-1), 4);
            gfx_PrintStringXY(currElectroneg, 76, 55);
            
            gfx_PrintStringXY("Group:", 50, 65);
            tempElementType = GetElementType(currAtom);
            strncpy(currElementType, groups+16*(tempElementType-1), 16);
            gfx_PrintStringXY(currElementType, 96, 65);
            
            gfx_PrintStringXY("Number:", 50, 25);
            gfx_SetTextXY(105, 25);
            gfx_PrintInt(currAtom,1+(currAtom>9)+(currAtom>99));
        }
        prevkey = key;
  
    } while (kb_Data[1] != kb_Graph && kb_Data[6] != kb_Clear);
    
    gfx_End();
    kb_Reset();
    
    return 0;
}

