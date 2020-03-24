
#include "main.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_flash.h"

#include "ltdc.h"

#include "Touchscreen.h"
#include "stdint.h"
#include <stdlib.h>
#include "GUI.h"
#include "CRC_check.h"
#include "Calibration_Address.h"
#include "Rabs_math.h"

#include "usb_device.h"
#include "usbd_customhid.h"

#include "Qspi_func.h"


//#include "fatfs.h"
//#include "CQS_Calculate.h"
//#include "CRI_Calculate.h"
//#include "Calculate_Measure.h"

#define MEASURE 0x00

//CMD DEFINITION
#define CMD_DATA_TRANSMIT 				0x01
#define CMD_RABS_DATA_TRANSMIT 		0x01
#define CMD_CNFG 									0x02
#define CMD_CAPTURE 							0x03
#define CMD_CRC_LOAD_STATUS				0x66
#define CMD_CALCULATED_DATA_TRANSMIT	0x04

#define CMD_FLASH_SET_WR_ADDR	 		0x0A
#define CMD_FLASH_WR_DATA			 		0x0B
#define CMD_FLASH_READ_DATA			 	0x0C
#define CMD_FLASH_ERASE_DATA			0x0D

//FLASH DATA ADDRESS
#define FLASH_DATA_START 		0x08100000
#define FLASH_DATA_SIZE			21002 //number of uint64_t data
#define FLASH_CRC_ADDR 			0x08129050 //addr for FLASH CRC check


UART_HandleTypeDef hlpuart1;
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

ADC_HandleTypeDef hadc1;
I2C_HandleTypeDef hi2c1;
LTDC_HandleTypeDef hltdc;
DMA2D_HandleTypeDef hdma2d;

//SD_HandleTypeDef hsd1;
//static void MX_SDMMC1_SD_Init(void);
//extern char SDPath[4];
//
//uint8_t wtext[] = "TKA spectrometry SD CARD TEST"; /* File write buffer */
//uint8_t rtext[100];
//
//
extern USBD_HandleTypeDef hUsbDeviceFS;
//FLASH_EraseInitTypeDef EraseInitStruct;
//CRC_Check_StatusTypeDef CRC_STATUS;


////////////////////////////////////////////////////////////


uint8_t dataToSend[64]= {0};
uint8_t dataToReceive[12]= {0};
uint8_t flag_EOS = 0;

uint64_t	flash_data_write, flash_data_read;
uint32_t	flash_address;
uint8_t		flash_data_read_SND[8]= {0};

uint16_t Calibration_year, Serial_part_device, Serial_number_device, Calibration_date, Calibration_month;

//extern FATFS SDFatFs;
//uint16_t graph_data[250] = {400,470,540,610,680,750,820,890,960,1030,1100,1170,1240,1310,1380,1450,1520,1590,1660,1730,1800,1870,1940,2010,2080,2150,2220,2290,2360,2430,2500,2570,2640,2710,2780,2850,2920,2990,3060,3130,3200,3270,3340,3410,3480,3550,3620,3690,3760,3830,3900,3970,4040,4110,4180,4250,4320,4390,4460,4530,4600,4670,4740,4810,4880,4950,5020,5090,5160,5230,5300,5370,5440,5510,5580,5650,5720,5790,5860,5930,6000,6070,6140,6210,6280,6350,6420,6490,6560,6630,6700,6770,6840,6910,6980,7050,7120,7190,7260,50500,50500,50000,49000,49000,49000,49000,50500,7890,7960,8030,8100,8170,8240,8310,8380,8450,8520,8590,8660,8730,8800,8870,8940,9010,9080,9150,9220,9290,9360,9430,9500,9570,9640,9710,9780,9850,9920,9990,10060,10130,10200,10270,10340,10410,10480,10550,10620,10690,10760,10830,10900,10970,11040,11110,11180,11250,11320,11390,11460,11530,11600,11670,11740,11810,11880,11950,12020,12090,12160,12230,12300,12370,12440,12510,12580,12650,12720,12790,12860,12930,13000,13070,13140,13210,13280,13350,13420,13490,13560,13630,13700,13770,13840,13910,13980,14050,14120,14190,14260,14330,14400,14470,14540,14610,14680,14750,14820,14890,14960,15030,15100,15170,15240,15310,15380,15450,15520,15590,15660,15730,15800,15870,15940,16010,16080,16150,16220,16290,16360,16430,16500,16570,16640,16710,16780,16850,16920,16990,17060,17130,17200,17270,17340,17410,17480,17550,17620,17690,17760, 17790};
//
//uint16_t graph_data2[250] = {0};
//uint16_t PARGraph_B, PARGraph_G, PARGraph_R, PARGraph_IR;
//uint8_t BluetoothStat = 0;

////////////////////////////////////////////////////////////////////////

uint8_t RxBuf[2];
extern uint8_t  GUI_screen_state, Graph_Field, Source_Type, Color_Field, Measure_Color_xy, pause, flag_spectral;
extern uint16_t Measure_Field;
//Line recieve data
uint16_t Line[1024] = {0}, Line_buff[1024] = {0};
float Line_Rabs_buff[1024] = {0.35, 0.55, 256.68, 5468.23, 1.56e-12, 155, 87.97, 56771.86, 10.558, 789.8, 0.0013, 12.144, 4557.86, 17.7999, 555.59, 3247.91};
float max_Rabs;
//Calibration factors data
float Spectral_Corection_Buff[1024] = {0}, WaveLenght[1024] = {0}, Scattering_Light = 0, Exposure_Factor = 0, Hazard_Blue[1024] = {0}, Hazard_Retina[1024] = {0};
float Factor1 = 0, Factor2 = 0, EnergyFactor_E = 0, EnergyFactor_L = 0;
float S0_lambda[1024] = {0}, S1_lambda[1024] = {0}, S2_lambda[1024] = {0};
float E_day, E_day_Wt, E_Night, SP_Measure, PPFD_PPL_Measure, PPFD_PPL_Blue_Measure, PPFD_PPL_Green_Measure, PPFD_PPL_Red_Measure, PPFD_PPL_Far_Red_Measure,
	ELr_Measure, ELb_Measure, CCT_Measure;

