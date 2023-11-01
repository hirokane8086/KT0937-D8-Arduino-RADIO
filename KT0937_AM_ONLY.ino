#include <Wire.h>

    #define XTAL_FREQ       32768
    #define DIVIDERP        1
    #define DIVIDERN        668
    #define SYS_CFGOK       1
    #define RCLK_EN         0
    
    #define FPFD            (XTAL_FREQ / DIVIDERP * 16)
    #define DIVIDERP_H      (DIVIDERP >> 8)
    #define DIVIDERP_L      (DIVIDERP % 256)
    #define DIVIDERN_H      (DIVIDERN >> 8)
    #define DIVIDERN_L      (DIVIDERN % 256)
    #define FPFD_H          (FPFD >> 16)
    #define FPFD_M          ((FPFD >> 8) & 0x00FF)
    #define FPFD_L          (FPFD % 65536)

#define FM_50KHz_STEP       5
#define FM_100KHz_STEP      10
#define AM_1KHz_STEP        1
#define AM_5KHz_STEP        5
#define AM_9KHz_STEP        9
#define AM_10KHz_STEP       10

    #define DE                    1 
    #define FM_BAND_BOTTOM        7600
    #define FM_BAND_TOP           10800
    #define MW_BAND_BOTTOM        504
    #define MW_BAND_TOP           1710
    #define FM_STEP               FM_100KHz_STEP
    #define MW_STEP               AM_1KHz_STEP
    
#define TUNE_INT_PL               0
#define TUNE_INT_EN               1
#define TUNE_INT_MODE             1
#define INT_PIN                   0
#define CH_PIN                    2  

#define AM_BBAGC_BW               7
#define MW_BBAGC_RATIO            5
#define MW_BBAGC_HI_TH            0x1B
#define MW_BBAGC_LOW_TH           0x16
#define MW_VOLUME                 10
#define MW_GAIN                   4        //0:6dB, 1:3dB, 2:0dB, 3:-3dB, 4:-6dB, 5:-9dB, 6:-12dB, 7:-15dB, 8:-18dB

#define SW_BBAGC_RATIO            5
#define SW_BBAGC_HI_TH            0x1B
#define SW_BBAGC_LOW_TH           0x16
#define SW_VOLUME                 10
#define SW_GAIN                   4        //0:6dB, 1:3dB, 2:0dB, 3:-3dB, 4:-6dB, 5:-9dB, 6:-12dB, 7:-15dB, 8:-18dB

#define ANT_CALI_SWITCH_BAND      1
#define BLEND_COMBO_MODE          1
#define FM_NBW_CTL_EN             0
#define AM_SUP_ENHANCE            1
#define SMUTE_FILTER_EN           0
#define AM_SEL_ENHANCE            1

#define ADJACENT_SM_EN            1
#define SW_GC                     6
#define LO_SEG_RST_EN             0
#define TH_AMDEAD                 0
#define AFC_RST_EN                0 
#define AFC_RST_AUTO_EN           1
#define CHAN_VALIDCODE_SEL        1

#define FM_RSSI_BIAS              0
#define AM_RSSI_BIAS              0
#define MW_Q                      4
#define Q_CTRL_EN                 1

#define ON                        1
#define OFF                       0
#define VOLUME                    31
#define ADCGUARD                  16
#define BLEND_START_SNR           63
#define BLEND_STOP_SNR            63
#define BLEND_START_RSSI          5       //0:8, 1:10, 2:12, 3:14, 4:16, 5:18, 6:20, 7:22, 8:24, 9:26, 10:28, 11:30, 12:32, 13:34, 14:36, 15:38(unit:dbuVEMF)
#define BLEND_STOP_RSSI           15      //0:8, 1:10, 2:12, 3:14, 4:16, 5:18, 6:20, 7:22, 8:24, 9:26, 10:28, 11:30, 12:32, 13:34, 14:36, 15:38(unit:dbuVEMF)
#define BLEND_MOD                 0       //0: RSSI,    1: SNR
#define DBLND                     0       //0: blend enable,    1: blend disable
#define MONO                      0       //0: stereo,    1: force mono
#define BLEND_START_COMBO         2

