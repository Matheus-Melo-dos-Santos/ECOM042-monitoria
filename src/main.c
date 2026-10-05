/*******************************************************************
 * @file main.c
 *
 * @brief Main file.
 * @author João Matheus Nascimento Dias (jmnd@ic.ufal.br)
 * @author José Félix de Oliveira Neto (jfon@ic.ufal.br)
 * @author Matheus Melo dos Santos (mms6@ic.ufal.br)
 * @version 0.1
 * @date 26/08/2026
 *******************************************************************/

#include <zephyr/kernel.h>

#include "board_io.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/gpio/gpio_emul.h>

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

int main(void)
{
	/* TODO (Atividade-03): chamar io_init() e, pra cada valor da sequência
	 * 0, 1, 0, 1: simular o botão e imprimir "Button: X -> LED: X".
	 */

	const int sequence[] = {0, 1, 0, 1};
	int ret = io_init();

	if (ret < 0) {
		return ret;
	}

	for (int i = 0; i < 4; i++) {

		ret = gpio_emul_input_set(button.port, button.pin, sequence[i]);

		if (ret < 0) {
			return -1;
		}

		const int button_value = button_read();

		if (button_value < 0) {
			return -1;
		}

		const int led_state = led_set(button_value);

		if (led_state < 0) {
			return -1;
		}

		const int led_value = gpio_emul_output_get(led.port, led.pin);

		if (led_value < 0) {
			return -1;
		}

		printk("Button: %d -> LED: %d\n", button_value, led_value);
	}

	return 0;
}