float calibratre_x_1964[1024] = {0}, calibratre_z_1964[1024] = {0}, calibratre_x_1931[1024] = {0}, calibratre_y_1931[1024] = {0}, calibratre_z_1931[1024] = {0};
uint16_t  WaveLenght_Graph[4] = {0},  DarkSignal = 0;
uint8_t Mode_EL = 1, SD_Detect, old_sd_detect = 10, write_FileNum = 0;
uint16_t colorimetry_XYZ[3] = {0}, lambda_d_Measure, lambda_c_Measure, Tc_Measure = 0;
int16_t colorimetry_LAB[3] = {0};
extern int16_t delta_Eab_Measure;
float colorimetry_xy[2] = {0}, colorimetry_uv[2] = {0};
uint16_t max_el = 0;
uint16_t cnt_delay_bar = 0;
extern uint8_t Rotation_Screen_Spectral, Rotation_Screen_Spectral_Old, Calculate_deltaEab_Done, Color_rend_Field, preGUI_screen_state;

//Calibration table factors data
float Spectral_day[1024] = {0}, Spectral_night[1024] = {0}, Spectral_B[1024] = {0}, Spectral_R[1024] = {0};

//																					7.812ms	15.625ms	31.25ms	62.5ms	125ms	250ms	500ms	1s			2s			4s
const uint16_t exposure_timer_period[10] = {93,			186,			372,		744,		1488,	2976,	5952,	11905,	23810,	47619}; //93 = 7.812ms

