#include "mcu_api.h"
#include "mcu_errno.h"

// Arduino Extension PIN = 3
#define TRIG 12
// Arduino Extension PIN = 4
#define ECHO 129

// From HC-SR04 datasheet
#define MIN_DISTANCE 2
#define MAX_DISTANCE 400

#define MAX_WAIT 10000
#define RET_ERROR -1

int get_distance() {
	// Send Trig signal to HC-SR04
	gpio_write(TRIG, 1);
	mcu_delay(10);
	gpio_write(TRIG, 0);

	// Read Echo signal from HC-SR04
	int i;

	i = 0;
	while ((gpio_read(ECHO) == 0) && (i < MAX_WAIT)) {
		mcu_delay(1);
		i++;
	}

	unsigned long t0 = time_us();
	if (gpio_read(ECHO) == 0 || i == MAX_WAIT) {
		return RET_ERROR;
	}

	i = 0;
	while ((gpio_read(ECHO) == 1) && (i < MAX_WAIT)) {
		mcu_delay(1);
		i++;
	}

	unsigned long t1 = time_us();
	if (gpio_read(ECHO) == 1 || i == MAX_WAIT) {
		return RET_ERROR;
	}

	unsigned long distance = (t1 - t0) / 58;
	//if (MIN_DISTANCE < distance && distance < MAX_DISTANCE) {
		return distance;
	//} else {
		//return RET_ERROR;
	//}
}

#define MAX_BUF 255
unsigned char buf[MAX_BUF];

void mcu_main() {
	// Setup Trig as OUTPUT
	gpio_setup(TRIG, 1);
	// Initially set Trig to LOW
	gpio_write(TRIG, 0);
	// Setup Echo as INPUT
	gpio_setup(ECHO, 0);

	while (1) {
		unsigned int len;
		len = host_receive(buf, MAX_BUF);

		if ((len >= 12) && (strncmp(buf, "get_distance", 12) == 0)) {
			unsigned int distance;
			distance = get_distance();
			len = mcu_snprintf(buf, MAX_BUF, "%d\n", distance);
			host_send(buf, len);
		}
	}
}
