#include "main.h"
#include "gpio.h"
#include <stdint.h>

void SystemClock_Config(void);
void MoverMotores(uint8_t dirState);

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  while (1)
  {
	  //int dirState = 0;
	  uint8_t dirState = 0;
/*
	  if((HAL_GPIO_ReadPin(In_Arriba_GPIO_Port, In_Arriba_Pin) == 1) && (HAL_GPIO_ReadPin(In_Abajo_GPIO_Port, In_Abajo_Pin) == 1) && (HAL_GPIO_ReadPin(In_Derecha_GPIO_Port, In_Derecha_Pin) == 1) && (HAL_GPIO_ReadPin(In_Izquierda_GPIO_Port, In_Izquierda_Pin) == 1) ){

	  }
*/
	  // Adelante
	  if((HAL_GPIO_ReadPin(In_Arriba_GPIO_Port, In_Arriba_Pin) == 1)){

		  HAL_Delay(5);
		  while(HAL_GPIO_ReadPin(In_Arriba_GPIO_Port, In_Arriba_Pin) == 1);
		  HAL_Delay(5);

		  dirState = 1;
		  MoverMotores(dirState);

	  }else if((HAL_GPIO_ReadPin(In_Abajo_GPIO_Port, In_Abajo_Pin) == 1)){

		  HAL_Delay(5);
		  while(HAL_GPIO_ReadPin(In_Abajo_GPIO_Port, In_Abajo_Pin) == 1);
		  HAL_Delay(5);

		  dirState = 2;
		  MoverMotores(dirState);

	  }else if((HAL_GPIO_ReadPin(In_Derecha_GPIO_Port, In_Derecha_Pin) == 1)){

		  HAL_Delay(5);
		  while(HAL_GPIO_ReadPin(In_Derecha_GPIO_Port, In_Derecha_Pin) == 1);
		  HAL_Delay(5);

		  dirState = 3;
		  MoverMotores(dirState);

	  } else if((HAL_GPIO_ReadPin(In_Izquierda_GPIO_Port, In_Izquierda_Pin) == 1)){

		  HAL_Delay(5);
		  while(HAL_GPIO_ReadPin(In_Izquierda_GPIO_Port, In_Izquierda_Pin) == 1);
		  HAL_Delay(5);

		  while(HAL_GPIO_ReadPin(In_Izquierda_GPIO_Port, In_Izquierda_Pin) == 1){
		  dirState = 4;
		  MoverMotores(dirState);
		  }
	  }


  }

}

void MoverMotores(uint8_t dirState){

	/*
	 * 1 = Adelante
	 * 2 = Atras
	 * 3 = Derecha
	 * 4 = Izquierda
	 */

	if(dirState == 1){ 		// Adelante

		while(HAL_GPIO_ReadPin(In_Arriba_GPIO_Port, In_Arriba_Pin) == 1){

			HAL_GPIO_WritePin(Der_FORWARD_GPIO_Port, Der_FORWARD_Pin, SET);
			HAL_Delay(20);
			HAL_GPIO_WritePin(Izq_FORWARD_GPIO_Port, Izq_FORWARD_Pin, SET);
			HAL_Delay(20);
		}
	}
	else if(dirState == 2){ // Atrás
		while(HAL_GPIO_ReadPin(In_Abajo_GPIO_Port, In_Abajo_Pin) == 1){
			HAL_GPIO_WritePin(Der_BACKWARD_GPIO_Port, Der_BACKWARD_Pin, SET);
			HAL_Delay(20);
			HAL_GPIO_WritePin(Izq_BACKWARD_GPIO_Port, Izq_BACKWARD_Pin, SET);
			HAL_Delay(20);
		}

	}
	else if(dirState == 3){ // Derecha
		while(HAL_GPIO_ReadPin(In_Derecha_GPIO_Port, In_Derecha_Pin) == 1){
			HAL_GPIO_WritePin(Der_BACKWARD_GPIO_Port, Der_BACKWARD_Pin, SET);
			HAL_Delay(20);
			HAL_GPIO_WritePin(Izq_FORWARD_GPIO_Port, Izq_FORWARD_Pin, SET);
			HAL_Delay(20);
		}


	}
	else if(dirState == 4){ // Izquierda
		while(HAL_GPIO_ReadPin(In_Izquierda_GPIO_Port, In_Izquierda_Pin) == 1){
			HAL_GPIO_WritePin(Der_FORWARD_GPIO_Port, Der_FORWARD_Pin, SET);
			HAL_Delay(20);
			HAL_GPIO_WritePin(Izq_BACKWARD_GPIO_Port, Izq_BACKWARD_Pin, SET);
			HAL_Delay(20);
		}

	}
	dirState = 0;

}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif
