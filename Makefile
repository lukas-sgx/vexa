CC = gcc
CFLAGS = -Wall -g
#PKGFLAGS = $(shell pkg-config --cflags --libs )

SRC = main.c

OUTPUT = build

BANK   = $(OUTPUT)/vexa

all: build_dir $(BANK)

build_dir:
	@echo "📂 Creating build directory..."
	@mkdir -p $(OUTPUT)

$(BANK): $(SRC)
	@echo "Compiling VEXA 🛠️" && $(CC) $(CFLAGS) $^ -o $@
	@echo "🚀 Launch VEXA" && ./$(BANK)

run:
	@echo "🚀 Launch VEXA" && ./$(BANK)

clean:
	@echo "🧹 Cleaning build files..."
	@rm -rf $(OUTPUT)