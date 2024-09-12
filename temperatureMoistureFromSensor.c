#define ADC_BASE 0xFF204000 	
//the base address of the adc
#define refresh 0xFF204004
//the address to write into for auto update
#define MOTOR_OUT  0xFF200060 
//J1 GPIO 
#define LEDS 0xFF200000
//do it on a scale of 5 where 0 is full of water and around 5 is dry (dc voltages from 0-5V))

int main(void){
volatile int* HUM_SENSOR=(int*)ADC_BASE;//base address channel0, is the channel of interest
volatile int* LEDs=(int*)LEDS;
volatile int* autoRef=(int*)refresh;
unsigned int tempData = 0;
unsigned int temp = 0;
*(autoRef) = 1; //Start the ADC read
while (1){
tempData = *(HUM_SENSOR); //Get the value of the selected channel
tempData=tempData&4095;
temp=(((float)tempData/4095)*1031+174)*2;
temp=((((float)temp-174)/6.25)-40)*2; 
*(LEDs) = temp; //Display the value on the LEDs
for(int i=0; i<5000000;i++);
}
//wait for human readable time
return 0;
}