#define DEPOP_TC                  3       //0:250ms,  1:500ms,    2:750ms,     3:1s
#define AUDV_DCLVL                2

#define FM_GAIN                   4       //0:0dB, 1:3.5dB, 2:6dB, 3:9.5dB, 4:-2.5dB, 5:-3.66dB, 6:-6dB, 7:-8.5dB

#define FM_AFCD                   0       //0:afc enable, 1:afc disable
#define FM_TH_AFC                 7       //0:5k, 1:15k, 2:25k, 3:35k, 4:50k, 5:100k, 6:150k, 7:200k

#define MW_AFCD                   0       //0:afc enable, 1:afc disable
#define MW_TH_AFC                 3 
#define FLT_SEL                   4       //0:1.2k, 1:2.4k, 2:3.6k, 3:4.8k, 4:6k

#define FM_DSMUTE                 0
#define FM_SMUTE_START_RSSI       5 
#define FM_SMUTE_SLOPE_RSSI       3
#define FM_SMUTE_START_SNR        0x15
#define FM_SMUTE_SLOPE_SNR        4 
#define FM_SMUTE_MIN_GAIN         3
#define TUNE_SMUTE_GAIN_FM        5

#define MW_DSMUTE                 1
#define MW_SMUTE_START_RSSI       0x17
#define MW_SMUTE_SLOPE_RSSI       4    
#define MW_SMUTE_START_SNR        0x30
#define MW_SMUTE_SLOPE_SNR        0  
#define MW_SMUTE_MIN_GAIN         1    
#define TUNE_SMUTE_GAIN_AM        3

#define SW_EN                     1
#define SW_AFCD                   0        //0:afc enable, 1:afc disable
#define SW_TH_AFC                 3 

#define SW_DSMUTE                 0
#define SW_SMUTE_START_RSSI       0x17
#define SW_SMUTE_SLOPE_RSSI       4    
#define SW_SMUTE_START_SNR        0x30
#define SW_SMUTE_SLOPE_SNR        0    
#define SW_SMUTE_MIN_GAIN         1    
#define TUNE_SMUTE_GAIN_SW        3

uint8_t RADIO = 0x35;

void setup() 
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Wire.begin();
  Wire.setClock(40000);
  digitalWrite(SDA, 0);  
  digitalWrite(SCL, 0);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.begin(9600);
  delay(2000); 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t regx ;
    regx = ReadRegister (RADIO , 0x06 );
    WriteRegister (RADIO , 0x06, (regx & 0xF8) | DIVIDERN_H);
    WriteRegister (RADIO , 0x07, DIVIDERN_L);

    regx = ReadRegister (RADIO , 0x08 ) ;
    WriteRegister (RADIO , 0x08, (regx & 0xF0) | FPFD_H);
    WriteRegister (RADIO , 0x09, FPFD_M);
    WriteRegister (RADIO , 0x0A, FPFD_L);

    regx = ReadRegister (RADIO , 0x0D);        
    WriteRegister (RADIO , 0x0D, (regx & 0xEF) | RCLK_EN<<4);        

    WriteRegister (RADIO , 0x05, DIVIDERP_L);
    regx = ReadRegister (RADIO ,0x04);
    WriteRegister (RADIO , 0x04, (regx & 0xF8) | (SYS_CFGOK << 7) | DIVIDERP_H);