volatile uint16_t	i=0, j=0;
volatile uint8_t	exp_num = 0, VGain = 0, LaserOnOff = 0, TFT_ON_OFF = 1, temp = 0, send_usb_block = 0, MeasureFlag_display = 0;
double percentage_charge; //battry charge
volatile uint32_t RGB565_480x272[130560] = {0x00000000};
uint8_t pause_button = 0;
/*bluetooth variable*/
const char ready[] = "TKA_SPECTROMETRY\r\n";
const char format[] = "\r\n";
char send[30];
float test_massive[1024] = {1926.71, 5299.29, 11100.57, 9315.43, 3980.57, 3188.14, 3664.57, 1630.71, 10472.86, 3526.86, 3384.00, 13495.43, 4074.71, 6148.57, 4531.00,
6455.14, 8395.43, 4631.57, 728.14, 4473.71, 3286.71, 11139.86, 6445.86, 10855.14, 5582.29, 11767.14, 14232.00, 3796.71, 11245.14, 6528.29, 11694.00, 10622.86, 2360.00, 8676.43, 7573.14,
12000.43, 2778.00, 7307.43, 550.86, 5516.71, 4844.14, 2842.29, 3001.14, 4703.86, 2198.00, 13131.86, 10063.86, 14106.57, 12594.43, 10966.71, 9173.57, 2684.86, 8156.29, 9743.71, 8636.00,
5238.57, 12117.14, 8587.29, 6230.00, 1341.29, 3054.71, 7155.57, 3783.29, 432.14, 5427.00, 9243.00, 7593.43, 2325.57, 5797.43, 4576.57, 10870.29, 791.14, 13256.00, 8155.29, 5065.57, 9083.00,
9022.29, 12590.57, 12473.57, 11993.29, 2684.71, 1162.57, 1663.57, 9232.14, 8096.29, 9815.71, 4122.00, 2219.71, 1239.71, 9065.43, 7177.71, 1918.43, 10605.86, 11601.29, 4655.00, 5509.43,
12162.57, 13934.71, 5589.71, 2746.00, 2626.71, 4613.86, 9562.71, 12437.29, 12461.57, 3158.71, 3089.29, 9518.43, 508.43, 1896.71, 9601.57, 8334.71, 3520.43, 5625.00, 12591.43, 7020.57,
11300.14, 13377.86, 3554.43, 12720.43, 2832.71, 11305.57, 5171.29, 12604.71, 11893.00, 6919.14, 3227.00, 49.71, 9667.71, 2525.86, 12332.14, 5245.14, 957.71, 10688.29, 2257.71, 12327.86,
2997.43, 8722.57, 9713.71, 7790.00, 10891.71, 3284.00, 4077.29, 8404.71, 8020.14, 14130.14, 2810.57, 12597.00, 10811.86, 5203.57, 10519.14, 3470.43, 11699.00, 1233.00, 579.00, 855.57,
6234.71, 12834.57, 1801.86, 3580.00, 5460.86, 3042.57, 10352.71, 1599.14, 11368.14, 10368.86, 2135.00, 5639.29, 11686.57, 729.29, 137.29, 5294.71, 4505.71, 12797.86, 13874.57, 2224.14,
3397.14, 9457.43, 6285.57, 5440.57, 14167.00, 12381.57, 10224.29, 1574.29, 5545.43, 7599.86, 7814.43, 2086.43, 738.00, 7564.57, 10717.00, 8095.29, 8737.43, 3156.29, 13037.43, 2578.00,
479.00, 10621.86, 9596.29, 12743.86, 1597.14, 11122.71, 10964.29, 2409.57, 2042.00, 2679.71, 12080.00, 4175.86, 11062.43, 3467.43, 5678.43, 13569.86, 7808.57, 5312.00, 8299.00, 5436.00,
13365.29, 8915.86, 6088.57, 2712.71, 9446.57, 12451.29, 11954.57, 11759.71, 6058.71, 2174.86, 6605.14, 9106.43, 7251.29, 11185.86, 8850.14, 12672.57, 10226.14, 3366.57, 6734.29, 404.14,
12423.00, 8846.29, 10711.43, 11297.57, 14272.57, 7461.14, 1604.29, 4376.71, 11991.57, 11434.43, 2409.71, 7661.86, 10132.71, 9331.43, 5077.14, 70.57, 10038.00, 13010.00, 12753.43, 11008.57,
8499.14, 13362.29, 10955.57, 13386.43, 6796.43, 4168.57, 7231.29, 3757.43, 2294.43, 2905.00, 9280.00, 7516.71, 13691.00, 14275.29, 5367.71, 10722.43, 5955.43, 10752.00, 5540.43, 5279.86,
5286.86, 6240.86, 6696.14, 9901.86, 12288.00, 10274.43, 14017.86, 5408.00, 10664.86, 1688.00, 5112.43, 14084.29, 10731.29, 6931.29, 9036.43, 10442.71, 13594.29, 8909.00, 7045.86, 3059.00,
12584.00, 9467.43, 11395.43, 60.00, 13568.43, 12155.71, 2995.43, 6290.71, 5887.86, 2261.86, 4073.14, 7745.29, 9394.86, 5257.14, 3452.29, 12864.57, 7513.57, 436.29, 50.00, 4913.71, 7164.00,
6369.57, 2996.86, 12775.29, 857.29, 8694.86, 13216.00, 8222.86, 3761.00, 10253.71, 7196.43, 6753.14, 3515.00, 4603.57, 11137.71, 10388.14, 5917.29, 10011.14, 5232.00, 9113.14, 6346.29,
79.71, 11695.29, 2880.00, 2676.43, 9609.43, 394.86, 6160.00, 1546.29, 11267.43, 11746.43, 5734.00, 9290.57, 9043.14, 3934.00, 3830.57, 6064.86, 9781.29, 4813.86, 1234.43, 5717.86, 120.14,
6322.57, 7509.71, 13829.29, 10769.57, 7286.86, 11069.14, 6519.29, 1883.00, 10949.86, 1637.43, 6534.00, 11283.71, 1197.00, 9522.14, 3886.14, 3770.43, 263.43, 13339.00, 7583.43, 7007.57,
10401.57, 14063.86, 1897.00, 13297.57, 7677.00, 5850.00, 4128.57, 8343.57, 3118.57, 3600.86, 7017.43, 1796.71, 12122.71, 9424.29, 6528.00, 5077.29, 13447.43, 5213.43, 8467.57, 1773.00,
4284.29, 2107.71, 10924.14, 11717.71, 6791.86, 1212.57, 3403.14, 4358.29, 4588.00, 10037.86, 7398.43, 5133.71, 7256.14, 12873.71, 8305.14, 12803.29, 9338.43, 1427.14, 2141.57, 11979.86,
6027.14, 14099.86, 9656.71, 10293.57, 8019.57, 3216.71, 7510.57, 13292.71, 11512.43, 6002.14, 2916.00, 2785.29, 7890.29, 7659.71, 5884.14, 3230.43, 4552.29, 1773.43, 943.86, 8305.29,
2373.71, 8451.57, 8129.43, 14152.14, 6853.71, 7548.29, 3969.43, 6199.71, 12017.14, 995.00, 6922.57, 83.14, 10727.86, 9814.57, 11040.00, 6205.71, 6148.57, 13748.71, 13885.86, 13271.86,
5697.57, 2010.14, 13826.43, 8092.43, 12664.57, 4422.71, 2242.71, 5372.57, 13019.29, 3601.71, 968.14, 4176.00, 5015.00, 4510.71, 448.29, 10057.00, 3354.43, 844.71, 1679.71, 457.57,
10493.29, 4769.29, 11754.14, 12799.71, 1675.43, 12151.71, 5938.71, 2646.14, 5080.86, 4323.86, 11032.43, 2266.00, 7475.57, 5995.71, 4368.57, 3625.71, 4915.14, 12229.86, 8328.71,
13271.57, 7536.71, 11602.29, 3695.86, 2259.43, 8781.86, 1070.00, 60.00, 12390.57, 13022.71, 13758.14, 9797.57, 3452.86, 6027.57, 13637.86, 13372.43, 9248.14, 3435.57, 8490.00,
2117.43, 4581.14, 12158.57, 189.29, 8819.43, 1234.43, 978.71, 7168.29, 432.71, 1922.57, 1596.86, 2974.57, 11355.86, 6468.00, 13755.71, 4284.71, 6800.00, 9424.14, 12290.29, 5245.86,
8151.00, 246.14, 10120.00, 10934.00, 5162.71, 7602.86, 11220.86, 10645.00, 9623.43, 6643.43, 12298.14, 6143.29, 1410.00, 1736.57, 6635.57, 5861.14, 9147.43, 6918.43, 3139.14, 11614.71,
14093.29, 10906.57, 6502.14, 9804.14, 5234.43, 4083.00, 2506.86, 2008.14, 117.57, 8210.29, 3785.57, 3256.71, 7321.71, 13641.86, 94.43, 12299.00, 4808.14, 11932.86, 3163.86, 2189.57,
11876.43, 12343.29, 4669.43, 8423.71, 10470.57, 2736.14, 8913.29, 169.86, 8735.14, 5260.43, 6994.00, 9434.00, 8343.14, 8614.14, 7323.57, 5918.57, 6180.14, 13286.86, 7441.00, 1829.71,
9858.43, 10714.43, 12398.86, 3224.43, 7443.71, 3533.29, 4397.57, 12836.43, 9102.43, 2732.86, 5041.71, 11810.71, 11772.86, 7138.86, 5568.57, 2640.14, 12629.43, 4840.71, 13900.43, 3699.00,
7569.00, 10306.14, 7020.71, 2388.43, 4114.57, 7462.14, 13618.86, 2067.71, 4989.86, 7458.29, 1676.71, 8109.57, 4699.57, 10405.57, 4006.57, 1205.29, 1501.14, 13796.29, 6521.14, 5813.29,
11230.00, 11481.71, 5881.14, 4032.14, 10954.43, 2289.14, 3977.43, 13437.57, 1449.00, 773.00, 11974.14, 6634.29, 12310.00, 186.00, 12415.00, 12587.14, 3759.14, 1719.29, 6517.14, 13748.71,
8759.29, 10083.57, 9483.14, 7134.57, 7945.86, 5906.57, 1712.43, 1723.00, 7354.57, 77.14, 5635.57, 6787.71, 229.57, 5110.00, 12164.71, 11517.86, 9471.14, 2990.14, 10755.29, 12239.14,
7183.14, 1985.00, 8429.29, 7988.00, 9429.00, 12254.71, 5545.43, 4352.43, 8254.57, 13935.86, 11282.29, 4183.71, 1515.14, 14218.00, 10675.43, 12918.00, 1656.29, 10556.86, 8770.57, 10508.43,
8243.57, 3341.00, 8278.86, 2961.86, 5264.57, 2357.43, 9688.86, 346.43, 6705.57, 3943.43, 13997.57, 8271.71, 12063.57, 12896.71, 11493.14, 867.86, 9529.43, 13128.57, 5415.71, 5987.29,
13999.29, 2276.14, 1075.14, 947.43, 13141.86, 8394.86, 11381.71, 6288.57, 1613.57, 12914.57, 3219.71, 4888.57, 13352.00, 9692.14, 3822.14, 4146.71, 13709.43, 4825.57, 4926.43, 7048.86,
12482.71, 9705.43, 5616.43, 734.29, 8091.00, 5830.57, 14083.71, 1143.14, 12875.57, 6463.43, 10959.29, 3566.86, 9431.71, 421.43, 10815.43, 6596.57, 8316.14, 2266.00, 10905.14, 11240.29,
6511.00, 3129.71, 4116.57, 4743.86, 903.29, 11776.43, 5463.57, 1815.57, 4839.86, 10653.86, 14059.14, 8277.14, 3546.71, 12200.57, 14041.71, 2486.14, 10952.29, 350.86, 9674.86, 10305.43,
4869.71, 1063.14, 6361.57, 7552.43, 9400.29, 14079.14, 12686.00, 2782.57, 9628.00, 1797.00, 3647.00, 5747.43, 6275.14, 462.00, 2811.14, 4202.86, 12041.14, 540.14, 10944.29, 12645.57,
4196.29, 9028.14, 7558.43, 12019.86, 7705.71, 10436.71, 3456.71, 4681.86, 10817.43, 268.14, 3875.29, 9841.57, 8974.14, 5951.29, 10545.29, 2976.00, 864.57, 11035.43, 13627.86, 657.00,
9071.57, 1807.57, 5566.86, 4614.86, 2233.71, 13260.57, 1283.71, 10927.43, 12190.00, 2052.29, 9748.43, 12852.00, 2843.43, 9673.43, 13957.43, 8901.71, 1393.00, 3869.57, 9564.57, 4459.71,
10875.71, 6519.29, 11537.00, 11788.71, 4625.86, 3026.57, 355.57, 4685.00, 12097.43, 4070.57, 12906.29, 5139.14, 4570.43, 1647.71, 927.14, 13998.86, 11.14, 10272.29, 8714.00, 5692.43,
4746.14, 2832.00, 8026.86, 11845.57, 1217.29, 3854.00, 2241.14, 4087.57, 6342.57, 7720.71, 3529.00, 2594.43, 13359.14, 6010.57, 6835.57, 12480.71, 1007.43, 1855.43, 13813.14, 11807.71,
5478.86, 3456.86, 2278.57, 10525.86, 4816.57, 13859.86, 5744.00, 2767.29, 9151.29, 1268.43, 11138.71, 10101.00, 11321.00, 8090.71, 2704.29, 10338.43, 11581.57, 10749.57, 9920.71, 11055.71,
3831.00, 2008.00, 1870.71, 14198.57, 8823.29, 4173.29, 442.57, 5912.57, 4290.86, 1511.71, 1579.00, 2188.57, 6834.57, 2419.57, 11707.00, 90.71, 11893.57, 10389.43, 9853.57, 192.86, 5758.86,
8849.57, 9202.71, 440.57, 12182.43, 3556.86, 12608.71, 2399.43, 3047.00, 5689.00, 1483.43, 9780.57, 12023.86, 8990.86, 5005.57, 8126.71, 7152.43, 3796.00, 3308.86, 4772.00, 9908.14,
13692.00, 7555.57, 10258.43, 12336.86, 10641.29, 8924.57, 12039.71, 4661.43, 8619.71, 3549.57, 2022.14, 9462.00, 2248.86, 3752.71, 6285.86, 6192.43, 12263.43, 7298.14, 6885.86, 6187.43,
5269.14, 7043.29, 3463.43, 10234.43, 11641.00, 1459.00, 11520.00, 5731.57, 425.71, 2013.57, 6499.57, 12196.57, 8484.57, 6104.71, 3226.71, 2141.43, 1584.00, 12490.57, 3884.86, 3367.00,
4485.86, 13103.00, 2657.86, 11811.29, 11094.00, 4527.43, 7947.14, 4113.43, 5538.29, 12002.71, 3461.86, 4198.14, 9902.00, 12950.71, 13736.71, 464.00, 7262.29, 7071.00, 10985.00, 8580.29,
4588.00, 359.43, 10567.86, 10101.29, 2554.29, 10738.86, 7672.00, 9470.00, 9893.86, 3773.14, 4477.43, 3601.86, 8934.57, 11763.43, 8769.43, 8068.57, 13086.57, 13634.71, 2505.71, 3034.29,
4042.29, 11193.86, 7593.00, 13066.00, 13206.57, 11850.29, 1594.71};


