![Static Badge](https://img.shields.io/badge/Version-0.0.1-blue)
![Static Badge](https://img.shields.io/badge/Language-white?logo=c%2B%2B&logoColor=%2300549D&labelColor=white&color=%2300549D)


# Baremetal Drivers

## Introduction
<p style="font-size:16px;">
This is a project to learn about Microcontroller and how to control it's different peripherals 
Basically it is mostly a project for self learning purpose
</p>

## GPIO Functions

### [`gpio_clock_init`](#gpio_clock_init)
```c
void gpio_clock_init(GPIO_TypeDef *GPIOx, uint8_t state)
```
### [`gpio_init`](#gpio_init)
```c
void gpio_init(GPIO_TypeDef *GPIOx, GPIO_Config_Typedef config)
```
### [`gpio_write_pin`](#gpio_write_pin)
```c
void gpio_write_pin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t state)
```
### [`gpio_read_pin`](#gpio_read_pin)
```c
void gpio_read_pin(GPIO_TypeDef *GPIOx, uint8_t pin)
```
### [`gpio_toggle_pin`](#gpio_toggle_pin)
```c
void gpio_toggle_pin(GPIO_TypeDef *GPIOx, uint8_t pin, uint32_t delay)
```


