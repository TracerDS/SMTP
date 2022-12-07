EXE_FILE := SMTP

SRC_DIR := src
HPP_LIB := hpp
OBJ_DIR := obj
BIN_DIR := bin

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CXXFLAGS := -g -O2 -I./$(HPP_LIB)
LDFLAGS := 

$(OBJ_FILES): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXE_FILE): $(OBJ_FILES)
	@echo "$(LD) $(LDFLAGS) $^ -o $(BIN_DIR)/$@"

all: $(EXE_FILE)

test:
	@echo 'SRC_DIR - "$(SRC_DIR)"'
	@echo 'HPP_LIB - "$(HPP_LIB)"'
	@echo 'OBJ_DIR - "$(OBJ_DIR)"'
	@echo 'SRC_FILES - "$(SRC_FILES)"'
	@echo 'OBJ_FILES - "$(OBJ_FILES)"'
	@echo 'CXXFLAGS - "$(CXXFLAGS)"'

clean:
	rm $(OBJ_FILES)


.PHONY: clean test all