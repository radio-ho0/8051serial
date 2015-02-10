CC = sdcc
FLAGS = -mmcs51 --model-small --std-c99
FILENAME = main
SRC = src
OUTPUT = output

MAKEHEX = packihx

all: bin

bin: hex
	hex2bin $(OUTPUT)/$(FILENAME).hex

hex: rel
	$(MAKEHEX) $(OUTPUT)/$(FILENAME).ihx >./$(OUTPUT)/$(FILENAME).hex

rel:
	$(CC) $(FLAGS) $(SRC)/lcd1602.c -c -o $(OUTPUT)/lcd1602.rel
	$(CC) $(FLAGS) $(SRC)/serlib.c -c -o $(OUTPUT)/serlib.rel
	$(CC) $(FLAGS) $(SRC)/$(FILENAME).c $(OUTPUT)/lcd1602.rel $(OUTPUT)/serlib.rel -o $(OUTPUT)/$(FILENAME).ihx
	
.PHONY: clean

clean:
	-rm  $(OUTPUT)/*.hex 
	-rm  $(OUTPUT)/*.rel
	

fire:
	stcflash $(OUTPUT)/$(FILENAME).bin  ###
	# I hate sudo
	#sudo stcflash timer.bin  ###