uint8_t buff_i2c[3] = {0,0x0A,0x00};
volatile uint32_t cnt_touch_delay =0;


uint8_t str1[60]={0};
typedef struct USART_prop{
	uint8_t usart_buf[13];
	uint8_t usart_cnt;
	uint8_t is_tcp_connect;
	uint8_t is_text;
} USART_prop_ptr;
USART_prop_ptr usartprop;
uint8_t ii=0;

uint8_t adcResult = 0;

uint8_t buff_i2c_b = 0;
uint16_t Touch_x = 0, Touch_y = 0;
double buf_pix;
uint16_t button_pos_x = 155, button_pos_y = 165;

uint32_t n;
extern uint16_t graph_data_old2[335], i_old_color;
uint16_t Cl, Cl_mass[350];


/* Test data for quadspi */
uint8_t qsr1=0, qsr2=0, qsr3=0;

uint32_t 	qspia1=0x0000,
			qspia2=0x1000,
			qspia3=0x2000,
			qspia4=0x3000;

uint8_t 	test1024[1024]={0}, test1024r[1024]={0};
uint16_t 	test16[1502]={0}, test16r[1502]={0};
uint32_t	test32[1024]={0}, test32r[1024]={0};

//uint16_t 	test16[128]={0}, test16_1[128]={0}, test16_2[128]={0};
//uint16_t 	test16r[384]={0};
//uint16_t 	test16r1[512]={0};

///////////////////////////////////////////////////////////////////////////////


void SystemClock_Config(void);

static void MX_ADC1_Init(void);

static void MX_GPIO_Init(void);
static void MX_LTDC_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_DMA2D_Init(void);

