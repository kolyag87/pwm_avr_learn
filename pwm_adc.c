//Code for Attiny 13

#define F_CPU 16000000
#define LED PB0
#define LED1 PB1
#define LED2 PB2

#include <avr/io.h>
#include <util/delay.h>

int s = 0;
int s1 = 0;
int i = 0;

void adc_setup (void)
{
    // Set the ADC input to PB2/ADC1
    ADMUX |= (1 << MUX0);
    ADMUX |= (1 << ADLAR);
 
    // Set the prescaler to clock/128 & enable ADC
    // At 9.6 MHz this is 75 kHz.
    // See ATtiny13 datasheet, Table 14.4.
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}
 
int adc_read (void)
{
    // Start the conversion
    ADCSRA |= (1 << ADSC);
 
    // Wait for it to finish
    while (ADCSRA & (1 << ADSC));
 
    return ADCH;
}
 
void pwm_setup (void)
{
    // Set Timer 0 prescaler to clock/8.
    // At 9.6 MHz this is 1.2 MHz.
    // See ATtiny13 datasheet, Table 11.9.
    TCCR0B |= (1 << CS01);
 
    // Set to 'Fast PWM' mode
    // Enable 'Fast PWM'
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
 
    // Clear OC0B and OC0A(!!!) output on compare match, upwards counting.
    TCCR0A |= (2 << COM0A0) | (2 << COM0B0);
}
 
void pwm_write (int val)
{
    OCR0B = val;
}

void _delay(int ms) {
    while (ms > 0) {
        _delay_ms(0.1);
        --ms;
    }
}
 
int main (void)
{
    DDRB |= (1 << LED) | (1 << LED1);
    DDRB &= ~(1 << LED2);
    pwm_setup();
  
    while (1) {
        s = rand() % 200; 
        //200 is initial value - brightness control can be
        //implemented by decreasing or increasing this value.
        //Potentiometer to PB2 as ADC input will make this feature on.
        //But it depends on the period for delay - think about it
        OCR0A = s;
        s = (int) s/4;
        _delay(s);
        s1 = rand() % 200;
        OCR0B = s1;
        s1 = (int) s1/4;
        _delay(s1);
    }
}
