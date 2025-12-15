name: C++ Build

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Create or fix Makefile
      run: |
        # Проверяем, есть ли Makefile
        if [ ! -f "Makefile" ]; then
          echo "Creating new Makefile..."
        else
          echo "Fixing existing Makefile..."
        fi
        
        # Создаем/перезаписываем Makefile с правилом 'all'
        cat > Makefile << 'EOF'
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Основная цель
all: build_all

# Эта цель собирает все исполняемые файлы
build_all:
	@echo "Building all tasks..."
	@echo "Если нужно изменить имена файлов - отредактируйте этот Makefile"

# Очистка
clean:
	rm -f task* program* *.o

.PHONY: all build_all clean
EOF
        
        echo "Makefile content:"
        cat Makefile
    
    - name: Build with make
      run: make all
    
    - name: List files
      run: ls -la
