CC = gcc
CFLAGS = -g

##################################
all: recipient sender target

sender: sender.c
    	gcc sender.c -o sender

recipient: recipient.c
	   gcc recipient.c -o recipient

target: script.bash
	./script.bash
				
clean:
	rm -f *.o
