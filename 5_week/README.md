# 2019년 2학기 수요일분반

# 임베디드 시스템 설계 및 실험 보고서

# 1조 5주차


---


# 개요

## 목표

## 세부실험내용

# 세팅


# 구현

## 전체코드
``` c
```



# 결론




25MHz를 20MHz로 세팅하기

25 /4

PREDIV2 = /5 = 5
PLL2MUL = *2 = 10
PREDIV1 = /2 = 5
PLLMUL = *4 = 20

```c
/* Configure PLLs ------------------------------------------------------*/
    /* PLL configuration: PLLCLK = ???? */
    // HSE = 25, PREDIV1_div2 : /2 , PLLMULL4: *4

	//HSE, PLL, PULLMUL 사용을 위한 초기화
	RCC->CFGR &= (uint32_t)~(RCC_CFGR_PLLXTPRE |  RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);

	//아래 코드에서 계산한 값에 *4
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 |
        RCC_CFGR_PLLMULL4);

    /* PLL2 configuration: PLL2CLK = ???? */
    /* PREDIV1 configuration: PREDIV1CLK = ???? */

	//PREDIV2, PLL2MUL, PREDIV1 사용을 위한 초기화
    RCC->CFGR2 &= (uint32_t)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
        RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);

	//HSE /5, *12, /5
    RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL12 |
        RCC_CFGR2_PREDIV1SRC_PLL2  | RCC_CFGR2_PREDIV1_DIV5);
```