static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);


static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);

void _Error_Handler(char *file, int line);



/* Data watchporint trigger functions */
//void DWT_Init(void)
//{
//  if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk))
//  {
//    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//    DWT->CYCCNT = 0;
//    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
//  }
//}
//
//uint32_t DWT_Get(void)
//{
//  return DWT->CYCCNT;
//}
//
//__inline
//uint8_t DWT_Compare(int32_t tp)
//{
//  return (((int32_t)DWT_Get() - tp) < 0);
//}
//
//void DWT_Delay(uint32_t us) // useconds
//{
//  int32_t tp = DWT_Get() + us * (SystemCoreClock/1000000);
//  while (DWT_Compare(tp));
//}


//void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

//void auto_exposure(void);
//void exposure_display(uint16_t X, uint16_t Y);

double Get_Battery_Level()
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 2);
	adcResult = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	return percentage_charge = 100.0*adcResult/190;
}

/*BLUETOOTH UART processing*/

void send_bluetooth_float(uint32_t data)
{
		uint8_t data_bluetooth_send[4] = {0};

		data_bluetooth_send[0] = (data >> 24) & 0x000000FF;
		data_bluetooth_send[1] = (data >> 16) & 0x000000FF;
		data_bluetooth_send[2] = (data >> 8) & 0x000000FF;
		data_bluetooth_send[3] = (data) & 0x000000FF;

		HAL_UART_Transmit(&hlpuart1, (uint8_t*)&data_bluetooth_send, 4, 1);
}

void string_parse(uint8_t* buf_str)
{

	uint32_t buff_float;
	uint8_t	data_bluetooth_send[2] = {0};

	if(buf_str[0] == 0xAB)
	{
		if(buf_str[1] == 0x12)
		{
			if(buf_str[2] == 0x02)
			{
					/*Laser On/Off*/
							LaserOnOff = (buf_str[4] > 0) ? 1 : 0;
						if(LaserOnOff == 0){
					 			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
							}else
							{
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
							}
//							sprintf(send, "TKA battery level: %.1f%%", Get_Battery_Level());
//							HAL_UART_Transmit(&hlpuart1, (uint8_t*)&send, 30, 5);

							//send absolute spectral
							for(i = 0; i < 1024; i++){
								memcpy(&buff_float, &test_massive[i], sizeof(float));
								send_bluetooth_float(buff_float);
						}
							colorimetry_xy[0] = 0.133;
							colorimetry_xy[1] = 0.852;
							//send xy color
								memcpy(&buff_float, &colorimetry_xy[0], sizeof(float));
								send_bluetooth_float(buff_float);

								memcpy(&buff_float, &colorimetry_xy[1], sizeof(float));
								send_bluetooth_float(buff_float);

								//send CCT
								memcpy(&buff_float, &Tc_Measure, sizeof(uint16_t));
								data_bluetooth_send[0] = (buff_float >> 8) & 0x000000FF;
								data_bluetooth_send[1] = (buff_float) & 0x000000FF;
								HAL_UART_Transmit(&hlpuart1, (uint8_t*)&data_bluetooth_send, 2, 1);

								//send Source type
								HAL_UART_Transmit(&hlpuart1, &Source_Type, 1, 1);

								//send delta_Eab
						Calculate_deltaEab_Done = 0x01;
						delta_Eab_Measure = -79;
								if(Calculate_deltaEab_Done == 0x01)
								{
									memcpy(&buff_float, &delta_Eab_Measure, sizeof(int16_t));
									data_bluetooth_send[0] = (buff_float >> 8) & 0x000000FF;
									data_bluetooth_send[1] = (buff_float) & 0x000000FF;
									HAL_UART_Transmit(&hlpuart1, (uint8_t*)&data_bluetooth_send, 2, 1);
								}


			}
		}
	}else
	{
		__asm("nop");
	}
}

