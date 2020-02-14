obj-m := simple_char_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

build:
	$(CC) -Wall app.c -o driver_app

purge:
	rm driver_app