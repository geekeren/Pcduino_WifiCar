DIR=$(shell pwd)/../

INCS = -I.\
        -I$(DIR) \
        -I$(DIR)/hardware \
        -I$(DIR)/hardware/arduino \
        -I$(DIR)/hardware/arduino/cores \
        -I$(DIR)/hardware/arduino/cores/arduino \
        -I$(DIR)/hardware/arduino/variants \
        -I$(DIR)/hardware/arduino/variants/sunxi
LIBS=../libarduino.a
TARGET=output/

OBJS = wificar 
all: 
	@mkdir -p $(TARGET)
	@for i in $(OBJS); do echo "$(CXX) $(INCS) $$i.c -o $(TARGET)/$$i $(LIBS)" && $(CXX) $(INCS) $$i.c  -lpthread -o $(TARGET)/$$i $(LIBS) ; done
clean:
	@for i in $(OBJS); do rm -f $(TARGET)/$$i; done