//void usb_receive_processing(void)
//{
//	HAL_StatusTypeDef	flash_ok = HAL_ERROR;
//	uint16_t CRC_pack = 0;
//	uint32_t PAGEError = 0;
//		if(dataToReceive[0] == 0xAB)
//		{
//			if(dataToReceive[1] == 0x12)
//			{
//			switch(dataToReceive[2])
//				{
//					case CMD_DATA_TRANSMIT :
//						send_usb_block = 1;
//					if(dataToReceive[3] == CMD_RABS_DATA_TRANSMIT)
//					{
//						packet_generator_Rabs_data_send();
//					}else{
//						packet_generator_data_send();
//					}
//						memset(dataToReceive, 0, sizeof(dataToReceive));
//						send_usb_block = 0;
//					break;
//
//					case CMD_CNFG :
//						send_usb_block = 0;
//						memset(dataToSend, 0, sizeof(dataToSend));
//
//						dataToSend[0] = 0xAB;
//						dataToSend[1] = 0x12;
//						dataToSend[2] = CMD_CNFG;
//
//						if (exp_num != dataToReceive[3]){
//							exp_num = dataToReceive[3];
//							htim2.Init.Period = exposure_timer_period[exp_num];
//							MX_TIM2_Init();
//							Calibration_Exposure_Change(exp_num);
//						} else{
//							__asm("nop");
//						}
//
//					/*Laser On/Off*/
//						if (LaserOnOff != dataToReceive[4]){
//							LaserOnOff = (dataToReceive[4] > 0) ? 1 : 0;
//							if(LaserOnOff == 0){
//								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//							}else
//							{
//								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//							}
//						} else{
//							__asm("nop");
//						}
//
//				/*	Set videogain*/
//						if (VGain != dataToReceive[5]){
//							VGain = (dataToReceive[5] > 0) ? 1 : 0;
//							if(VGain == 0){
//								HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_SET);
//							}else
//							{
//								HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);
//							}
//						} else{
//							__asm("nop");
//						}
//
//					/*	Set TFT On/Off*/
//						if (TFT_ON_OFF != dataToReceive[6]){
//							TFT_ON_OFF = (dataToReceive[6] > 0) ? 1 : 0;
//							if(TFT_ON_OFF == 1){
//								HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);//TFT_booster SHDN on
//								HAL_NVIC_EnableIRQ(TIM4_IRQn); //TFT_booster SHDN on
//								HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET); //LTDC_En on
//							}else
//							{
//								HAL_NVIC_DisableIRQ(TIM4_IRQn);	//TFT_booster SHDN off
//								HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_RESET); //TFT_booster SHDN off
//								HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); //LTDC_En off
//							}
//						} else{
//							__asm("nop");
//						}
//
//					/*	Set E/L Mode*/
//						if (Mode_EL != dataToReceive[7]){
//							Mode_EL = (dataToReceive[7] > 0) ? 1 : 0; //Mode_EL=1 -Rabs_E, Mode_EL=0 -Rabs_L
//						} else{
//							__asm("nop");
//						}
//
//						dataToSend[3] = exp_num;
//						dataToSend[4] = LaserOnOff;
//						dataToSend[5] = VGain;
//						dataToSend[6] = TFT_ON_OFF;
//						dataToSend[7] = Mode_EL;
//						dataToSend[63] = (CRC_pack+dataToSend[0]+dataToSend[1]+dataToSend[2]+dataToSend[3]+dataToSend[4]+dataToSend[5]+dataToSend[6]);
//
//						USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
//						memset(dataToReceive, 0, sizeof(dataToReceive));
//					break;
//
//					case	 CMD_FLASH_ERASE_DATA :
//						EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
//						EraseInitStruct.NbPages = 42;
//						EraseInitStruct.Page = 0;
//						EraseInitStruct.Banks = FLASH_BANK_2;
//						HAL_FLASH_Unlock();
//						if(HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK) {
//							//Erase error!
//						}
//						__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
//						HAL_FLASH_Lock();
//						memset(dataToReceive, 0, sizeof(dataToReceive));
//					break;
//					case CMD_FLASH_SET_WR_ADDR :
//						flash_address = ((uint32_t)dataToReceive[3]<<24)|((uint32_t)dataToReceive[4]<<16)|((uint32_t)dataToReceive[5]<<8)|((uint32_t)dataToReceive[6]);
//
//						dataToSend[0] = 0xAB;
//						dataToSend[1] = 0x12;
//						dataToSend[2] = 0x1A;
//						memset(dataToReceive, 0, sizeof(dataToReceive));
//						HAL_Delay(2);
//					break;
//
//					case CMD_FLASH_WR_DATA :
//						flash_ok = HAL_ERROR;
//						flash_data_write = ((uint64_t)dataToReceive[7]<<56)|((uint64_t)dataToReceive[8]<<48)|\
//																((uint64_t)dataToReceive[9]<<40)|((uint64_t)dataToReceive[10]<<32|\
//																(uint64_t)dataToReceive[3]<<24)|((uint64_t)dataToReceive[4]<<16)|\
//																((uint64_t)dataToReceive[5]<<8)|((uint64_t)dataToReceive[6]);
//						HAL_FLASH_Unlock();
//						__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
//						while(flash_ok != HAL_OK){
//							flash_ok = HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, flash_address, flash_data_write);
//						}
//						HAL_FLASH_Lock();
//						memset(dataToReceive, 0, sizeof(dataToReceive));
//						HAL_Delay(2);
//					break;
//
//					case CMD_FLASH_READ_DATA :
//						flash_address = ((uint32_t)dataToReceive[3]<<24)|((uint32_t)dataToReceive[4]<<16)|((uint32_t)dataToReceive[5]<<8)|((uint32_t)dataToReceive[6]);
//						flash_data_read = flash_data_read_buff(flash_address);
//
//						memcpy(flash_data_read_SND, &flash_data_read, sizeof(uint64_t));
//
//						dataToSend[0] = 0xAB;
//						dataToSend[1] = 0x12;
//						dataToSend[2] = 0x1C;
//
//						dataToSend[7] = flash_data_read_SND[7];
//						dataToSend[8] = flash_data_read_SND[6];
//						dataToSend[9] = flash_data_read_SND[5];
//						dataToSend[10]= flash_data_read_SND[4];
//						dataToSend[3] = flash_data_read_SND[3];
//						dataToSend[4] = flash_data_read_SND[2];
//						dataToSend[5] = flash_data_read_SND[1];
//						dataToSend[6]	= flash_data_read_SND[0];
//
//						USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
//						memset(dataToReceive, 0, sizeof(dataToReceive));
//						HAL_Delay(2);
//					break;
//					case CMD_CRC_LOAD_STATUS:
//						dataToSend[0] = 0xAB;
//						dataToSend[1] = 0x12;
//						dataToSend[2] = 0x66;
//						if(CRC_STATUS == CRC_OK){
//							dataToSend[3] = 0x01;
//						} else
//						{
//							dataToSend[3] = 0x00;
//						}
//						USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataToSend, 64);
//						memset(dataToReceive, 0, sizeof(dataToReceive));
//						HAL_Delay(2);
//					break;
//
//				case CMD_CALCULATED_DATA_TRANSMIT :
//						send_usb_block = 1;
//
//						packet_generator_Calculated_data_send();
//
//						memset(dataToReceive, 0, sizeof(dataToReceive));
//						send_usb_block = 0;
//					break;
//
//
//					default : __asm("nop");
//				}
//			}
//		}
//		else
//		{
//			__asm("nop");
//		}
//}

void UART2_RxCpltCallback(void)
{

	uint8_t b;
  b = str1[0];
 if (usartprop.usart_cnt>12)
  {
    usartprop.usart_cnt = 0;
    HAL_UART_Receive_IT(&hlpuart1,(uint8_t*)str1,1);
    return;
  }
  usartprop.usart_buf[usartprop.usart_cnt] = b;
  if(b==0x0A)
  {
    usartprop.usart_buf[usartprop.usart_cnt+1]=0;
    string_parse((uint8_t*)usartprop.usart_buf);
    usartprop.usart_cnt=0;
    HAL_UART_Receive_IT(&hlpuart1,(uint8_t*)str1,1);

    return;
  }
  usartprop.usart_cnt++;
  HAL_UART_Receive_IT(&hlpuart1,(uint8_t*)str1,1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart==&hlpuart1)
  {
    UART2_RxCpltCallback();
  }
}

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  /* TIM Inits*/
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();		/* Battery level */
  MX_TIM7_Init();

  HAL_Delay(1);

  /* Peripherial Inits */
  MX_ADC1_Init();

  MX_GPIO_Init();

  MX_SPI1_Init();

  MX_LTDC_Init();

  MX_DMA2D_Init();

  MX_I2C1_Init();

  HAL_Delay(1);
  MX_LPUART1_UART_Init();

  HAL_Delay(1);
  MX_USB_DEVICE_Init();

  HAL_NVIC_SetPriority(TIM4_IRQn, 1, 0);  //Booster
  HAL_NVIC_EnableIRQ(TIM4_IRQn);
  HAL_TIM_Base_Start(&htim4);
  HAL_TIM_OC_Start_IT(&htim4, TIM_CHANNEL_1);
  HAL_TIM_OC_Start_IT(&htim4, TIM_CHANNEL_2);

  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  HAL_TIM_Base_Start_IT(&htim6);

  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 1);  //ST Signal
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  HAL_TIM_Base_Start_IT(&htim2);

