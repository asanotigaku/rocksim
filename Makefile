CC	:= gcc
CXX	:= g++

BIN	:= rocksim
OBJS:= main.o

%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o:%.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

default:
	make $(BIN)

run:$(BIN)
	./$(BIN)

clean:
	rm -fr $(BIN) *.o

$(BIN):$(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)
