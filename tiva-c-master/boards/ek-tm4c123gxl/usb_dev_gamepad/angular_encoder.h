#ifndef __ANGULAR_ENCODER_H__
#define __ANGULAR_ENCODER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define D0    GPIO_PIN_0
#define D1    GPIO_PIN_1
#define D2    GPIO_PIN_2
#define D3    GPIO_PIN_3
#define D4    GPIO_PIN_4
#define D5    GPIO_PIN_5
#define D6    GPIO_PIN_6

#define ENCODER_GPIO_PERIPH     SYSCTL_PERIPH_GPIOB
#define ENCODER_GPIO_BASE       GPIO_PORTB_BASE
#define ENCODER_PINS           (0 | D6 | D5 | D4 | D3 | D2 | D1 | D0)

#ifdef __cplusplus
extern "C"
{
#endif

extern void EncoderInit(void);
extern uint8_t EncoderPoll(uint8_t *pui8Delta,
                             uint8_t *pui8Raw);

#ifdef __cplusplus
}
#endif

#endif