//  HAL_FLASH_Unlock();
//  HAL_FLASH_OB_Unlock();



 /* For SD Card */
//  MX_TIM7_Init();
//  HAL_NVIC_EnableIRQ(TIM7_IRQn);
//  HAL_Delay(1);
//  HAL_TIM_Base_Start_IT(&htim7);


  HAL_LTDC_SetAddress(&hltdc,(uint32_t) &RGB565_480x272,0);
  Touch_Ini();

  if (USBD_LL_BatteryCharging(&hUsbDeviceFS) != USBD_OK) {
    USBD_Start(&hUsbDeviceFS);
    }

  Get_Battery_Level();
  HAL_Delay(1);


  GUI_Title_Screen();
  HAL_Delay(1000);
//  usb_receive_processing();
  GUI_screen_state = Measure_Screen;
  GUI_Measure_Screen();


  while (1)
  {

//	  usb_receive_processing();

	  GUI_Display_Refresh();

  }

}


void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure the main internal regulator output voltage
    */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 64;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 30;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV5;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1|RCC_PERIPHCLK_USB|RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_SDMMC1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
	PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
	PeriphClkInit.LtdcClockSelection = RCC_LTDCCLKSOURCE_PLLSAI2_DIV4;
	PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_SYSCLK;
	PeriphClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLLP;


  PeriphClkInit.PLLSAI2.PLLSAI2Source = RCC_PLLSOURCE_HSE;
	PeriphClkInit.PLLSAI2.PLLSAI2M = 2;
  PeriphClkInit.PLLSAI2.PLLSAI2N = 9;
  PeriphClkInit.PLLSAI2.PLLSAI2P = RCC_PLLP_DIV2;
  PeriphClkInit.PLLSAI2.PLLSAI2R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI2.PLLSAI2Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI2.PLLSAI2ClockOut = RCC_PLLSAI2_LTDCCLK;

	PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSE;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 2;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 12;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	  HAL_PWREx_EnableVddIO2();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PF5 VIDEO_GAIN*/
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_SET); //VIDEO_GAIN OFF

  /*Configure GPIO pin : PC4 ST LASER*/
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);		//ST init HIGH
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);	//Laser init OFF

    /*Configure GPIO pin : PA7 IRQ*/
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PF2 LTDC_Reset*/
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_SET);

	/*Configure GPIO pin : PF1 TouchScreen_Reset*/
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);

	/*Configure GPIO pin : PF11 LTDC_Display_En*/
	GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET);

		/*Configure GPIO pin : PG11 TFT_BOOSTER*/
	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);

	/*Configure GPIO pin : PF3 Touch_Screen INT*/
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	/*Configure GPIO pin : PC15 SD CARD Detection INT*/
	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 2); //SDO IRQ
	HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0); //Touchscreen IRQ
//	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 1); //SD Card IRQ
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
//	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

static void MX_LTDC_Init(void)
{

  LTDC_LayerCfgTypeDef pLayerCfg;

  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 5;
  hltdc.Init.VerticalSync = 30;
  hltdc.Init.AccumulatedHBP = 40;
  hltdc.Init.AccumulatedVBP = 8;
  hltdc.Init.AccumulatedActiveW = 520;
  hltdc.Init.AccumulatedActiveH = 280;
  hltdc.Init.TotalWidth = 525;
  hltdc.Init.TotalHeigh = 288;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 480;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 272;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  pLayerCfg.FBStartAdress = 0;
  pLayerCfg.ImageWidth = 480;
  pLayerCfg.ImageHeight = 272;
  pLayerCfg.Backcolor.Blue = 255;
  pLayerCfg.Backcolor.Green = 255;
  pLayerCfg.Backcolor.Red = 255;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }


}

/* LPUART1 init function */
static void MX_LPUART1_UART_Init(void)
{

	hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 9600;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}

/* DMA2D init function */
static void MX_DMA2D_Init(void)
{

  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_R2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB565;
  hdma2d.Init.OutputOffset = 0;
	hdma2d.LayerCfg[0].InputOffset = 0;
  hdma2d.LayerCfg[0].InputColorMode = DMA2D_INPUT_RGB565;
  hdma2d.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[0].InputAlpha =125;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 125;

  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
      _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
      _Error_Handler(__FILE__, __LINE__);
  }

}

static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x307075B1;
  hi2c1.Init.OwnAddress1 = 112;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }
  /**Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }
  /**Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Common config
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_8B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.NbrOfDiscConversion = 1;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel
    */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}


/* SPI1 init function */
static void MX_SPI1_Init(void){

  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;//SPI_BAUDRATEPRESCALER_2
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_ENABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;

  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	__HAL_SPI_ENABLE(&hspi1);
}

/* Timer for Line_CLK generator*/
static void MX_TIM5_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 2;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 30;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
  sConfigOC.Pulse = 5;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim5);

}

/*Timer for ST_Exposure time*/
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 10000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = exposure_timer_period[exp_num];
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/*Timer TFT_booster SHDn PWM mode*/
static void MX_TIM4_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 100;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 2000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

	 if (HAL_TIM_OC_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }


  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

	sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 1000; //more cnt - zero; 1000 - 50%
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

	sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 2000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}

static void MX_TIM6_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 48000;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 3800;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }

}

static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 60000;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 200;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
	  _Error_Handler(__FILE__, __LINE__);
  }

}