////////////////////////////////////////////////////////////////////////////////////////////////////////////

    regx = ReadRegister (RADIO , 0x0F);
    WriteRegister (RADIO , 0x0F, (regx & 0xF0) | VOLUME );    
    regx = ReadRegister (RADIO , 0x4E);
    WriteRegister (RADIO , 0x4E, (regx & 0xC8) | (DEPOP_TC << 4) | AUDV_DCLVL );
    regx = ReadRegister (RADIO , 0x28 ) ;
    WriteRegister (RADIO , 0x28 , ((regx & 0b11001111) | 0b00000000)) ; // BASS BOOST

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    regx = ReadRegister (RADIO , 0x1F);
    WriteRegister (RADIO , 0x1F, (regx & 0x7F) | (TUNE_INT_PL << 7));
    regx = ReadRegister (RADIO , 0x22);
    WriteRegister (RADIO , 0x22, (regx & 0x3F) | (TUNE_INT_EN << 7) | (TUNE_INT_MODE << 6));
    regx = ReadRegister (RADIO , 0x4F);
    WriteRegister (RADIO , 0x4F, (regx & 0xFC) | INT_PIN);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    regx = ReadRegister (RADIO , 0x51);                            
    WriteRegister (RADIO , 0x51, (regx & 0xFC) | CH_PIN);

    regx = ReadRegister (RADIO , 0x76);                            
    WriteRegister (RADIO , 0x76, (regx & 0xF3) | (CHAN_VALIDCODE_SEL << 2));

    while (1)
    {
        regx = ReadRegister (RADIO , 0x1B ) ;
        if ((regx & 0x04) == 0x04) break;
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    regx = ReadRegister (RADIO , 0x1B ) ;
    WriteRegister (RADIO , 0x1B , ((regx & 0x5F) | (AFC_RST_EN << 7) | (AFC_RST_AUTO_EN << 5))) ;

    regx = ReadRegister (RADIO , 0x38);
    WriteRegister (RADIO , 0x38, (regx & 0x7F) | (SW_AFCD << 7));

    regx = ReadRegister (RADIO , 0x3E);
    WriteRegister (RADIO , 0x3E, (regx & 0xB8) | (FM_AFCD << 6) | FM_TH_AFC);

    regx = ReadRegister (RADIO , 0x3F);
    WriteRegister (RADIO , 0x3F, (regx & 0xB8) | (MW_AFCD << 6) | MW_TH_AFC);

    regx = ReadRegister (RADIO , 0x55);
    WriteRegister (RADIO , 0x55, (regx & 0xC0) | (SW_TH_AFC << 3) | MW_Q);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    regx = ReadRegister (RADIO , 0x65);            
    WriteRegister (RADIO , 0x65, (regx & 0x8F) | (MW_BBAGC_RATIO << 4) | AM_BBAGC_BW);
    regx = ReadRegister (RADIO , 0x67);            
    WriteRegister (RADIO , 0x67, (regx & 0xC0) | MW_BBAGC_HI_TH);
    regx = ReadRegister (RADIO , 0x68);            
    WriteRegister (RADIO , 0x68, (regx & 0xC0) | MW_BBAGC_LOW_TH);
    regx = ReadRegister (RADIO , 0x69);            
    WriteRegister (RADIO , 0x69, (regx & 0xF0) | MW_VOLUME);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    regx = ReadRegister (RADIO ,0x38);            
    WriteRegister (RADIO ,0x38, (regx & 0x8F) | (SW_BBAGC_RATIO << 4));
    regx = ReadRegister (RADIO ,0x3A);            
    WriteRegister (RADIO ,0x3A, (regx & 0xC0) | SW_BBAGC_HI_TH);
    regx = ReadRegister (RADIO ,0x52);            
    WriteRegister (RADIO ,0x52, (regx & 0xC0) | SW_BBAGC_LOW_TH);
    regx = ReadRegister (RADIO ,0x39);            
    WriteRegister (RADIO ,0x39, (regx & 0xF0) | SW_VOLUME);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    regx = ReadRegister (RADIO ,0x2A);            
    WriteRegister (RADIO ,0x2A, (regx & 0x8F) | (FM_GAIN << 4));
    regx = ReadRegister (RADIO ,0x38);            
    WriteRegister (RADIO ,0x38, (regx & 0xF0) | SW_GAIN);               
    WriteRegister (RADIO ,0x62, (MW_GAIN << 4) | FLT_SEL);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    regx = ReadRegister (RADIO ,0x29);
    WriteRegister (RADIO ,0x29, (regx & 0xEF) | (BLEND_MOD << 4));    
    regx = ReadRegister (RADIO ,0x2B);
    WriteRegister (RADIO ,0x2B, (regx & 0x76) | (MONO << 7) | (DE << 3) | DBLND);    
    WriteRegister (RADIO ,0x2C, (BLEND_START_RSSI << 4) | BLEND_STOP_RSSI);  
    regx = ReadRegister (RADIO ,0x34);            
    WriteRegister (RADIO ,0x34, (regx & 0xC0) | BLEND_START_SNR);            
    regx = ReadRegister (RADIO ,0x35);            
    WriteRegister (RADIO ,0x35, (regx & 0xC0) | BLEND_STOP_SNR);          
    regx = ReadRegister (RADIO ,0x7E);            
    WriteRegister (RADIO ,0x7E, (regx & 0x8F) | (BLEND_START_COMBO << 4));   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    regx = ReadRegister (RADIO ,0x16);
    WriteRegister (RADIO ,0x16, (regx & 0xFC) | TUNE_SMUTE_GAIN_FM);
    regx = ReadRegister (RADIO ,0x19);
    WriteRegister (RADIO ,0x19, (regx & 0x03) | (MW_SMUTE_MIN_GAIN << 5) | (FM_SMUTE_MIN_GAIN << 2));
    regx = ReadRegister (RADIO ,0x1A);              
    WriteRegister (RADIO ,0x1A, (regx & 0x3F) | (FM_DSMUTE << 7) | (MW_DSMUTE << 6));
    regx = ReadRegister (RADIO ,0x1D);
    WriteRegister (RADIO ,0x1D, (regx & 0x80) | MW_SMUTE_START_RSSI);
    regx = ReadRegister (RADIO ,0x1E);
    WriteRegister (RADIO ,0x1E, (regx & 0xF8) | MW_SMUTE_SLOPE_RSSI);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    regx = ReadRegister (RADIO ,0x1F);
    WriteRegister (RADIO ,0x1F, (regx & 0x88) | (FM_SMUTE_START_RSSI << 4) | FM_SMUTE_SLOPE_RSSI);
    regx = ReadRegister (RADIO ,0x20);
    WriteRegister (RADIO ,0x20, (regx & 0x80) | MW_SMUTE_START_SNR);
    regx = ReadRegister (RADIO ,0x21);
    WriteRegister (RADIO ,0x21, (regx & 0x08) | (Q_CTRL_EN << 7) | (MW_SMUTE_SLOPE_SNR << 4) | FM_SMUTE_SLOPE_SNR);
    regx = ReadRegister (RADIO ,0x22);
    WriteRegister (RADIO ,0x22, (regx & 0xC0) | FM_SMUTE_START_SNR);
    regx = ReadRegister (RADIO ,0x23);
    WriteRegister (RADIO ,0x23, (regx & 0xFE) | ADJACENT_SM_EN);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    regx = ReadRegister (RADIO ,0x53);
    WriteRegister (RADIO ,0x53, (regx & 0xE3) | (TUNE_SMUTE_GAIN_AM << 2));

    WriteRegister (RADIO ,0xF4, (SW_DSMUTE << 7) | SW_SMUTE_START_SNR);
    WriteRegister (RADIO ,0xF5, SW_SMUTE_START_RSSI);
    regx = ReadRegister (RADIO ,0xF6);
    WriteRegister (RADIO ,0xF6, (regx & 0xC0) | (SW_SMUTE_SLOPE_SNR << 3) | SW_SMUTE_SLOPE_RSSI);
    WriteRegister (RADIO ,0xF7, (SW_SMUTE_MIN_GAIN << 3) | (TUNE_SMUTE_GAIN_SW << 2));

    regx = ReadRegister (RADIO ,0x16);                         
    WriteRegister (RADIO ,0x16, (regx & 0xEF) | (SW_EN << 4)); 

    regx = ReadRegister (RADIO ,0x2F);
    WriteRegister (RADIO ,0x2F, (ANT_CALI_SWITCH_BAND << 5) | (BLEND_COMBO_MODE << 4) | (FM_NBW_CTL_EN << 3) | 
                        (AM_SUP_ENHANCE << 2) | (SMUTE_FILTER_EN << 1) | AM_SEL_ENHANCE);   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    regx = ReadRegister (RADIO ,0x30);                         
    WriteRegister (RADIO ,0x30, (regx & 0xE0) | FM_RSSI_BIAS);
    regx = ReadRegister (RADIO ,0x63);                         
    WriteRegister (RADIO ,0x63, (regx & 0xE0) | AM_RSSI_BIAS);
    
    regx = ReadRegister (RADIO ,0x24);
    WriteRegister (RADIO ,0x24, (regx & 0x7F));

    regx = ReadRegister (RADIO ,0x2D);
    WriteRegister (RADIO ,0x2D, (regx & 0xF8) | SW_GC);
    regx = ReadRegister (RADIO ,0x37);            
    WriteRegister (RADIO ,0x37, (regx & 0xDF) | (LO_SEG_RST_EN << 5));
    regx = ReadRegister (RADIO ,0x3B);            
    WriteRegister (RADIO ,0x3B, (regx & 0x8F) | (TH_AMDEAD << 4));

    regx = ReadRegister (RADIO , 0x18 ) ;
    WriteRegister (RADIO , 0x18 , ((regx & 0b11001111) | 0b00010000)) ; // FMBANDSP

    regx = ReadRegister (RADIO , 0x18 ) ;
    WriteRegister (RADIO , 0x18 , ((regx & 0b11111100) | 0b00000000)) ; // AMBANDSP

///////////////////////////////////////////////////////////////////////////////////////////////////////////

ADC_Switch(OFF) ;

regx = ReadRegister (RADIO , 0x8C ) ;
WriteRegister (RADIO , 0x8C , ((regx & 0b10000000) | 0x06 )) ; // AM_HIGH_CHAN 14:8
WriteRegister (RADIO , 0x8D , ((regx & 0b00000000) | 0x54 )) ; // AM_HIGH_CHAN 7:0
regx = ReadRegister (RADIO , 0x88 ) ;
WriteRegister (RADIO , 0x88 , ((regx & 0b11110000) | 0x06 )) ; // FM_HIGH_CHAN 11:8
WriteRegister (RADIO , 0x89 , 0b10111000) ; // FM_HIGH_CHAN 7:0
regx = ReadRegister (RADIO , 0x98 ) ;
WriteRegister (RADIO , 0x98 , ((regx & 0b10000000) | 0x02 )) ; // LOW_CHAN 14:8
WriteRegister (RADIO , 0x99 , ((regx & 0b00000000) | 0x0A )) ; // LOW_CHAN 7:0
regx = ReadRegister (RADIO , 0x9A ) ;
WriteRegister (RADIO , 0x9A , ((regx & 0b11110000) | 0x04 )) ; //CHAN_NUM 11:8
WriteRegister (RADIO , 0x9B , 0x4A) ;                          //CHAN_NUM 7:0
regx = ReadRegister (RADIO , 0x88 ) ;
WriteRegister (RADIO , 0x88 , ((regx & 0b00111111) | 0b11000000 )) ; // cange band | AM

ADC_Switch(ON) ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WriteRegister (RADIO , 0xA0 , 0x17) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() 

{

Serial.print("AM= ");
Serial.println (bitRead(ReadRegister(RADIO,0x88),6));
delay(1000) ;

uint16_t regx = AM_GetFreq() ;
Serial.println((regx), DEC ) ;
delay(1000) ;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WriteRegister (uint8_t devadr , uint8_t regadr , uint8_t dataval)
  {
    Wire.beginTransmission(devadr); // device
    Wire.write(regadr);             // register
    Wire.write(dataval);            // data
    Wire.endTransmission(0);
  }
/************************************************************************************/
/************************************************************************************/
uint8_t ReadRegister(uint8_t devadr ,uint8_t regadr)
  {  
    Wire.beginTransmission(devadr);
    Wire.write(regadr);
    Wire.endTransmission(0);
    Wire.requestFrom(devadr,1,0);
    return Wire.read();
  }
/************************************************************************************/
/************************************************************************************/
void ChangeBit(byte devadr, byte regadr, byte bitpos, bool setting)
  {
    byte r = ReadRegister(devadr, regadr);  
    if (setting == 1)
        {
            bitSet     (r, bitpos);
        } 
    else
    if (setting == 0)  
        {
            bitClear   (r, bitpos);
        }
    WriteRegister(devadr, regadr, r);
  }
/************************************************************************************/
/************************************************************************************/
uint8_t getAMFM(void)
 {
 uint8_t regx ;
 regx = bitRead(ReadRegister(RADIO,0x88),6);
 return(regx) ;
 }
/************************************************************************************/
/************************************************************************************/

void ByteW (int Register_Address, int Byte_Data)
{
    Wire.beginTransmission(RADIO);
    Wire.write(Register_Address);
    Wire.write(Byte_Data);
    Wire.endTransmission();
}

/************************************************************************************/
/************************************************************************************/
bool PreInit(void)        
{
    byte regx;
    byte regy;
    byte i;
    for (i = 0;i < 10;i++)
    {
        delay(10);
        regx = ReadRegister(RADIO , 0x02);
        regy = ReadRegister(RADIO , 0x03);
        regx = ( (regx << 8) | regy );
          if (regx == 0x4B54) return(1);
    }
    return(0);
}
/************************************************************************************/
/************************************************************************************/
bool VolumeSet(uint8_t cVol)
{
    uint8_t regx ;

    regx = ReadRegister (RADIO , 0x0F);
    WriteRegister (RADIO , 0x0F, (regx & 0xE0) | cVol ) ;

    return(1);
}
/************************************************************************************/
/************************************************************************************/
uint8_t FM_ReadRSSI(void) //dbuvmf
{
    uint8_t regx;
    regx = ReadRegister (RADIO , 0xE6);
    return(3 + (regx & 0x7F));
} 
/************************************************************************************/
/************************************************************************************/
bool Tuning_Indicator(void)
{
    uint8_t regx;

    regx = ReadRegister (RADIO , 0xDE);
    regx = regx & 0x04;
        
    return(regx);
}
/************************************************************************************/
/************************************************************************************/
uint8_t GetSNR(void)
{
    uint8_t regx;
    regx = ReadRegister (RADIO ,0xE2);
    regx = regx & 0x3F;
    return(regx);
}
/************************************************************************************/
/************************************************************************************/
uint8_t AM_ReadRSSI(void) //unit is dbm
{
    uint8_t regx;
    regx = ReadRegister (RADIO ,0xEA);
    return(3+(regx & 0x7F));
}
/************************************************************************************/
/************************************************************************************/
uint16_t AM_GetCap(void)
{
    uint8_t regx,regy;
    regx = ReadRegister (RADIO ,0x56);
    regy = ReadRegister (RADIO ,0x57);
    return(((regx & 0x3F) << 8) | regy );
}
/************************************************************************************/
/************************************************************************************/
uint8_t AM_GetSNR(void)
{
    uint8_t regx;
    regx = ReadRegister (RADIO ,0xEC);
    regx = regx & 0x7F;
    return(regx);
}
/************************************************************************************/
/************************************************************************************/
uint16_t AM_GetFreq(void)
{
    uint8_t regx,regy;
    uint16_t a;
    regx = ReadRegister (RADIO ,0xe4);
    regy = ReadRegister (RADIO ,0xe5);
    a = ((regx & 0x7F) << 8) | regy ;
    return(a);
}
/************************************************************************************/
/************************************************************************************/
uint16_t FM_GetFreq(void)
{
    uint16_t temp;
    temp= (AM_GetFreq()*5);
    return(temp);
}
/************************************************************************************/
/************************************************************************************/
bool GetSTEREO(void)
{
    uint8_t regx;

    regx = ReadRegister (RADIO ,0x1C);
        
    return(regx);
}
/************************************************************************************/
/************************************************************************************/
void ADC_Switch(bool adcSwitch)
{
    uint8_t regx;
    if(ON==adcSwitch)
    {
        regx = ReadRegister (RADIO ,0x71);
        WriteRegister (RADIO ,0x71, (regx & 0X7F) | 0x04); //adc enable
    }
    else
    {
        regx = ReadRegister (RADIO ,0x71);
        WriteRegister (RADIO ,0x71, regx | 0x80);          //adc disable
    }
}
/************************************************************************************/
/************************************************************************************/
