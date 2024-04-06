SRC_DIR = src
INCLUDE_DIR = include

CC = g++

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,%.o,$(SRCS))

SERVER_OBJ = server
CLIENT_OBJ = client

build:$(SERVER_OBJ) $(CLIENT_OBJ)

$(SERVER_OBJ):server.o utils.o
	$(CC) $^ -o $@

$(CLIENT_OBJ):client.o utils.o
	$(CC) $^ -o $@

%.o: $(SRC_DIR)/%.cpp
	$(CC) -I$(INCLUDE_DIR) -c $^ -o $@

clean:
	rm -f *.o $(SERVER_OBJ) $(CLIENT_OBJ)