/*Timer TFT_booster SHDN PWM mode*/
void TIM4_IRQHandler(void)
{

	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_11);


	HAL_NVIC_ClearPendingIRQ(TIM4_IRQn);
	HAL_TIM_IRQHandler(&htim4);
}

/* Get battery lvl */
void TIM6_DAC_IRQHandler(void)
{
	pause_button = 0;
  /* USER CODE BEGIN TIM6_IRQn 0 */
	Get_Battery_Level();

	/* USER CODE END TIM6_IRQn 0 */
	HAL_NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
  HAL_TIM_IRQHandler(&htim6);

}

/*ST signal generator*/
void TIM2_IRQHandler(void)
{

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
//	DWT_Delay(10);
	i = 0;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

  cnt_delay_bar = 0;

	HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);
	HAL_TIM_IRQHandler(&htim2);
}

/*SDO_IRQ interrupt*/
//void EXTI9_5_IRQHandler(void)
//{
//	DWT_Delay(1);
//  HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&RxBuf, (uint8_t*)&RxBuf, 2, 0);
//
//	if((RxBuf[0] << 8 | RxBuf[1])>=0xCFFF)
//	{
//		Line[i] = Line[i-1];
//	} else if((RxBuf[0] << 8 | RxBuf[1])<=0x0EFF)
//	{
//		Line[i] = Line[i-1];
//	} else
//	{
//		Line[i] = RxBuf[0] << 8 | RxBuf[1];
//	}
//
//
//	if(i >= 1023)
//	{
//		if(send_usb_block == 0 && (!pause))
//			{
//				memcpy(Line_buff, Line, sizeof(Line));
//			}
//			i = 0;
//
//	} else
//	{
//			i++;
//	}
//
//	HAL_NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
//  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
//}




/*Touch_screen interrupt*/
void EXTI3_IRQHandler(void)
{
	cnt_touch_delay = cnt_touch_delay + 1;

	uint16_t Touch_x = 0, Touch_y = 0;
	TS_Get_XY1(TS_I2C_ADDRESS, &Touch_x, &Touch_y);



	if((!TFT_ON_OFF) && (cnt_touch_delay >= 50))
	{
			TFT_ON_OFF = 0x01;
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_11, GPIO_PIN_SET);//TFT_booster SHDN on
			HAL_NVIC_EnableIRQ(TIM4_IRQn); //TFT_booster SHDN on
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET); //LTDC_En on
		}
		else{
		if(TFT_ON_OFF && (cnt_touch_delay >= 0x08)){

			if((Mode_EL == 0x00) && ((Touch_x >= 109*TS_Callib & Touch_x <= (109+54)*TS_Callib & Touch_y >=426*TS_Callib & Touch_y <=(426+54)*TS_Callib)))
			{
				pause_button++;
				if(pause_button > 3)
				{
					LaserOnOff = !LaserOnOff;
					LaserOnOff ? HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET):HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
					cnt_touch_delay = 0;
					pause_button = 0;
				}
				GUI_Touch_Processing();
				cnt_touch_delay = 0;
			} else {
				GUI_Touch_Processing();
				cnt_touch_delay = 0;
			}
		}

		HAL_NVIC_ClearPendingIRQ(EXTI3_IRQn);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
	}
}

/* SD ???  */
//void TIM7_IRQHandler(void)
//{
//	if((GUI_screen_state == Measure_Screen || GUI_screen_state == Measure2_Screen || GUI_screen_state == Measure3_Screen||
//			GUI_screen_state == Graph_Screen || GUI_screen_state == Color_Screen) && !pause &&  !flag_spectral)
//		{
//			cnt_delay_bar++;
//
//			if(exp_num > 4){
//
//				if(cnt_delay_bar == ((exposure_timer_period[exp_num]/12)/500))
//					{
//						GUI_Bar_Measure(85, 13, 0.2);
//					}
//				else if (cnt_delay_bar == 2*(exposure_timer_period[exp_num]/12)/500)
//					{
//						GUI_Bar_Measure(85, 13, 0.4);
//					}
//					else if (cnt_delay_bar == 3*(exposure_timer_period[exp_num]/12)/500)
//					{
//						GUI_Bar_Measure(85, 13, 0.6);
//					}
//					else if (cnt_delay_bar == 4*(exposure_timer_period[exp_num]/12)/500)
//					{
//						GUI_Bar_Measure(85, 13, 0.8);
//					 }
//					else if (cnt_delay_bar == 5*((exposure_timer_period[exp_num]/12)/500))
//					{
//
//						GUI_Bar_Measure(85, 13, 1);
//					}
//				} else if(exp_num > 2)
//				{
//							if(cnt_delay_bar == 1){
//								GUI_Bar_Measure(85, 13, 0.5);
//							} else if(cnt_delay_bar == 2){
////								if(preGUI_screen_state == Graph_Screen){
////									Spectral_DrawGraph(20, 20, Line_buff, TFT_Red, Rotation_Screen_Spectral);
////								//	Spectral_RefreshGraph(Rotation_Screen_Spectral);
////									}
//								GUI_Bar_Measure(85, 13, 1);
//							}
//				} else {
////					if(preGUI_screen_state == Graph_Screen){
////									Spectral_DrawGraph(20, 20, Line_buff, TFT_Red, Rotation_Screen_Spectral);
////								//	Spectral_RefreshGraph(Rotation_Screen_Spectral);
////					}
//									GUI_Bar_Measure(85, 13, 1);}
//			}
//
//	SD_Detect = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15);
//	if(old_sd_detect != SD_Detect){
//		GUI_Button_SD_Card(55, 426, !SD_Detect);
//		old_sd_detect = SD_Detect;
//		if(SD_Detect == 0){
//				MX_SDMMC1_SD_Init();
//				MX_FATFS_Init();
//			} else
//			{
//			FATFS_UnLinkDriver(SDPath);
//				HAL_SD_DeInit(&hsd1);
//			}
//	}
//
//	HAL_NVIC_ClearPendingIRQ(TIM7_IRQn);
//	HAL_TIM_IRQHandler(&htim7);
//}

void _Error_Handler(char *file, int line)
{
  while(1)
  {
  }

}



#ifdef  USE_FULL_ASSERT

void assert_failed(char *file, uint32_t line)
{ 

}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
